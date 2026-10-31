#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
#include <functional>

#include <boost/functional/hash.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/range/adaptor/map.hpp>
#include <boost/range/any_range.hpp>

#include <ais/serialization/Datum.h> // For Boost serialization
#include <ais/log/AisLogger.h>
#include <ais/task/Task.h>

#include <iterators/unordered_map_list_iterator.hpp>

#include "DataLinkParam.h"
#include "VarLengthDataLinkParam.h"
#include "VarLengthDataLinkParamFactory.h"
#include "VarLengthDataLinkParamPool.h"

#define MPH_T0_KMPH(val) (float)(val * 1.60934)
#define GROUND_SPEED_PID                   0x18
#define GEAR_PID                           0xF002
#define ACTUAL_GEAR_PID   		           0xF5D9
#define GROUND_SPEED_AND_DIRECTION_PID     0xF4FD

#define MSB_MASK                           0x8000
#define BYTE_2_MASK                        0xFF00
#define BYTE_1_MASK                        0x00FF
#define CDL_MACH_GEAR_IN_REV               0x20
#define CDL_MACH_ACTUAL_GEAR_IN_REV        0x10
#define CDL_STATUS_OK                      0
#define GEAR_FLAGS_DATA_FAULT              0x80

#define PARAM_NOT_FOUND -1

#ifndef _DataLinkData_h_
#define _DataLinkData_h_

class DataLinkDataStorage
{
public:
    typedef enum ParamInfoStatus
    {
        PARAM_INFO_STATUS_DATA_AVAILABLE,
        PARAM_INFO_STATUS_DATA_NOT_AVAILABLE
    } ParamInfoStatus_t;

    typedef enum
    {
        DL_DATA_DIAG_FMI_FMI9 = 9, // CDL2_FMI_ABNORMAL_UPDATE
        DL_DATA_DIAG_FMI_FMI14 = 14 // Special Instruction
    } DldFmiCode_t;

    typedef enum
    {
        DL_DATA_DIAG_INACTIVE = 0,
        DL_DATA_DIAG_ACTIVE,
    } DldFmiStatus_t;

    typedef struct ParamInfo
    {
        uint32_t sid; //input
        uint32_t paramId; //input
        DataLinkParam dlParam; //output
        ParamInfoStatus_t status; //output
    } ParamInfo_t;

    typedef struct
    {
        float Val;
        ParamInfoStatus_t Stat;
    } CalcParamData_t;

    typedef struct
    {
        uint16_t Val;
        ParamInfoStatus_t Stat;
    } GearData_t;

    /******************************************************************************
     CLASS NAME: dlpDiag
     DESCRIPTION: Diagnostic informations for data link.
     *******************************************************************************/
    class dlpDiag
    {
    public:
        uint16_t Cid;
        uint32_t Mid;

        /******************************************************************************
         FUNCTION NAME: dlpDiag default constructor & destructor
         DESCRIPTION: used by map creation & delete
         PARAMETER DESCRIPTION:  No parameter.
         *******************************************************************************/
        dlpDiag() : dlpDiag(0, 0) {}

        /******************************************************************************
         FUNCTION NAME: dlpDiag constructor
         DESCRIPTION: make dlpDiag from cid and mid, set both fmi 9 and fmi 14 to inactive
         PARAMETER DESCRIPTION:  No parameter.
         RETURN VALUE:  void
         *******************************************************************************/
        dlpDiag(uint16_t cid, uint32_t mid) :
            Cid(cid),
            Mid(mid),
            Fmi9Status(),
            Fmi14Status(),
            LastFmi9Status(DL_DATA_DIAG_INACTIVE),
            LastFmi14Status(DL_DATA_DIAG_INACTIVE) {}

        /******************************************************************************
         FUNCTION NAME: UpdateLastFmi9Status
         DESCRIPTION: update FMI 9 status and save previous Fmi into vector
         PARAMETER DESCRIPTION:  fmiStatus.
         RETURN VALUE:  void
         *******************************************************************************/
        void UpdateLastFmi9Status( DldFmiStatus_t fmiStatus )
        {
            LastFmi9Status = fmiStatus;
            Fmi9Status.push_back( fmiStatus );
        }

