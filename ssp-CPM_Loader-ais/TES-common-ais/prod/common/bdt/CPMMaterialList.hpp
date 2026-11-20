#pragma once

#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <memory>
#include <boost/tokenizer.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string.hpp>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include "CPMConfigDataParser.hpp"
#include "CPMConfigDataBuilder.hpp"
#include "CPMList.h"

#ifndef BDT_CPMMATERIALLIST_HPP
#define BDT_CPMMATERIALLIST_HPP

namespace tes_common_ais {
    struct CPMMaterialListEntry {
        std::string name;
        uint32_t id;
        float density;

        friend bool operator==(const CPMMaterialListEntry& a, const CPMMaterialListEntry& b) {
            if ((a.name == b.name) && (a.id == b.id) && (a.density == b.density)) {
                return true;
            }
            return false;
        }

        friend bool operator!=(const CPMMaterialListEntry& a, const CPMMaterialListEntry& b) {
            return !(a == b);
        }
    };

    class CPMMaterialList {
    public:
        CPMMaterialList() = default;

        CPMMaterialList(std::istream& is, bool csv = false) {
            if (csv) {
                std::string line;
                uint32_t lineNumber = 0;
                CPMListWeightUnits csvUnits = CPMListWeightUnits::TONNES;

                while (std::getline(is, line)) {
                    ++lineNumber;

                    // Skip the first line, the second line contains the units.
                    if (2 == lineNumber) {
                        boost::algorithm::trim(line);
                        boost::tokenizer<boost::escaped_list_separator<char>> tok(line);
                        std::vector<std::string> splitline(tok.begin(), tok.end());
                        if (splitline.size() >= 3) {
                            csvUnits = densityUnitsStringToWeightUnits(splitline[2]);
                        }
                    }
                    else if (lineNumber > 2) {
                        boost::algorithm::trim(line);
                        if (line.empty()) {
                            continue;
                        }

                        // Split the line, allowing for commas within text fields
                        boost::tokenizer<boost::escaped_list_separator<char>> tok(line);
                        std::vector<std::string> splitline(tok.begin(), tok.end());

                        // Check if there are three entries
                        if (splitline.size() < 3) {
                            AIS_LOG_ERROR("Not enough columns");
                            continue;
                        }

                        // First column is the name
                        std::string name(splitline[0]);

                        // Remove any quotation marks and truncate
                        name.erase(std::remove(name.begin(), name.end(), '"'), name.end());

                        // Second column is ID
                        uint32_t id = std::atol(splitline[1].c_str());

                        // Third column is target weight
                        float density = std::atof(splitline[2].c_str());

                        // Convert to metric
                        density = convertDensityFromUnits(density, csvUnits);

                        materials_.push_back(CPMMaterialListEntry{ name, id, density });
                    }
                }
            }
            else {
                { // Boost Property Tree
                    boost::property_tree::ptree tree;
                    boost::property_tree::read_json(is, tree);
                    boost::property_tree::ptree materialList = tree.get_child("MaterialList");
                    for (const auto& it : materialList) {
                        materials_.push_back(
                            CPMMaterialListEntry{
                                it.second.get<std::string>("name"),
                                it.second.get<uint32_t>("id"),
                                it.second.get<float>("density")
                            }
                        );
                    }
                }
            }
        }

        CPMMaterialList(const std::vector<unsigned char>& bdtData) {
            CPMConfigDataParser parser{ 0xC831 };
            parser.parse(bdtData);
            for (const auto& en : parser.getAllRecords()) {
                const std::string& name = en.getName();
                const std::map<uint32_t, GidData>& gidData = en.getGidData();

                // Parse Material ID (GID 0x000003FD)
                uint32_t id;
                try {
                    const GidData& d = gidData.at(0x000003FD);
                    id = d.getData<uint32_t>();
                }
                catch (const std::exception& e) {
                    // not found or conversion error
                    (void)e;
                    id = 0;
                }

                // Parse Material Density (GID 0x0000049D)
                float density;
                try {
                    const GidData& d = gidData.at(0x0000049D);
                    density = d.getData<float>();
                }
                catch (const std::exception& e) {
                    // not found or conversion error
                    (void)e;
                    density = 0.f;
                }

                materials_.push_back(CPMMaterialListEntry{ name, id, density });
            }
        }

        void toJson(std::ostream& os) const {
            rapidjson::StringBuffer sb;
            rapidjson::PrettyWriter<rapidjson::StringBuffer> writer{ sb };
            //rapidjson::Writer<rapidjson::StringBuffer> writer{ sb };
            writer.SetIndent(' ', 2);
            writer.SetMaxDecimalPlaces(2);
            writer.StartObject();
            writer.Key("MaterialList");
            writer.StartArray();
            for (const auto& m : materials_) {
                writer.StartObject();
                writer.Key("name"); writer.String(m.name);
                writer.Key("id"); writer.Uint(m.id);
                writer.Key("density"); writer.Double(m.density);
                writer.EndObject();
            }
            writer.EndArray();
            writer.EndObject();
            os << sb.GetString();
        }

        void toCsv(std::ostream& os, bool headerRow = false, CPMListWeightUnits weightUnits = CPMListWeightUnits::TONNES) const {
            if (headerRow) {
                os << "Material Name,Material ID,Material Density" << std::endl;
                os << "text,integer" << "," << weightUnitsToDensityUnitsString(weightUnits) << std::endl;
            }
            for (const auto& m : materials_) {
                os << "\"\"\"" + m.name + "\"\"\"," << m.id << "," << convertDensityToUnits(m.density, weightUnits) << std::endl;
            }
        }

