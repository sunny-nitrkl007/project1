/*******************************************************************************
** COPYRIGHT (C) 2016-2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsSaLinkageTables.cpp
DESCRIPTION: Functions required for select the appropriate map for selected application
             to calculate lift and tilt parameters
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef  _LPS_SA_WEIGHAPP_H_
#include "LpsSaWeighApp.h"
#endif

#include <math.h>
#include <iostream>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
#define NORMALIZE(VAL, MIN, MAX) ((((float)(VAL) - (float)(MIN)) / ((float)(MAX) - (float)(MIN))) * 100.f)


/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
static float normalize(float val, float min, float max);

/******************************************************************************
FUNCTION NAME:normalize
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
static float normalize(float val, float min, float max) {
    float norm;

    if (val > max) {
        /* If exceeds max, set to 100% */
        norm = 100.0;
    }
    else if (val < min) {
        /* If less than min, set to 0% */
        norm = 0.0;
    }
    else {
        norm = ((val - min)/(max - min)) * 100.f;
    }

    return norm;
}

/******************************************************************************
FUNCTION NAME: LpsSaLoadKinematicsTbl
DESCRIPTION: This function reads the kinematics table from the ruby file
PARAMETER DESCRIPTION: none
RETURN VALUE: none
*******************************************************************************/
bool LpsSaWeighApp::LpsSaLoadKinematicsTbl(void)
{
    bool everythingOk = true;

    // Helper: declare a double_array param, read it, cast element-wise to float vector.
    // Returns true if the vector is non-empty after the read.
    auto getFloatArray = [&](const std::string& key,
                             std::vector<float>& dst) -> bool {
        declare_parameter<std::vector<double>>(key, std::vector<double>{});
        const auto v = get_parameter(key).as_double_array();
        dst.assign(v.begin(), v.end());
        return !dst.empty();
    };

    // --- WM-03: scalar params ---

    // tiltSensorType (optional, default ROTARY=0)
    // Clamp to uint8_t range before enum cast — mirrors the original uint8_t intermediate
    // that prevented out-of-range YAML values silently reaching the ROTARY/INLINE branch.
    declare_parameter<int>("kinematics.tilt_sensor_type",
                           static_cast<int>(TILT_SENSOR_TYPE_ROTARY));
    {
        const int raw = get_parameter("kinematics.tilt_sensor_type").as_int();
        const uint8_t clamped = (raw >= 0 && raw <= 255)
                                    ? static_cast<uint8_t>(raw)
                                    : static_cast<uint8_t>(TILT_SENSOR_TYPE_ROTARY);
        linkage_table_cnfg.tiltSensorType = static_cast<LpsSaTiltSensorType_t>(clamped);
    }
    AIS_LOG_INFO("tiltSensorType %u", linkage_table_cnfg.tiltSensorType);

    // hydPresSensorSlope (optional, default HYD_PRES_SENSOR_SLOPE = 0.0018)
    declare_parameter<double>("kinematics.hyd_pres_sensor_slope",
                              static_cast<double>(HYD_PRES_SENSOR_SLOPE));
    linkage_table_cnfg.hydPresSensorSlope = static_cast<float>(
        get_parameter("kinematics.hyd_pres_sensor_slope").as_double());
    AIS_LOG_INFO("hydPresSensorSlope %f", linkage_table_cnfg.hydPresSensorSlope);

    // hydPresSensorIntercept (optional, default HYD_PRES_SENSOR_INTERCEPT = 5.0)
    declare_parameter<double>("kinematics.hyd_pres_sensor_intercept",
                              static_cast<double>(HYD_PRES_SENSOR_INTERCEPT));
    linkage_table_cnfg.hydPresSensorIntercept = static_cast<float>(
        get_parameter("kinematics.hyd_pres_sensor_intercept").as_double());
    AIS_LOG_INFO("hydPresSensorIntercept %f", linkage_table_cnfg.hydPresSensorIntercept);

    // invertLiftDc (optional, default 0 = no invert)
    declare_parameter<int>("kinematics.invert_lift_dc", 0);
    linkage_table_cnfg.invertLiftDc = static_cast<uint16_t>(
        get_parameter("kinematics.invert_lift_dc").as_int());
    AIS_LOG_INFO("invertLiftDc %d", linkage_table_cnfg.invertLiftDc);

    // invertTiltDc (optional, default 0 = no invert)
    declare_parameter<int>("kinematics.invert_tilt_dc", 0);
    linkage_table_cnfg.invertTiltDc = static_cast<uint16_t>(
        get_parameter("kinematics.invert_tilt_dc").as_int());
    AIS_LOG_INFO("invertTiltDc %d", linkage_table_cnfg.invertTiltDc);

    // liftRefVel (optional, default 0)
    declare_parameter<double>("kinematics.lift_ref_vel", 0.0);
    linkage_table_cnfg.liftRefVel = static_cast<float>(
        get_parameter("kinematics.lift_ref_vel").as_double());
    AIS_LOG_INFO("liftRefVel %f", linkage_table_cnfg.liftRefVel);

    // --- WM-03: lift sensor array params (required) ---

    if (!getFloatArray("kinematics.in_lift_dc", linkage_table_cnfg.inLiftDc)) {
        AIS_LOG_ERROR("inLiftDc read fail.");
        everythingOk = false;
    }
    else {
        AIS_LOG_INFO("\n inLiftDc \n");
        for (const auto& value : linkage_table_cnfg.inLiftDc) { AIS_LOG_INFO("%f", value); }
    }

    if (!getFloatArray("kinematics.out_lift_angle", linkage_table_cnfg.outLiftAngle)) {
        AIS_LOG_ERROR("outLiftAngle read fail.");
        everythingOk = false;
    }
    else {
        if (linkage_table_cnfg.outLiftAngle.size() != linkage_table_cnfg.inLiftDc.size()) {
            AIS_LOG_ERROR("inLiftDc and outLiftAngle size mismatch.");
            everythingOk = false;
        }
        AIS_LOG_INFO("\n outLiftAngle \n");
        for (const auto& value : linkage_table_cnfg.outLiftAngle) { AIS_LOG_INFO("%f", value); }
    }

    if (!getFloatArray("kinematics.in_tilt_dc", linkage_table_cnfg.inTiltDc)) {
        AIS_LOG_ERROR("inTiltDc read fail.");
        everythingOk = false;
    }
    else {
        AIS_LOG_INFO("\n inTiltDc \n");
        for (const auto& value : linkage_table_cnfg.inTiltDc) { AIS_LOG_INFO("%f", value); }
    }

    if (!getFloatArray("kinematics.in_lift_angle", linkage_table_cnfg.inLiftAngle)) {
        AIS_LOG_ERROR("inLiftAngle read fail.");
        everythingOk = false;
    }
    else {
        AIS_LOG_INFO("\n inLiftAngle \n");
        for (const auto& value : linkage_table_cnfg.inLiftAngle) { AIS_LOG_INFO("%f", value); }
    }

    if (!getFloatArray("kinematics.out_lift_cyl_len", linkage_table_cnfg.outLiftCylLen)) {
        AIS_LOG_ERROR("outLiftCylLen read fail.");
        everythingOk = false;
    }
    else {
        if (linkage_table_cnfg.outLiftCylLen.size() != linkage_table_cnfg.inLiftAngle.size()) {
            AIS_LOG_ERROR("inLiftAngle and outLiftCylLen size mismatch.");
            everythingOk = false;
        }
        AIS_LOG_INFO("\n outLiftCylLen \n");
        for (const auto& value : linkage_table_cnfg.outLiftCylLen) { AIS_LOG_INFO("%f", value); }
    }

    // --- WM-03: optional lift array params ---

    if (getFloatArray("kinematics.out_lift_angle_gain", linkage_table_cnfg.outLiftAngleGain)) {
        if (linkage_table_cnfg.outLiftAngleGain.size() != linkage_table_cnfg.inLiftAngle.size()) {
            AIS_LOG_ERROR("inLiftAngle and outLiftAngleGain size mismatch.");
            everythingOk = false;
        }
    }
    else {
        // Not an error — may not be provided.
        AIS_LOG_INFO("outLiftAngleGain read error.");
        linkage_table_cnfg.outLiftAngleGain.clear();
    }

    if (getFloatArray("kinematics.out_lift_pres_no_bucket", linkage_table_cnfg.outLiftPresNoBucket)) {
        if (linkage_table_cnfg.outLiftPresNoBucket.size() != linkage_table_cnfg.inLiftAngle.size()) {
            AIS_LOG_ERROR("inLiftAngle and outLiftPresNoBucket size mismatch.");
            everythingOk = false;
        }
    }
    else {
        // Not an error — may not be provided.
        AIS_LOG_INFO("outLiftPresNoBucket read error.");
        linkage_table_cnfg.outLiftPresNoBucket.clear();
    }

    if (getFloatArray("kinematics.out_lift_angle_accel", linkage_table_cnfg.outLiftAngleAccel)) {
        if (linkage_table_cnfg.outLiftAngleAccel.size() != linkage_table_cnfg.inLiftAngle.size()) {
            AIS_LOG_ERROR("inLiftAngle and outLiftAngleAccel size mismatch.");
            everythingOk = false;
        }
    }
    else {
        // Not an error — may not be provided.
        AIS_LOG_INFO("outLiftAngleAccel read error.");
        linkage_table_cnfg.outLiftAngleAccel.clear();
    }

    // --- WM-03: tilt table params (required) ---
    // outTiltAngle and outTiltCylLen are required; if absent init must fail.

    bool outTiltAngleOk = getFloatArray("kinematics.out_tilt_angle",
                                        linkage_table_cnfg.outTiltAngle);
    bool outTiltCylLenOk = getFloatArray("kinematics.out_tilt_cyl_len",
                                         linkage_table_cnfg.outTiltCylLen);

    if (!outTiltAngleOk || !outTiltCylLenOk) {
        AIS_LOG_ERROR("outTiltAngle and/or outTiltCylLen read failed");
        return false;
    }

    {
        std::size_t outTiltAngleSizeExpected;
        std::size_t outTiltCylLenSizeExpected;

        if (linkage_table_cnfg.tiltSensorType == TILT_SENSOR_TYPE_ROTARY) {
            // Rotary sensor: read xTiltAngle, yLiftAngle (required for ROTARY)
            bool xOk = getFloatArray("kinematics.x_tilt_angle",
                                     linkage_table_cnfg.xTiltAngle);
            bool yOk = getFloatArray("kinematics.y_lift_angle",
                                     linkage_table_cnfg.yLiftAngle);
            if (!xOk || !yOk) {
                AIS_LOG_ERROR("xTiltAngle and/or yLiftAngle read failed");
                return false;
            }
            AIS_LOG_INFO("\n xTiltAngle \n");
            for (const auto& value : linkage_table_cnfg.xTiltAngle) { AIS_LOG_INFO("%f", value); }
            AIS_LOG_INFO("\n yLiftAngle \n");
            for (const auto& value : linkage_table_cnfg.yLiftAngle) { AIS_LOG_INFO("%f", value); }

            outTiltAngleSizeExpected  = linkage_table_cnfg.inTiltDc.size();
            outTiltCylLenSizeExpected = linkage_table_cnfg.xTiltAngle.size()
                                        * linkage_table_cnfg.yLiftAngle.size();
        }
        else { // TILT_SENSOR_TYPE_INLINE
            // Inline sensor: read xTiltCylLen, yLiftCylLen (required for INLINE)
            bool xOk = getFloatArray("kinematics.x_tilt_cyl_len",
                                     linkage_table_cnfg.xTiltCylLen);
            bool yOk = getFloatArray("kinematics.y_lift_cyl_len",
                                     linkage_table_cnfg.yLiftCylLen);
            if (!xOk || !yOk) {
                AIS_LOG_ERROR("xTiltCylLen and/or yLiftCylLen read failed");
                return false;
            }
            AIS_LOG_INFO("\n xTiltCylLen \n");
            for (const auto& value : linkage_table_cnfg.xTiltCylLen) { AIS_LOG_INFO("%f", value); }
            AIS_LOG_INFO("\n yLiftCylLen \n");
            for (const auto& value : linkage_table_cnfg.yLiftCylLen) { AIS_LOG_INFO("%f", value); }

            outTiltAngleSizeExpected  = linkage_table_cnfg.xTiltCylLen.size()
                                        * linkage_table_cnfg.yLiftCylLen.size();
            outTiltCylLenSizeExpected = linkage_table_cnfg.inTiltDc.size();
        }

        // Confirm outTiltAngle size matches expected
        if (linkage_table_cnfg.outTiltAngle.size() != outTiltAngleSizeExpected) {
            AIS_LOG_ERROR("outTiltAngle size mismatch.");
            return false;
        }
        AIS_LOG_INFO("\n outTiltAngle \n");
        for (const auto& value : linkage_table_cnfg.outTiltAngle) { AIS_LOG_INFO("%f", value); }

        // Confirm outTiltCylLen size matches expected
        if (linkage_table_cnfg.outTiltCylLen.size() != outTiltCylLenSizeExpected) {
            AIS_LOG_ERROR("outTiltCylLen size mismatch.");
            return false;
        }
        AIS_LOG_INFO("\n outTiltCylLen \n");
        for (const auto& value : linkage_table_cnfg.outTiltCylLen) { AIS_LOG_INFO("%f", value); }
    }

    // inTiltAngle (required)
    if (!getFloatArray("kinematics.in_tilt_angle", linkage_table_cnfg.inTiltAngle)) {
        AIS_LOG_ERROR("inTiltAngle read fail.");
        everythingOk = false;
    }
    else {
        AIS_LOG_INFO("\n inTiltAngle \n");
        for (const auto& value : linkage_table_cnfg.inTiltAngle) { AIS_LOG_INFO("%f", value); }
    }

    // outBktAngle (required, must match inTiltAngle size)
    if (!getFloatArray("kinematics.out_bkt_angle", linkage_table_cnfg.outBktAngle)) {
        AIS_LOG_ERROR("outBktAngle read fail.");
        everythingOk = false;
    }
    else {
        if (linkage_table_cnfg.outBktAngle.size() != linkage_table_cnfg.inTiltAngle.size()) {
            AIS_LOG_ERROR("inTiltAngle and outBktAngle size mismatch.");
            everythingOk = false;
        }
        AIS_LOG_INFO("\n outBktAngle \n");
        for (const auto& value : linkage_table_cnfg.outBktAngle) { AIS_LOG_INFO("%f", value); }
    }

    // KnmaticsTiltCylLenMinMax (required, must be size 2)
    if (!getFloatArray("kinematics.knmatics_tilt_cyl_len_min_max",
                       linkage_table_cnfg.KnmaticsTiltCylExtMinMax)) {
        AIS_LOG_ERROR("KnmaticsTiltCylLenMinMax read fail.");
        everythingOk = false;
    }
    else {
        if (2 != linkage_table_cnfg.KnmaticsTiltCylExtMinMax.size()) {
            AIS_LOG_ERROR("KnmaticsTiltCylLenMinMax size != 2.");
            everythingOk = false;
        }
        AIS_LOG_INFO("\n KnmaticsTiltCylLenMinMax \n");
        for (const auto& value : linkage_table_cnfg.KnmaticsTiltCylExtMinMax) { AIS_LOG_INFO("%f", value); }
    }

    // KnmaticsTiltAngleMinMax (required, must be size 2)
    if (!getFloatArray("kinematics.knmatics_tilt_angle_min_max",
                       linkage_table_cnfg.KnmaticsTiltAngleMinMax)) {
        AIS_LOG_ERROR("KnmaticsTiltAngleMinMax read fail.");
        everythingOk = false;
    }
    else {
        if (2 != linkage_table_cnfg.KnmaticsTiltAngleMinMax.size()) {
            AIS_LOG_ERROR("KnmaticsTiltAngleMinMax size != 2.");
            everythingOk = false;
        }
        AIS_LOG_INFO("\n KnmaticsTiltAngleMinMax \n");
        for (const auto& value : linkage_table_cnfg.KnmaticsTiltAngleMinMax) { AIS_LOG_INFO("%f", value); }
    }

    // KnmaticsLiftCylLenMinMax (required, must be size 2)
    if (!getFloatArray("kinematics.knmatics_lift_cyl_len_min_max",
                       linkage_table_cnfg.KnmaticsLiftCylExtMinMax)) {
        AIS_LOG_ERROR("KnmaticsLiftCylLenMinMax read fail.");
        everythingOk = false;
    }
    else {
        if (2 != linkage_table_cnfg.KnmaticsLiftCylExtMinMax.size()) {
            AIS_LOG_ERROR("KnmaticsLiftCylLenMinMax size != 2.");
            everythingOk = false;
        }
        AIS_LOG_INFO("\n KnmaticsLiftCylLenMinMax \n");
        for (const auto& value : linkage_table_cnfg.KnmaticsLiftCylExtMinMax) { AIS_LOG_INFO("%f", value); }
    }

    return everythingOk;
}


