#ifndef DEBUGSTAGING_H_
#define DEBUGSTAGING_H_

#include <cstdint>
#include <std_t.h>
#include <LpsCommonTypeDef.h>
#include <cpm_filter.h>
#include <LpsCommonStructures.h>
#include <LpsPublic.h>
#include <LpsPrivate.h>
#include "adv/TipoffAssist.h"

namespace weigh_data {

class DebugStaging {
public:
    DebugStaging() :
        m_LpsWrk(),
        m_TipoffInputs(),
        m_TipoffOutputs() {
        m_LpsWrk.DigDetectData.DigDetected = false;
        m_LpsWrk.DigDetectData.WtStabilized = false;
        m_LpsWrk.WrwTbl.WkTbl.BeenBelowRange = false;
        m_LpsWrk.OverloadWarnTbl.DigReverseFlag = false;
        m_LpsWrk.OverloadWarnTbl.InOverloadRange = false;
        m_LpsWrk.OverloadWarnTbl.Level = LPS_WEIGH_OVERLOAD_LEVEL_NONE;
    }

    LpsWrkTbl_t m_LpsWrk;
    TipoffAssistInputs m_TipoffInputs;
    TipoffAssistOutputs m_TipoffOutputs;

    unsigned_16 reweighWarn = 0;

    int DebugLiftCylHePeriod = 0;
    int DebugLiftCylHeWidth = 0;
    float DebugLiftCylHeDc = 0.f;
    float DebugLiftCylHePress = 0.f;
    LpsStat_t DebugLiftCylHePressStatus = LPS_STATUS_BAD;

    int DebugLiftCylRePeriod = 0;
    int DebugLiftCylReWidth = 0;
    float DebugLiftCylReDc = 0.f;
    float DebugLiftCylRePress = 0.f;
    LpsStat_t DebugLiftCylRePressStatus = LPS_STATUS_BAD;

    int DebugTiltCylHePeriod = 0;
    int DebugTiltCylHeWidth = 0;
    float DebugTiltCylHeDc = 0.f;
    float DebugTiltCylHePress = 0.f;
    LpsStat_t DebugTiltCylHePressStatus = LPS_STATUS_BAD;

    int DebugTiltCylRePeriod = 0;
    int DebugTiltCylReWidth = 0;
    float DebugTiltCylReDc = 0.f;
    float DebugTiltCylRePress = 0.f;
    LpsStat_t DebugTiltCylRePressStatus = LPS_STATUS_BAD;

    int DebugLiftCylPeriod = 0;
    int DebugLiftCylWidth = 0;
    float DebugLiftCylDc = 0.f;
    float DebugLiftCylRawExt = 0.f;
    float DebugLiftCylFiltExt = 0.f;
    float DebugLiftCylNormLen = 0.f;
    float DebugLiftCylVel = 0.f;
    float DebugLiftAngle = 0.f;
    float DebugLiftAngVel = 0.f;
    LpsStat_t DebugLiftPositionStatus = LPS_STATUS_BAD;

    int DebugTiltCylPeriod = 0;
    int DebugTiltCylWidth = 0;
    float DebugTiltCylDc = 0.f;
    float DebugTiltCylRawLen = 0.f;
    float DebugTiltCylNormLen = 0.f;
    float DebugTiltCylVel = 0.f;
    float DebugTiltAngle = 0.f;
    float DebugTiltAngleABC = 0.f;
    LpsStat_t DebugTiltPositionStatus = LPS_STATUS_BAD;

    float DebugBucketAngle = 0.f;
    LpsStat_t DebugBucketAngleStatus = LPS_STATUS_BAD;
    float DebugHydOilTemp = 0.f;
    LpsHydOilTempSensorStat_t DebugHydOilTempStatus = LPS_HYD_OIL_TEMP_STATUS_BAD;
    uint16_t DebugRequestedGear = 0;
    LpsStat_t DebugRequestedGearStatus = LPS_STATUS_BAD;
    float DebugWeighUpdtLoaderBktPayldTrgtWt = 0.f;
    uint32_t DebugWeighUpdtClockKeyonSec = 0;
    uint32_t DebugWeighUpdtPassCount = 0;

    float chassisImuGravityX = 0.f;
    float chassisImuGravityY = 0.f;
    float chassisImuGravityZ = 0.f;
    float chassisImuVelocityX = 0.f;
    float chassisImuVelocityY = 0.f;
    float chassisImuVelocityZ = 0.f;
    float chassisImuBiasMagJerk = 0.f;
    float chassisImuBiasMagAngAccel = 0.f;
    float chassisImuBiasMaxAngVel = 0.f;
    float chassisImuBiasAngVelX = 0.f;
    float chassisImuBiasAngVelY = 0.f;
    float chassisImuBiasAngVelZ = 0.f;
    float chassisImuPitch = 0.f;
    float chassisImuRoll = 0.f;
    uint8_t chassisImuSensorLinAccStatus = 0;
    uint8_t chassisImuSensorAngVelStatus = 0;
    float chassisImuLinAccX = 0.f;
    float chassisImuLinAccY = 0.f;
    float chassisImuLinAccZ = 0.f;
    float chassisImuAngVelX = 0.f;
    float chassisImuAngVelY = 0.f;
    float chassisImuAngVelZ = 0.f;
};

using LpsSaWeighDebugChannelStorage = DebugStaging;
using LpsSaWeighDebugChannel = DebugStaging;

}

#endif
