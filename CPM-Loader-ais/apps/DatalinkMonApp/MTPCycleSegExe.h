/*******************************************************************************
** COPYRIGHT (C) 2019 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME:  MTPCycleSegExe.h

DESCRIPTION: MG App Seg public include file.
*******************************************************************************/

#ifndef __MTP_CYC_SEG_APP_H__
#define __MTP_CYC_SEG_APP_H__

#include <ais/config/ConfigSection.h>
#include <ais/task/Task.h>
#include <stdio.h>
#include <unordered_map>
#include <functional>
#include <commTask/commTask.h>
#include <interfaces/AppReg/InterfaceTypes.h>
#include <interfaces/CreateFileRequest/InterfaceTypes.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <interfaces/PartNumbers/InterfaceTypes.h>
#include <interfaces/ShmClock/InterfaceTypes.h>
#include <interfaces/VP3Record/InterfaceTypes.h>

class MTPCycleSegApp: public task::Task
{
public:

    /* Constructor */
    MTPCycleSegApp( const std::string& taskName );

    /* Destructor */
    virtual ~MTPCycleSegApp();

    virtual bool initialize();
    virtual bool executive();
    virtual void cleanup();

private:

    // SCS Functions
    bool ReadDataLinkData();
    // SCS Channels
    DataLinkDataInput*              dataLinkDataInput;


    // Constants and Typedefs
    static constexpr unsigned_32 DefaultGpsDistanceThreshold = 20; // meters
    static constexpr unsigned_32 DefaultGpsTimeThreshold     = 60; // seconds
    const std::string Vp3AppName                             = "VP3FileCreationApp";
    const std::string ProductIdDefault                       = "AG900001";

    typedef std::string SNPrefix_t;
    typedef std::unordered_map<SNPrefix_t, uint32_t> AppIdMap_t;

    // Variables
    static const AppIdMap_t appIdMap;

    std::string             taskName;
    ConfigSection           rubyCfg;
    unsigned_8              previousPositionStatus;
};

#endif
