/**
***************************************************************************
* @file XcpServerTask.h
*
* A simple task to use as an empty starting point
*
* Copyright 2010
*
* National Robotics Engineering Center, Carnegie Mellon University
* 10 40th Street, Pittsburgh, PA 15201
* www.rec.ri.cmu.edu
*
* Control Instructions (who can see this code): NREC Confidential.
* Not for public release unless permission granted by program manager.
*
* Usage Rights (who can use this code): Usage allowed for all NREC
* programs with permissions from author and program manager.
*
* This notice must appear in all copies of this file and its derivatives.
*
* Created under Program: ACRS
*
* History of Significant Contributions (don't put commit logs here):
* 2010-10-22 cbaker@rec.ri.cmu.edu  Created file.
***************************************************************************
*/

#ifndef XCPSERVERTASK_H_
#define XCPSERVERTASK_H_

#include "ros2wrapper/Ros2TaskWrapper.h"

#include "XcpScsInputsDb.h"
#include "TipoffAssistLogging.hpp"

/**@brief A Do-Nothing Task as a starting point
 *
 */

class XcpServerTask: public ros2_wrapper::Ros2TaskWrapper {
public:
    // Ros2TaskWrapper construction requires a task name
    XcpServerTask( const std::string& taskName );

    // ALWAYS virtual destructors for polymorphic classes
    virtual ~XcpServerTask( );

    // principal Ros2TaskWrapper interface: all derivatives must implement these

    // called once, at startup, after the node is created
    virtual bool initialize( );

    // called periodically, at cycle_rate_hz
    virtual bool executive( );

    // called on shutdown for pre-exit cleanup
    virtual void cleanup( );

    // creates the executive timer (cycle_rate_hz)
    virtual void startExecutiveTimer( );

    XcpScsInputs m_xcpScsInputs;
    TipoffAssistLogging toaLogging;

private:

    template<typename Msg>
    bool createRosInput(const rclcpp::Node::SharedPtr& rosNode, ros2_wrapper::RosInputInterface<Msg>*& input,
                        const std::string& topic, size_t qosDepth);

    template<typename Msg>
    bool createRosInput(const rclcpp::Node::SharedPtr& rosNode, ros2_wrapper::RosInputInterface<Msg>*& input,
                        const std::string& topic, const rclcpp::QoS& qos);

    void cleanupRosInterfaces( );

    /* ROS2 inputs injected into m_xcpScsInputs (owned here, deleted in cleanupRosInterfaces()) */
    XcpScsInputs::RosInputs rosInputs_;
};

#endif
