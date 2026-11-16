/*******************************************************************************
 ** @attention COPYRIGHT (C) 2013-2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
 **
 ** @file    LpsAdvCANProcess.cpp
 **
 ** @brief   This reads the Machineinput Interface for poseTask
 *******************************************************************************/

/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/
#include <cstring>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <fcntl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <unistd.h>
#include <oel_pack.h>
#include "ROS2Logger.hpp"
#include <catdllib_fid_def.h>

#include "LpsAdvCANProcess.h"

/*******************************************************************************
 ** -- #Define, Struct's, Typedef's, Enum's --
 *******************************************************************************/

/*******************************************************************************
 ** -- Function Prototypes --
 *******************************************************************************/

/*******************************************************************************
 ** -- Symbols --
 *******************************************************************************/

/*******************************************************************************
 ** -- Start of code for this file --
 *******************************************************************************/


/******************************************************************************
FUNCTION NAME:LpsAdvCANProcess constructor
DESCRIPTION: LpsAdvCANProcess constructor for initializes an instance of its class
PARAMETER DESCRIPTION:  task name is passed
RETURN VALUE:  No return Value form constructor
*******************************************************************************/
LpsAdvCANProcess::LpsAdvCANProcess( ):
    CAN734_count(0),
    CAN733_count(0),
    dropped(0),
    socket_(-1),
    init_flag_(false),
    lastMsgId_(0),
    CAN734Received_(false),
    CAN733Received_(false),
    lift_he_pressure_(0),
    lift_re_pressure_(0),
    lift_valve_cmd_(0),
    tilt_valve_cmd_(0),
    cal_override_acknowledge_(0),
    lift_lever_status_(0),
    tilt_linkage_dc_(0),
    lift_linkage_dc_(0)
{
}

/******************************************************************************
FUNCTION NAME:LpsAdvCANProcess destructor
DESCRIPTION: LpsAdvCANProcess destructor for deallocating an instance of its class
PARAMETER DESCRIPTION: No parameter
RETURN VALUE:   No return Value form destructor
*******************************************************************************/
LpsAdvCANProcess::~LpsAdvCANProcess()
{
    if (socket_ >= 0) {
        close(socket_);
        socket_ = -1;
    }
}

/******************************************************************************
FUNCTION NAME:initialize
DESCRIPTION: SCS channel is initialized
PARAMETER DESCRIPTION:  No parameter
RETURN VALUE:  Boolean
*******************************************************************************/
bool LpsAdvCANProcess::init( )
{
    bool success = true;
	RCLCPP_INFO(ROS2Logger::Instance().GetLogger(), "LpsAdvCANProcess::initialize" );

	// Close if already open.
	if (socket_ >= 0) {
	    close(socket_);
	    socket_ = -1;
	}

	// Not using the shared helper because it also depends on the AIS CanPacket type.
	socket_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);

	if (socket_ >= 0) {
        int flags = fcntl(socket_, F_GETFL, 0);
        if ((flags < 0) || (fcntl(socket_, F_SETFL, flags | O_NONBLOCK) != 0)) {
            RCLCPP_FATAL(ROS2Logger::Instance().GetLogger(), "Failed to set CAN socket nonblocking: %s", strerror(errno));
            success = false;
        }

        const struct can_filter rxFilter = {0x734, 0x7F8};
        if (setsockopt(socket_, SOL_CAN_RAW, CAN_RAW_FILTER, &rxFilter, sizeof(rxFilter)) < 0) {
            RCLCPP_FATAL(ROS2Logger::Instance().GetLogger(), "Failed to set CAN filter: %s", strerror(errno));
            success = false;
        }

        int receiveLocalMsgs = 0;
        if (setsockopt(socket_, SOL_CAN_RAW, CAN_RAW_LOOPBACK, &receiveLocalMsgs, sizeof(receiveLocalMsgs)) < 0) {
            RCLCPP_FATAL(ROS2Logger::Instance().GetLogger(), "Failed to disable CAN loopback: %s", strerror(errno));
            success = false;
        }

        int receiveOwnMsgs = 0;
        if (setsockopt(socket_, SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS, &receiveOwnMsgs, sizeof(receiveOwnMsgs)) < 0) {
            RCLCPP_FATAL(ROS2Logger::Instance().GetLogger(), "Failed to disable own CAN messages: %s", strerror(errno));
            success = false;
        }

        struct ifreq interfaceRequest{};
        std::strncpy(interfaceRequest.ifr_name, "can2", sizeof(interfaceRequest.ifr_name) - 1);
        if (ioctl(socket_, SIOCGIFINDEX, &interfaceRequest) < 0) {
            RCLCPP_FATAL(ROS2Logger::Instance().GetLogger(), "Failed to find CAN interface can2: %s", strerror(errno));
            success = false;
        }
        else {
            struct sockaddr_can address{};
            address.can_family = AF_CAN;
            address.can_ifindex = interfaceRequest.ifr_ifindex;
            if (bind(socket_, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) < 0) {
                RCLCPP_FATAL(ROS2Logger::Instance().GetLogger(), "Failed to bind CAN interface can2: %s", strerror(errno));
                success = false;
            }
        }
	}
	else {
	    RCLCPP_FATAL(ROS2Logger::Instance().GetLogger(),"Failed to open socket, error %d (%s)", errno, strerror(errno));
        success = false;
	}

	init_flag_ = false;
    lastMsgId_ = 0;
    CAN734Received_ = false;
    CAN733Received_ = false;

	return success;
}

