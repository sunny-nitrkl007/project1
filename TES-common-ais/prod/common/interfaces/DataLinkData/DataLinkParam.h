////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: DataLinkParam
//
// File Name: DataLinkParam.h
//
//  Abstract: This class is inherited from class DataLinkParamInfo.
//
////////////////////////////////////////////////////////
#ifndef DATALINKPARAM_H
#define DATALINKPARAM_H

#include <vector>

#include <cdl2_struct.h>

#include "DataLinkParamInfo.h"

#include "VarLengthDataLinkParam_decl.h"
#include "VarLengthDataLinkParamFactory_decl.h"

class DataLinkParam : public DataLinkParamInfo
{
public:
/******************************************************************************
 Constructor
*******************************************************************************/
    DataLinkParam() :
        DataLinkParamInfo(),
        LastGoodValue(0),
        LastValue(0),
        LastValueDouble(.0f),
        LastValueDsi(DSI_CODE_CONDITIONS_NOT_MET()),
        PIDDataReceived(false),
        FaultDataCounter(0),
        StaleDataCounter(0),
        DlpDataVector(),
        varLengthDataLinkParam() // nullptr
    {
    }

/******************************************************************************
 Destructor
*******************************************************************************/
    ~DataLinkParam()
    {
    }

/******************************************************************************
 Assignment operator overload constructor - 
*******************************************************************************/
    DataLinkParam& operator= (const DataLinkParam& rhs)
    {
        DataLinkParamInfo::operator=(rhs);
        LastGoodValue = rhs.LastGoodValue;
        LastValue = rhs.LastValue;
        LastValueDouble = rhs.LastValueDouble;
        LastValueDsi = rhs.LastValueDsi;
        PIDDataReceived = rhs.PIDDataReceived;
        FaultDataCounter = rhs.FaultDataCounter;
        StaleDataCounter = rhs.StaleDataCounter;
        DlpDataVector = rhs.DlpDataVector;
        varLengthDataLinkParam.reset();
        return *this;
    }


    void UpdateParam(const DataLinkParam &dlp)
    {
        // Add new entry in vector with new data and dsi
        DataLinkParam::dlpData_t dlpData;
        dlpData.Value = dlp.GetLastValue<unsigned_32>();
        dlpData.Dsi = dlp.LastValueDsi;        
        DlpDataVector.push_back(dlpData);

        // Update statistics
        LastValueDsi = dlp.LastValueDsi;
        LastValue = dlp.LastValue;
        LastValueDouble = dlp.LastValueDouble;
        PIDDataReceived = true;
        // Work around for CSNS falsly providing DSI value for CDL2_I8_DSI
        if (!dlp.UsesDsi())
        {
            LastValueDsi = 0;
        }
        if (0 == LastValueDsi)
        { // For good data
            ResetFaultDataCount();
            ResetStaleDataCount();
            LastGoodValue = dlp.LastValue;
        }
        else
        { // For fault code
            IncreaseFaultDataCount();
        }
    }

