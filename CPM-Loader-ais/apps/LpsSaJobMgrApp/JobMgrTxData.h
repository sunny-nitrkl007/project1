#ifndef JOBMGRTXDATA_H_
#define JOBMGRTXDATA_H_

#include <cstdint>
#include <chrono>
#include <deque>
#include <string>
#include <LpsPtPublic.h>

#include "JobMgrProtocolTypes.h"
#include "JobMgrSimpleCalData.h"

namespace jobmgr_data {

class JobMgrTxData
{
public:
    JobMgrTxData() :
        timePoint(std::chrono::steady_clock::now()),
        taskNumber(1),
        passCount(0),
        truckWeight(0.f),
        truckWeightAccuracy(LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE),
        TruckStartWeight(0.f),
        remainingWeight(0.f),
        totalWeight(0.f),
        totalWeightAccuracy(LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE),
        subtotalCount(0),
        ticketId(),
        materialId(0),
        materialName(),
        materialDensity(0.f),
        truckId(0),
        truckName(),
        truckTargetWeight(0.f),
        truckListEnabled(true),
        materialListEnabled(true),
        tag1Enabled(false), customListName1(), tag1(),
        tag2Enabled(false), customListName2(), tag2(),
        tag3Enabled(false), customListName3(), tag3(),
        tag4Enabled(false), customListName4(), tag4(),
        ManualTipOffState(LpsSaJobMgrManualTipOffState_t::LPS_SA_JOB_MGR_MAN_TIP_OFF_UNAVAILABLE),
        TipOffTriggerType(LpsSaTipOffTriggerType_t::LPS_SA_JOB_MGR_TIP_OFF_TRIGGER_DISABLED),
        TipOffState(LpsSaJobMgrTipOffState_t::LPS_SA_JOB_MGR_TIP_OFF_UNAVAILABLE),
        OperationMode(LpsSaJobMgrOperationMode_t::LPS_SA_JOB_MGR_UNCALIBRATED),
        StandbyState(LpsSaJobMgrStandbyState_t::LPS_SA_JOB_MGR_STANDBY_DEACTIVATED),
        ClearMinusOneEnableStat(LpsSaJobMgrClearMinusOneEnableStat_t::LPS_SA_JOB_MGR_MINUS_ONE_BTN_ENABLED),
        DispBestBktWt{ 0.f, false },
        TipOffStateCfg(LpsSaJobMgrTipOffState_t::LPS_SA_JOB_MGR_TIP_OFF_UNAVAILABLE),
        simpleCalData(),
        storeCount(0),
        storeRejected(false),
        ReqPloadCtrlSysStat(ReqPloadCtrlSysStat_t::NONE),
        HornStoreState(StorePloadHornStat_t::NOT_SOUND_HORN),
        AutoStorePassCount(0),
        AutoTruckIdEnabled(false),
        AutoMaterialIdEnabled(false),
        manualAddEnabled(false),
        multiTaskEnabled(false),
        multiTaskCount(0),
        TipoffActive(false),
        tipoffAssistActive(false),
        tipoffAssistActiveEid(0),
        manualAddAvailable(false),
        splitModeEnabled(false),
        lftDisabled(false),
        targetType(0),
        stepNumber(1),
        iconType(0),
        targetPasses(0) {}

    std::chrono::steady_clock::time_point timePoint;

    uint8_t taskNumber;
    uint16_t passCount;
    float truckWeight;
    LpsWeighBktWtAccuracy_t truckWeightAccuracy;
    float TruckStartWeight;
    float remainingWeight;
    float totalWeight;
    LpsWeighBktWtAccuracy_t totalWeightAccuracy;
    uint32_t subtotalCount;
    std::string ticketId;

    uint32_t materialId;
    std::string materialName;
    float materialDensity;

    uint32_t truckId;
    std::string truckName;
    float truckTargetWeight;

    bool truckListEnabled;
    bool materialListEnabled;

    bool tag1Enabled;
    std::string customListName1;
    std::string tag1;
    bool tag2Enabled;
    std::string customListName2;
    std::string tag2;
    bool tag3Enabled;
    std::string customListName3;
    std::string tag3;
    bool tag4Enabled;
    std::string customListName4;
    std::string tag4;

    LpsSaJobMgrManualTipOffState_t ManualTipOffState;
    LpsSaTipOffTriggerType_t TipOffTriggerType;
    LpsSaJobMgrTipOffState_t TipOffState;
    LpsSaJobMgrOperationMode_t OperationMode;
    LpsSaJobMgrStandbyState_t StandbyState;
    LpsSaJobMgrClearMinusOneEnableStat_t ClearMinusOneEnableStat;
    DispBestBktWt_t DispBestBktWt;
    LpsSaJobMgrTipOffState_t TipOffStateCfg;
    std::deque<SimpleCalData_t> simpleCalData;
    unsigned int storeCount;
    bool storeRejected;
    ReqPloadCtrlSysStat_t ReqPloadCtrlSysStat;
    StorePloadHornStat_t HornStoreState;
    uint16_t AutoStorePassCount;
    bool AutoTruckIdEnabled;
    bool AutoMaterialIdEnabled;
    bool manualAddEnabled;
    bool multiTaskEnabled;
    uint8_t multiTaskCount;
    bool TipoffActive;
    bool tipoffAssistActive;
    uint_least16_t tipoffAssistActiveEid;
    bool manualAddAvailable;
    bool splitModeEnabled;
    bool lftDisabled;
    uint8_t targetType;
    uint16_t stepNumber;
    uint8_t iconType;
    uint16_t targetPasses;

    inline bool ReadHornStoreEnable( void ){ return HornStoreState == SOUND_HORN? true : false;}
};

}

#endif
