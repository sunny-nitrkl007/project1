#include <ais/serialization/Datum.h> // For Boost serialization

#ifndef _CalMgrCmdReqst_h_
#define _CalMgrCmdReqst_h_

#if defined (__cplusplus)
extern "C"
{
#endif
#ifndef CAL_MGR_H_
#include  <cal_mgr.h>
#endif
#ifndef CDL2_MOD_PROTO_H_
#include  <cdl2_mod_proto.h>
#endif

#include <oel_rtos_posix.h>
#include <oel_oop.h>
#include <clock_struct.h>
#ifndef boolean
#include <cat_std_types.h>
#endif
#include <cdl2_struct.h>
#include <cdl_mod_struct.h>
#include <scl_j1939_struct.h>
#include <cdl_critics_defs.h>
#include <cdl2_defs.h>
#include <oel_rtos.h>
#include <cdl2_mod_defs.h>
#if defined (__cplusplus)
}
#endif

typedef struct
{
	unsigned_16  Src;
	unsigned_16  Dest;
	bool 		 CalibrationReqstFlag;
	CAL_MGR_MC_E Calcmd;
	unsigned_16	 Cal_id;		/* Calibration / Service Mode ID */
	unsigned_32  CalIterm[(CAL_LAST_ITERM_BIT>>5)+1];
}CalibrationRequest_t;

class CalMgrCmdReqstStorage
{
public:
  CalMgrCmdReqstStorage() /* Initialize Fields Here */
  {
	  CalibrationRequest.CalibrationReqstFlag = false;
  }

  CalibrationRequest_t CalibrationRequest;

  template <class Archive>
  void serialize(Archive& ar, unsigned int version)
  {
    /* Archive Fields Here */
	  ar & CalibrationRequest.Src;
	  ar & CalibrationRequest.Dest;
	  ar & CalibrationRequest.CalibrationReqstFlag;
	  ar & CalibrationRequest.Calcmd;
	  ar & CalibrationRequest.Cal_id;
	  ar & CalibrationRequest.CalIterm;
  }

  void toCsv(CsvOutStream& out) const
  {
	  out("Cal reqst flag ",CalibrationRequest.CalibrationReqstFlag);
      out("Cal cmd ",CalibrationRequest.Calcmd);
      out("Cal id ",CalibrationRequest.Cal_id);
  }

private:
  /* Add Fields Here */
};

typedef Datum<CalMgrCmdReqstStorage> CalMgrCmdReqst;

BOOST_CLASS_VERSION(CalMgrCmdReqstStorage, 1);
#endif

