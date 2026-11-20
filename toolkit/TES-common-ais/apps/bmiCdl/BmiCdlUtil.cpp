#ifndef Task_h
#include <ais/task/Task.h>
#endif

#ifndef BMICDLUTIL_H
#include "BmiCdlUtil.h"
#endif

BmiCdlUtil::BmiCdlUtil()
{
	lastGroundSpeed = 0.0;
}

BmiCdlUtil::~BmiCdlUtil()
{

}

float BmiCdlUtil::DerivativeOfGroundSpeed(float currGroundSpeed, float ReqRateSec)
{
	AIS_LOG_INFO("lastGroundSpeed %f currGroundSpeed %f ReqRateSec %f",
			this->lastGroundSpeed, currGroundSpeed, ReqRateSec);
	float foreAftAccel = (currGroundSpeed - this->lastGroundSpeed)/ReqRateSec;
	this->lastGroundSpeed = currGroundSpeed;

	return foreAftAccel;
}
