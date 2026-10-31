#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <boost/tokenizer.hpp>
#include <vector>
#include <unordered_set>
#include <algorithm>

#include "CPMOperatorIdList.h"

namespace tes_common_ais {

CPMOperatorIdList::CPMOperatorIdList(std::istream& is, bool csv) 
 : fileStatus(OperatorIdFileStatus::Unknown)
{
   if (csv) {
      std::string line;
      uint32_t lineNumber = 0;
      std::unordered_set<int32_t> passcodes;
      while ((fileStatus == OperatorIdFileStatus::Unknown) && std::getline(is, line)) {
         lineNumber++;
         if (lineNumber == 1) {
            std::size_t found = line.find("Operator Name,Operator Passcode");
            if (found == std::string::npos) {
               fileStatus = OperatorIdFileStatus::HeadingsInvalid;
            }
         }
         else if (lineNumber == 2) {
            std::size_t found = line.find("text,integer");
            if (found == std::string::npos) {
               fileStatus = OperatorIdFileStatus::HeadingsInvalid;
            }
         }
         else { // lineNumber > 2
            boost::algorithm::trim(line); // Trim whitespace

            if (line.empty()) {
               continue;
            }

            // Split the line, allowing for commas within text fields
            boost::tokenizer<boost::escaped_list_separator<char>> tok(line);
            std::vector<std::string> splitLine(tok.begin(), tok.end());

            // Check if there are two entries
            if (splitLine.size() != 2) {
               fileStatus = OperatorIdFileStatus::EntryInvalid;
               break;
            }

            // Parse the name
            std::string name(splitLine[0]);

            // Remove any quotation marks and truncate
            name.erase(std::remove(name.begin(), name.end(), '"'), name.end());
            if(name.length() > CPMOperatorIdListEntry::NameMaxLength) {
               name.resize(CPMOperatorIdListEntry::NameMaxLength);
            }
            else if (name.length() < CPMOperatorIdListEntry::NameMinLength) {
               fileStatus = OperatorIdFileStatus::NameTooShort;
               break;
            }

            // Parse the passcode
            std::string passcodeString(splitLine[1]);

            // Check passcode number of characters
            if (passcodeString.size() < CPMOperatorIdListEntry::PasscodeMinChars) {
               fileStatus = OperatorIdFileStatus::PasscodeTooShort;
               break;
            }

            // Check that passcode is a positive integer
            if (std::find_if(passcodeString.begin(), passcodeString.end(), [](char c) { return !std::isdigit(c); }) != passcodeString.end()) {
               fileStatus = OperatorIdFileStatus::PasscodeInvalid;
               break;
            }

            int32_t passcode = std::strtol(passcodeString.c_str(), nullptr, 10);

            // Check passcode range
            if((passcode > CPMOperatorIdListEntry::PasscodeMax) || (passcode < CPMOperatorIdListEntry::PasscodeMin)) {
               fileStatus = OperatorIdFileStatus::PasscodeOutOfRange;
               break;
            }

            // Check that passcode doesn't already exist in container
            auto search = passcodes.find(passcode);
            if (search != passcodes.end()) {
               fileStatus = OperatorIdFileStatus::PasscodeDuplicated;
               break;
            }

            passcodes.insert(passcode);

            // If no errors, add to container
            operatorIds_.push_back(CPMOperatorIdListEntry{ name, passcode });
         }
      }
      if(fileStatus != OperatorIdFileStatus::Unknown) {
         // Clear the vector memory and log error
         operatorIds_.clear();
         std::string fileStatusError(toString(fileStatus) + ": " + line);
         AIS_LOG_ERROR("%s", fileStatusError.c_str());
         return;
      }
   }
   else {
      { // Boost Property Tree
         boost::property_tree::ptree tree;
         boost::property_tree::read_json(is, tree);
         boost::property_tree::ptree operatorIdList = tree.get_child("OperatorIdList");
         for (const auto& it : operatorIdList) {
            operatorIds_.push_back(CPMOperatorIdListEntry{
               it.second.get<std::string>("name"),
                     it.second.get<int32_t>("passcode"),
            }
            );
         }
      }
   }
   fileStatus = OperatorIdFileStatus::Success;
}

void CPMOperatorIdList::toJson(std::ostream& os) const {
   rapidjson::StringBuffer sb;
   rapidjson::PrettyWriter<rapidjson::StringBuffer> writer{ sb };
   //rapidjson::Writer<rapidjson::StringBuffer> writer{ sb };
   writer.SetIndent(' ', 2);
   writer.SetMaxDecimalPlaces(2);
   writer.StartObject();
   writer.Key("OperatorIdList");
   writer.StartArray();
   for (const auto& t : operatorIds_) {
      writer.StartObject();
      writer.Key("name"); writer.String(t.name);
      writer.Key("passcode"); writer.Uint(t.passcode);
      writer.EndObject();
   }
   writer.EndArray();
   writer.EndObject();
   os << sb.GetString();
}

void CPMOperatorIdList::toCsv(std::ostream& os, bool headerRows) const {
   if (headerRows) {
      os << "Operator Name,Operator Passcode" << std::endl;
      os << "text,integer" << std::endl;
   }
   for (const auto& t : operatorIds_) {
      // Surround with quotation marks to support commas
      os << "\"" << t.name << "\"," << t.passcode << std::endl;
   }
}

// Find the Operator ID associated with the provided passcode.  Returns true if successful.
bool CPMOperatorIdList::getOperatorId(CPMOperatorIdListEntry &operatorId, int32_t passcode) {
   bool ret = false;
   for (auto entry : operatorIds_) {
      if (entry.passcode == passcode) {
         operatorId = entry;
         ret = true;
         break;
      }
   }
   return ret;
}

void CPMOperatorIdList::addOperatorId(CPMOperatorIdListEntry&& operatorId) {
   operatorIds_.push_back(std::move(operatorId));
}

const std::vector<CPMOperatorIdListEntry>& CPMOperatorIdList::getOperatorIds() const {
   return operatorIds_;
}
}

