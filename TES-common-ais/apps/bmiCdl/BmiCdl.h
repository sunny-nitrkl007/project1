#ifndef BMICDL_H
#define BMICDL_H

#ifndef Task_h
#include <ais/task/Task.h>
#endif

#ifndef _DataLinkDataInterfaceTypes_h_
#include <interfaces/DataLinkData/InterfaceTypes.h>
#endif

#include <interfaces/AppReg/InterfaceTypes.h>
#ifndef BMICDLWRAPPER_H
#include "BmiCdlWrapper.h"
#endif

#ifndef BMICDLCFG_H
#include "BmiCdlCfg.h"
#endif

extern BmiCdlWrapper CdlWrapper;

class BmiCdl: public task::Task
{
public:
    BmiCdl( const std::string& taskName );
    virtual ~BmiCdl( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );
protected:
private:
    AppRegStorage AppRegList;
    AppRegInput *AppRegInput_;
    AppRegOutput  *AppRegOutput_;
    DataLinkDataOutput *DataLinkDataOutput_;
    uint32_t *PidIndexTbl;
    BmiCdlUtil Util;
    BmiCdlCfg Cfg;
    DataLinkData dlDataObj;

    float ReqRateSec;
    void UpdateRegistrations();

};

#endif
