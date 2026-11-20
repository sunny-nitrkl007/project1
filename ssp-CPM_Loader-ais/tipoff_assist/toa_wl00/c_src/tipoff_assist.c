/***********************************************************************
* DESCRIPTION :
*       Calculates the mass and distance of the tool pinned to a wheel
*       loader linkage and its payload.  Wraps individual model-linkage
*       combo files' functions.
*
*       Copyright Caterpillar, Inc. 2017-2019
*
***********************************************************************/

#include <math.h>
#include "tipoff_assist.h"
#include "tipoff_assist_950_14A_HL.h"
#include "tipoff_assist_950_14A_LOG.h"
#include "tipoff_assist_950_14A_STD.h"
#include "tipoff_assist_950_14A_Z_HL.h"
#include "tipoff_assist_950_14A_Z_LOG.h"
#include "tipoff_assist_950_14A_Z_STD.h"
#include "tipoff_assist_962_14A_HL.h"
#include "tipoff_assist_962_14A_LOG.h"
#include "tipoff_assist_962_14A_STD.h"
#include "tipoff_assist_962_14A_Z_HL.h"
#include "tipoff_assist_962_14A_Z_SL.h"
#include "tipoff_assist_962_14A_Z_STD.h"
#include "tipoff_assist_966_14A_HL.h"
#include "tipoff_assist_966_14A_LOG.h"
#include "tipoff_assist_966_14A_STD.h"
#include "tipoff_assist_972_14A_HL.h"
#include "tipoff_assist_972_14A_SL.h"
#include "tipoff_assist_972_14A_STD.h"
#include "tipoff_assist_980_14A_BLK.h"
#include "tipoff_assist_980_14A_HL.h"
#include "tipoff_assist_980_14A_HVY.h"
#include "tipoff_assist_980_14A_LOG.h"
#include "tipoff_assist_980_14A_STD.h"
#include "tipoff_assist_982_14A_HL.h"
#include "tipoff_assist_982_14A_LOG.h"
#include "tipoff_assist_982_14A_STD.h"


