/*******************************************************************************
** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: PwmInput.cpp
DESCRIPTION:
*******************************************************************************/

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "PwmInput.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#define MAX_ECM_CH 4 //totel ECM Channels
#define FIFTY 50
#define ZERO 0 //0
#define STRING_SIZE 200 // single file, long string

/*   A6N2
*/
#define CH_1_FILE_MODE_PWM 	"echo 1 > /sys/class/tty/ttyS2/inputs/pwm_freq_stg_1/mode"
#define CH_2_FILE_MODE_PWM 	"echo 1 > /sys/class/tty/ttyS2/inputs/pwm_freq_stg_2/mode"
#define CH_3_FILE_MODE_PWM 	"echo 1 > /sys/class/tty/ttyS2/inputs/pwm_freq_stg_3/mode"
#define CH_4_FILE_MODE_PWM 	"echo 1 > /sys/class/tty/ttyS2/inputs/pwm_freq_stg_4/mode"

#define PWM_ENABLE_FILE 	"/sys/class/tty/ttyS2/inputs/coherent/enable"
#define PWM_DATA_FILE       "/sys/class/tty/ttyS2/inputs/coherent/data"
#define PWM_DEBUG_FILE       "/opt/Pwm_data.txt"

#define PWM_ENABLE_VALUES  	1,255


PwmInputChannels pwmOut;

PwmInputChannelsOutput   *outPwm ;

FILE* PWM_debug_file;	// sysfs files enable PWM input
FILE* PWM_data_file;	// sysfs files to read the Width for each PWM input
char widthString[STRING_SIZE];					// hold the value strings from sysfs files
int length;				// string length to remove the 0x0a character to 0x00
/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
using namespace task;

AbstractTaskCore* task::getTaskImplementation(void)
{
static PwmInput thisTask("PwmInput"); 
return dynamic_cast<Task *>(&thisTask);
}

/******************************************************************************
FUNCTION NAME:PwmInput constructor
DESCRIPTION: PwmInput constructor for initializes an instance of its class     
PARAMETER DESCRIPTION:  task name is passed
RETURN VALUE:  No return Value form constructor           
*******************************************************************************/
PwmInput::PwmInput( const std::string& taskName ):
    Task( taskName ),
    AppRegList( taskName ),
    AppRegInput_( nullptr ),
    AppRegOutput_( nullptr )


{
}

/******************************************************************************
FUNCTION NAME:PwmInput destructorl
DESCRIPTION: PwmInput destructor for deallocating an instance of its class
PARAMETER DESCRIPTION: No parameter
RETURN VALUE:   No return Value form destructor           
*******************************************************************************/
PwmInput::~PwmInput( )
{
}

/******************************************************************************
FUNCTION NAME:initialize
DESCRIPTION: SCS channel and PWM input buffer library is initialize
PARAMETER DESCRIPTION:  No parameter
RETURN VALUE:  Boolean           
*******************************************************************************/
bool PwmInput::initialize( )
{

	int cycleRate_hz;
	uint32_t keyoffTime = 0;

	getLogger().log_info( "PwmInput::initialize" );
	getTaskConfig().get( "cycleRate_hz", cycleRate_hz );

	if(!(getTaskConfig().get( "PwmAppKeyoffTimeout", keyoffTime)))
	{
		keyoffTime = 0;
	}
	printf("Key off Timeout : %u \n" , keyoffTime);
	AppRegList.SetKeyOffTimeOutMSec(keyoffTime);
	system(CH_1_FILE_MODE_PWM);
	system(CH_2_FILE_MODE_PWM);
	system(CH_3_FILE_MODE_PWM);
	system(CH_4_FILE_MODE_PWM);

//	PWM_debug_file = fopen(PWM_DEBUG_FILE , "a");
	
//	fprintf(PWM_debug_file , "Begin New Data \n ");

	/* Initialsing SCS interface */
	outPwm  = dynamic_cast<PwmInputChannelsOutput*>( InterfaceDb::fetch("PwmInputChannelsOutput") );
	AppRegOutput_ = dynamic_cast<AppRegOutput*>( InterfaceDb::fetch("AppRegOutput") );
	AppRegInput_ = dynamic_cast<AppRegInput*>( InterfaceDb::fetch("AppRegInput") );
	if ( !AppRegOutput_)
	{
		getLogger().log_error( "Interface AppRegOutput_ not configured." );
	}
	if ( !AppRegInput_)
    {
    	getLogger().log_error( "Interface AppRegInput_ not configured." );
    }
	
	return true;
}