/******************************************************************************
FUNCTION NAME: sendTX
DESCRIPTION:   Sends a CAN-11bit message for mesg_id with 8 data bytes
PARAMETER DESCRIPTION: data[8] - 8 data bytes to send
                       mesg_id - is the CAN11-bit message id
RETURN VALUE: None -
*******************************************************************************/
void LpsAdvCANProcess::sendTX(uint8_t data[8], uint8_t length, uint16_t mesg_id)
{
    if (socket_ >= 0) {
        if (length > CAN_MAX_DLEN) {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Invalid CAN payload length %u", length);
            return;
        }

        struct can_frame frame{};
        frame.can_id = mesg_id;
        frame.can_dlc = length;
        std::memcpy(frame.data, data, sizeof(frame.data));

        int bytesSent = write(socket_, &frame, sizeof(frame));
        if (bytesSent != static_cast<int>(sizeof(frame))) {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Failed to write complete CAN message to socket, bytes=%d error %d (%s)", bytesSent, errno, strerror(errno));
        }
    }
    else {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Socket not open for publishing");
    }
}

/*
 * Purge all messages from the rx buffer and return the number of messages purged.
 */
int LpsAdvCANProcess::purgeRxBuffer()
{
    CanPacket rxPacket;
    int count = 0;
    while (getPacket(rxPacket, 0)) {
        ++count;
    }
    return count;
}

