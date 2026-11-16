#include <chrono>
#include <array>
#include <utility>
#include <string>
#include <boost/filesystem/path.hpp>

#include <boost/serialization/array.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>

#include <boost/archive/archive_exception.hpp>

#include "JobMgrLoadRecord.h"

class LpsSaJobMgrTasks {
public:
    LpsSaJobMgrTasks(const std::string& filePath, float defaultTargetWeight = 0.f) :
        numberOfTasks_(defaultNumberOfTasks_),
        filePath_(filePath),
        defaultTargetWeight_(defaultTargetWeight),
        loadIndex_(0),
        nullLoad_(),
        loads_(),
        loadsSplit_(),
        loadsBatch_(),
        loadsMix_(),
        loadsBlendLoads_(),
        loadsBlendWeight_(),
        targetTypes_() {

        // Since loads_ was just default constructed, there should only be one subtotal per load record.
        for (jobmgr_data::LpsSaLoadRecordChannelStorage& l : loads_) {
            l.getCurrentSubtotal().truckTargetWeightTonnes = defaultTargetWeight;
        }

        // initialize targetTypes for all task by default to SINGLE
        targetTypes_.fill(jobmgr_data::LpsSaLoadRecordTargetType::SINGLE);

        // initialize the target type for the loads
        initTargetTypes();
    }

    LpsSaJobMgrTasks(const boost::filesystem::path& filePath, float defaultTargetWeight = 0.f) :
        LpsSaJobMgrTasks(filePath.string(), defaultTargetWeight) {}

    LpsSaJobMgrTasks() : LpsSaJobMgrTasks(std::string("")) {}

    LpsSaJobMgrTasks(const LpsSaJobMgrTasks&) = default;

    uint8_t getCurrentTaskNumber() const {
        return loadIndex_ + 1;
    }

    void setTaskNumberNext() {
        uint8_t loadIndex = loadIndex_;
        if (loadIndex < (numberOfTasks_ - 1)) {
            loadIndex_ = loadIndex + 1;
        }
        else {
            loadIndex_ = 0;
        }
    }

    void setTaskNumberPrevious() {
        uint8_t loadIndex = loadIndex_;
        if (loadIndex > 0) {
            loadIndex_ = loadIndex - 1;
        }
        else {
            loadIndex_ = numberOfTasks_ - 1;
        }
    }

    bool setTaskNumber(uint8_t taskNumber) {
        bool success;
        if ((taskNumber > 0) && (taskNumber <= numberOfTasks_)) {
            loadIndex_ = taskNumber - 1;
            success = true;
        }
        else {
            success = false;
        }
        return success;
    }

    void setTargetType(uint8_t targetType) {
        targetTypes_.at(loadIndex_) = targetType;
    }

    /*
     * Gets a reference to the load information for the current task.
     * Protects against index out of bounds.
     */
    jobmgr_data::LpsSaLoadRecordChannelStorage& getCurrentTaskLoad() {
        if (loadIndex_ < loads_.size()) {
            switch (targetTypes_[loadIndex_]) {
            case jobmgr_data::LpsSaLoadRecordTargetType::SINGLE:
                return loads_[loadIndex_];
                break;
            case jobmgr_data::LpsSaLoadRecordTargetType::SPLIT:
                return loadsSplit_[loadIndex_];
                break;
            case jobmgr_data::LpsSaLoadRecordTargetType::BATCH:
                return loadsBatch_[loadIndex_];
                break;
            case jobmgr_data::LpsSaLoadRecordTargetType::MIX:
                return loadsMix_[loadIndex_];
                break;
            case jobmgr_data::LpsSaLoadRecordTargetType::BLEND_LOADS:
                return loadsBlendLoads_[loadIndex_];
                break;
            case jobmgr_data::LpsSaLoadRecordTargetType::BLEND_WEIGHT:
                return loadsBlendWeight_[loadIndex_];
                break;
            default:
                break;
            }
        }

        return nullLoad_;
    }

    const jobmgr_data::LpsSaLoadRecordChannelStorage& getCurrentTaskLoad() const {
        return getCurrentTaskLoad();
    }

    void currentTaskLoadInit(const jobmgr_data::LpsSaLoadRecordChannelStorage& initLoad) {
        jobmgr_data::LpsSaLoadRecordChannelStorage& load = getCurrentTaskLoad();
        load = initLoad;
    }

    void currentTaskLoadAddPass(float weight, uint8_t accuracy, uint32_t shmTime) {
        jobmgr_data::LpsSaLoadRecordSubtotal& subtotal = getCurrentTaskLoad().getCurrentSubtotal();
        subtotal.addPass(weight, accuracy, shmTime);
    }

