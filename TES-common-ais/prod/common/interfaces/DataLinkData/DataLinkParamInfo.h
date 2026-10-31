////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: DataLinkParamInfo
//
// File Name: DataLinkParamInfo.h
//
//  Abstract: SCS interface for data link parameters.
//
////////////////////////////////////////////////////////
#ifndef DATALINKPARAMINFO_H
#define DATALINKPARAMINFO_H

#include <sstream>
#include <string>
#include <unordered_map>

#ifndef STD_T_H_
#include <std_t.h>
#endif

#include <boost/serialization/access.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/vector.hpp>

#include <ais/log/AisLogger.h>
#include <ais/serialization/csvable.h>
#include <taskPlugins/interfaces/DatalinkParameterDataTypes.h>
#include "VarLengthDataLinkParamFactory_decl.h"


class DataLinkParamInfo : public csvable
{
   public:
      static constexpr unsigned int DATALINK_PARAM_VERSION = 5;
      static constexpr cdl2_parameter_type_t CDL2_DOUBLE = static_cast<cdl2_parameter_type_t>(datalink::DataType::DOUBLE);
      using PidKey_t = uint32_t;

      DataLinkParamInfo() :
          paramIdentifierType(DATA_LINK_PARAM_IDENTIFIER_UNKNOWN),
          DlType(DATA_LINK_PARAM_UNKNOWN),
          SourceId(),
          ParamId(),
          ParameterType(255),
          VarLengthParamType(VarLengthDataLinkParamFactory::NOT_APPLICABLE),
          Scaling(),
          Offset(),
          Units(),
          paramInitStatus(0),
          paramName() {}
           
      virtual ~DataLinkParamInfo() {}

      typedef enum
      {
         DATA_LINK_PARAM_CDL = 0,
         DATA_LINK_PARAM_CAN1_1939,
         DATA_LINK_PARAM_CAN2_1939,
         DATA_LINK_PARAM_CAN3_1939,
         DATA_LINK_PARAM_ETH,
         DATA_LINK_PARAM_INT,     // Internally generated
         DATA_LINK_PARAM_UNKNOWN, // Default value
         DATA_LINK_PARAM_UDP_CAN,
         DATA_LINK_PARAM_CDA
      } DlpDataLinkType_t;

      typedef enum
      {
          DATA_LINK_PARAM_IDENTIFIER_PID = 0,
          DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN,
          DATA_LINK_PARAM_IDENTIFIER_CAT_EXT,     // The first 3 are widely used
          DATA_LINK_PARAM_IDENTIFIER_PROP_A_PGN,   // In case of need
          DATA_LINK_PARAM_IDENTIFIER_SPN,
          DATA_LINK_PARAM_IDENTIFIER_UNKNOWN,
          DATA_LINK_PARAM_IDENTIFIER_CPOP,         // Configurable Periodic Output protocol
          DATA_LINK_PARAM_IDENTIFIER_S7_P,
          DATA_LINK_PARAM_IDENTIFIER_CDA
      } DlpParamIdentifierType_t;

      typedef enum
      {
         DATA_LINK_PARAM_CDL_STATUS_OK = 0,
         DATA_LINK_PARAM_CDL_STATUS_FAULT,
      }DlpCdlStatus_t;

