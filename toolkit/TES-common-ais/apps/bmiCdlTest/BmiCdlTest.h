#ifndef BMICDLTEST_H
#define BMICDLTEST_H

#include <ais/task/Task.h>

#ifndef _Tpms2DataLinkChannel_h_
#include <interfaces/DataLinkData/InterfaceTypes.h>
#endif

#include <interfaces/DataLinkData/DataLinkData.h>
#include <interfaces/DataLinkData/GPSDataLinkParam.h>
#include <interfaces/DataLinkData/VarLengthDataLinkParam.h>

typedef enum
{
   RET_SUCCESS = 0,
   RET_ERROR
}Ret_t;

typedef enum
{
    STATUS_OK =0,
    STATUS_BAD
}stat_t;

typedef struct
{
   uint16_t Val;
   stat_t Stat;
}Data_uint16_t;

typedef struct
{
   float Val;
   stat_t Stat;
}Data_float_t;


class BmiCdlTest: public task::Task
{
public:
    BmiCdlTest( const std::string& taskName );
    virtual ~BmiCdlTest( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );

    Data_float_t GroundSpeed;
    Data_uint16_t GearData;
protected:
private:

    DataLinkDataInput *DataLinkDataInput_;
    std::vector<DataLinkParam::dlpData_t> DlDataVect;


};

#endif
