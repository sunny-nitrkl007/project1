///////////////////////////////////////////////////////////////////////////////
///
/// @file      XcpScsInputsDb.h
/// @brief     Structure containing all data coming in (former SCS inputs, now
///            ROS2 topics) that needs to be pushed into the XCP measurement DB.
///
///            No AIS dependency: every input is the ROS2 message published by
///            its producer (ROS2 apps directly, AIS apps through
///            ScsToRos2Bridge, which owns every AIS <-> ROS2 conversion).
///
///////////////////////////////////////////////////////////////////////////////
#ifndef XCPSCSINPUTS_H_
#define XCPSCSINPUTS_H_

#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <deque>
#include <map>
#include <string>
#include <vector>

#include <rcutils/logging.h>

#include <cpm_common_interfaces/msg/autonomy_condition_diagnostics_tx_channel.hpp>
#include <cpm_common_interfaces/msg/cycle_seg_tx_channel.hpp>
#include <cpm_common_interfaces/msg/lps_sa_job_mgr_reqst_channel.hpp>
#include <cpm_common_interfaces/msg/lps_sa_ui_bem_sim_state_interface.hpp>
#include <cpm_common_interfaces/msg/lps_sa_ui_display_state_interface.hpp>
#include <cpm_common_interfaces/msg/lps_sa_weigh_reqst_channel.hpp>
#include <cpm_common_interfaces/msg/lps_sa_weigh_resp_channel.hpp>
#include <cpm_common_interfaces/msg/lps_sa_weigh_tx_channel.hpp>
#include <cpm_common_interfaces/msg/widgets_debug_data.hpp>
#include <cpm_common_interfaces/msg/work_order_assist_tx_channel.hpp>
#include <job_mgr_interfaces/msg/lps_sa_job_mgr_debug_channel.hpp>
#include <job_mgr_interfaces/msg/lps_sa_job_mgr_resp_channel.hpp>
#include <job_mgr_interfaces/msg/lps_sa_job_mgr_tx_channel.hpp>
#include <job_mgr_interfaces/msg/switch_input_scs.hpp>
#include <weigh_app_interfaces/msg/data_link_data.hpp>
#include <weigh_app_interfaces/msg/lps_sa_nvm_cal_data_channel.hpp>
#include <weigh_app_interfaces/msg/lps_sa_nvm_cal_on_the_fly_data_channel.hpp>
#include <weigh_app_interfaces/msg/lps_sa_weigh_debug_channel.hpp>
#include <weigh_app_interfaces/msg/lps_sa_weigh_init_debug_channel.hpp>
#include <weigh_app_interfaces/msg/machine.hpp>
#include <weigh_app_interfaces/msg/pwm_input_channels.hpp>
#include <weigh_app_interfaces/msg/system_hardware_health_storage.hpp>
#include <weigh_app_interfaces/msg/tipoff_model_test_points.hpp>

#include "ros2wrapper/RosInputInterface.h"
#include "ROS2Logger.hpp"

#include <stddef.h>     /* offsetof */
#include "xcp_server/db/XCPServerDb.hpp"
using namespace xcp_server;

// Macros that are used to push SCS data into 'db': DB_PUSH invokes db.update, DB_PUSH_ARRAY expands into a for-loop with DB_PUSH invocations
#define DB_PUSH(item) db.update(groupIdx | offset++, (item))
#define DB_PUSH_ARRAY(array_name,num_elements) for (uint8_t iter=0; iter < num_elements; iter++)                                   \
                                               {                                                                                   \
                                                  DB_PUSH(array_name[iter]);                                                       \
                                               }

// Little-endian unpack that advances the byte pointer (replaces the platform OEL_UNPACK_LE_8/24 macros).
#define XCP_UNPACK_LE_8(ptr, value)  do { (value) = static_cast<uint8_t>((ptr)[0]); (ptr) += 1; } while (0)
#define XCP_UNPACK_LE_24(ptr, value) do { (value) = static_cast<uint32_t>((ptr)[0]) | (static_cast<uint32_t>((ptr)[1]) << 8) | \
                                                    (static_cast<uint32_t>((ptr)[2]) << 16); (ptr) += 3; } while (0)

// Values of the legacy constants used by update() (LpsPublic.h LPS_WEIGH_OVERLOAD_LEVEL_NONE,
// DataLinkParam.h DSI_CODE_OK()).
static constexpr int32_t  kLpsWeighOverloadLevelNone = 0;
static constexpr uint16_t kDsiCodeOk = 0;

// Element i of an unbounded ROS2 array field, or 0 when the message carries fewer elements. The legacy
// PwmData arrays were fixed-size (MAX_CH) and value-initialised, and update() reads them unconditionally.
template<typename V>
static inline typename V::value_type xcpArrayElement(const V& values, size_t i)
{
    return (i < values.size()) ? values[i] : typename V::value_type();
}
///////////////////////////////////////////////////////////////////////////////
/// @brief One former SCS input channel, now a ROS2 topic. The ROS2 message is
///        the base class, so XcpScsInputs::update() reads the message fields.
///
/// Same semantics as an SCS input channel read through SCSInData<T>:
/// - the channel keeps at most queueSize messages (the AIS channel "queueSize"
///   of interfaces_*.rb) and drops the oldest when full;
/// - update() takes at most one message per call and returns true;
/// - isTimedOut() uses "<interface>_rxTimeout_sec" (0 = never times out).
///////////////////////////////////////////////////////////////////////////////
template<typename Msg>
class RosInData : public Msg
{
public:
    typedef std::chrono::steady_clock Clock;

    RosInData() :
        Msg(),
        m_interfaceName(),
        m_rxTimeout_sec(0.0),
        m_lastRxDataTime(),
        m_pRxInterface(nullptr),
        m_queue(),
        m_queueSize(1),
        m_initCalled(false),
        m_nullPointerLogged(false)
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief  Initialize the channel for reading (counterpart of SCSInData<T>::initReadInterface)
    /// @param  interfaceName - former SCS interface name (key of the rx timeout)
    /// @param  rxInterface   - ROS2 input, owned by the caller (unbind with stop() before deleting it)
    /// @param  queueSize     - AIS channel queueSize of this interface
    /// @param  cs            - rx timeouts, key "<interfaceName>_rxTimeout_sec"
    /// @return true if the channel was successfully configured
    ///////////////////////////////////////////////////////////////////////////////
    bool initReadInterface(const std::string& interfaceName, ros2_wrapper::RosInputInterface<Msg>* rxInterface,
                           unsigned int queueSize, const std::map<std::string, double>& cs)
    {
        m_initCalled = true;
        m_interfaceName = interfaceName;
        m_pRxInterface = rxInterface;
        m_queueSize = (0 == queueSize) ? 1 : queueSize;
        if (nullptr == m_pRxInterface)
        {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Error Creating Interface %s", m_interfaceName.c_str());
            return false;
        }
        const std::string rxTimeoutKey = m_interfaceName + "_rxTimeout_sec";
        const std::map<std::string, double>::const_iterator it = cs.find(rxTimeoutKey);
        if (it == cs.end())
        {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "%s not found in the XcpServerTask parameters", rxTimeoutKey.c_str());
            return false;
        }
        m_rxTimeout_sec = it->second;
        return true;
    }

    /// @brief Drop the ROS2 input. Call before the owner deletes it.
    void stop()
    {
        m_pRxInterface = nullptr;
    }

    /// @brief true if no data was received for longer than the rx timeout
    bool isTimedOut() const
    {
        return ((m_rxTimeout_sec != 0) &&
                (std::chrono::duration<double>(Clock::now() - m_lastRxDataTime).count() > m_rxTimeout_sec));
    }

    /// @brief Get any new data on this channel
    /// @return true if new data was received
    bool update()
    {
        if (nullptr != m_pRxInterface)
        {
            Msg msg;
            while (m_pRxInterface->get(msg))
            {
                if (m_queue.size() >= m_queueSize)
                {
                    m_queue.pop_front();
                }
                m_queue.push_back(msg);
            }
            if (!m_queue.empty())
            {
                static_cast<Msg&>(*this) = m_queue.front();
                m_queue.pop_front();
                m_lastRxDataTime = Clock::now();
                logReceived();
                return true;
            }
        }
        else if (m_initCalled && !m_nullPointerLogged)
        {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "[update] | Channel pointer is NULL - cannot get data on %s",
                    m_interfaceName.c_str());
            m_nullPointerLogged = true;
        }
        return false;
    }

private:
    // Former SCSInData<T>::update() DEBUG line; the message is printed with the generated ROS2 to_yaml().
    void logReceived()
    {
        if (!rcutils_logging_logger_is_enabled_for(ROS2Logger::Instance().GetLogger().get_name(), RCUTILS_LOG_SEVERITY_DEBUG))
        {
            return;
        }
        RCLCPP_DEBUG(ROS2Logger::Instance().GetLogger(), "[update] | Received new data on %s: (%s)",
                m_interfaceName.c_str(), to_yaml(static_cast<const Msg&>(*this), true).c_str());
    }

    std::string                           m_interfaceName;
    double                                m_rxTimeout_sec;
    Clock::time_point                     m_lastRxDataTime;
    ros2_wrapper::RosInputInterface<Msg>* m_pRxInterface;   // not owned
    std::deque<Msg>                       m_queue;          // the former SCS channel queue
    unsigned int                          m_queueSize;
    bool                                  m_initCalled;
    bool                                  m_nullPointerLogged;
};

///////////////////////////////////////////////////////////////////////////////
/// @brief Replacement of interfaces::baseTypes::InputInterface<T> for the drain
///        loop `while (input->get(msg)) { ... }` (DataLinkData). Like the SCS
///        channel, at most queueSize messages are kept (oldest dropped).
///////////////////////////////////////////////////////////////////////////////
template<typename Msg>
class RosInputAdapter
{
public:
    RosInputAdapter() : m_pRxInterface(nullptr), m_queue(), m_queueSize(1) {}

    // The interface is owned by the caller and must outlive this object or be unbound first.
    void bind(ros2_wrapper::RosInputInterface<Msg>* rxInterface, unsigned int queueSize)
    {
        m_pRxInterface = rxInterface;
        m_queueSize = (0 == queueSize) ? 1 : queueSize;
    }

    void unbind()
    {
        m_pRxInterface = nullptr;
    }

    bool get(Msg& data)
    {
        if (nullptr == m_pRxInterface)
        {
            return false;
        }
        Msg msg;
        while (m_pRxInterface->get(msg))
        {
            if (m_queue.size() >= m_queueSize)
            {
                m_queue.pop_front();
            }
            m_queue.push_back(msg);
        }
        if (m_queue.empty())
        {
            return false;
        }
        data = m_queue.front();
        m_queue.pop_front();
        return true;
    }

private:
    ros2_wrapper::RosInputInterface<Msg>* m_pRxInterface;   // not owned
    std::deque<Msg>                       m_queue;
    unsigned int                          m_queueSize;
};

class XcpScsInputs
{

  public:

    ParameterDb db;