    typedef struct 
    {
      unsigned_32 Value;
      unsigned_16 Dsi;

      template <class Archive>
      void serialize(Archive &ar, unsigned int version)
      {
        ar & Value;
        ar & Dsi;
      }
    }dlpData_t;

/******************************************************************************
 Searilize data to publish
*******************************************************************************/
    template <class Archive>
    void serialize(Archive &ar, unsigned int version)
    {
        // Old versions not supported
        if (version != DataLinkParamInfo::DATALINK_PARAM_VERSION) return;

        DataLinkParamInfo::serialize(ar, version);
        ar & LastGoodValue;
        ar & LastValue;
        ar & LastValueDouble;
        ar & LastValueDsi;
        ar & PIDDataReceived;
        ar & FaultDataCounter;
        ar & StaleDataCounter;
        ar & DlpDataVector;
    }

/******************************************************************************
 To save data in CSV format
*******************************************************************************/
    void toCsv(CsvOutStream& out) const
    {
        DataLinkParamInfo::toCsv(out);

        if (LastGoodValue.size() > 0) {
            std::string LastGoodValuestr(LastGoodValue.begin(),LastGoodValue.begin());
            out("LastGoodValue", LastGoodValuestr);
        }
        else {
            out("LastGoodValue", "");
        }
        if (LastValue.size() > 0) {
            std::string LastValuestr(LastValue.begin(), LastValue.begin());
            out("LastValue", LastValuestr);
        }
        else {
            out("LastValue", "");
        }
        out("LastValueDouble", LastValueDouble);
        out("LastValueDsi", LastValueDsi);
        out("PIDDataReceived", PIDDataReceived);
        out("FaultDataCounter", FaultDataCounter);
        out("StaleDataCounter", StaleDataCounter);
    }

/******************************************************************************
 Below function is to get the LastGood Engineer value
*******************************************************************************/
    double GetLastGoodValueEng(void) const
    {
      //Read data into double. Handle unsigned data to prevent large number handle as negative number.
      double lastGoodValueDouble;
      switch (this->ParameterType)
      {
      case CDL2_U8_DSI:
      case CDL2_U8_NO_DSI:
      case CDL2_U16_DSI:
      case CDL2_U16_NO_DSI:
      case CDL2_U32_DSI:
      case CDL2_U32_NO_DSI:
      {
         lastGoodValueDouble = static_cast<double>(GetLastGoodValue<unsigned_32>());
         break;
      }
      case CDL2_VAR_NO_DSI:
      {
         lastGoodValueDouble = 0.0;
         break;
      }
      default:
      {
         lastGoodValueDouble = static_cast<double>(GetLastGoodValue<int_32>());
         break;
      }
      }
      return static_cast<double>((lastGoodValueDouble * GetScaling()) + GetOffset());
   }

/******************************************************************************
 Below functions is to get the LastGoodValue
*******************************************************************************/
   template<class T> T GetLastGoodValue(void) const
   {
      //get the data based on its param type and cast to the return type to keep the sign.
      std::vector<unsigned_8> lastGoodValue_adj = this->LastGoodValue;
      T returnValue;
      switch ( this->ParameterType )
      {
      case CDL2_I8_DSI:
      case CDL2_I8_NO_DSI:
      {
         lastGoodValue_adj.resize( 1 );
         returnValue = static_cast<T>( *reinterpret_cast<int_8*>( &lastGoodValue_adj[0] ) );
         break;
      }
      case CDL2_I16_DSI:
      case CDL2_I16_NO_DSI:
      {
         lastGoodValue_adj.resize( 2 );
         returnValue = static_cast<T>( *reinterpret_cast<int_16*>( &lastGoodValue_adj[0] ) );
         break;
      }
      case CDL2_I32_DSI:
      case CDL2_I32_NO_DSI:
      {
         lastGoodValue_adj.resize( 4 );
         returnValue = static_cast<T>( *reinterpret_cast<int_32*>( &lastGoodValue_adj[0] ) );
         break;
      }
      default:
      {
         lastGoodValue_adj.resize( sizeof(T), 0 );
         returnValue = *reinterpret_cast<T*>( &lastGoodValue_adj[0] );
         break;
      }
      }
      return returnValue;
   }

/******************************************************************************
 Below function is to get the LastValue
*******************************************************************************/
   double GetLastValueEng(void) const
   {
      //Read data into double. Handle unsigned data to prevent large number handle as negative number.
      double lastValueDouble;
      switch (this->ParameterType)
      {
      case CDL2_U8_DSI:
      case CDL2_U8_NO_DSI:
      case CDL2_U16_DSI:
      case CDL2_U16_NO_DSI:
      case CDL2_U32_DSI:
      case CDL2_U32_NO_DSI:
      {
         lastValueDouble = GetLastValue<unsigned_32>();
         break;
      }
      case CDL2_VAR_NO_DSI:
      {
         lastValueDouble = 0.0;
         break;
      }
      default:
      {
         lastValueDouble = GetLastValue<int_32>();
         break;
      }
      }
      return static_cast<double>((lastValueDouble * GetScaling()) + GetOffset());
   }
/******************************************************************************
 Below function is to get the LastValue
*******************************************************************************/
   template<class T> T GetLastValue(void) const
   {
      //get the data based on its param type and cast to the return type to keep the sign.
      std::vector<unsigned_8> lastValue_adj = this->LastValue;
      T returnValue;
      switch (this->ParameterType)
      {
      case CDL2_I8_DSI:
      case CDL2_I8_NO_DSI:
      {
         lastValue_adj.resize(1);
         returnValue= static_cast<T>(*reinterpret_cast<int_8*>(&lastValue_adj[0]));
         break;
      }
      case CDL2_I16_DSI:
      case CDL2_I16_NO_DSI:
      {
         lastValue_adj.resize(2);
         returnValue = static_cast<T>(*reinterpret_cast<int_16*>(&lastValue_adj[0]));
         break;
      }
      case CDL2_I32_DSI:
      case CDL2_I32_NO_DSI:
      {
         lastValue_adj.resize(4);
         returnValue = static_cast<T>(*reinterpret_cast<int_32*>(&lastValue_adj[0]));
         break;
      }
      default:
      {
         lastValue_adj.resize(sizeof(T), 0);
         returnValue = *reinterpret_cast<T*>(&lastValue_adj[0]);
         break;
      }
      }
      return returnValue;
   }

/******************************************************************************
 Get the Raw data vector for debugging
*******************************************************************************/
   const std::vector<unsigned_8>& GetLastValueVector() const
   {
       return this->LastValue;
   }

/******************************************************************************
 Get the Raw data vector for debugging
*******************************************************************************/
   const std::vector<unsigned_8>& GetLastGoodValueVector() const
   {
       return this->LastGoodValue;
   }

/******************************************************************************
 Below function is to get the LastValueDouble
*******************************************************************************/
   double GetLastValueDouble(void) const
   {
       return LastValueDouble;
   }

/******************************************************************************
 Below function is to set the LastValue for fixed length PIDs only
*******************************************************************************/
   void SetLastValue(const std::vector<unsigned_8>& lastValue, uint16_t paramDsi, bool updateLastGoodValue = false)
   {
       // if the invoker has no data for us then he only cares about setting the DSI. When DSI is invalid
       if (!lastValue.empty())
       {
           this->LastValue = lastValue;
           if (updateLastGoodValue && (paramDsi == DSI_CODE_OK()))
           {
               this->LastGoodValue = LastValue;
           }
       }
       this->LastValueDsi = paramDsi;
       PIDDataReceived = true;
   }

/******************************************************************************
 Below function is to set the LastValue for fixed length PIDs only
 lastValue is the raw unpacked PID value
*******************************************************************************/
   void SetLastValue(uint32_t lastValue, uint16_t paramDsi, bool updateLastGoodValue = false)
   {
       this->LastValue.assign(reinterpret_cast<unsigned_8*>(&lastValue), reinterpret_cast<unsigned_8*>(&lastValue) + sizeof(lastValue));

       if (GetVarLengthParamType() == VarLengthDataLinkParamFactory::SPL_PID_REV_DATA_BYTE_ORDER)
       {
           AIS_LOG_INFO("Special Data Byte Order");
           std::reverse(LastValue.begin(), LastValue.end());
       }
       this->LastValueDsi = paramDsi;
       if (updateLastGoodValue && (paramDsi == DSI_CODE_OK()))
       {
           this->LastGoodValue = LastValue;
       }
       PIDDataReceived = true;
   }

/******************************************************************************
 Below function is to set the LastValueEng for fixed length PIDs only
 Returns false if any meta data (Scaling, Offset, ParameterType, etc) is not set
*******************************************************************************/
   bool SetLastValueEng(double lastValueEng, uint16_t paramDsi)
   {
        // Return false if necessary meta data is not set
        if (!FullyInitialized())
        {
            return false;
        }

        this->LastValueDsi = paramDsi;

        switch (this->ParameterType)
        {
        case CDL2_VAR_NO_DSI:
        {
            return false;
        }
        default:
        {
            // Scale, round, and convert to unsigned
            double roundingOffset = lastValueEng > 0 ? 0.5 : -0.5;
            auto value = static_cast<uint32_t>(static_cast<int32_t>(lastValueEng / GetScaling() - GetOffset() + roundingOffset));
            LastValue.assign(reinterpret_cast<unsigned_8 *>(&value), reinterpret_cast<unsigned_8 *>(&value) + sizeof(decltype(value)));
            break;
        }
        }
        PIDDataReceived = true;
        return true;
   }

/******************************************************************************
 Set the LastValue for double precision parameters only
 *******************************************************************************/
   void SetLastValueDouble(double lastValueDouble, uint16_t paramDsi)
   {
       LastValueDouble = lastValueDouble;
       LastValueDsi = paramDsi;
   }