/******************************************************************************
FUNCTION NAME:executive
DESCRIPTION:   executive function is required to publish the data to SCS channel
PARAMETER DESCRIPTION: No parameter
RETURN VALUE: Boolean            
*******************************************************************************/
timeval last;

bool PwmInput::executive( )
{
    timeval a;
    timeval c;
    timeval d;
    timeval e;

    gettimeofday(&a, 0);

	if(AppRegInput_)
	{	       
		UpdateRegistrations();
	}

	if (pwmOut.samplePWMInputs()) {
	    gettimeofday(&c, 0);
	}
	else {
	    AIS_LOG_FATAL("Failed to read PWM Inputs");
	}

	gettimeofday(&d, 0);

    if ( outPwm )
	{
		pwmOut.PwmData.ActualTimeUs = ((c.tv_sec*1000 + c.tv_usec/1000) - (a.tv_sec*1000 + a.tv_usec/1000));
		pwmOut.PwmData.DiffTime = ((d.tv_sec*1000 + d.tv_usec/1000) - (c.tv_sec*1000 + c.tv_usec/1000));
		pwmOut.PwmData.Exp++;
		outPwm ->publish( pwmOut );
	}
	else
	{
    	std::cout << "outPwm: NULL" << std::endl;
	}


    /* Return true for the executive method to be periodically invoked  */
	/* Return false to proceed to a graceful shutdown  */
    gettimeofday(&e, 0);
	
	pwmOut.PwmData.ExecTime = ((e.tv_sec*1000 + e.tv_usec/1000) - (a.tv_sec*1000 + a.tv_usec/1000));

	if(pwmOut.PwmData.ExecTime > 19)
	{
    	std::cout << " Read_PWM_data: " << (pwmOut.PwmData.ActualTimeUs) << " close: " << (pwmOut.PwmData.DiffTime) << " pub: " << ((e.tv_sec*1000 + e.tv_usec/1000) - (d.tv_sec*1000 + d.tv_usec/1000)) << " all: " << 
		(pwmOut.PwmData.ExecTime) << " interval:" << ((a.tv_sec*1000 + a.tv_usec/1000) - (last.tv_sec*1000 + last.tv_usec/1000)) << std::endl;
	
	//	fprintf(PWM_debug_file, "%d ms exectime at %d exp \n", pwmOut.PwmData.ExecTime, pwmOut.PwmData.Exp);	
	}
    last = a;	// save start of execute timestamp

	return true;  
}
void PwmInput::UpdateRegistrations(void)
{
    AIS_LOG_INFO( "AppRegTest::UpdateRegistrations" );

    AppReg appRegInfo;
    while (AppRegInput_->get(appRegInfo))
    {
        /*printf("Register Req type: %d App Name: %s dest app name: %s state: %d -> RecvdAppName: %s \n",
                 appRegInfo.GetMsgType(), appRegInfo.GetAppName().c_str(),
                 appRegInfo.GetDestAppName().c_str(), appRegInfo.GetAppState(),
                 AppRegList.GetAppName().c_str());   */

        if(!appRegInfo.IsMsgAddressedToMe(AppRegList.GetAppName())) 
			continue;

        if(appRegInfo.GetMsgType() == AppRegStorage::APP_REG_REQ)
        {
            AppRegList.UpdateAppRegState(&appRegInfo);
            //LOG_INFO("Update reg response %d", appRegInfo.GetRegStatus());
            AppRegOutput_->publish( appRegInfo );
        }
    }

}
/******************************************************************************
FUNCTION NAME:cleanup
DESCRIPTION:      
PARAMETER DESCRIPTION:                        
RETURN VALUE:void             
*******************************************************************************/
void PwmInput::cleanup( )
{
 AppReg appRegInfo;


 	while(!AppRegList.IsKeyOffTimeOut())
     {
 	 AIS_LOG_FATAL("Waiting %d : %d",
                AppRegList.GetTimeDiffMSec(), AppRegList.GetKeyOffTimeOutMSec());
	executive();
	if(AppRegList.IsAppRegListEmpty())
        {
            break;
        }
        //20 msec in IsKeyOffTimeOut for each loop. total of 120ms
     }

     if(AppRegList.IsKeyOffTimeOut())
     {
    	 getLogger().log_info( "Timed out....exiting." );
     }
     getLogger().log_info( "PwmInput::cleanup" );
//	 fclose(PWM_debug_file);
}