bool LpsSaWeighApp::LpsSaLoadMachineProperties(void)
{
    bool everythingOk = true;
    bool isAdvVariant = (ADVANCED == getApplicationVariant());

    AIS_LOG_INFO("MachineMSN: %s", machineMSN.c_str());

    // Internal Msn — derived by parsing machineMSN already read in WM-05
    try {
        std::string internal_msn_str = machineMSN.substr(3,5);
        machineProperties.internalMsn = std::stoi(internal_msn_str, 0, 10);
        AIS_LOG_INFO("InternalMsn: %d", machineProperties.internalMsn);
    }
    catch (...) {
        if (isAdvVariant) {
            AIS_LOG_ERROR("Error while parsing for internal msn");
            everythingOk = false;
        }
    }

    // --- WM-04: MachineSpecificConfig (machine properties) ---
    // NOTE: If no Robot_<variant>.yaml is loaded at launch, all params below fall back
    // to their declared defaults (mostly 0.0/0/false). The required-key checks below will
    // then fire and set everythingOk=false, causing LpsSaInitWeighTbl() to return false
    // and initialization to fail — matching the original behaviour where a missing
    // MachineSpecificConfig section caused an immediate return false.

    // ToolBcLen (ADV required)
    // NOTE: 0.0 is used as a sentinel for "not provided". No production robot has ToolBcLen=0.
    declare_parameter<double>("machine_specific_config.tool_bc_len", 0.0);
    machineProperties.toolBcLength = static_cast<float>(
        get_parameter("machine_specific_config.tool_bc_len").as_double());
    if (machineProperties.toolBcLength == 0.f && isAdvVariant) {
        AIS_LOG_ERROR("ToolBcLen not available in Cfg file");
        everythingOk = false;
    }
    AIS_LOG_INFO("ToolBcLen: %f", machineProperties.toolBcLength);

    // ToolBcAngle (ADV required)
    // NOTE: 0.0 sentinel — no production robot has ToolBcAngle=0.
    declare_parameter<double>("machine_specific_config.tool_bc_angle", 0.0);
    machineProperties.toolBcAngle = static_cast<float>(
        get_parameter("machine_specific_config.tool_bc_angle").as_double());
    if (machineProperties.toolBcAngle == 0.f && isAdvVariant) {
        AIS_LOG_ERROR("ToolBcAngle not available in Cfg file");
        everythingOk = false;
    }
    AIS_LOG_INFO("ToolBcAngle: %f", machineProperties.toolBcAngle);

    // NoOfTiltCyls (ADV required)
    // NOTE: 0 sentinel — no ADV production robot has 0 tilt cylinders.
    declare_parameter<int>("machine_specific_config.no_of_tilt_cyls", 0);
    machineProperties.numOfTiltCylinders = static_cast<uint8_t>(
        get_parameter("machine_specific_config.no_of_tilt_cyls").as_int());
    if (machineProperties.numOfTiltCylinders == 0 && isAdvVariant) {
        AIS_LOG_ERROR("NoOfTiltCyls not available in Cfg file");
        everythingOk = false;
    }
    AIS_LOG_INFO("NoOfTiltCyls: %d", machineProperties.numOfTiltCylinders);

    // TiltCylBoreDia (ADV required)
    // NOTE: 0.0 sentinel — no production robot has a tilt cylinder bore of 0 mm.
    declare_parameter<double>("machine_specific_config.tilt_cyl_bore_dia", 0.0);
    machineProperties.tiltBoreDiameter = static_cast<float>(
        get_parameter("machine_specific_config.tilt_cyl_bore_dia").as_double());
    if (machineProperties.tiltBoreDiameter == 0.f && isAdvVariant) {
        AIS_LOG_ERROR("TiltCylBoreDia not available in Cfg file");
        everythingOk = false;
    }
    AIS_LOG_INFO("TiltCylBoreDia: %f", machineProperties.tiltBoreDiameter);

    // TiltCylRodDia (ADV required)
    // NOTE: 0.0 sentinel — no production robot has a tilt cylinder rod of 0 mm.
    declare_parameter<double>("machine_specific_config.tilt_cyl_rod_dia", 0.0);
    machineProperties.tiltRodDiameter = static_cast<float>(
        get_parameter("machine_specific_config.tilt_cyl_rod_dia").as_double());
    if (machineProperties.tiltRodDiameter == 0.f && isAdvVariant) {
        AIS_LOG_ERROR("TiltCylRodDia not available in Cfg file");
        everythingOk = false;
    }
    AIS_LOG_INFO("TiltCylRodDia: %f", machineProperties.tiltRodDiameter);

    // NoOfLiftCyls (always required)
    // NOTE: 0 sentinel — every production robot has at least 1 lift cylinder.
    declare_parameter<int>("machine_specific_config.no_of_lift_cyls", 0);
    machineProperties.numOfLiftCylinders = static_cast<uint8_t>(
        get_parameter("machine_specific_config.no_of_lift_cyls").as_int());
    if (machineProperties.numOfLiftCylinders == 0) {
        AIS_LOG_ERROR("NoOfLiftCyls not available in Cfg file");
        everythingOk = false;
    }
    AIS_LOG_INFO("NoOfLiftCyls: %d", machineProperties.numOfLiftCylinders);

    // LiftCylBoreDia (always required)
    // NOTE: 0.0 sentinel — no production robot has a lift cylinder bore of 0 mm.
    declare_parameter<double>("machine_specific_config.lift_cyl_bore_dia", 0.0);
    machineProperties.liftBoreDiameter = static_cast<float>(
        get_parameter("machine_specific_config.lift_cyl_bore_dia").as_double());
    if (machineProperties.liftBoreDiameter == 0.f) {
        AIS_LOG_ERROR("LiftCylBoreDia not available in Cfg file");
        everythingOk = false;
    }
    AIS_LOG_INFO("LiftCylBoreDia: %f", machineProperties.liftBoreDiameter);

    // LiftCylRodDia (always required)
    // NOTE: 0.0 sentinel — no production robot has a lift cylinder rod of 0 mm.
    declare_parameter<double>("machine_specific_config.lift_cyl_rod_dia", 0.0);
    machineProperties.liftRodDiameter = static_cast<float>(
        get_parameter("machine_specific_config.lift_cyl_rod_dia").as_double());
    if (machineProperties.liftRodDiameter == 0.f) {
        AIS_LOG_ERROR("LiftCylRodDia not available in Cfg file");
        everythingOk = false;
    }
    AIS_LOG_INFO("LiftCylRodDia: %f", machineProperties.liftRodDiameter);

    // DigTargetWt (ADV required)
    declare_parameter<double>("machine_specific_config.dig_target_wt", 0.0);
    machineProperties.ratedPayload = static_cast<float>(
        get_parameter("machine_specific_config.dig_target_wt").as_double());
    if (machineProperties.ratedPayload == 0.f && isAdvVariant) {
        AIS_LOG_ERROR("DigTargetWt not available in Cfg file");
        everythingOk = false;
    }
    AIS_LOG_INFO("DigTargetWt: %f", machineProperties.ratedPayload);

    // LoaderBktPayldTrgtWt (optional, default 0)
    declare_parameter<double>("machine_specific_config.loader_bkt_payld_trgt_wt", 0.0);
    machineProperties.bucketPayloadTargetWeightDefault = static_cast<float>(
        get_parameter("machine_specific_config.loader_bkt_payld_trgt_wt").as_double());
    AIS_LOG_INFO("LoaderBktPayldTrgtWt: %f", machineProperties.bucketPayloadTargetWeightDefault);

    // LiftArmAbLength (optional, default 0)
    declare_parameter<double>("machine_specific_config.lift_arm_ab_length", 0.0);
    machineProperties.liftArmAbLength = static_cast<float>(
        get_parameter("machine_specific_config.lift_arm_ab_length").as_double());
    AIS_LOG_INFO("LiftArmAbLength: %f", machineProperties.liftArmAbLength);

    // KgPerLiftKpaAtMidExtension (optional, default 0)
    declare_parameter<double>("machine_specific_config.kg_per_lift_kpa_at_mid_ext", 0.0);
    machineProperties.kgPerLiftKpaAtMidExtension = static_cast<float>(
        get_parameter("machine_specific_config.kg_per_lift_kpa_at_mid_ext").as_double());
    AIS_LOG_INFO("KgPerLiftKpaAtMidExtension: %f", machineProperties.kgPerLiftKpaAtMidExtension);

    // LiftKpaNoBucketMidExtension (optional, default 0)
    declare_parameter<double>("machine_specific_config.lift_kpa_no_bucket_mid_ext", 0.0);
    machineProperties.liftKpaNoBucketMidExtension = static_cast<float>(
        get_parameter("machine_specific_config.lift_kpa_no_bucket_mid_ext").as_double());
    AIS_LOG_INFO("LiftKpaNoBucketMidExtension: %f", machineProperties.liftKpaNoBucketMidExtension);

    // HydOilTempOptional (optional, default false)
    declare_parameter<bool>("machine_specific_config.hyd_oil_temp_optional", false);
    machineProperties.hydOilTempOptional =
        get_parameter("machine_specific_config.hyd_oil_temp_optional").as_bool();
    AIS_LOG_INFO("HydOilTempOptional: %d", machineProperties.hydOilTempOptional);

    // HydOilTempEnabledDefault (optional, default true)
    // If HydOilTemp is not optional, force enabled regardless of config value.
    declare_parameter<bool>("machine_specific_config.hyd_oil_temp_enabled_default", true);
    machineProperties.hydOilTempEnabledDefault =
        get_parameter("machine_specific_config.hyd_oil_temp_enabled_default").as_bool();
    if (false == machineProperties.hydOilTempOptional) {
        machineProperties.hydOilTempEnabledDefault = true;
    }
    AIS_LOG_INFO("HydOilTempEnabledDefault is set to: %d", machineProperties.hydOilTempEnabledDefault);

    // AccelCompSupported (optional, default false)
    declare_parameter<bool>("machine_specific_config.accel_comp_supported", false);
    machineProperties.accelCompSupported =
        get_parameter("machine_specific_config.accel_comp_supported").as_bool();
    AIS_LOG_INFO("AccelCompSupported: %d", machineProperties.accelCompSupported);

    // LegalForTradeSupported (optional, default false) — also drives imuCompSupported
    declare_parameter<bool>("machine_specific_config.legal_for_trade_supported", false);
    machineProperties.legalForTradeSupported =
        get_parameter("machine_specific_config.legal_for_trade_supported").as_bool();
    AIS_LOG_INFO("LegalForTradeSupported: %d", machineProperties.legalForTradeSupported);

    // If LFT is supported, then IMU-based compensation is supported
    // In the future, this could be different where IMU-based compensation is supported
    // even without support for LFT, but not for now.
    machineProperties.imuCompSupported = machineProperties.legalForTradeSupported;

    // IMUCompLoadCGAngleOffset (optional, default 2.0)
    declare_parameter<double>("machine_specific_config.imu_comp_load_cg_angle_offset", 2.0);
    machineProperties.imuCompLoadCGAngleOffset = static_cast<float>(
        get_parameter("machine_specific_config.imu_comp_load_cg_angle_offset").as_double());
    AIS_LOG_INFO("IMUCompLoadCGAngleOffset: %f", machineProperties.imuCompLoadCGAngleOffset);

    return everythingOk;
}