   /******************************************************************************
 Set the LastValue for variable length PIDs only
 Preconditions: ParamId, SourceId have been set.
*******************************************************************************/
   void SetVarLengthParamValue(const std::vector<uint8_t> &paramValue, uint16_t paramDsi)
   {
       // Populate last value with the data regardless of the DSI.  If UpdateParam is called
       // then LastValue might be copied into the LastGoodValue so it needs to have valid data
       LastValueDsi = paramDsi;
       if (paramValue.size() > 0)
       {
           LastValue = paramValue;

           if (0 == LastValueDsi)
           {
               LastGoodValue = paramValue;
               AIS_LOG_DEBUG("LastGoodValue.size %d", LastGoodValue.size());
           }
           PIDDataReceived = true;
       }
       else
       {
           LastValue.clear();
       }
   }

   /******************************************************************************
 Set the LastValue for variable length PIDs only
 Preconditions: ParamId, SourceId have been set.
*******************************************************************************/
   void SetVarLengthParamValue(const uint8_t *paramValue, uint8_t paramLength, uint16_t paramDsi)
   {
       // Populate last value with the data regardless of the DSI.  If UpdateParam is called
       // then LastValue might be copied into the LastGoodValue so it needs to have valid data
       LastValueDsi = paramDsi;
       if ((nullptr != paramValue) && (paramLength > 0))
       {
           LastValue.assign(paramValue, paramValue + paramLength);

           if (0 == LastValueDsi)
           {
               LastGoodValue.assign(paramValue, paramValue + paramLength);
               AIS_LOG_DEBUG("LastGoodValue.size %d", LastGoodValue.size());
           }
           PIDDataReceived = true;
       }
       else
       {
           LastValue.clear();
       }
   }

