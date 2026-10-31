////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiCdlDiag
//
// File Name: BmiCdlDiag.cpp
//
//  Abstract: Handle CDL data link Diagnostic Conditions.
//
////////////////////////////////////////////////////////

#include "BmiCdlDiag.h"

#ifndef Task_h
#include <ais/task/Task.h>
#endif

#ifndef BMICDLCDL2DEF_H
#include "BmiCdlCdl2Def.h"
#endif

#include "BmiCdlWrapper.h"
#include <cdl2_struct.h>

void BmiCdlDiag::AppActivateSystemEvent( unsigned_16 cid, unsigned_8 fmi)
{
   AIS_LOG_WARN("FMI Active, cid: %X  fmi: %d", cid, fmi );

   switch ( fmi )
   {
      case CDL2_FMI_ABNORMAL_UPDATE:
         BmiCdlWrapper::UpdateDlpDiag( cid, FindMidbyCid(cid),
               DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI9,
               DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_ACTIVE );
         break;
      case CDL2_FMI_BAD_DEVICE:
         BmiCdlWrapper::UpdateDlpDiag( cid, FindMidbyCid(cid),
               DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI14,
               DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_ACTIVE );
         break;
   }
}

void BmiCdlDiag::AppDeactivateSystemEvent( unsigned_16 cid, unsigned_8 fmi)
{
   AIS_LOG_NOTICE("FMI DeActive, cid: %X  fmi: %d", cid, fmi);
   switch ( fmi )
   {
      case CDL2_FMI_ABNORMAL_UPDATE:
         BmiCdlWrapper::UpdateDlpDiag( cid, FindMidbyCid(cid),
               DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI9,
               DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_INACTIVE );
         break;
      case CDL2_FMI_BAD_DEVICE:
         BmiCdlWrapper::UpdateDlpDiag( cid, FindMidbyCid(cid),
               DataLinkData::DldFmiCode_t::DL_DATA_DIAG_FMI_FMI14,
               DataLinkData::DldFmiStatus_t::DL_DATA_DIAG_INACTIVE );
         break;
   }
}

unsigned_8 BmiCdlDiag::FindMidbyCid(unsigned_16 cid)
{
   for(int i=0; i<(BmiCdlCbsEcmTbl.Header.num_table_entries); i++)
   {
      if(BmiCdlCbsEcmTbl.table[i].cid == cid)
      {
         return BmiCdlCbsEcmTbl.table[i].mid;
      }
   }
   return 0;
}