        void toBdt(std::vector<unsigned char>& vo) const {
            CPMConfigDataBuilder builder{ 0xC831 };

            // Material Id
            auto pMaterialIdEncoding = std::make_shared<const GidEncoding>(
                0x000003FD, // Gid
                2, // Version
                GidEncoding::GidDsiDefinition::DSI_NOT_SUPPORTED,
                GidEncoding::GidDataOrder::LSB_FIRST,
                GidEncoding::GidDataLengthType::FIXED,
                32U,
                GidEncoding::GidDataType::SCALED_UNSIGNED_ZERO_OFFSET,
                std::vector<unsigned char>{ 0 /* Scaling */, 0 /* Units */}
            );

            // Material Density
            auto pMaterialDensityEncoding = std::make_shared<const GidEncoding>(
                0x0000049D, // Gid
                2, // Version
                GidEncoding::GidDsiDefinition::LARGEST_32_VALUES,
                GidEncoding::GidDataOrder::LSB_FIRST,
                GidEncoding::GidDataLengthType::FIXED,
                16U,
                GidEncoding::GidDataType::SCALED_UNSIGNED_ZERO_OFFSET,
                std::vector<unsigned char>{ 0 /* Scaling */, 132 /* Units */}
            );

            // Add the gid encodings, in the order that they are to be encoded
            builder.addGidEncoding(pMaterialIdEncoding);
            builder.addGidEncoding(pMaterialDensityEncoding);

            // Then add the trucks
            uint32_t recordIdNumber = 0;
            for (const auto& m : materials_) {
                builder.addEntryNameRecord(
                    EntryNameRecord{
                        recordIdNumber,
                        m.name,
                        { // map<uint32_t, GidData>
                            {
                                pMaterialIdEncoding->getGid(),
                                GidData{ pMaterialIdEncoding, m.id }
                            },
                            {
                                pMaterialDensityEncoding->getGid(),
                                GidData{ pMaterialDensityEncoding, m.density }
                            }
                        },
                        0U, 0U, 0U
                    }
                );
                recordIdNumber++;
            }

            builder.build(vo);
        }

        friend std::ostream& operator<<(std::ostream& out, const CPMMaterialList& list) {
            list.toJson(out);
            return out;
        }

        friend bool operator==(const CPMMaterialList& a, const CPMMaterialList& b) {
            const std::vector<CPMMaterialListEntry>& v1 = a.getMaterials();
            const std::vector<CPMMaterialListEntry>& v2 = b.getMaterials();
            if (v1.size() != v2.size()) {
                return false;
            }

            for (size_t ii = 0; ii < v1.size(); ii++) {
                if (v1[ii] != v2[ii]) {
                    return false;
                }
            }

            return true;
        }

        friend bool operator!=(const CPMMaterialList& a, const CPMMaterialList& b) {
            return !(a == b);
        }

        const std::vector<CPMMaterialListEntry>& getMaterials() const {
            return materials_;
        }

        void addMaterial(CPMMaterialListEntry&& material) {
            materials_.push_back(std::move(material));
        }

    private:
        std::vector<CPMMaterialListEntry> materials_;

        static inline CPMListWeightUnits densityUnitsStringToWeightUnits(const std::string& densityUnitsString) {
            CPMListWeightUnits weightUnits;
            if ("lb/ft3" == densityUnitsString) {
                weightUnits = CPMListWeightUnits::TONS;
            }
            else {
                weightUnits = CPMListWeightUnits::TONNES;
            }
            return weightUnits;
        }

        static inline std::string weightUnitsToDensityUnitsString(CPMListWeightUnits weightUnits) {
            std::string weightUnitsString;
            if ((CPMListWeightUnits::TONS == weightUnits) ||
                    (CPMListWeightUnits::KLBS == weightUnits) ||
                    (CPMListWeightUnits::LBS == weightUnits)) {
                weightUnitsString = "lb/ft3";
            }
            else {
                weightUnitsString = "kg/m3";
            }
            return weightUnitsString;
        }

        static inline float convertDensityToUnits(float value, CPMListWeightUnits toWeightUnits) {
            float result;
            if ((CPMListWeightUnits::TONS == toWeightUnits) ||
                    (CPMListWeightUnits::KLBS == toWeightUnits) ||
                    (CPMListWeightUnits::LBS == toWeightUnits)) {
                // English weight units gets converted from kg/m3 to lb/ft3
                result = value * 0.062428f;
            }
            else {
                // Other weight units remain kg/m3
                result = value;
            }
            return result;
        }

        static inline float convertDensityFromUnits(float value, CPMListWeightUnits fromWeightUnits) {
            float result;
            if ((CPMListWeightUnits::TONS == fromWeightUnits) ||
                    (CPMListWeightUnits::KLBS == fromWeightUnits) ||
                    (CPMListWeightUnits::LBS == fromWeightUnits)) {
                // English weight units gets converted to kg/m3 from lb/ft3
                result = value / 0.062428f;
            }
            else {
                // Other weight units remain kg/m3
                result = value;
            }
            return result;
        }
    };
}

#endif