        /******************************************************************************
         FUNCTION NAME: UpdateLastFmi14Status
         DESCRIPTION: update FMI 14 status and save previous Fmi into vector
         PARAMETER DESCRIPTION:  fmiStatus.
         RETURN VALUE:  void
         *******************************************************************************/
        void UpdateLastFmi14Status( DldFmiStatus_t fmiStatus )
        {
            Fmi14Status.push_back( LastFmi14Status );
            LastFmi14Status = fmiStatus;
        }

        /******************************************************************************
         FUNCTION NAME: GetLastFmi9Status
         DESCRIPTION: return last FMI 9 status
         PARAMETER DESCRIPTION:  No parameter.
         RETURN VALUE:  DldFmiStatus_t
         *******************************************************************************/
        DldFmiStatus_t GetLastFmi9Status()
        {
            return LastFmi9Status;
        }

        /******************************************************************************
         FUNCTION NAME: GetLastFmi14Status
         DESCRIPTION: return last FMI 14 status
         PARAMETER DESCRIPTION:  No parameter.
         RETURN VALUE:  DldFmiStatus_t
         *******************************************************************************/
        DldFmiStatus_t GetLastFmi14Status()
        {
            return LastFmi14Status;
        }

        /******************************************************************************
         FUNCTION NAME: GetFmi9Status
         DESCRIPTION: return history vector for FMI 9
         PARAMETER DESCRIPTION:  No parameter.
         RETURN VALUE:  std::vector<DldFmiStatus_t>
         *******************************************************************************/
        std::vector<DldFmiStatus_t> GetFmi9Status()
        {
            return Fmi9Status;
        }

        /******************************************************************************
         FUNCTION NAME: GetFmi14Status
         DESCRIPTION: return history vector for FMI 14
         PARAMETER DESCRIPTION:  No parameter.
         RETURN VALUE:  std::vector<DldFmiStatus_t>
         *******************************************************************************/
        std::vector<DldFmiStatus_t> GetFmi14Status()
        {
            return Fmi14Status;
        }

        /******************************************************************************
         FUNCTION NAME: ClearFmiStatus
         DESCRIPTION:
         PARAMETER DESCRIPTION:  No parameter.
         RETURN VALUE:  void
         *******************************************************************************/
        void ClearFmiStatus()
        {
            Fmi9Status.clear();
            Fmi14Status.clear();
        }

        /******************************************************************************
         FUNCTION NAME: serialize
         DESCRIPTION:
         RETURN VALUE:  void
         *******************************************************************************/
        template<class Archive>
        void serialize(Archive &ar, unsigned int version )
        {
            ar & Cid;
            ar & Mid;
            ar & Fmi9Status;
            ar & Fmi14Status;
            ar & LastFmi9Status;
            ar & LastFmi14Status;
        }

    private:
        std::vector<DldFmiStatus_t> Fmi9Status;
        std::vector<DldFmiStatus_t> Fmi14Status;
        DldFmiStatus_t LastFmi9Status;
        DldFmiStatus_t LastFmi14Status;
    };

    /******************************************************************************
     FUNCTION NAME: DataLinkDataStorage constructor
     DESCRIPTION:
     PARAMETER DESCRIPTION:  No parameter.
     *******************************************************************************/
    DataLinkDataStorage() :
        DlDataMap(),
        DlpDiagInfo(),
        TaskSourceId(0) {}

    using DlDiagsKey_t = std::pair<uint16_t, uint32_t>;  // <cid, mid>
    using DlDiags_t = std::map<DlDiagsKey_t, dlpDiag>;

    using DlParmPtr_t = DataLinkParam*;
    using ConstDlParmPtr_t = const DataLinkParam*;

    // 2D Lookup of ID + ParamType -> DatalinkType + SID
    using DlKey_t = uint32_t;
    using DlParamsInner_t = std::list<DataLinkParam>;
    using DlParams_t = std::unordered_map<DlKey_t, DlParamsInner_t>;

   /******************************************************************************
     FUNCTION NAME: begin, end
     DESCRIPTION:   Used to iterator through all parameters (replaces GetDataLinkMap)
     USAGE: for (const DataLinkParam& dlParam : dataLinkData)
            {
                double value = dlParam.GetLastGoodValueEng();
                ...
     *******************************************************************************/
    typedef unordered_map_list_iterator<DlKey_t, DataLinkParam> iterator;

