#ifndef LPSSAMATERIALLISTMGR_HPP
#define LPSSAMATERIALLISTMGR_HPP

#include <interfaces/LpsSaListMgr/InterfaceCommon.h>
#include <interfaces/LpsSaListMgr/TxInterface.hpp>
#include <interfaces/LpsSaListMgr/LpsSaListMgr.hpp>

#include "CPMMaterialList.hpp"

class LpsSaMaterialListMgr final : public LpsSaListMgr {
public:
    LpsSaMaterialListMgr() :
        LpsSaListMgr(LpsSaListMgrInterfaceListType::MATERIAL) {}

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

    inline std::string getJsonFileName() const { return LpsSaListMgrTxInterface::materialListJsonFileName; };
    inline std::string getCsvFileName() const { return LpsSaListMgrTxInterface::materialListCsvFileName; };
    inline std::string getBdtFileName() const { return "MaterialList.bdt"; }

    bool loadFromJson(std::istream& json) {
        bool success = true;
        try {
            materialList_ = CPMMaterialList(json);
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool loadFromCsv(std::istream& csv) {
        bool success = true;
        try {
            materialList_ = CPMMaterialList(csv, true);
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool loadFromProtobuf(const cat::cpm::list::List& list) {
        bool success = true;
        try {
            materialList_ = CPMMaterialList(list);
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool serializeToJson(std::ostream& json) const {
        bool success = true;
        try {
            materialList_.toJson(json);
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool serializeToProtobuf(std::ostream& pb) const override {
        bool success = true;
        try {
            materialList_.toProtobuf(pb, listRevision_.getRevision());
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool serializeToCsv(std::ostream& csv, LpsCommonWeightUnits displayUnits) const override {
        bool success = true;
        try {
            materialList_.toCsv(csv, true, convertWeightUnits(displayUnits));
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
        List.set_type(listsync::List_TYPE_MATERIAL);

        // set the revision timestamp
        auto secs =  std::chrono::system_clock::to_time_t(listRevision_.getRevision());
        google::protobuf::Timestamp* revision = new google::protobuf::Timestamp();
        revision->set_seconds(secs);
        List.set_allocated_revision(revision);

        List.SerializeToOstream(&os);

        return;
    }

protected:
    CPMMaterialList materialList_;

    const std::string defaultJsonContent_ = R"({
  "MaterialList": [
    { "name": "Material1", "id": 1, "density": 1780.0 },
    { "name": "Material2", "id": 2, "density": 1780.0 },
    { "name": "Material3", "id": 3, "density": 1780.0 },
    { "name": "Material4", "id": 4, "density": 1780.0 },
    { "name": "Material5", "id": 5, "density": 1780.0 }
  ]
})";
};

#endif /* LPSSAMATERIALLISTMGR_HPP */
