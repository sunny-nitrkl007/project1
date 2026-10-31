////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiCdlDiag
//
// File Name: BmiCdlDiag.h
//
//  Abstract: Handle CDL data link Diagnostic Conditions.
//
////////////////////////////////////////////////////////

#ifndef BMICDLDIAG_H
#define BMICDLDIAG_H

#ifndef COMMTASK_H_
#include <commTask/commTask.h>
#endif
#include "DataLinkData.h"
#include "BmiCdlWrapper.h"

class BmiCdlDiag
{
public:
   BmiCdlDiag() = delete;
   ~BmiCdlDiag() = delete;
   static void AppActivateSystemEvent( unsigned_16 cid, unsigned_8 fmi);
   static void AppDeactivateSystemEvent( unsigned_16 cid, unsigned_8 fmi);
   static unsigned_8 FindMidbyCid(unsigned_16 cid);

protected:

private:

};

#endif // BMICDLDIAG_H
