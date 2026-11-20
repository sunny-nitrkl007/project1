#ifndef OPERATORIDLISTMGR_HPP_
#define OPERATORIDLISTMGR_HPP_

#include <bdt/CPMOperatorIdList.h>

#include <interfaces/LpsSaListMgr/InterfaceCommon.h>
#include <interfaces/LpsSaListMgr/TxInterface.hpp>
#include <interfaces/LpsSaListMgr/LpsSaListMgr.hpp>

enum class OperatorIdState {
   Unknown,
   Disabled,
   Invalid,
   Valid
};

inline std::string toString (OperatorIdState e)
{
   const std::map<OperatorIdState,const char*> EnumStrings {
      { OperatorIdState::Unknown,  "Unknown" },
      { OperatorIdState::Disabled, "Disabled" },
      { OperatorIdState::Invalid,  "Invalid" },
      { OperatorIdState::Valid,    "Valid" }
   };
   auto   it  = EnumStrings.find(e);
   return it == EnumStrings.end() ? "Out of range" : it->second;
}

struct OperatorIdStatus {
   int32_t currentPasscode = tes_common_ais::CPMOperatorIdListEntry::PasscodeNull;
   size_t numRecords = 0;
   std::string operatorName = tes_common_ais::CPMOperatorIdListEntry::NullString;
   OperatorIdState state = OperatorIdState::Unknown;
   tes_common_ais::OperatorIdFileStatus fileStatus = tes_common_ais::OperatorIdFileStatus::Unknown;

   inline std::string getStateString() { return toString(state); }
   inline std::string getFileStatusString() { return toString(fileStatus); }
};

class OperatorIdListMgr : public LpsSaListMgr {
public:
   OperatorIdListMgr():
      LpsSaListMgr(LpsSaListMgrInterfaceListType::OPERATOR_ID),
      operatorIdList_(),
      operatorIdStatus_(),
      enabled(false) {}

   virtual inline std::string getCsvFileName() const { return LpsSaListMgrTxInterface::operatorIdListCsvFileName; };
   virtual inline std::string getJsonFileName() const { return LpsSaListMgrTxInterface::operatorIdListJsonFileName; };

   bool loadFromJson(std::istream& json) {
      bool success = false;
      try {
         operatorIdList_ = tes_common_ais::CPMOperatorIdList(json, false);
         operatorIdStatus_.fileStatus = operatorIdList_.getFileStatus();
         success = true;
      }
      catch (...) {
         AIS_LOG_FATAL("LoadFromJson failed");
      }
      return success;
   }

   virtual bool loadFromCsv(std::istream& csv) {
      bool success = false;
      try {
         tes_common_ais::CPMOperatorIdList tempOperatorIdList_ = tes_common_ais::CPMOperatorIdList(csv, true);
         operatorIdStatus_.fileStatus = tempOperatorIdList_.getFileStatus(); // TODO: write fileStatus to LastOperatorIdListUploadStatus.json 
         if (operatorIdStatus_.fileStatus == tes_common_ais::OperatorIdFileStatus::Success) {
            operatorIdList_= std::move(tempOperatorIdList_);
            success = true;
         }
      }
      catch (...) {
      }
      return success;
   }

   virtual bool serializeToJson(std::ostream& json) const {
      bool success = false;
      try {
         operatorIdList_.toJson(json);
         success = true;
      }
      catch (...) {
      }
      return success;
   }

   virtual bool serializeToCsv(std::ostream& csv, LpsCommonWeightUnits displayUnits) const override {
      bool success = false;
      try {
         operatorIdList_.toCsv(csv, true);
         success = true;
      }
      catch (...) {
      }
      return success;
   }

   OperatorIdStatus getOperatorIdStatus() {
      tes_common_ais::CPMOperatorIdListEntry operatorId;
      operatorIdStatus_.numRecords = 0;
      if (!enabled) {
         operatorIdStatus_.state = OperatorIdState::Disabled;
      }
      else if (storagePath_.size() == 0) {
         operatorIdStatus_.state = OperatorIdState::Unknown;
      }
      else {
         // Reload from Storage
         if (loadNoLock(LpsSaListMgrInterfaceListFormat::JSON, storagePath_)) {
            operatorIdStatus_.numRecords = operatorIdList_.getNumRecords();
            // An empty list is considered Valid
            if (operatorIdStatus_.numRecords == 0) {
               operatorIdStatus_.state = OperatorIdState::Valid;
            }
            // No passcode has been entered
            else if (operatorIdStatus_.currentPasscode == tes_common_ais::CPMOperatorIdListEntry::PasscodeNull) {
               operatorIdStatus_.state = OperatorIdState::Invalid;
            }
            // Operator has requested to skip passcode entry
            else if (operatorIdStatus_.currentPasscode == tes_common_ais::CPMOperatorIdListEntry::PasscodeSkip) {
               operatorIdStatus_.state = OperatorIdState::Valid;
            }
            // Current passcode is found in the Operator ID list
            else if (operatorIdList_.getOperatorId(operatorId, operatorIdStatus_.currentPasscode)) {
               operatorIdStatus_.state = OperatorIdState::Valid;
            }
            // Current passcode is not found in the Operator ID list
            else {
               operatorIdStatus_.state = OperatorIdState::Invalid;
            }
         }
         else {
            // Load from JSON will only fail if there is no file
            operatorIdStatus_.fileStatus = tes_common_ais::OperatorIdFileStatus::FileNotFound;
            operatorIdStatus_.state = OperatorIdState::Valid;
         }
      }
      // Set name to either default value or name found in Operator ID List
      operatorIdStatus_.operatorName = operatorId.name;

      return operatorIdStatus_;
   };

   void setOperatorId(int32_t passcode) {
      operatorIdStatus_.currentPasscode = passcode;
   }

   void setEnabled(bool operatorIdEnabled) {
      enabled = operatorIdEnabled;
   }

protected:
   std::string readPath_;
private:
   tes_common_ais::CPMOperatorIdList operatorIdList_;
   OperatorIdStatus operatorIdStatus_;
   bool enabled;
};
#endif /*OPERATORIDLISTMGR_HPP*/
