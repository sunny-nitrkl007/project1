
#include "BmiJ1939Test.h"
#include <time.h>

using namespace task;

struct timespec startTime, endTime;
#define BMI_CDL_PID_ENGINE_SPEED               0x40
#define BMI_CDL_PID_FUEL_RATE                   0xF525
#define BMI_CDL_PID_TOTAL_FUEL                  0xC8

#define BMI_CDL_PID_ACTUAL_GEAR                0xF5D9
#define GROUND_SPEED_WITH_DIRECTION_PID        0xF4FD
#define BMI_CDL_PID_DISTANCE_TRAVELLED          0xFC2E

#define BMI_CDL_PID_YAWRATE                   0xD01373
#define BMI_CDL_PID_LONG_ACCELERATION           0xD01375
#define BMI_CDL_PID_SLOPE                      0xF533

#define BMI_CDL_PID_BODY_UP                     0xF604
#define BMI_CDL_PID_AMBIENT_TEMP                0xF477
#define BMI_CDL_PID_PRODUCT_ID               0xF84D

#define BMI_CDL_PID_ENG_COOL_TEMP               0x44
#define BMI_CDL_PID_HYD_OIL_TEMP               0x45
#define BMI_CDL_PID_ENG_OIL_PRESSURE           0x54
#define BMI_CDL_PID_BATTERY_VOLTAGE            0xF013

#define BMI_CDL_PID_IMP_LOCKOUT_SWICTH_POS            0xF0B8
#define BMI_CDL_PID_BUCK_PAYLOAD                     0xF2C6
#define BMI_CDL_PID_TOT_MACH_OPE_CYCLE_CNT            0xFE22
#define BMI_CDL_PID_TOT_NEU_GEAR_OPERATING_HRS        0xFD31
#define BMI_CDL_PID_TRANS_OIL_TEMP                  0x4D
#define BMI_CDL_PID_FUEL_LVL_PERCENT               0x17
#define BMI_CDL_PID_PARKING_BRAKE_STATUS               0xF602

#define PROPRIETARY_A                0xEF00
#define EEC_1                      0xF004
#define EEC_2                      0xF003
#define ETC_1                      0xF002
#define ETC_2                      0xF005
#define EBC_1                     0xF001
char ProductId[8];

AbstractTaskCore* task::getTaskImplementation(void)
{
    static BmiJ1939Test thisTask("BmiJ1939Test");
    return dynamic_cast<Task *>(&thisTask);
}

BmiJ1939Test::BmiJ1939Test( const std::string& taskName ):
    Task( taskName ),       
    DataLinkDataInput_(NULL)   
{

}

BmiJ1939Test::~BmiJ1939Test( )
{
}

bool BmiJ1939Test::initialize( )
{
    AIS_LOG_NOTICE( "BmiJ1939Test::initialize" );

    DataLinkDataInput_ = dynamic_cast<DataLinkDataInput*>( InterfaceDb::fetch("DataLinkDataInput") );

    if ( !DataLinkDataInput_ )
    {
        AIS_LOG_FATAL( "no DataLinkDataInput_ interface not defined" );
        return false;
    }


    return true;
}

