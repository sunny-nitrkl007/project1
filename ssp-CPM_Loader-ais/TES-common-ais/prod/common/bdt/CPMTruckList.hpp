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

#ifndef BDT_CPMTRUCKLIST_HPP
#define BDT_CPMTRUCKLIST_HPP

namespace tes_common_ais {
    struct CPMTruckListEntry {
        std::string name;
        uint32_t id;
        float targetWeight;

        friend bool operator==(const CPMTruckListEntry& a, const CPMTruckListEntry& b) {
            if ((a.name == b.name) && (a.id == b.id) && (a.targetWeight == b.targetWeight)) {
                return true;
            }
            return false;
        }

        friend bool operator!=(const CPMTruckListEntry& a, const CPMTruckListEntry& b) {
            return !(a == b);
        }
    };

    class CPMTruckList {
    public:
        CPMTruckList() = default;

        CPMTruckList(std::istream& is, bool csv = false) {
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
                            csvUnits = weightUnitsStringToWeightUnits(splitline[2]);
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
                        float targetWeight = std::atof(splitline[2].c_str());

                        // Convert to metric
                        targetWeight = convertWeightFromUnits(targetWeight, csvUnits);

                        trucks_.push_back(CPMTruckListEntry{ name, id, targetWeight });
                    }
                }
            }
            else {
                { // Boost Property Tree
                    boost::property_tree::ptree tree;
                    boost::property_tree::read_json(is, tree);
                    boost::property_tree::ptree truckList = tree.get_child("TruckList");
                    for (const auto& it : truckList) {
                        trucks_.push_back(
                            CPMTruckListEntry{
                                it.second.get<std::string>("name"),
                                it.second.get<uint32_t>("id"),
                                it.second.get<float>("targetWeight")
                            }
                        );
                    }
                }
            }
        }

        CPMTruckList(const std::vector<unsigned char>& bdtData) {
            CPMConfigDataParser parser{ 0xC834 };
            parser.parse(bdtData);
            for (const auto& en : parser.getAllRecords()) {
                const std::string& name = en.getName();
                const std::map<uint32_t, GidData>& gidData = en.getGidData();

                // Parse Truck Payload ID (GID 0x000003F7)
                uint32_t id;
                try {
                    const GidData& d = gidData.at(0x000003F7);
                    id = d.getData<uint32_t>();
                }
                catch (const std::exception& e) {
                    // not found or conversion error
                    (void)e;
                    id = 0;
                }

                // Parse Truck Payload Target Weight (GID 0x000003F8)
                float targetWeight;
                try {
                    const GidData& d = gidData.at(0x000003F8);
                    targetWeight = d.getData<float>();
                }
                catch (const std::exception& e) {
                    // not found or conversion error
                    (void)e;
                    targetWeight = 0.f;
                }

                trucks_.push_back(CPMTruckListEntry{ name, id, targetWeight });
            }
        }

        void toJson(std::ostream& os) const {
            rapidjson::StringBuffer sb;
            rapidjson::PrettyWriter<rapidjson::StringBuffer> writer{ sb };
            //rapidjson::Writer<rapidjson::StringBuffer> writer{ sb };
            writer.SetIndent(' ', 2);
            writer.SetMaxDecimalPlaces(3);
            writer.StartObject();
            writer.Key("TruckList");
            writer.StartArray();
            for (const auto& t : trucks_) {
                writer.StartObject();
                writer.Key("name"); writer.String(t.name);
                writer.Key("id"); writer.Uint(t.id);
                writer.Key("targetWeight"); writer.Double(t.targetWeight);
                writer.EndObject();
            }
            writer.EndArray();
            writer.EndObject();
            os << sb.GetString();
        }

        void toCsv(std::ostream& os, bool headerRow = false, CPMListWeightUnits weightUnits = CPMListWeightUnits::TONNES) const {
            if (headerRow) {
                os << "Truck Name,Truck Payload ID,Truck Payload Target Weight" << std::endl;
                os << "text,integer" << "," << weightUnitsToWeightUnitsString(weightUnits) << std::endl;
            }
            for (const auto& t : trucks_) {
                os << "\"\"\"" + t.name + "\"\"\"," << t.id << "," << convertWeightToUnits(t.targetWeight, weightUnits) << std::endl;
            }
        }

        void toBdt(std::vector<unsigned char>& vo) const {
            CPMConfigDataBuilder builder{ 0xC834 };

            // Truck Payload Id
            auto pTruckPayloadIdEncoding = std::make_shared<const GidEncoding>(
                0x000003F7, // Gid
                2, // Version
                GidEncoding::GidDsiDefinition::DSI_NOT_SUPPORTED,
                GidEncoding::GidDataOrder::LSB_FIRST,
                GidEncoding::GidDataLengthType::FIXED,
                32U,
                GidEncoding::GidDataType::SCALED_UNSIGNED_ZERO_OFFSET,
                std::vector<unsigned char>{ 0 /* Scaling */, 0 /* Units */}
            );

            // Truck Payload Target Weight
            auto pTruckPayloadTargetWeightEncoding = std::make_shared<const GidEncoding>(
                0x000003F8, // Gid
                2, // Version
                GidEncoding::GidDsiDefinition::LARGEST_32_VALUES,
                GidEncoding::GidDataOrder::LSB_FIRST,
                GidEncoding::GidDataLengthType::FIXED,
                32U,
                GidEncoding::GidDataType::SCALED_UNSIGNED_ZERO_OFFSET,
                std::vector<unsigned char>{ 12 /* Scaling */, 34 /* Units */}
            );

            // Add the gid encodings, in the order that they are to be encoded
            builder.addGidEncoding(pTruckPayloadIdEncoding);
            builder.addGidEncoding(pTruckPayloadTargetWeightEncoding);

            // Then add the trucks
            uint32_t recordIdNumber = 0;
            for (const auto& t : trucks_) {
                builder.addEntryNameRecord(
                    EntryNameRecord{
                        recordIdNumber,
                        t.name,
                        { // map<uint32_t, GidData>
                            {
                                pTruckPayloadIdEncoding->getGid(),
                                GidData{ pTruckPayloadIdEncoding, t.id }
                            },
                            {
                                pTruckPayloadTargetWeightEncoding->getGid(),
                                GidData{ pTruckPayloadTargetWeightEncoding, t.targetWeight }
                            }
                        },
                        0U, 0U, 0U
                    }
                );
                recordIdNumber++;
            }

            builder.build(vo);
        }

        friend std::ostream& operator<<(std::ostream& out, const CPMTruckList& list) {
            list.toJson(out);
            return out;
        }

        friend bool operator==(const CPMTruckList& a, const CPMTruckList& b) {
            const std::vector<CPMTruckListEntry>& v1 = a.getTrucks();
            const std::vector<CPMTruckListEntry>& v2 = b.getTrucks();
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

        friend bool operator!=(const CPMTruckList& a, const CPMTruckList& b) {
            return !(a == b);
        }

        const std::vector<CPMTruckListEntry>& getTrucks() const {
            return trucks_;
        }

        void addTruck(CPMTruckListEntry&& truck) {
            trucks_.push_back(std::move(truck));
        }

    private:
        std::vector<CPMTruckListEntry> trucks_;

        static inline CPMListWeightUnits weightUnitsStringToWeightUnits(const std::string& weightUnitsString) {
            CPMListWeightUnits weightUnits;
            if (weightUnitsString.rfind("Ton", 0) == 0) {
                // Starts with "Ton"
                weightUnits = CPMListWeightUnits::TONS;
            }
            else if (weightUnitsString.rfind("kg", 0) == 0) {
                // Starts with "kg"
                weightUnits = CPMListWeightUnits::KGS;
            }
            else if (weightUnitsString.rfind("lb", 0) == 0) {
                // Starts with "lb"
                if ("lbsx1000" == weightUnitsString) {
                    weightUnits = CPMListWeightUnits::KLBS;
                }
                else {
                    weightUnits = CPMListWeightUnits::LBS;
                }
            }
            else {
                weightUnits = CPMListWeightUnits::TONNES;
            }
            return weightUnits;
        }

        static inline std::string weightUnitsToWeightUnitsString(CPMListWeightUnits weightUnits) {
            std::string weightUnitsString;
            if (CPMListWeightUnits::TONS == weightUnits) {
                weightUnitsString = "Tons";
            }
            else if (CPMListWeightUnits::KLBS == weightUnits) {
                weightUnitsString = "lbsx1000";
            }
            else if (CPMListWeightUnits::LBS == weightUnits) {
                weightUnitsString = "lbs";
            }
            else if (CPMListWeightUnits::KGS == weightUnits) {
                weightUnitsString = "kg";
            }
            else {
                weightUnitsString = "tonnes";
            }
            return weightUnitsString;
        }

        static inline float convertWeightToUnits(float value, CPMListWeightUnits toUnits) {
            float result;
            if (CPMListWeightUnits::TONS == toUnits) {
                result = value * 1.10231f;
            }
            else if (CPMListWeightUnits::KLBS == toUnits) {
                result = value * 2.20462f;
            }
            else if (CPMListWeightUnits::LBS == toUnits) {
                result = value * 2204.62f;
            }
            else if (CPMListWeightUnits::KGS == toUnits) {
                result = value * 1000.f;
            }
            else {
                result = value;
            }
            return result;
        }

        static inline float convertWeightFromUnits(float value, CPMListWeightUnits fromUnits) {
            float result;
            if (CPMListWeightUnits::TONS == fromUnits) {
                result = value / 1.10231f;
            }
            else if (CPMListWeightUnits::KLBS == fromUnits) {
                result = value / 2.20462f;
            }
            else if (CPMListWeightUnits::LBS == fromUnits) {
                result = value / 2204.62f;
            }
            else if (CPMListWeightUnits::KGS == fromUnits) {
                result = value / 1000.f;
            }
            else {
                result = value;
            }
            return result;
        }
    };
}

#endif
