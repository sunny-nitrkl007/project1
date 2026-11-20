#ifndef WORKORDERASSIST_SETTINGSSTORAGE_H
#define WORKORDERASSIST_SETTINGSSTORAGE_H

#include <mutex>

#include <boost/filesystem.hpp>
#include <boost/serialization/version.hpp>

#include <interfaces/WorkOrderAssist/Settings.hpp>

struct WorkOrderAssistSettingsStorage {
public:
    WorkOrderAssistSettingsStorage() :
        mtx_(),
        filePath_(),
        settings_() {}

    inline void setFilePath(const boost::filesystem::path& filePath) {
        std::lock_guard<std::mutex> lck(mtx_);
        filePath_ = filePath.string();
    }

    inline void getSettings(WorkOrderAssistSettings& settings) const {
        std::lock_guard<std::mutex> lck(mtx_);
        settings = settings_;
    }

    inline void setSettings(const WorkOrderAssistSettings& settings) {
        std::lock_guard<std::mutex> lck(mtx_);
        settings_ = settings;
    }

    inline bool isEnabled() const {
        std::lock_guard<std::mutex> lck(mtx_);
        bool enabled = settings_.installed && settings_.enabled;
        return enabled;
    }

    inline void setSite(int32_t siteId, const std::string& siteName) {
        std::lock_guard<std::mutex> lck(mtx_);
        settings_.siteId = siteId;
        settings_.siteName = siteName;
    }

    bool load();
    bool save() const;

private:
    mutable std::mutex mtx_;
    std::string filePath_;
    WorkOrderAssistSettings settings_;

    inline void reset() {
        settings_ = WorkOrderAssistSettings();
    }

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & settings_;
    }
};

BOOST_CLASS_VERSION(WorkOrderAssistSettingsStorage, 1);

#endif