bool BmiJ1939Test::executive( )
{
   AIS_LOG_NOTICE( "executive" );

    int count = 0;
    int count1 = 0;
    int Param_Id = 0; // To check received PID

    DataLinkData dlData;
    clock_gettime(CLOCK_MONOTONIC_RAW, &startTime);
    while (DataLinkDataInput_->get(dlData))
    {
      //print data
      auto& dlDataMap = *dlData.GetDataLinkDataMapPtr();
      count++;
      for (auto& dlParamPair : dlDataMap)
      {
         count1++;
         for (auto& dlParamRef : dlParamPair.second)
         {
            auto dlParam = &dlParamRef;
            AIS_LOG_NOTICE("sid %x Param_Id %x  dsi %x LastValue raw %X eng %.3f LastGoodValue raw %X eng %.3f scaling %.3f offset %.3f units %d",
                  dlParam->GetSid(),
                  dlParam->GetParamId(),
                  dlParam->GetLastValueDsi(),
                  dlParam->GetLastValue<unsigned_32>(),
                  dlParam->GetLastValueEng(),
                  dlParam->GetLastGoodValue<unsigned_32>(),
                  dlParam->GetLastGoodValueEng(),
                  dlParam->GetScaling(),
                  dlParam->GetOffset(),
                  dlParam->GetUnits());

            DlDataVect = dlParam->GetdlpDataVector();
            for(std::vector<DataLinkParam::dlpData_t>::iterator it = DlDataVect.begin(); it != DlDataVect.end(); ++it)
            {
               AIS_LOG_NOTICE("From Vector: value %x Dsi %x ", it->Value, it->Dsi);
            }


            if(dlParam->GetParamIdentifierType() == DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN)
            {
               switch(dlParam->GetParamId())
               {

                     case EEC_1:
                           AIS_LOG_INFO(" EEC1 PGN Received");
                           AIS_LOG_INFO("GetVarLengthParamDsi = %d",dlParam->GetVarLengthParamDsi());
                     if( DataLinkParam::DSI_CODE_OK() == dlParam->GetVarLengthParamDsi())
                     {
                        if((dlParam->GetVarLengthParamType() == VarLengthDataLinkParamPool::PGN) )
                        {
                           const boost::shared_ptr<VarLengthDataLinkParam> varLengthParam = dlParam->GetVarLengthParam();
                           const unsigned_8* varParamBlock = dlParam->GetVarParamBlock();
                           const unsigned_8 varParamBlockSize = dlParam->GetVarParamBlockLength();
                           AIS_LOG_INFO("varParamBlockSize %d", varParamBlockSize);
                           for (int i = 0; i < varParamBlockSize; i++)
                           {
                              AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
                           }
                        }
                        else
                        {
                           if (dlParam->GetVarLengthParamType() != VarLengthDataLinkParamPool::PGN)
                           {
                              AIS_LOG_WARN("Expected VarLengthParamType to equal %d, but equals %d instead.", VarLengthDataLinkParamPool::PGN, dlParam->GetVarLengthParamType());
                           }
                        }
                     }
                     break;

                     case EEC_2:
                        AIS_LOG_INFO(" EEC2 PGN Received");
                        AIS_LOG_INFO("GetVarLengthParamDsi = %d",dlParam->GetVarLengthParamDsi());
                        if( DataLinkParam::DSI_CODE_OK() == dlParam->GetVarLengthParamDsi())
                        {
                           Param_Id = dlParam->GetParamId();
                           AIS_LOG_INFO("Param_Id = 0x%X", Param_Id);
                           AIS_LOG_INFO("ParamType = %d", dlParam->GetVarLengthParamType());
                           AIS_LOG_INFO("GetVarParamBlockLength = %d", dlParam->GetVarParamBlockLength());
                           if(dlParam->GetVarLengthParamType() == VarLengthDataLinkParamPool::PGN)
                           {
                              const unsigned_8* varParamBlock = dlParam->GetVarParamBlock();
                              const unsigned_8 varParamBlockSize = dlParam->GetVarParamBlockLength();
                              AIS_LOG_INFO("varParamBlockSize %d", varParamBlockSize);
                              for (int i = 0; i < varParamBlockSize; i++)
                              {
                                 AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
                              }

                           }
                           else
                           {
                              if (dlParam->GetVarLengthParamType() != VarLengthDataLinkParamPool::PGN)
                              {
                                 AIS_LOG_WARN("Expected VarLengthParamType to equal %d, but equals %d instead.", VarLengthDataLinkParamPool::PGN, dlParam->GetVarLengthParamType());
                              }
                           }
                        }
                     break;
                  case ETC_1:
                        AIS_LOG_INFO(" ETC1 PGN Received");
                        AIS_LOG_INFO("GetVarLengthParamDsi = %d",dlParam->GetVarLengthParamDsi());
                        if( DataLinkParam::DSI_CODE_OK() == dlParam->GetVarLengthParamDsi())
                        {
                           Param_Id = dlParam->GetParamId();
                           AIS_LOG_INFO("Param_Id = 0x%X", Param_Id);
                           AIS_LOG_INFO("ParamType = %d", dlParam->GetVarLengthParamType());
                           AIS_LOG_INFO("GetVarParamBlockLength = %d", dlParam->GetVarParamBlockLength());
                           if(dlParam->GetVarLengthParamType() == VarLengthDataLinkParamPool::PGN)
                           {
                              const unsigned_8* varParamBlock = dlParam->GetVarParamBlock();
                              const unsigned_8 varParamBlockSize = dlParam->GetVarParamBlockLength();
                              AIS_LOG_INFO("varParamBlockSize %d", varParamBlockSize);
                              for (int i = 0; i < varParamBlockSize; i++)
                              {
                                 AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
                              }

                           }else
                              {
                                 if (dlParam->GetVarLengthParamType() != VarLengthDataLinkParamPool::PGN)
                                 {
                                    AIS_LOG_WARN("Expected VarLengthParamType to equal %d, but equals %d instead.", VarLengthDataLinkParamPool::PGN, dlParam->GetVarLengthParamType());
                                 }
                              }
                        }
                  break;
                  case ETC_2:
                        AIS_LOG_INFO(" ETC2 PGN Received");
                        AIS_LOG_INFO("GetVarLengthParamDsi = %d",dlParam->GetVarLengthParamDsi());
                        if( DataLinkParam::DSI_CODE_OK() == dlParam->GetVarLengthParamDsi())
                        {
                           Param_Id = dlParam->GetParamId();
                           AIS_LOG_INFO("Param_Id = 0x%X", Param_Id);
                           AIS_LOG_INFO("ParamType = %d", dlParam->GetVarLengthParamType());
                           AIS_LOG_INFO("GetVarParamBlockLength = %d", dlParam->GetVarParamBlockLength());
                           if(dlParam->GetVarLengthParamType() == VarLengthDataLinkParamPool::PGN)
                           {
                              const unsigned_8* varParamBlock = dlParam->GetVarParamBlock();
                              const unsigned_8 varParamBlockSize = dlParam->GetVarParamBlockLength();
                              AIS_LOG_INFO("varParamBlockSize %d", varParamBlockSize);
                              for (int i = 0; i < varParamBlockSize; i++)
                              {
                                 AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
                              }
                           }
                           else
                           {
                              if (dlParam->GetVarLengthParamType() != VarLengthDataLinkParamPool::PGN)
                              {
                                 AIS_LOG_WARN("Expected VarLengthParamType to equal %d, but equals %d instead.", VarLengthDataLinkParamPool::PGN, dlParam->GetVarLengthParamType());
                              }
                           }
                        }
                     break;
                     case EBC_1:
                        AIS_LOG_INFO(" EBC1 PGN Received");
                        AIS_LOG_INFO("GetVarLengthParamDsi = %d",dlParam->GetVarLengthParamDsi());
                        if( DataLinkParam::DSI_CODE_OK() == dlParam->GetVarLengthParamDsi())
                        {
                           Param_Id = dlParam->GetParamId();
                           AIS_LOG_INFO("Param_Id = 0x%X", Param_Id);
                           AIS_LOG_INFO("ParamType = %d", dlParam->GetVarLengthParamType());
                           AIS_LOG_INFO("GetVarParamBlockLength = %d", dlParam->GetVarParamBlockLength());
                           if(dlParam->GetVarLengthParamType() == VarLengthDataLinkParamPool::PGN)
                           {
                              const unsigned_8* varParamBlock = dlParam->GetVarParamBlock();
                              const unsigned_8 varParamBlockSize = dlParam->GetVarParamBlockLength();
                              AIS_LOG_INFO("varParamBlockSize %d", varParamBlockSize);
                              for (int i = 0; i < varParamBlockSize; i++)
                              {
                                 AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
                              }

                           }
                           else
                           {
                              if (dlParam->GetVarLengthParamType() != VarLengthDataLinkParamPool::PGN)
                              {
                                 AIS_LOG_WARN("Expected VarLengthParamType to equal %d, but equals %d instead.", VarLengthDataLinkParamPool::PGN, dlParam->GetVarLengthParamType());
                              }
                           }
                        }
                     break;

               }
            }
            if(dlParam->GetParamIdentifierType() == DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_PID)
            {
               switch(dlParam->GetParamId())
               {
                  case BMI_CDL_PID_ENGINE_SPEED:

                           AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                        if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                        {
                           RxedData.Val = dlParam->GetLastValueEng();
                           RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                           AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                        }
                  break;
                  case BMI_CDL_PID_HYD_OIL_TEMP:

                                       AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                                    if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                                    {
                                       RxedData.Val = dlParam->GetLastValueEng();
                                       RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                                       AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                                    }
                              break;
                  case BMI_CDL_PID_IMP_LOCKOUT_SWICTH_POS:

                                       AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                                    if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                                    {
                                       RxedData.Val = dlParam->GetLastValueEng();
                                       RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                                       AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                                    }
                              break;

                  case BMI_CDL_PID_BUCK_PAYLOAD:

                                       AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                                    if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                                    {
                                       RxedData.Val = dlParam->GetLastValueEng();
                                       RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                                       AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                                    }
                              break;

                  case BMI_CDL_PID_TOT_MACH_OPE_CYCLE_CNT:

                                       AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                                    if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                                    {
                                       RxedData.Val = dlParam->GetLastValueEng();
                                       RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                                       AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                                    }
                              break;

                  case BMI_CDL_PID_TOT_NEU_GEAR_OPERATING_HRS:

                              AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                                 if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                                 {
                                    RxedData.Val = dlParam->GetLastValueEng();
                                    RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                                    AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                                 }
                        break;

                  case BMI_CDL_PID_TRANS_OIL_TEMP:

                              AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                                 if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                                 {
                                    RxedData.Val = dlParam->GetLastValueEng();
                                    RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                                    AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                                 }
                        break;
                  case BMI_CDL_PID_FUEL_LVL_PERCENT:

                              AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                                 if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                                 {
                                    RxedData.Val = dlParam->GetLastValueEng();
                                    RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                                    AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                                 }
                        break;



                  case BMI_CDL_PID_PARKING_BRAKE_STATUS:

                              AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                                 if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                                 {
                                    RxedData.Val = dlParam->GetLastValueEng();
                                    RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                                    AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                                 }
                        break;

                  case BMI_CDL_PID_BATTERY_VOLTAGE:

                                       AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                                    if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                                    {
                                       RxedData.Val = dlParam->GetLastValueEng();
                                       RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                                       AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                                    }
                              break;
                  case BMI_CDL_PID_ENG_OIL_PRESSURE:

                              AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                                 if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                                 {
                                    RxedData.Val = dlParam->GetLastValueEng();
                                    RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                                    AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                                 }
                        break;

                  case BMI_CDL_PID_FUEL_RATE:

                           AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                        if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                        {
                           RxedData.Val = dlParam->GetLastValueEng();
                           RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                           AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                        }
                     break;

                  case BMI_CDL_PID_TOTAL_FUEL:

                        AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                     if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                     {
                        RxedData.Val = dlParam->GetLastValueEng();
                        RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                        AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                     }
                  break;

                  case BMI_CDL_PID_ACTUAL_GEAR:

                     AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                     if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                     {
                        RxedData.Val = dlParam->GetLastValueEng();
                        RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                        AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                     }
               break;

                  case GROUND_SPEED_WITH_DIRECTION_PID:

                     AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                     if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                     {
                        RxedData.Val = dlParam->GetLastValueEng();
                        RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                        AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                     }
               break;

                  case BMI_CDL_PID_DISTANCE_TRAVELLED:

                     AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                     if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                     {
                        RxedData.Val = dlParam->GetLastValueEng();
                        RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                        AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                     }
               break;

                  case BMI_CDL_PID_YAWRATE:

                     AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                     if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                     {
                        RxedData.Val = dlParam->GetLastValueEng();
                        RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                        AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                     }
               break;

                  case BMI_CDL_PID_LONG_ACCELERATION:

                     AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                     if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                     {
                        RxedData.Val = dlParam->GetLastValueEng();
                        RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                        AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                     }
               break;

                  case BMI_CDL_PID_SLOPE:

                     AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                     if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                     {
                        RxedData.Val = dlParam->GetLastValueEng();
                        RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                        AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                     }
               break;

                  case BMI_CDL_PID_BODY_UP:

                     AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                     if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                     {
                        RxedData.Val = dlParam->GetLastValueEng();
                        RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                        AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                     }
               break;

                  case BMI_CDL_PID_AMBIENT_TEMP:

                     AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                     if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                     {
                        RxedData.Val = dlParam->GetLastValueEng();
                        RxedData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                        AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %f   stat = %d ", dlParam->GetParamId(), RxedData.Val, RxedData.Stat);
                     }
               break;
                  case BMI_CDL_PID_PRODUCT_ID:
                     AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                     if((dlParam->GetVarLengthParamType() == VarLengthDataLinkParamPool::PRODUCT_ID) &&
                           (dlParam->GetVarParamBlockLength() == ProductIdDataLinkParam::m_ProductIdParamSize))
                     {
                        const boost::shared_ptr<VarLengthDataLinkParam> varLengthParam = dlParam->GetVarLengthParam();
                        ProductIdDataLinkParam* productIdParam = dynamic_cast<ProductIdDataLinkParam*>(varLengthParam.get());
                        productIdParam->GetProductId(ProductId);

                        AIS_LOG_INFO("Received product id  : %s.", ProductId);
                     }
                  break;
                  case 0xD01F89:

                  AIS_LOG_INFO("pid = 0x%X", dlParam->GetParamId());
                  if( DataLinkParam::DSI_CODE_OK() == dlParam->GetLastValueDsi())
                  {
                     GearData.Val = dlParam->GetLastValueEng();
                     GearData.Stat = static_cast<stat_t>(dlParam->GetLastValueDsi());

                     AIS_LOG_INFO("Rxed Data for PID 0x%X with Val =  %d   stat = %d ", dlParam->GetParamId(), GearData.Val, GearData.Stat);
                  }
               break;
                  /*If required, add remaining all PID's here */
               }
            }
            if(dlParam->GetParamIdentifierType() == DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT)
            {
               AIS_LOG_INFO("Reached here1");
               switch(dlParam->GetParamId())
               {

                  case 0xF01A:
                     AIS_LOG_INFO(" Received 0xF01A CAT EXT ID");
                     AIS_LOG_INFO("GetVarLengthParamDsi = %d",dlParam->GetVarLengthParamDsi());
                     if( DataLinkParam::DSI_CODE_OK() == dlParam->GetVarLengthParamDsi())
                     {
                        if((dlParam->GetVarLengthParamType() == VarLengthDataLinkParamPool::CAT_EXT) )
                        {
                           const boost::shared_ptr<VarLengthDataLinkParam> varLengthParam = dlParam->GetVarLengthParam();
                           const unsigned_8* varParamBlock = dlParam->GetVarParamBlock();
                           const unsigned_8 varParamBlockSize = dlParam->GetVarParamBlockLength();
                           AIS_LOG_INFO("varParamBlockSize %d", varParamBlockSize);
                           for (int i = 0; i < varParamBlockSize; i++)
                           {
                              AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
                           }
                        }
                        else
                        {
                           if (dlParam->GetVarLengthParamType() != VarLengthDataLinkParamPool::CAT_EXT)
                           {
                              AIS_LOG_WARN("Expected VarLengthParamType to equal %d, but equals %d instead.", VarLengthDataLinkParamPool::CAT_EXT, dlParam->GetVarLengthParamType());
                           }
                        }
                     }
                  break;
                  case 0xF0B2:
                     AIS_LOG_INFO(" Received 0xF0B2 CAT EXT ID");
                     AIS_LOG_INFO("GetVarLengthParamDsi = %d",dlParam->GetVarLengthParamDsi());
                     if( DataLinkParam::DSI_CODE_OK() == dlParam->GetVarLengthParamDsi())
                     {
                        if((dlParam->GetVarLengthParamType() == VarLengthDataLinkParamPool::CAT_EXT) )
                        {
                           const boost::shared_ptr<VarLengthDataLinkParam> varLengthParam = dlParam->GetVarLengthParam();
                           const unsigned_8* varParamBlock = dlParam->GetVarParamBlock();
                           const unsigned_8 varParamBlockSize = dlParam->GetVarParamBlockLength();
                           AIS_LOG_INFO("varParamBlockSize %d", varParamBlockSize);
                           for (int i = 0; i < varParamBlockSize; i++)
                           {
                              AIS_LOG_INFO("pidData[%2d]    %x", i, varParamBlock[i]);
                           }
                        }
                        else
                        {
                           if (dlParam->GetVarLengthParamType() != VarLengthDataLinkParamPool::CAT_EXT)
                           {
                              AIS_LOG_WARN("Expected VarLengthParamType to equal %d, but equals %d instead.", VarLengthDataLinkParamPool::CAT_EXT, dlParam->GetVarLengthParamType());
                           }
                        }
                     }
                  break;
               }
            }
         }
      }
      auto dlDiag = dlData.GetDlpDiagInfo();
     for (auto it = dlDiag.begin(); it!=dlDiag.end(); it++)
     {
         if(it->second.GetFmi9Status().size() > 0)
         {
           AIS_LOG_ERROR("*****Mid 0x%02X, Cid %u, FMI 9 Active: %d", it->second.Mid, it->second.Cid, it->second.GetLastFmi9Status());
         }
         if(it->second.GetFmi14Status().size() > 0)
         {
           AIS_LOG_ERROR("*****Mid 0x%02X, Cid %u, FMI 14 Active: %d", it->second.Mid, it->second.Cid, it->second.GetLastFmi14Status());
         }
     }

    }

   clock_gettime(CLOCK_MONOTONIC_RAW, &endTime);
   AIS_LOG_NOTICE("count = %d, count1 = %d, sec = %ld, nsec = %ld endTimeSec = %ld, endTimeNsec = %ld", count, count1, startTime.tv_sec, startTime.tv_nsec,endTime.tv_sec, endTime.tv_nsec);

   // measure cycle rate and print out rate every 100 cycles
    static int cn = 0;
    cn++;
    static TimeStamp ts;
    TimeStamp last = ts;
    ts= localhostNow();
    double cr = (ts - last).toDouble();

    if ( cn % 5 == 1)
    {
       AIS_LOG_NOTICE( "cycle rate is %lf hertz\n", 1.0 / cr );
    }


    return true;
}

// Tests
// 1. task with an executive thread at 100Hz, determine if timing is periodic as expected (.01s between cycles)
// 2. task with 100Hz thread, receiving from 3 interfaces, data published at 1Hz, 20Hz, 100Hz
// 3. publishing data from both callback methods and from executive method
// 4. interfaces with 1 and 10 deep queues
// 5. reading 1 at a time, versus draining queue in callback
// 6. reading data in executive versus in a callback



void BmiJ1939Test::cleanup( )
{
    AIS_LOG_NOTICE( "BmiJ1939Test::cleanup" );


}