      typedef enum
      {
         DATA_LINK_PARAM_CDL_UNITS_NO_UNIT = 0,
         DATA_LINK_PARAM_CDL_UNITS_KPA,
         DATA_LINK_PARAM_CDL_UNITS_KPA_,
         DATA_LINK_PARAM_CDL_UNITS_DEG_C,
         DATA_LINK_PARAM_CDL_UNITS_KM_PER_HR,
         DATA_LINK_PARAM_CDL_UNITS_RPM,
         DATA_LINK_PARAM_CDL_UNITS_VOLTS,
         DATA_LINK_PARAM_CDL_UNITS_LITERS,
         DATA_LINK_PARAM_CDL_UNITS_PERCENT,
         DATA_LINK_PARAM_CDL_UNITS_LTRS_PER_HR,
         DATA_LINK_PARAM_CDL_UNITS_DEG,
         DATA_LINK_PARAM_CDL_UNITS_MM,
         DATA_LINK_PARAM_CDL_UNITS_MM_,
         DATA_LINK_PARAM_CDL_UNITS_PULSES_PER_KM,
         DATA_LINK_PARAM_CDL_UNITS_KW,
         DATA_LINK_PARAM_CDL_UNITS_HRS,
         DATA_LINK_PARAM_CDL_UNITS_SEC,
         DATA_LINK_PARAM_CDL_UNITS_MS,
         DATA_LINK_PARAM_CDL_UNITS_NM,
         DATA_LINK_PARAM_CDL_UNITS_MIN,
         DATA_LINK_PARAM_CDL_UNITS_RPM_PER_SEC,
         DATA_LINK_PARAM_CDL_UNITS_METERS_PER_SEC,
         DATA_LINK_PARAM_CDL_UNITS_HZ,
         DATA_LINK_PARAM_CDL_UNITS_AMPS,
         DATA_LINK_PARAM_CDL_UNITS_Nm3_PER_HOUR,
         DATA_LINK_PARAM_CDL_UNITS_MJ_PER_NM3,
         DATA_LINK_PARAM_CDL_UNITS_OHMS,
         DATA_LINK_PARAM_CDL_UNITS_METERS_PER_SEC2,
         DATA_LINK_PARAM_CDL_UNITS_KG_PER_HR
      }DlpUnits_t;

      template <class Archive>
      void serialize(Archive &ar, unsigned int version)
      {
         // Old versions not supported
         if (version != DataLinkParamInfo::DATALINK_PARAM_VERSION) return;

         /* Archive Fields Here */
         ar & paramName;
         ar & paramIdentifierType;
         ar & SourceId;
         ar & ParamId;
         ar & ParameterType;
         ar & VarLengthParamType;
         ar & Scaling;
         ar & Offset;
         ar & Units;
         ar & paramInitStatus;
         ar & DlType;
      }

      void toCsv(CsvOutStream& out) const
      {
         out("Parameter Name", paramName);
         out("paramIdentifierType", paramIdentifierType);
         out("DlType", DlType);
         out("SourceId", SourceId);
         out("ParamId", ParamId);
         out("ParameterType", ParameterType);
         out("VarLengthParamType", VarLengthParamType);
         out("Scaling", Scaling);
         out("Offset", Offset);
         out("Units", Units);
      }

      DlpParamIdentifierType_t GetParamIdentifierType(void) const
      {
         return this->paramIdentifierType;
      }

      void SetParamIdentifierType(DlpParamIdentifierType_t paramIdType)
      {
         paramInitStatus |= identifierMask;
         this->paramIdentifierType = paramIdType;
      }

      ///////////////////////////////////////////////////////////////////////////////
      /// @brief Provide string representation of ParamIdentifierType
      ///
      /// @param none
      ///
      /// @return ParamIdentifierType converted to string
      ///
      ///////////////////////////////////////////////////////////////////////////////
      static const char* GetParamIdTypeCstr(const DataLinkParamInfo& dlParam)
      {
         const std::unordered_map<uint16_t, const char*> EnumStrings {
            { DATA_LINK_PARAM_IDENTIFIER_PID,         "PID" },
            { DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN,  "PUBLIC_PGN" },
            { DATA_LINK_PARAM_IDENTIFIER_CAT_EXT,     "CAT_EXT" },
            { DATA_LINK_PARAM_IDENTIFIER_PROP_A_PGN,  "PROP_A_PGN" },
            { DATA_LINK_PARAM_IDENTIFIER_SPN,         "SPN" },
            { DATA_LINK_PARAM_IDENTIFIER_CPOP,        "CPOP" },
            { DATA_LINK_PARAM_IDENTIFIER_CDA,         "CDA" }
         };
         auto   it  = EnumStrings.find(static_cast<uint16_t>(dlParam.paramIdentifierType));
         return it == EnumStrings.end() ? "--" : it->second;
      }
      static std::string GetParamIdTypeString(const DataLinkParamInfo& dlParam)
      {
         return GetParamIdTypeCstr(dlParam);
      }
      std::string GetParamIdTypeString() const
      {
         return GetParamIdTypeCstr(*this);
      }
      const char* GetParamIdTypeCstr() const
      {
         return GetParamIdTypeCstr(*this);
      }