/******************************************************************************
FUNCTION NAME: lpsSaGetLiftPosition
DESCRIPTION: Calculates the lift cylinder extension from the lift angle
PARAMETER DESCRIPTION: float liftAngle
RETURN VALUE: LpsSaLiftPosition_t
*******************************************************************************/
LpsSaLiftPosition_t LpsSaWeighApp::lpsSaGetLiftPosition(float liftAngle, bool liftOk)
{
    LpsSaLiftPosition_t liftPosition;
    liftPosition.angle = liftAngle;
    
    if ((liftOk) && (NULL != linkage_table_cnfg.outLiftCylLen.data())) {

        liftPosition.percentAngle = normalize(
                liftAngle,
                linkage_table_cnfg.inLiftAngle[0],
                linkage_table_cnfg.inLiftAngle[linkage_table_cnfg.inLiftAngle.size()-1]);

        /* Convert lift angle to cylinder length */
        float cylinderLength = LpsLookup(
                liftAngle,
                linkage_table_cnfg.inLiftAngle.data(),
                linkage_table_cnfg.outLiftCylLen.data(),
                linkage_table_cnfg.inLiftAngle.size());

        liftPosition.cylinderLength = cylinderLength;

        liftPosition.cylinderExtension = cylinderLength - linkage_table_cnfg.KnmaticsLiftCylExtMinMax[0];

        liftPosition.percentCylinderLength = normalize(
                cylinderLength,
                linkage_table_cnfg.outLiftCylLen[0],
                linkage_table_cnfg.outLiftCylLen[linkage_table_cnfg.outLiftCylLen.size()-1]);

        liftPosition.status = LPS_STATUS_OK;
    }
    else {
        liftPosition.percentAngle = 0;
        liftPosition.cylinderLength = 0;
        liftPosition.percentCylinderLength = 0;
        liftPosition.cylinderExtension = 0;
        liftPosition.status = LPS_STATUS_BAD;
    }

    return liftPosition;
}

