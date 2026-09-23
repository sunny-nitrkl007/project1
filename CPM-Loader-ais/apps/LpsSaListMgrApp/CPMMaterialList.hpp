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

#include <ext/rapidjson/RapidJsonGuarded.h>

#include <interfaces/LpsSaListMgr/CPMList.h>
#include <interfaces/LpsSaListMgr/CPMListSync/CPMList.pb.h>

#ifndef CPMMATERIALLIST_HPP
#define CPMMATERIALLIST_HPP

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

    CPMMaterialList(const cat::cpm::list::List& list) {
        // check to see if there are list items
        if (list.has_content()) {
            const cat::cpm::list::List_Content listContent = list.content();
            auto size = listContent.entries_size();
            for (int i=0; i<size; ++i) {
                materials_.push_back(
                        CPMMaterialListEntry{
                    listContent.entries(i).name(),
                            (uint32_t)listContent.entries(i).id().value(),
                            (float)listContent.entries(i).density().value()
                }
                );
            }
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

    void toProtobuf(std::ostream& os, const std::chrono::system_clock::time_point& revision_tp) const {
        namespace listsync = cat::cpm::list;
        listsync::List List;
        listsync::List_Content* List_Content = new listsync::List_Content;

        // set the list type
        List.set_type(listsync::List_TYPE_MATERIAL);

        // set max list length and name length
        List.set_max_list_length(CPMLIST_MAX_LIST_LENGTH);
        List.set_max_name_length(CPMLIST_MAX_NAME_LENGTH);

        // set the revision timestamp
        auto secs =  std::chrono::duration_cast<std::chrono::seconds>(revision_tp.time_since_epoch()).count();
        google::protobuf::Timestamp* revision = new google::protobuf::Timestamp();
        revision->set_seconds(secs);
        List.set_allocated_revision(revision);

        // set the content
        List.set_allocated_content(List_Content);

        // set the list items
        for (const auto& m : materials_) {
            listsync::List_Entry* List_Entry;
            List_Entry = List_Content->add_entries();
            List_Entry->set_name(m.name);
            google::protobuf::UInt32Value* id = new google::protobuf::UInt32Value;
            id->set_value(m.id);
            List_Entry->set_allocated_id(id);
            google::protobuf::FloatValue* density = new google::protobuf::FloatValue;
            density->set_value(m.density);
            List_Entry->set_allocated_density(density);
        }

        List.SerializeToOstream(&os);
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

#endif
