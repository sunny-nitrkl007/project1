#ifndef PROTOCOLTYPES_H_
#define PROTOCOLTYPES_H_

#include <bitset>
#include <chrono>
#include <cstdint>
#include <LpsPublic.h>
#include <cdl2_struct.h>
#include <scl_prmsw.h>

namespace weigh_data {

typedef enum
{
    ZEROED = 0x0394,
    NOT_ZEROED = 0x0395
} PloadSysZeroStat_t;

typedef enum
{
    CAL_ENTRY_REQUIRED = 0x001A,
    CAL_ENTRY_NOT_REQUIRED = 0x001B
} PloadSysCalWtEntryReqStat_t;

typedef enum
{
    BUCKET_PAYLOAD_NOT_AVAILABLE = 0,
    BUCKET_PAYLOAD_AVAILABLE = 1,
    BUCKET_PAYLOAD_STORED = 2,
    BUCKET_PAYLOAD_NOT_INSTALLED = 0xF4
} BktPayloadData_t;

namespace ACDInfoPopUp {
    enum {
        PAYLOAD_TOO_HEAVY_TO_ZERO,
        PAYLOAD_NOT_ZEROED,
        PAYLOAD_CAL_ACCEPTED,
        PAYLOAD_ZERO_ACCEPTED,
        PAYLOAD_REWEIGH_LIFT_TOO_SLOW,
        PAYLOAD_REWEIGH_STOPPED_IN_RANGE,
        PAYLOAD_REWEIGH_NOT_RACKED,
        PAYLOAD_REWEIGH_SPEED_CHANGING,
        PAYLOAD_REWEIGH_INCONSISTENT,
        PAYLOAD_REWEIGH_PRESSURE_CHANGING,
        PAYLOAD_REWEIGH_EXCESSIVE_PITCH,
        PAYLOAD_REWEIGH_WARMUP_LIFT,
        PAYLOAD_RAISE_STALL,
        PAYLOAD_LOWER_STALL,
        PAYLOAD_CAL_WT_ENTRY_REQUIRED,
        NUM_BITS,
    };
    static_assert(NUM_BITS <= 32, "ACDInfoPopUp::NUM_BITS > 32");
    typedef std::bitset<NUM_BITS> type;
}

namespace ACDWeighStatus {
    enum {
        LOWER_STALL = 7,
        RAISE_STALL,
        INSUFFICIENT_DATA,
        REWEIGH_PRESSURE_CHANGING,
        REWEIGH_INCONSISTENT,
        REWEIGH_SPEED_CHANGING,
        REWEIGH_NOT_RACKED_EXCESSIVE_PITCH,
        REWEIGH_STOPPED_IN_RANGE,
        REWEIGH_LIFT_TOO_SLOW,
        NUM_BITS,
    };
    static_assert(NUM_BITS <= 16, "ACDWeighStatus::NUM_BITS > 16");
    typedef std::bitset<NUM_BITS> type;
}

namespace ACDDiagPopUp {
    enum {
        TILT_RE_FREQ_ABNORMAL = 8,
        TILT_RE_VOLTAGE_BELOW_NORMAL,
        TILT_RE_VOLTAGE_ABOVE_NORMAL,
        TILT_HE_FREQ_ABNORMAL,
        TILT_HE_VOLTAGE_BELOW_NORMAL,
        TILT_HE_VOLTAGE_ABOVE_NORMAL,
        HYDRAULIC_OIL_TEMP_BAD,
        MACHINE_MODEL_NOT_SET,
        PAYLOAD_SYSTEM_NOT_INSTALLED,
        PAYLOAD_SYSTEM_OUT_OF_CAL,
        LIFT_RE_FREQ_ABNORMAL,
        LIFT_RE_VOLTAGE_BELOW_NORMAL,
        LIFT_RE_VOLTAGE_ABOVE_NORMAL,
        LIFT_HE_FREQ_ABNORMAL,
        LIFT_HE_VOLTAGE_BELOW_NORMAL,
        LIFT_HE_VOLTAGE_ABOVE_NORMAL,
        LIFT_LINK_OUT_OF_CAL,
        LIFT_LINK_FREQ_ABNORMAL,
        LIFT_LINK_VOLTAGE_BELOW_NORMAL,
        LIFT_LINK_VOLTAGE_ABOVE_NORMAL,
        TILT_LINK_OUT_OF_CAL,
        TILT_LINK_FREQ_ABNORMAL,
        TILT_LINK_VOLTAGE_BELOW_NORMAL,
        TILT_LINK_VOLTAGE_ABOVE_NORMAL,
        NUM_BITS,
    };
    static_assert(NUM_BITS <= 32, "ACDDiagPopUp::NUM_BITS > 32");
    typedef std::bitset<NUM_BITS> type;
}

namespace ACDEventPopUp {
    enum {
        BATTERY_HIGH = 28,
        BATTERY_LOW = 29,
        PAYLOAD_LFT_NOT_SEALED = 30,
        OVERLOAD_LIMIT_EXCEEDED = 31,
        NUM_BITS,
    };
    static_assert(NUM_BITS <= 32, "ACDEventPopUp::NUM_BITS > 32");
    typedef std::bitset<NUM_BITS> type;
}

struct LpsSaLiftPosition_t {
    float angle;
    float percentAngle;
    float cylinderLength;
    float percentCylinderLength;
    float cylinderExtension;
    LpsStat_t status;

