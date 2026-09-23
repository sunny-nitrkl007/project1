#include <chrono>
#include <chrono/convert.hpp>

#include <oel_pack.h>
#include <catdllib_fid_def.h>

#include <ais/task/Task.h>
#include <ais/log/Logger.h>

#include "rclcpp/rclcpp.hpp"
#include "ros2wrapper/RosOutputInterface.h"
#include <weigh_app_interfaces/msg/tipoff_model_test_points.hpp>

#ifdef __cplusplus
extern "C" {
#endif

#include <toa_wl00_model_if.h>
#include <toa_wl00_po.h>
#include <toa_wl00.h>


#ifdef __cplusplus
}
#endif

#include "TipoffAssist.h"

#define TIPOFF_ASSIST_RUN_UNIT_TEST 0 /* set to 1 to run unit test, 0 for production */

static void initTipoffAssistModelData(LpsSaMachineProperties_t const& machine_properties);

static void readCSV(TipoffAssistInputs& tipoff_inputs);

extern toa_wl00_catParameters_si_RAM_t toa_wl00_catParameters_si_RAM;

class TipoffModelTestPointsPublisher {
public:
    TipoffModelTestPointsPublisher(std::shared_ptr<rclcpp::Node> rosNode, const char* topic) :
            rosOut_(rosNode, topic) {}

    void publish(weigh_app_interfaces::msg::TipoffModelTestPoints const& txOut) {
        rosOut_.publish(txOut);
    }

private:
    ros2_wrapper::RosOutputInterface<weigh_app_interfaces::msg::TipoffModelTestPoints> rosOut_;
};

TipoffAssist::TipoffAssist():
        TipoffAssistOut(),
        TipoffModelTestPointsRosOut_(nullptr) {}

TipoffAssist::~TipoffAssist() {
    delete TipoffModelTestPointsRosOut_;
}

bool TipoffAssist::initialize(LpsSaMachineProperties_t const& machine_properties, std::shared_ptr<rclcpp::Node> rosNode) {
    uint32_t appNumber = machine_properties.internalMsn;
    AIS_LOG_INFO("TipoffAssist::initialize");

    // If we don't have an application number, we won't run.
    if (0 == appNumber) {
        AIS_LOG_WARN("Tip-off Assist not supported for this machine configuration.");
    }

    TipoffModelTestPointsRosOut_ = new TipoffModelTestPointsPublisher(
            rosNode, "tipoff_model_test_points");
    if (!TipoffModelTestPointsRosOut_) {
        AIS_LOG_WARN("TipoffModelTestPointsRosOut_ failed to initialize.");
    }

    initTipoffAssistModelData(machine_properties);

    /* Initialize config parameters pointer */
    toa_wl00_work.toa_wl00_M.toa_wl00_catParameters_si_RAM_p = &toa_wl00_catParameters_si_RAM;

    /* Initialize tipoff assist model */
    toa_wl00_po_init();

    return true;
}

