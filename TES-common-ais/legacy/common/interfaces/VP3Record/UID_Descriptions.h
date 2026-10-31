#ifndef _UID_Descriptions_h_
#define _UID_Descriptions_h_
/* Record Size */
#define RECORD_MAX_SIZE                     13  //13 bytes data 


/* Modify lines below this as required. */
/* UID Related */

/* Record ID */
#define RECORD_ID                    (char)0xAA
#define RECORD_SIZE                  0x00,0x0A 

/* ---------- Segment UID's Information - VP3 Record ----------------- */

#define SEG_ID_PREFIX               (char)0x81,0x01,0x00
#define SEGMENT_ID                  SEG_ID_PREFIX,0x2F
#define TIMESTAMP_STARTIME          SEG_ID_PREFIX,0x07
#define SEGMENT_DURATION            SEG_ID_PREFIX,0x74
#define FUEL_CONSUMED               SEG_ID_PREFIX,0x4D
#define DISTANCE_TRAVELLED          SEG_ID_PREFIX,0x4C

/* ---------- Cycle UID's Information - VP3 Record ----------------- */

#define CYC_ID_PREFIX               (char)0x81,0x01,0x00
#define CYCLE_ID                    CYC_ID_PREFIX,0x2E
#define CYCLE_STARTIME              CYC_ID_PREFIX,0x07
#define CYCLE_STOPTIME              CYC_ID_PREFIX,0x07

/* ---------- Load UID's Information - VP3 Record ----------------- */

#define LOAD_PREFIX                 (char)0x81,0x01,0x00
#define LOAD_TIMESTAMP_STARTIME     LOAD_PREFIX,0x07
#define LOAD_TIMESTAMP_ENDTIME      LOAD_PREFIX,0x07
#define LOAD_TANSMISSIONSHIFT_COUNT LOAD_PREFIX,0x20

/* ---------- Payload UID's Information - VP3 Record ----------------- */

#define PAYLOAD_PREFIX              (char)0x81,0x01,0x00
#define PAYLOAD_TIME_OFFSET         PAYLOAD_PREFIX,0x75
#define PAYLOAD_CALCULATION_METHOD  0x00,0x01,0x1A,0x78
#define PAYLOAD_WEIGHT              PAYLOAD_PREFIX,0x4E
#define PAYLOAD_TIMESTAMP_STARTIME  PAYLOAD_PREFIX,0x07
#define PAYLOAD_PASSCOUNT           0x00,0x01,0x0F,0x4E
#define PAYLOAD_CARRYBACKPLDWT      0x00,0x01,0x13,0x60

/* ---------- Status UID's Information - VP3 Record ----------------- */

#define DATASOURCE_STANDALONE       0x00,0x37
#define DATASOURCE_TELEMATICS       0x01,(char)0x90

/* RecordType */
enum Record_Type: unsigned char
{
    LOAD =0x01,
    PAYLOAD,
    CYCLE,
    SEGMENT,
    STATUS,
    GPS
};

/* ID's */
enum UID_ID: unsigned  char
{
    ID_DEFAULT = 0x00,
    MACHINE_IDLE_DURATION = 0x01,
    LOADSTARTTIME = 0x13,
    LOADENDTIME = 0x14,
    OFFSETTIME_STARTIME = 0x15,
    CYCLE_START_TIME = 0x17,
    CYCLE_STOP_TIME = 0x18,
    SEGMENT_TIME_START = 0x19,
 
    // to be added based on the application.
};
        
/* Size */
enum UID_SIZE: unsigned char
{
     ONEBYTE =0x01,
     TWOBYTE,
     THREEBYTE,
     FOURBYTE,
     TENBYTE =0x0A,
     SHORTSTR = 32
     // to be added based on the application.
};

/* DataTypes*/            
enum UID_DataType: unsigned char
{
    DT_DEFAULT = 0x00,
    UNSIGNED_8 = 0x06,
    UNSIGNED_16MSB = 0x08,
    UNSIGNED_16 = 0x09,
    SIGNED_16MSB = 0x0A,
    SIGNED_16 = 0x0B,
    UIDTIMESTAMP = 0x13,
    SIGNED_32_FLOAT = 0x15,

    // to be added based on the application.
};
/* Color */    
enum UID_COLOR: unsigned char
{
     COLOR_DEFAULT = 0x00,
     PAYLOD_CYCLE = 0x0C,
     PAYLOAD_STATUS = 0x0D,
     CYCLE_TIMER = 0x1C,

     // to be added based on the application. 
};

/* FULL_PAYLOAD_UID's */
extern char UID_PayloadTime_Offset[] ;
extern char UID_Payload_CalcMethod[];
extern char UID_Payload_Weight[];
extern char UID_Payload_StartTime[];
extern char UID_Payload_PassCount[];
extern char UID_Payload_CarryBackPldWt[];

/* FULL_SEGMENT_UID's */
extern char UID_SegmentId[];
extern char UID_SegmentTime_Start[];
extern char UID_SegmentDuration[];
extern char UID_SegmentFuelConsumed[];
extern char UID_SegmentDistanceTravelled[];

/* FULL_CYCLE_UID's */
extern char UID_CycleId[];
extern char UID_CycleTime_Start[];
extern char UID_CycleTime_Stop[];

/* FULL_LOAD_UID's */
extern char UID_Load_Timestamp_Start[] ;
extern char UID_Load_TimeStamp_End[];
extern char UID_Load_TransmissionShiftCount[] ;

#endif

