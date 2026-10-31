////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Caterpillar Inc.  All Rights Reserved.
//
//     Class: bmi_ethernet_parser
//
// File Name: bmi_ethernet_parser.cpp
//
//  Abstract: Implementation of the class that builds
//            the tables used in the setup of
//            the OEL task and does the hardware initialization.
//
////////////////////////////////////////////////////////
#include <algorithm> // std::find
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <ais/log/AisLogger.h>

#include <interfaces/DataLinkDataWrapper/DataLinkDataWrapper.h>

#include "bmi_ethernet_parser.h"

////////////////////////////////////////////////////////////////////////////

// The following macro wraps an instruction/operation into a try-catch block and outputs a log message in case of failure
#define BMIETHCFG_WRAP(instruction, flag, failureLogMsg, ...)        \
    try                                                              \
    {                                                                \
        instruction;                                                 \
        flag = true;                                                 \
    }                                                                \
    catch (const std::exception &e)                                  \
    {                                                                \
        AIS_LOG_INFO(failureLogMsg ": [[%s]]", ##__VA_ARGS__, e.what()); \
        flag = false;                                                \
    }

namespace tes_common_ais
{
namespace bmi_config_parser {

// Forward delcarations
static bool ValidateConfig(const BmiEthcfg_t& BmiEthCfgTbl);
static bool ValidatePidConfig(const BmiEthcfg_t& BmiEthCfgTbl);
static bool ValidateSpnConfig(const BmiEthcfg_t& BmiEthCfgTbl);
static bool ValidateExtIdConfig(const BmiEthcfg_t& BmiEthCfgTbl);

////////////////////////////////////////////////////////////////////////////
// Function        : GetJSONParam
// Description     : This function extract a parameter from a Property Tree
//                   built off JSON file
// Return Type     : bool - 'true' if extracted without errors, 'false' otherwise
// Argument [in]   : const boost::property_tree::ptree& propertyTree - Reference
//                      to the Property Tree,
//                   const std::string& parameterName - Name of the JSON element,
//                   const std::string& fieldName - Name of the parameter within
//                      JSON element
// Argument [out]  : T& dataStorage - Storage for the parameter
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
template <typename T>
static bool GetJSONParam(const boost::property_tree::ptree &propertyTree,
                         const std::string &parameterName,
                         const std::string &fieldName,
                         T &dataStorage)
{
    bool returnFlag = false;
    const std::string extractNode = parameterName + "." + fieldName;

    AIS_LOG_INFO("Attempting to extract %s for '%s'", fieldName.c_str(), parameterName.c_str());
    BMIETHCFG_WRAP(dataStorage = propertyTree.get<T>(extractNode),
                   returnFlag, "%s for '%s' has failed the extraction", fieldName.c_str(), parameterName.c_str())

    return returnFlag;
}

////////////////////////////////////////////////////////////////////////////
// Function        : GetJSONParamU32
// Description     : This function extract a parameter from a Property Tree
//                   built off JSON file which process the parameter as a
//                   hexadecimal string (JSON does not support hex notation)
// Return Type     : bool - 'true' if converted successfully, 'false' otherwise
// Argument [in]   : const boost::property_tree::ptree& propertyTree - Reference
//                      to the Property Tree,
//                   const std::string& parameterName - Name of the JSON element,
//                   const std::string& fieldName - Name of the parameter within
//                      JSON element
// Argument [out]  : unsigned_32& dataStorage - Storage for the parameter
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
static bool GetJSONParamU32(const boost::property_tree::ptree &propertyTree,
                            const std::string &parameterName,
                            const std::string &fieldName,
                            unsigned_32 &dataStorage)
{
    bool returnFlag = false;
    std::string tempStorageStr;
    unsigned_32 tempStorageNum = 0;

    // Extract parameter as a hexadecimal string
    if (!returnFlag && GetJSONParam(propertyTree, parameterName, fieldName, tempStorageStr))
    {
        std::size_t numCharsProcessed = 0;
        AIS_LOG_INFO("Parsing '%s' of '%s' as a string", fieldName.c_str(), parameterName.c_str());
        BMIETHCFG_WRAP(tempStorageNum = std::stoul(tempStorageStr, &numCharsProcessed, 16),
                       returnFlag,
                       "Failed to convert parameter '%s' field '%s' value '%s' to integer using hex base",
                       parameterName.c_str(), fieldName.c_str(), tempStorageStr.c_str())
        returnFlag &= (tempStorageStr.length() == numCharsProcessed);
    }

    if (returnFlag)
    {
        AIS_LOG_INFO("Converted parameter '%s' field '%s' to 0x%X", parameterName.c_str(), fieldName.c_str(), tempStorageNum);
        dataStorage = tempStorageNum;
    }

    return returnFlag;
}

////////////////////////////////////////////////////////////////////////////
// Function        : ParseJSONFile
// Description     : JSON file parser for SPN/CDL PID Data that populates local/class table
//                   with the handled SPN/CDL PID parameters
// Return Type     : bool - 'true' if parsed with no errors, 'false' otherwise
// Argument [in]   : const std::string& jsonConfigFileName - JSON file name
// Argument [out]  : BmiEthcfg_t& BmiEthCfgTbl - Parsed table
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool ParseJSONFile(const std::string &jsonConfigFileName, BmiEthcfg_t& BmiEthCfgTbl)
{
    // JSON Keys
    constexpr auto ETHERNET_ECM_SOURCE_CONFIG    = "Ethernet_ECM_Source_Config";
    // constexpr auto ETHERNET_PGN_CONFIG           = "PGN";
    constexpr auto ETHERNET_SPN_CONFIG           = "SPN";
    constexpr auto ETHERNET_CDL_PID_CONFIG       = "CDL_PID";
    constexpr auto ETHERNET_CAT_EXT_CONFIG       = "CAT_EXT_ID";
    // constexpr auto ECM_NAME                      = "ecm_name";
    constexpr auto ECM_FID                       = "ecm_fid";
    constexpr auto ECM_IP_ADDRESS                = "ip_address";
    constexpr auto ECM_CID                       = "cid";
    constexpr auto CDL_PID_ID                    = "CDL PID";
    constexpr auto SPN_ID                        = "SPN ID";
    constexpr auto CAT_EXT_ID                    = "CAT EXTID";
    constexpr auto DATA_SIZE_BYTES               = "Data Size(bytes)";
    constexpr auto DATA_SIZE_BITS                = "Data Size(bits)";
    constexpr auto DATA_BYTE_ORDER               = "Data Byte Order";
    constexpr auto REQUEST_PERIOD                = "Request Period(mu)";
    constexpr auto SOURCE_FID                    = "Source FID";
    constexpr auto DATA_TYPE                     = "Data Type";
    constexpr auto VAR_LENGTH_DATA_TYPE          = "VarLengthDataType";
    constexpr auto DSI_SUPPORT                   = "Dsi Support";
    constexpr auto DIAG_SUPPORT                  = "Diag Support";
    constexpr auto STATUS_CONV                   = "Status Conversion";
    constexpr auto SCALING                       = "Scaling";
    constexpr auto OFFSET                        = "Offset";
    constexpr auto UNITS                         = "Units";
    constexpr auto PID_PARM_PATTERN_UNSIGNED     = "unsigned";
    constexpr auto PID_PARM_PATTERN_DSI          = "Enable";
    constexpr auto PID_PARM_PATTERN_BYTE_ORDER   = "LSB";
    constexpr auto PID_PARM_PATTERN_DIAG_ENABLE  = "Enable";

    boost::property_tree::ptree propTree;
    bool ParseStatus = true;

    AIS_LOG_INFO("Parsing file %s", jsonConfigFileName.c_str());

    // Attempt to load the JSON file
    BMIETHCFG_WRAP(boost::property_tree::read_json(jsonConfigFileName, propTree),
                   ParseStatus, "Failed to read '%s'", jsonConfigFileName.c_str())

    if (ParseStatus)
    {
        // Go through each element of the JSON file
        for (auto &jsonElement : propTree)
        {
            // Check the JSON element name to see if this is a SPN parameter
            if (std::string::npos != jsonElement.first.find(ETHERNET_SPN_CONFIG))
            {
                AIS_LOG_INFO(" Found JSON element '%s' ", jsonElement.first.c_str());
                // Extract each node from the Identified JSON element
                for (auto &property : jsonElement.second)
                {
                    // Construct new entry with the element's name and all default parameters ENM
                    BmiEthSpnCfgTbl_t newSPNEntry{property.first, DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_SPN, FALSE, 0, 0, 0, 0, 1.0, 0};

                    AIS_LOG_INFO(" Parsing element '%s' ", newSPNEntry.ParamName.c_str());
                    AIS_LOG_INFO(" newSPNEntry.ParameterIdentifierType '%d' ", newSPNEntry.ParameterIdentifierType);

                    // Extract all mandatory parameters first
                    if (!GetJSONParamU32(jsonElement.second, newSPNEntry.ParamName, SPN_ID, newSPNEntry.spn))
                    {
                        AIS_LOG_ALERT(" Unable to retrieve SPN ID for parameter '%s'", newSPNEntry.ParamName.c_str());
                        ParseStatus = false;
                    }
                    else if (!GetJSONParam(jsonElement.second, newSPNEntry.ParamName, DATA_SIZE_BITS, newSPNEntry.size_in_bits))
                    {
                        AIS_LOG_ALERT("Unable to retrieve SPN data size for parameter '%s'", newSPNEntry.ParamName.c_str());
                        ParseStatus = false;
                    }
                    else if (!GetJSONParam(jsonElement.second, newSPNEntry.ParamName, REQUEST_PERIOD, newSPNEntry.RequestPeriod))
                    {
                        AIS_LOG_ALERT("Unable to retrieve SPN Request Rate for parameter '%s'", newSPNEntry.ParamName.c_str());
                        ParseStatus = false;
                    }
                    else if (!GetJSONParamU32(jsonElement.second, newSPNEntry.ParamName, SOURCE_FID, newSPNEntry.SourceFid))
                    {
                        AIS_LOG_ALERT("Unable to retrieve FID for parameter '%s'", newSPNEntry.ParamName.c_str());
                        ParseStatus = false;
                    }
                    else
                    {
                        std::string node_name = newSPNEntry.ParamName + ".";

                        std::string Byte_Order = jsonElement.second.get<std::string>(node_name + DATA_BYTE_ORDER);
                        
                        std::string Diag_Support = jsonElement.second.get<std::string>(node_name + DIAG_SUPPORT);

                        newSPNEntry.DiagSupport = (std::string::npos != Diag_Support.find(PID_PARM_PATTERN_DIAG_ENABLE)) ? CSF_PGT_CLIENT_DIAG_SUPPORTED : CSF_PGT_CLIENT_DIAG_NOT_SUPPORTED;
                        AIS_LOG_INFO(" newSPNEntry.DiagSupport:%d ", newSPNEntry.DiagSupport);
                        // Extract all optional parameters
                        (void)GetJSONParam(jsonElement.second, newSPNEntry.ParamName, SCALING, newSPNEntry.Scaling);
                        (void)GetJSONParam(jsonElement.second, newSPNEntry.ParamName, OFFSET, newSPNEntry.Offset);

                        // Add the new SPN with all its properties to the container
                        BmiEthCfgTbl.SpnCfg.push_back(newSPNEntry);
                    }
                }
            }
            // Check the JSON element name to see if this is a CDL PID parameter
            else if (std::string::npos != jsonElement.first.find(ETHERNET_CDL_PID_CONFIG))
            {
                AIS_LOG_INFO(" Found JSON element '%s' ", jsonElement.first.c_str());
                // Extract each node from the Identified JSON element
                for (auto &property : jsonElement.second)
                {
                    // Construct new entry with the element's name and all default parameters
                    BmiEthPidCfgTbl_t newPIDEntry{property.first, DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID, 0, 0, 0, 0, 0, "", 0, "", 0, 0, 1.0, 0, DataLinkParamInfo::DATA_LINK_PARAM_CDL_UNITS_NO_UNIT};
                    AIS_LOG_INFO(" Parsing element '%s' ", newPIDEntry.ParamName.c_str());
                    AIS_LOG_INFO(" newPIDEntry.ParameterIdentifierType '%d' ", newPIDEntry.ParameterIdentifierType);
                    // Extract all mandatory parameters first
                    if (!GetJSONParamU32(jsonElement.second, newPIDEntry.ParamName, CDL_PID_ID, newPIDEntry.data_ID))
                    {
                        AIS_LOG_ALERT(" Unable to retrieve CDL PID for parameter '%s'", newPIDEntry.ParamName.c_str());
                        ParseStatus = false;
                    }
                    else if (!GetJSONParam(jsonElement.second, newPIDEntry.ParamName, DATA_SIZE_BYTES, newPIDEntry.data_size))
                    {
                        AIS_LOG_ALERT("Unable to retrieve PID data size for parameter '%s'", newPIDEntry.ParamName.c_str());
                        ParseStatus = false;
                    }
                    else if (!GetJSONParam(jsonElement.second, newPIDEntry.ParamName, REQUEST_PERIOD, newPIDEntry.RequestPeriod))
                    {
                        AIS_LOG_ALERT("Unable to retrieve PID Request Rate for parameter '%s'", newPIDEntry.ParamName.c_str());
                        ParseStatus = false;
                    }
                    else if (!GetJSONParamU32(jsonElement.second, newPIDEntry.ParamName, SOURCE_FID, newPIDEntry.SourceFid))
                    {
                        AIS_LOG_ALERT("Unable to retrieve FID for parameter '%s'", newPIDEntry.ParamName.c_str());
                        ParseStatus = false;
                    }
                    else
                    {
                        std::string node_name = newPIDEntry.ParamName + ".";

                        newPIDEntry.ByteOrder = jsonElement.second.get<std::string>(node_name + DATA_BYTE_ORDER);
                        std::string strDataType = jsonElement.second.get<std::string>(node_name + DATA_TYPE);
                        newPIDEntry.DsiSupport = jsonElement.second.get<std::string>(node_name + DSI_SUPPORT);
                        uint8_t enableDsi = (std::string::npos != newPIDEntry.DsiSupport.find(PID_PARM_PATTERN_DSI)) ? SCL_PDB_PID_DSI_AVAIL : SCL_PDB_PID_DSI_NA;

                        if (boost::iequals("signed_8", strDataType))
                        {
                            newPIDEntry.ParameterType = ((enableDsi == SCL_PDB_PID_DSI_AVAIL) ? CDL2_I8_DSI : CDL2_I8_NO_DSI);
                        }
                        else if (boost::iequals("signed_16", strDataType))
                        {
                            newPIDEntry.ParameterType = ((enableDsi == SCL_PDB_PID_DSI_AVAIL) ? CDL2_I16_DSI : CDL2_I16_NO_DSI);
                        }
                        else if (boost::iequals("signed_32", strDataType))
                        {
                            newPIDEntry.ParameterType = ((enableDsi == SCL_PDB_PID_DSI_AVAIL) ? CDL2_I32_DSI : CDL2_I32_NO_DSI);
                        }
                        else if (boost::iequals("unsigned_8", strDataType))
                        {
                            newPIDEntry.ParameterType = ((enableDsi == SCL_PDB_PID_DSI_AVAIL) ? CDL2_U8_DSI : CDL2_U8_NO_DSI);
                        }
                        else if (boost::iequals("unsigned_16", strDataType))
                        {
                            newPIDEntry.ParameterType = ((enableDsi == SCL_PDB_PID_DSI_AVAIL) ? CDL2_U16_DSI : CDL2_U16_NO_DSI);
                        }
                        else if (boost::iequals("unsigned_32", strDataType))
                        {
                            newPIDEntry.ParameterType = ((enableDsi == SCL_PDB_PID_DSI_AVAIL) ? CDL2_U32_DSI : CDL2_U32_NO_DSI);
                        }
                        else
                        {
                            AIS_LOG_FATAL("Failed convert param %x data type %s", newPIDEntry.data_ID, strDataType);
                        }

                        AIS_LOG_DEBUG("ByteOrder:%s ", newPIDEntry.ByteOrder.c_str());
                        AIS_LOG_DEBUG("%s is ParameterType:%d ", strDataType.c_str(), newPIDEntry.ParameterType);
                        AIS_LOG_DEBUG("DsiSupport:%s ", newPIDEntry.DsiSupport.c_str());
                        //setting PID flags
                        newPIDEntry.flags = ((std::string::npos != newPIDEntry.ByteOrder.find(PID_PARM_PATTERN_BYTE_ORDER)) ? SCL_PDB_PID_LSB : SCL_PDB_PID_MSB) |
                                                     (((std::string::npos != strDataType.find(PID_PARM_PATTERN_UNSIGNED)) ? SCL_PDB_PID_UNSIGNED : SCL_PDB_PID_SIGNED)) |
                                                     (enableDsi);
                        AIS_LOG_DEBUG("newPIDEntry.flags: %d ", newPIDEntry.flags);

                        std::string Diag_Support = jsonElement.second.get<std::string>(node_name + DIAG_SUPPORT);
                        newPIDEntry.DiagSupport = (std::string::npos != Diag_Support.find(PID_PARM_PATTERN_DIAG_ENABLE)) ? CSF_PGT_CLIENT_DIAG_SUPPORTED : CSF_PGT_CLIENT_DIAG_NOT_SUPPORTED;
                        AIS_LOG_DEBUG(" newPIDEntry.DiagSupport:%d ", newPIDEntry.DiagSupport);

                        (void)GetJSONParam(jsonElement.second, newPIDEntry.ParamName, VAR_LENGTH_DATA_TYPE, newPIDEntry.VarLengthDataType);
                        (void)GetJSONParam(jsonElement.second, newPIDEntry.ParamName, SCALING, newPIDEntry.Scaling);
                        (void)GetJSONParam(jsonElement.second, newPIDEntry.ParamName, OFFSET, newPIDEntry.Offset);
                        newPIDEntry.Units = static_cast<DataLinkParamInfo::DlpUnits_t>(jsonElement.second.get<int>(node_name + UNITS));

                        // Add the new PID with all its properties to the container
                        BmiEthCfgTbl.PidCfg.push_back(newPIDEntry);
                    }
                }
            }

            // Check the JSON element name to see if this is a CAT EXT parameter
            else if (std::string::npos != jsonElement.first.find(ETHERNET_CAT_EXT_CONFIG))
            {
                AIS_LOG_INFO(" Found JSON element '%s' ", jsonElement.first.c_str());
                // Extract each node from the Identified JSON element
                for (auto &property : jsonElement.second)
                {
                    // Construct new entry with the element's name and all default parameters
                    BmiEthCatExtIdCfgTbl_t newExtIdEntry{property.first, DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT, 0, 0, 0, 0, 0};

                    AIS_LOG_INFO(" Parsing element '%s' ", newExtIdEntry.ParamName.c_str());
                    AIS_LOG_INFO(" newSPNEntry.ParameterIdentifierType '%d' ", newExtIdEntry.ParameterIdentifierType);
                    unsigned_32 CatExtId;
                    // Extract all mandatory parameters first
                    if (!GetJSONParamU32(jsonElement.second, newExtIdEntry.ParamName, CAT_EXT_ID, CatExtId))
                    {
                        AIS_LOG_ALERT(" Unable to retrieve CAT EXT-ID for parameter '%s'", newExtIdEntry.ParamName.c_str());
                        ParseStatus = false;
                    }
                    else if (!GetJSONParam(jsonElement.second, newExtIdEntry.ParamName, DATA_SIZE_BYTES, newExtIdEntry.data_size))
                    {
                        AIS_LOG_ALERT("Unable to retrieve CAT EXT-ID data size for parameter '%s'", newExtIdEntry.ParamName.c_str());
                        ParseStatus = false;
                    }
                    else if (!GetJSONParam(jsonElement.second, newExtIdEntry.ParamName, REQUEST_PERIOD, newExtIdEntry.RequestPeriod))
                    {
                        AIS_LOG_ALERT("Unable to retrieve CAT EXT-ID Request Rate for parameter '%s'", newExtIdEntry.ParamName.c_str());
                        ParseStatus = false;
                    }
                    else if (!GetJSONParamU32(jsonElement.second, newExtIdEntry.ParamName, SOURCE_FID, newExtIdEntry.SourceFid))
                    {
                        AIS_LOG_ALERT("Unable to retrieve FID for parameter '%s'", newExtIdEntry.ParamName.c_str());
                        ParseStatus = false;
                    }
                    else
                    {
                        newExtIdEntry.cat_ext_id = static_cast<uint_least16_t>(CatExtId);
                        std::string node_name = newExtIdEntry.ParamName + ".";

                        std::string Diag_Support = jsonElement.second.get<std::string>(node_name + DIAG_SUPPORT);

                        newExtIdEntry.DiagSupport = (std::string::npos != Diag_Support.find(PID_PARM_PATTERN_DIAG_ENABLE)) ? CSF_PGT_CLIENT_DIAG_SUPPORTED : CSF_PGT_CLIENT_DIAG_NOT_SUPPORTED;
                        AIS_LOG_INFO(" newExtIdEntry.DiagSupport:%d ", newExtIdEntry.DiagSupport);

                        // Add the new CAT EXT ID with all its properties to the container
                        BmiEthCfgTbl.ExtIdCfg.push_back(newExtIdEntry);
                    }
                }
            }
            // Check the JSON element name to see if this is a ECM CONFIG parameter
            else if (std::string::npos != jsonElement.first.find(ETHERNET_ECM_SOURCE_CONFIG))
            {
                AIS_LOG_INFO(" Found JSON element '%s' ", jsonElement.first.c_str());
                for (auto &property : jsonElement.second)
                {
                    // Construct new entry with the element's name and all default parameters
                    BmiEthEcmCfg_t newECMEntry{property.first, 0, 0, 0};
                    AIS_LOG_INFO(" Parsing element '%s' ", newECMEntry.EcmId.c_str());

                    // Extract all mandatory parameters first
                    if (!GetJSONParamU32(jsonElement.second, newECMEntry.EcmId, ECM_FID, newECMEntry.Fid))
                    {
                        AIS_LOG_ALERT(" Unable to retrieve FID for parameter '%s'", newECMEntry.EcmId.c_str());
                        ParseStatus = false;
                    }
                    if (!GetJSONParamU32(jsonElement.second, newECMEntry.EcmId, ECM_IP_ADDRESS, newECMEntry.IPAddress))
                    {
                        AIS_LOG_ALERT(" Unable to retrieve IP Address for parameter '%s'", newECMEntry.EcmId.c_str());
                        ParseStatus = false;
                    }
                    else
                    {
                        (void)GetJSONParam(jsonElement.second, newECMEntry.EcmId, ECM_CID, newECMEntry.Cid);

                        // Add the new PID with all its properties to the container
                        BmiEthCfgTbl.EcmSrcCfg.push_back(newECMEntry);
                    }
                }
            }
            else
            {
                AIS_LOG_ALERT(" UnIdentified JSON element ");
            }
        }
    }

    if (!ParseStatus)
    {
        AIS_LOG_ERROR("JSON file '%s' contains errors", jsonConfigFileName.c_str());
    }
    else if (ValidateConfig(BmiEthCfgTbl))
    {
        ParseStatus = true;
    }

    return ParseStatus;
}

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939Config::ValidateConfigTables
// Description     : Validate the json config table
// Return Type     : bool - 'true' if configured with correct values, 'false' otherwise
// Argument [in]   : BmiEthcfg_t&  BmiEthCfgTbl
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
static bool ValidateConfig(const BmiEthcfg_t& BmiEthCfgTbl)
{
    AIS_LOG_INFO("PID size : %d, Spn Size: %d, CatExtId size: %d", BmiEthCfgTbl.PidCfg.size(), BmiEthCfgTbl.SpnCfg.size(), BmiEthCfgTbl.ExtIdCfg.size());

    if (!ValidatePidConfig(BmiEthCfgTbl))
    {
        AIS_LOG_ERROR("PID validation failed.");
        return false;
    }

    if (!ValidateSpnConfig(BmiEthCfgTbl))
    {
        AIS_LOG_ERROR("SPN validation failed.");
        return false;
    }

    if (!ValidateExtIdConfig(BmiEthCfgTbl))
    {
        AIS_LOG_ERROR("CAT EXT ID validation failed.");
        return false;
    }

    return true;
}

static bool ValidatePidConfig(const BmiEthcfg_t& BmiEthCfgTbl)
{

    if (BmiEthCfgTbl.PidCfg.size() <= 0)
    {
        return true;
    }

    for (const auto &jsonPidBlock : (BmiEthCfgTbl.PidCfg))
    {
        bool Valid = false;
        for (const auto &jsonEcmCfgBlock : (BmiEthCfgTbl.EcmSrcCfg))
        {
            if (jsonEcmCfgBlock.Fid == jsonPidBlock.SourceFid)
            {
                Valid = true;
            }
        }
        if (false == Valid)
        {
            AIS_LOG_ERROR(" Configured Source FID 0x%X does not match any in ECM config table for PID 0x%X", jsonPidBlock.SourceFid, jsonPidBlock.data_ID);
            return Valid;
        }
    }

    return true;
}
static bool ValidateSpnConfig(const BmiEthcfg_t& BmiEthCfgTbl)
{
    if (BmiEthCfgTbl.SpnCfg.size() <= 0)
    {
        return true;
    }
    for (const auto &jsonSpnBlock : (BmiEthCfgTbl.SpnCfg))
    {
        bool Valid = false;
        for (const auto &jsonEcmCfgBlock : (BmiEthCfgTbl.EcmSrcCfg))
        {
            if (jsonEcmCfgBlock.Fid == jsonSpnBlock.SourceFid)
            {
                Valid = true;
            }
        }
        if (false == Valid)
        {
            AIS_LOG_ERROR(" Configured Source FID 0x%X does not match any in ECM config table for SPN 0x%X", jsonSpnBlock.SourceFid, jsonSpnBlock.spn);
            return Valid;
        }
    }

    return true;
}

static bool ValidateExtIdConfig(const BmiEthcfg_t& BmiEthCfgTbl)
{
    if (BmiEthCfgTbl.ExtIdCfg.size() <= 0)
    {
        return true;
    }
    for (const auto &jsonExtIdBlock : (BmiEthCfgTbl.ExtIdCfg))
    {
        bool Valid = false;
        for (const auto &jsonEcmCfgBlock : (BmiEthCfgTbl.EcmSrcCfg))
        {
            if (jsonEcmCfgBlock.Fid == jsonExtIdBlock.SourceFid)
            {
                Valid = true;
            }
        }
        if (false == Valid)
        {
            AIS_LOG_ERROR(" Configured Source FID 0x%X does not match any in ECM config table for CAT EXT ID 0x%X", jsonExtIdBlock.cat_ext_id);
            return Valid;
        }
    }

    return true;
}

bool AddToDataLinkDataWrapper(const BmiEthcfg_t& bmiEthcfg)
{
    // Add PIDs to DataLinkData
    for (const auto& newPIDEntry : bmiEthcfg.PidCfg)
    {
        // Adding data to the new dlDataMap
        DataLinkParam dlParam;

        dlParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_ETH);
        dlParam.SetParameterName(newPIDEntry.ParamName);
        dlParam.SetParamIdentifierType(newPIDEntry.ParameterIdentifierType);
        dlParam.SetParamId(newPIDEntry.data_ID);
        dlParam.SetParameterType(newPIDEntry.ParameterType);
        dlParam.SetVarLengthParamType(static_cast<VarLengthDataLinkParamPool::VarLengthParamType>(newPIDEntry.VarLengthDataType));
        dlParam.SetSid(newPIDEntry.SourceFid);
        dlParam.SetScaling(newPIDEntry.Scaling);
        dlParam.SetOffset(newPIDEntry.Offset);
        dlParam.SetUnits(newPIDEntry.Units);

        // Add Data to Data Link SCS channel
        if (!DataLinkDataWrapper::AddDataLinkData(dlParam))
        {
            return false;
        }
    }

    // Add CAT EXT IDs to DataLinkData
    for (const auto& newExtIdEntry : bmiEthcfg.ExtIdCfg)
    {
        // Adding data to the new dlDataMap
        DataLinkParam dlParam;

        dlParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_ETH);
        dlParam.SetParameterName(newExtIdEntry.ParamName);
        dlParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT);
        dlParam.SetParamId(newExtIdEntry.cat_ext_id);

        // Set ParameterType, assumes all CAT EXT IDs are unsigned with no DSI
        switch (newExtIdEntry.data_size)
        {
        case 1:
            dlParam.SetParameterType(CDL2_U8_NO_DSI);
            break;
        case 2:
            dlParam.SetParameterType(CDL2_U16_NO_DSI);
            break;
        case 3:
        case 4: // Intentional fall-through
            dlParam.SetParameterType(CDL2_U32_NO_DSI);
            break;
        default:
            dlParam.SetParameterType(CDL2_VAR_NO_DSI);
            break;
        }

        dlParam.SetSid(newExtIdEntry.SourceFid);

        // No Scaling/Offset for CAT EXT ID
        dlParam.SetScaling(1);
        dlParam.SetOffset(0);

        //Add Data to Data Link SCS channel
        if (!DataLinkDataWrapper::AddDataLinkData(dlParam))
        {
            return false;
        }
    }

    // Add SPNs to DataLinkData
    for (const auto& newSPNEntry : bmiEthcfg.SpnCfg)
    {
        // Adding data to the new dlDataMap
        DataLinkParam dlParam;

        dlParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_ETH);
        dlParam.SetParameterName(newSPNEntry.ParamName);
        dlParam.SetParamIdentifierType(newSPNEntry.ParameterIdentifierType);
        dlParam.SetParamId(newSPNEntry.spn);

        // Set ParameterType, assumes all SPNSs are unsigned with no DSI
        if (newSPNEntry.size_in_bits <= 8)
        {
            dlParam.SetParameterType(CDL2_U8_NO_DSI);
        }
        else if (newSPNEntry.size_in_bits <= 16)
        {
            dlParam.SetParameterType(CDL2_U16_NO_DSI);
        }
        else if (newSPNEntry.size_in_bits <= 32)
        {
            dlParam.SetParameterType(CDL2_U32_NO_DSI);
        }
        else
        {
            dlParam.SetParameterType(CDL2_VAR_NO_DSI);
        }

        dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::SPN);
        dlParam.SetSid(newSPNEntry.SourceFid);
        dlParam.SetScaling(newSPNEntry.Scaling);
        dlParam.SetOffset(newSPNEntry.Offset);

        //Add Data to Data Link SCS channel
        if (!DataLinkDataWrapper::AddDataLinkData(dlParam))
        {
            return false;
        }
    }

    return true;
}