    void currentTaskLoadClearCurrentSubtotal() {
        jobmgr_data::LpsSaLoadRecordChannelStorage& load = getCurrentTaskLoad();
        jobmgr_data::LpsSaLoadRecordSubtotal& subtotal = load.getCurrentSubtotal();

        subtotal.clearSubtotal();

        if (load.passCount() == 0) {
            load.clear();
        }
    }

    bool currentTaskLoadRemoveLastPass(uint32_t shmTime) {
        jobmgr_data::LpsSaLoadRecordChannelStorage& load = getCurrentTaskLoad();
        jobmgr_data::LpsSaLoadRecordSubtotal& subtotal = load.getCurrentSubtotal();

        bool removedPass = subtotal.removeLastPass();

        if (!removedPass) {
            // if no passes to remove, then go to previous subtotal
            load.selectSubtotal(shmTime, load.getCurrentSubtotalIndex()-1);
        }

        if (load.passCount() == 0) {
            load.clear();
        }

        return removedPass;
    }

    bool currentTaskSetTargetWeight(float targetWeight) {
        jobmgr_data::LpsSaLoadRecordSubtotal& subtotal = getCurrentTaskLoad().getCurrentSubtotal();
        if (subtotal.truckTargetWeightTonnes != targetWeight) {
            subtotal.truckTargetWeightTonnes = targetWeight;
            return true;
        }
        return false;
    }

    void currentTaskSetLFTDisable(bool disable) {
        jobmgr_data::LpsSaLoadRecordChannelStorage& load = getCurrentTaskLoad();
        if (disable) {
            load.storeAction(jobmgr_data::LpsSaLoadRecordStoreAction::TICKET_NOT_FOR_TRADE);
        }
        else {
            load.storeAction(jobmgr_data::LpsSaLoadRecordStoreAction::AUTO);
        }
    }

    // resets the LFT disable state to enabled by default (AUTO is enabled)
    void allTasksResetLFTDisableState() {
        for (jobmgr_data::LpsSaLoadRecordChannelStorage& l : loads_) {
            l.storeAction(jobmgr_data::LpsSaLoadRecordStoreAction::AUTO);
        }
    }

    bool currentTaskGetLFTDisable() {
        jobmgr_data::LpsSaLoadRecordChannelStorage& load = getCurrentTaskLoad();
        if (load.storeAction() == jobmgr_data::LpsSaLoadRecordStoreAction::TICKET_NOT_FOR_TRADE) {
            return true;
        }

        return false;
    }

    jobmgr_data::LpsSaLoadRecordChannelStorage currentTaskLoadClose(uint32_t shmTime) {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

        jobmgr_data::LpsSaLoadRecordChannelStorage& load = getCurrentTaskLoad();

        // Grab a copy of the load to return
        jobmgr_data::LpsSaLoadRecordChannelStorage returnLoad = load;

        // Clear out our load/subtotals
        load.clear();
        load.selectSubtotal(shmTime, 1);

        // Update the closing information in the load to return
        returnLoad.getCurrentSubtotal().endTime.utcTime = now;
        returnLoad.getCurrentSubtotal().endTime.shmTime = shmTime;

        // Set to the load store time
        returnLoad.storeTime.utcTime = now;
        returnLoad.storeTime.shmTime = shmTime;

        return returnLoad;
    }

    inline void setFilePath(const boost::filesystem::path& filePath) {
        setFilePath(filePath.string());
    }

    inline void setFilePath(const std::string& filePath) {
        filePath_ = filePath;
    }

    inline void setDefaultTargetWeight(float defaultTargetWeight) {
        defaultTargetWeight_ = defaultTargetWeight;
    }

    inline void setNumberOfTasks(uint8_t numberOfTasks) {
        if (numberOfTasks < 1) {
            numberOfTasks = 1;
        }
        else if (numberOfTasks > maxNumberOfTasks_) {
            numberOfTasks = maxNumberOfTasks_;
        }

        numberOfTasks_ = numberOfTasks;

        // If the load index is out of bounds, fix it.
        if (loadIndex_ >= numberOfTasks) {
            loadIndex_ = 0;
        }
    }

    inline uint8_t getNumberOfTasks() const {
        return numberOfTasks_;
    }

