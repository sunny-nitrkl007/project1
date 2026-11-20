#ifndef BMIJ1939TEST_H
#define BMIJ1939TEST_H

#include <ais/task/Task.h>

#ifndef _Tpms2DataLinkChannel_h_
#include <interfaces/DataLinkData/InterfaceTypes.h>
#endif

#include <interfaces/DataLinkData/GPSDataLinkParam.h>
#include <interfaces/DataLinkData/TimeZoneDataLinkParam.h>
#include <interfaces/DataLinkData/VarLengthDataLinkParam.h>
#include <interfaces/DataLinkData/ProductIdDataLinkParam.h>

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


class BmiJ1939Test: public task::Task
{
public:
    BmiJ1939Test( const std::string& taskName );
    virtual ~BmiJ1939Test( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );

    Data_float_t RxedData;
    Data_uint16_t GearData;
protected:
private:

    DataLinkDataInput *DataLinkDataInput_;
    std::vector<DataLinkParam::dlpData_t> DlDataVect;


};

#endif
