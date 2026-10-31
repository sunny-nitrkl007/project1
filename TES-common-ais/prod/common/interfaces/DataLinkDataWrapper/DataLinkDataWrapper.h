////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Caterpillar Inc.  All Rights Reserved.
//
//     Class: DataLinkDataWrapper
//
// File Name: DataLinkDataWrapper.h
//
//  Abstract: Declaration of the class that provides
//            thread safe accessor functions for DataLinkData
//
////////////////////////////////////////////////////////

#ifndef DATALINKDATAWRAPPER_H_
#define DATALINKDATAWRAPPER_H_

#include <mutex>
#include <std_types.h>

#include <interfaces/DataLinkData/InterfaceTypes.h>

class DataLinkDataWrapper
{
public:
    DataLinkDataWrapper();
    virtual ~DataLinkDataWrapper() {}

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Initialize SCS channel and DataLinkData
    /// @return true if successful and false otherwise
    /// @param optional string name of DataLinkDataOutput channel in ruby config
    ///////////////////////////////////////////////////////////////////////////////
    static bool Initialize(std::string dataLinkDataOutputName = "DataLinkDataOutput");

     ///////////////////////////////////////////////////////////////////////////////
     /// @brief Accumulates DataLink meta data into an SCS object for future publishing
     /// @return true if successful and false otherwise
     /// @param DataLinkParam& dlParam 
     ///////////////////////////////////////////////////////////////////////////////
    static bool AddDataLinkData(DataLinkParam &dlParam);

     ///////////////////////////////////////////////////////////////////////////////
     /// @brief Accumulates received data from handlers into an SCS object for publishing
     /// @return true if successful and false otherwise
     /// @param DataLinkParam& dlParam
     ///////////////////////////////////////////////////////////////////////////////
    static bool UpdateDataLinkData(DataLinkParam &dlParam);

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Sends all the accumulated data over SCS interface. This is meant to be invoked periodically from the main task
    ///////////////////////////////////////////////////////////////////////////////
    static void SendDataLinkData();

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Updates FMI status
    /// @param cid
    /// @param mid
    /// @param fmi
    /// @param status
    ///////////////////////////////////////////////////////////////////////////////
    static void UpdateDlpDiagStatus(unsigned_16 cid, unsigned_32 mid, DataLinkData::DldFmiCode_t fmi, DataLinkData::DldFmiStatus_t status);

private:
    static DataLinkDataOutput*       m_pDataLinkDataOutput;
    static DataLinkData              m_DataLinkData;
    static std::mutex                m_LockDataLink;
};

#endif
