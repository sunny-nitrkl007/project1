/*******************************************************************************
 ** COPYRIGHT (C) 2017 CATERPILLAR INC. ALL RIGHTS RESERVED.
 --------------------------------------------------------------------------------
 FILE NAME: CoachingTaskTest.h
 DESCRIPTION:
 *******************************************************************************/
#ifndef _COACHINGTASKTEST_H_
#define _COACHINGTASKTEST_H_
/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/
#include <ais/task/Task.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <interfaces/DataLinkData/SecuritySystemCurrentSecurityIDParam.h>
#include <interfaces/CoachingSummaryData/InterfaceTypes.h>
#include <interfaces/Coaching3x3Data/InterfaceTypes.h>

/*******************************************************************************
 ** -- #defines --
 *******************************************************************************/
class CoachingTaskTest : public task ::Task
{
public:
   CoachingTaskTest();
   CoachingTaskTest(const std::string& taskName );
   virtual ~CoachingTaskTest();
   virtual bool initialize();
   virtual bool executive();
   void cleanup(void);

private:
   CoachingSummaryDataInput* coachingSummaryDataInput;
   Coaching3x3DataInput* coaching3x3DataInput;
   DataLinkDataOutput* dataLinkDataOutput;

   DataLinkData dataLinkData;
};

#endif /* _COACHINGTASKTEST_H_ */
