////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939SCS
//
// File Name: BmiJ1939SCS.h
//
//  Abstract: Declarations for the class that handles
//            the SCS objects for this application
//
////////////////////////////////////////////////////////

#ifndef BMIJ1939SCS_H_
#define BMIJ1939SCS_H_

#include <mutex>              // std::mutex
#include <std_types.h>
#ifndef _DataLinkDataInterfaceTypes_h_
#include <interfaces/DataLinkData/InterfaceTypes.h>
#endif

class BmiJ1939SCS
{
public:
   BmiJ1939SCS( void );
   virtual ~BmiJ1939SCS( void ) { }

   static bool AddDataLinkData( DataLinkParam& dlParam );
   static bool UpdateDataLinkData( DataLinkParam& dlParam );
   static void SendDataLinkData( void );
   static void UpdateDiagStatus( unsigned_16 cid, unsigned_32 mid, DataLinkData::DldFmiCode_t fmi, DataLinkData::DldFmiStatus_t status );
   static bool SCSInitJ1939( DataLinkParamInfo::DlpDataLinkType_t dataLinkType );

private:
   static DataLinkDataOutput*                   m_pSCSDataLinkData;
   static DataLinkData                          m_AccumulatedData;
   static std::mutex                            m_LockDataLink;
};

#endif // BMIJ1939SCS_H_