/******************************************************************************
FUNCTION NAME: lpsSaGetLiftAngle
DESCRIPTION: Calculates the lift angle from lift dc
PARAMETER DESCRIPTION:
RETURN VALUE: float linkage_angle
*******************************************************************************/
float LpsSaWeighApp::lpsSaGetLiftAngle(float liftLinkageDc, bool liftOk)
{
    float liftAngle;

    if (liftOk) {
        /* Apply LPF on Dutycycle */
        cpm_filter_low_pass_filter2(&LiftLinkageSensorDcLpFilt, liftLinkageDc);

        float sensorDutyCycleFiltered = LiftLinkageSensorDcLpFilt.y;

        DebugLpsSaXCPChannels.DebugLiftCylDc = sensorDutyCycleFiltered;
        WeighPidTbl.LiftLinkageSensorDc = sensorDutyCycleFiltered;

        /* Normalize sensor duty cycle */
        float normalizedPosition = normalize(sensorDutyCycleFiltered,
                liftCalNvmTbl_.lift_full_lower_dc, liftCalNvmTbl_.lift_full_raise_dc);

        /* Convert duty cycle to lift angle */
        liftAngle = LpsLookup(normalizedPosition,
                linkage_table_cnfg.inLiftDc.data(),
                linkage_table_cnfg.outLiftAngle.data(),
                linkage_table_cnfg.inLiftDc.size());
    }
    else {
        // Reset the filter
        cpm_filter_low_pass_filter2_reset(&LiftLinkageSensorDcLpFilt);

        // Not good
        liftAngle = 0;
    }

    return liftAngle;
}

