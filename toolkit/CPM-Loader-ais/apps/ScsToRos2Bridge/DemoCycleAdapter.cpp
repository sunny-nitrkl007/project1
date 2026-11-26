#include "DemoCycleAdapter.h"
#include "ROS2Logger.hpp"
#include <algorithm>
#include <exception>

#define DEMO_COMMAND_MATCH(name) static_assert(static_cast<uint8_t>(DemoAppReqstCommand::name) == \
    demo_app_interfaces::msg::DemoAppRequest::name, "Demo command enum mismatch")
DEMO_COMMAND_MATCH(WRITE_LIFT_POSITION);
DEMO_COMMAND_MATCH(WRITE_LIFT_POSITION_RATE);
DEMO_COMMAND_MATCH(WRITE_TILT_POSITION);
DEMO_COMMAND_MATCH(WRITE_TILT_POSITION_RATE);
DEMO_COMMAND_MATCH(WRITE_PAYLOAD);
DEMO_COMMAND_MATCH(WRITE_PAYLOAD_RATE);
DEMO_COMMAND_MATCH(DIG);
DEMO_COMMAND_MATCH(WRW);
DEMO_COMMAND_MATCH(DUMP);
DEMO_COMMAND_MATCH(LLW);
DEMO_COMMAND_MATCH(PDUMP);
DEMO_COMMAND_MATCH(CARRY);
DEMO_COMMAND_MATCH(NONE);
#undef DEMO_COMMAND_MATCH

bool DemoCycleAdapter::initialize(const rclcpp::Node::SharedPtr& node)
{
    node_ = node;
    if (!task::InterfaceDb::bind("DemoAppReqstChannelInput", requestsIn_) ||
        !task::InterfaceDb::bind("DemoAppTxChannelOutput", txOut_) ||
        !task::InterfaceDb::bind("DataLinkDataOutput", dataOut_)) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo bridge SCS bindings missing");
        return false;
    }
    if (!initializeDataLinkData()) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo DataLinkData registration failed");
        return false;
    }
    try {
        requestsOut_ = node_->create_publisher<demo_app_interfaces::msg::DemoAppRequestBatch>(
                "demo_app_requests", rclcpp::QoS(rclcpp::KeepLast(20)).reliable().durability_volatile());
        cycleIn_ = node_->create_subscription<demo_app_interfaces::msg::DemoAppCycle>(
                "demo_app_cycle", rclcpp::QoS(rclcpp::KeepLast(30)).reliable().durability_volatile(),
                [this](demo_app_interfaces::msg::DemoAppCycle::ConstSharedPtr cycle,
                       const rclcpp::MessageInfo& info) { receive(*cycle, info); });
    } catch (const std::exception& error) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo ROS initialization failed: %s", error.what());
        return false;
    }
    return true;
}

bool DemoCycleAdapter::initializeDataLinkData()
{
    const uint32_t ids[] = {0x0045, 0xD10EE7, 0xD11884, 61444, 0xD1000E, 0xFE5D};
    const uint32_t sids[] = {0x2E, 0x2E, 0x2E, 0x00, 0x28, 0x00};
    const decltype(CDL2_I16_DSI) types[] = {
        CDL2_I16_DSI, CDL2_U8_DSI, CDL2_U8_DSI, CDL2_VAR_NO_DSI, CDL2_U16_DSI, CDL2_U32_DSI};
    for (size_t i = 0; i < params_.size(); ++i) {
        auto& param = params_[i];
        param.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_CDL);
        param.SetParamIdentifierType(i == 3 ? DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN :
                                            DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
        param.SetParameterType(types[i]);
        if (i == 3) {
            param.SetVarLengthParamType(VarLengthDataLinkParamFactory::PGN);
        }
        param.SetParamId(ids[i]);
        param.SetSid(sids[i]);
        param.SetScaling(i == 5 ? 0.001 : 1.0);
        param.SetOffset(0);
        if (!data_.AddDataLinkParam(param)) {
            return false;
        }
    }
    return true;
}

bool DemoCycleAdapter::accept(const demo_app_interfaces::msg::DemoAppCycle& cycle,
                             const rclcpp::MessageInfo& info)
{
    if (cycle.session_id.empty() || cycle.session_id.size() > 256 || cycle.sequence == 0) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Invalid Demo session/sequence");
        return false;
    }
    std::array<uint8_t, RMW_GID_STORAGE_SIZE> gid;
    const auto& source = info.get_rmw_message_info().publisher_gid;
    std::copy(source.data, source.data + gid.size(), gid.begin());
    if (std::all_of(gid.begin(), gid.end(), [](uint8_t byte) { return byte == 0; })) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo producer identity unavailable");
        failed_ = true;
        return false;
    }
    if (retiredSessions_.count(cycle.session_id)) {
        RCLCPP_WARN(ROS2Logger::Instance().GetLogger(), "Rejected retired Demo session %s", cycle.session_id.c_str());
        return false;
    }
    if (!session_.empty() && cycle.session_id != session_) {
        if (gid == producer_) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo session changed without producer restart");
            failed_ = true;
            return false;
        }
        if (retiredSessions_.size() == 1024) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo session history limit reached; refusing unsafe eviction");
            failed_ = true;
            return false;
        }
        retiredSessions_.insert(session_);
        RCLCPP_WARN(ROS2Logger::Instance().GetLogger(), "Demo producer restart: %s -> %s", session_.c_str(), cycle.session_id.c_str());
        sequence_ = 0;
        data_ = DataLinkData();
        params_ = std::array<DataLinkParam, 6>();
        if (!initializeDataLinkData()) {
            failed_ = true;
            return false;
        }
    } else if (!session_.empty() && gid != producer_) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Multiple Demo producers for one session");
        failed_ = true;
        return false;
    }
    if (cycle.sequence <= sequence_) {
        RCLCPP_WARN(ROS2Logger::Instance().GetLogger(), "Rejected Demo duplicate/regression: %llu after %llu",
                    static_cast<unsigned long long>(cycle.sequence), static_cast<unsigned long long>(sequence_));
        return false;
    }
    if (cycle.sequence - sequence_ > 1) {
        RCLCPP_WARN(ROS2Logger::Instance().GetLogger(), "Demo cycle gap: %llu missing before %llu",
                    static_cast<unsigned long long>(cycle.sequence - sequence_ - 1),
                    static_cast<unsigned long long>(cycle.sequence));
    }
    session_ = cycle.session_id;
    producer_ = gid;
    sequence_ = cycle.sequence;
    return true;
}

