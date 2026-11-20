////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Caterpillar Inc.  All Rights Reserved.
//
//     Class: DataLinkDataWrapper
//
// File Name: DataLinkDataWrapper.cpp
//
//  Abstract: Implementation of the class that provides
//            thread safe accessor functions for DataLinkData
//
////////////////////////////////////////////////////////

#include <ais/task/InterfaceDb.h>

#include "DataLinkDataWrapper.h"

// Declare class static data members
DataLinkData DataLinkDataWrapper::m_DataLinkData;
std::mutex DataLinkDataWrapper::m_LockDataLink;
DataLinkDataOutput* DataLinkDataWrapper::m_pDataLinkDataOutput = nullptr;

bool DataLinkDataWrapper::Initialize(std::string dataLinkDataOutputName)
{
    m_pDataLinkDataOutput = dynamic_cast<DataLinkDataOutput*>( task::InterfaceDb::fetch( dataLinkDataOutputName ) );

    if (m_pDataLinkDataOutput == nullptr)
    {
        AIS_LOG_ERROR("Unable to bind DataLinkDataOuptut");
        return false;
    }

    // Claim mutex for the entire duration of this function
    std::lock_guard<std::mutex> scopeLock( m_LockDataLink );

    return true;
}

bool DataLinkDataWrapper::AddDataLinkData(DataLinkParam &dlParam)
{
    // Claim mutex for the entire duration of this function
    std::lock_guard<std::mutex> scopeLock( m_LockDataLink );

    return m_DataLinkData.AddDataLinkParam( dlParam );
}

bool DataLinkDataWrapper::UpdateDataLinkData(DataLinkParam &dlParam)
{
    // Claim mutex for the entire duration of this function
    std::lock_guard<std::mutex> scopeLock( m_LockDataLink );

    return m_DataLinkData.UpdateDataLinkParam( dlParam );
}

void DataLinkDataWrapper::SendDataLinkData()
{
    // Claim mutex for the entire duration of this function
    std::lock_guard<std::mutex> scopeLock( m_LockDataLink );

    //only for Testing
    m_DataLinkData.PrintDataLinkParamMap();
    // NULL check handled during initialization
    m_pDataLinkDataOutput->publish( m_DataLinkData );
}

void DataLinkDataWrapper::UpdateDlpDiagStatus(unsigned_16 cid, unsigned_32 mid, DataLinkData::DldFmiCode_t fmi, DataLinkData::DldFmiStatus_t status) 
{
    // Claim mutex for the entire duration of this function
    std::lock_guard<std::mutex> scopeLock( m_LockDataLink );

    (void)m_DataLinkData.DlpDiagFmiUpdate( cid, mid, fmi, status );
}