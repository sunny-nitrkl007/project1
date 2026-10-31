
#include "VP3FileCreationSimulatorApp.h"

using namespace task;


AbstractTaskCore* task::getTaskImplementation(void)
{
    static VP3FileCreationSimulatorApp thisTask("VP3FileCreationSimulatorApp");
    return dynamic_cast<Task *>(&thisTask);
}

VP3FileCreationSimulatorApp::VP3FileCreationSimulatorApp( const std::string& taskName ):
    Task( taskName ),
    output_( NULL ),
	createFileRequestOutput_( NULL ),
	AppRegOutput_( NULL )
{
}

VP3FileCreationSimulatorApp::~VP3FileCreationSimulatorApp( )
{
}

bool VP3FileCreationSimulatorApp::initialize( )
{
    AIS_LOG_INFO( "VP3FileCreationSimulatorApp::initialize" );

    output_ = dynamic_cast<VP3RecordOutput*>( InterfaceDb::fetch( "VP3RecordOutput" ) );
    createFileRequestOutput_ = dynamic_cast<CreateFileRequestOutput*>( InterfaceDb::fetch( "CreateFileRequestOutput" ) );
	AppRegOutput_ = dynamic_cast<AppRegOutput*>( InterfaceDb::fetch("AppRegOutput") );
	
    getTaskConfig().get( "MaxRecordsToCreateFile", MaxRecordsToCreateFile );

    return true;
}



int loop = 0;
unsigned int createFileCounter = 0;
AppReg appRegInfo;

bool VP3FileCreationSimulatorApp::executive( )
{
    AIS_LOG_INFO( "VP3FileCreationSimulatorApp::executive" );

    if ( output_ )
    {
        //LOG_FATAL( "task configured to write to output interface" );
		appRegInfo.SetAppRegAttr("VP3Simulator", AppRegStorage::APP_REG_STATE_ACTIVE, "VP3FileCreationApp");
        AppRegOutput_->publish( appRegInfo );

        for (int x=0; x<=loop; x++)
        {
        	publishVp3Record();
        }

        loop++;
        if (loop > 5)
        	loop = 0;

        createFileCounter++;
        if (createFileCounter >= MaxRecordsToCreateFile)
        {
            static CreateFileRequest request;

            if ( createFileRequestOutput_ )
            {
            	request.fileNumber = 10129;			// VP3 filetype number
            	request.Requester  = "Simulator";
            	createFileRequestOutput_->publish( request );
            }

            createFileCounter = 0;
        }


        // measure cycle rate and print out rate every 100 cycles
        static int cn = 0;
        cn++;
        static TimeStamp ts;
        TimeStamp last = ts;
        ts= localhostNow();
        double cr = (ts - last).toDouble();
        if ( cn % 5 == 1)
        {
            printf( "cycle rate is %lf hertz\n", 1.0 / cr );
        }
    }
    else
    {
        AIS_LOG_ERROR( "no output interface defined" );
        return false;
    }

    return true;
}



void VP3FileCreationSimulatorApp::cleanup( )
{
    printf( "VP3FileCreationSimulatorApp::cleanup" );
	
	appRegInfo.SetAppRegAttr("VP3Simulator", AppRegStorage::APP_REG_STATE_INACTIVE, "VP3FileCreationApp");
    AppRegOutput_->publish( appRegInfo );
}


typedef struct __attribute__((packed))
{
	unsigned int utc;
	short int offset;
	unsigned int smh;
}timestamp;

typedef union _data {
	float f;
	char  s[4];
} myData;