/******************************************************************************
DESCRIPTION: Update function to receive data on CAN-11bit
PARAMETERS:
    bool& allRxd - true if a matched pair was received, otherwise false.
RETURN:
    bool - true if new 732 message is received or missed, otherwise false.
*******************************************************************************/
bool LpsAdvCANProcess::update(bool& allRxd)
{
    if (!init_flag_) {
        // Clear the Rx buffer on startup.
        int count = purgeRxBuffer();
        init_flag_ = true;
        lastMsgId_ = 0;
        CAN734Received_ = false;
        CAN733Received_ = false;
        RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"Number of CAN packets received at startup: %d", count);
        allRxd = false;
        return false;
    }

    CanPacket rxPacket;

    bool CAN734Missed = false;
    bool CAN733Missed = false;

    bool CAN734Received = CAN734Received_;
    bool CAN733Received = CAN733Received_;

    /*
     * Every time I receive a 734, return, that will be the time-keeper message.
     * If I receive a 733 without receiving a 734, then return assuming I missed a 734.
     */
    while (getPacket(rxPacket, 0)) {

        // Skip past 29-bit extended msg identifiers
        if (rxPacket.extendedId) {
            continue;
        }

        if (0x734 == rxPacket.msgId) {
            unpack734Data(rxPacket);
            CAN734Received = true;
            ++CAN734_count;

            if (lastMsgId_ == rxPacket.msgId) {
                // We already had one of these, and we got another one, we must have missed something
               RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Two CAN734 messages received in a row without a CAN733 message.");
                CAN733Missed = true;
                break; // problem
            }

            lastMsgId_ = rxPacket.msgId;
        }
        else if (0x733 == rxPacket.msgId) {
            unpack733Data(rxPacket);
            CAN733Received = true;
            ++CAN733_count;

            if (lastMsgId_ == rxPacket.msgId) {
                // We already had one of these, and we got another one, we must have missed something
               RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Two CAN733 messages received in a row without a CAN734 message.");
                CAN734Missed = true;
                break; // problem
            }

            lastMsgId_ = rxPacket.msgId;
        }
        else {
           RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Received an unexpected message 0x%X.", rxPacket.msgId);
            break; // problem
        }

        if (CAN734Received) {
            break; // success!
        }
    }

    if (CAN734Missed || CAN733Missed) {
        ++dropped;
    }

    if (CAN734Received) {
        allRxd = CAN733Received; // Did we receive both?
        CAN734Received_ = false; // Start over.
        CAN733Received_ = false; // Start over.
        return true; // Timestep message received.
    }
    else if (CAN733Received) {
        allRxd = false;
        CAN734Received_ = false; // Wasn't received yet.
        CAN733Received_ = true; // Remember that we received this for next time.
        return CAN734Missed; // Timestep message missed.
    }
    else {
        allRxd = false;
        CAN734Received_ = false; // Still waiting.
        CAN733Received_ = false; // Still waiting.
        return false;
    }
}

/*
 * Does the same thing SocketCANBase version does except supports
 * a timeout and handles more errors.
 */
bool LpsAdvCANProcess::getPacket(CanPacket& m, int timeout_ms)
{
    bool success = false;
    if (socket_ >= 0) {
        struct timeval waitd; // Read Timeout
        waitd.tv_sec = (time_t)(timeout_ms / 1000);
        waitd.tv_usec = (time_t)((timeout_ms - waitd.tv_sec * 1000) * 1000);

        fd_set read_flags; // Flags for select
        FD_ZERO(&read_flags);           // Zero the flags ready for using
        FD_SET(socket_, &read_flags);

        // This make the blocked 'read' system call to a non-block read timed out call
        // solving any read block issue when any of the CAN device lost communication.
        int selected = select(socket_+1, &read_flags, nullptr, nullptr, &waitd);
        if (selected < 0) {
            if (errno != EINTR) {
                RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Failed to wait for CAN message, error %d (%s)", errno, strerror(errno));
            }
            return false;
        }

        if (selected > 0 && FD_ISSET(socket_, &read_flags)) {
            struct can_frame frame;
            memset(&frame, 0, sizeof(frame));

            int nbytes = read(socket_, &frame, sizeof(frame));

            if (nbytes <= 0) {
               RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Failed to read from CAN socket, error %d (%s)", errno, strerror(errno));
            }
            else if (nbytes != static_cast<int>(sizeof(frame))) {
               RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Incomplete CAN frame nbytes=%d", nbytes);
            }
            else if (frame.can_dlc > CAN_MAX_DLEN) {
                RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(), "Invalid CAN payload length %u", frame.can_dlc);
            }
            else {
                m.extendedId = (frame.can_id & CAN_EFF_FLAG) != 0;
                m.remoteFrame = (frame.can_id & CAN_RTR_FLAG) != 0;
                m.errorFrame = (frame.can_id & CAN_ERR_FLAG) != 0;
                m.msgId = m.extendedId ? (frame.can_id & CAN_EFF_MASK) : (frame.can_id & CAN_SFF_MASK);
                m.length = frame.can_dlc;
                std::memcpy(m.payload_, frame.data, frame.can_dlc);
                success = true;
            }
        }
    }
    else {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Socket is not open, cannot read");
    }
    return success;
}

/*
 * Unpack the provided CAN packet.
 */
