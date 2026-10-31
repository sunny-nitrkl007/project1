/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef _CoachingTask_h_
#define _CoachingTask_h_

#include <deque>
#include <mutex>
#include <numeric>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>

#include <ais/task/Task.h>
#include <ais/time/PassiveTimer.h>

#include <interfaces/CoachingTipHistory/InterfaceTypes.h>
#include <interfaces/CoachingShowHideStatus/InterfaceTypes.h>
#include <interfaces/CoachingSummaryData/InterfaceTypes.h>
#include <interfaces/Coaching3x3Data/InterfaceTypes.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <interfaces/BreadcrumbLog/InterfaceTypes.h>
#include <interfaces/ShmClock/InterfaceTypes.h>

#include "CoachingTaskWsInterface.h"
#include "CoachingAppSpecificInterface.h"
#include "CoachingTaskServer.h"

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

/*******************************************************************************
** -- Class Declaration and Definition --
*******************************************************************************/

class CoachingTask : public task::Task, coaching_task::IWsApp
{
public:
    // task::Task construction requires a task name
    CoachingTask( ) = default;
    CoachingTask(const std::string& taskName );

    // ALWAYS virtual destructors for polymorphic classes
    ~CoachingTask( ) override;

    // principal task::Task interface: all derivatives must implement these

    // called once, at startup, after comms are connected
    bool initialize( ) override;

    // called periodically, according to the task config file
    bool executive( ) override;

    // called on the first Ctrl-C for pre-exit cleanup
    void cleanup( ) override;

    // IApp interface
    void sendData(coaching_task::GrpId grpId) override;
    void setPublishRate(coaching_task::GrpId grpId, uint32_t interval) override;
    void setOperatorId(const std::string& operatorId) override;
    void setTipAutoEnableTime(int64_t tipAutoEnableTimeSeconds) override;
    void setElapsedTimeSec(int64_t elapsedTimeSec) override;
    void setOpTipOnOff(bool tipOn, uint32_t tipNumber) override;
    void setSysTipShowHide(bool showTip, uint32_t tipNumber) override;
    void resetStats() override;
    void setBreadcrumbRequestedRecords(size_t maxRequestedBreadcrumbRecords) override;
    void setBreadcrumbGpsTimeSeconds(size_t BreadcrumbGpsTimeSeconds) override;
    void setBreadcrumbGpsDistanceMeters(size_t BreadcrumbGpsDistanceMeters) override;
    void setTutorialViewed(uint32_t tipNumber) override;
    void setTipViewed(uint32_t tipNumber) override;
    void setTipIncrement(uint32_t tipNumber) override;
    void setTipDecrement(uint32_t tipNumber) override;

private:
    class WebsocketTimer
    {
    public:
        // Sets up the timer.  If timeout is 0, the timer is deactivated
        void setTimer(uint32_t timeout)
        {
            this->timeout = timeout;
            timer = 0;
        }

        // Runs the timer (if active) and returns true if expired, false otherwise
        bool isExpired()
        {
            if ((timeout > 0) && (++timer > timeout))
            {
                timer = 0;
                return true;
            }
            return false;
        }

        WebsocketTimer() : timeout{0}, timer{0} {}

    private:
        uint32_t timeout;
        uint32_t timer;
    };

    // Limit val by min and max.  max must be > min
    template<class T>
    T limit(T val, T min, T max) { return val < min ? min : (val > max ? max : val); }

    static constexpr uint32_t DefaultWsPort = 55566;

    const std::string NvmFileExtension = ".bin";
    const std::string DefaultCoachingDataPath = R"(/tmp/CoachingTask/CoachingDataRecords)";
    const std::string DefaultOperatorId = "None";
    const std::string DefaultVideoPath = R"(/CPM/videos)";      // taking out /opt and /www since this is not needed when using lighttpd server
    const std::string OperatorIdListFileName = "OperatorIds" + NvmFileExtension;
    const std::string CoachingTipHistoryFileName = "CoachingTipHistory" + NvmFileExtension;

    // SCS Channels
    CoachingShowHideStatusOutput *coachingShowHideStatusOutput;
    CoachingSummaryDataOutput *coachingSummaryDataOutput;
    Coaching3x3DataOutput *coaching3x3DataOutput;
    CoachingTipHistoryOutput *coachingTipHistoryOutput;
    DataLinkDataInput *dataLinkDataInput;
    BreadcrumbLogOutput *breadcrumbLogOutput;
    ShmClockInput *shmClockInput;

    ConfigSection& configs;

    CoachingAppSpecific* coachingAppSpecific;
    CoachingSummaryData coachingSummaryData;
    Coaching3x3DataList coaching3x3DataList;
    BreadcrumbLog breadcrumbLog;
    CoachingShowHideStatus coachingShowHideStatus;
    CoachingTipHistory coachingTipHistory;
    boost::filesystem::path coachingDataPath;
    PassiveTimer tipHistoryStartupTimer;
    float cycleRate_hz;
    std::string activeOperatorId;
    std::vector<std::string> operatorList;
    uint32_t maxSavedOperators;
    size_t BreadcrumbRequestedRecords;
    size_t BreadcrumbMaxRecords;
    size_t BreadcrumbMinRecords;
    size_t BreadcrumbGpsTimeSeconds;
    size_t BreadcrumbGpsDistanceMeters;
    uint32_t displayRequiredTimeSeconds;
    uint32_t nvmWriteWaitTimeSeconds;
    int64_t nvmWriteSecondsSinceEpoch;
    float algorithmWmaWindowHrs;
    bool algorithmIsPoisson;
    boost::filesystem::path videoPath;
    bool shuttingDown;
    bool coachingSystemEnabled;
    bool coachingEnabledDefault;
    bool coachingInstalledDefault;
    bool coachingFake_SafeState;
    bool tipAutoEnableTimeSeconds_wsFlag;  // indicates new value from WebSocket

    // Websocket Server
    mutable std::mutex wsMutex;
    std::unique_ptr<coaching_task::Server> pServer;
    std::array<WebsocketTimer,coaching_task::GRP_ID_SIZE> wsTimers;

    // CoachingTask
    void sendDataToWs(coaching_task::GrpId grpId);
    void setOperatorIdImpl(const std::string& operatorId);
    void setTipAutoEnableTimeImpl(int64_t tipAutoEnableTimeSeconds);
    void setMetadata();

    // CoachingTaskNVM
    void initCoachingRecords();
    bool loadCoachingRecords();
    bool saveCoachingRecords();
    void manageOperatorIdList();
    bool loadOperatorIdList();
    bool saveOperatorIdList();

    // CoachingTaskGPS
    void checkGPS(DataLinkParam *dlParam);

    // Check DL Good/Bad for Breadcrumbs Log
    void checkBreadcrumbDlGoodBadStatus();

};

#endif
