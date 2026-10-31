////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiCdlWrapper
//
// File Name: BmiCdlWrapper.h
//
//  Abstract: Handle incoming CDL data link parameters.
//
////////////////////////////////////////////////////////
#ifndef Task_h
#include <ais/task/Task.h>
#endif

#ifndef OEL_PACK_H_
#include <oel_pack.h>
#endif

#ifndef BMICDLCDL2DEF_H
#include "BmiCdlCdl2Def.h"
#endif

#ifndef BMICDLWRAPPER_H
#include "BmiCdlWrapper.h"
#endif

#ifndef BMICDLPIDDEF_H
#include "BmiCdlPidDef.h"
#endif

#include <fstream>
#include <vector>

#include "VarLengthDataLinkParamPool.h"
#include "BmiCdlDiag.h"

#define BYTE_2_MASK 0xFF00
#define BYTE_1_MASK 0x00FF
//#define WRITE_TO_FILE


cdl2_4byte_rx_data_parm_t BmiCdlInputRxDataTbl[BMI_CDL_PARAM_TBL_ENTRIES_COUNT] = {0};
cdl2_cbs_input_tbl_t BmiCdlPidDataTbl = { BMI_CDL_PARAM_TBL_ENTRIES_COUNT, BmiCdlInputRxDataTbl };

static pthread_mutex_t syncLock = PTHREAD_MUTEX_INITIALIZER;
static DataLinkData dlData;

const BmiCdlParamCfg_t *ParamCfgPtr;
unsigned_32 paramTblIndex;
struct timespec CurrTime10, CurrTime20;

enum ParamSizeType
{
   FIXED,
   VARIABLE,
   UNDEFINED
};

BmiCdlWrapper::BmiCdlWrapper()
{
}

BmiCdlWrapper::~BmiCdlWrapper()
{
}

void BmiCdlWrapper::Initialize(void)
{
   AIS_LOG_INFO("BmiCdlWrapper::Initialize");
   signed int err_return_code = -1;

#ifdef WRITE_TO_FILE
if(std::remove("/opt/tmp/outputFiles/bmiCdl_PidData.out") != 0)
   {
      AIS_LOG_FATAL("Not able to delete bmiCdl_PidData.out");
   }
   else
   {
      AIS_LOG_FATAL("Successfully deleted bmiCdl_PidData.out");
   }

  std::ofstream textFile;
  textFile.open("/opt/tmp/outputFiles/bmiCdl_PidData.out", std::ofstream::app);
  if (textFile.is_open())
  {
      textFile << "TS, " << "PID, " <<  "Length, " <<  "DSI, " <<  "Data "  << "\n";
  }
  else
  {
      AIS_LOG_DEBUG("Unable to open bmiCdl_PidData.out");
  }
  textFile.close();

#endif
#ifdef WRITE_AUTOMATION_DATA
  CDL_Aut.AutomationInit();
#endif
   commInitialize();

   /* Initialize CAT data-link */
   cdl2_ginit(); /* This must be called during pre_irq initializations */

   /* Initialize CAT data-link */
   cdl2_read_response_ginit();
   cdl2_write_response_ginit();
   cdl2_spb_response_ginit();
   cdl2_pgb_response_ginit();
   cdl2_transmit_ginit();

   /* Initialize front panel routines. Supports PIDs 0xB4, 0xB5, 0xB6, 0xB7,
	 0xB8, 0xB9, 0xBA, 0xBB */
   cdl2_cfp_ginit();

   /* Initialize transmit FIFO buffer */
   (void) cdl2_transmit_ginit();

   /* CDL2 module specific initializations */
   /* Use the following ginit call to use CDL2 */
   cdl_rcv_did_set(OFF, 0x01, 0xFF); /* Ignore transmissions to these MID's. */
   cdl_rcv_did_set(ON, 0x00, 0x00); /* Accept general broadcast MID's. */
   cdl_default_mid_set(BMI_CDL_DRE_ADDRESS);
   cdl_rcv_did_set(ON, BMI_CDL_DRE_ADDRESS, BMI_CDL_DRE_ADDRESS);

   AIS_LOG_INFO("cdl2_cbs_ginit");
   err_return_code = cdl2_cbs_ginit( 0x00, /* Harness code not required */
         (cdl2_cbs_system_cfg_t *)&BmiCdlCbsSysTbl,  /* CBS system config table */
         (cdl2_cbs_ecm_cfg_t *) &BmiCdlCbsEcmTbl,  /* CBS ecm config table */
         (cdl2_cbs_parm_cfg_t *) BmiCdlCbsParamTbl, /* CBS parm config table */
         (cdl2_cbs_input_tbl_t *)NIL,
         (cdl2_cbs_get_func_ptr_t *)NIL,
         (cdl2_cbs_get_data_ptr_t *)NIL );

   AIS_LOG_WARN("cdl2_cbs_ginit -> err_return_code : %d  %x", err_return_code,
         err_return_code);

   AIS_LOG_INFO("cdl2_cbs_read_poll_enable");

   unsigned_16 PidCount = BmiCdlCbsParamTbl->Header.num_table_entries;
   unsigned_32 pidEnableRet;
   for(unsigned_16 pidIndex=0; pidIndex < PidCount; pidIndex++)
   {
      if(CBS_READ_POLL == BmiCdlCbsParamTbl->CbsParamTbl[pidIndex].parm_request_type)
      {
         pidEnableRet = cdl2_cbs_read_poll_enable(BmiCdlCbsParamTbl->CbsParamTbl[pidIndex].parm_id32);
         if(pidEnableRet == CDL2_TRANSMIT_STATUS_OKAY)
         {
            AIS_LOG_INFO("Read poll enabled ...Success for pid : %x",
                  BmiCdlCbsParamTbl->CbsParamTbl[pidIndex].parm.cdl_id32);
         }
         else if(pidEnableRet == CBS_READ_POLL_NOT_INIT_ERR ||
               pidEnableRet == CBS_READ_POLL_INVALID_ID_ERR)
         {
            AIS_LOG_ERROR("Read poll enabled ...%d for pid : %x",
                  pidEnableRet, BmiCdlCbsParamTbl->CbsParamTbl[pidIndex].parm.cdl_id32);
         }
         else if(pidEnableRet == CBS_READ_POLL_BUSY_ERR)
         {
            AIS_LOG_ERROR("Read poll enabled ...Busy for pid : %x",
                  BmiCdlCbsParamTbl->CbsParamTbl[pidIndex].parm.cdl_id32);
         }
         else if(pidEnableRet == CBS_READ_POLL_MAX_ERR)
         {
            AIS_LOG_ERROR("Read poll enabled ...Maxed out for pid : %x",
                  BmiCdlCbsParamTbl->CbsParamTbl[pidIndex].parm.cdl_id32);
         }
      }
   }

   cdl2_evt_report_ginit((cdl2_deactivate_system_event_t *)&BmiCdlDiag::AppDeactivateSystemEvent,
          (cdl2_activate_system_event_t *)&BmiCdlDiag::AppActivateSystemEvent);

}

