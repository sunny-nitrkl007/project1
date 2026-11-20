#include <ais/serialization/Datum.h> // For Boost serialization

#ifndef _CalMgrCmdResp_h_
#define _CalMgrCmdResp_h_

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

typedef enum
{
	  LPS_SA_CAL_SUCCESS,
	  LPS_SA_CAL_FAIL,
	  LPS_SA_CAL_UNKNOWN
}LpsSaCalRespCode_t;

typedef struct
{
	LpsSaCalRespCode_t RespCode;
	CAL_MGR_MR_E CalResp;
	unsigned_8	stepNo;
	unsigned_16 error;
	unsigned_16 warning;
	unsigned_8	EnableQualRead;
}LpsSaWeighCalibrationResp_t;

class CalMgrCmdRespStorage
{
public:
  CalMgrCmdRespStorage() /* Initialize Fields Here */ { }

  LpsSaWeighCalibrationResp_t  CalibrationResp;

  template <class Archive>
  void serialize(Archive& ar, unsigned int version)
  {
    /* Archive Fields Here */
	  ar & CalibrationResp.RespCode;
	  ar & CalibrationResp.CalResp;
	  ar & CalibrationResp.error;
	  ar & CalibrationResp.warning;
	  ar & CalibrationResp.stepNo;
	  ar & CalibrationResp.EnableQualRead;
  }

  void toCsv(CsvOutStream& out) const
  {
	  out("Cal Resp",CalibrationResp.CalResp);
	  out("Cal error",CalibrationResp.error);
	  out("Cal warning",CalibrationResp.warning);
	  out("Cal step no",CalibrationResp.stepNo);
	  out("Cal EnableQualRead",CalibrationResp.EnableQualRead);
  }

private:
  /* Add Fields Here */
};

typedef Datum<CalMgrCmdRespStorage> CalMgrCmdResp;

BOOST_CLASS_VERSION(CalMgrCmdRespStorage, 1);
#endif

