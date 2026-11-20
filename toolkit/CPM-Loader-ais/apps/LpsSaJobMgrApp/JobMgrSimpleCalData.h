#ifndef JOBMGRSIMPLECALDATA_H_
#define JOBMGRSIMPLECALDATA_H_

#include <string>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>

#include "JobMgrProtocolTypes.h"

namespace jobmgr_data {

typedef struct
{
	std::string	timeStamp; // contains sec,min,hrs,mm,dd,yy
	float truckWt;
	float zeroedTruckWt;
	
	template <class Archive>
	void serialize(Archive& ar, unsigned int version)
	{
		ar & timeStamp;
		ar & truckWt;
		ar & zeroedTruckWt;
	}
} SimpleCalData_t;

}

BOOST_CLASS_VERSION(jobmgr_data::SimpleCalData_t, 0);

#endif