      cdl2_parameter_type_t GetParameterType(void) const
      {
         return this->ParameterType;
      }

      void SetParameterType(cdl2_parameter_type_t parameterType)
      {
         paramInitStatus |= parameterTypeMask;
         this->ParameterType = parameterType;
      }

      ///////////////////////////////////////////////////////////////////////////////
      /// @brief Provide string representation of ParameterType
      ///
      /// @param none
      ///
      /// @return ParameterType converted to string
      ///
      ///////////////////////////////////////////////////////////////////////////////
      static const char* GetParameterTypeCstr(const DataLinkParamInfo& dlParam)
      {
         const std::unordered_map<cdl2_parameter_type_t, const char*> EnumStrings {
            { CDL2_U8_DSI,     "CDL2_U8_DSI" },
            { CDL2_I8_DSI,     "CDL2_I8_DSI" },
            { CDL2_U16_DSI,    "CDL2_U16_DSI" },
            { CDL2_I16_DSI,    "CDL2_I16_DSI" },
            { CDL2_U32_DSI,    "CDL2_U32_DSI" },
            { CDL2_I32_DSI,    "CDL2_I32_DSI" },
            { CDL2_U8_NO_DSI,  "CDL2_U8_NO_DSI" },
            { CDL2_I8_NO_DSI,  "CDL2_I8_NO_DSI" },
            { CDL2_U16_NO_DSI, "CDL2_U16_NO_DSI" },
            { CDL2_I16_NO_DSI, "CDL2_I16_NO_DSI" },
            { CDL2_U32_NO_DSI, "CDL2_U32_NO_DSI" },
            { CDL2_I32_NO_DSI, "CDL2_I32_NO_DSI" },
            { CDL2_VAR_NO_DSI, "CDL2_VAR_NO_DSI" }
         };
         auto   it  = EnumStrings.find(dlParam.ParameterType);
         return it == EnumStrings.end() ? "--" : it->second;
      }
      static std::string GetParameterTypeString(const DataLinkParamInfo& dlParam)
      {
         return GetParameterTypeCstr(dlParam);
      }
      std::string GetParameterTypeString() const
      {
         return GetParameterTypeCstr(*this);
      }
      const char* GetParameterTypeCstr() const
      {
         return GetParameterTypeCstr(*this);
      }

      /******************************************************************************
       FUNCTION NAME: SetDataLinkType
      DESCRIPTION: Set the DataLinkType for the DataLinkData object. Can be useful for diagnostics.
      PARAMETER DESCRIPTION:  dataLinkType: data link type .
      *******************************************************************************/
      void SetDataLinkType(DataLinkParamInfo::DlpDataLinkType_t dataLinkType)
      {
         DlType = dataLinkType;
      }

      static const char* GetDataLinkTypeCstr(const DataLinkParamInfo& dlParam)
      {
         const std::unordered_map<uint16_t, const char*> EnumStrings {
         { DataLinkParamInfo::DATA_LINK_PARAM_CDL,        "CDL" },
         { DataLinkParamInfo::DATA_LINK_PARAM_CAN1_1939,  "CAN1_1939" },
         { DataLinkParamInfo::DATA_LINK_PARAM_CAN2_1939,  "CAN2_1939" },
         { DataLinkParamInfo::DATA_LINK_PARAM_ETH,        "ETH" },
         { DataLinkParamInfo::DATA_LINK_PARAM_INT,        "INT" },
         { DataLinkParamInfo::DATA_LINK_PARAM_UDP_CAN,    "UDP_CAN" },
         { DataLinkParamInfo::DATA_LINK_PARAM_CDA,        "CDA" }
         };
         auto   it  = EnumStrings.find(static_cast<uint16_t>(dlParam.DlType));
         return it == EnumStrings.end() ? "--" : it->second;
      }

      const char* GetDataLinkTypeCstr() const
      {
         return GetDataLinkTypeCstr(*this);
      }

