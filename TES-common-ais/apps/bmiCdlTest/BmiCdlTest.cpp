
#include "BmiCdlTest.h"
#include <time.h>

using namespace task;

struct timespec startTime, endTime;
#define BMI_CDL_PID_GROUND_SPEED            0x18
#define BMI_CDL_PID_GEAR                    0xF002
#define BMI_CDL_PID_ACTUAL_GEAR            0xF5D9
#define GROUND_SPEED_WITH_DIRECTION_PID     0xF4FD

AbstractTaskCore* task::getTaskImplementation(void)
{
    static BmiCdlTest thisTask("BmiCdlTest");
    return dynamic_cast<Task *>(&thisTask);
}

BmiCdlTest::BmiCdlTest( const std::string& taskName ):
    Task( taskName ),
    GroundSpeed{0.0, STATUS_BAD},
    GearData{0, STATUS_BAD},
    DataLinkDataInput_(nullptr)
{

}

BmiCdlTest::~BmiCdlTest( )
{
}

bool BmiCdlTest::initialize( )
{
    AIS_LOG_INFO( "BmiCdlTest::initialize" );

    DataLinkDataInput_ = dynamic_cast<DataLinkDataInput*>( InterfaceDb::fetch("DataLinkDataInput") );

    if ( !DataLinkDataInput_ )
    {
        AIS_LOG_FATAL( "no DataLinkDataInput_ interface not defined" );
        return false;
    }


    return true;
}

bool BmiCdlTest::executive( )
{
    AIS_LOG_INFO( "executive" );

    int count = 0;
    int count1 = 0;
    int Param_Id = 0; // To check if it's gear or actual gear

    DataLinkData dlData;
    clock_gettime(CLOCK_MONOTONIC_RAW, &startTime);
    while (DataLinkDataInput_->get(dlData))
    {
      //print data
      AIS_LOG_INFO("");
      auto& dlDataMap = dlData.GetDataLinkDataMap();
      count++;
      for (auto& kv : dlDataMap)
      {
         for (const DataLinkParam& dlParam : kv.second)
         {
            count1++;
            AIS_LOG_INFO("ParamID type %d sid %x paramId %x  dsi %x LastValue raw %X eng %.3f LastGoodValue raw %X eng %.3f scaling %.3f offset %.3f units %d",
                dlParam.GetDataLinkType(), dlParam.GetParamIdentifierType(), dlParam.GetSid(), dlParam.GetParamId(), dlParam.GetLastValueDsi(),
                dlParam.GetLastValue<unsigned_32>(), dlParam.GetLastValueEng(), dlParam.GetLastGoodValue<unsigned_32>(),
                dlParam.GetLastGoodValueEng(),dlParam.GetScaling(), dlParam.GetOffset(), dlParam.GetUnits());

            DlDataVect = dlParam.GetdlpDataVector();
            for(std::vector<DataLinkParam::dlpData_t>::iterator it = DlDataVect.begin(); it != DlDataVect.end(); ++it)
            {
                AIS_LOG_DEBUG("From Vector: value %x Dsi %x ", it->Value, it->Dsi);
            }

            // To calculate machine speed save gear (or actual gear) and ground speed values
                if (BMI_CDL_PID_GEAR == dlParam.GetParamId())
                {
                    Param_Id = BMI_CDL_PID_GEAR;
                    GearData.Val = dlParam.GetLastValueEng();
                    GearData.Stat = static_cast<stat_t>(dlParam.GetLastValueDsi());
                }
                else if (BMI_CDL_PID_ACTUAL_GEAR == dlParam.GetParamId())
                {
                    Param_Id = BMI_CDL_PID_ACTUAL_GEAR;
                    GearData.Val = dlParam.GetLastValueEng();
                    GearData.Stat = static_cast<stat_t>(dlParam.GetLastValueDsi());
                }
                else if (BMI_CDL_PID_GROUND_SPEED == dlParam.GetParamId())
                {
                    GroundSpeed.Val = dlParam.GetLastValueEng();
                    GroundSpeed.Stat = static_cast<stat_t>(dlParam.GetLastValueDsi());
                }
                else if (GROUND_SPEED_WITH_DIRECTION_PID == dlParam.GetParamId())
                {
                    Param_Id = GROUND_SPEED_WITH_DIRECTION_PID;
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
   AIS_LOG_DEBUG("count = %d, count1 = %d, sec = %ld, nsec = %ld endTimeSec = %ld, endTimeNsec = %ld", count, count1, startTime.tv_sec, startTime.tv_nsec,endTime.tv_sec, endTime.tv_nsec);

   // measure cycle rate and print out rate every 100 cycles
    static int cn = 0;
    cn++;
    static TimeStamp ts;
    TimeStamp last = ts;
    ts= localhostNow();
    double cr = (ts - last).toDouble();

    if ( cn % 5 == 1)
    {
        AIS_LOG_ERROR( "cycle rate is %lf hertz\n", 1.0 / cr );
    }

    getLogger().log_info("Param_Id %x, GroundSpeed.Stat %d, GearData.Stat %d", Param_Id, GroundSpeed.Stat, GearData.Stat);

    if(Param_Id !=0 && Param_Id !=GROUND_SPEED_WITH_DIRECTION_PID
        && STATUS_OK == GroundSpeed.Stat && STATUS_OK == GearData.Stat)
    {
        DataLinkDataStorage::CalcParamData_t machineSpeedData;

        machineSpeedData = dlData.CalcMachineSpeed(GroundSpeed.Val, GearData.Val, Param_Id);

        getLogger().log_info("MachineSpeed.Val = %f MachineSpeed.Stat %d\n",machineSpeedData.Val,machineSpeedData.Stat);
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



void BmiCdlTest::cleanup( )
{
    AIS_LOG_INFO( "BmiCdlTest::cleanup" );


}
