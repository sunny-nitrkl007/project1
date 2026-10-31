////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939SCS
//
// File Name: BmiJ1939SCS.cpp
//
//  Abstract: Implementation of the class that handles
//            the SCS objects for this application
//
////////////////////////////////////////////////////////

#include <ais/task/InterfaceDb.h>
#include "BmiJ1939SCS.h"
#include "BmiJ1939.h"


// Declare class static data members
DataLinkData BmiJ1939SCS::m_AccumulatedData;
std::mutex BmiJ1939SCS::m_LockDataLink;
DataLinkDataOutput* BmiJ1939SCS::m_pSCSDataLinkData = nullptr;

////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939SCS::SCSInitJ1939
// Description     : Class constructor
// Return Type     : bool - true if successful and false otherwise
// Argument [in]   : DataLinkParamInfo::DlpDataLinkType_t dataLinkType
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiJ1939SCS::SCSInitJ1939(DataLinkParamInfo::DlpDataLinkType_t dataLinkType)
{
   m_pSCSDataLinkData = dynamic_cast<DataLinkDataOutput*>( task::InterfaceDb::fetch( "DataLinkDataOutput" ) );

   if (m_pSCSDataLinkData == nullptr)
   {
      AIS_LOG_ERROR("Unable to bind DataLinkDataOuptut");
      return false;
   }

   // Claim mutex for the entire duration of this function
   std::lock_guard<std::mutex> scopeLock( m_LockDataLink );

   return true;
}


////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939SCS::UpdateDataLinkData
// Description     : Serves as a callback function from the J1939 data
//                   handlers. Accumulates J1939 data link data into an
//                   SCS object for future publishing
// Return Type     : bool - true if successful and false otherwise
// Argument [in]   : const DataLinkParam& dlParam - New J1939 data to append
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiJ1939SCS::UpdateDataLinkData( DataLinkParam& dlParam )
{
   // Claim mutex for the entire duration of this function
   std::lock_guard<std::mutex> scopeLock( m_LockDataLink );

 /*  // Add new data to the data to be sent out
   unsigned_8 type = static_cast<unsigned_8>( dlParam.GetParamType() );
   if( type == 0 )
   {
   AIS_LOG_NOTICE( "Adding to send param 0x%X (type %d) with DSI 0x%X and value %.3f",
         dlParam.GetParamId(), type, dlParam.GetLastValueDsi(), dlParam.GetLastValueEng() );
   }
   else if( type ==3 )
   {
	   AIS_LOG_NOTICE( "Adding to send param 0x%X (type %d) with DSI 0x%X and VarParamBlockLength %d",
	            dlParam.GetParamId(), type, dlParam.GetLastValueDsi(), dlParam.GetVarParamBlockLength());
   }*/

#ifdef WRITE_AUTOMATION_DATA
   BmiJ1939Automation::AutomationDataWrite (dlParam);
#endif

   return m_AccumulatedData.UpdateDataLinkParam(dlParam);
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939SCS::AddDataLinkData
// Description     : Serves as a callback function from the J1939 data
//                   handlers. Accumulates J1939 data link data into an
//                   SCS object for future publishing
// Return Type     : bool - true if successful and false otherwise
// Argument [in]   : const DataLinkParam& dlParam - New J1939 data to append
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
bool BmiJ1939SCS::AddDataLinkData( DataLinkParam& dlParam )
{
	 // Claim mutex for the entire duration of this function
	std::lock_guard<std::mutex> scopeLock( m_LockDataLink );

	return m_AccumulatedData.AddDataLinkParam( dlParam );
}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939SCS::UpdateDiagStatus
// Description     : Accumulates J1939 data link data into an
//                   SCS object for future publishing
// Return Type     : None
// Argument [in]   : unsigned_16 cid - cid for ECM
//					 unsigned_32 mid - source address
//					 DataLinkData::DldFmiCode_t fmi - FMI code i.e. 9 or 14
//					 DataLinkData::DldFmiStatus_t status - FMI Active status
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939SCS::UpdateDiagStatus( unsigned_16 cid, unsigned_32 mid, DataLinkData::DldFmiCode_t fmi, DataLinkData::DldFmiStatus_t status )
{
	// Claim mutex for the entire duration of this function
   std::lock_guard<std::mutex> scopeLock( m_LockDataLink );

   (void)m_AccumulatedData.DlpDiagFmiUpdate( cid, mid, fmi, status );

}
////////////////////////////////////////////////////////////////////////////
// Function        : BmiJ1939SCS::SendDataLinkData
// Description     : Sends all the accumulated J1939 data over SCS interface.
//                   This is meant to be invoked periodically from the main task
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
void BmiJ1939SCS::SendDataLinkData( void )
{
   // Claim mutex for the entire duration of this function
   std::lock_guard<std::mutex> scopeLock( m_LockDataLink );

   // NULL check handled during initialization
   m_pSCSDataLinkData->publish( m_AccumulatedData );
}