int_16 BmiCdlWrapper::AppPidHandler(  unsigned_8 *data, /* pointer to message receive data */
      unsigned_8 data_len, /* message data length */
      void  *pie, /* pointer to pie or data */
      unsigned_16 rx_data_dsi_code /* receive data DSI */
)
{
   clock_gettime(CLOCK_MONOTONIC, &CurrTime10);

   AIS_LOG_DEBUG("AppPidHandler");

   DataLinkParam dlParam;

   // Set DataLinkType
   dlParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_CDL);

   std::vector<unsigned_8> paramData;

   paramTblIndex = (*((unsigned_32*) pie));
   //TODO: check index is valid
   ParamCfgPtr = &BmiCdlAppCfgTbl.ParamCfgTbl[paramTblIndex];

   VarLengthDataLinkParamPool::VarLengthParamType varLengthParamType = static_cast<VarLengthDataLinkParamPool::VarLengthParamType>(ParamCfgPtr->ConvTbl.VarLengthDataType);
   if ( nullptr == data )
   {
      return 0;
   }

   switch ( data_len )
   {
   case sizeof( unsigned_8 ):
   {
      unsigned_8 tempValue;
      OEL_UNPACK_BE_8_NO_INCR( data, tempValue );
      paramData.assign(reinterpret_cast<unsigned_8 *>( &tempValue ),
            reinterpret_cast<unsigned_8 *>( &tempValue ) + sizeof( tempValue ) ); //save temp value into paramData
      break;
   }
   case sizeof( unsigned_16 ):
   {
      unsigned_16 tempValue;
      OEL_UNPACK_BE_16_NO_INCR(data, tempValue);
      paramData.assign( reinterpret_cast<unsigned_8 *>( &tempValue ),
            reinterpret_cast<unsigned_8 *>( &tempValue ) + sizeof( tempValue ) ); //save temp value into paramData
      break;
   }
   case sizeof( unsigned_32 ):
   {
      unsigned_32 tempValue;
      OEL_UNPACK_BE_32_NO_INCR( data, tempValue );
      paramData.assign(reinterpret_cast<unsigned_8 *>( &tempValue ),
            reinterpret_cast<unsigned_8 *>( &tempValue ) + sizeof( tempValue ) ); //save temp value into paramData
      break;
   }
   default:
   {
      break;
   }
   }

   dlParam.SetSid(ParamCfgPtr->CbsParamTbl.mid);
   dlParam.SetParamId(ParamCfgPtr->CbsParamTbl.parm_id32);

   if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType)
   {
      dlParam.SetLastValue(paramData, rx_data_dsi_code);
   }
   else if (VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType)
   {
      // for special pid like F5D9 swapping is needed for normal data
      if (rx_data_dsi_code == BMI_CDL_DATA_STATUS_OK)
      {
         std::reverse( paramData.begin(), paramData.end() );
         dlParam.SetLastValue( paramData, rx_data_dsi_code);
      }
   }
   else
   {
      if (rx_data_dsi_code == BMI_CDL_DATA_STATUS_OK)
      {
         dlParam.SetVarLengthParamType( varLengthParamType );
         dlParam.SetVarLengthParamValue( data, data_len, rx_data_dsi_code );
      }
   }

   dlParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);

   pthread_mutex_lock(&syncLock);
   bool result = dlData.UpdateDataLinkParam(dlParam);
   pthread_mutex_unlock(&syncLock);

   if (false == result)
   {
       return 0;
   }

   if (rx_data_dsi_code == BMI_CDL_DATA_STATUS_OK)
   {
      AIS_LOG_INFO("pid %x, data_len %d, rx_data_dsi_code %u varLengthParamType %u", dlParam.GetParamId(),
            data_len, rx_data_dsi_code, varLengthParamType );

        if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType ||
            VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType)
        {
            AIS_LOG_INFO("param_type %d, pidData %x   %d", dlParam.GetParameterType(), dlParam.GetLastValue<unsigned_32>(), dlParam.GetLastValue<unsigned_32>() );
        }
        else
        {
            const unsigned_8* varParamBlock = dlParam.GetVarParamBlock();
            const unsigned_8 varParamBlockSize = dlParam.GetVarParamBlockLength();
            for (int i = 0; i < varParamBlockSize; i++)
            {
                AIS_LOG_INFO("pidData[%2d]          %x", i, varParamBlock[i]);
            }
        }

    }
    else // if rx_data_dsi_code not 0
    {
       AIS_LOG_WARN("pid %x, data_len %d, rx_data_dsi_code %x", dlParam.GetParamId(), data_len, rx_data_dsi_code);

        if (VarLengthDataLinkParamPool::NOT_APPLICABLE == varLengthParamType ||
            VarLengthDataLinkParamPool::SPL_PID_REV_DATA_BYTE_ORDER == varLengthParamType)
        {
           AIS_LOG_WARN("pidData %x   %d", dlParam.GetLastValue<unsigned_32>(), dlParam.GetLastValue<unsigned_32>());
        }
        else
        {
            for (int i = 0; i < data_len; i++)
            {
               AIS_LOG_WARN("pidData[%2d]          %x", i, data[i]);
            }
        }
    }
    
    clock_gettime(CLOCK_MONOTONIC, &CurrTime20);