    iterator begin(){ return iterator::begin(DlDataMap); }
    iterator end(){ return iterator::end(DlDataMap); }

    using TaskSourceId_t = size_t;

    /******************************************************************************
     FUNCTION NAME: save
     DESCRIPTION:   serializes DataLinkData
     RETURN VALUE:  void
     *******************************************************************************/
    template<class Archive>
    void save(Archive &ar, unsigned int version )
    {
        // Old versions not supported
        if (version != DataLinkParamInfo::DATALINK_PARAM_VERSION) return;

        /* Archive Fields Here */
        ar << TaskSourceId;
        size_t mapSize = DlDataMap.size();
        ar << mapSize;
        for (auto it : DlDataMap)
        {
            ar << it.second;
        }
        ar << DlpDiagInfo;
    }

    /******************************************************************************
     FUNCTION NAME: load
     DESCRIPTION:   deserializes DataLinkData
     RETURN VALUE:  void
     *******************************************************************************/
    template<class Archive>
    void load(Archive &ar, unsigned int version )
    {
        // Old versions not supported
        if (version != DataLinkParamInfo::DATALINK_PARAM_VERSION) return;

        /* Archive Fields Here */
        ar >> TaskSourceId;
        size_t mapSize;
        ar >> mapSize;
        DlDataMap.clear();
        for (size_t i = 0; i < mapSize; ++i)
        {
            DlParamsInner_t params;
            ar >> params;
            if (!params.empty())
            {
                DlKey_t key;
                if (params.front().GenerateCdlKey(key, false))
                {
                    DlDataMap.emplace(key, std::move(params));
                }
            }
        }
        DlpDiagInfo.clear();
        ar >> DlpDiagInfo;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    /******************************************************************************
     FUNCTION NAME: SetTaskSourceId
     DESCRIPTION:  Generates and stores TaskSourceId for the provided task.  
      Assumes task name is unique
     PARAMETER DESCRIPTION:  task::Task&
     RETURN VALUE:  TaskSourceId (can be stored for future use)
     *******************************************************************************/
    TaskSourceId_t SetTaskSourceId(const task::Task& task)
    {
        TaskSourceId = std::hash<std::string>{}(task.getTaskName());
        return TaskSourceId;
    }

    /******************************************************************************
     FUNCTION NAME: GetTaskSourceId
     DESCRIPTION:  Accessor for TaskSourceId
     PARAMETER DESCRIPTION:  None
     RETURN VALUE:  TaskSourceId 
     *******************************************************************************/
    TaskSourceId_t GetTaskSourceId() const
    {
        return TaskSourceId;
    }

    /******************************************************************************
     FUNCTION NAME: GetTaskSourceId
     DESCRIPTION:  Generates TaskSourceId for the provided task.
      Assumes task name is unique
     PARAMETER DESCRIPTION:  task::Task&
     RETURN VALUE:  TaskSourceId
     *******************************************************************************/
    static TaskSourceId_t GetTaskSourceId(const task::Task& task)
    {
        return std::hash<std::string>{}(task.getTaskName());
    }

    /******************************************************************************
     FUNCTION NAME: CalcMachineSpeed
     DESCRIPTION:
     PARAMETER DESCRIPTION:  No parameter.
     RETURN VALUE:  void
     *******************************************************************************/
    static CalcParamData_t CalcMachineSpeed( float GrondSpeed, unsigned_16 Gear, int ParamId )
    {
        CalcParamData_t machineSpeed;
        bool isReverseGear = FALSE;

        machineSpeed.Val = -1; // TODO: What should be the dafult?
        machineSpeed.Stat = PARAM_INFO_STATUS_DATA_NOT_AVAILABLE;

        // if actual gear
        if( ACTUAL_GEAR_PID == ParamId )
        {
            uint16_t byte2 = Gear & BYTE_2_MASK;
            uint16_t byte1 = Gear & BYTE_1_MASK;
            Gear = ( byte2 >> 8 ) | ( byte1 << 8 );

            uint8_t actualGearFlags = (uint8_t) ( Gear );
            AIS_LOG_INFO( "actualGearFlags %x ", actualGearFlags );

            if( ( actualGearFlags & CDL_MACH_ACTUAL_GEAR_IN_REV ) == CDL_MACH_ACTUAL_GEAR_IN_REV )
            {
                isReverseGear = TRUE;
            }
        }
        // for gear
        else if( GEAR_PID == ParamId )
        {
            uint8_t gearFlags = (uint8_t) ( Gear );
            AIS_LOG_INFO( "gearFlags %x ", gearFlags );

            if( ( gearFlags & CDL_MACH_GEAR_IN_REV ) == CDL_MACH_GEAR_IN_REV )
            {
                isReverseGear = TRUE;
            }
        }
        else
        {
            return machineSpeed;
        }

        machineSpeed.Val = MPH_T0_KMPH( GrondSpeed );
        machineSpeed.Stat = PARAM_INFO_STATUS_DATA_AVAILABLE;

        if( isReverseGear )
        {
            machineSpeed.Val = ( -machineSpeed.Val );
        }
        AIS_LOG_DEBUG( "Input GrondSpeed %f, coverted to MachineSpeed %f", GrondSpeed, machineSpeed.Val );

        return machineSpeed;
    }

    /******************************************************************************
     FUNCTION NAME: AddDataLinkParam
     DESCRIPTION: add new data link parameter into the dlDataMap.  The Parameter must
      have a unique ParamId and ParameterIdentifierType.  If the Parameter has multiple
      sources (Source Address/SID and/or DataLinkType), a separate DataLinkData object
      must be used for each instance of the Parameter.
     PARAMETER DESCRIPTION:  dlp: data link parameter
     RETURN VALUE: bool - true if add was successful and false otherwise.
     *******************************************************************************/
    /* These new methods are for new  DlDataMap */
    bool AddDataLinkParam( DataLinkParam &dlp )
    {
        DataLinkParam* pParam{nullptr};
        return AddDataLinkParam(dlp, pParam);
    }

    // Overload that also returns pointer to the parameter added
    bool AddDataLinkParam(DataLinkParam &dlp, DataLinkParam*& pParam)
    {
        try
        {
            DataLinkParamInfo::PidKey_t dlKey;
            if (dlp.GenerateCdlKey(dlKey, true))
            {
                AIS_LOG_DEBUG("Adding %s 0x%X with keyPairPID 0x%X", dlp.GetParamIdTypeCstr(), dlp.GetParamId(), dlKey);
                DlDataMap[dlKey].push_back(dlp); // adding new entry to the DataMap
                pParam = &DlDataMap.at(dlKey).back();
                return true;
            }
            else
            {
                AIS_LOG_ERROR("Error adding %s 0x%X : not enough fields initialized to form a key", dlp.GetParamIdTypeCstr(), dlp.GetParamId());
            }
        }
        catch (std::exception &e)
        {
            AIS_LOG_ERROR("Error adding %s 0x%X : %s", dlp.GetParamIdTypeCstr(), dlp.GetParamId(), e.what());
        }
        return false;
    }

    /******************************************************************************
     FUNCTION NAME: UpdateDataLinkParam
     DESCRIPTION: update data link parameter into the map.
     PARAMETER DESCRIPTION:  dlp: data link parameter .
     RETURN VALUE:  bool - true if update was successful and false otherwise.
     *******************************************************************************/
    bool UpdateDataLinkParam( DataLinkParam &dlp )
    {
        // search key in dlDataMap. Then update it with new values
        DataLinkParamInfo::PidKey_t dlKey;
        if (dlp.GenerateCdlKey(dlKey, false))
        {
            auto it = DlDataMap.find(dlKey);
            if (it != DlDataMap.end())
            {
                auto& params = it->second;
                auto itInner = std::find_if(params.begin(), params.end(),
                    [&dlp](const DataLinkParam& dlpFound) { return (dlp.GetSid() == dlpFound.GetSid()) && (dlp.GetDataLinkType() == dlpFound.GetDataLinkType()); } );
                if (itInner != params.end())
                {
                    itInner->UpdateParam(dlp);
                    AIS_LOG_DEBUG("PID %x Update success", dlp.GetParamId());
                    return true;
                }
            }
            AIS_LOG_ERROR("PID %x Update failed for SID 0x%02X (%s)", dlp.GetParamId(), dlp.GetSid(), dlp.GetDataLinkTypeCstr());
            return false;
        }
        AIS_LOG_ERROR("Error updating data link param: not enough fields initialized to form a key");
        return false;
    }

    /******************************************************************************
     FUNCTION NAME: HandleDataLinkDataMap
     DESCRIPTION: process the data link data map after publish.
     PARAMETER DESCRIPTION:  No parameter.
     RETURN VALUE:  void
     *******************************************************************************/
    void HandleDataLinkDataMap()
    {
        for(auto& dlParamPair : DlDataMap)
        {
            for (auto& dlParam : dlParamPair.second)
            {
                if( dlParam.IsPIDDataReceived() ) // If we have PID data, reset the stale counter
                {
                    dlParam.ResetStaleDataCount();
                }
                else
                {
                    dlParam.IncreaseStaleDataCount(); // else increse the stale counter
                    dlParam.ResetFaultDataCount(); // and reset the fault data counter
                }

                //ClearDataLinkDataMap - vector,lastValue, lastvalueDsi
                dlParam.ClearDlpDataVector();
                dlParam.SetPIDDataReceived( false );
            }
        }
    }

    /******************************************************************************
     FUNCTION NAME: PrintDataLinkParamMap
     DESCRIPTION: iterate all parameter in the map and print the data.
     PARAMETER DESCRIPTION:  No parameter.
     RETURN VALUE:  void
     *******************************************************************************/
    void PrintDataLinkParamMap() const
    {
        if (AIS_LOG_DEBUG_ENABLED)
        {
            AIS_LOG_DEBUG( "Printing complete DataLinkData data map" );
            for (const auto& dlParamPair : DlDataMap)
            {
                for (const auto& dlParam : dlParamPair.second)
                {
                    if (dlParam.GetParameterType() != CDL2_VAR_NO_DSI)
                    {
                        AIS_LOG_DEBUG( "%s %s = 0x%X, sid 0x%X, type %s, stale %u, fault %u, LastGoodValue %u (0x%X), LastValue 0x%X, LastGoodValueEng %f, dsi %x",
                            dlParam.GetParamIdTypeCstr(), dlParam.GetParamName().c_str(), dlParam.GetParamId(), dlParam.GetSid(), dlParam.GetParameterTypeCstr(),
                            dlParam.GetStaleDataCount(), dlParam.GetFaultDataCount(), dlParam.GetLastGoodValue<unsigned_32>(), dlParam.GetLastGoodValue<unsigned_32>(),
                            dlParam.GetLastValue<unsigned_32>(), dlParam.GetLastGoodValueEng(), dlParam.GetLastValueDsi() );
                    }
                    else
                    {
                        // Print Variable length PIDs as a string of bytes
                        // NOTE: stringstreams are not copyable so stored as a reference as a workaround
                        struct VarLengthPrinter
                        {
                            std::stringstream& ss;
                            const std::vector<unsigned_8>& value;
                            VarLengthPrinter(std::stringstream& ss, const std::vector<unsigned_8>& value) :
                                ss(ss),
                                value(value)
                            {}
                        };
                        std::vector<VarLengthPrinter> varLengthPrinters;
                        std::stringstream ssLastGoodValue;
                        varLengthPrinters.emplace_back(ssLastGoodValue, dlParam.GetLastGoodValueVector());
                        std::stringstream ssLastValue;
                        varLengthPrinters.emplace_back(ssLastValue, dlParam.GetLastValueVector());
                        for (auto& printer : varLengthPrinters)
                        {
                            if (printer.value.size() == 0)
                            {
                                printer.ss << "N/A";
                            }
                            else
                            {
                                printer.ss << "0x";
                                for (auto dataByte : printer.value)
                                {
                                    uint32_t paddedByte = dataByte;
                                    printer.ss << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << paddedByte;
                                }
                            }
                        }
                        AIS_LOG_DEBUG( "%s %s = 0x%X, sid 0x%X, type %s, stale %u, fault %u, LastGoodValue %s, LastValue %s, dsi %x",
                            dlParam.GetParamIdTypeCstr(), dlParam.GetParamName().c_str(), dlParam.GetParamId(), dlParam.GetSid(), dlParam.GetParameterTypeCstr(),
                            dlParam.GetStaleDataCount(), dlParam.GetFaultDataCount(), varLengthPrinters[0].ss.str().c_str(),
                            varLengthPrinters[1].ss.str().c_str(), dlParam.GetLastValueDsi() );
                    }
                }
            }

            AIS_LOG_DEBUG( "Printing vectors in DLD map" );
            for (const auto& dlParamPair : DlDataMap)
            {
                for (const auto& dlParam : dlParamPair.second)
                {
                    std::vector<DataLinkParam::dlpData_t> dlpDataVector = dlParam.GetdlpDataVector();
                    for( std::vector<DataLinkParam::dlpData_t>::iterator itr = dlpDataVector.begin(); itr != dlpDataVector.end(); itr++ )
                    {
                        AIS_LOG_DEBUG( "%s 0x%X, value %u (0x%X), dsi %u ", dlParam.GetParamIdTypeCstr(), dlParam.GetParamId(), itr->Value, itr->Value, itr->Dsi );
                    }
                }
            }
        }
    }

    /******************************************************************************
     FUNCTION NAME: GetParams
     DESCRIPTION:   Used to iterator through all parameters (replaces GetDataLinkMap)
     USAGE: for (const DataLinkParam& dlParam : dataLinkData.GetParams())
            {
                double value = dlParam.GetLastGoodValueEng();
                ...
     RETURN VALUE:  See above
     *******************************************************************************/
    DataLinkDataStorage& GetParams()
    { 
        return *this;
    }

    /******************************************************************************
     FUNCTION NAME: GetDataLinkDataMap
     DESCRIPTION: return object DlDataMap.
     PARAMETER DESCRIPTION:  No parameter.
     RETURN VALUE:  std::map<std::string, DataLinkParam>
     *******************************************************************************/
    const DlParams_t& GetDataLinkDataMap() const
    {
        return DlDataMap;
    }

    DlParams_t& GetDataLinkDataMap()
    {
        return DlDataMap;
    }

    /******************************************************************************
     FUNCTION NAME: GetDataLinkDataMapPtr
     DESCRIPTION: return the pointer for the DlDataMap.
     PARAMETER DESCRIPTION:  No parameter.
     RETURN VALUE:  std::map<std::string, DataLinkParam> *
     *******************************************************************************/
    const DlParams_t *GetDataLinkDataMapPtr() const
    {
        return &DlDataMap;
    }

    DlParams_t *GetDataLinkDataMapPtr( void )
    {
        return &DlDataMap;
    }

    /******************************************************************************
     FUNCTION NAME: GetParam
     DESCRIPTION: Get parameter value by paramID and ParameterIdentifierType.
                  May only be used if PID comes from a single source (DataLinkType and Source Address)
     USAGE: DlParmPtr_t dlParam;
            if (GetParam(dlParam, BMI_CDL_PID_ENGINE_SPEED, DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_PID)) {
                engineSpeed = dlParam->GetLastGoodValueEng();
            }

     PARAMETER DESCRIPTION:  dlParam: Pointer to the DataLinkParam (return)
                             ParamId: ParamID to search for in the map
                             ParameterIdentifierType: PID, SPN, etc
     RETURN VALUE:  true if a unique entry of ParamId and ParameterIdentifierType is found, dlParam is guaranteed to be a valid pointer to a DataLinkParam object
                    false otherwise, dlParam is nullptr

     *******************************************************************************/
    bool GetParam(ConstDlParmPtr_t &dlParam, unsigned_32 ParamId, DataLinkParam::DlpParamIdentifierType_t ParameterIdentifierType) const
    {
        // Find an entry with the matching ParamID
        auto it = DlDataMap.find(DataLinkParamInfo::GenerateCdlKey(ParamId, ParameterIdentifierType));
        if (it != DlDataMap.end() && (it->second.size() == 1))
        {
            dlParam = &it->second.front();
            return true;
        }
        dlParam = nullptr;
        return false;
    }

    bool GetParam(DlParmPtr_t &dlParam, unsigned_32 ParamId, DataLinkParam::DlpParamIdentifierType_t ParameterIdentifierType)
    {
        return GetParam(const_cast<ConstDlParmPtr_t&>(dlParam), ParamId, ParameterIdentifierType);
    }

    /******************************************************************************
     FUNCTION NAME: GetParam
     DESCRIPTION: Get parameter value by paramID, ParameterIdentifierType, Source Address, and DatalinkType.
     USAGE: DlParmPtr_t dlParam;
            if (GetParam(dlParam, BMI_CDL_PID_ENGINE_SPEED, DataLinkParam::, DATA_LINK_PARAM_CAN1_1939, 0x03)) {
                engineSpeed = dlParam->GetLastGoodValueEng();
            }

     PARAMETER DESCRIPTION:  dlParam: Pointer to the DataLinkParam (return)
                             ParamId: ParamID to search for in the map
                             ParameterIdentifierType: PID, SPN, etc
                             DataLinkType: DATA_LINK_PARAM_CAN1_1939 etc
                             SourceId: Source Address
     RETURN VALUE:  true if a unique entry of ParamId and ParameterIdentifierType is found, dlParam is guaranteed to be a valid pointer to a DataLinkParam object
                    false otherwise, dlParam is nullptr

     *******************************************************************************/
    bool GetParam(ConstDlParmPtr_t &dlParam, unsigned_32 ParamId, DataLinkParam::DlpParamIdentifierType_t ParameterIdentifierType, DataLinkParam::DlpDataLinkType_t DataLinkType, uint32_t SourceId) const
    {
        // Find an entry with the matching ParamID
        auto it = DlDataMap.find(DataLinkParamInfo::GenerateCdlKey(ParamId, ParameterIdentifierType));
        if (it != DlDataMap.end())
        {
            auto& params = it->second;
            auto itInner = std::find_if(params.begin(), params.end(),
                [DataLinkType, SourceId](const DataLinkParam& dlpFound) { return (SourceId == dlpFound.GetSid()) && (DataLinkType == dlpFound.GetDataLinkType()); } );
            if (itInner != params.end())
            {
                dlParam = &(*itInner);
                return true;
            }
        }
        dlParam = nullptr;
        return false;
    }

    bool GetParam(DlParmPtr_t &dlParam, unsigned_32 ParamId, DataLinkParam::DlpParamIdentifierType_t ParameterIdentifierType, DataLinkParam::DlpDataLinkType_t DataLinkType, uint32_t SourceId)
    {
        return GetParam(const_cast<ConstDlParmPtr_t&>(dlParam), ParamId, ParameterIdentifierType, DataLinkType, SourceId);
    }

    /******************************************************************************
     FUNCTION NAME: GetLastPIDValueIfGood
     DESCRIPTION: Get last good value of a fixed length PID.  Returns true if succesful.
                  May only be used if PID comes from a single source (DataLinkType and Source Address)
     PARAMETER DESCRIPTION:  ParamId: ParamID to search for in the map
                             ParamVParamValuelue: Last good value of the parameter (return)
     RETURN VALUE:  true if ParamValue contains the last (good) value
     *******************************************************************************/
    template <class T>
    bool GetLastPIDValueIfGood(unsigned_32 ParamId, T &ParamValue) const
    {
        ConstDlParmPtr_t dlParam;
        if (GetParam(dlParam, ParamId, DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID) &&
            dlParam->GetLastValueDsi() == DataLinkParam::DATA_LINK_PARAM_CDL_STATUS_OK)
        {
            ParamValue = dlParam->GetLastValue<T>();
            return true;
        }
        else
        {
            return false;
        }
    }


    /******************************************************************************
     FUNCTION NAME: GetLastPIDValueIfReceived
     DESCRIPTION: Get last received good value of a fixed length PID.  Returns true if succesful.
                  May only be used if PID comes from a single source (DataLinkType and Source Address)
     PARAMETER DESCRIPTION:  ParamId: ParamID to search for in the map
                             ParamVParamValuelue: Last good value of the parameter (return)
     RETURN VALUE:  true if ParamValue contains the last (good) value
     *******************************************************************************/
    template <class T>
    bool GetLastPIDValueIfReceived(unsigned_32 ParamId, T &ParamValue) const
    {
        ConstDlParmPtr_t dlParam;
        if (GetParam(dlParam, ParamId, DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID) &&
            dlParam->IsPIDDataReceived() &&
            dlParam->GetLastValueDsi() == DataLinkParam::DATA_LINK_PARAM_CDL_STATUS_OK)
        {
            ParamValue = dlParam->GetLastValue<T>();
            return true;
        }
        else
        {
            return false;
        }
    }

    /******************************************************************************
     FUNCTION NAME: GetLastPIDValueEngIfGood
     DESCRIPTION: Get last good scaled/engineering value of a fixed length PID.  Returns true if succesful.
                  May only be used if PID comes from a single source (DataLinkType and Source Address)
     PARAMETER DESCRIPTION:  ParamId: ParamID to search for in the map
                             ParamVlue: Last good value of the parameter (return)
     RETURN VALUE:  true if ParamValue contains the last (good) value
     *******************************************************************************/
    bool GetLastPIDValueEngIfGood(unsigned_32 ParamId, double &ParamValue) const
    {
        ConstDlParmPtr_t dlParam;
        if (GetParam(dlParam, ParamId, DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID) &&
            dlParam->GetLastValueDsi() == DataLinkParam::DATA_LINK_PARAM_CDL_STATUS_OK)
        {
            ParamValue = dlParam->GetLastValueEng();
            return true;
        }
        else
        {
            return false;
        }
    }

    /******************************************************************************
     FUNCTION NAME: GetDlpDiagInfo
     DESCRIPTION:return entire diagnostic information map
     PARAMETER DESCRIPTION:  No parameter.
     RETURN VALUE:  std::map<DlDiagsKey_t, dlpDiag>
     *******************************************************************************/
    DlDiags_t GetDlpDiagInfo() const
    {
        return DlpDiagInfo;
    }

    /******************************************************************************
     FUNCTION NAME: GetDiagnostic
     DESCRIPTION: return diagnostic information by providing cid and mid.
     PARAMETER DESCRIPTION:  cid: component id, mid: module id., diagnostic: dlpDiag (return)
     RETURN VALUE:  true if found, false otherwise
     *******************************************************************************/
    bool GetDiagnostic(uint16_t cid, uint32_t mid, dlpDiag& diagnostic) const
    {
        auto it = DlpDiagInfo.find(DlDiagsKey_t{cid, mid});
        if (it == DlpDiagInfo.end())
        {
            return false;
        }
        diagnostic = it->second;
        return true;
    }

    /******************************************************************************
     FUNCTION NAME: DlpDiagFmiUpdate
     DESCRIPTION: Update Fmi status for each Cid & Mid
     PARAMETER DESCRIPTION:  cid: component id, mid: module id, fmi: failure mode id, status: active/inactive
     RETURN VALUE:  void
     *******************************************************************************/
    void DlpDiagFmiUpdate( uint16_t cid, uint32_t mid, DldFmiCode_t fmi, DldFmiStatus_t status )
    {
        DlDiagsKey_t diagKey {cid, mid};
        auto it = DlpDiagInfo.find( diagKey );
        if( it == DlpDiagInfo.end() )
        {
            AIS_LOG_DEBUG("Adding cid %u, mid 0x%02X", cid, mid);
            DlpDiagInfo.emplace( diagKey, dlpDiag( cid, mid ) );
            it = DlpDiagInfo.find( diagKey );
        }
        switch ( fmi )
        {
            case DL_DATA_DIAG_FMI_FMI9:
                AIS_LOG_DEBUG("Updating FMI9 for cid %u, mid 0x%02X, status %u", cid, mid, status);
                it->second.UpdateLastFmi9Status( status );
                break;
            case DL_DATA_DIAG_FMI_FMI14:
                AIS_LOG_DEBUG("Updating FMI14 for cid %u, mid 0x%02X, status %u", cid, mid, status);
                it->second.UpdateLastFmi14Status( status );
                break;
        }
    }

    /******************************************************************************
     FUNCTION NAME: ClearDlpDiagInfo
     DESCRIPTION: clear fmi status history for all element in the map.
     PARAMETER DESCRIPTION:  No parameter.
     RETURN VALUE:  void
     *******************************************************************************/
    void ClearDlpDiagInfo()
    {
        for( auto& it : DlpDiagInfo )
        {
            it.second.ClearFmiStatus();
        }
    }

private:
    /* Add Fields Here */
    DlParams_t DlDataMap;
    DlDiags_t DlpDiagInfo;
    TaskSourceId_t TaskSourceId;
};

typedef Datum<DataLinkDataStorage> DataLinkData;

BOOST_CLASS_VERSION(DataLinkDataStorage, DataLinkParamInfo::DATALINK_PARAM_VERSION);
#endif

