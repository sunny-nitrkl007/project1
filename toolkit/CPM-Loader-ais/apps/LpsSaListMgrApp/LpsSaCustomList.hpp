#pragma once

#ifndef LPSSACUSTOMLIST_H
#define LPSSACUSTOMLIST_H

#include <stdexcept>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <memory>
#include <chrono>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string.hpp>

//#define RAPIDJSON_NAMESPACE rapidjson110
//#define RAPIDJSON_HAS_STDSTRING 1
#include <ext/rapidjson/RapidJsonGuarded.h>

#include <chrono/print.hpp>
#include <interfaces/LpsSaListMgr/CPMListSync/CPMList.pb.h>

class LpsSaCustomList {
public:
    LpsSaCustomList() :
        listName_(),
        list_() {}

    LpsSaCustomList(std::string defaultListName) :
        listName_(defaultListName),
        list_() {}

    LpsSaCustomList(const std::string& defaultListName, std::istream& is, bool csv = false, int skipLines = 0) :
            listName_(defaultListName),
            list_() {
        if (csv) {
            std::string line;
            while (std::getline(is, line)) {
                if (skipLines > 0) {
                    skipLines--;
                    continue;
                }

                boost::algorithm::trim(line); // Trim whitespace

                if (line.empty()) {
                    continue;
                }

                std::stringstream lineStream(line);
                std::string name;
                if (std::getline(lineStream, name, ',')) {
                    list_.push_back(std::move(name));
                }
            }
        }
        else {
            // Boost Property Tree
            boost::property_tree::ptree tree;
            boost::property_tree::read_json(is, tree);
            boost::property_tree::ptree::value_type node = tree.front();

            listName_ = node.first;

            const boost::property_tree::ptree& list = node.second;
            for (const auto& it : list) {
                list_.push_back(it.second.get<std::string>("name"));
            }
        }
    }

    LpsSaCustomList(const std::string& defaultListName, const cat::cpm::list::List& list) :
            listName_(defaultListName),
            list_() {

            // check to see if there are list items
            if (list.has_content()) {
                const cat::cpm::list::List_Content listContent = list.content();
                listName_ = listContent.name();
                auto size = listContent.entries_size();
                for (int i=0; i<size; ++i) {
                    list_.push_back(listContent.entries(i).name());
                }
            }
    }

    void toJson(std::ostream& os) const {
        rapidjson::StringBuffer sb;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer{ sb };
        //rapidjson110::Writer<rapidjson110::StringBuffer> writer{ sb };
        writer.SetIndent(' ', 2);
        writer.SetMaxDecimalPlaces(2);
        writer.StartObject();
        writer.Key(listName_);
        writer.StartArray();
        for (const auto& itemName : list_) {
            writer.StartObject();
            writer.Key("name"); writer.String(itemName);
            writer.EndObject();
        }
        writer.EndArray();
        writer.EndObject();
        os << sb.GetString();
    }

    void toProtobuf(std::ostream& os, std::string defaultListName, const std::chrono::system_clock::time_point& revision_tp) const {
        namespace listsync = cat::cpm::list;
        listsync::List List;
        listsync::List_Content* List_Content = new listsync::List_Content;

        // set the list type
        if ("Custom 1" == defaultListName) {
            List.set_type(listsync::List_TYPE_CUSTOM1);
        }
        else if ("Custom 2" == defaultListName) {
            List.set_type(listsync::List_TYPE_CUSTOM2);
        }
        else if ("Custom 3" == defaultListName) {
            List.set_type(listsync::List_TYPE_CUSTOM3);
        }
        else if ("Custom 4" == defaultListName) {
            List.set_type(listsync::List_TYPE_CUSTOM4);
        }
        else {
            List.set_type(listsync::List_TYPE_INVALID);
        }

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

        // set the list name
        List_Content->set_name(listName_);

        // set the list items
        for (const auto& item : list_) {
            listsync::List_Entry* List_Entry;
            List_Entry = List_Content->add_entries();
            List_Entry->set_name(item);
        }

        List.SerializeToOstream(&os);
    }

    void toCsv(std::ostream& os, bool headerRow = false) const {
        if (headerRow) {
            os << "name" << std::endl;
        }
        for (const auto& item : list_) {
            // Make sure name doesn't contain any commas (even though they save lives)
            std::remove_copy(item.cbegin(), item.cend(), std::ostream_iterator<char>(os), ',');
            os << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const LpsSaCustomList& list) {
        list.toJson(out);
        return out;
    }

    friend bool operator==(const LpsSaCustomList& a, const LpsSaCustomList& b) {
        if (a.getName() != b.getName()) {
            return false;
        }

        return a.getList() == b.getList();
    }

    friend bool operator!=(const LpsSaCustomList& a, const LpsSaCustomList& b) {
        return !(a == b);
    }

    std::string getName() const {
        return listName_;
    }

    void setName(const std::string& name) {
        listName_ = name;
    }

    const std::vector<std::string>& getList() const {
        return list_;
    }

    void addItem(std::string&& itemName) {
        list_.push_back(std::move(itemName));
    }

    void clear() {
        list_.clear();
    }

private:
    std::string listName_;
    std::vector<std::string> list_;
};

#undef RAPIDJSON_HAS_STDSTRING
#undef RAPIDJSON_NAMESPACE

#endif

