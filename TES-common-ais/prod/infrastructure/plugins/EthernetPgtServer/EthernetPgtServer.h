///////////////////////////////////////////////////////////////////////////////
// @attention COPYRIGHT (C) 2020 CATERPILLAR INC. ALL RIGHTS RESERVED.
//
// @file    EthernetPgtServer.hpp
//
// @brief   Implement Ethernet PGT Server
///////////////////////////////////////////////////////////////////////////////
#ifndef ETHERNETPGTSERVER_HPP_
#define ETHERNETPGTSERVER_HPP_

///////////////////////////////////////////////////////////////////////////////
// -- #Include's --
///////////////////////////////////////////////////////////////////////////////

#include "task/AutonomyTask.h"

#include <sys/socket.h>

#include <boost/functional/hash.hpp>
#include <atomic>
#include <mutex>
#include <unordered_map>
#include <utility>
#include <vector>

#include <csf_pgt_server.h>
#include <cdl2_proto.h>
#include <cdl2_struct.h>
#include <scl_pdb.h>

#include <catdllib_fid_def.h>
#include <taskPlugins/base/TaskPlugin.hpp>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <bmi/bmi_ethernet_parser.h>

#include "EthernetPgtServerApplicationInterface.h"


///////////////////////////////////////////////////////////////////////////////
// -- #Define, Struct's, Typedef's, Enum's --
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// -- Class Definition
///////////////////////////////////////////////////////////////////////////////
class EthernetPgtServer : public TaskPlugin, public EthernetPgtServerApplicationInterface
{
public:
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor request a reference to the parent task
    ///////////////////////////////////////////////////////////////////////////////
    EthernetPgtServer() :
        m_InitDone(false),
        m_Fid(0)
    {}

// TaskPlugin //

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Get the plugin name (used for configuring update rate)
    /// @return name of the plugin
    ///////////////////////////////////////////////////////////////////////////////
    std::string getName() override { return "EthernetPgtServer"; }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool initialize() override { return true; }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initializes the plugin after comms initialization
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool postInitialize() override;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Updates the plugin, expected to be called every executive loop of the
    ///        parent task.
    /// @return true if successful, otherwise false
    ///////////////////////////////////////////////////////////////////////////////
    bool update() override;

// EthernetPgtServerApplicationInterface //

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the PID engineering/scaled value
    /// @param paramId - parameter id
    /// @param value - parameter value
    /// @return true if successful, false
    ///////////////////////////////////////////////////////////////////////////////
    bool setPidValueEng(uint32_t paramId, double value) override;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the raw PID/unscaled value.  Useful for gear PIDs etc.
    /// @param paramId - parameter id
    /// @param value - parameter value
    /// @return true if successful, false
    ///////////////////////////////////////////////////////////////////////////////
    bool setPidValueRaw(uint32_t paramId, uint32_t value) override;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the DSI of the PID, if > 0 the value is overwritten
    /// @param paramId - parameter id
    /// @param value - parameter value
    /// @return true if successful, false
    ///////////////////////////////////////////////////////////////////////////////
    bool setPidDsi(uint32_t paramId, uint8_t dsi) override;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the SPN value
    /// @param spnId - parameter id
    /// @param value - parameter value
    /// @return true if successful, false
    ///////////////////////////////////////////////////////////////////////////////
    bool setSpnValueEng(uint32_t spnId, double value) override;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Set the CAT Ext Id value
    /// @param catExtId - parameter id
    /// @param value - parameter value
    /// @return true if successful, false
    ///////////////////////////////////////////////////////////////////////////////
    bool setCatExtIdValue(uint32_t catExtId, uint32_t value) override;

private:

    // Callback handlers
    static int_16 cdl_tx_hdlr(void *tx_pie, unsigned_8 *data);
    static uint_least16_t scl_pdb_spn_tx_hdlr(uint_least8_t datalink_type, uint_least8_t datalink_instance, 
                                                     uint_least32_t src_id, uint_least32_t dest_id, void* datalink_info, uint_least8_t* data_buf,
                                                     uint_least16_t data_buf_size, const scl_pdb_spn_tx_config_t* spn_config);
    static uint_least16_t scl_pdb_cat_ext_id_tx_hdlr(uint_least8_t datalink_type,uint_least8_t datalink_instance,uint_least32_t src_id,
                                                     uint_least32_t dest_id, void* datalink_info,uint_least8_t* data,uint_least16_t data_size,
                                                     const scl_pdb_cat_ext_id_tx_config_t *cat_ext_id_config);