void RemoveEntriesByFid(BmiEthcfg_t& bmiEthcfg, uint32_t fid)
{

    bmiEthcfg.PidCfg.erase(std::remove_if(bmiEthcfg.PidCfg.begin(), bmiEthcfg.PidCfg.end(),
                                [fid](const BmiEthPidCfgTbl_t& pidInfo)
                                { return pidInfo.SourceFid != fid; }
                                ), bmiEthcfg.PidCfg.end());

    bmiEthcfg.SpnCfg.erase(std::remove_if(bmiEthcfg.SpnCfg.begin(), bmiEthcfg.SpnCfg.end(),
                                [fid](const BmiEthSpnCfgTbl_t& spnInfo)
                                { return spnInfo.SourceFid != fid; }
                                ), bmiEthcfg.SpnCfg.end());

    bmiEthcfg.ExtIdCfg.erase(std::remove_if(bmiEthcfg.ExtIdCfg.begin(), bmiEthcfg.ExtIdCfg.end(),
                                [fid](const BmiEthCatExtIdCfgTbl_t& catExtIdInfo)
                                { return catExtIdInfo.SourceFid != fid; }
                                ), bmiEthcfg.ExtIdCfg.end());
}

bool GetRxPidConfigTable(const BmiEthcfg_t& bmiEthcfg, RxPidConfigTable_t& rxPidConfigTable)
{
    for (const auto& entry : bmiEthcfg.PidCfg)
    {
        scl_pdb_pid_rx_config_t pidRxConfig;
        pidRxConfig.data_ID = entry.data_ID;
        pidRxConfig.data_size = entry.data_size;
        pidRxConfig.flags = entry.flags;
        rxPidConfigTable[entry.data_ID] = pidRxConfig;
    }
    return true;
}