    RosInData<weigh_app_interfaces::msg::SystemHardwareHealthStorage> m_systemHardwareHealth;
    RosInData<cpm_common_interfaces::msg::LpsSaWeighReqstChannel> m_lpsSaWeighReqstChannel;
    RosInData<cpm_common_interfaces::msg::LpsSaWeighRespChannel> m_lpsSaWeighRespChannel;
    RosInData<weigh_app_interfaces::msg::LpsSaWeighDebugChannel> m_lpsSaWeighDebugChannel;
    RosInData<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel> m_lpsSaWeighInitDebugChannel;
    RosInData<cpm_common_interfaces::msg::LpsSaWeighTxChannel> m_lpsSaWeighTxChannel;
    RosInData<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel> m_lpsSaNvmDataChannel;
    RosInData<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel> m_lpsSaNvmOnTheFlyDataChannel;
    RosInData<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel> m_lpsSaJobMgrTxChannel;
    RosInData<weigh_app_interfaces::msg::PwmInputChannels> m_pwmInputChannels;
    RosInData<weigh_app_interfaces::msg::Machine> m_machine;
    RosInData<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel> m_lpsSaJobMgrReqstChannel;
    RosInData<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel> m_lpsSaJobMgrRespChannel;
    RosInData<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel> m_lpsSaJobMgrDebugChannel;
    RosInData<job_mgr_interfaces::msg::SwitchInputScs> m_switchInputScs;
    RosInData<cpm_common_interfaces::msg::WorkOrderAssistTxChannel> m_workOrderAssistTxChannel;
    RosInData<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface> m_displayStateChannel;
    RosInData<cpm_common_interfaces::msg::WidgetsDebugData> m_widgetsDebugdata;
    RosInData<cpm_common_interfaces::msg::CycleSegTxChannel> m_cycleSegTxData;
    RosInData<weigh_app_interfaces::msg::TipoffModelTestPoints> m_tipoffModelTestPoints;
    RosInData<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel> m_autonomyConditionDiagnosticsTxChannel;
    RosInData<cpm_common_interfaces::msg::LpsSaUIBemSimStateInterface> m_BemSimDebugChannel;

    RosInputAdapter<weigh_app_interfaces::msg::DataLinkData>* dataLinkDataInput = nullptr;
    RosInputAdapter<weigh_app_interfaces::msg::DataLinkData> m_dataLinkDataAdapter;

