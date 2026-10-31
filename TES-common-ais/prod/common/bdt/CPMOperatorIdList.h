#pragma once

#include <stdexcept>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <memory>

#include <ais/log/AisLogger.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string.hpp>

#include "CPMConfigDataParser.hpp"
#include "CPMConfigDataBuilder.hpp"

#include <ais/task/Task.h>

#ifndef BDT_CPMOPERATORIDLIST_H
#define BDT_CPMOPERATORIDLIST_H

namespace tes_common_ais {
struct CPMOperatorIdListEntry {
   static constexpr auto NullString = "           ";
   static constexpr size_t NameMaxLength = 11;
   static constexpr size_t NameMinLength = 1;
   static constexpr int32_t PasscodeSkip = -1;
   static constexpr int32_t PasscodeNull = -2;
   static constexpr int32_t PasscodeMin = 0;
   static constexpr int32_t PasscodeMax = 9999;
   static constexpr size_t PasscodeMinChars = 4;

   std::string name;
   int32_t passcode;

   friend bool operator==(const CPMOperatorIdListEntry& a, const CPMOperatorIdListEntry& b) {
      if ((a.name == b.name) && (a.passcode == b.passcode)) {
         return true;
      }
      return false;
   }

   friend bool operator!=(const CPMOperatorIdListEntry& a, const CPMOperatorIdListEntry& b) {
      return !(a == b);
   }

   CPMOperatorIdListEntry(std::string name, int32_t passcode) : name(name), passcode(passcode) {}
   CPMOperatorIdListEntry() : name(NullString), passcode(PasscodeNull) {}
};

enum class OperatorIdFileStatus {
   Unknown,
   Success,
   FileNotFound,
   HeadingsInvalid,
   EntryInvalid,
   PasscodeInvalid,
   PasscodeOutOfRange,
   PasscodeDuplicated,
   PasscodeTooShort,
   NameTooShort
};

inline std::string toString(OperatorIdFileStatus e)
{
   const std::map<OperatorIdFileStatus,const char*> EnumStrings {
      { OperatorIdFileStatus::Unknown, "Error: File status unknown or corrupted" },
      { OperatorIdFileStatus::Success, "Good" },
      { OperatorIdFileStatus::FileNotFound, "Error: File not found" },
      { OperatorIdFileStatus::HeadingsInvalid, "Error: Invalid column headings and/or attributes" },
      { OperatorIdFileStatus::EntryInvalid, "Error: Too many or too few items" },
      { OperatorIdFileStatus::PasscodeInvalid, "Error: Passcode is not a positive integer" },
      { OperatorIdFileStatus::PasscodeOutOfRange, "Error: Passcode out of range" },
      { OperatorIdFileStatus::PasscodeDuplicated, "Error: Passcode duplicated" },
      { OperatorIdFileStatus::PasscodeTooShort, "Error: Passcode too short" },
      { OperatorIdFileStatus::NameTooShort, "Error: Name too short" }
   };
   auto   it  = EnumStrings.find(e);
   return it == EnumStrings.end() ? "Out of range" : it->second;
}

class CPMOperatorIdList {
public:
   CPMOperatorIdList() = default;

   CPMOperatorIdList(std::istream& is, bool csv);

   void toJson(std::ostream& os) const;

   void toCsv(std::ostream& os, bool headerRows = true) const;

   friend std::ostream& operator<<(std::ostream& out, const CPMOperatorIdList& list) {
      list.toJson(out);
      return out;
   }

   friend bool operator==(const CPMOperatorIdList& a, const CPMOperatorIdList& b) {
      const std::vector<CPMOperatorIdListEntry>& v1 = a.getOperatorIds();
      const std::vector<CPMOperatorIdListEntry>& v2 = b.getOperatorIds();
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

   friend bool operator!=(const CPMOperatorIdList& a, const CPMOperatorIdList& b) {
      return !(a == b);
   }

   // Find the Operator ID associated with the provided passcode.  Returns true if successful.
   bool getOperatorId(CPMOperatorIdListEntry &operatorId, int32_t passcode);

   void addOperatorId(CPMOperatorIdListEntry&& operatorId);

   inline OperatorIdFileStatus getFileStatus() { return fileStatus; }
   inline size_t getNumRecords() { return operatorIds_.size(); }

private:
   std::vector<CPMOperatorIdListEntry> operatorIds_;

   const std::vector<CPMOperatorIdListEntry>& getOperatorIds() const;

   OperatorIdFileStatus fileStatus;

};
}
#endif //BDT_CPMOPERATORIDLIST_H