      /******************************************************************************
       FUNCTION NAME: GetDataLinkType
      DESCRIPTION: Get the DataLinkType for the DataLinkData object. Can be useful for diagnostics.
      RETURN VALUE: DlpDataLinkType
      *******************************************************************************/
      DataLinkParamInfo::DlpDataLinkType_t GetDataLinkType(void) const
      {
         return DlType;
      }

      ///////////////////////////////////////////////////////////////////////////////
      /// @brief Determines if parameter is encoded with DSI
      /// @return true if parameter has DSI false otherwise
      ///////////////////////////////////////////////////////////////////////////////
      bool UsesDsi() const
      {
         return ParameterType >= CDL2_U8_NO_DSI;
      }

      uint32_t GetSid(void) const
      {
         return this->SourceId;
      }
      void SetSid(uint32_t sourceId)
      {
          paramInitStatus |= sidMask;
          this->SourceId = sourceId;
      }

      uint64_t GetParamId(void) const
      {
         return this->ParamId;
      }
      void SetParamId(uint64_t pid)
      {
         paramInitStatus |= pidMask;
         ParamId = pid;
      }

      DlpUnits_t GetUnits(void) const
      {
         return this->Units;
      }

      void SetUnits(DlpUnits_t engUnits)
      {
         this->Units = engUnits;
      }

      ///////////////////////////////////////////////////////////////////////////////
      /// @brief Provide string representation of Units
      ///
      /// @param none
      ///
      /// @return Units converted to string
      ///
      ///////////////////////////////////////////////////////////////////////////////
      static const char* GetUnitsCstr(const DataLinkParamInfo& dlParam)
      {
         const std::unordered_map<uint16_t, const char*> EnumStrings {
            {DATA_LINK_PARAM_CDL_UNITS_NO_UNIT,         "NO_UNIT"           },
            {DATA_LINK_PARAM_CDL_UNITS_KPA,             "KPA"               },
            {DATA_LINK_PARAM_CDL_UNITS_KPA_,            "KPA_"              },
            {DATA_LINK_PARAM_CDL_UNITS_DEG_C,           "DEG_C"             },
            {DATA_LINK_PARAM_CDL_UNITS_KM_PER_HR,       "KM_PER_HR"         },
            {DATA_LINK_PARAM_CDL_UNITS_RPM,             "RPM"               },
            {DATA_LINK_PARAM_CDL_UNITS_VOLTS,           "VOLTS"             },
            {DATA_LINK_PARAM_CDL_UNITS_LITERS,          "LITERS"            },
            {DATA_LINK_PARAM_CDL_UNITS_PERCENT,         "PERCENT"           },
            {DATA_LINK_PARAM_CDL_UNITS_LTRS_PER_HR,     "LTRS_PER_HR"       },
            {DATA_LINK_PARAM_CDL_UNITS_DEG,             "DEG"               },
            {DATA_LINK_PARAM_CDL_UNITS_MM,              "MM"                },
            {DATA_LINK_PARAM_CDL_UNITS_MM_,             "MM_"               },
            {DATA_LINK_PARAM_CDL_UNITS_PULSES_PER_KM,   "PULSES_PER_KM"     },
            {DATA_LINK_PARAM_CDL_UNITS_KW,              "KW"                },
            {DATA_LINK_PARAM_CDL_UNITS_HRS,             "HRS"               },
            {DATA_LINK_PARAM_CDL_UNITS_SEC,             "SEC"               },
            {DATA_LINK_PARAM_CDL_UNITS_MS,              "MS"                },
            {DATA_LINK_PARAM_CDL_UNITS_NM,              "NM"                },
            {DATA_LINK_PARAM_CDL_UNITS_MIN,             "MIN"               },
            {DATA_LINK_PARAM_CDL_UNITS_RPM_PER_SEC,     "RPM_PER_SEC"       },
            {DATA_LINK_PARAM_CDL_UNITS_METERS_PER_SEC,  "METERS_PER_SEC"    },
            {DATA_LINK_PARAM_CDL_UNITS_HZ,              "HZ"                },
            {DATA_LINK_PARAM_CDL_UNITS_AMPS,            "AMPS"              },
            {DATA_LINK_PARAM_CDL_UNITS_Nm3_PER_HOUR,    "Nm3_PER_HOUR"      },
            {DATA_LINK_PARAM_CDL_UNITS_MJ_PER_NM3,      "MJ_PER_NM3"        },
            {DATA_LINK_PARAM_CDL_UNITS_OHMS,            "OHMS"              },
            {DATA_LINK_PARAM_CDL_UNITS_METERS_PER_SEC2, "METERS_PER_SEC2"   },
            {DATA_LINK_PARAM_CDL_UNITS_KG_PER_HR,       "KG_PER_HR"         }
         };
         auto   it  = EnumStrings.find(static_cast<uint16_t>(dlParam.Units));
         return it == EnumStrings.end() ? "--" : it->second;
      }
      static std::string GetUnitsString(const DataLinkParamInfo& dlParam)
      {
         return GetUnitsCstr(dlParam);
      }
      std::string GetUnitsString() const
      {
         return GetUnitsCstr(*this);
      }
      const char* GetUnitsCstr() const
      {
         return GetUnitsCstr(*this);
      }