   //GetVarLengthParam precondition: ParamId, SourceId have been set.
   const boost::shared_ptr<VarLengthDataLinkParam> GetVarLengthParam()
   {
       if (!varLengthDataLinkParam) {
           varLengthDataLinkParam = VarLengthDataLinkParamFactory::GetNewParam(*this);
       }

       return varLengthDataLinkParam;
   }

   uint8_t GetVarParamBlockLength() const
   {
       return LastGoodValue.size();
   }

   void ClearVarParamBlock()
   {
       LastGoodValue.clear();
   }

   const uint8_t* GetVarParamBlock() const
   {
      return LastGoodValue.data();
   }

   void SetVarLengthParamType(VarLengthDataLinkParamFactory::VarLengthParamType paramType)
   {
      if (paramType != VarLengthParamType) {
         // Reset the parser (VarLengthParam) if the type changes.
         varLengthDataLinkParam.reset();
         VarLengthParamType = paramType;
      }
   }

   VarLengthDataLinkParamFactory::VarLengthParamType GetVarLengthParamType() const
   {
      return VarLengthParamType;
   }

/******************************************************************************
 Below functions are to set and get the LastValueDsi (this DSI is shared between
 fixed and variable length parameters. GetVarLengthParamDsi is not really needed
 but is left here for backwards compatibility.
*******************************************************************************/
    uint16_t GetLastValueDsi(void) const
    {
        return this->LastValueDsi;
    }

    uint16_t GetVarLengthParamDsi(void) const
    {
       return this->LastValueDsi;
    }

    static constexpr uint_least16_t MakeDsiCode(cdl2_data_status_indentifiers_e cdl2_dsi) {
        return MakeDsiCode((uint_least8_t)cdl2_dsi);
    }