    LpsSaLiftPosition_t() :
        angle(0.f),
        percentAngle(0.f),
        cylinderLength(0.f),
        percentCylinderLength(0.f),
        cylinderExtension(0.f),
        status(LPS_STATUS_BAD) {}
};

struct LpsSaTiltPosition_t {
    float angle;
    float percentAngle;
    float cylinderLength;
    float percentCylinderLength;
    float cylinderExtension;
    float bucketAngle;
    LpsStat_t status;

    LpsSaTiltPosition_t() :
        angle(0.f),
        percentAngle(0.f),
        cylinderLength(0.f),
        percentCylinderLength(0.f),
        cylinderExtension(0.f),
        bucketAngle(0.f),
        status(LPS_STATUS_BAD) {}
};

typedef LpsInstWtRawStat_t LpsSaPayloadRatioStatus_t;
#define LPS_SA_PAYLOAD_RATIO_STATUS_OK LPS_INST_RAW_WT_STATUS_OK
#define LPS_SA_PAYLOAD_RATIO_STATUS_UNKNOWN LPS_INST_RAW_WT_STATUS_BAD
#define LPS_SA_PAYLOAD_RATIO_STATUS_RAISE_STALL LPS_INST_RAW_WT_STATUS_RAISE_STALL
#define LPS_SA_PAYLOAD_RATIO_STATUS_LOWER_STALL LPS_INST_RAW_WT_STATUS_LOWER_STALL

struct LpsSaPayload_t {
    float payloadRatioRaw;
    float payloadRatio;
    LpsSaPayloadRatioStatus_t payloadRatioStatus;

    LpsSaPayload_t() :
        payloadRatioRaw(0.f),
        payloadRatio(0.f),
        payloadRatioStatus(LPS_SA_PAYLOAD_RATIO_STATUS_UNKNOWN) {}
};

struct LpsSaLftSealStatus_t {
    bool sealed = false;
    std::chrono::system_clock::time_point sealTime;
    uint_least32_t sealId;

    LpsSaLftSealStatus_t() :
        sealed(false),
        sealTime(std::chrono::system_clock::time_point::min()),
        sealId(0) {}
};

class LpsSaWeighTxChannelStorage {
public:
    enum ToaAnchorStatus_t {
        UNCHANGED,
        RESET,
        ACCEPTED,
        REJECTED
    };

    enum TiltSensorConfig_t : uint16_t {
        ROTARY_POSITION_SENSOR = 0x01C3,
        IN_CYLINDER_POSITION_SENSOR = 0x01C4
    };

    enum AudibleAnnunciationPriority_t : uint16_t {
        TONE_NONE = 0,
        TONE_CONFIRMATION = 2,
        TONE_ATTENTION = 6
    };

    enum TestStatus_t : uint8_t {
        INACTIVE = 0,
        TESTING,
        RECORDING,
        FAILED
    };
};

using LpsSaWeighTxChannel = LpsSaWeighTxChannelStorage;

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
    LPS_SA_JOB_MGR_STANDBY_ACTIVATED = 0,
    LPS_SA_JOB_MGR_STANDBY_DEACTIVATED
} LpsSaJobMgrStandbyState_t;

namespace VarLengthDataLinkParamFactory {
    enum VarLengthParamType {
        NOT_APPLICABLE,
        GPS,
        SPL_PID_REV_DATA_BYTE_ORDER,
        TIME_ZONE,
        PRODUCT_ID,
        PGN,
        SPN,
        do_not_use_SECURITY_SYSTEM_CURRENT_KEY,
        UNSUPPORTED,
        CAT_EXT
    };
}

