#ifndef LPSSATRUCKLISTMGR_HPP
#define LPSSATRUCKLISTMGR_HPP

#include <interfaces/LpsSaListMgr/InterfaceCommon.h>
#include <interfaces/LpsSaListMgr/TxInterface.hpp>
#include <interfaces/LpsSaListMgr/LpsSaListMgr.hpp>

#include "CPMTruckList.hpp"

class LpsSaTruckListMgr final : public LpsSaListMgr {
public:
    LpsSaTruckListMgr() :
        LpsSaListMgr(LpsSaListMgrInterfaceListType::TRUCK) {}

    bool initialize(const boost::filesystem::path& storageRoot) {
        setStoragePath(storageRoot);

        // initialize and load list revision
        std::string revisionFilename = LpsSaListMgrInterfaceListType_string(listType_);
        revisionFilename += "_revision";
        listRevision_.setStoragePath(storageRoot, revisionFilename);
        listRevision_.load();

        if (!loadFromStorage()) {
            // Load default
            std::istringstream iss(defaultJsonContent_);
            loadFromJson(iss);
            return false;
        }
        return true;
    }

    inline std::string getJsonFileName() const { return LpsSaListMgrTxInterface::truckListJsonFileName; };
    inline std::string getCsvFileName() const { return LpsSaListMgrTxInterface::truckListCsvFileName; };
    inline std::string getBdtFileName() const { return "TruckList.bdt"; }

    bool loadFromJson(std::istream& json) {
        bool success = true;
        try {
            truckList_ = CPMTruckList(json);
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool loadFromCsv(std::istream& csv) {
        bool success = true;
        try {
            truckList_ = CPMTruckList(csv, true);
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool loadFromProtobuf(const cat::cpm::list::List& list) {
        bool success = true;
        try {
            truckList_ = CPMTruckList(list);
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool serializeToJson(std::ostream& json) const {
        bool success = true;
        try {
            truckList_.toJson(json);
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool serializeToProtobuf(std::ostream& pb) const override {
        bool success = true;
        try {
            truckList_.toProtobuf(pb, listRevision_.getRevision());
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool serializeToCsv(std::ostream& csv, LpsCommonWeightUnits displayUnits) const override {
        bool success = true;
        try {
            truckList_.toCsv(csv, true, convertWeightUnits(displayUnits));
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    void createListRevision (std::ostream& os ) const override {
        namespace listsync = cat::cpm::list;
        listsync::List List;

        // set the list type
        List.set_type(listsync::List_TYPE_TRUCK);

        // set the revision timestamp
        auto secs =  std::chrono::system_clock::to_time_t(listRevision_.getRevision());
        google::protobuf::Timestamp* revision = new google::protobuf::Timestamp();
        revision->set_seconds(secs);
        List.set_allocated_revision(revision);

        List.SerializeToOstream(&os);

        return;
    }

public:
    CPMTruckList truckList_;

protected:
    const std::string defaultJsonContent_ = R"({
  "TruckList": [
    { "name": "Truck1", "id": 1, "targetWeight": 11.0 },
    { "name": "Truck2", "id": 2, "targetWeight": 12.0 },
    { "name": "Truck3", "id": 3, "targetWeight": 13.0 },
    { "name": "Truck4", "id": 4, "targetWeight": 14.0 },
    { "name": "Truck5", "id": 5, "targetWeight": 15.0 }
  ]
})";
};

#endif /* LPSSATRUCKLISTMGR_HPP */