    bool load();
    bool save();

private:
    static constexpr uint8_t maxNumberOfTasks_ = 9;
    static constexpr uint8_t defaultNumberOfTasks_ = 2;
    uint8_t numberOfTasks_;
    std::string filePath_;
    float defaultTargetWeight_;
    uint8_t loadIndex_;
    jobmgr_data::LpsSaLoadRecordChannelStorage nullLoad_;
    std::array<jobmgr_data::LpsSaLoadRecordChannelStorage, maxNumberOfTasks_> loads_;
    std::array<jobmgr_data::LpsSaLoadRecordChannelStorage, maxNumberOfTasks_> loadsSplit_;
    std::array<jobmgr_data::LpsSaLoadRecordChannelStorage, maxNumberOfTasks_> loadsBatch_;
    std::array<jobmgr_data::LpsSaLoadRecordChannelStorage, maxNumberOfTasks_> loadsMix_;
    std::array<jobmgr_data::LpsSaLoadRecordChannelStorage, maxNumberOfTasks_> loadsBlendLoads_;
    std::array<jobmgr_data::LpsSaLoadRecordChannelStorage, maxNumberOfTasks_> loadsBlendWeight_;

    std::array<uint8_t, maxNumberOfTasks_> targetTypes_;

    void initTargetTypes() {
        // initialize the targetType for the loads
        for (jobmgr_data::LpsSaLoadRecordChannelStorage& l : loads_) {
            l.setTargetType(jobmgr_data::LpsSaLoadRecordTargetType::SINGLE);
        }

        for (jobmgr_data::LpsSaLoadRecordChannelStorage& l : loadsSplit_) {
            l.setTargetType(jobmgr_data::LpsSaLoadRecordTargetType::SPLIT);
        }

        for (jobmgr_data::LpsSaLoadRecordChannelStorage& l : loadsBatch_) {
            l.setTargetType(jobmgr_data::LpsSaLoadRecordTargetType::BATCH);
        }

        for (jobmgr_data::LpsSaLoadRecordChannelStorage& l : loadsMix_) {
            l.setTargetType(jobmgr_data::LpsSaLoadRecordTargetType::MIX);
        }

        for (jobmgr_data::LpsSaLoadRecordChannelStorage& l : loadsBlendLoads_) {
            l.setTargetType(jobmgr_data::LpsSaLoadRecordTargetType::BLEND_LOADS);
        }

        for (jobmgr_data::LpsSaLoadRecordChannelStorage& l : loadsBlendWeight_) {
            l.setTargetType(jobmgr_data::LpsSaLoadRecordTargetType::BLEND_WEIGHT);
        }
    }

    void validate() {
        setNumberOfTasks(numberOfTasks_);
    }

    friend class boost::serialization::access;

    template<class Archive>
    void save(Archive & ar, const unsigned int version) const {
        uint8_t storedSize = loads_.size();
        ar << storedSize;
        ar << loadIndex_;
        ar << boost::serialization::make_array(loads_.data(), storedSize);
        ar << numberOfTasks_;

        ar << boost::serialization::make_array(loadsSplit_.data(), storedSize);
        ar << boost::serialization::make_array(loadsBatch_.data(), storedSize);
        ar << boost::serialization::make_array(loadsMix_.data(), storedSize);
        ar << boost::serialization::make_array(loadsBlendLoads_.data(), storedSize);
        ar << boost::serialization::make_array(loadsBlendWeight_.data(), storedSize);

        ar << boost::serialization::make_array(targetTypes_.data(), storedSize);
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int version) {
        uint8_t storedSize;
        ar >> storedSize;
        ar >> loadIndex_;

        if (storedSize <= loads_.size()) {
            ar >> boost::serialization::make_array(loads_.data(), storedSize);
        }
        else {
            throw boost::archive::archive_exception(boost::archive::archive_exception::exception_code::array_size_too_short);
        }

        if (version >= 1) {
            ar >> numberOfTasks_;
        }

        if (version >= 2) {
            if (storedSize <= loadsSplit_.size() && storedSize <= loadsBatch_.size() && storedSize <= loadsMix_.size() &&
                    storedSize <= loadsBlendLoads_.size() && storedSize <= loadsBlendWeight_.size()) {
                ar >> boost::serialization::make_array(loadsSplit_.data(), storedSize);
                ar >> boost::serialization::make_array(loadsBatch_.data(), storedSize);
                ar >> boost::serialization::make_array(loadsMix_.data(), storedSize);
                ar >> boost::serialization::make_array(loadsBlendLoads_.data(), storedSize);
                ar >> boost::serialization::make_array(loadsBlendWeight_.data(), storedSize);

                ar >> boost::serialization::make_array(targetTypes_.data(), storedSize);
            }
            else {
                throw boost::archive::archive_exception(boost::archive::archive_exception::exception_code::array_size_too_short);
            }
        }

        validate();

        initTargetTypes(); // Just in case they got goofed up somehow
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

BOOST_CLASS_VERSION(LpsSaJobMgrTasks, 2);