    static constexpr uint_least16_t MakeDsiCode(uint_least8_t dsi) {
        // This is the scl_util definition of dsi_code
        // SCL_UTIL_DSI_ERROR_FLAG | (SCL_UTIL_DSI_CODE_MASK & dsi)
        return (uint_least16_t)(0xFF00 | (0x001F & dsi));
    }

    static constexpr uint_least8_t ExtractDsi(uint_least16_t dsi_code) {
        return (uint_least8_t)(dsi_code & 0x001F);
    }

    static constexpr uint_least16_t DSI_CODE_OK() { return 0; }
    static constexpr uint_least16_t DSI_CODE_ABNORMAL_UPDATE() { return MakeDsiCode(CDL2_DSI_ABNORMAL_UPDATE); }
    static constexpr uint_least16_t DSI_CODE_PARAM_NOT_AVAIL() { return MakeDsiCode(CDL2_DSI_PARAM_NOT_AVAIL); }
    static constexpr uint_least16_t DSI_CODE_NO_RESPONSE() { return MakeDsiCode(CDL2_DSI_NO_RESPONSE); }
    static constexpr uint_least16_t DSI_CODE_CONDITIONS_NOT_MET() { return MakeDsiCode(CDL2_DSI_CONDITIONS_NOT_MET); }

/******************************************************************************
 Below functions are to set and get the IsPIDDataReceived
*******************************************************************************/
    bool IsPIDDataReceived(void) const
    {
        return this->PIDDataReceived;
    }
    void SetPIDDataReceived(bool dataReceived)
    {
        this->PIDDataReceived = dataReceived;
    }

/******************************************************************************
 Below functions are to set and get the FaultDataCounter
*******************************************************************************/
    uint8_t GetFaultDataCount(void) const
    {
        return this->FaultDataCounter;
    }
    void ResetFaultDataCount()
    {
        this->FaultDataCounter = 0;
    }
    void IncreaseFaultDataCount(void)
    {
        if (this->FaultDataCounter < 256)
        {
            (this->FaultDataCounter)++;
        }
    }

/******************************************************************************
 Below functions are to set and get the StaleDataCounter
*******************************************************************************/
    uint8_t GetStaleDataCount(void) const
    {
        return this->StaleDataCounter;
    }
    void ResetStaleDataCount()
    {
        this->StaleDataCounter = 0;
    }
    void IncreaseStaleDataCount(void)
    {
        if (this->StaleDataCounter < 256)
        {
            (this->StaleDataCounter)++;
        }
    }

/******************************************************************************
 Below functions are to set and get the LastValueDsi
*******************************************************************************/
    const std::vector<dlpData_t>& GetdlpDataVector(void) const
    {
        return this->DlpDataVector;
    }
    void UpdateDlpDataVector(const dlpData_t& dlpData)
    {
        this->DlpDataVector.push_back(dlpData);
    }
    void ClearDlpDataVector()
    {
       this->DlpDataVector.clear();
    }
    uint8_t dlpDataVectorSize() const
    {
        return DlpDataVector.size();
    }

private:
   friend class VarLengthDataLinkParam;

   std::vector<unsigned_8> LastGoodValue;
   std::vector<unsigned_8> LastValue;
   double LastValueDouble; ///< Used for CDA double precision parameters (GPS, etc)
   unsigned_16 LastValueDsi;
   bool PIDDataReceived; // to check if the PID data received in complete execution cycle
   unsigned_8 FaultDataCounter;
   unsigned_8 StaleDataCounter;
   std::vector<dlpData_t> DlpDataVector;

   // Need to keep a copy of this here because application level users don't use shared pointers properly
   //  They get the underlying pointer and ditch the shared pointer... if they are the last ones to
   //  delete the shared pointer, then the underlying object gets deleted.  Then, when they try to use
   //  the underlying pointer, they fail.  So, we will keep it alive here so they can continue to be dumb.
   boost::shared_ptr<VarLengthDataLinkParam> varLengthDataLinkParam;
};


BOOST_CLASS_VERSION(DataLinkParam, DataLinkParamInfo::DATALINK_PARAM_VERSION);

#endif // DATALINKPARAM_H