/******************************************************************************
FUNCTION NAME: lpsSaGetNormalizedTiltPosition
DESCRIPTION: Calculates normalized tilt position from dc
PARAMETER DESCRIPTION:
RETURN VALUE: float linkage_angle
*******************************************************************************/
float LpsSaWeighApp::lpsSaGetNormalizedTiltPosition(float tiltLinkageDc, bool tiltOk)
{
    float normalizedPosition;

    if (tiltOk) {
        /* Apply LPF to duty cycle */
        cpm_filter_low_pass_filter2(&TiltLinkageSensorDcLpFilt, tiltLinkageDc);

        float tiltSensorDutyCycleFiltered = TiltLinkageSensorDcLpFilt.y;

        DebugLpsSaXCPChannels.DebugTiltCylDc = tiltSensorDutyCycleFiltered;
        WeighPidTbl.TiltLinkageSensorDc = tiltSensorDutyCycleFiltered;

        /* Normalize sensor duty cycle for tilt */
        normalizedPosition = normalize(tiltSensorDutyCycleFiltered,
                tiltCalNvmTbl_.tilt_full_dump_dc, tiltCalNvmTbl_.tilt_full_rack_dc);
    }
    else {
        /* Reset the filter */
        cpm_filter_low_pass_filter2_reset(&TiltLinkageSensorDcLpFilt);

        normalizedPosition = 0;
    }

    return normalizedPosition;
}