void toa_mass_and_dist_by_id(unsigned long int id, double tilt_force, double lift_force, double tilt_cyl_ext,
                             double arm_ang, double BC_len, double imu_x, double imu_y,
                             double *return_mass, double *return_dist) {
    if (id == 50700) {
		mass_and_dist_950_14A_STD(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
	}
    else if (id == 50701) {
		mass_and_dist_950_14A_HL(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
	}
    else if (id == 50702) {
		mass_and_dist_950_14A_LOG(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
	}
    else if (id == 50708) {
		mass_and_dist_950_14A_Z_STD(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
	}
    else if (id == 50709) {
		mass_and_dist_950_14A_Z_HL(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
	}
    else if (id == 50710) {
		mass_and_dist_950_14A_Z_LOG(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
	}
    else if (id == 62700) {
		mass_and_dist_962_14A_STD(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
	}
    else if (id == 62701) {
		mass_and_dist_962_14A_HL(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
	}
    else if (id == 62702) {
		mass_and_dist_962_14A_LOG(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
	}
    else if (id == 62708) {
		mass_and_dist_962_14A_Z_STD(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
	}
    else if (id == 62709) {
		mass_and_dist_962_14A_Z_HL(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
	}
	else if (id == 62711) {
		mass_and_dist_962_14A_Z_SL(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
	}
    else if (id == 66701) {
        mass_and_dist_966_14A_HL(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }
    else if (id == 66702) {
        mass_and_dist_966_14A_LOG(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }
    else if (id == 66700) {
        mass_and_dist_966_14A_STD(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }
    else if (id == 72701) {
        mass_and_dist_972_14A_HL(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }
	else if (id == 72703) {
        mass_and_dist_972_14A_SL(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }
    else if (id == 72700) {
        mass_and_dist_972_14A_STD(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }
	else if (id == 80705) {
        mass_and_dist_980_14A_BLK(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }
    else if (id == 80701) {
        mass_and_dist_980_14A_HL(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }
	else if (id == 80706) {
        mass_and_dist_980_14A_HVY(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }
	else if (id == 80702) {
        mass_and_dist_980_14A_LOG(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }
    else if (id == 80700) {
        mass_and_dist_980_14A_STD(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }
    else if (id == 82701) {
        mass_and_dist_982_14A_HL(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }	
    else if (id == 82702) {
        mass_and_dist_982_14A_LOG(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }
    else if (id == 82700) {
        mass_and_dist_982_14A_STD(tilt_force, lift_force, tilt_cyl_ext, arm_ang, BC_len, imu_x, imu_y, return_mass, return_dist);
    }
    else {
        *return_mass = NAN;
        *return_dist = NAN;
    }
}

void toa_tilt_sens_to_bucket_ang_by_id(unsigned long int id, double tilt_cyl_ext, double arm_ang, double BC_len,
                                       double hook_ang, double *return_tilt_sens_to_bucket_ang) {
    if (id == 50700) {
		tilt_sens_to_bucket_ang_950_14A_STD(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
	}
    else if (id == 50701) {
		tilt_sens_to_bucket_ang_950_14A_HL(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
	}
    else if (id == 50702) {
		tilt_sens_to_bucket_ang_950_14A_LOG(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
	}
    else if (id == 50708) {
		tilt_sens_to_bucket_ang_950_14A_Z_STD(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
	}
    else if (id == 50709) {
		tilt_sens_to_bucket_ang_950_14A_Z_HL(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
	}
    else if (id == 50710) {
		tilt_sens_to_bucket_ang_950_14A_Z_LOG(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
	}
    else if (id == 62700) {
		tilt_sens_to_bucket_ang_962_14A_STD(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
	}
    else if (id == 62701) {
		tilt_sens_to_bucket_ang_962_14A_HL(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
	}
    else if (id == 62702) {
		tilt_sens_to_bucket_ang_962_14A_LOG(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
	}
    else if (id == 62708) {
		tilt_sens_to_bucket_ang_962_14A_Z_STD(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
	}
    else if (id == 62709) {
		tilt_sens_to_bucket_ang_962_14A_Z_HL(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
	}
	else if (id == 62711) {
		tilt_sens_to_bucket_ang_962_14A_Z_SL(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
	}
	else if (id == 66701) {
        tilt_sens_to_bucket_ang_966_14A_HL(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }
    else if (id == 66702) {
        tilt_sens_to_bucket_ang_966_14A_LOG(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }
    else if (id == 66700) {
        tilt_sens_to_bucket_ang_966_14A_STD(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }
    else if (id == 72701) {
        tilt_sens_to_bucket_ang_972_14A_HL(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }
	else if (id == 72703) {
        tilt_sens_to_bucket_ang_972_14A_SL(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }
    else if (id == 72700) {
        tilt_sens_to_bucket_ang_972_14A_STD(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }
    else if (id == 80705) {
        tilt_sens_to_bucket_ang_980_14A_BLK(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }
    else if (id == 80701) {
        tilt_sens_to_bucket_ang_980_14A_HL(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }
	else if (id == 80706) {
        tilt_sens_to_bucket_ang_980_14A_HVY(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }
	else if (id == 80702) {
        tilt_sens_to_bucket_ang_980_14A_LOG(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }
    else if (id == 80700) {
        tilt_sens_to_bucket_ang_980_14A_STD(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }
    else if (id == 82701) {
        tilt_sens_to_bucket_ang_982_14A_HL(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }	
    else if (id == 82702) {
        tilt_sens_to_bucket_ang_982_14A_LOG(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }
    else if (id == 82700) {
        tilt_sens_to_bucket_ang_982_14A_STD(tilt_cyl_ext, arm_ang, BC_len, hook_ang, return_tilt_sens_to_bucket_ang);
    }
    else {
        *return_tilt_sens_to_bucket_ang = NAN;
    }
}