TipoffAssistOutputs* TipoffAssist::update(TipoffAssistInputs& tipoff_inputs) {

    /* unit test with data from ppg */
    if (TIPOFF_ASSIST_RUN_UNIT_TEST) {
        readCSV(tipoff_inputs);
        AIS_LOG_INFO("Tipoff Assist in Unit Test Mode");
    }

    /* Update inputs */
    TOA_invalidate_outputs = tipoff_inputs.invalidate_outputs;
    TOA_lift_valve_cmd = tipoff_inputs.lift_valve_cmd;
    TOA_tilt_valve_cmd = tipoff_inputs.tilt_valve_cmd;
    TOA_lift_angle = tipoff_inputs.lift_angle;
    TOA_tilt_extension = tipoff_inputs.tilt_extension;
    TOA_lift_he_pressure = tipoff_inputs.lift_he_pressure;
    TOA_lift_re_pressure = tipoff_inputs.lift_re_pressure;
    TOA_tilt_he_pressure = tipoff_inputs.tilt_he_pressure;
    TOA_tilt_re_pressure = tipoff_inputs.tilt_re_pressure;
    TOA_eef_imu_accelX = tipoff_inputs.eef_imu_accelX;
    TOA_eef_imu_accelY = tipoff_inputs.eef_imu_accelY;
    TOA_eef_imu_accelZ = tipoff_inputs.eef_imu_accelZ;
    TOA_steering_angle = tipoff_inputs.steering_angle;
    TOA_tool_mass = tipoff_inputs.tool_mass;
    TOA_truck_target_wt = tipoff_inputs.truck_target_wt;
    TOA_truck_start_weight = tipoff_inputs.truck_start_weight;
    TOA_bucket_current_weight_accuracy = tipoff_inputs.bucket_current_weight_accuracy;
    TOA_bucket_current_weight  = tipoff_inputs.bucket_current_weight;
    TOA_tipoff_mode = tipoff_inputs.tipoff_mode;
    TOA_zero_offset = tipoff_inputs.zero_offset;
    TOA_simple_cal_factor = tipoff_inputs.simple_cal_factor;
    TOA_imu_pitch_cal = tipoff_inputs.mach_pitch_cal_offset;
    TOA_unlatch_trigger = tipoff_inputs.unlatch_trigger;
    TOA_bucket_angle = tipoff_inputs.bucket_angle;
    TOA_anchor_zero_offset = tipoff_inputs.anchor_zero_offset;
    TOA_anchor_factor = tipoff_inputs.anchor_factor;
    TOA_Pass_Count = tipoff_inputs.pass_count;
    TOA_Lift_Norm_Angle = tipoff_inputs.lift_norm_angle;
    TOA_Lift_Norm_Length = tipoff_inputs.lift_norm_length;
    TOA_Tilt_Norm_Angle = tipoff_inputs.tilt_norm_angle;
    TOA_Tilt_Norm_Length = tipoff_inputs.tilt_norm_length;
    TOA_Friction_Mu = tipoff_inputs.friction_mu;
    TOA_Friction_Offset = tipoff_inputs.friction_offset;

    /* Update tipoff assist model */
    toa_wl00_po_0();

    /* Update outputs */
    TipoffAssistOut.tilt_sensitivity_out = TOA_tilt_sensitivity_out;
    TipoffAssistOut.arbitrated_payload_norm_error_out = TOA_arbitrated_payload_norm_error_out;
    TipoffAssistOut.weigh_status_out = TOA_weigh_status_out;
    TipoffAssistOut.payload_norm_stdev_out = TOA_payload_norm_stdev_out;
    TipoffAssistOut.pcs_weight_accuracy_out = TOA_pcs_weight_accuracy_out;
    TipoffAssistOut.current_weight_norm_error_out = TOA_current_weight_norm_error_out;
    TipoffAssistOut.error_code_out = TOA_error_code_out;
    TipoffAssistOut.spill_rate_out = TOA_spill_rate_out;
    TipoffAssistOut.payload_send_to_CPM = TOA_payload_send_to_CPM;
    TipoffAssistOut.payload_status_send_to_CPM = TOA_payload_status_send_to_CPM;
    TipoffAssistOut.bucket_payload_target = TOA_bucket_payload_target;
    TipoffAssistOut.unsecured_payload_lower_bound_norm = TOA_unsecured_payload_lower_bound_norm;
    TipoffAssistOut.unsecured_payload_upper_bound_norm = TOA_unsecured_payload_upper_bound_norm;
    TipoffAssistOut.min_secure_bucket_angle = TOA_min_secure_bucket_angle;
    TipoffAssistOut.unsecured_PFW_status = TOA_unsecured_PFW_status;

    /* Publish Tipoff Model Test Points via ROS2 */
    if (TipoffModelTestPointsRosOut_ != nullptr) {
        weigh_app_interfaces::msg::TipoffModelTestPoints txOut;
        txOut.toa_pfw_sec_latch                   = toa_wl00_work.BlockIO.toa_pfwSecLatch;
        txOut.toa_pfw_sec_payload                 = toa_wl00_work.BlockIO.toa_pfwSecPayload;
        txOut.toa_pfw_sec_status                  = toa_wl00_work.BlockIO.toa_pfwSecStatus;
        txOut.toa_pfw_sec_st_dev                  = toa_wl00_work.BlockIO.toa_pfwSecStDev;
        txOut.toa_target_payload_final             = toa_wl00_work.BlockIO.toa_targetPayloadFinal;
        txOut.toa_target_payload_status            = toa_wl00_work.BlockIO.toa_targetPayloadStatus;
        txOut.toa_pfw_nl_notch_mean_est            = toa_wl00_work.BlockIO.toa_pfwNlNotchMeanEst;
        txOut.toa_pfw_nl_notch_st_dev_est          = toa_wl00_work.BlockIO.toa_pfwNlNotchStDevEst;
        txOut.toa_lw_lpf_post                      = toa_wl00_work.BlockIO.toa_lwLpfPost;
        txOut.toa_payload_adjusted                 = toa_wl00_work.BlockIO.toa_payloadAdjusted;
        txOut.toa_send_payload_arb                 = toa_wl00_work.BlockIO.toa_sendPayloadArb;
        txOut.toa_sfunc_in_grav_x                  = toa_wl00_work.BlockIO.toa_sfuncInGravX;
        txOut.toa_sfunc_in_grav_y                  = toa_wl00_work.BlockIO.toa_sfuncInGravY;
        txOut.toa_sfunc_in_lift_force              = toa_wl00_work.BlockIO.toa_sfuncInLiftForce;
        txOut.toa_sfunc_in_tilt_force              = toa_wl00_work.BlockIO.toa_sfuncInTiltForce;
        txOut.toa_sfunc_out_raw_mass_tonne         = toa_wl00_work.BlockIO.toa_sfuncOutRawMassTonne;
        txOut.toa_app_number                       = toa_wl00_catParameters_si_RAM.toa_appNumber;
        txOut.toa_lift_bore_dia                    = toa_wl00_catParameters_si_RAM.toa_liftBoreDia;
        txOut.toa_lift_rod_dia                     = toa_wl00_catParameters_si_RAM.toa_liftRodDia;
        txOut.toa_rated_payload                    = toa_wl00_catParameters_si_RAM.toa_ratedPayload;
        txOut.toa_tilt_bore_dia                    = toa_wl00_catParameters_si_RAM.toa_tiltBoreDia;
        txOut.toa_tilt_num_cyl                     = toa_wl00_catParameters_si_RAM.toa_tiltNumCyl;
        txOut.toa_tilt_rod_dia                     = toa_wl00_catParameters_si_RAM.toa_tiltRodDia;
        txOut.toa_tool_bc_length                   = toa_wl00_catParameters_si_RAM.toa_toolBcLength;
        txOut.toa_tool_bc_angle                    = toa_wl00_catParameters_si_RAM.toa_toolBcAngle;
        txOut.toa_payload_anc_adjusted             = toa_wl00_work.BlockIO.toa_payloadAncAdjusted;
        txOut.toa_payload_anc_zeroed               = toa_wl00_work.BlockIO.toa_payloadAncZeroed;
        txOut.toa_imu_cal_pitch_angle              = TOA_imu_pitch_cal;
        txOut.toa_pfw_unsec_status                 = toa_wl00_work.BlockIO.toa_pfwUnsecStatus;
        txOut.toa_pfw_unsec_bound_lower            = toa_wl00_work.BlockIO.toa_pfwUnsecBoundLower;
        txOut.toa_pfw_unsec_bound_upper            = toa_wl00_work.BlockIO.toa_pfwUnsecBoundUpper;
        txOut.toa_lw_spill_rate                    = toa_wl00_work.BlockIO.toa_lwSpillRate;
        txOut.toa_lw_status                        = toa_wl00_work.BlockIO.toa_lwStatus;
        txOut.toa_raw_dist                         = toa_wl00_work.BlockIO.toa_rawDist;
        txOut.toa_raw_payload                      = toa_wl00_work.BlockIO.toa_rawPayload;
        txOut.toa_payload_zeroed                   = toa_wl00_work.BlockIO.toa_payloadZeroed;
        txOut.toa_pfw_is_warm                      = toa_wl00_work.BlockIO.toa_pfwIsWarm;
        txOut.toa_pfw_sec_is_secure                = toa_wl00_work.BlockIO.toa_pfwSecIsSecure;
        txOut.toa_pfw_sec_is_no_sliding            = toa_wl00_work.BlockIO.toa_pfwSecIsNoSliding;
        txOut.toa_pfw_sec_is_no_collapsing         = toa_wl00_work.BlockIO.toa_pfwSecIsNoCollapsing;
        txOut.toa_pfw_sec_is_racked                = toa_wl00_work.BlockIO.toa_pfwSecIsRacked;
        txOut.toa_pfw_sec_min_bucket_ang           = toa_wl00_work.BlockIO.toa_pfwSecMinBucketAng;
        txOut.toa_pfw_mc_ok                        = toa_wl00_work.BlockIO.toa_pfwMcOk;
        txOut.toa_pfw_mc_maybe_stalled             = toa_wl00_work.BlockIO.toa_pfwMcMaybeStalled;
        txOut.toa_pfw_mc_maybe_rack_stall          = toa_wl00_work.BlockIO.toa_pfwMcMaybeRackStall;
        txOut.toa_pfw_mc_maybe_grounded            = toa_wl00_work.BlockIO.toa_pfwMcMaybeGrounded;
        txOut.toa_stat_payload_nl_notch_one_up     = toa_wl00_work.BlockIO.toa_statPayloadNlNotchOneUp;
        txOut.toa_stat_payload_nl_notch_one_low    = toa_wl00_work.BlockIO.toa_statPayloadNlNotchOneLow;
        txOut.toa_stat_payload_nl_notch_one_size   = toa_wl00_work.BlockIO.toa_statPayloadNlNotchOneSize;
        txOut.toa_stat_payload_nl_notch_two_up     = toa_wl00_work.BlockIO.toa_statPayloadNlNotchTwoUp;
        txOut.toa_stat_payload_nl_notch_two_low    = toa_wl00_work.BlockIO.toa_statPayloadNlNotchTwoLow;
        txOut.toa_stat_payload_nl_notch_two_size   = toa_wl00_work.BlockIO.toa_statPayloadNlNotchTwoSize;
        txOut.toa_stat_payload_nl_one_up           = toa_wl00_work.BlockIO.toa_statPayloadNlOneUp;
        txOut.toa_stat_payload_nl_one_low          = toa_wl00_work.BlockIO.toa_statPayloadNlOneLow;
        txOut.toa_stat_payload_nl_one_size         = toa_wl00_work.BlockIO.toa_statPayloadNlOneSize;
        txOut.toa_stat_payload_nl_two_up           = toa_wl00_work.BlockIO.toa_statPayloadNlTwoUp;
        txOut.toa_stat_payload_nl_two_low          = toa_wl00_work.BlockIO.toa_statPayloadNlTwoLow;
        txOut.toa_stat_payload_nl_two_size         = toa_wl00_work.BlockIO.toa_statPayloadNlTwoSize;
        txOut.toa_pfw_nl_st_dev_est                = toa_wl00_work.BlockIO.toa_pfwNlStDevEst;
        txOut.toa_pfw_nl_mean_est                  = toa_wl00_work.BlockIO.toa_pfwNlMeanEst;
        txOut.toa_pfw_payload_filt_final           = toa_wl00_work.BlockIO.toa_pfwPayloadFiltFinal;
        txOut.toa_pfw_payload_notch_filt_final     = toa_wl00_work.BlockIO.toa_pfwPayloadNotchFiltFinal;
        txOut.toa_pfw_payload_notch_post           = toa_wl00_work.BlockIO.toa_pfwPayloadNotchPost;
        txOut.toa_pfw_latch_invalidate             = toa_wl00_work.BlockIO.toa_pfwLatchInvalidate;
        txOut.toa_imu_raw_eef_accl_x               = toa_wl00_work.BlockIO.toa_imuRawEefAcclX;
        txOut.toa_imu_raw_eef_accl_y               = toa_wl00_work.BlockIO.toa_imuRawEefAcclY;
        txOut.toa_imu_raw_eef_accl_z               = toa_wl00_work.BlockIO.toa_imuRawEefAcclZ;
        txOut.toa_imu_neef_grav_x                  = toa_wl00_work.BlockIO.toa_imuNeefGravX;
        txOut.toa_imu_neef_grav_y                  = toa_wl00_work.BlockIO.toa_imuNeefGravY;
        txOut.toa_imu_neef_grav_z                  = toa_wl00_work.BlockIO.toa_imuNeefGravZ;
        txOut.toa_imu_neef_pitch                   = toa_wl00_work.BlockIO.toa_imuNeefPitch;
        txOut.toa_target_comp_margin               = toa_wl00_work.BlockIO.toa_targetCompMargin;
        txOut.toa_target_payload_post_comp         = toa_wl00_work.BlockIO.toa_targetPayloadPostComp;
        txOut.toa_target_payload_pre_comp          = toa_wl00_work.BlockIO.toa_targetPayloadPreComp;
        txOut.toa_stat_payload_secure_two_size     = toa_wl00_work.BlockIO.toa_statPayloadSecureTwoSize;
        txOut.toa_stat_payload_secure_one_upper    = toa_wl00_work.BlockIO.toa_statPayloadSecureOneUpper;
        txOut.toa_stat_payload_secure_one_lower    = toa_wl00_work.BlockIO.toa_statPayloadSecureOneLower;
        txOut.toa_stat_payload_secure_one_size     = toa_wl00_work.BlockIO.toa_statPayloadSecureOneSize;
        txOut.toa_stat_payload_secure_two_upper    = toa_wl00_work.BlockIO.toa_statPayloadSecureTwoUpper;
        txOut.toa_stat_payload_secure_two_lower    = toa_wl00_work.BlockIO.toa_statPayloadSecureTwoLower;
        txOut.toa_send_cpm_live_payload            = toa_wl00_work.BlockIO.toa_sendCpmLivePayload;
        TipoffModelTestPointsRosOut_->publish(txOut);
    }

    return (&TipoffAssistOut);
}

