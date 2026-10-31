#include "VP3Test.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

using namespace task;

AbstractTaskCore* task::getTaskImplementation(void)
{
   static VP3Test thisTask("VP3Test");
   return dynamic_cast<Task *>(&thisTask);
}

VP3Test::VP3Test(const std::string& taskName ):
    Task( taskName ),
    outShm(NULL)
{
   // TODO Auto-generated constructor stub

}

VP3Test::~VP3Test()
{
   // TODO Auto-generated destructor stub
}

bool VP3Test::initialize()
{
   outShm = dynamic_cast<ShmClockOutput*>( InterfaceDb::fetch("ShmClockOutput") );

   if(!outShm)
   {
      AIS_LOG_ERROR("Cannot initialize ShmClockOutput Channel");
      return false;
   }
  return true;
}

bool VP3Test::executive()
{
   ShmClock ShmObj;
   if(outShm)
   {
      AIS_LOG_ERROR("**************  the ShmClock  values *****");
      std::strncpy(ShmObj.pidF82D_pdata,std::string("1234562L").c_str(),8);
      std::strncpy(ShmObj.SWPartNum,std::string("172354647M").c_str(),10);
      ShmObj.ModelNum = "JJ456";
      std::strncpy(ShmObj.ECMPartNum,std::string("123456789G").c_str(),10);

      outShm ->publish(ShmObj);
   }
   else
   {
         /* Do nothing */
      }
   return true;
}
void VP3Test::cleanup( )
{
   getLogger().log_info( "RipperTest::cleanup" );
//  fclose(PWM_debug_file);
}