/******************************************************************************
FUNCTION NAME: lpsSaGetTiltAngle
DESCRIPTION: Calculates the tilt angle from normalized tilt position
PARAMETER DESCRIPTION:
RETURN VALUE: float tilt linkage_angle
*******************************************************************************/
float LpsSaWeighApp::lpsSaGetTiltAngle(float tiltNormalizedPosition, bool tiltOk)
{
    (void)tiltOk;
    float tiltAngle = LpsLookup(tiltNormalizedPosition,
                        linkage_table_cnfg.inTiltDc.data(),
                        linkage_table_cnfg.outTiltAngle.data(),
                        linkage_table_cnfg.inTiltDc.size());

    return tiltAngle;
}

/******************************************************************************
FUNCTION NAME: lpsSaGetTiltRotaryPosition
DESCRIPTION: Calculates the tilt cylinder length from the given lift and
             tilt angles for rotary sensors
PARAMETER DESCRIPTION: float liftAngle, float tiltAngle
RETURN VALUE: LpsSaTiltPosition_t
*******************************************************************************/
LpsSaTiltPosition_t LpsSaWeighApp::lpsSaGetTiltRotaryPosition(float liftAngle, bool liftOk, float tiltAngle, bool tiltOk)
{
    LpsSaTiltPosition_t tiltPosition;
    tiltPosition.angle = tiltAngle;

    if ((liftOk) && (tiltOk) && (!linkage_table_cnfg.outTiltCylLen.empty())) {

        tiltPosition.percentAngle = normalize(tiltAngle,
                linkage_table_cnfg.KnmaticsTiltAngleMinMax[0],
                linkage_table_cnfg.KnmaticsTiltAngleMinMax[1]);

        /* Convert  lift angle to cylinder length */
        tiltPosition.cylinderLength = LpsLookup2d(
                liftAngle,
                tiltAngle,
                linkage_table_cnfg.yLiftAngle.data(),
                linkage_table_cnfg.xTiltAngle.data(),
                linkage_table_cnfg.outTiltCylLen.data(),
                linkage_table_cnfg.yLiftAngle.size(),
                linkage_table_cnfg.xTiltAngle.size());

        tiltPosition.cylinderExtension = tiltPosition.cylinderLength - linkage_table_cnfg.KnmaticsTiltCylExtMinMax[0];

        tiltPosition.percentCylinderLength = normalize(
                tiltPosition.cylinderLength,
                linkage_table_cnfg.KnmaticsTiltCylExtMinMax[0],
                linkage_table_cnfg.KnmaticsTiltCylExtMinMax[1]);

        tiltPosition.bucketAngle = liftAngle + LpsLookup(tiltAngle,
                linkage_table_cnfg.inTiltAngle.data(),
                linkage_table_cnfg.outBktAngle.data(),
                linkage_table_cnfg.inTiltAngle.size());

        tiltPosition.status = LPS_STATUS_OK;
    }
    else {
        tiltPosition.percentAngle = 0;
        tiltPosition.cylinderLength = 0;
        tiltPosition.percentCylinderLength = 0;
        tiltPosition.bucketAngle = 0;
        tiltPosition.cylinderExtension = 0;
        tiltPosition.status = LPS_STATUS_BAD;
    }

    return tiltPosition;
}   