bool LpsAdvCANProcess::unpack734Data(const CanPacket& packet)
{
    if (packet.length < 8) {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Wrong size for CAN734 %d", packet.length);
        return false; // problem
    }

    // Unpack 734
    uint_least8_t *data = (uint_least8_t*)&packet.payload_[0];
    OEL_UNPACK_BE_16(data, lift_he_pressure_);
    OEL_UNPACK_BE_16(data, lift_re_pressure_);
    OEL_UNPACK_BE_16(data, tilt_linkage_dc_);
    OEL_UNPACK_BE_16(data, lift_linkage_dc_);
    return true;
}

/*
 * Unpack the provided CAN packet.
 */
bool LpsAdvCANProcess::unpack733Data(const CanPacket& packet)
{
    if (packet.length < 6) {
       RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"Wrong size for CAN733 %d", packet.length);
        return false; // problem
    }

    // Unpack 733
    uint_least8_t *data = (uint_least8_t*)&packet.payload_[0];
    OEL_UNPACK_BE_16(data, lift_valve_cmd_);
    OEL_UNPACK_BE_16(data, tilt_valve_cmd_);
    OEL_UNPACK_BE_8(data, cal_override_acknowledge_);
    OEL_UNPACK_BE_8(data, lift_lever_status_);
    return true;
}

bool LpsAdvCANProcess::get_lift_he_pressure(float &he_pressure_val)
{
    if (IS_KNOWN2U(lift_he_pressure_)) {
        he_pressure_val = lift_he_pressure_;
        return true;
    }
    else
    {
        he_pressure_val = 0.f;
        return false;
    }
}

bool LpsAdvCANProcess::get_lift_re_pressure(float &re_pressure_val)
{
    if (IS_KNOWN2U(lift_re_pressure_)) {
        re_pressure_val = lift_re_pressure_;
        return true;
    }
    else
    {
        re_pressure_val = 0.f;
        return false;
    }
}

bool LpsAdvCANProcess::get_lift_linkage_dc(float &lift_linkage_dc)
{
    if (IS_KNOWN2U(lift_linkage_dc_))  {
        lift_linkage_dc = lift_linkage_dc_ * 0.002;
        return true;
    }
    else {
        lift_linkage_dc = 0.f;
        return false;
    }
}

bool LpsAdvCANProcess::get_tilt_linkage_dc(float &tilt_linkage_dc)
{
    if (IS_KNOWN2U(tilt_linkage_dc_))  {
        tilt_linkage_dc = tilt_linkage_dc_ * 0.002;
        return true;
    }
    else {
        tilt_linkage_dc = 0.f;
        return false;
    }
}

bool LpsAdvCANProcess::get_lift_valve_cmd(float &lift_valve_cmd)
{
    if (IS_KNOWN2S(lift_valve_cmd_))  {
        lift_valve_cmd = lift_valve_cmd_ * 0.1;
        return true;
    }
    else
    {
        lift_valve_cmd = 0.f;
        return false;
    }
}

bool LpsAdvCANProcess::get_tilt_valve_cmd(float &tilt_valve_cmd)
{
    if (IS_KNOWN2S(tilt_valve_cmd_))  {
        tilt_valve_cmd = tilt_valve_cmd_ * 0.1;
        return true;
    }
    else
    {
        tilt_valve_cmd = 0.f;
        return false;
    }
}

bool LpsAdvCANProcess::isCalOverrideActive()
{

    /* check if cal override acknowledge is 1 */
    if (cal_override_acknowledge_) {
        return true;
    }
    else {
        return false;
    }
}

void LpsAdvCANProcess::get_lift_lever_status(LpsAdvCANProcess::LiftLeverStatus_t& lift_lever_status)
{
    lift_lever_status = LiftLeverStatus_t();

    /* lift_lever_centered - bits 0-1 */
    if (0x01 & lift_lever_status_) {
        lift_lever_status.lift_lever_faulted = true;
    }

    /* lift_lever_lower detent - bits 2-3 */
    if (0x04 & lift_lever_status_) {
        lift_lever_status.lift_lever_lower_detent = true;
    }

    /* lift_lever_raise detent - bits 4-5 */
    if (0x10 & lift_lever_status_) {
        lift_lever_status.lift_lever_raise_detent = true;
    }

    /* lift_lever_faulted - bits 6-7 */
    if (0x40 & lift_lever_status_) {
        lift_lever_status.lift_lever_centered = true;
    }
}