void VP3FileCreationSimulatorApp::publishVp3Record()
{
    VP3Record record1,record2,record3,record4,record5,record6;
	
	timestamp TS;
	TS.utc = 0x45E43DFB;
	TS.offset = -90;
	TS.smh = 0x00856DCF;
	unsigned short int no_of_features = 0x00FF;
	short int dummy_features = -32767;  //0x8001 in hex
	unsigned char feature_type = 0x0F;
	char dummy_type = (char)-128;       //0x80 in hex
	float duration = 1234.567;
	std::string productID = "LAJ00149";
	unsigned long int securityKey = 0x1234567812345678;
	long int dummyKey = -1234567812345678; //0xFFFB9D2AC81810B2 in hex
	
	record1.setRecordType(Record_Type::LOAD);	
#if (MAKE_300_REC)	
	for(int i = 0; i < 50; i++)
#endif
	{
		record1.add_timestamp(UID_timestamp,TS.utc,TS.offset,TS.smh,true);
		record1.add_data_to_record<uint8_t>(UID_feature_type,feature_type,true);
		record1.add_data_to_record<int8_t>(UID_dummy_type,dummy_type,true);
		record1.add_data_to_record<uint16_t>(UID_no_of_features,no_of_features,true);
		record1.add_data_to_record<int16_t>(UID_dummy_features,dummy_features,true);
		record1.add_data_to_record<float>(UID_duration,duration,true);
		record1.add_string_to_record(UID_ProductID,productID);
		record1.add_data_to_record<uint64_t>(UID_Machine_security_key,securityKey,true);
		record1.add_data_to_record<int64_t>(UID_dummy_key,dummyKey,true);
	}
	output_->publish( record1 );

#if (!MAKE_300_REC)
	//Following are MSB forms of the above values.
	
	timestamp TS1;
	TS1.utc = 0xFB3DE445;
	TS1.offset = 0x0000;
	TS1.smh = 0xCF6D8500;
	unsigned short int no_of_features1 = 0xFF00;
	short int dummy_features1 = 0x0180;
	unsigned char feature_type1 = 0x0F;
	myData num;
	num.s[3] = 0x25; num.s[2] = 0x52; num.s[1] = 0x9A; num.s[0] = 0x44;
	//char productID1[] = {'L','A','J','0','0','1','4','9'};
	std::string productID1 = "LAJ00149";
	unsigned long int securityKey1 = 0x7856341278563412;
	long int dummyKey1 = 0xB21018C82A9DFBFF;
	
	record2.setRecordType(Record_Type::PAYLOAD);
	record2.add_timestamp(UID_timestamp,TS1.utc,TS1.offset,TS1.smh,false);
	record1.add_data_to_record<uint8_t>(UID_feature_type,feature_type1,false);
	record1.add_data_to_record<uint16_t>(UID_no_of_features,no_of_features1,false);
	record1.add_data_to_record<int16_t>(UID_dummy_features,dummy_features1,false);
	record1.add_data_to_record<float>(UID_duration,num.f,false);
	record1.add_string_to_record(UID_ProductID,productID1);
	record1.add_data_to_record<uint64_t>(UID_Machine_security_key,securityKey1,false);
	record1.add_data_to_record<int64_t>(UID_dummy_key,dummyKey1,false);
	output_->publish( record2 );
	
	record3.setRecordType(Record_Type::CYCLE);
	record3.add_timestamp(UID_timestamp,TS.utc,TS.offset,TS.smh,true);
	record3.add_data_to_record<uint8_t>(UID_feature_type,feature_type,true);
	record3.add_data_to_record<uint16_t>(UID_no_of_features,no_of_features,true);
	record3.add_data_to_record<float>(UID_duration,duration,true);
	record3.add_string_to_record(UID_ProductID,productID);
	output_->publish( record3 );
	
	record4.setRecordType(Record_Type::SEGMENT);
	record4.add_timestamp(UID_timestamp,TS.utc,TS.offset,TS.smh,true);
	record4.add_data_to_record<uint8_t>(UID_feature_type,feature_type,true);
	record4.add_data_to_record<uint16_t>(UID_no_of_features,no_of_features,true);
	record4.add_data_to_record<float>(UID_duration,duration,true);
	record4.add_string_to_record(UID_ProductID,productID);
	output_->publish( record4 );
	
	std::string truckName = "TrukName";
	std::string materialName = "Material Name.";
	record5 = VP3RecordBuilder::makeStatusRecord(TS.utc, TS.offset, TS.smh, truckName, materialName, 5.5f, "");
	output_->publish( record5 );
	
#if (MAKE_7TH_REC)
	record6.setRecordType(Record_Type::GPS);
	record6.add_timestamp(UID_timestamp,TS.utc,TS.offset,TS.smh,true);
	record6.add_data_to_record<uint8_t>(UID_feature_type,feature_type,true);
	record6.add_data_to_record<uint16_t>(UID_no_of_features,no_of_features,true);
	record6.add_data_to_record<float>(UID_duration,duration,true);
	record6.add_string_to_record(UID_ProductID,productID);
	output_->publish( record6 );
#endif
	
#endif
}
