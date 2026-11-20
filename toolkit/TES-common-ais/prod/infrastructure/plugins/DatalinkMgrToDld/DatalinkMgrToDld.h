///////////////////////////////////////////////////////////////////////////////
// @attention COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
//
// @file    DatalinkMgrToDld.hpp
//
// @brief   Handle J1939 comms with ET.
///////////////////////////////////////////////////////////////////////////////
#ifndef DATALINKMGRTODLD_HPP_
#define DATALINKMGRTODLD_HPP_

///////////////////////////////////////////////////////////////////////////////
// -- #Include's --
///////////////////////////////////////////////////////////////////////////////

#include "task/AutonomyTask.h"

#include <boost/functional/hash.hpp>
#include <mutex>
#include <unordered_map>
#include <utility>
#include <vector>

#include <taskPlugins/interfaces/DatalinkManagerInterface.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>

///////////////////////////////////////////////////////////////////////////////
// -- #Define, Struct's, Typedef's, Enum's --
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- Class Definition
///////////////////////////////////////////////////////////////////////////////
//class DatalinkMgrToDld : public TaskPlugin, public DatalinkMgrToDldApplicationInterface
class DatalinkMgrToDld : public TaskPlugin
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor request a reference to the parent task
    ///////////////////////////////////////////////////////////////////////////////
    DatalinkMgrToDld() = delete;
    DatalinkMgrToDld(DatalinkManagerInterface& datalinkManager) :
        m_datalinkManager(datalinkManager),
        m_pDataLinkDataOutput(nullptr)
    {}

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the plugin name (used for configuring update rate)
    /// @return name of the plugin
    ///////////////////////////////////////////////////////////////////////////////
    std::string getName() override { return "DatalinkMgrToDld"; }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool initialize() override
    {
        bool success = true;

        if (!task::InterfaceDb::bind("DataLinkDataPublisherOutput", m_pDataLinkDataOutput))
        {
            success = false;
        }

        AIS_LOG_DEBUG("DatalinkMgrToDld_initialize():%d", success);

        return success;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin after j1939 initialization
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool postInitialize() override 
    {
        bool success = true;

        AIS_LOG_DEBUG("post_initialize()**************************");
        m_RxTable = m_datalinkManager.getParameterDataRxTable();
        m_TxTable = m_datalinkManager.getParameterDataTxTable();

        for (auto& entry : m_RxTable)
        {
            // Add PID to DataLinkData if configured
            DataLinkParam dlParam;
            auto& rxParam = entry.second;
            auto paramId = rxParam.getId();
            dlParam.SetParamId(paramId);
            auto paramIdentifierType = toDlpParameterIdentifierType(rxParam.getParameterType());
            auto datalinkType = toDlpDataLinkType(rxParam.getDatalinkProtocol());
            dlParam.SetParamIdentifierType(static_cast<DataLinkParam::DlpParamIdentifierType_t>(paramIdentifierType));
            dlParam.SetDataLinkType(static_cast<DataLinkParam::DlpDataLinkType_t>(datalinkType));
            dlParam.SetSid(rxParam.getSourceId());
            dlParam.SetScaling(rxParam.getScaling());
            dlParam.SetOffset(rxParam.getOffset());
            dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::NOT_APPLICABLE);
            if (datalink::DataType::VAR_NO_DSI == rxParam.getDataType())
            {
                dlParam.SetParameterType(CDL2_VAR_NO_DSI);   // VAR length
                AIS_LOG_DEBUG("%s id:0x%02X name:%s dType:%x, scale:%f off:%f bytes:%d ****", rxParam.getParameterTypeString(), paramId, rxParam.getName().c_str(), rxParam.getDataType(), rxParam.getScaling(), rxParam.getOffset(), rxParam.getLengthInBytes());
            }
            else
            {
                dlParam.SetParameterType(cdl2_parameter_type_t(rxParam.getDataType()));   // U8, S16, ...
            }

            DataLinkParam* pNewParam;
            if (!m_DataLinkData.AddDataLinkParam(dlParam, pNewParam))
            {
                success = false;
            }
            else
            {
                // Add to lookup
                m_DatalinkMgrToDldRxTable.emplace_back(DatalinkMgrToDldRxEntry{rxParam, *pNewParam});
            }

            AIS_LOG_DEBUG("%s SA:0x%02X id:0x%02X name:%s dType:%x, pType:%d scale:%f off:%f bytes:%d", rxParam.getParameterTypeString(), rxParam.getSourceId(), paramId, rxParam.getName().c_str(), rxParam.getDataType(), rxParam.getParameterType(), rxParam.getScaling(), rxParam.getOffset(), rxParam.getLengthInBytes());
        }


        for (auto& entry : m_TxTable)
        {
            auto& txParam = entry.second;
            auto paramId = txParam.getId();
            if (txParam.isWriteable())   // is TX parameter Writeable, then add to DataLinkData
            {
                // Add PID to DataLinkData if configured
                DataLinkParam dlParam;
                dlParam.SetParamId(paramId);
                auto paramIdentifierType = toDlpParameterIdentifierType(txParam.getParameterType());
                dlParam.SetParamIdentifierType(static_cast<DataLinkParam::DlpParamIdentifierType_t>(paramIdentifierType));
                dlParam.SetSid(0xEE);    // for now always 0xEE for TX, not sure how to get J1939-SA, CDL-MID, FID, ...
                dlParam.SetScaling(txParam.getScaling());
                dlParam.SetOffset(txParam.getOffset());
                dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::NOT_APPLICABLE);
                if (datalink::DataType::VAR_NO_DSI == txParam.getDataType())
                {
                    dlParam.SetParameterType(CDL2_VAR_NO_DSI);   // VAR length
                    AIS_LOG_DEBUG("TX id:0x%02X name:%s dType:%x, scale:%f off:%f bytes:%d ****", paramId, txParam.getName().c_str(), txParam.getDataType(), txParam.getScaling(), txParam.getOffset(), txParam.getLengthInBytes());
                }
                else
                {
                    dlParam.SetParameterType(cdl2_parameter_type_t(txParam.getDataType()));   // U8, S16, ...
                }

                DataLinkParam* pNewParam;
                if (!m_DataLinkData.AddDataLinkParam(dlParam, pNewParam))
                {
                    AIS_LOG_DEBUG("TX ERROR --- first:%s %x  second:%s ADDED", txParam.getParameterTypeString(), txParam.getName().c_str());
                    success = false;
                }
                else
                {
                    AIS_LOG_DEBUG("TX GOOD  --- first:%s %x  second:%s ADDED", txParam.getParameterTypeString(), paramId, txParam.getName().c_str());

                    // Add to lookup
                    m_DatalinkMgrToDldTxTable.emplace_back(DatalinkMgrToDldTxEntry{txParam, *pNewParam});
                }
            }
            else
            {
                AIS_LOG_DEBUG("TX --- first:%s %x  second:%s  IGNORED", txParam.getParameterTypeString(), paramId, txParam.getName().c_str());
            }
        }


        return success;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Updates the plugin, expected to be called every executive loop of the
    ///        parent task.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool update() override
    {
        AIS_LOG_DEBUG("DatalinkMgrToDld_update()");
        for (auto& entry : m_DatalinkMgrToDldRxTable)
        {
            auto& rxParam = entry.parameterData;
            auto& dlParam = entry.datalinkParam;

            if (rxParam.getDataType() == datalink::DataType::DOUBLE)
            {
                dlParam.SetLastValueDouble(rxParam.getValueEng(), rxParam.getDsi());
            }
            else
            {
                dlParam.SetVarLengthParamValue(rxParam.getValueRawVector(), rxParam.getDsi());  // raw & dsi state
            }
            
            // the below code is to verify the DatalinkManager data matches what is put into dlParam
            if (CDL2_VAR_NO_DSI == dlParam.GetParameterType())
            {
                auto paramId = rxParam.getId();
                auto parameterType = rxParam.getParameterType();
                if ((0xF0B2 == paramId) && (parameterType == datalink::ParameterType::CAT_EXT_ID))  // need to add two bytes to the beginning  0xF0B2 so SecuritySystemCurrentIDParam.h works
                {
                    std::vector<uint8_t> y;
                    y = dlParam.GetLastValueVector();
                    // AIS_LOG_DEBUG("id:0x%02X dsi:%d L%d  %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x", dlParam->GetParamId(), dlParam->GetLastValueDsi(), dlParam->GetVarParamBlockLength(), y[0], y[1], y[2], y[3], y[4], y[5], y[6], y[7], y[8], y[9], y[10], y[11], y[12], y[13], y[14], y[15], y[16], y[17], y[18], y[19]);
                    AIS_LOG_DEBUG("id:0x%02X dsi:%d L%d %s", paramId, dlParam.GetLastValueDsi(), dlParam.GetVarParamBlockLength(), convertByteVectorToString(y).c_str());

                    y.insert(y.begin(), 0xB2);
                    y.insert(y.begin(), 0xF0);
                    dlParam.SetVarLengthParamValue(y, rxParam.getDsi());
                }
            }
            // Loop is only needed for debugging
            if (AIS_LOG_DEBUG_ENABLED)
            {
                std::vector<uint8_t> z;
                z = dlParam.GetLastValueVector();
                std::string paramStr;
                if (z.size() > 0)
                {
                    paramStr = "0x";
                    for (auto val : z)
                    {
                        paramStr += ais::utility::to_hex_string(val, 2, "");
                    }
                }
                else
                {
                    paramStr = "(Empty)";
                }
                AIS_LOG_DEBUG(":%s SA:0x%02X id:0x%02X dsi:%d Eng:%f L%d  %s", rxParam.getName().c_str(), dlParam.GetSid(), dlParam.GetParamId(), dlParam.GetLastValueDsi(), dlParam.GetLastValueEng(), dlParam.GetVarParamBlockLength(), paramStr.c_str());
            }
        }

        for (auto& entry : m_DatalinkMgrToDldTxTable)
        {
            auto& txParam = entry.parameterData;
            auto& dlParam = entry.datalinkParam;
            datalink::RawData rawData{txParam.getValueRawVector()};
            uint8_t dsi{txParam.getDsi()};
            dlParam.SetVarLengthParamValue(rawData, dsi);  // raw & dsi state
            if (AIS_LOG_DEBUG_ENABLED)
            {
                auto paramId = txParam.getId();
                std::vector<uint8_t> w;
                w = dlParam.GetLastValueVector();
                // AIS_LOG_DEBUG("TX:%s id:0x%02X dsi:%d L%d  %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x", entry.second.getName().c_str(), dlParam->GetParamId(), dlParam->GetLastValueDsi(), dlParam->GetVarParamBlockLength(), w[0], w[1], w[2], w[3], w[4], w[5], w[6], w[7], w[8], w[9], w[10], w[11], w[12], w[13], w[14], w[15], w[16], w[17], w[18], w[19]);
                AIS_LOG_DEBUG("TX:%s  SA:0x%02X id:0x%02X dsi:%d L%d  %s", txParam.getName().c_str(), dlParam.GetSid(), paramId, dlParam.GetLastValueDsi(), dlParam.GetVarParamBlockLength(), convertByteVectorToString(w).c_str());
            }
        }

        m_pDataLinkDataOutput->publish(m_DataLinkData); // publish

        return true;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Called during cleanup of the parent task.
    ///////////////////////////////////////////////////////////////////////////////
    void cleanup() override
    {
        AIS_LOG_DEBUG("DatalinkMgrToDld_cleanup()");
    }


private:
    DatalinkManagerInterface& m_datalinkManager;
    DataLinkDataOutput* m_pDataLinkDataOutput;
    DatalinkManagerInterface::ParameterDataRxTable m_RxTable;
    DatalinkManagerInterface::ParameterDataTxTable m_TxTable;
    DataLinkData m_DataLinkData;

    struct DatalinkMgrToDldRxEntry
    {
        datalink::ParameterDataReadInterface& parameterData;
        DataLinkParam& datalinkParam;
    };

    std::vector<DatalinkMgrToDldRxEntry> m_DatalinkMgrToDldRxTable;

    struct DatalinkMgrToDldTxEntry
    {
        datalink::ParameterDataInterface& parameterData;
        DataLinkParam& datalinkParam;
    };

    std::vector<DatalinkMgrToDldTxEntry> m_DatalinkMgrToDldTxTable;

    std::string convertByteVectorToString(const datalink::RawData& rawData)
    {
        std::stringstream stream;
        if (rawData.size() == 0)
        {
            stream << '0';
        }
        else
        {
            for (auto dataByte : rawData)
            {
                uint32_t paddedByte = dataByte;
                stream << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << paddedByte;
            }
        }
        return stream.str();
    }

    DataLinkParamInfo::DlpParamIdentifierType_t toDlpParameterIdentifierType(datalink::ParameterType parameterType)
    {
        const std::unordered_map<datalink::ParameterType_t, DataLinkParamInfo::DlpParamIdentifierType_t> Table {
            { static_cast<datalink::ParameterType_t>(datalink::ParameterType::PID), DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_PID },
            { static_cast<datalink::ParameterType_t>(datalink::ParameterType::CAT_EXT_ID), DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT },
            { static_cast<datalink::ParameterType_t>(datalink::ParameterType::PGN), DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN },
            { static_cast<datalink::ParameterType_t>(datalink::ParameterType::SPN), DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_SPN },
            { static_cast<datalink::ParameterType_t>(datalink::ParameterType::CPOP), DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_CPOP },
            { static_cast<datalink::ParameterType_t>(datalink::ParameterType::CDA), DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_CDA }
        };
        auto   it  = Table.find(static_cast<datalink::ParameterType_t>(parameterType));
        return it == Table.end() ? DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_UNKNOWN : it->second;
    }

    DataLinkParamInfo::DlpDataLinkType_t toDlpDataLinkType(datalink::DatalinkProtocol protocol)
    {
        const std::unordered_map<datalink::DatalinkProtocol_t, DataLinkParamInfo::DlpDataLinkType_t> Table {
            { static_cast<datalink::DatalinkProtocol_t>(datalink::DatalinkProtocol::CDL), DataLinkParam::DATA_LINK_PARAM_CDL },
            { static_cast<datalink::DatalinkProtocol_t>(datalink::DatalinkProtocol::ETHERNET_PGT), DataLinkParam::DATA_LINK_PARAM_ETH },
            { static_cast<datalink::DatalinkProtocol_t>(datalink::DatalinkProtocol::J1939), DataLinkParam::DATA_LINK_PARAM_CAN1_1939 },
            { static_cast<datalink::DatalinkProtocol_t>(datalink::DatalinkProtocol::UDP_CAN), DataLinkParam::DATA_LINK_PARAM_UDP_CAN },
            { static_cast<datalink::DatalinkProtocol_t>(datalink::DatalinkProtocol::CDA), DataLinkParam::DATA_LINK_PARAM_CDA }
        };
        auto   it  = Table.find(static_cast<datalink::DatalinkProtocol_t>(protocol));
        return it == Table.end() ? DataLinkParam::DATA_LINK_PARAM_UNKNOWN : it->second;
    }
};

#endif
