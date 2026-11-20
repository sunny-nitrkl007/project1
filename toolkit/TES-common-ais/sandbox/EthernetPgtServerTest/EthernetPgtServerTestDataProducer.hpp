///////////////////////////////////////////////////////////////////////////////
// @attention COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
//
// @file    EthernetPgtServerTestDataProducer.hpp
//
// @brief   Provides test data to Ethernet PGT Server
///////////////////////////////////////////////////////////////////////////////
#ifndef ETHERNETPGTSERVERTESTDATAPRODUCER_HPP_
#define ETHERNETPGTSERVERTESTDATAPRODUCER_HPP_

///////////////////////////////////////////////////////////////////////////////
// -- #Include's --
///////////////////////////////////////////////////////////////////////////////

#include "task/AutonomyTask.h"

#include <boost/functional/hash.hpp>
#include <mutex>
#include <unordered_map>
#include <utility>
#include <vector>

#include <taskPlugins/base/TaskPlugin.hpp>
#include <plugins/EthernetPgtServer/EthernetPgtServerApplicationInterface.h>
#include <catdl/BMI_CDL_PID_Coaching.h>

///////////////////////////////////////////////////////////////////////////////
// -- #Define, Struct's, Typedef's, Enum's --
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- Class Definition
///////////////////////////////////////////////////////////////////////////////
class EthernetPgtServerTestDataProducer : public TaskPlugin
{
public:

    // Must match the order of parameter entries EthernetPgtServerTestDataProducder.rb
    enum PgtParamConfigIndex
    {
        PARAM_ID = 0,
        PARAM_WRITE_TYPE = 1,
        PARAM_VALUE = 2
    };

    static constexpr auto PID_PREFIX = "PID";
    static constexpr auto SPN_PREFIX = "SPN";
    static constexpr auto CAT_EXT_ID_PREFIX = "CAT_EXT_ID";

    static constexpr auto WRITE_TYPE_ENG = "ENG";
    static constexpr auto WRITE_TYPE_RAW = "RAW";
    static constexpr auto WRITE_TYPE_DSI = "DSI";

    // These need to match the datalink definition for PID 0xF84D
    enum class ParamWriteType : uint8_t {
        ENG = 0,
        RAW = 1,
        DSI = 2
    };