bool GetRxSpnConfigTable(const BmiEthcfg_t& bmiEthcfg, RxSpnConfigTable_t& rxSpnConfigTable)
{
    for (const auto& entry : bmiEthcfg.SpnCfg)
    {
        scl_pdb_spn_rx_config_t spnRxConfig;
        spnRxConfig.spn = entry.spn;
        spnRxConfig.size_in_bits = entry.size_in_bits;
        // ENM spnRxConfig.status_conv = entry.status_conv;
        // ENM spnRxConfig.byte_order = entry.byte_order;
        rxSpnConfigTable[entry.spn] = spnRxConfig;
    }
    return true;
}

bool GetRxCatExtIdConfigTable(const BmiEthcfg_t& bmiEthcfg, RxCatExtIdConfigTable_t& rxCatExtIdConfigTable)
{
    for (const auto& entry : bmiEthcfg.ExtIdCfg)
    {
        scl_pdb_cat_ext_id_rx_config_t catExtIdRxConfig;
        catExtIdRxConfig.cat_ext_id = entry.cat_ext_id;
        catExtIdRxConfig.data_size = entry.data_size;
        rxCatExtIdConfigTable[entry.cat_ext_id] = catExtIdRxConfig;
    }
    return true;
}

bool GetTxSpnConfigTable(const BmiEthcfg_t& bmiEthcfg, TxSpnConfigTable_t& txSpnConfigTable)
{
    // Enable the Tx PID on all protocols/datalinks
    static const uint_least32_t featureFlag{CDL2_PIT_ALL_FEATURES_ENABLE};
    for (const auto& entry : bmiEthcfg.SpnCfg)
    {
        scl_pdb_spn_tx_config_t spnTxConfig;
        spnTxConfig.spn = entry.spn;
        spnTxConfig.size_in_bits = entry.size_in_bits;
        spnTxConfig.feature_flag = &featureFlag;
        txSpnConfigTable[entry.spn] = spnTxConfig;
    }
    return true;
}

