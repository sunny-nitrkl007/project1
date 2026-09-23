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

#ifndef CPMTRUCKLIST_HPP
#define CPMTRUCKLIST_HPP

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

    CPMTruckList(const cat::cpm::list::List& list) {
        // check to see if there are list items
        if (list.has_content()) {
            const cat::cpm::list::List_Content listContent = list.content();
            auto size = listContent.entries_size();
            for (int i=0; i<size; ++i) {
                trucks_.push_back(
                        CPMTruckListEntry{
                    listContent.entries(i).name(),
                            (uint32_t)listContent.entries(i).id().value(),
                            (float)listContent.entries(i).target_weight().value()
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

    void toProtobuf(std::ostream& os, const std::chrono::system_clock::time_point& revision_tp) const {
        namespace listsync = cat::cpm::list;
        listsync::List List;
        listsync::List_Content* List_Content = new listsync::List_Content;

        // set the list type
        List.set_type(listsync::List_TYPE_TRUCK);

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
        for (const auto& t : trucks_) {
            listsync::List_Entry* List_Entry;
            List_Entry = List_Content->add_entries();
            List_Entry->set_name(t.name);
            google::protobuf::UInt32Value* id = new google::protobuf::UInt32Value;
            id->set_value(t.id);
            List_Entry->set_allocated_id(id);
            google::protobuf::FloatValue* targetWt = new google::protobuf::FloatValue;
            targetWt->set_value(t.targetWeight);
            List_Entry->set_allocated_target_weight(targetWt);
        }

        List.SerializeToOstream(&os);
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

#endif