void DemoCycleAdapter::receive(const demo_app_interfaces::msg::DemoAppCycle& cycle,
                              const rclcpp::MessageInfo& info)
{
    if (failed_) {
        return;
    }
    try {
        if (node_->count_publishers("demo_app_cycle") > 1) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo cycle requires exactly one producer");
            failed_ = true;
            return;
        }
        if (!accept(cycle, info)) {
            return;
        }
        params_[0].SetLastValue(cycle.hydraulic_oil_temperature, 0);
        params_[2].SetLastValue(cycle.sea_level_installation, 0);
        params_[1].SetLastValue(cycle.production_measurement, 0);
        params_[3].SetVarLengthParamValue(cycle.engine_speed_pgn.data(),
                                        cycle.engine_speed_pgn.size(), DataLinkParam::DSI_CODE_OK());
        params_[4].SetLastValue(cycle.service_mode, DataLinkParam::DSI_CODE_OK());
        params_[5].SetLastValue(cycle.total_fuel_used, DataLinkParam::DSI_CODE_OK());
        const size_t order[] = {0, 2, 1, 3, 4, 5};
        for (size_t i : order) {
            if (!data_.UpdateDataLinkParam(params_[i])) {
                RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo DataLinkData update failed");
                failed_ = true;
                return;
            }
        }
        try {
            if (!dataOut_->publish(data_)) {
                RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo DLD SCS publish failed; continuing Tx without cycle replay");
            }
        } catch (const std::exception& error) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo DLD SCS publish threw: %s; continuing without replay", error.what());
        } catch (...) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo DLD SCS publish threw; continuing without replay");
        }
        data_.HandleDataLinkDataMap();
        data_.ClearDlpDiagInfo();
        try {
            if (!txOut_->publish(convertTx(cycle.tx))) {
                RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo Tx SCS publish failed; next cycle will continue without replay");
            }
        } catch (const std::exception& error) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo Tx SCS publish threw: %s; next cycle will continue", error.what());
        } catch (...) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo Tx SCS publish threw; next cycle will continue");
        }
    } catch (const std::exception& error) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo cycle failed without replay: %s", error.what());
        failed_ = true;
    }
}

bool DemoCycleAdapter::executive()
{
    if (failed_) {
        return false;
    }
    try {
        DemoAppReqstChannel request;
        for (size_t i = 0; i < 20 && requestsIn_->get(request); ++i) {
            requestsOut_->publish(convertRequests(request));
        }
    } catch (const std::exception& error) {
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Demo request batch forwarding failed: %s", error.what());
        failed_ = true;
    }
    return !failed_;
}

demo_app_interfaces::msg::DemoAppRequestBatch
DemoCycleAdapter::convertRequests(const DemoAppReqstChannel& scs)
{
    demo_app_interfaces::msg::DemoAppRequestBatch ros;
    ros.enabled = scs.data.enabled;
    ros.requests.reserve(scs.requests.size());
    for (const auto& request : scs.requests) {
        demo_app_interfaces::msg::DemoAppRequest converted;
        converted.command = static_cast<uint8_t>(request.command);
        converted.arg = request.liftposition();
        converted.arg1 = request.dig();
        ros.requests.push_back(converted);
    }
    return ros;
}

DemoAppTxChannel DemoCycleAdapter::convertTx(const weigh_app_interfaces::msg::DemoAppTxChannel& ros)
{
    DemoAppTxChannel scs;
    scs.liftposition = ros.liftposition;
    scs.liftposition_rate = ros.liftposition_rate;
    scs.tiltposition = ros.tiltposition;
    scs.tiltposition_rate = ros.tiltposition_rate;
    scs.payload = ros.payload;
    scs.payload_rate = ros.payload_rate;
    scs.dig = ros.dig;
    scs.wrw = ros.wrw;
    scs.llw = ros.llw;
    scs.dump = ros.dump;
    scs.pdump = ros.pdump;
    scs.rack = ros.rack;
    scs.carry = ros.carry;
    scs.weight1 = ros.weight1;
    scs.pres_lift_he_demo = ros.pres_lift_he_demo;
    scs.pres_lift_re_demo = ros.pres_lift_re_demo;
    scs.angle_lift_demo = ros.angle_lift_demo;
    scs.angle_AFE_demo = ros.angle_afe_demo;
    scs.angle_ABC_demo = ros.angle_abc_demo;
    return scs;
}