  ///////////////////////////////////////////////////////////////////////////////
  /// @brief Run "update" on all of the scs channels in the structure
  ///
  /// @return true if any channel has new data, false otherwise
  ///////////////////////////////////////////////////////////////////////////////
  bool update()
  {
    bool retVal = true;
    static bool init_done = false;

    /* index group: 00000 */
    if (m_systemHardwareHealth.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 0;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, false); // Address 0 can't be used
        db.update(groupIdx | offset++, m_systemHardwareHealth.available_system_memory_kb);
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.system_up_time_sec));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.load_avg1min));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.load_avg5min));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.load_avg15min));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.eth0_tx_kbs));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.eth0_rx_kbs));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.eth1_tx_kbs));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.eth1_rx_kbs));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.system_cpu_usage_percent));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.system_cpu_io_wait_percent));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.system_cpu_irq_percent));
        db.update(groupIdx | offset++, static_cast<float>(m_systemHardwareHealth.battery_voltage));
        db.update(groupIdx | offset++, m_systemHardwareHealth.total_system_memory_kb);

        { // Find disk space
            unsigned int avail_kb = 0;
            float percentUse = 100.f;

            for (const auto& diskSpace : m_systemHardwareHealth.list_of_remaining_disk_space) {
                if (diskSpace.filesystem == "/dev/mmcblk0p2") {
                    avail_kb = diskSpace.avail_kb;
                    percentUse = std::atof(diskSpace.percent_use.c_str());
                    break;
                }
            }

            // Add the channels
            db.update(groupIdx | offset++, avail_kb);
            db.update(groupIdx | offset++, percentUse);
        }

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 10000 */
    if ( m_lpsSaWeighReqstChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 1;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, m_lpsSaWeighReqstChannel.command.value == cpm_common_interfaces::msg::WeighReqstChannelCommand::ZERO);
        db.update(groupIdx | offset++, m_lpsSaWeighReqstChannel.command.value == cpm_common_interfaces::msg::WeighReqstChannelCommand::RESET_BEST_BUCKET_WEIGHT);
        db.update(groupIdx | offset++, m_lpsSaWeighReqstChannel.command.value == cpm_common_interfaces::msg::WeighReqstChannelCommand::CAPTURE_CYLINDER_EXTENSION_REFERENCE);
        db.update(groupIdx | offset++, m_lpsSaWeighReqstChannel.command.value == cpm_common_interfaces::msg::WeighReqstChannelCommand::WRITE_WEIGH_RANGE);
        db.update(groupIdx | offset++, m_lpsSaWeighReqstChannel.arg_f1);
        db.update(groupIdx | offset++, m_lpsSaWeighReqstChannel.arg_f2);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 20000 */
    if ( m_lpsSaWeighRespChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 2;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, m_lpsSaWeighRespChannel.command.value == cpm_common_interfaces::msg::WeighReqstChannelCommand::ZERO ? m_lpsSaWeighRespChannel.success : false);
        db.update(groupIdx | offset++, m_lpsSaWeighRespChannel.command.value == cpm_common_interfaces::msg::WeighReqstChannelCommand::RESET_BEST_BUCKET_WEIGHT ? m_lpsSaWeighRespChannel.success : false);
        db.update(groupIdx | offset++, m_lpsSaWeighRespChannel.command.value == cpm_common_interfaces::msg::WeighReqstChannelCommand::WRITE_WEIGH_RANGE ? m_lpsSaWeighRespChannel.success : false);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 30000 */
    if (m_lpsSaWeighDebugChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 3;
        static constexpr uint32_t groupIdx = index << 16;

        /* LpsUpdtTbl_t m_weighUpdtTbl */
        db.update(groupIdx | 0x00, (int)m_lpsSaWeighDebugChannel.debug_lift_cyl_he_press_status);
        db.update(groupIdx | 0x01, m_lpsSaWeighDebugChannel.debug_lift_cyl_he_press);
        db.update(groupIdx | 0x02, (int)m_lpsSaWeighDebugChannel.debug_lift_cyl_re_press_status);
        db.update(groupIdx | 0x03, m_lpsSaWeighDebugChannel.debug_lift_cyl_re_press);
        db.update(groupIdx | 0x04, (int)m_lpsSaWeighDebugChannel.debug_lift_position_status);
        db.update(groupIdx | 0x05, m_lpsSaWeighDebugChannel.debug_lift_cyl_norm_len);
        db.update(groupIdx | 0x06, (int)m_lpsSaWeighDebugChannel.debug_lift_position_status);
        db.update(groupIdx | 0x07, m_lpsSaWeighDebugChannel.debug_lift_cyl_vel);
        db.update(groupIdx | 0x08, (int)m_lpsSaWeighDebugChannel.debug_hyd_oil_temp_status);
        db.update(groupIdx | 0x09, m_lpsSaWeighDebugChannel.debug_hyd_oil_temp);
        db.update(groupIdx | 0x0A, m_lpsSaWeighDebugChannel.debug_weigh_updt_clock_keyon_sec);
        db.update(groupIdx | 0x0B, m_lpsSaWeighDebugChannel.debug_weigh_updt_pass_count);
        db.update(groupIdx | 0x0C, false /* ZeroButtonPress */);
        db.update(groupIdx | 0x0D, (int)m_lpsSaWeighDebugChannel.debug_tilt_position_status);
        db.update(groupIdx | 0x0E, m_lpsSaWeighDebugChannel.debug_tilt_cyl_norm_len);
        db.update(groupIdx | 0x0F, (int)m_lpsSaWeighDebugChannel.debug_tilt_position_status);
        db.update(groupIdx | 0x10, m_lpsSaWeighDebugChannel.debug_tilt_cyl_vel);
        db.update(groupIdx | 0x11, (int)m_lpsSaWeighDebugChannel.debug_bucket_angle_status);
        db.update(groupIdx | 0x12, m_lpsSaWeighDebugChannel.debug_bucket_angle);
        db.update(groupIdx | 0x13, (int)m_lpsSaWeighDebugChannel.debug_requested_gear_status);
        db.update(groupIdx | 0x14, m_lpsSaWeighDebugChannel.debug_requested_gear);
        db.update(groupIdx | 0x15, (bool)static_cast<char>(m_lpsSaWeighDebugChannel.live_weigh_tbl_use_fast_filter));
        db.update(groupIdx | 0x16, m_lpsSaWeighDebugChannel.debug_weigh_updt_loader_bkt_payld_trgt_wt);

        /* LpsWrkTbl_t m_LpsWrk */
        db.update(groupIdx | 0x17, m_lpsSaWeighDebugChannel.lift_cyl_pressure_v0);
        db.update(groupIdx | 0x18, m_lpsSaWeighDebugChannel.inst_wt_llw_filt);
        db.update(groupIdx | 0x19, m_lpsSaWeighDebugChannel.inst_wt_der);
        db.update(groupIdx | 0x1A, m_lpsSaWeighDebugChannel.inst_wt_raw.val);
        db.update(groupIdx | 0x1B, (int)m_lpsSaWeighDebugChannel.inst_wt_raw.stat);
        db.update(groupIdx | 0x1C, m_lpsSaWeighDebugChannel.inst_wt_filt);
        db.update(groupIdx | 0x1D, m_lpsSaWeighDebugChannel.cyl_flow_const_lift_he_flow_const);
        db.update(groupIdx | 0x1E, m_lpsSaWeighDebugChannel.cyl_flow_const_lift_re_to_he_flow_ratio);
        db.update(groupIdx | 0x1F, (int)static_cast<int32_t>(m_lpsSaWeighDebugChannel.linkage_movement_lift));
        db.update(groupIdx | 0x20, (int)static_cast<int32_t>(m_lpsSaWeighDebugChannel.linkage_movement_tilt));
        db.update(groupIdx | 0x21, m_lpsSaWeighDebugChannel.wrw_tbl_op_tbl_wt);
        db.update(groupIdx | 0x22, (int)static_cast<int32_t>(m_lpsSaWeighDebugChannel.wrw_tbl_op_tbl_warning));
        db.update(groupIdx | 0x23, (int)static_cast<int32_t>(m_lpsSaWeighDebugChannel.wrw_tbl_op_tbl_status));
        db.update(groupIdx | 0x24, (int)m_lpsSaWeighDebugChannel.wrw_tbl_op_tbl_indicator);
        db.update(groupIdx | 0x25, (bool)static_cast<char>(m_lpsSaWeighDebugChannel.wrw_tbl_wk_tbl_been_below_range));
        db.update(groupIdx | 0x26, (int)static_cast<char>(m_lpsSaWeighDebugChannel.lps_stall_detect_lift_stalled));
        db.update(groupIdx | 0x27, (int)static_cast<int32_t>(m_lpsSaWeighDebugChannel.dump_state_status));
        db.update(groupIdx | 0x28, m_lpsSaWeighDebugChannel.best_bkt_wt_wt);
        db.update(groupIdx | 0x29, static_cast<uint16_t>(m_lpsSaWeighDebugChannel.best_bkt_wt_payload_calc_meth));
        db.update(groupIdx | 0x2A, m_lpsSaWeighDebugChannel.low_lift_wt_last_input);
        db.update(groupIdx | 0x2B, m_lpsSaWeighDebugChannel.low_lift_wt_mean_est);
        db.update(groupIdx | 0x2C, m_lpsSaWeighDebugChannel.low_lift_wt_mean_est_comp);
        db.update(groupIdx | 0x2D, m_lpsSaWeighDebugChannel.low_lift_wt_variance_est);
        db.update(groupIdx | 0x2E, m_lpsSaWeighDebugChannel.low_lift_wt_stdev_est);
        db.update(groupIdx | 0x2F, m_lpsSaWeighDebugChannel.low_lift_wt_confidence);
        db.update(groupIdx | 0x30, m_lpsSaWeighDebugChannel.low_lift_wt_confidence_est);
        db.update(groupIdx | 0x31, m_lpsSaWeighDebugChannel.low_lift_wt_confidence_timer);
        db.update(groupIdx | 0x32, m_lpsSaWeighDebugChannel.low_lift_wt_wt);
        db.update(groupIdx | 0x33, (int)static_cast<int32_t>(m_lpsSaWeighDebugChannel.low_lift_wt_stat));
        db.update(groupIdx | 0x34, false /* ZeroAccepted */);
        db.update(groupIdx | 0x35, false /* TooHeavyToZero */);
        db.update(groupIdx | 0x36, (int)static_cast<int32_t>(m_lpsSaWeighDebugChannel.zero_adj_tbl_zero_adj_status));
        db.update(groupIdx | 0x37, m_lpsSaWeighDebugChannel.dump_wt_change_data_dump_cumulative_wt_change);
        db.update(groupIdx | 0x38, (bool)static_cast<char>(m_lpsSaWeighDebugChannel.dig_detect_data_dig_started));
        db.update(groupIdx | 0x39, (bool)static_cast<char>(m_lpsSaWeighDebugChannel.dig_detect_data_dig_detected));
        db.update(groupIdx | 0x3A, (int)static_cast<int32_t>(m_lpsSaWeighDebugChannel.dig_detect_data_dig_state));
        db.update(groupIdx | 0x3B, (bool)static_cast<char>(m_lpsSaWeighDebugChannel.dig_detect_data_wt_stabilized));
        db.update(groupIdx | 0x3C, static_cast<uint32_t>(m_lpsSaWeighDebugChannel.dig_detect_data_dig_duration));
        db.update(groupIdx | 0x3D, m_lpsSaWeighDebugChannel.live_weigh_tbl_wt);
        db.update(groupIdx | 0x3E, (int)static_cast<int32_t>(m_lpsSaWeighDebugChannel.live_weigh_tbl_stat));
        db.update(groupIdx | 0x3F, m_lpsSaWeighDebugChannel.reweigh_warn);

        /* Lift Cylinder Head End Pressure */
        db.update(groupIdx | 0x40, m_lpsSaWeighDebugChannel.debug_lift_cyl_he_period);
        db.update(groupIdx | 0x41, m_lpsSaWeighDebugChannel.debug_lift_cyl_he_width);
        db.update(groupIdx | 0x42, m_lpsSaWeighDebugChannel.debug_lift_cyl_he_dc);
        db.update(groupIdx | 0x43, m_lpsSaWeighDebugChannel.debug_lift_cyl_he_press);

        /* Lift Cylinder Rod End Pressure */
        db.update(groupIdx | 0x44, m_lpsSaWeighDebugChannel.debug_lift_cyl_re_period);
        db.update(groupIdx | 0x45, m_lpsSaWeighDebugChannel.debug_lift_cyl_re_width);
        db.update(groupIdx | 0x46, m_lpsSaWeighDebugChannel.debug_lift_cyl_re_dc);
        db.update(groupIdx | 0x47, m_lpsSaWeighDebugChannel.debug_lift_cyl_re_press);

        /* Lift Cylinder */
        db.update(groupIdx | 0x48, m_lpsSaWeighDebugChannel.debug_lift_cyl_period);
        db.update(groupIdx | 0x49, m_lpsSaWeighDebugChannel.debug_lift_cyl_width);
        db.update(groupIdx | 0x4A, m_lpsSaWeighDebugChannel.debug_lift_cyl_dc);
        db.update(groupIdx | 0x4B, m_lpsSaWeighDebugChannel.debug_lift_cyl_raw_ext);
        db.update(groupIdx | 0x4C, m_lpsSaWeighDebugChannel.debug_lift_cyl_filt_ext);
        db.update(groupIdx | 0x4D, m_lpsSaWeighDebugChannel.debug_lift_cyl_norm_len);
        db.update(groupIdx | 0x4E, m_lpsSaWeighDebugChannel.debug_lift_cyl_vel);
        db.update(groupIdx | 0x4F, m_lpsSaWeighDebugChannel.debug_lift_angle);

        /* Tilt Cylinder */
        db.update(groupIdx | 0x50, m_lpsSaWeighDebugChannel.debug_tilt_cyl_period);
        db.update(groupIdx | 0x51, m_lpsSaWeighDebugChannel.debug_tilt_cyl_width);
        db.update(groupIdx | 0x52, m_lpsSaWeighDebugChannel.debug_tilt_cyl_dc);
        db.update(groupIdx | 0x53, m_lpsSaWeighDebugChannel.debug_tilt_cyl_raw_len);
        db.update(groupIdx | 0x54, m_lpsSaWeighDebugChannel.debug_tilt_cyl_vel);
        db.update(groupIdx | 0x55, m_lpsSaWeighDebugChannel.debug_tilt_angle);
        db.update(groupIdx | 0x56, m_lpsSaWeighDebugChannel.debug_tilt_angle_abc);

        /* Overloads */
        db.update(groupIdx | 0x57, m_lpsSaWeighDebugChannel.overload_warn_tbl_bucket_load_factor);
        db.update(groupIdx | 0x58, (bool)static_cast<char>(m_lpsSaWeighDebugChannel.overload_warn_tbl_dig_reverse_flag));
        db.update(groupIdx | 0x59, (bool)static_cast<char>(m_lpsSaWeighDebugChannel.overload_warn_tbl_in_overload_range));
        db.update(groupIdx | 0x5A, false /* Previously InWaitForLatch */);
        db.update(groupIdx | 0x5B, static_cast<int32_t>(m_lpsSaWeighDebugChannel.overload_warn_tbl_level) != kLpsWeighOverloadLevelNone);
        db.update(groupIdx | 0x5C, m_lpsSaWeighDebugChannel.overload_warn_tbl_prev_dig_state);

        /* tipoff assists channels */
        db.update(groupIdx | 0x5D, (bool)static_cast<char>(m_lpsSaWeighDebugChannel.best_bkt_wt_tipoff_live_weight_in_use));
        db.update(groupIdx | 0x5E, 0); /* not used */
        db.update(groupIdx | 0x5F, m_lpsSaWeighDebugChannel.tipoff_inputs.bucket_current_weight);
        db.update(groupIdx | 0x60, m_lpsSaWeighDebugChannel.tipoff_inputs.bucket_current_weight_accuracy);
        db.update(groupIdx | 0x61, m_lpsSaWeighDebugChannel.tipoff_inputs.eef_imu_accel_x);
        db.update(groupIdx | 0x62, m_lpsSaWeighDebugChannel.tipoff_inputs.eef_imu_accel_y);
        db.update(groupIdx | 0x63, m_lpsSaWeighDebugChannel.tipoff_inputs.eef_imu_accel_z);
        db.update(groupIdx | 0x64, m_lpsSaWeighDebugChannel.tipoff_inputs.input_status);
        db.update(groupIdx | 0x65, (bool)m_lpsSaWeighDebugChannel.tipoff_inputs.invalidate_outputs);
        db.update(groupIdx | 0x66, m_lpsSaWeighDebugChannel.tipoff_inputs.lift_angle);
        db.update(groupIdx | 0x67, m_lpsSaWeighDebugChannel.tipoff_inputs.lift_he_pressure);
        db.update(groupIdx | 0x68, m_lpsSaWeighDebugChannel.tipoff_inputs.lift_re_pressure);
        db.update(groupIdx | 0x69, m_lpsSaWeighDebugChannel.tipoff_inputs.lift_valve_cmd);
        db.update(groupIdx | 0x6A, m_lpsSaWeighDebugChannel.tipoff_inputs.steering_angle);
        db.update(groupIdx | 0x6B, m_lpsSaWeighDebugChannel.tipoff_inputs.tilt_extension);
        db.update(groupIdx | 0x6C, m_lpsSaWeighDebugChannel.tipoff_inputs.tilt_he_pressure);
        db.update(groupIdx | 0x6D, m_lpsSaWeighDebugChannel.tipoff_inputs.tilt_re_pressure);
        db.update(groupIdx | 0x6E, m_lpsSaWeighDebugChannel.tipoff_inputs.tilt_valve_cmd);
        db.update(groupIdx | 0x6F, m_lpsSaWeighDebugChannel.tipoff_inputs.tipoff_mode);
        db.update(groupIdx | 0x70, m_lpsSaWeighDebugChannel.tipoff_inputs.tool_mass);
        db.update(groupIdx | 0x71, m_lpsSaWeighDebugChannel.tipoff_inputs.truck_start_weight);
        db.update(groupIdx | 0x72, m_lpsSaWeighDebugChannel.tipoff_inputs.truck_target_wt);
        db.update(groupIdx | 0x73, m_lpsSaWeighDebugChannel.tipoff_outputs.arbitrated_payload_norm_error_out);
        db.update(groupIdx | 0x74, m_lpsSaWeighDebugChannel.tipoff_outputs.current_weight_norm_error_out);
        db.update(groupIdx | 0x75, m_lpsSaWeighDebugChannel.tipoff_outputs.error_code_out);
        db.update(groupIdx | 0x76, m_lpsSaWeighDebugChannel.tipoff_outputs.payload_norm_stdev_out);
        db.update(groupIdx | 0x77, m_lpsSaWeighDebugChannel.tipoff_outputs.payload_send_to_cpm);
        db.update(groupIdx | 0x78, m_lpsSaWeighDebugChannel.tipoff_outputs.payload_status_send_to_cpm);
        db.update(groupIdx | 0x79, m_lpsSaWeighDebugChannel.tipoff_outputs.pcs_weight_accuracy_out);
        db.update(groupIdx | 0x7A, m_lpsSaWeighDebugChannel.tipoff_outputs.spill_rate_out);
        db.update(groupIdx | 0x7B, m_lpsSaWeighDebugChannel.tipoff_outputs.tilt_pressure_out);
        db.update(groupIdx | 0x7C, m_lpsSaWeighDebugChannel.tipoff_outputs.tilt_sensitivity_out);
        db.update(groupIdx | 0x7D, m_lpsSaWeighDebugChannel.tipoff_outputs.weigh_status_out);
        db.update(groupIdx | 0x7E, m_lpsSaWeighDebugChannel.tipoff_inputs.zero_offset);
        db.update(groupIdx | 0x7F, m_lpsSaWeighDebugChannel.tipoff_inputs.simple_cal_factor);
        db.update(groupIdx | 0x80, m_lpsSaWeighDebugChannel.tipoff_inputs.bucket_angle);
        db.update(groupIdx | 0x81, (bool)m_lpsSaWeighDebugChannel.tipoff_inputs.unlatch_trigger);

        /* Tilt Cylinder Head End Pressure */
        db.update(groupIdx | 0x82, m_lpsSaWeighDebugChannel.debug_tilt_cyl_he_period);
        db.update(groupIdx | 0x83, m_lpsSaWeighDebugChannel.debug_tilt_cyl_he_width);
        db.update(groupIdx | 0x84, m_lpsSaWeighDebugChannel.debug_tilt_cyl_he_dc);
        db.update(groupIdx | 0x85, m_lpsSaWeighDebugChannel.debug_tilt_cyl_he_press);

        /* Tilt Cylinder Rod End Pressure */
        db.update(groupIdx | 0x86, m_lpsSaWeighDebugChannel.debug_tilt_cyl_re_period);
        db.update(groupIdx | 0x87, m_lpsSaWeighDebugChannel.debug_tilt_cyl_re_width);
        db.update(groupIdx | 0x88, m_lpsSaWeighDebugChannel.debug_tilt_cyl_re_dc);
        db.update(groupIdx | 0x89, m_lpsSaWeighDebugChannel.debug_tilt_cyl_re_press);

        /* more tip-assist channels */
        db.update(groupIdx | 0x8A, m_lpsSaWeighDebugChannel.tipoff_inputs.anchor_zero_offset);
        db.update(groupIdx | 0x8B, m_lpsSaWeighDebugChannel.tipoff_inputs.anchor_factor);
        db.update(groupIdx | 0x8C, m_lpsSaWeighDebugChannel.tipoff_outputs.bucket_payload_target);
        db.update(groupIdx | 0x8D, m_lpsSaWeighDebugChannel.tipoff_inputs.pass_count);
        db.update(groupIdx | 0x8E, m_lpsSaWeighDebugChannel.tipoff_inputs.lift_norm_angle);
        db.update(groupIdx | 0x8F, m_lpsSaWeighDebugChannel.tipoff_inputs.lift_norm_length);
        db.update(groupIdx | 0x90, m_lpsSaWeighDebugChannel.tipoff_inputs.tilt_norm_angle);
        db.update(groupIdx | 0x91, m_lpsSaWeighDebugChannel.tipoff_inputs.tilt_norm_length);
        db.update(groupIdx | 0x92, m_lpsSaWeighDebugChannel.tipoff_outputs.min_secure_bucket_angle);
        db.update(groupIdx | 0x93, m_lpsSaWeighDebugChannel.tipoff_outputs.unsecured_pfw_status);
        db.update(groupIdx | 0x94, m_lpsSaWeighDebugChannel.tipoff_outputs.unsecured_payload_lower_bound_norm);
        db.update(groupIdx | 0x95, m_lpsSaWeighDebugChannel.tipoff_outputs.unsecured_payload_upper_bound_norm);
        db.update(groupIdx | 0x96, m_lpsSaWeighDebugChannel.tipoff_inputs.friction_mu);
        db.update(groupIdx | 0x97, m_lpsSaWeighDebugChannel.tipoff_inputs.friction_offset);

        // Chassis IMU
        db.update(groupIdx | 0x98, m_lpsSaWeighDebugChannel.chassis_imu_gravity_x);
        db.update(groupIdx | 0x99, m_lpsSaWeighDebugChannel.chassis_imu_gravity_y);
        db.update(groupIdx | 0x9A, m_lpsSaWeighDebugChannel.chassis_imu_gravity_z);
        db.update(groupIdx | 0x9B, m_lpsSaWeighDebugChannel.chassis_imu_velocity_x);
        db.update(groupIdx | 0x9C, m_lpsSaWeighDebugChannel.chassis_imu_velocity_y);
        db.update(groupIdx | 0x9D, m_lpsSaWeighDebugChannel.chassis_imu_velocity_z);
        db.update(groupIdx | 0x9E, m_lpsSaWeighDebugChannel.chassis_imu_bias_ang_vel_x);
        db.update(groupIdx | 0x9F, m_lpsSaWeighDebugChannel.chassis_imu_bias_ang_vel_y);
        db.update(groupIdx | 0xA0, m_lpsSaWeighDebugChannel.chassis_imu_bias_ang_vel_z);
        db.update(groupIdx | 0xA1, m_lpsSaWeighDebugChannel.chassis_imu_pitch);
        db.update(groupIdx | 0xA2, m_lpsSaWeighDebugChannel.chassis_imu_roll);
        db.update(groupIdx | 0xA3, m_lpsSaWeighDebugChannel.chassis_imu_sensor_lin_acc_status);
        db.update(groupIdx | 0xA4, m_lpsSaWeighDebugChannel.chassis_imu_sensor_ang_vel_status);
        db.update(groupIdx | 0xA5, m_lpsSaWeighDebugChannel.chassis_imu_bias_mag_jerk);
        db.update(groupIdx | 0xA6, m_lpsSaWeighDebugChannel.chassis_imu_bias_mag_ang_accel);
        db.update(groupIdx | 0xA7, m_lpsSaWeighDebugChannel.chassis_imu_bias_max_ang_vel);
        db.update(groupIdx | 0xA8, m_lpsSaWeighDebugChannel.chassis_imu_lin_acc_x);
        db.update(groupIdx | 0xA9, m_lpsSaWeighDebugChannel.chassis_imu_lin_acc_y);
        db.update(groupIdx | 0xAA, m_lpsSaWeighDebugChannel.chassis_imu_lin_acc_z);
        db.update(groupIdx | 0xAB, m_lpsSaWeighDebugChannel.chassis_imu_ang_vel_x);
        db.update(groupIdx | 0xAC, m_lpsSaWeighDebugChannel.chassis_imu_ang_vel_y);
        db.update(groupIdx | 0xAD, m_lpsSaWeighDebugChannel.chassis_imu_ang_vel_z);

        // Added for Acceleration Compensation
        db.update(groupIdx | 0xB0, m_lpsSaWeighDebugChannel.debug_lift_ang_vel);
        db.update(groupIdx | 0xB1, m_lpsSaWeighDebugChannel.lift_position_filt_velocity);
        db.update(groupIdx | 0xB2, m_lpsSaWeighDebugChannel.wrw_tbl_wk_tbl_result_weight_ave_raw);
        db.update(groupIdx | 0xB3, m_lpsSaWeighDebugChannel.wrw_tbl_wk_tbl_result_weight_ave);
        db.update(groupIdx | 0xB4, m_lpsSaWeighDebugChannel.lift_position_filt_length);
        db.update(groupIdx | 0xB5, m_lpsSaWeighDebugChannel.lift_cyl_pressure);
        db.update(groupIdx | 0xB6, m_lpsSaWeighDebugChannel.inst_wt_raw_pre_tilt_comp);
        db.update(groupIdx | 0xB7, m_lpsSaWeighDebugChannel.inst_wt_raw_post_tilt_comp);
        db.update(groupIdx | 0xB8, m_lpsSaWeighDebugChannel.lift_position_filt_angle);

        // Added for Pitch and Roll Compensation
        db.update(groupIdx | 0xC0, m_lpsSaWeighDebugChannel.wrw_tbl_wk_tbl_result_weight_ave_raw_imu_comp);
        db.update(groupIdx | 0xC1, m_lpsSaWeighDebugChannel.lift_cyl_pressure_imu_adjusted);

        db.update(groupIdx | 0xFF, updateCounter++);
    }

    /* index group: 40000 */
    if ( m_lpsSaWeighInitDebugChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 4;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, 1); /* unused */
        db.update(groupIdx | offset++, (int)static_cast<uint16_t>(m_lpsSaWeighInitDebugChannel.cal_status));
        db.update(groupIdx | offset++, m_lpsSaWeighInitDebugChannel.cal_weight);
        db.update(groupIdx | offset++, m_lpsSaWeighInitDebugChannel.cal_adjust);
        db.update(groupIdx | offset++, m_lpsSaWeighInitDebugChannel.zero_weight);
        db.update(groupIdx | offset++, m_lpsSaWeighInitDebugChannel.start_of_weigh);
        db.update(groupIdx | offset++, m_lpsSaWeighInitDebugChannel.tilt_comp_gain_scalar);
        db.update(groupIdx | offset++, m_lpsSaWeighInitDebugChannel.dig_target_wt);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 50000 */
    if ( m_lpsSaWeighTxChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 5;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, (int)m_lpsSaWeighTxChannel.dig_stat);
        db.update(groupIdx | offset++, (int)m_lpsSaWeighTxChannel.cal_stat);
        db.update(groupIdx | offset++, (int)m_lpsSaWeighTxChannel.dump_stat);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.best_bkt_wt_in_tonnes);
        db.update(groupIdx | offset++, (int)0); // This was zero status, but never worked
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.payload_calc_meth);
        db.update(groupIdx | offset++, (int)m_lpsSaWeighTxChannel.lift_cyl_vel.stat);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.lift_cyl_vel.val);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.weigh_range.weigh_range_bottom);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.weigh_range.weigh_range_size);
        db.update(groupIdx | offset++, (int)m_lpsSaWeighTxChannel.lift_position.status);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.lift_position.percent_cylinder_length);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.can11_message_timeout_flag);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.simple_cal_adjust);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.zero_weight);
        db.update(groupIdx | offset++, m_lpsSaWeighTxChannel.warmup_lifts_required);
        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 60000 */
    if ( m_lpsSaJobMgrTxChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 6;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, m_lpsSaJobMgrTxChannel.pass_count);
        db.update(groupIdx | offset++, m_lpsSaJobMgrTxChannel.truck_target_weight);
        db.update(groupIdx | offset++, (float)m_lpsSaJobMgrTxChannel.truck_weight);
        db.update(groupIdx | offset++, m_lpsSaJobMgrTxChannel.material_id);
        db.update(groupIdx | offset++, (int)static_cast<int32_t>(m_lpsSaJobMgrTxChannel.manual_tip_off_state));
        db.update(groupIdx | offset++, (int)static_cast<int32_t>(m_lpsSaJobMgrTxChannel.tip_off_trigger_type.value));
        db.update(groupIdx | offset++, (int)static_cast<int32_t>(m_lpsSaJobMgrTxChannel.tip_off_state.value));
        db.update(groupIdx | offset++, (int)static_cast<int32_t>(m_lpsSaJobMgrTxChannel.operation_mode));
        db.update(groupIdx | offset++, (int)static_cast<int32_t>(m_lpsSaJobMgrTxChannel.standby_state.value));
        db.update(groupIdx | offset++, (int)static_cast<int32_t>(m_lpsSaJobMgrTxChannel.clear_minus_one_enable_stat));
        db.update(groupIdx | offset++, m_lpsSaJobMgrTxChannel.disp_best_bkt_wt.val);
        db.update(groupIdx | offset++, (int)m_lpsSaJobMgrTxChannel.disp_best_bkt_wt.is_ok);
        db.update(groupIdx | offset++, (int)static_cast<int32_t>(m_lpsSaJobMgrTxChannel.tip_off_state_cfg.value));

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 70000 */
    if ( m_pwmInputChannels.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 7;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, (int)m_pwmInputChannels.actual_time_us);
        db.update(groupIdx | offset++, m_pwmInputChannels.exec_time);
        db.update(groupIdx | offset++, m_pwmInputChannels.diff_time);
        db.update(groupIdx | offset++, m_pwmInputChannels.exp);

        db.update(groupIdx | offset++, xcpArrayElement(m_pwmInputChannels.width, 0));
        db.update(groupIdx | offset++, xcpArrayElement(m_pwmInputChannels.width, 1));
        db.update(groupIdx | offset++, xcpArrayElement(m_pwmInputChannels.width, 2));
        db.update(groupIdx | offset++, xcpArrayElement(m_pwmInputChannels.width, 3));
        db.update(groupIdx | offset++, xcpArrayElement(m_pwmInputChannels.period, 0));
        db.update(groupIdx | offset++, xcpArrayElement(m_pwmInputChannels.period, 1));
        db.update(groupIdx | offset++, xcpArrayElement(m_pwmInputChannels.period, 2));
        db.update(groupIdx | offset++, xcpArrayElement(m_pwmInputChannels.period, 3));

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 0x8xxxx - Cycle Segmentation */
    if ( m_cycleSegTxData.update() || !init_done ) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 8;
        static constexpr uint32_t groupIdx = index << 16;

        db.update(groupIdx | 0, m_cycleSegTxData.active_segment_id);
        db.update(groupIdx | 1, m_cycleSegTxData.dig_state);
        db.update(groupIdx | 2, m_cycleSegTxData.segment_last_completed_id);
        db.update(groupIdx | 3, m_cycleSegTxData.segment_seconds_since_last_end);
        db.update(groupIdx | 4, m_cycleSegTxData.segment_sequence_number);

        db.update(groupIdx | 5, m_cycleSegTxData.cycle_seg_in.ground_spd_kph);
        db.update(groupIdx | 6, m_cycleSegTxData.cycle_seg_in.payload_ratio);
        db.update(groupIdx | 7, m_cycleSegTxData.cycle_seg_in.payload_ratio_status);
        db.update(groupIdx | 8, m_cycleSegTxData.cycle_seg_in.payload_ratio_raw);
        db.update(groupIdx | 9, m_cycleSegTxData.cycle_seg_in.payload_ratio_raw_status);
        db.update(groupIdx | 10, m_cycleSegTxData.cycle_seg_in.lift_valve_cmd);
        db.update(groupIdx | 11, m_cycleSegTxData.cycle_seg_in.tilt_valve_cmd);
        db.update(groupIdx | 12, m_cycleSegTxData.cycle_seg_in.bucket_angle);
        db.update(groupIdx | 13, m_cycleSegTxData.cycle_seg_in.lift_angle);
        db.update(groupIdx | 14, m_cycleSegTxData.cycle_seg_in.desired_gear);
        db.update(groupIdx | 15, m_cycleSegTxData.cycle_seg_in.engine_spd_rpm);
        db.update(groupIdx | 16, m_cycleSegTxData.cycle_seg_in.tilt_lever_cmd);
        db.update(groupIdx | 17, m_cycleSegTxData.cycle_seg_in.tilt_cyl_pos);
        db.update(groupIdx | 18, m_cycleSegTxData.cycle_seg_in.machine_idle_status);
        db.update(groupIdx | 19, m_cycleSegTxData.cycle_seg_in.keyswitch_state);
        db.update(groupIdx | 20, m_cycleSegTxData.cycle_seg_in.real_time);
        db.update(groupIdx | 21, m_cycleSegTxData.cycle_seg_in.real_time_status);
        db.update(groupIdx | 22, m_cycleSegTxData.cycle_seg_in.timezone_offset);
        db.update(groupIdx | 23, m_cycleSegTxData.cycle_seg_in.total_fuel_high_res);
        db.update(groupIdx | 24, m_cycleSegTxData.cycle_seg_in.total_fuel_low_res);
        db.update(groupIdx | 25, m_cycleSegTxData.cycle_seg_in.fuel_rate);
        db.update(groupIdx | 26, m_cycleSegTxData.cycle_seg_in.ard_fuel_rate);
        db.update(groupIdx | 27, m_cycleSegTxData.cycle_seg_in.gps_latitude);
        db.update(groupIdx | 28, m_cycleSegTxData.cycle_seg_in.gps_longitude);
        db.update(groupIdx | 29, m_cycleSegTxData.cycle_seg_in.gps_status);
        db.update(groupIdx | 30, m_cycleSegTxData.cycle_seg_in.service_hour_meter);
        db.update(groupIdx | 31, m_cycleSegTxData.cycle_seg_in.payload_weight);
        db.update(groupIdx | 32, m_cycleSegTxData.cycle_seg_in.payload_weight_status);
        db.update(groupIdx | 33, m_cycleSegTxData.cycle_seg_in.payload_calc_method);
        db.update(groupIdx | 34, m_cycleSegTxData.cycle_seg_in.ext_force_normalized);
        db.update(groupIdx | 35, m_cycleSegTxData.cycle_seg_in.impl_operation_status);
        db.update(groupIdx | 36, m_cycleSegTxData.cycle_seg_in.engine_load_factor);

        db.update(groupIdx | 37, m_cycleSegTxData.cycle_seg_out.commit_segment_record);
        db.update(groupIdx | 38, m_cycleSegTxData.cycle_seg_out.segment_record_id);
        db.update(groupIdx | 39, m_cycleSegTxData.cycle_seg_out.segment_rec_start_sim_time);
        db.update(groupIdx | 40, m_cycleSegTxData.cycle_seg_out.segment_rec_duration);
        db.update(groupIdx | 41, m_cycleSegTxData.cycle_seg_out.segment_rec_distance);
        db.update(groupIdx | 42, m_cycleSegTxData.cycle_seg_out.segment_rec_start_real_time);
        db.update(groupIdx | 43, m_cycleSegTxData.cycle_seg_out.segment_rec_fuel_used);
        db.update(groupIdx | 44, m_cycleSegTxData.cycle_seg_out.segment_rec_latitude);
        db.update(groupIdx | 45, m_cycleSegTxData.cycle_seg_out.segment_rec_longitude);
        db.update(groupIdx | 46, m_cycleSegTxData.cycle_seg_out.segment_rec_idle_time);
        db.update(groupIdx | 47, m_cycleSegTxData.cycle_seg_out.segment_rec_hour_meter);
        db.update(groupIdx | 48, m_cycleSegTxData.cycle_seg_out.segment_rec_payload);
        db.update(groupIdx | 49, m_cycleSegTxData.cycle_seg_out.segment_rec_payload_calc_method);
        db.update(groupIdx | 50, m_cycleSegTxData.cycle_seg_out.commit_rec_gps);
        db.update(groupIdx | 51, m_cycleSegTxData.cycle_seg_out.segment_dig_state);
        db.update(groupIdx | 52, m_cycleSegTxData.cycle_seg_out.segment_last_completed_id);
        db.update(groupIdx | 53, m_cycleSegTxData.cycle_seg_out.segment_time_since_last_end);
        db.update(groupIdx | 54, m_cycleSegTxData.cycle_seg_out.segment_sequence_number);
        db.update(groupIdx | 55, m_cycleSegTxData.cycle_seg_out.keyswitch_override_flag);
        db.update(groupIdx | 56, m_cycleSegTxData.cycle_seg_out.segment_active_segment_id);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 90000 */
    if ( m_lpsSaJobMgrReqstChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 9;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command.value == cpm_common_interfaces::msg::JobMgrReqstChannelCommand::ZERO);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command.value == cpm_common_interfaces::msg::JobMgrReqstChannelCommand::MINUS_ONE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command.value == cpm_common_interfaces::msg::JobMgrReqstChannelCommand::CLEAR);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command.value == cpm_common_interfaces::msg::JobMgrReqstChannelCommand::STORE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command.value == cpm_common_interfaces::msg::JobMgrReqstChannelCommand::STANDBY_ACTIVATE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command.value == cpm_common_interfaces::msg::JobMgrReqstChannelCommand::STANDBY_DEACTIVATE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command.value == cpm_common_interfaces::msg::JobMgrReqstChannelCommand::TIPOFF_MODE_TOGGLE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command.value == cpm_common_interfaces::msg::JobMgrReqstChannelCommand::MANUAL_TIPOFF_ACTIVATE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command.value == cpm_common_interfaces::msg::JobMgrReqstChannelCommand::MANUAL_TIPOFF_DEACTIVATE);
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command.value == cpm_common_interfaces::msg::JobMgrReqstChannelCommand::WRITE_TIPOFF_TRIGGER_TYPE);
        db.update(groupIdx | offset++, (int)static_cast<int32_t>(m_lpsSaJobMgrReqstChannel.data_tipoff_trigger_type.value));
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command.value == cpm_common_interfaces::msg::JobMgrReqstChannelCommand::WRITE_TIPOFF_MODE);
        db.update(groupIdx | offset++, (int)static_cast<int32_t>(m_lpsSaJobMgrReqstChannel.data_tipoff_mode.value));
        db.update(groupIdx | offset++, m_lpsSaJobMgrReqstChannel.command.value == cpm_common_interfaces::msg::JobMgrReqstChannelCommand::REWEIGH);

        { // Target truck weight command?
            bool found = false;
            for (const auto& r : m_lpsSaJobMgrReqstChannel.requests) {
                if (cpm_common_interfaces::msg::LpsSaJobMgrReqst::WRITE_TRUCK_TARGET_WEIGHT == r.command) {
                    db.update(groupIdx | offset++, true);
                    db.update(groupIdx | offset++, r.arg2);
                    found = true;
                    break;
                }
            }
            if (!found) {
                // No target truck weight command.
                db.update(groupIdx | offset++, false);
                db.update(groupIdx | offset++, 0.f);
            }
        }

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: A0000 */
    if ( m_lpsSaJobMgrRespChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 10;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        /*
         * These were never working anyway so they are now just set to 0
         */
//        db.update(groupIdx | offset++, 0 /* ZeroResp */);
//        db.update(groupIdx | offset++, 0 /* MinusOneResp */);
//        db.update(groupIdx | offset++, 0 /* ClearResp */);
//        db.update(groupIdx | offset++, 0 /* StoreResp */);
//        db.update(groupIdx | offset++, 0 /* StandByActResp */);
//        db.update(groupIdx | offset++, 0 /* StandByDeActResp */);
//        db.update(groupIdx | offset++, 0 /* TipOffTruckPileToggleResp */);
//        db.update(groupIdx | offset++, 0 /* TipOffActResp */);
//        db.update(groupIdx | offset++, 0 /* TipOffDeactResp */);
//        db.update(groupIdx | offset++, 0 /* ReWeighResp */);
//        db.update(groupIdx | offset++, 0 /* TargetWeightResp */);
//        db.update(groupIdx | offset++, 0 /* TipOffTriggerTypeResp */);
//        db.update(groupIdx | offset++, 0 /* TipOffStateResp */);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: B0000 */
    if (m_lpsSaJobMgrDebugChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 11;
        static constexpr uint32_t groupIdx = index << 16;

        db.update(groupIdx | 0x00, m_lpsSaJobMgrDebugChannel.current_state);
        db.update(groupIdx | 0x01, m_lpsSaJobMgrDebugChannel.tipoff_assist_activation_count);

        db.update(groupIdx | 0xFF, updateCounter++);
    }

    /* index group: C0000 */
    if ( m_switchInputScs.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 12;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        // read store button press
        db.update(groupIdx | offset++, static_cast<int32_t>(m_switchInputScs.stg_values[3].value));

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: D0000 */
    if ( m_lpsSaNvmDataChannel.update() || !init_done)
    {
       static int updateCounter = 0;
       static constexpr uint32_t index = 13;
       static constexpr uint32_t groupIdx = index << 16;
       int offset = 0;

       // The expression below expands into a for-loop to DB_PUSH: raise_slow_empty_lift_heights[0], raise_slow_empty_lift_heights[1], ... , raise_slow_empty_lift_heights[10]
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_slow_empty_lift_heights, 11)

       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_slow_empty_pressures, 11)
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.lower_slow_empty_lift_heights, 11)
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.lower_slow_empty_pressures, 11)
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_slow_full_lift_heights, 11)
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_slow_full_pressures, 11)
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.lower_slow_full_lift_heights, 11)
       DB_PUSH_ARRAY(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.lower_slow_full_pressures, 11)
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_speed_empty_slow);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_speed_empty_fast);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_fast_delta_p_empty);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_speed_full_slow);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_speed_full_fast);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_main.raise_fast_delta_p_full);

       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.lift_full_lower_dc_inf_value);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.lift_full_raise_dc_inf_value);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.tilt_full_dump_dc_inf_value);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.tilt_full_rack_dc_inf_value);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.pcs_vel_slope);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.pcs_cal_weight);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.zero_weight);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.cal_adjust);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.temp_slope);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.empty_temp);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.full_temp);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.empty_bucket_weight_est);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.cal_adjust_temp);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.hyd_oil_type_index);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.tilt_dump_stop_angle_inf_value);
       DB_PUSH(m_lpsSaNvmDataChannel.lps_sa_nvm_calibration_data_debug.tilt_rack_stop_angle_inf_value);

       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.full_slow_imu_offset_final));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.full_slow_imu_offset_temp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.full_slow_imu_offset_temp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.full_slow_imu_offset_temp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.empty_slow_imu_offset_temp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.empty_slow_imu_offset_temp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.empty_slow_imu_offset_temp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.full_slow_lumped_weight_temp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.full_slow_lumped_weight_temp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.full_slow_lumped_weight_temp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.empty_slow_lumped_weight_temp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.empty_slow_lumped_weight_temp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.empty_slow_lumped_weight_temp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.empty_slow_imu_offset_final));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.full_slow_lumped_weight_final));
       DB_PUSH(static_cast<float>(m_lpsSaNvmDataChannel.imu_cal_results.empty_slow_lumped_weight_final));

       db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: E0000 */
    if ( m_lpsSaNvmOnTheFlyDataChannel.update() || !init_done)
    {
       static int updateCounter = 0;
       static constexpr uint32_t index = 14;
       static constexpr uint32_t groupIdx = index << 16;
       int offset = 0;

       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.status_flags.cal_in_progress));
       DB_PUSH(static_cast<uint32_t>(0)); // Placeholder for removed channel.
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.status_flags.empty_bkt_cal_done));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.status_flags.full_bkt_cal_done));

       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.hyd_oil_temp_met));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.enforce_raise_detent));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.enforce_lower_detent));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.raise_fast_vel_done));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.raise_slow_fit_done));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.raise_fast_fit_done));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.lower_slow_fit_done));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.internal_step));

       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_updates.lift_he_pres_stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_updates.lift_re_pres_stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_updates.lift_cyl_length_norm_stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_updates.hyd_oil_temp_stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_updates.lift_cyl_vel_stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_updates.tilt_cyl_length_norm_stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_updates.bkt_angle_stat));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_updates.lift_lever_info_lever_info_available));
       DB_PUSH(static_cast<uint32_t>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_updates.lift_lever_info_faulted));

       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.raise_num_points);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.lower_num_points);

       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.full_slow_imu_offset_final));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.full_slow_imu_offset_temp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.full_slow_imu_offset_temp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.full_slow_imu_offset_temp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.empty_slow_imu_offset_temp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.empty_slow_imu_offset_temp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.empty_slow_imu_offset_temp3));

       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.lps_cal_ovr_state);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.lift_bottom_flag);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.lift_top_flag);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.lps_cal_app_inf_cal_ovr_active);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.lps_cal_app_inf_lower_cmd_lmt);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.lps_cal_app_inf_raise_cmd_lmt);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.lift_faulted);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.lift_in_center);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.lift_in_lower_detent);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.lift_in_raise_detent);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.lift_valve_cmd_percent);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.cal_ovr_acknowledge);

       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.full_slow_lumped_weight_temp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.full_slow_lumped_weight_temp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.full_slow_lumped_weight_temp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.empty_slow_lumped_weight_temp1));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.empty_slow_lumped_weight_temp2));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.empty_slow_lumped_weight_temp3));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.empty_slow_imu_offset_final));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.full_slow_lumped_weight_final));
       DB_PUSH(static_cast<float>(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.curve_info.imu_cal_results.empty_slow_lumped_weight_final));

       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.tilt_overrides.cal_tilt_override_complete);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.tilt_overrides.cal_tilt_override_fail);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.tilt_overrides.count_of_samples);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.tilt_overrides.desired_tilt_extmm);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.tilt_overrides.lps_cal_tilt_ovr_start_request);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.tilt_overrides.lps_cal_tilt_ovr_state);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.tilt_overrides.tilt_dump_cmd_ovr);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.tilt_overrides.tilt_noise_max);
       DB_PUSH(m_lpsSaNvmOnTheFlyDataChannel.lps_sa_nvm_calibration_data_on_the_fly.cal_overrides.tilt_overrides.tilt_noise_min);
       
       db.update(groupIdx | 255, updateCounter++);

    }

    /* index group: Fxxxx - Work Order Assist */
    if ( m_workOrderAssistTxChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 15;
        static constexpr uint32_t groupIdx = index << 16;

        db.update(groupIdx | 0, m_workOrderAssistTxChannel.activity_detected);
        db.update(groupIdx | 1, m_workOrderAssistTxChannel.active_site_id);
        db.update(groupIdx | 2, static_cast<int32_t>(m_workOrderAssistTxChannel.active_job_id)); // Narrowing Conversion
        db.update(groupIdx | 3, m_workOrderAssistTxChannel.hub_service_tx_error_count);
        db.update(groupIdx | 4, m_workOrderAssistTxChannel.hub_service_tx_success_count);
        db.update(groupIdx | 5, m_workOrderAssistTxChannel.hub_service_rx_count);
        db.update(groupIdx | 6, m_workOrderAssistTxChannel.hub_service_comms_active);
        db.update(groupIdx | 7, m_workOrderAssistTxChannel.number_of_jobs);
        // ...
        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 100000 - Widgets Debug Data */
    if ( m_widgetsDebugdata.update() | !init_done ) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 16;
        static constexpr uint32_t groupIdx = index << 16;
        int offset = 0;

        db.update(groupIdx | offset++, m_widgetsDebugdata.distance.forward_mm);
        db.update(groupIdx | offset++, m_widgetsDebugdata.distance.reverse_mm);
        db.update(groupIdx | offset++, (bool)m_widgetsDebugdata.distance.status);
        db.update(groupIdx | offset++, m_widgetsDebugdata.rotation.forward);
        db.update(groupIdx | offset++, m_widgetsDebugdata.rotation.reverse);
        db.update(groupIdx | offset++, (bool)m_widgetsDebugdata.rotation.status);
        db.update(groupIdx | offset++, m_widgetsDebugdata.dig_time_current);
        db.update(groupIdx | offset++, m_widgetsDebugdata.traveling_loaded_revs);
        db.update(groupIdx | offset++, (int)static_cast<int32_t>(m_widgetsDebugdata.dig_state));
        db.update(groupIdx | offset++, m_widgetsDebugdata.ground_speed_info_speed);
        db.update(groupIdx | offset++, m_widgetsDebugdata.ground_speed_info_data_status);
        db.update(groupIdx | offset++, m_widgetsDebugdata.gear_info_gear);
        db.update(groupIdx | offset++, (int)m_widgetsDebugdata.gear_info_gear_status);
        // ...
        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 11xxxx - Display State */
    if ( m_displayStateChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 17;
        static constexpr uint32_t groupIdx = index << 16;

        db.update(groupIdx | 0, m_displayStateChannel.state.heartbeat_count);
        db.update(groupIdx | 1, m_displayStateChannel.state.service_mode_enable_code_entered);
        db.update(groupIdx | 2, m_displayStateChannel.state.in_service_mode);
        db.update(groupIdx | 3, m_displayStateChannel.state.document_id);
        // ...
        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 12xxxx - Tip-Off Assist */
    if ( m_tipoffModelTestPoints.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 18;
        static constexpr uint32_t groupIdx = index << 16;

        db.update(groupIdx | 0x00, m_tipoffModelTestPoints.toa_sfunc_out_raw_mass_tonne);
        db.update(groupIdx | 0x01, m_tipoffModelTestPoints.toa_payload_adjusted);
        db.update(groupIdx | 0x02, m_tipoffModelTestPoints.toa_sfunc_in_tilt_force);
        db.update(groupIdx | 0x03, m_tipoffModelTestPoints.toa_sfunc_in_lift_force);
        db.update(groupIdx | 0x04, m_tipoffModelTestPoints.toa_sfunc_in_grav_x);
        db.update(groupIdx | 0x05, m_tipoffModelTestPoints.toa_sfunc_in_grav_y);
        db.update(groupIdx | 0x06, m_tipoffModelTestPoints.toa_pfw_nl_notch_st_dev_est);
        db.update(groupIdx | 0x07, m_tipoffModelTestPoints.toa_pfw_nl_notch_mean_est);
        db.update(groupIdx | 0x08, m_tipoffModelTestPoints.toa_pfw_sec_latch);
        db.update(groupIdx | 0x09, m_tipoffModelTestPoints.toa_lw_lpf_post);
        db.update(groupIdx | 0x0A, m_tipoffModelTestPoints.toa_target_payload_final);
        db.update(groupIdx | 0x0B, m_tipoffModelTestPoints.toa_target_payload_status);
        db.update(groupIdx | 0x0C, m_tipoffModelTestPoints.toa_send_payload_arb);
        db.update(groupIdx | 0x0D, m_tipoffModelTestPoints.toa_imu_cal_pitch_angle);
        db.update(groupIdx | 0x0E, m_tipoffModelTestPoints.toa_app_number);
        db.update(groupIdx | 0x0F, m_tipoffModelTestPoints.toa_tilt_bore_dia);
        db.update(groupIdx | 0x10, m_tipoffModelTestPoints.toa_tilt_num_cyl);
        db.update(groupIdx | 0x11, m_tipoffModelTestPoints.toa_tilt_rod_dia);
        db.update(groupIdx | 0x12, m_tipoffModelTestPoints.toa_lift_bore_dia);
        db.update(groupIdx | 0x13, m_tipoffModelTestPoints.toa_lift_rod_dia);
        db.update(groupIdx | 0x14, m_tipoffModelTestPoints.toa_rated_payload);
        db.update(groupIdx | 0x15, m_tipoffModelTestPoints.toa_tool_bc_length);
        db.update(groupIdx | 0x16, m_tipoffModelTestPoints.toa_payload_anc_zeroed);
        db.update(groupIdx | 0x17, m_tipoffModelTestPoints.toa_payload_anc_adjusted);

        db.update(groupIdx | 0x18, m_tipoffModelTestPoints.toa_pfw_sec_payload);
        db.update(groupIdx | 0x19, m_tipoffModelTestPoints.toa_pfw_sec_status);
        db.update(groupIdx | 0x1A, m_tipoffModelTestPoints.toa_pfw_sec_st_dev);
        db.update(groupIdx | 0x1B, m_tipoffModelTestPoints.toa_pfw_nl_st_dev_est);
        db.update(groupIdx | 0x1C, m_tipoffModelTestPoints.toa_pfw_unsec_status);
        db.update(groupIdx | 0x1D, m_tipoffModelTestPoints.toa_pfw_unsec_bound_lower);
        db.update(groupIdx | 0x1E, m_tipoffModelTestPoints.toa_pfw_unsec_bound_upper);
        db.update(groupIdx | 0x1F, m_tipoffModelTestPoints.toa_lw_spill_rate);
        db.update(groupIdx | 0x20, m_tipoffModelTestPoints.toa_lw_status);
        db.update(groupIdx | 0x21, m_tipoffModelTestPoints.toa_raw_dist);
        db.update(groupIdx | 0x22, m_tipoffModelTestPoints.toa_raw_payload);
        db.update(groupIdx | 0x23, m_tipoffModelTestPoints.toa_payload_zeroed);
        db.update(groupIdx | 0x24, m_tipoffModelTestPoints.toa_pfw_is_warm);
        db.update(groupIdx | 0x25, m_tipoffModelTestPoints.toa_pfw_sec_is_secure);
        db.update(groupIdx | 0x26, m_tipoffModelTestPoints.toa_pfw_sec_is_no_sliding);
        db.update(groupIdx | 0x27, m_tipoffModelTestPoints.toa_pfw_sec_is_no_collapsing);
        db.update(groupIdx | 0x28, m_tipoffModelTestPoints.toa_pfw_sec_is_racked);
        db.update(groupIdx | 0x29, m_tipoffModelTestPoints.toa_pfw_sec_min_bucket_ang);
        db.update(groupIdx | 0x2A, m_tipoffModelTestPoints.toa_pfw_mc_ok);
        db.update(groupIdx | 0x2B, m_tipoffModelTestPoints.toa_pfw_mc_maybe_stalled);
        db.update(groupIdx | 0x2C, m_tipoffModelTestPoints.toa_pfw_mc_maybe_rack_stall);
        db.update(groupIdx | 0x2D, m_tipoffModelTestPoints.toa_pfw_mc_maybe_grounded);
        db.update(groupIdx | 0x2E, m_tipoffModelTestPoints.toa_stat_payload_nl_notch_one_up);
        db.update(groupIdx | 0x2F, m_tipoffModelTestPoints.toa_stat_payload_nl_notch_one_low);
        db.update(groupIdx | 0x30, m_tipoffModelTestPoints.toa_stat_payload_nl_notch_one_size);
        db.update(groupIdx | 0x31, m_tipoffModelTestPoints.toa_stat_payload_nl_notch_two_up);
        db.update(groupIdx | 0x32, m_tipoffModelTestPoints.toa_stat_payload_nl_notch_two_low);
        db.update(groupIdx | 0x33, m_tipoffModelTestPoints.toa_stat_payload_nl_notch_two_size);
        db.update(groupIdx | 0x34, m_tipoffModelTestPoints.toa_stat_payload_nl_one_up);
        db.update(groupIdx | 0x35, m_tipoffModelTestPoints.toa_stat_payload_nl_one_low);
        db.update(groupIdx | 0x36, m_tipoffModelTestPoints.toa_stat_payload_nl_one_size);
        db.update(groupIdx | 0x37, m_tipoffModelTestPoints.toa_stat_payload_nl_two_up);
        db.update(groupIdx | 0x38, m_tipoffModelTestPoints.toa_stat_payload_nl_two_low);
        db.update(groupIdx | 0x39, m_tipoffModelTestPoints.toa_stat_payload_nl_two_size);
        db.update(groupIdx | 0x3A, m_tipoffModelTestPoints.toa_pfw_nl_mean_est);
        db.update(groupIdx | 0x3B, m_tipoffModelTestPoints.toa_pfw_payload_filt_final);
        db.update(groupIdx | 0x3C, m_tipoffModelTestPoints.toa_pfw_payload_notch_filt_final);
        db.update(groupIdx | 0x3D, m_tipoffModelTestPoints.toa_pfw_payload_notch_post);
        db.update(groupIdx | 0x3E, m_tipoffModelTestPoints.toa_pfw_latch_invalidate);
        db.update(groupIdx | 0x3F, m_tipoffModelTestPoints.toa_imu_raw_eef_accl_x);
        db.update(groupIdx | 0x40, m_tipoffModelTestPoints.toa_imu_raw_eef_accl_y);
        db.update(groupIdx | 0x41, m_tipoffModelTestPoints.toa_imu_raw_eef_accl_z);
        db.update(groupIdx | 0x42, m_tipoffModelTestPoints.toa_imu_neef_grav_x);
        db.update(groupIdx | 0x43, m_tipoffModelTestPoints.toa_imu_neef_grav_y);
        db.update(groupIdx | 0x44, m_tipoffModelTestPoints.toa_imu_neef_grav_z);
        db.update(groupIdx | 0x45, m_tipoffModelTestPoints.toa_imu_neef_pitch);
        db.update(groupIdx | 0x46, m_tipoffModelTestPoints.toa_target_comp_margin);
        db.update(groupIdx | 0x47, m_tipoffModelTestPoints.toa_target_payload_post_comp);
        db.update(groupIdx | 0x48, m_tipoffModelTestPoints.toa_target_payload_pre_comp);
        db.update(groupIdx | 0x49, m_tipoffModelTestPoints.toa_stat_payload_secure_two_size);
        db.update(groupIdx | 0x4A, m_tipoffModelTestPoints.toa_stat_payload_secure_one_upper);
        db.update(groupIdx | 0x4B, m_tipoffModelTestPoints.toa_stat_payload_secure_one_lower);
        db.update(groupIdx | 0x4C, m_tipoffModelTestPoints.toa_stat_payload_secure_one_size);
        db.update(groupIdx | 0x4D, m_tipoffModelTestPoints.toa_stat_payload_secure_two_upper);
        db.update(groupIdx | 0x4E, m_tipoffModelTestPoints.toa_stat_payload_secure_two_lower);
        db.update(groupIdx | 0x4F, m_tipoffModelTestPoints.toa_send_cpm_live_payload);
        db.update(groupIdx | 0x4F, m_tipoffModelTestPoints.toa_tool_bc_angle);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 13xxxx - AutonomyConditionsDiagnosticsTX */
    if ( m_autonomyConditionDiagnosticsTxChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 19;
        static constexpr uint32_t groupIdx = index << 16;

        db.update(groupIdx | 0x00, m_autonomyConditionDiagnosticsTxChannel.display_ethernet_bad);
        db.update(groupIdx | 0x01, m_autonomyConditionDiagnosticsTxChannel.product_link_ethernet_bad);

        db.update(groupIdx | 255, updateCounter++);
    }

    /* index group: 14xxxx - BEMSimMgrState */
    if ( m_BemSimDebugChannel.update() || !init_done) {
        static int updateCounter = 0;
        static constexpr uint32_t index = 20;
        static constexpr uint32_t groupIdx = index << 16;
        // Added for BEM Simulator
        db.update(groupIdx | 0x00, m_BemSimDebugChannel.cnfg.charge_mode);
        db.update(groupIdx | 0x01, m_BemSimDebugChannel.cnfg.start_charge);
        db.update(groupIdx | 0x02, m_BemSimDebugChannel.total_fuel_used);
        db.update(groupIdx | 0x03, m_BemSimDebugChannel.cnfg.last_discharge_rate);
        db.update(groupIdx | 0x04, m_BemSimDebugChannel.cnfg.bem_sim_enabled);
        db.update(groupIdx | 0x05, m_BemSimDebugChannel.cnfg.charger_capacity);
        db.update(groupIdx | 0x06, m_BemSimDebugChannel.cnfg.engine_derate_enabled);
        db.update(groupIdx | 0x07, m_BemSimDebugChannel.charge_level);
        db.update(groupIdx | 0x08, m_BemSimDebugChannel.discharge_rate);
        db.update(groupIdx | 0x09, m_BemSimDebugChannel.derate_engine_cmd);
        db.update(groupIdx | 0x0A, m_BemSimDebugChannel.derate_engine_rpm);
        db.update(groupIdx | 0x0B, m_BemSimDebugChannel.charge_rate);
        db.update(groupIdx | 0x0C, m_BemSimDebugChannel.time_to_charged);
        db.update(groupIdx | 0x0D, m_BemSimDebugChannel.time_to_discharged);

        db.update(groupIdx | 255, updateCounter++);

    }

    { /* index group: 15xxxx - Datalink Inputs */
        static constexpr uint32_t index = 21;
        static constexpr uint32_t groupIdx = index << 16;

        static uint8_t tirePressureReceiverAmbientRFLevel = 0;
        static uint8_t tireLocation = 0;
        static uint8_t tireRefPressure = 0; // 8 kPa/bit
        static uint8_t tirePressure = 0; // 8 kPa/bit
        static uint8_t tireInfoAge = 255; // 1 minute/bit
        static uint8_t tireRFSignal = 127; // log2 RF level 1 count/bit
        static uint32_t tireSensorSN = 0;

        bool receivedData = false;

        if (nullptr != dataLinkDataInput) {
            weigh_app_interfaces::msg::DataLinkData dlData;
            while (dataLinkDataInput->get(dlData)) {
                for (auto& dlParam : dlData.params) {
                    // Look for tire pressure monitoring receiver data parameter
                    if ((weigh_app_interfaces::msg::DataLinkParam::IDENTIFIER_TYPE_PID == dlParam.identifier_type) &&
                            (0x0800 == dlParam.param_id) &&
                            (dlParam.pid_data_received)) {

                        // We have received new information about this pid
                        if (0 == dlParam.last_value_dsi) {
                            const std::vector<uint8_t>& data = dlParam.var_param_block;
                            if (data.size() >= 7) {
                                //RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Length = %d, Ambient RF Level = %d", data.size(), data[4]);
                                //RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "%d, %d, %d, %d, %d, %d, %d", data[0], data[1], data[2], data[3], data[4], data[5], data[6]);
                                tirePressureReceiverAmbientRFLevel = data[4];
                                receivedData = true;
                            }
                            else {
                                //RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Length = %d", data.size());
                                tirePressureReceiverAmbientRFLevel = 0;
                                receivedData = true;
                            }
                        }
                        else {
                            //RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "We have a DSI for tire monitoring data = %d.", dlParam.last_value_dsi);
                            tirePressureReceiverAmbientRFLevel = 0;
                            receivedData = true;
                        }
                    }

                    // Look for the Tire Pressure Reference Information - TPRI PGN
                    else if ((weigh_app_interfaces::msg::DataLinkParam::IDENTIFIER_TYPE_PUBLIC_PGN == dlParam.identifier_type) &&
                            (64953 == dlParam.param_id) &&
                            (dlParam.pid_data_received) &&
                            (weigh_app_interfaces::msg::DataLinkParam::VAR_LENGTH_PARAM_TYPE_PGN == dlParam.var_length_param_type)) {
                        uint16_t dsi = dlParam.last_value_dsi;
                        uint8_t len = static_cast<uint8_t>(dlParam.var_param_block.size());
                        const uint8_t* data = dlParam.var_param_block.data();

                        if ((nullptr != data) && (kDsiCodeOk == dsi) && (len >= 8)) {
                            XCP_UNPACK_LE_8(data, tireLocation);
                            XCP_UNPACK_LE_8(data, tireRefPressure);
                            XCP_UNPACK_LE_8(data, tirePressure);
                            XCP_UNPACK_LE_8(data, tireInfoAge);
                            XCP_UNPACK_LE_8(data, tireRFSignal);
                            tireRFSignal = tireRFSignal & 0x7F;
                            XCP_UNPACK_LE_24(data, tireSensorSN);
                        }
                        else {
                            // Problem
                            tireLocation = 0;
                            tireRefPressure = 0;
                            tirePressure = 0;
                            tireInfoAge = 255;
                            tireRFSignal = 127;
                            tireSensorSN = 0;
                        }
                        receivedData = true;
                    }
                }
            }
        }

        if ((!init_done) || (receivedData)) {
            static int updateCounter = 0;
            db.update(groupIdx | 0x00, tirePressureReceiverAmbientRFLevel);
            db.update(groupIdx | 0x01, tireLocation);
            db.update(groupIdx | 0x02, tireRefPressure);
            db.update(groupIdx | 0x03, tirePressure);
            db.update(groupIdx | 0x04, tireInfoAge);
            db.update(groupIdx | 0x05, tireRFSignal);
            db.update(groupIdx | 0x06, tireSensorSN);
            db.update(groupIdx | 255, updateCounter++);
        }
    }

    /* mark init done */
    if (!init_done) {
        init_done = true;
    }

    return retVal;
  }


  ///////////////////////////////////////////////////////////////////////////////
  /// @brief ROS2 input interfaces injected by the owner. They are created and
  ///        deleted by XcpServerTask; this class does not own them.
  ///////////////////////////////////////////////////////////////////////////////
  struct RosInputs
  {
    ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::SystemHardwareHealthStorage>* systemHardwareHealth = nullptr;
    ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighReqstChannel>* weighReqst = nullptr;
    ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighRespChannel>* weighResp = nullptr;
    ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaWeighTxChannel>* weighTx = nullptr;
    ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::LpsSaWeighDebugChannel>* weighDebug = nullptr;
    ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::LpsSaWeighInitDebugChannel>* weighInitDebug = nullptr;
    ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::LpsSaNvmCalDataChannel>* nvmCalData = nullptr;
    ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::LpsSaNvmCalOnTheFlyDataChannel>* nvmCalOnTheFlyData = nullptr;
    ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrTxChannel>* jobMgrTx = nullptr;
    ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::PwmInputChannels>* pwmInputChannels = nullptr;
    ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaJobMgrReqstChannel>* jobMgrReqst = nullptr;
    ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrRespChannel>* jobMgrResp = nullptr;
    ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::LpsSaJobMgrDebugChannel>* jobMgrDebug = nullptr;
    ros2_wrapper::RosInputInterface<job_mgr_interfaces::msg::SwitchInputScs>* switchInput = nullptr;
    ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::CycleSegTxChannel>* cycleSegTx = nullptr;
    ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::WorkOrderAssistTxChannel>* workOrderAssistTx = nullptr;
    ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::TipoffModelTestPoints>* tipoffModelTestPoints = nullptr;
    ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::AutonomyConditionDiagnosticsTxChannel>* autonomyConditionDiagnosticsTx = nullptr;
    ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaUIBemSimStateInterface>* bemSimState = nullptr;
    ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::LpsSaUIDisplayStateInterface>* displayState = nullptr;
    ros2_wrapper::RosInputInterface<cpm_common_interfaces::msg::WidgetsDebugData>* widgetsDebugData = nullptr;
    ros2_wrapper::RosInputInterface<weigh_app_interfaces::msg::DataLinkData>* dataLinkData = nullptr;
  };

  ///////////////////////////////////////////////////////////////////////////////
  /// @brief Run "initReadInterface" on all of the scs channels in the structure
  ///        (ROS2: bind each channel to its injected ROS2 input). The number
  ///        before cs is the AIS channel queueSize (interfaces_Loaders.rb,
  ///        interfaces_CpmCommon.rb, interfaces_coretech.rb; default 1).
  ///        cs holds the former ScsRxTimeouts section ("<Input>_rxTimeout_sec").
  ///
  /// @return true if all interfaces were successfully configured, false if any failed
  ///////////////////////////////////////////////////////////////////////////////
  bool initReadInterface( const RosInputs& in, const std::map<std::string, double>& cs )
  {
    bool retVal = true;

    if (!m_systemHardwareHealth.initReadInterface("SystemHardwareHealthInput", in.systemHardwareHealth, 100, cs)) {
        retVal = false;
    }

    if ( !m_lpsSaWeighReqstChannel.initReadInterface("LpsSaWeighReqstChannelInput", in.weighReqst, 20, cs) ) retVal = false;
    if ( !m_lpsSaWeighRespChannel.initReadInterface("LpsSaWeighRespChannelInput", in.weighResp, 20, cs) ) retVal = false;
    if ( !m_lpsSaWeighTxChannel.initReadInterface("LpsSaWeighTxChannelInput", in.weighTx, 20, cs) ) retVal = false;
    if ( !m_lpsSaWeighDebugChannel.initReadInterface("LpsSaWeighDebugChannelInput", in.weighDebug, 1, cs) ) retVal = false;
    if ( !m_lpsSaWeighInitDebugChannel.initReadInterface("LpsSaWeighInitDebugChannelInput", in.weighInitDebug, 1, cs) ) retVal = false;
    if ( !m_lpsSaNvmDataChannel.initReadInterface("LpsSaNvmCalDataChannelInput", in.nvmCalData, 1, cs) ) retVal = false;
    if ( !m_lpsSaNvmOnTheFlyDataChannel.initReadInterface("LpsSaNvmCalOnTheFlyDataChannelInput", in.nvmCalOnTheFlyData, 3, cs) ) retVal = false;
    if ( !m_lpsSaJobMgrTxChannel.initReadInterface("LpsSaJobMgrTxChannelInput", in.jobMgrTx, 20, cs) ) retVal = false;
    if ( !m_pwmInputChannels.initReadInterface("PwmInputChannelsInput", in.pwmInputChannels, 30, cs) ) retVal = false;
    // MachineInput: no task publishes the Machine channel (MachineOutput is bound nowhere) and
    // m_machine is never read, so there is no ROS2 topic to subscribe to. m_machine keeps its defaults.
    if ( !m_lpsSaJobMgrReqstChannel.initReadInterface("LpsSaJobMgrReqstChannelInput", in.jobMgrReqst, 20, cs) ) retVal = false;
    if ( !m_lpsSaJobMgrRespChannel.initReadInterface("LpsSaJobMgrRespChannelInput", in.jobMgrResp, 20, cs) ) retVal = false;
    if ( !m_lpsSaJobMgrDebugChannel.initReadInterface("LpsSaJobMgrDebugChannelInput", in.jobMgrDebug, 1, cs) ) retVal = false;
    if ( !m_switchInputScs.initReadInterface("SwitchInputScsInput", in.switchInput, 1, cs) ) retVal = false;
    if ( !m_cycleSegTxData.initReadInterface("CycleSegTxChannelInput", in.cycleSegTx, 1, cs) ) retVal = false;
    if ( !m_workOrderAssistTxChannel.initReadInterface("WorkOrderAssistTxInput", in.workOrderAssistTx, 5, cs) ) retVal = false;
    if ( !m_tipoffModelTestPoints.initReadInterface("TipoffModelTestPointsInput", in.tipoffModelTestPoints, 20, cs) ) retVal = false;
    if ( !m_autonomyConditionDiagnosticsTxChannel.initReadInterface("AutonomyConditionDiagnosticsTxInput", in.autonomyConditionDiagnosticsTx, 5, cs) ) retVal = false;
    if ( !m_BemSimDebugChannel.initReadInterface("BEMSimStateInput", in.bemSimState, 1, cs) ) retVal = false;
    if ( !m_displayStateChannel.initReadInterface("DisplayStateInput", in.displayState, 1, cs) ) retVal = false;
    if ( !m_widgetsDebugdata.initReadInterface("WidgetsDebugDataInput", in.widgetsDebugData, 20, cs) ) retVal = false;
    if ( !m_BemSimDebugChannel.initReadInterface("BEMSimStateInput", in.bemSimState, 1, cs) ) { retVal = false; }

    if (nullptr != in.dataLinkData) {
        m_dataLinkDataAdapter.bind(in.dataLinkData, 30);
        dataLinkDataInput = &m_dataLinkDataAdapter;
    }
    if(nullptr == dataLinkDataInput) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "DataLinkDataInput Interface not configured.");
        retVal = false;
    }

    return retVal;
  }

  ///////////////////////////////////////////////////////////////////////////////
  /// @brief Drop every injected ROS2 input. Call before the owner deletes them.
  ///////////////////////////////////////////////////////////////////////////////
  void stop()
  {
    m_systemHardwareHealth.stop();
    m_lpsSaWeighReqstChannel.stop();
    m_lpsSaWeighRespChannel.stop();
    m_lpsSaWeighDebugChannel.stop();
    m_lpsSaWeighInitDebugChannel.stop();
    m_lpsSaWeighTxChannel.stop();
    m_lpsSaNvmDataChannel.stop();
    m_lpsSaNvmOnTheFlyDataChannel.stop();
    m_lpsSaJobMgrTxChannel.stop();
    m_pwmInputChannels.stop();
    m_machine.stop();
    m_lpsSaJobMgrReqstChannel.stop();
    m_lpsSaJobMgrRespChannel.stop();
    m_lpsSaJobMgrDebugChannel.stop();
    m_switchInputScs.stop();
    m_workOrderAssistTxChannel.stop();
    m_displayStateChannel.stop();
    m_widgetsDebugdata.stop();
    m_cycleSegTxData.stop();
    m_tipoffModelTestPoints.stop();
    m_autonomyConditionDiagnosticsTxChannel.stop();
    m_BemSimDebugChannel.stop();
    m_dataLinkDataAdapter.unbind();
    dataLinkDataInput = nullptr;
  }

};

#endif /*XCPSCSINPUTS_H_*/