static void initTipoffAssistModelData(LpsSaMachineProperties_t const& machine_properties) {
    toa_wl00_catParameters_si_RAM.toa_appNumber = machine_properties.internalMsn;
    toa_wl00_catParameters_si_RAM.toa_liftBoreDia = machine_properties.liftBoreDiameter;
    toa_wl00_catParameters_si_RAM.toa_liftRodDia = machine_properties.liftRodDiameter;
    toa_wl00_catParameters_si_RAM.toa_ratedPayload = machine_properties.ratedPayload;
    toa_wl00_catParameters_si_RAM.toa_tiltBoreDia = machine_properties.tiltBoreDiameter;
    toa_wl00_catParameters_si_RAM.toa_tiltNumCyl = machine_properties.numOfTiltCylinders;
    toa_wl00_catParameters_si_RAM.toa_tiltRodDia = machine_properties.tiltRodDiameter;
    toa_wl00_catParameters_si_RAM.toa_toolBcLength = machine_properties.toolBcLength;
    toa_wl00_catParameters_si_RAM.toa_toolBcAngle = machine_properties.toolBcAngle;

    return;
}

#include "csvReader.h"

static void readCSV(TipoffAssistInputs& tipoff_inputs) {
    // Creating an object of CSVWriter
    static CSVReader reader("/opt/07312019_toa_weights1.csv");

    // Get the data from CSV File
    static std::vector<std::vector<std::string> > dataList = reader.getData();

    static int total_rows = dataList.size();
    static int index = 1;

    if (total_rows == 0)
    {
        AIS_LOG_ERROR("Attempt to run tipoff assist unit test with no data file records");
    }

    /* get row */
    if (index < total_rows) {
        std::vector<std::string> vec = dataList[index];
        index++;

        int i=0;
        TOA_weigh_status_out = std::stoi(vec[i++]);
        TOA_arbitrated_payload_norm_error_out = std::stof(vec[i++]);
        tipoff_inputs.bucket_current_weight = std::stof(vec[i++]);
        tipoff_inputs.bucket_current_weight_accuracy = std::stoi(vec[i++]);
        TOA_current_weight_norm_error_out = std::stof(vec[i++]);
        tipoff_inputs.eef_imu_accelX = std::stof(vec[i++]);
        tipoff_inputs.eef_imu_accelY = std::stof(vec[i++]);
        tipoff_inputs.eef_imu_accelZ = std::stof(vec[i++]);
        TOA_error_code_out = std::stof(vec[i++]);
        vec[i++];
        tipoff_inputs.invalidate_outputs = std::stoi(vec[i++]);
        tipoff_inputs.lift_angle = std::stof(vec[i++]);
        tipoff_inputs.lift_he_pressure = std::stof(vec[i++]);
        tipoff_inputs.lift_re_pressure = std::stof(vec[i++]);
        tipoff_inputs.lift_valve_cmd = std::stof(vec[i++]);
        TOA_payload_norm_stdev_out = std::stof(vec[i++]);
        TOA_payload_send_to_CPM = std::stof(vec[i++]);
        TOA_payload_status_send_to_CPM = std::stoi(vec[i++]);
        TOA_pcs_weight_accuracy_out = std::stoi(vec[i++]);
        TOA_spill_rate_out = std::stof(vec[i++]);
        tipoff_inputs.steering_angle = std::stof(vec[i++]);
        tipoff_inputs.tilt_extension = std::stof(vec[i++]);
        tipoff_inputs.tilt_he_pressure = std::stof(vec[i++]);
        TOA_tilt_pressure_out = std::stof(vec[i++]);
        tipoff_inputs.tilt_re_pressure = std::stof(vec[i++]);
        TOA_tilt_sensitivity_out = std::stof(vec[i++]);
        tipoff_inputs.tilt_valve_cmd = std::stof(vec[i++]);
        tipoff_inputs.tipoff_mode = std::stoi(vec[i++]);
        vec[i++];
        tipoff_inputs.tool_mass = std::stof(vec[i++]);
        tipoff_inputs.truck_start_weight = std::stof(vec[i++]);
        tipoff_inputs.truck_target_wt = std::stof(vec[i++]);
    }
    else
        tipoff_inputs.invalidate_outputs = 1;
}