    static std::string toString(EthernetPgtServerTestDataProducer::ParamWriteType e)
    {
        const std::map<EthernetPgtServerTestDataProducer::ParamWriteType, const char*> EnumStrings {
            { EthernetPgtServerTestDataProducer::ParamWriteType::ENG, "ENG" },
            { EthernetPgtServerTestDataProducer::ParamWriteType::RAW, "RAW" },
            { EthernetPgtServerTestDataProducer::ParamWriteType::DSI, "DSI" }
        };
        auto   it  = EnumStrings.find(e);
        return it == EnumStrings.end() ? "--" : it->second;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor request a reference to the parent task
    ///////////////////////////////////////////////////////////////////////////////
    EthernetPgtServerTestDataProducer() = delete;
    EthernetPgtServerTestDataProducer(EthernetPgtServerApplicationInterface& ethernetPgtServer) :
        m_EthernetPgtServer{ethernetPgtServer}
    {}

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the plugin name (used for configuring update rate)
    /// @return name of the plugin
    ///////////////////////////////////////////////////////////////////////////////
    std::string getName() override { return "EthernetPgtServerTestDataProducer"; }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool initialize() override
    {
        ConfigSection pluginConfig;
        if (!m_parent.getTaskParser().getSection(getName(), pluginConfig))
        {
            AIS_LOG_ERROR("Config section for %s not found", getName().c_str());
            return false;
        }

        // Extract PID, SPN, CAT EXT ID parameters from the ruby config
        auto keys = pluginConfig.getParameterNames();
        for(auto it = keys.begin(); it != keys.end(); ++it)
        {
            auto const& key = *it;
            std::vector<std::string> configArray;
            if(pluginConfig.getArray(key, configArray))
            {
                uint32_t paramId = strtol(configArray.at(PgtParamConfigIndex::PARAM_ID).c_str(), nullptr, 16);

                auto paramWriteType = configArray.at(PgtParamConfigIndex::PARAM_WRITE_TYPE) == toString(ParamWriteType::ENG) ? ParamWriteType::ENG :
                                      configArray.at(PgtParamConfigIndex::PARAM_WRITE_TYPE) == toString(ParamWriteType::RAW) ? ParamWriteType::RAW : ParamWriteType::DSI;

                double paramValueEng = 0.0f;
                uint32_t paramValueRaw = 0;
                uint8_t dsi = 0;
                if (paramWriteType == ParamWriteType::ENG)
                {
                    paramValueEng = strtod(configArray.at(PgtParamConfigIndex::PARAM_VALUE).c_str(), nullptr);
                    AIS_LOG_INFO("Adding %s 0x%X with engineering value %f", key.c_str(), paramId, paramValueEng);
                }
                else if (paramWriteType == ParamWriteType::RAW)
                {
                    paramValueRaw = static_cast<uint32_t>(strtol(configArray.at(PgtParamConfigIndex::PARAM_VALUE).c_str(), nullptr, 16));
                    AIS_LOG_INFO("Adding %s 0x%X with raw value 0x%X", key.c_str(), paramId, paramValueRaw);
                }
                else // DSI
                {
                    dsi = static_cast<uint8_t>(strtol(configArray.at(PgtParamConfigIndex::PARAM_VALUE).c_str(), nullptr, 10));
                    AIS_LOG_INFO("Adding %s 0x%X with DSI %u", key.c_str(), paramId, dsi);
                }

                if (key.compare(0, strlen(PID_PREFIX), PID_PREFIX) == 0)
                {
                    if (m_PidValuesEng.count(paramId) > 0 || m_PidValuesRaw.count(paramId) > 0)
                    {
                        AIS_LOG_WARN("PID $%X already added", paramId);
                        continue;
                    }
                    if (paramWriteType == ParamWriteType::ENG)
                    {
                        m_PidValuesEng[paramId] = paramValueEng;
                    }
                    else if (paramWriteType == ParamWriteType::RAW)
                    {
                        m_PidValuesRaw[paramId] = paramValueRaw;
                    }
                    else // DSI
                    {
                        m_PidValuesDsi[paramId] = dsi;
                    }
                }
                else if (key.compare(0, strlen(SPN_PREFIX), SPN_PREFIX) == 0)
                {
                    if (m_SpnValuesRaw.count(paramId) > 0 || m_SpnValuesEng.count(paramId) > 0)
                    {
                        AIS_LOG_WARN("SPN 0x%X already added", paramId);
                        continue;
                    }
                    if (paramWriteType == ParamWriteType::ENG)
                    {
                        m_SpnValuesEng[paramId] = paramValueEng;
                    }
                    else
                    {
                        m_SpnValuesRaw[paramId] = paramValueRaw;
                    }
                }
                else if (key.compare(0, strlen(CAT_EXT_ID_PREFIX), CAT_EXT_ID_PREFIX) == 0)
                {
                    if (m_CatExtIdValues.count(paramId) > 0)
                    {
                        AIS_LOG_WARN("CAT EXT ID 0x%X already added", paramId);
                        continue;
                    }
                    m_CatExtIdValues[paramId] = paramValueRaw;
                }
                else
                {
                    AIS_LOG_WARN("Unknown parameter key %s", key.c_str());
                }
            }
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
        // Set Parameter values for testing, since they are static only need to set once
        static bool updated = false;
        if (!updated)
        {
            for (auto& param : m_PidValuesEng)
            {
                m_EthernetPgtServer.setPidValueEng(param.first, param.second);
            }

            for (auto& param : m_PidValuesRaw)
            {
                m_EthernetPgtServer.setPidValueRaw(param.first, param.second);
            }

            for (auto& param : m_PidValuesDsi)
            {
                m_EthernetPgtServer.setPidDsi(param.first, param.second);
            }

            for (auto& param : m_SpnValuesEng)
            {
                m_EthernetPgtServer.setSpnValueEng(param.first, param.second);
            }

            for (auto& param : m_CatExtIdValues)
            {
                m_EthernetPgtServer.setCatExtIdValue(param.first, param.second);
            }
            updated = true;
        }

        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Called during cleanup of the parent task.
    ///////////////////////////////////////////////////////////////////////////////
    void cleanup() override{};

private:
    EthernetPgtServerApplicationInterface& m_EthernetPgtServer;

    std::unordered_map<uint32_t, double> m_PidValuesEng;
    std::unordered_map<uint32_t, uint32_t> m_PidValuesRaw;
    std::unordered_map<uint32_t, uint8_t> m_PidValuesDsi;
    std::unordered_map<uint32_t, double> m_SpnValuesEng;
    std::unordered_map<uint32_t, uint32_t> m_SpnValuesRaw;
    std::unordered_map<uint32_t, uint32_t> m_CatExtIdValues;
};

#endif