    // Holds a CDL PID value and metadata. In the future this could be refactored into an interface to make the underlying
    // bmiConfig platform specific
    struct PidTxData_t
    {
        tes_common_ais::bmi_config_parser::BmiEthPidCfgTbl_t& bmiConfig;
        unsigned_32 data;
        bool dataValid;

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set the Data and valid flag
        /// @param data - parameter value
        ///////////////////////////////////////////////////////////////////////////////
        void setData(unsigned_32 data) { this->data = data; dataValid = true; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the parameter value
        /// @return parameter value
        ///////////////////////////////////////////////////////////////////////////////
        unsigned_32 getData() { return data; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Check if the data been set (includes producer setting DSI)
        /// @return true if data is valid, false otherwise
        ///////////////////////////////////////////////////////////////////////////////
        bool isDataValid() const { return dataValid; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Get the size of the parameter in bytes
        /// @return size of the parameter in bytes
        ///////////////////////////////////////////////////////////////////////////////
        unsigned_8 getDataSizeBytes() const { return bmiConfig.data_size; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Check if LSB is first
        /// @return true if LSB false false if MSB first
        ///////////////////////////////////////////////////////////////////////////////
        bool isLsbFirst() const { return tes_common_ais::bmi_config_parser::isLsbFirst(bmiConfig); }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Check if parameter is signed
        /// @return true if parameter is signed false otherwise
        ///////////////////////////////////////////////////////////////////////////////
        bool isSigned() const { return tes_common_ais::bmi_config_parser::isSigned(bmiConfig); }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Check if the parameter value is encoded with DSI
        /// @return true if DSI is supported false otherwise
        ///////////////////////////////////////////////////////////////////////////////
        bool isDsiSupported() const { return tes_common_ais::bmi_config_parser::isDsiSupported(bmiConfig); }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Set the dsi
        /// @param dsi value, must be non-zero.  DSI can only be cleared by setting a valid value
        /// @return true if successful, false
        ///////////////////////////////////////////////////////////////////////////////
        bool setDsi(uint8_t dsi)
        {
            if (isDsiSupported() && dsi > 0)
            {
                switch (bmiConfig.ParameterType)
                {
                case CDL2_U8_DSI:
                case CDL2_U16_DSI:
                case CDL2_U32_DSI:
                    data = UNKNOWN4U | dsi;
                    break;
                case CDL2_I8_DSI:
                    data = UNKNOWN1S | dsi;
                    break;
                case CDL2_I16_DSI:
                    data = UNKNOWN2S | dsi;
                    break;
                case CDL2_I32_DSI:
                    data = UNKNOWN4S | dsi;
                    break;
                default:
                    return false;
                }
                dataValid = true;
                return true;
            }
            return false;
        }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Clear the parameter data and valid flag
        ///////////////////////////////////////////////////////////////////////////////
        void clearData()
        {
            if (isDsiSupported())
            {
                data = isSigned() ? UNKNOWN4S : UNKNOWN4U;
            }
            else
            {
                data = 0;
            }
            dataValid = false;
        }
    };

    // Holds an SPN value and metadata
    struct SpnTxData_t
    {
        SpnTxData_t(tes_common_ais::bmi_config_parser::BmiEthSpnCfgTbl_t& bmiConfig,
                    std::vector<uint_least8_t> data) :
            bmiConfig(bmiConfig),
            data(data)
        {}

        tes_common_ais::bmi_config_parser::BmiEthSpnCfgTbl_t& bmiConfig;
        std::vector<uint_least8_t> data;

        std::vector<uint_least8_t>& getData() { return data; }
        uint_least16_t getDataSizeBits() { return bmiConfig.size_in_bits; }

        bool setValueEng(double valueEng)
        {
            auto valueSpn = static_cast<uint32_t>(static_cast<int32_t>(valueEng / bmiConfig.Scaling - bmiConfig.Offset + 0.5));
            data.assign(reinterpret_cast<unsigned_8 *>(&valueSpn), reinterpret_cast<unsigned_8 *>(&valueSpn) + sizeof(decltype(valueSpn)));
            return true;
        }

        void clearData()
        {
            for (auto& entry : data)
            {
                entry = 0XFF;
            }
        }
    };

        // Holds a CAT EXT ID value and metadata
    struct CatExtIdTxData_t
    {
        CatExtIdTxData_t(tes_common_ais::bmi_config_parser::BmiEthCatExtIdCfgTbl_t& bmiConfig,
                    std::vector<uint_least8_t> data) :
            bmiConfig(bmiConfig),
            data(data)
        {}

        tes_common_ais::bmi_config_parser::BmiEthCatExtIdCfgTbl_t& bmiConfig;
        std::vector<uint_least8_t> data;

        uint_least16_t getData(uint_least8_t* data)
        { 
            for (size_t i = 0; i < this->data.size(); i++)
            {
                data[i] = this->data[i];
            }
            
            return this->data.size();
        }

        uint_least16_t getDataSizeBytes() { return bmiConfig.data_size; }

        bool setValue(uint32_t value)
        {
            data.assign(reinterpret_cast<unsigned_8 *>(&value), reinterpret_cast<unsigned_8 *>(&value) + getDataSizeBytes());
            return true;
        }

        void clearData()
        {
            for (auto& entry : data)
            {
                entry = 0XFF;
            }
        }
    };

    static std::mutex m_Mutex;

    static std::unordered_map<uint32_t, PidTxData_t> m_PidTxDataTable;

    static tes_common_ais::bmi_config_parser::TxSpnConfigTable_t m_SpnTxConfigTable;
    static std::unordered_map<uint_least32_t, SpnTxData_t> m_SpnTxDataTable;

    static tes_common_ais::bmi_config_parser::TxCatExtIdConfigTable_t m_CatExtIdTxConfigTable;
    static std::unordered_map<uint_least32_t, CatExtIdTxData_t> m_CatExtIdTxDataTable;

    static std::vector<scl_pdb_t> m_SclPdbTable;

    static tes_common_ais::bmi_config_parser::BmiEthcfg_t m_BmiEthConfigTable;

    std::atomic<bool> m_InitDone;
    uint_least32_t m_Fid;
    std::string m_JsonConfigFile;

    // csf_http_server
    sockaddr_in m_SockAddr;
    csf_httpd_config_t m_HttpdConfig;
    csf_httpd_server_t *m_pHttpdServer;

    // csf_pgt_server
    csf_pgt_server_config_t m_PgtServerConfig;
};

#endif