      float GetScaling(void) const
      {
         return this->Scaling;
      }
      void SetScaling(float scaling)
      {
         paramInitStatus |= scalingMask;
         this->Scaling = scaling;
      }

      float GetOffset(void) const
      {
         return this->Offset;
      }
      void SetOffset(float offset)
      {
         paramInitStatus |= offsetMask;
         this->Offset = offset;
      }

      // Only set parameter name if loglevel is DEBUG
      void SetParameterName(const std::string& paramName)
      {
         if (logger::SingletonLogger::Instance()->getPriorityMask().enabled(logger::Priority::debug))
         {
            this->paramName = paramName;
         }
         else
         {
            AIS_LOG_INFO("Skipping name since log level is higher than DEBUG");
         }
      }
      const std::string& GetParamName() const
      {
         return paramName;
      }

      bool FullyInitialized() const
      {
         if (this->paramInitStatus == fullyInitialized)
         {
            return true;
         }
         else
         {
            AIS_LOG_ERROR("Metadata not fully initialized, paramInitStatus: 0x%02x", this->paramInitStatus);
            return false;
         }
      }

      bool KeyInitialized(void) const
      {
         if ((this->paramInitStatus & keyInitialized) == keyInitialized)
         {
            return true;
         }
         else
         {
            AIS_LOG_ERROR("Key not initialized, paramInitStatus: 0x%02x", this->paramInitStatus);
            return false;
         }
      }

      static PidKey_t GenerateCdlKey(uint32_t paramId, DlpParamIdentifierType_t paramIdentifierType)
      {
         return (paramIdentifierType << 24) | paramId;
      }

      bool GenerateCdlKey(PidKey_t &key, bool newParam) const
      {
         // Check if all of the fields required to form a key were initialized for the parameter
         if ((newParam && !FullyInitialized()) || !KeyInitialized())
         {
            return false;
         }
         else
         {
            key = (GetParamIdentifierType() << 24) | GetParamId();
            return true;
         }
      }

   protected:
      friend class boost::serialization::access;

      static constexpr uint8_t sidMask = 0x01;
      static constexpr uint8_t pidMask = 0x02;
      static constexpr uint8_t identifierMask = 0x04;
      static constexpr uint8_t parameterTypeMask = 0x10;
      static constexpr uint8_t scalingMask = 0x20;
      static constexpr uint8_t offsetMask = 0x40;
      static constexpr uint8_t fullyInitialized = sidMask | pidMask | identifierMask | parameterTypeMask | scalingMask | offsetMask;
      static constexpr uint8_t keyInitialized = pidMask | identifierMask;

      /* Add Fields Here */
      DlpParamIdentifierType_t paramIdentifierType;
      DlpDataLinkType_t DlType;
      uint32_t SourceId;
      uint64_t ParamId;
      cdl2_parameter_type_t ParameterType;
      VarLengthDataLinkParamFactory::VarLengthParamType VarLengthParamType;

      float Scaling;
      float Offset;
      DlpUnits_t Units;
      uint8_t paramInitStatus;

      std::string paramName;
};

BOOST_CLASS_VERSION(DataLinkParamInfo, DataLinkParamInfo::DATALINK_PARAM_VERSION);

#endif // DATALINKPARAMINFO_H

