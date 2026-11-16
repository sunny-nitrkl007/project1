#ifndef JOBMGRPROTOCOLTYPES_H_
#define JOBMGRPROTOCOLTYPES_H_

#include <cstdint>

namespace jobmgr_data {

typedef enum
{
    LPS_SA_JOB_MGR_TIP_OFF_TRIGGER_AUTO = 0,
    LPS_SA_JOB_MGR_TIP_OFF_TRIGGER_MANUAL = 1,
    LPS_SA_JOB_MGR_TIP_OFF_TRIGGER_DISABLED = 2
} LpsSaTipOffTriggerType_t;

typedef enum
{
    LPS_SA_JOB_MGR_TIP_OFF_PILE_ENABLE = 0,
    LPS_SA_JOB_MGR_TIP_OFF_TRUCK_ENABLE = 1,
    LPS_SA_JOB_MGR_TIP_OFF_UNAVAILABLE = 2
} LpsSaJobMgrTipOffState_t;

typedef enum
{
    LPS_SA_JOB_MGR_MAN_TIP_OFF_AVAILABLE = 0,
    LPS_SA_JOB_MGR_MAN_TIP_OFF_UNAVAILABLE,
    LPS_SA_JOB_MGR_MAN_TIP_OFF_ACTIVE,
    LPS_SA_JOB_MGR_MAN_TIP_OFF_INACTIVE
} LpsSaJobMgrManualTipOffState_t;

typedef enum
{
    LPS_SA_JOB_MGR_UNCALIBRATED = 0x0346,
    LPS_SA_JOB_MGR_WEIGH_MODE = 0x0009,
    LPS_SA_JOB_MGR_STANDBY_MODE = 0x00AF,
    LPS_SA_JOB_MGR_EXCESS_MODE = 0x034E
} LpsSaJobMgrOperationMode_t;

typedef enum
{
    LPS_SA_JOB_MGR_STANDBY_ACTIVATED = 0,
    LPS_SA_JOB_MGR_STANDBY_DEACTIVATED
} LpsSaJobMgrStandbyState_t;

typedef enum
{
    LPS_SA_JOB_MGR_CLEAR_BTN_ENABLED = 0,
    LPS_SA_JOB_MGR_MINUS_ONE_BTN_ENABLED
} LpsSaJobMgrClearMinusOneEnableStat_t;

typedef struct {
    float val;
    bool isOk;
} DispBestBktWt_t;

enum class ReqPloadCtrlSysStat_t : uint16_t
{
    NONE = 0x003A,
    CLEAR = 0x0227,
    REWEIGH = 0x02FB,
    ZERO = 0x035E,
    STORE = 0x035F,
    TIPOFFTOGGLE = 0x059E,
    MINUS_ONE = 0x0630
};

typedef enum
{
    SOUND_HORN = 0x031A,
    NOT_SOUND_HORN = 0x031B
} StorePloadHornStat_t;

namespace output {
constexpr uint8_t OUTPUT_SINK_3 = 2;
constexpr uint8_t PORT_OFF = 0;
constexpr uint8_t PORT_ON = 1;
constexpr uint8_t NO_FLASH = 0;
}

enum class LpsSaLoadRecordStoreAction : uint8_t {
    AUTO = 0,
    EXTERNAL,
    UI,
    TICKET_NOT_FOR_TRADE,
    TICKET_LEGAL_FOR_TRADE
};

enum LpsSaLoadRecordTargetType : uint8_t {
    SINGLE = 0,
    SPLIT = 1,
    BATCH = 2,
    MIX = 3,
    BLEND_LOADS = 4,
    BLEND_WEIGHT = 5,
};

}

#endif
