///////////////////////////////////////////////////////////////////////////////
// @attention COPYRIGHT (C) 2021 CATERPILLAR INC. ALL RIGHTS RESERVED.
//
// @file    PartNumbersPublisher.hpp
//
// @brief   Publishes PartNubmers SCS object
///////////////////////////////////////////////////////////////////////////////
#ifndef PARTNUMBERSPUBLISHER_HPP_
#define PARTNUMBERSPUBLISHER_HPP_

///////////////////////////////////////////////////////////////////////////////
// -- #Include's --
///////////////////////////////////////////////////////////////////////////////

#include "task/AutonomyTask.h"

#include <mutex>
#include <utility>
#include <vector>

#include <boost/functional/hash.hpp>

#include <catdllib_pid_def.h>
#include <version/EcmHwVersion.h>
#include <ais/task/load_version.h>
#include <taskPlugins/base/TaskPlugin.hpp>
#include <taskPlugins/interfaces/DatalinkManagerInterface.h>
#include <interfaces/PartNumbers/InterfaceTypes.h>

///////////////////////////////////////////////////////////////////////////////
// -- #Define, Struct's, Typedef's, Enum's --
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- Class Definition
///////////////////////////////////////////////////////////////////////////////
//class PartNumbersPublisher : public TaskPlugin, public PartNumbersPublisherApplicationInterface
class PartNumbersPublisher : public TaskPlugin
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor request a reference to the parent task
    ///////////////////////////////////////////////////////////////////////////////
    PartNumbersPublisher() = delete;
    PartNumbersPublisher(DatalinkManagerInterface& datalinkManager) :
        m_pPartNumbersOutput(nullptr)
    {}

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the plugin name (used for configuring update rate)
    /// @return name of the plugin
    ///////////////////////////////////////////////////////////////////////////////
    std::string getName() override { return "PartNumbersPublisher"; }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool initialize() override
    {
        bool success = true;

        if (!task::InterfaceDb::bind("PartNumbersOutput", m_pPartNumbersOutput))
        {
            success = false;
        }

        auto ecmHwVersion = getEcmHwInfo();
        m_PartNumbers.SetECMPartNum(ecmHwVersion.partnum);

        m_PartNumbers.SetSwGroupPartNum(get_softwareGroupPartNumber());
        m_PartNumbers.SetSwGroupReleaseDate(get_softwareGroupReleaseDate());
        m_PartNumbers.SetSwGroupDescription(get_softwareGroupDescription());

        AIS_LOG_DEBUG("PartNumbersPublisher::initialize(): %d", success);

        return success;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin after j1939 initialization
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool postInitialize() override 
    {
        // Check for Product ID in either Tx or Rx
        bool productIdRegistered = false;
        datalink::ParameterDataConnection connection;
        if (auto pParameterData = m_DatalinkManager.getParameterDataTx(PID_PRODUCT_ID_NUMBER, datalink::ParameterType::PID))
        {
            if (pParameterData->isWriteable())
            {
                AIS_LOG_INFO("Registering Product ID PID 0x%02X (Tx)", PID_PRODUCT_ID_NUMBER);
                pParameterData->connectOnValueReceived(boost::bind(&PartNumbersPublisher::onProductIdChanged, boost::ref(*this), _1, _2), connection);
                // Set initial value from DatalinkManager
                onProductIdChanged(*pParameterData, datalink::ParameterWriteMethod::INTERNAL);
                productIdRegistered = true;
            }
        }
        if (auto pParameterData = m_DatalinkManager.getParameterDataRx(PID_PRODUCT_ID_NUMBER, datalink::ParameterType::PID))
        {
            AIS_LOG_INFO("Registering Product ID PID 0x%02X (Tx)", PID_PRODUCT_ID_NUMBER);
            pParameterData->connectOnValueReceived(boost::bind(&PartNumbersPublisher::onProductIdChanged, boost::ref(*this), _1, _2), connection);
            // Set initial value from DatalinkManager
            onProductIdChanged(*pParameterData, datalink::ParameterWriteMethod::INTERNAL);
            productIdRegistered = true;
        }

        if (!productIdRegistered)
        {
            AIS_LOG_ERROR("Unable to find Product ID PID 0x%02X in Rx or Tx of DatalinkManager", PID_PRODUCT_ID_NUMBER);
            return false;
        }

        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Updates the plugin, expected to be called every executive loop of the
    ///        parent task.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool update() override
    {
        {
            std::lock_guard<std::mutex> lock(m_DatalinkMutex);
            m_pPartNumbersOutput->publish(m_PartNumbers);
        }

        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Called during cleanup of the parent task.
    ///////////////////////////////////////////////////////////////////////////////
    void cleanup() override
    {
    }

    void onProductIdChanged(const datalink::ParameterDataReadInterface& parameterData, datalink::ParameterWriteMethod writeMethod)
    {
        static datalink::RawData productIdPrev;
        auto productId = parameterData.getValueRawVector();
        if (productId != productIdPrev)
        {
            productIdPrev = std::move(productId);
            std::string productIdStr(productIdPrev.data(), productIdPrev.data() + productIdPrev.size());
            AIS_LOG_INFO("Received new product ID %s", productIdStr.c_str());
            {
                std::lock_guard<std::mutex> lock(m_DatalinkMutex);
                m_PartNumbers.SetProductIdNum(productIdStr);
            }
        }
    }

private:
    DatalinkManagerInterface& m_DatalinkManager;
    PartNumbersOutput* m_pPartNumbersOutput;
    PartNumbers m_PartNumbers;
    std::mutex m_DatalinkMutex;
};

#endif
