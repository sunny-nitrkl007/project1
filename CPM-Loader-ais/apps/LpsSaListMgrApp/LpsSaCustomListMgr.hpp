#ifndef LPSSACUSTOMLISTMGR_HPP
#define LPSSACUSTOMLISTMGR_HPP

#include <interfaces/LpsSaListMgr/InterfaceCommon.h>
#include <interfaces/LpsSaListMgr/TxInterface.hpp>
#include <interfaces/LpsSaListMgr/LpsSaListMgr.hpp>

#include "LpsSaCustomList.hpp"

class LpsSaCustomListMgr final : public LpsSaListMgr {
public:
    LpsSaCustomListMgr(LpsSaListMgrInterfaceListType listType) :
        LpsSaListMgr(listType),
        customList_(getDefaultListName(listType)) {}

    bool initialize(const boost::filesystem::path& storageRoot) {
        setStoragePath(storageRoot);
        
        // initialize and load list revision
        std::string revisionFilename = LpsSaListMgrInterfaceListType_string(listType_);
        revisionFilename += "_revision";
        listRevision_.setStoragePath(storageRoot, revisionFilename);
        listRevision_.load();

        if (!loadFromStorage()) {
            customList_.clear();
            return false;
        }
        return true;
    }

    inline std::string getJsonFileName() const {
        return LpsSaListMgrTxInterface::getCustomListJsonFileName(listType_);
    };

    inline std::string getCsvFileName() const {
        return LpsSaListMgrTxInterface::getCustomListCsvFileName(listType_);
    };

    std::string getListName() const {
        return customList_.getName();
    }

    void setListName(const std::string& name) {
        customList_.setName(name);
    }

    bool loadFromJson(std::istream& json) {
        bool success = true;
        try {
            customList_ = LpsSaCustomList(customList_.getName(), json);
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool loadFromCsv(std::istream& csv) {
        bool success = true;
        try {
            customList_ = LpsSaCustomList(customList_.getName(), csv, true, 1);
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool loadFromProtobuf(const cat::cpm::list::List& list) {
        bool success = true;
        try {
            customList_ = LpsSaCustomList(getDefaultListName(listType_), list);
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool serializeToJson(std::ostream& json) const {
        bool success = true;
        try {
            customList_.toJson(json);
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool serializeToProtobuf(std::ostream& pb) const override {
        bool success = true;
        try {
            customList_.toProtobuf(pb, getDefaultListName(listType_), listRevision_.getRevision());
        }
        catch (...) {
            success = false;
        }
        return success;
    }

    bool serializeToCsv(std::ostream& csv, LpsCommonWeightUnits displayUnits) const override {
        bool success = true;
        try {
            customList_.toCsv(csv, true);
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
        std::string defaultListName = getDefaultListName(listType_);
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

        // set the revision timestamp
        auto secs =  std::chrono::system_clock::to_time_t(listRevision_.getRevision());
        google::protobuf::Timestamp* revision = new google::protobuf::Timestamp();
        revision->set_seconds(secs);
        List.set_allocated_revision(revision);

        List.SerializeToOstream(&os);

        return;
    }        

protected:
    LpsSaCustomList customList_;
};

#endif