class DataLinkParam {
public:
    typedef enum
    {
        DATA_LINK_PARAM_CDL = 0,
        DATA_LINK_PARAM_CAN1_1939,
        DATA_LINK_PARAM_CAN2_1939,
        DATA_LINK_PARAM_CAN3_1939,
        DATA_LINK_PARAM_ETH,
        DATA_LINK_PARAM_INT,
        DATA_LINK_PARAM_UNKNOWN,
        DATA_LINK_PARAM_UDP_CAN,
        DATA_LINK_PARAM_CDA
    } DlpDataLinkType_t;

    typedef enum
    {
        DATA_LINK_PARAM_IDENTIFIER_PID = 0,
        DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN,
        DATA_LINK_PARAM_IDENTIFIER_CAT_EXT,
        DATA_LINK_PARAM_IDENTIFIER_PROP_A_PGN,
        DATA_LINK_PARAM_IDENTIFIER_SPN,
        DATA_LINK_PARAM_IDENTIFIER_UNKNOWN,
        DATA_LINK_PARAM_IDENTIFIER_CPOP,
        DATA_LINK_PARAM_IDENTIFIER_S7_P,
        DATA_LINK_PARAM_IDENTIFIER_CDA
    } DlpParamIdentifierType_t;

    static constexpr uint_least16_t MakeDsiCode(cdl2_data_status_indentifiers_e cdl2_dsi) {
        return MakeDsiCode((uint_least8_t)cdl2_dsi);
    }

    static constexpr uint_least16_t MakeDsiCode(uint_least8_t dsi) {
        return (uint_least16_t)(0xFF00 | (0x001F & dsi));
    }

    static constexpr uint_least8_t ExtractDsi(uint_least16_t dsi_code) {
        return (uint_least8_t)(dsi_code & 0x001F);
    }

    static constexpr uint_least16_t DSI_CODE_OK() { return 0; }
    static constexpr uint_least16_t DSI_CODE_ABNORMAL_UPDATE() { return MakeDsiCode(CDL2_DSI_ABNORMAL_UPDATE); }
    static constexpr uint_least16_t DSI_CODE_PARAM_NOT_AVAIL() { return MakeDsiCode(CDL2_DSI_PARAM_NOT_AVAIL); }
    static constexpr uint_least16_t DSI_CODE_NO_RESPONSE() { return MakeDsiCode(CDL2_DSI_NO_RESPONSE); }
    static constexpr uint_least16_t DSI_CODE_CONDITIONS_NOT_MET() { return MakeDsiCode(CDL2_DSI_CONDITIONS_NOT_MET); }
};

typedef enum
{
    LPS_SA_CAL_SUCCESS = 0,
    LPS_SA_CAL_FAIL = 1,
    LPS_SA_CAL_UNKNOWN = 2
} CalibrationResponseCode;

enum rpa_application_ready_code_e {
    APP_READY_CODE_OK_TO_FLASH = 0
};
typedef int_least16_t rpa_application_ready_code_t;

class AutonomyConditionDiagnosticsTxInterfaceStorage {
public:
    static bool checkSEAInstallStatus(const uint16_t& status) {
        bool seaInstalled = false;

        switch(status)
        {
        case SCL_PRMSW_FEAT_STATUS_INSTALLED_ENABLED:
        case SCL_PRMSW_FEAT_STATUS_INSTALLED_DISABLED:
        case SCL_PRMSW_FEAT_STATUS_FREE_USE_INSTALLED:
            seaInstalled = true;
            break;
        case SCL_PRMSW_FEAT_STATUS_UNINSTALLED:
        case SCL_PRMSW_FEAT_STATUS_NONE:
        default:
            seaInstalled = false;
            break;
        }

        return seaInstalled;
    }

    static bool checkSEAEnableStatus(const uint16_t& status) {
        bool seaEnabled = false;

        switch(status)
        {
        case SCL_PRMSW_FEAT_STATUS_INSTALLED_ENABLED:
        case SCL_PRMSW_FEAT_STATUS_FREE_USE_INSTALLED:
            seaEnabled = true;
            break;
        case SCL_PRMSW_FEAT_STATUS_UNINSTALLED:
        case SCL_PRMSW_FEAT_STATUS_INSTALLED_DISABLED:
        case SCL_PRMSW_FEAT_STATUS_NONE:
        default:
            seaEnabled = false;
            break;
        }

        return seaEnabled;
    }
};

using AutonomyConditionDiagnosticsTxInterface = AutonomyConditionDiagnosticsTxInterfaceStorage;
using DataLinkParamInfo = DataLinkParam;

}

#endif