#ifdef WRITE_TO_FILE

  std::ofstream textFile;
  textFile.open("/opt/tmp/outputFiles/bmiCdl_PidData.out", std::ofstream::app);
  if (textFile.is_open())
  {

      textFile <<  (CurrTime10.tv_sec * 1000) + (CurrTime10.tv_nsec / 1000000) << ", " 
            << (CurrTime20.tv_sec * 1000) + (CurrTime20.tv_nsec / 1000000) << ", "
            << std::hex << dlParam.GetParamId() << ", "
            << std::to_string(data_len) << ", "
            << std::hex  << rx_data_dsi_code << ", "
            << std::hex << paramData << ", "
            << std::to_string(paramData) << "\n";
  }
  else
  {
      AIS_LOG_DEBUG("Unable to open bmiCdl_PidData.out");
  }
  textFile.close();

#endif
#ifdef WRITE_AUTOMATION_DATA
  CDL_Aut.AutomationDataWriting(dlParam,rx_data_dsi_code,data_len);
#endif
   return (0);
}

void BmiCdlWrapper::AppConnectFunc(unsigned_8 mid, unsigned_8 status)
{
   AIS_LOG_INFO("*******AppConnectFunc*********");
   AIS_LOG_INFO("mid %x", mid);
   AIS_LOG_INFO("status %x", status);
}

void BmiCdlWrapper::PublishCdlData(DataLinkDataOutput* pDataLinkDataOutput)
{
   pthread_mutex_lock(&syncLock);
   // NULL check handled during initialization
   pDataLinkDataOutput->publish(dlData);

   // TODO: ONLY FOR TESTING, DON'T COMMIT
   // dlData.PrintDataLinkParamMap();

   pthread_mutex_unlock(&syncLock);
}


bool BmiCdlWrapper::AddDlParam(DataLinkParam dlParam)
{
   pthread_mutex_lock(&syncLock);  
   bool returnValue = dlData.AddDataLinkParam(dlParam);
   pthread_mutex_unlock(&syncLock);

   return returnValue;
}
void BmiCdlWrapper::UpdateDlpDiag( uint16_t cid, uint8_t mid, DataLinkData::DldFmiCode_t fmi, DataLinkData::DldFmiStatus_t status )
{
    pthread_mutex_lock(&syncLock);
    dlData.DlpDiagFmiUpdate( cid, mid, fmi, status );
    pthread_mutex_unlock(&syncLock);
}