/******************************************************************************
FUNCTION NAME: lpsSaGetTiltInlinePosition
DESCRIPTION: Calculates the tilt angle from the given lift and
             tilt cylinder length for inline sensors
PARAMETER DESCRIPTION: float liftAngle, float liftCylinderLength, float tiltCylinderLength
RETURN VALUE: LpsSaTiltPosition_t
*******************************************************************************/
LpsSaTiltPosition_t LpsSaWeighApp::lpsSaGetTiltInlinePosition(float liftAngle, float liftCylinderLength, bool liftOk, float tiltCylinderLength, bool tiltOk)
{
    LpsSaTiltPosition_t tiltPosition;
    tiltPosition.cylinderLength = tiltCylinderLength;

    if ((liftOk) && (tiltOk) && (!linkage_table_cnfg.outTiltAngle.empty())) {

        tiltPosition.cylinderExtension = tiltCylinderLength - linkage_table_cnfg.KnmaticsTiltCylExtMinMax[0];

        tiltPosition.percentCylinderLength = normalize(
            tiltCylinderLength,
            linkage_table_cnfg.KnmaticsTiltCylExtMinMax[0],
            linkage_table_cnfg.KnmaticsTiltCylExtMinMax[1]);

        /* Convert cylinder length lift to angle */
        float tiltAngle = LpsLookup2d(
                liftCylinderLength,
                tiltCylinderLength,
                linkage_table_cnfg.yLiftCylLen.data(),
                linkage_table_cnfg.xTiltCylLen.data(),
                linkage_table_cnfg.outTiltAngle.data(),
                linkage_table_cnfg.yLiftCylLen.size(),
                linkage_table_cnfg.xTiltCylLen.size());

        // Map the calibrated angle limits to nominal limits
        if (GetTiltCylCalStatus()) {
            float inMin = tiltCalNvmTbl_.tilt_full_dump_stop_angle;
            float inMax = tiltCalNvmTbl_.tilt_full_rack_stop_angle;
            float outMin = linkage_table_cnfg.KnmaticsTiltAngleMinMax[0];
            float outMax = linkage_table_cnfg.KnmaticsTiltAngleMinMax[1];
            float temp = (tiltAngle - inMin) / (inMax - inMin);
            tiltAngle = (temp * (outMax - outMin)) + outMin;
        }

        tiltPosition.angle = tiltAngle;

        tiltPosition.percentAngle = normalize(tiltAngle,
                linkage_table_cnfg.KnmaticsTiltAngleMinMax[0],
                linkage_table_cnfg.KnmaticsTiltAngleMinMax[1]);

        tiltPosition.bucketAngle = liftAngle + LpsLookup(tiltAngle,
                linkage_table_cnfg.inTiltAngle.data(),
                linkage_table_cnfg.outBktAngle.data(),
                linkage_table_cnfg.inTiltAngle.size());

        tiltPosition.status = LPS_STATUS_OK;
    }
    else {
        tiltPosition.percentAngle = 0;
        tiltPosition.cylinderLength = 0;
        tiltPosition.percentCylinderLength = 0;
        tiltPosition.bucketAngle = 0;
        tiltPosition.cylinderExtension = 0;
        tiltPosition.status = LPS_STATUS_BAD;
    }

    return tiltPosition;
}