bool GetTxCatExtIdConfigTable(const BmiEthcfg_t& bmiEthcfg, TxCatExtIdConfigTable_t& txCatExtIdConfigTable)
{
    for (const auto& entry : bmiEthcfg.ExtIdCfg)
    {
        scl_pdb_cat_ext_id_tx_config_t catExtIdTxConfig;
        catExtIdTxConfig.cat_ext_id = entry.cat_ext_id;
        catExtIdTxConfig.data_size = entry.data_size;
        txCatExtIdConfigTable[entry.cat_ext_id] = catExtIdTxConfig;
    }
    return true;
}

void PrintConfigTables( const tes_common_ais::bmi_config_parser::BmiEthcfg_t& appEthCfgTbl )
{
   AIS_LOG_INFO("Printing the Json Tables Data");
   for ( const auto& jsonPidBlock : (appEthCfgTbl.PidCfg) )
   {
       AIS_LOG_INFO("jsonPidBlock.ParameterName %s", jsonPidBlock.ParamName.c_str());
       AIS_LOG_INFO("jsonPidBlock.ParameterNumber 0x%X", jsonPidBlock.data_ID);
       AIS_LOG_INFO("jsonPidBlock.SourceFID 0x%X", jsonPidBlock.SourceFid);
       AIS_LOG_INFO("jsonPidBlock.RequestPeriod: %u",jsonPidBlock.RequestPeriod);
       AIS_LOG_INFO("jsonPidBlock.DataSize: %d",jsonPidBlock.data_size);
       AIS_LOG_INFO("jsonPidBlock.flags 0x%X", jsonPidBlock.flags);
       AIS_LOG_INFO("jsonPidBlock.VarLengthDataType: %d",jsonPidBlock.VarLengthDataType);
       AIS_LOG_INFO("jsonPidBlock.Scaling: %f",jsonPidBlock.Scaling);
       AIS_LOG_INFO("jsonPidBlock.Offset: %f",jsonPidBlock.Offset);
       AIS_LOG_INFO("jsonPidBlock.Units: %u",jsonPidBlock.Units);
       AIS_LOG_INFO("jsonPidBlock.DiagSupport: %d",jsonPidBlock.DiagSupport);
       AIS_LOG_INFO("jsonPidBlock.ParameterIdentifierType: %d",jsonPidBlock.ParameterIdentifierType);
   }

  for ( const auto& jsonSpnBlock : (appEthCfgTbl.SpnCfg) )
  {
       AIS_LOG_INFO("jsonSpnBlock.ParameterName %s", jsonSpnBlock.ParamName.c_str());
       AIS_LOG_INFO("jsonSpnBlock.ParameterNumber 0x%X", jsonSpnBlock.spn);
       AIS_LOG_INFO("jsonSpnBlock.SourceFID 0x%X", jsonSpnBlock.SourceFid);
       AIS_LOG_INFO("jsonSpnBlock.RequestPeriod: %u",jsonSpnBlock.RequestPeriod);
       AIS_LOG_INFO("jsonSpnBlock.DataSize: %d",jsonSpnBlock.size_in_bits);
     // ENM   AIS_LOG_INFO("jsonSpnBlock.Byte_order 0x%X", jsonSpnBlock.byte_order);
     // ENM   AIS_LOG_INFO("jsonSpnBlock.Status_conv: %d ", jsonSpnBlock.status_conv);
       AIS_LOG_INFO("jsonSpnBlock.Scaling: %f",jsonSpnBlock.Scaling);
       AIS_LOG_INFO("jsonSpnBlock.Offset: %f",jsonSpnBlock.Offset);
       AIS_LOG_INFO("jsonSpnBlock.DiagSupport: %d",jsonSpnBlock.DiagSupport);
       AIS_LOG_INFO("jsonSpnBlock.ParameterIdentifierType: %d",jsonSpnBlock.ParameterIdentifierType);

   }

  for ( const auto& jsonExtIdBlock : (appEthCfgTbl.ExtIdCfg) )
   {
       AIS_LOG_INFO("jsonExtIdBlock.ParameterName %s", jsonExtIdBlock.ParamName.c_str());
       AIS_LOG_INFO("jsonExtIdBlock.ParameterNumber 0x%X", jsonExtIdBlock.cat_ext_id);
       AIS_LOG_INFO("jsonExtIdBlock.SourceFID 0x%X", jsonExtIdBlock.SourceFid);
       AIS_LOG_INFO("jsonExtIdBlock.RequestPeriod: %u",jsonExtIdBlock.RequestPeriod);
       AIS_LOG_INFO("jsonExtIdBlock.DataSize: %d",jsonExtIdBlock.data_size);
       AIS_LOG_INFO("jsonExtIdBlock.DiagSupport: %d",jsonExtIdBlock.DiagSupport);
       AIS_LOG_INFO("jsonExtIdBlock.ParameterIdentifierType: %d",jsonExtIdBlock.ParameterIdentifierType);

   }

  for ( const auto& jsonEcmCfgBlock : (appEthCfgTbl.EcmSrcCfg) )
  {
       AIS_LOG_INFO("jsonEcmCfgBlock.EcmId %s", jsonEcmCfgBlock.EcmId.c_str());
       AIS_LOG_INFO("jsonEcmCfgBlock.FID 0x%X", jsonEcmCfgBlock.Fid);
       AIS_LOG_INFO("jsonEcmCfgBlock.IPAddress 0x%X", jsonEcmCfgBlock.IPAddress);
       AIS_LOG_INFO("jsonEcmCfgBlock.CID %d", jsonEcmCfgBlock.Cid);

  }
}

}
}