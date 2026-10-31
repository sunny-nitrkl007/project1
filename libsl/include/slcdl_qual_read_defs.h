/******************************************************************************
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%
*** %% COPYRIGHT (C) 1997-2004 CATERPILLAR INC. ALL RIGHTS RESERVED.
*** %%     This work contains proprietary information which may constitute
*** %%     a trade secret and/or be confidential.  Copyright notice is
*** %%     precautionary only and does not imply publication.
*** %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
*** FILE:
***	slcdl_qual_read_defs.h
***
*** DESCRIPTION:
***	This is the definition include file for the simulink CDL qual read module.
***
***
******************************************************************************/
#ifndef SLCDL_QUAL_READ_DEFS_H_
#define SLCDL_QUAL_READ_DEFS_H_

#define SLCDL_QUAL_READ_MAX_POSSIBLE   0x0003
#define SLCDL_QUAL_READ_MIN_POSSIBLE   0x0004
#define SLCDL_QUAL_READ_NOMINAL        0x0005
#define SLCDL_QUAL_READ_SETPOINT       0x0006
#define SLCDL_QUAL_READ_CALIBRATION    0x0007
#define SLCDL_QUAL_READ_MAX_ACTUAL     0x0008
#define SLCDL_QUAL_READ_MIN_ACTUAL     0x0009
#define SLCDL_QUAL_READ_MIN_GRAPH      0x000A
#define SLCDL_QUAL_READ_MAX_GRAPH      0x000B

/*These are included for backwards compatibility.*/
#define QUAL_READ_MAX_POSSIBLE_VALUE   SLCDL_QUAL_READ_MAX_POSSIBLE
#define QUAL_READ_MIN_POSSIBLE_VALUE   SLCDL_QUAL_READ_MIN_POSSIBLE
#define QUAL_READ_NOMINAL_VALUE        SLCDL_QUAL_READ_NOMINAL
#define QUAL_READ_SETPOINT_VALUE       SLCDL_QUAL_READ_SETPOINT
#define QUAL_READ_CALIBRATION_VALUE    SLCDL_QUAL_READ_CALIBRATION
#define QUAL_READ_MAX_ACTUAL_VALUE     SLCDL_QUAL_READ_MAX_ACTUAL
#define QUAL_READ_MIN_ACTUAL_VALUE     SLCDL_QUAL_READ_MIN_ACTUAL

#endif /* SLCDL_QUAL_READ_DEFS_H_ */
