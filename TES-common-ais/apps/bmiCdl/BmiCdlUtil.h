#ifndef BMICDLUTIL_H
#define BMICDLUTIL_H

#ifndef BMICDLTYPES_H
#include "BmiCdlTypes.h"
#endif

class BmiCdlUtil
{
public:
	BmiCdlUtil();
	~BmiCdlUtil();
	float DerivativeOfGroundSpeed(float currGroundSpeed, float ReqRateSec);
protected:

private:
	float lastGroundSpeed;
};

#endif // BMICDLUTIL_H
