/*******************************************************************************
** COPYRIGHT (C) 2016-2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsSaCalibration.cpp
DESCRIPTION:This file provides the update routines for the application software
            for LPS library.
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#ifndef  _LPS_SA_WEIGHAPP_H_
#include "LpsSaWeighApp.h"
#endif

#include <iostream>
#include <algorithm>

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

float_32  LpsWeighPtrDumpWtBuffer[WEIGH_LIB_DUMP_BUFF_SIZE];

unsigned_32 cal_iterm[(CAL_LAST_ITERM_BIT>>5)+1];   /* Default Cal Iterm */

/******************************************************************************
FUNCTION NAME: LpsSaLoadCalibrationTbl
DESCRIPTION: This function reads the calibration table from the ruby file
PARAMETER DESCRIPTION: none
RETURN VALUE: none
*******************************************************************************/
void LpsSaWeighApp::LpsSaLoadDefaultCalibrationTbl(void)
{
    /*
     * Load the Default Calibration Tables
     *  - Before this, payloadCalNvmTbl_ has been default initialized.
     */
    payloadCalNvmTbl_.data.CalStatus = 0;

    // --- WM-01: DefaultCalConfig ---
    // No current robot sets this section (0/122 variants). Guard matches original
    // getSection() failure path: log error, leave structs at constructor defaults.
    declare_parameter<bool>("default_cal_config.config_present", false);
    if (!get_parameter("default_cal_config.config_present").as_bool()) {
        AIS_LOG_ERROR("DefaultCalConfig section not found");
    }
    else {
        // Helper: declare double param, read, cast to float. Sentinel: 0.0 = not provided.
        auto getDccFloat = [&](const std::string& key) -> float {
            declare_parameter<double>(key, 0.0);
            return static_cast<float>(get_parameter(key).as_double());
        };
        // Helper: declare double_array param, read into float vector. Returns false if absent.
        auto getDccArray = [&](const std::string& key, std::vector<float>& dst) -> bool {
            declare_parameter<std::vector<double>>(key, std::vector<double>{});
            const auto v = get_parameter(key).as_double_array();
            if (v.size() < static_cast<size_t>(LPS_CAL_CURVE_FIT_NUM_POINTS)) {
                return false;
            }
            dst.assign(v.begin(), v.end());
            return true;
        };

        bool calibratedByDefault = false;
        { // Read cal status: sentinel -1; LPS_WEIGH_SYSTEM_CALIBRATED=0 enables cal flags
            declare_parameter<int>("default_cal_config.cal_stat", -1);
            const int raw = get_parameter("default_cal_config.cal_stat").as_int();
            if (LPS_WEIGH_SYSTEM_CALIBRATED == static_cast<LpsWeighCalStatus_t>(raw)) {
                calibratedByDefault = true;
            }
        }

        { // Load lift sensor default calibration
            // Original writes the value unconditionally (cfg.get side-effect) but only
            // sets lift_cal_stat if both keys present. Mirror that: write each independently,
            // track allThere for the cal-stat gate.
            const float raise = getDccFloat("default_cal_config.lift_cyl_max_dc");
            const float lower = getDccFloat("default_cal_config.lift_cyl_min_dc");
            const bool raisePresent = (raise != 0.f);
            const bool lowerPresent = (lower != 0.f);
            if (raisePresent) { liftCalNvmTbl_.lift_full_raise_dc = raise; }
            if (lowerPresent) { liftCalNvmTbl_.lift_full_lower_dc = lower; }
            if (raisePresent && lowerPresent && calibratedByDefault) {
                liftCalNvmTbl_.lift_cal_stat = CAL_LIFT_LINKAGE_MASK;
            }
        }

        if (TILT_SENSOR_TYPE_ROTARY == linkage_table_cnfg.tiltSensorType)
        { // Load tilt sensor default calibration (rotary robots only)
            const float rack = getDccFloat("default_cal_config.tilt_cyl_max_dc");
            const float dump = getDccFloat("default_cal_config.tilt_cyl_min_dc");
            const bool rackPresent = (rack != 0.f);
            const bool dumpPresent = (dump != 0.f);
            if (rackPresent) { tiltCalNvmTbl_.tilt_full_rack_dc = rack; }
            if (dumpPresent) { tiltCalNvmTbl_.tilt_full_dump_dc = dump; }
            if (rackPresent && dumpPresent && calibratedByDefault) {
                tiltCalNvmTbl_.tilt_sensor_type = TILT_SENSOR_TYPE_ROTARY;
                tiltCalNvmTbl_.tilt_cal_stat = CAL_TILT_LINKAGE_MASK;
            }
        }

        { // Load empty bucket payload calibration tables
            bool allThere = true;
            std::vector<float> arr;

            arr.clear();
            allThere &= getDccArray("default_cal_config.slow_raise_empty_bkt_lift_ht", arr);
            if (!arr.empty()) {
                arr.resize(LPS_CAL_CURVE_FIT_NUM_POINTS);
                std::copy(arr.begin(), arr.end(), payloadCalNvmTbl_.data.SlowRaiseEmptyBktLiftHt);
            }

            arr.clear();
            allThere &= getDccArray("default_cal_config.slow_raise_empty_bkt_lift_pres", arr);
            if (!arr.empty()) {
                arr.resize(LPS_CAL_CURVE_FIT_NUM_POINTS);
                std::copy(arr.begin(), arr.end(), payloadCalNvmTbl_.data.SlowRaiseEmptyBktLiftPres);
            }

            arr.clear();
            allThere &= getDccArray("default_cal_config.slow_lower_empty_bkt_lift_ht", arr);
            if (!arr.empty()) {
                arr.resize(LPS_CAL_CURVE_FIT_NUM_POINTS);
                std::copy(arr.begin(), arr.end(), payloadCalNvmTbl_.data.SlowLowerEmptyBktLiftHt);
            }

            arr.clear();
            allThere &= getDccArray("default_cal_config.slow_lower_empty_bkt_lift_pres", arr);
            if (!arr.empty()) {
                arr.resize(LPS_CAL_CURVE_FIT_NUM_POINTS);
                std::copy(arr.begin(), arr.end(), payloadCalNvmTbl_.data.SlowLowerEmptyBktLiftPres);
            }

            const float fastRaiseEmpty = getDccFloat("default_cal_config.fast_raise_empty_bkt_delta_pres");
            const float emptySlowSpd   = getDccFloat("default_cal_config.empty_bkt_slow_raise_spd");
            const float emptyFastSpd   = getDccFloat("default_cal_config.empty_bkt_fast_raise_spd");
            if (fastRaiseEmpty != 0.f) { payloadCalNvmTbl_.data.FastRaiseEmptyBktDeltaPres = fastRaiseEmpty; } else { allThere = false; }
            if (emptySlowSpd   != 0.f) { payloadCalNvmTbl_.data.EmptyBktSlowRaiseSpd       = emptySlowSpd;   } else { allThere = false; }
            if (emptyFastSpd   != 0.f) { payloadCalNvmTbl_.data.EmptyBktFastRaiseSpd       = emptyFastSpd;   } else { allThere = false; }

            if (allThere && calibratedByDefault) {
                payloadCalNvmTbl_.data.CalStatus |= CAL_EMPTY_BKT_CURVE_MASK;
            }
        }

        { // Load full bucket payload calibration tables
            bool allThere = true;
            std::vector<float> arr;

            arr.clear();
            allThere &= getDccArray("default_cal_config.slow_raise_full_bkt_lift_ht", arr);
            if (!arr.empty()) {
                arr.resize(LPS_CAL_CURVE_FIT_NUM_POINTS);
                std::copy(arr.begin(), arr.end(), payloadCalNvmTbl_.data.SlowRaiseFullBktLiftHt);
            }

            arr.clear();
            allThere &= getDccArray("default_cal_config.slow_raise_full_bkt_lift_pres", arr);
            if (!arr.empty()) {
                arr.resize(LPS_CAL_CURVE_FIT_NUM_POINTS);
                std::copy(arr.begin(), arr.end(), payloadCalNvmTbl_.data.SlowRaiseFullBktLiftPres);
            }

            arr.clear();
            allThere &= getDccArray("default_cal_config.slow_lower_full_bkt_lift_ht", arr);
            if (!arr.empty()) {
                arr.resize(LPS_CAL_CURVE_FIT_NUM_POINTS);
                std::copy(arr.begin(), arr.end(), payloadCalNvmTbl_.data.SlowLowerFullBktLiftHt);
            }

            arr.clear();
            allThere &= getDccArray("default_cal_config.slow_lower_full_bkt_lift_pres", arr);
            if (!arr.empty()) {
                arr.resize(LPS_CAL_CURVE_FIT_NUM_POINTS);
                std::copy(arr.begin(), arr.end(), payloadCalNvmTbl_.data.SlowLowerFullBktLiftPres);
            }

            const float fastRaiseFull = getDccFloat("default_cal_config.fast_raise_full_bkt_delta_pres");
            const float fullSlowSpd   = getDccFloat("default_cal_config.full_bkt_slow_raise_spd");
            const float fullFastSpd   = getDccFloat("default_cal_config.full_bkt_fast_raise_spd");
            if (fastRaiseFull != 0.f) { payloadCalNvmTbl_.data.FastRaiseFullBktDeltaPres = fastRaiseFull; } else { allThere = false; }
            if (fullSlowSpd   != 0.f) { payloadCalNvmTbl_.data.FullBktSlowRaiseSpd       = fullSlowSpd;   } else { allThere = false; }
            if (fullFastSpd   != 0.f) { payloadCalNvmTbl_.data.FullBktFastRaiseSpd       = fullFastSpd;   } else { allThere = false; }

            if (allThere && calibratedByDefault) {
                payloadCalNvmTbl_.data.CalStatus |= CAL_FULL_BKT_CURVE_MASK;
            }
        }

        { // Load default calibration weight
            const float calwt = getDccFloat("default_cal_config.calwt");
            if (calwt != 0.f) {
                payloadCalNvmTbl_.data.CalWeight = calwt;
                if (calibratedByDefault) {
                    payloadCalNvmTbl_.data.CalStatus |= CAL_BKT_WT_MASK;
                }
            }
        }
    }

    // If empty and full curves are done, then velocity compensation is done.
    if ((0 != (payloadCalNvmTbl_.data.CalStatus & CAL_EMPTY_BKT_CURVE_MASK)) &&
            (0 != (payloadCalNvmTbl_.data.CalStatus & CAL_FULL_BKT_CURVE_MASK))) {
        payloadCalNvmTbl_.data.CalStatus |= CAL_VELCAL;
    }

    AIS_LOG_INFO("Default calibration status %X", payloadCalNvmTbl_.data.CalStatus);

    // Simple Cal Factor is always defaulted to 0
    payloadCalNvmTbl_.data.CalAdjust = 0.f;

    // Zero is always defaulted to 0
    payloadCalNvmTbl_.data.ZeroWeight = 0.f;
}
/******************************************************************************
FUNCTION NAME:LpsSaInitWeighTbl
DESCRIPTION:
PARAMETER DESCRIPTION:
RETURN VALUE:
*******************************************************************************/
bool LpsSaWeighApp::LpsSaInitWeighTbl()
{
    bool everythingOk = true;
    LpsInitTbl_t& weighInitTbl = LpsSaInitTbl.WeighInitTbl;
    LpsMachSpecificCfg_t& machSpecificCfg = weighInitTbl.MachSpecificCfg;

    // Weighing library set to 20 msec execution rate
    getTaskConfig().get("CPMExecRate", weighInitTbl.ExecRate);
    declare_parameter<double>("cpm_exec_rate", static_cast<double>(weighInitTbl.ExecRate));
    weighInitTbl.ExecRate = static_cast<decltype(weighInitTbl.ExecRate)>(get_parameter("cpm_exec_rate").as_double());
    AIS_LOG_INFO("CPMExecRate %f", weighInitTbl.ExecRate);

    // Load the default calibration table from the ruby file
    LpsSaLoadDefaultCalibrationTbl();

    // Copying default calibration table into the weigh init table.
    copyCalNVMToWeighInitTable(machSpecificCfg.CalibTbl);

    // --- WM-02: MachineSpecificConfig (weighing params) ---
    // Guard: if the robot YAML was not loaded, weighing.config_present will be absent/false.
    // This matches the original behaviour where a missing MachineSpecificConfig section
    // caused everythingOk=false and skipped all subsequent reads.
    declare_parameter<bool>("weighing.config_present", false);
    if (!get_parameter("weighing.config_present").as_bool()) {
        AIS_LOG_ERROR("MachineSpecificConfig (weighing params) not found — Robot YAML not loaded?");
        everythingOk = false;
        return everythingOk;
    }

    // Helper: declare double param, read, cast to float
    auto getFloatParam = [&](const std::string& key, double def) -> float {
        declare_parameter<double>(key, def);
        return static_cast<float>(get_parameter(key).as_double());
    };
    // Helper: declare int param, read, return int
    auto getIntParam = [&](const std::string& key, int def) -> int {
        declare_parameter<int>(key, def);
        return get_parameter(key).as_int();
    };
    // Helper for float arrays (double_array → float vector)
    auto getFloatArrayWm02 = [&](const std::string& key, std::vector<float>& dst) -> bool {
        declare_parameter<std::vector<double>>(key, std::vector<double>{});
        const auto v = get_parameter(key).as_double_array();
        dst.assign(v.begin(), v.end());
        return !dst.empty();
    };

    // Group 1: Hydraulic oil type (optional, default LPS_OIL_TYPE_SAE_10W=0)
    {
        const int raw = getIntParam("weighing.hyd_oil_type",
                                    static_cast<int>(LPS_OIL_TYPE_SAE_10W));
        machSpecificCfg.HydOilType = static_cast<LpsHydOilType_t>(raw);
    }

    // Group 2: Hydraulic line loss coefficients (optional, default 0 = no temp compensation)
    machSpecificCfg.HydPressLossCoeff.LiftCylHeLineLoss2ndOrdrCoeff =
        getFloatParam("weighing.lift_cyl_he_line_loss_2nd_ordr_coeff", 0.0);
    machSpecificCfg.HydPressLossCoeff.LiftCylHeLineLoss1stOrdrCoeff =
        getFloatParam("weighing.lift_cyl_he_line_loss_1st_ordr_coeff", 0.0);
    machSpecificCfg.HydPressLossCoeff.LiftCylReLineLoss2ndOrdrCoeff =
        getFloatParam("weighing.lift_cyl_re_line_loss_2nd_ordr_coeff", 0.0);
    machSpecificCfg.HydPressLossCoeff.LiftCylReLineLoss1stOrdrCoeff =
        getFloatParam("weighing.lift_cyl_re_line_loss_1st_ordr_coeff", 0.0);

    // Group 3: Weigh range config (optional, struct already default-initialised in header)
    WeighRangeConfig.defaultStartOfWeighRange =
        getFloatParam("weighing.start_of_weigh", static_cast<double>(DEFAULT_WEIGH_RANGE_START));
    WeighRangeConfig.defaultEndOfWeighRange =
        getFloatParam("weighing.end_of_weigh", static_cast<double>(DEFAULT_WEIGH_RANGE_END));
    WeighRangeConfig.minimumWeighRangeSize =
        getFloatParam("weighing.weigh_range_min", static_cast<double>(DEFAULT_MIN_WEIGH_RANGE_SIZE));
    WeighRangeConfig.minimumWeighRangeStart =
        getFloatParam("weighing.min_weigh_range_start", static_cast<double>(DEFAULT_MIN_WEIGH_RANGE_START));
    WeighRangeConfig.maximumWeighRangeEnd =
        getFloatParam("weighing.max_weigh_range_end", static_cast<double>(DEFAULT_MAX_WEIGH_RANGE_END));

    // Group 4: LLW (Low-Lift-Weigh) config (all optional)
    machSpecificCfg.LlwTbl.FilterFactorMean      = getFloatParam("weighing.filter_factor_mean",      0.0);
    machSpecificCfg.LlwTbl.FilterFactorVariance   = getFloatParam("weighing.filter_factor_variance",  0.0);
    machSpecificCfg.LlwTbl.ErrorBand              = getFloatParam("weighing.error_band",              0.0);
    machSpecificCfg.LlwTbl.MinimumConfidenceTime  = getFloatParam("weighing.minimum_confidence_time", 0.0);
    machSpecificCfg.LlwTbl.AutoWeighRangeConfThr  = getFloatParam("weighing.auto_weigh_range_conf_thr",0.0);
    machSpecificCfg.LlwTbl.AutoWeighMinLiftHt     = getFloatParam("weighing.auto_weigh_min_lift_ht",  0.0);
    machSpecificCfg.LlwTbl.WtCf                  = getFloatParam("weighing.wt_cf",                   0.0);
    machSpecificCfg.LlwTbl.StageOneCf             = getFloatParam("weighing.stage_one_cf",            0.0);
    machSpecificCfg.LlwTbl.StageTwoCf             = getFloatParam("weighing.stage_two_cf",            0.0);
    machSpecificCfg.LlwTbl.StageThreeCf           = getFloatParam("weighing.stage_three_cf",          0.0);
    machSpecificCfg.LlwTbl.DampingRate            = getFloatParam("weighing.damping_rate",            0.0);

    { // WtLpsOptional + WtLpsOptionalCf — both must be present to apply (paired)
        // Default false for WtLpsOptional; 0.0 is sentinel for "not provided" for WtLpsOptionalCf.
        declare_parameter<bool>("weighing.wt_lps_optional", false);
        declare_parameter<double>("weighing.wt_lps_optional_cf", 0.0);
        const bool wtLpsOpt  = get_parameter("weighing.wt_lps_optional").as_bool();
        const float wtLpsCf  = static_cast<float>(get_parameter("weighing.wt_lps_optional_cf").as_double());
        if (wtLpsOpt && wtLpsCf != 0.f) {
            // Both present — apply the pair (mirrors original: both rubyCfg.get() must succeed)
            machSpecificCfg.LlwTbl.WtLpsOptional  = wtLpsOpt;
            machSpecificCfg.LlwTbl.WtLpsOptionalCf = wtLpsCf;
        }
        else {
            machSpecificCfg.LlwTbl.WtLpsOptional = false;
        }
    }

    { // LiftAngVelFilterCf — computed default: max(StageOneCf, StageTwoCf, StageThreeCf)
        // 0.0 sentinel means "not provided" — safe as no robot has filter CF of exactly 0.
        declare_parameter<double>("weighing.lift_ang_vel_filter_cf", 0.0);
        const float cf = static_cast<float>(get_parameter("weighing.lift_ang_vel_filter_cf").as_double());
        if (cf == 0.f) {
            machSpecificCfg.LiftVelFilterCf = std::max(machSpecificCfg.LlwTbl.StageOneCf,
                std::max(machSpecificCfg.LlwTbl.StageTwoCf, machSpecificCfg.LlwTbl.StageThreeCf));
        }
        else {
            machSpecificCfg.LiftVelFilterCf = cf;
        }
    }

    // Group 5: Zero weight config
    {
        // ZeroBktWtAccuracyLimit (optional, default LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_HIGH=3)
        const int raw = getIntParam("weighing.zero_bkt_wt_accuracy_limit",
                                    static_cast<int>(LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_HIGH));
        machSpecificCfg.ZeroBktWtAccuracyLimit = static_cast<LpsWeighBktWtAccuracy_t>(raw);
    }
    machSpecificCfg.ZeroRangeLimit              = getFloatParam("weighing.zero_range_limit",                0.0);
    machSpecificCfg.ZeroAdjInitTimeInterval     = static_cast<unsigned_32>(
        getIntParam("weighing.zero_adj_init_time_interval",  0));
    machSpecificCfg.ZeroAdjAutoTimeInterval     = static_cast<unsigned_32>(
        getIntParam("weighing.zero_adj_auto_time_interval",  0));
    { // ZeroAdjAutoTimeIntervalFast — computed default: = ZeroAdjAutoTimeInterval when absent
        // 0 sentinel: safe since no robot configures a 0-second fast interval.
        const unsigned_32 fast = static_cast<unsigned_32>(
            getIntParam("weighing.zero_adj_auto_time_interval_fast", 0));
        machSpecificCfg.ZeroAdjAutoTimeIntervalFast = (fast == 0u)
            ? machSpecificCfg.ZeroAdjAutoTimeInterval
            : fast;
    }
    machSpecificCfg.ZeroAdjOilTempWarnThreshold = getFloatParam("weighing.zero_adj_oil_temp_warn_threshold", 0.0);
    { // ZeroAdjOilTempDelta (optional, default LPS_OIL_TEMP_DELTA=10.0)
        declare_parameter<double>("weighing.zero_adj_oil_temp_delta", 10.0); // LPS_OIL_TEMP_DELTA
        machSpecificCfg.ZeroAdjOilTempDelta = static_cast<float>(
            get_parameter("weighing.zero_adj_oil_temp_delta").as_double());
    }

    // Group 6: Tilt compensation (optional)
    machSpecificCfg.TiltComp.TiltCompGainScalar     = getFloatParam("weighing.tilt_comp_gain_scalar",      0.0);
    machSpecificCfg.TiltComp.TiltCompEmptyBktWtGain = getFloatParam("weighing.tilt_comp_empty_bkt_wt_gain",0.0);
    machSpecificCfg.TiltComp.TiltCompMaxGain         = getFloatParam("weighing.tilt_comp_max_gain",         0.0);

    if (!getFloatArrayWm02("weighing.lift_cyl_ext_pct_axis", CalibTblRuby.lift_cyl_ext_pct_axis)) {
        AIS_LOG_ERROR("LiftCylExtPctAxis read fail.");
    }
    if (!getFloatArrayWm02("weighing.tilt_comp_gain_data", CalibTblRuby.tilt_comp_gain_data)) {
        AIS_LOG_ERROR("TiltCompGainData read fail.");
    }
    if (!getFloatArrayWm02("weighing.tilt_cyl_ext_pct_axis", CalibTblRuby.tilt_cyl_ext_pct_axis)) {
        AIS_LOG_ERROR("TiltCylExtPctAxis read fail.");
    }

    // TiltMap pointers — CalibTblRuby is a class member so .data() lifetime = node lifetime
    machSpecificCfg.TiltMap.NumColumns = CalibTblRuby.lift_cyl_ext_pct_axis.size();
    machSpecificCfg.TiltMap.ColumnAxis = CalibTblRuby.lift_cyl_ext_pct_axis.data();
    machSpecificCfg.TiltMap.NumRows    = CalibTblRuby.tilt_cyl_ext_pct_axis.size();
    machSpecificCfg.TiltMap.RowAxis    = CalibTblRuby.tilt_cyl_ext_pct_axis.data();
    machSpecificCfg.TiltMap.Data       = CalibTblRuby.tilt_comp_gain_data.data();

    // TipoffPitchCalOffset (optional, default 0)
    cnfg_.tipoffPitchCalOffset = getFloatParam("weighing.tipoff_pitch_cal_offset", 0.0);

    // Group 7: Dig / Dump / LiveWeigh config (all optional)
    machSpecificCfg.DigConfig.DigTargetWt           = getFloatParam("weighing.dig_target_wt",            0.0);
    machSpecificCfg.DigConfig.DigDurationMaxLimit    = getFloatParam("weighing.dig_duration_max_limit",   0.0);
    machSpecificCfg.DigConfig.DigDurationMinLimit    = getFloatParam("weighing.dig_duration_min_limit",   0.0);
    machSpecificCfg.DigConfig.DigStartLimit          = getFloatParam("weighing.dig_start_limit",          0.0);
    machSpecificCfg.DigConfig.DigEndLimit            = getFloatParam("weighing.dig_end_limit",            0.0);
    machSpecificCfg.DigConfig.LiftLowerVelocityLimit = getFloatParam("weighing.lift_lower_velocity_limit",0.0);

    machSpecificCfg.DumpConfig.TiltCylExtThreshold       = getFloatParam("weighing.tilt_cyl_ext_threshold",        0.0);
    machSpecificCfg.DumpConfig.TiltCylExtThresholdStrict  = getFloatParam("weighing.tilt_cyl_ext_threshold_strict", 0.0);
    machSpecificCfg.DumpConfig.FullDumpBktAngleThreshold  = getFloatParam("weighing.full_dump_bkt_angle_threshold",  0.0);
    machSpecificCfg.DumpConfig.PartDumpBktAngleThreshold  = getFloatParam("weighing.part_dump_bkt_angle_threshold",  0.0);
    machSpecificCfg.DumpConfig.FullRackBktAngleThreshold  = getFloatParam("weighing.full_rack_bkt_angle_threshold",  0.0);
    machSpecificCfg.DumpConfig.TiltAngleABCThreshold      = getFloatParam("weighing.tilt_angle_abc_threshold",       0.0);

    machSpecificCfg.LiveWeighConfig.FastFiltWtCf = getFloatParam("weighing.fast_filt_wt_cf", 0.0);
    machSpecificCfg.LiveWeighConfig.SlowFiltWtCf = getFloatParam("weighing.slow_filt_wt_cf", 0.0);

    // Group 8: QR calibration thresholds (optional, explicit defaults)
    {
        declare_parameter<int>("weighing.qr_min_hyd_oil_temp_celsius", 40);
        WeighPidTbl.QR_HydOilTempMin_C = static_cast<int16_t>(
            get_parameter("weighing.qr_min_hyd_oil_temp_celsius").as_int());
        AIS_LOG_INFO("HydOilTempMin: %d", WeighPidTbl.QR_HydOilTempMin_C);
    }
    {
        declare_parameter<int>("weighing.qr_min_lift_cyl_velocity_mm_sec", -25);
        WeighPidTbl.QR_LiftCylVelMin_mm_sec = static_cast<int16_t>(
            get_parameter("weighing.qr_min_lift_cyl_velocity_mm_sec").as_int());
        AIS_LOG_INFO("LiftCylVelMin: %d", WeighPidTbl.QR_LiftCylVelMin_mm_sec);
    }
    {
        declare_parameter<int>("weighing.qr_max_lift_cyl_velocity_mm_sec", 25);
        WeighPidTbl.QR_LiftCylVelMax_mm_sec = static_cast<int16_t>(
            get_parameter("weighing.qr_max_lift_cyl_velocity_mm_sec").as_int());
        AIS_LOG_INFO("LiftCylVelCalValue: %d", WeighPidTbl.QR_LiftCylVelMax_mm_sec);
    }

    // FilterTauDelay (optional, uint8_t, default 0)
    {
        declare_parameter<int>("weighing.filter_tau_delay", 0);
        LpsSaWeighInfoTbl.FilterTauDelay = static_cast<unsigned char>(
            get_parameter("weighing.filter_tau_delay").as_int());
    }

    // PwmcycleRate_hz (optional, float, default 0)
    LpsSaWeighInfoTbl.PwmcycleRate = getFloatParam("weighing.pwm_cycle_rate_hz", 0.0);

    weighInitTbl.DumpWtBuffer.PtrDumpWtBuffer = LpsWeighPtrDumpWtBuffer;
    weighInitTbl.DumpWtBuffer.bufferSize = WEIGH_LIB_DUMP_BUFF_SIZE;

    if (!LpsSaLoadKinematicsTbl()) {
        AIS_LOG_ERROR("Failed to load Kinematics.");
        everythingOk = false;
    }

    { // Read the Machine Type — WM-05
        declare_parameter<std::string>("machine_type.internal_msn", "NOT00000");
        machineMSN = get_parameter("machine_type.internal_msn").as_string();

        // raise diagnostic if machine model is NOT_SET (default)
        // Also set everythingOk=false to match original behaviour where a missing
        // MachineType section caused an explicit everythingOk=false.
        if ("NOT00000" == machineMSN) {
            MachineModelNotSetOut setDiag;
            setAutonomyCondition(setDiag);
            LpsSaWeighInfoTbl.DiagState[ACDDiagPopUp::MACHINE_MODEL_NOT_SET] = true;
            LpsSaWeighInfoTbl.MachineModelNotSet = TRUE;
            everythingOk = false;
        }
        else {
            // Machine model has been selected
            clearAutonomyCondition<MachineModelNotSetOut>();
            LpsSaWeighInfoTbl.DiagState[ACDDiagPopUp::MACHINE_MODEL_NOT_SET] = false;
            LpsSaWeighInfoTbl.MachineModelNotSet = FALSE;
        }
    }

    if (!LpsSaLoadMachineProperties()) {
        AIS_LOG_ERROR("Failed to load Machine Properties.");
        everythingOk = false;
    }

    machSpecificCfg.NoOfLiftCyls = machineProperties.numOfLiftCylinders;
    machSpecificCfg.LiftCylBoreDia = machineProperties.liftBoreDiameter;
    machSpecificCfg.LiftCylRodDia = machineProperties.liftRodDiameter;
    machSpecificCfg.LiftArmAbLength = machineProperties.liftArmAbLength;
    machSpecificCfg.KgPerLiftKpaAtMidExtension = machineProperties.kgPerLiftKpaAtMidExtension;
    machSpecificCfg.LiftKpaNoBucketMidExtension = machineProperties.liftKpaNoBucketMidExtension;
    machSpecificCfg.AccelCompSupported = machineProperties.accelCompSupported;
    machSpecificCfg.IMUCompSupported = machineProperties.imuCompSupported;
    machSpecificCfg.IMUCompLoadCGAngleOffset = machineProperties.imuCompLoadCGAngleOffset;

    if (linkage_table_cnfg.outLiftCylLen.size() == linkage_table_cnfg.inLiftAngle.size()) {
        // Table sizes match, good
        machSpecificCfg.LiftLinkageMap.angleDeg = linkage_table_cnfg.inLiftAngle.data();
        machSpecificCfg.LiftLinkageMap.cylLenMm = linkage_table_cnfg.outLiftCylLen.data();
        machSpecificCfg.LiftLinkageMap.numPoints = linkage_table_cnfg.inLiftAngle.size();
    }
    else {
        // Table sizes don't match.
        machSpecificCfg.LiftLinkageMap.angleDeg = nullptr;
        machSpecificCfg.LiftLinkageMap.cylLenMm = nullptr;
        machSpecificCfg.LiftLinkageMap.numPoints = 0;
    }

    if (linkage_table_cnfg.outLiftAngleGain.size() == linkage_table_cnfg.inLiftAngle.size()) {
        // Table sizes match, good
        machSpecificCfg.LiftLinkageMap.gainDegPerMm = linkage_table_cnfg.outLiftAngleGain.data();
    }
    else {
        // Table sizes don't match.
        machSpecificCfg.LiftLinkageMap.gainDegPerMm = nullptr;
    }

    if (linkage_table_cnfg.outLiftPresNoBucket.size() == linkage_table_cnfg.inLiftAngle.size()) {
        // Table sizes match, good
        machSpecificCfg.LiftLinkageMap.presNoBucketkPa = linkage_table_cnfg.outLiftPresNoBucket.data();
    }
    else {
        // Table sizes don't match.
        machSpecificCfg.LiftLinkageMap.presNoBucketkPa = nullptr;
    }

    if ((linkage_table_cnfg.outLiftAngleAccel.size() == linkage_table_cnfg.inLiftAngle.size()) &&
            (linkage_table_cnfg.liftRefVel > 0.f)) {
        // Table sizes match, good
        machSpecificCfg.LiftLinkageMap.accelDegPerSec2 = linkage_table_cnfg.outLiftAngleAccel.data();
        machSpecificCfg.LiftLinkageMap.refVelMmPerSec = linkage_table_cnfg.liftRefVel;
    }
    else {
        // Table sizes don't match.
        machSpecificCfg.LiftLinkageMap.accelDegPerSec2 = nullptr;
        machSpecificCfg.LiftLinkageMap.refVelMmPerSec = 0.f;
    }

    return everythingOk;
}
