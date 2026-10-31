/******************************************************************************
*** FILE:
***	slcdl_pid_def.h
***
*** COPYRIGHT NOTICE:
***	Copyright 1997-2004.  Caterpillar Inc.  All Rights Reserved.
***	This work contains Caterpillar's proprietary information which
***	may constitute a trade secret and/or be confidential.  Copyright
***	notice is precautionary only and does not imply publication.
***
*** DESCRIPTION:
***	This is the definition include file for the simulink CDL qual read module***
******************************************************************************/
#ifndef SLCDL_PID_DEF_H_
#define SLCDL_PID_DEF_H_

#define SLCDL_PID_REQUEST_QUALIFIED               0xBF
/*
$BF	Request Qualified Data Parameter

	Used to request qualifier parameter data transmission from other 
	components on the data link. The requested information is qualified 
	parameter data for a standard parameter or sublisted parameter. See 
	'Read Request Parameters Help Document' for proper use.

	Parameter Data Length:		9 Bytes
	Data Type:			Binary
	Resolution:			Binary
	Valid Data Range:		$00 to $FF 
	Transmission Update Period:	As Needed
	Format:
		PID	Data
		$BF	n a a b b c c d d
		n - Byte count of data which follows (must be 8)
		a a - Qualifier Parameter ID
		b b - Qualifier Parameter Sublist ID
			(b b = $0000 if Qualifier Parameter is not sublisted)
		c c - Referenced Parameter ID (MSB = $00 for non pre-byte PIDs)
		d d - Sublist Identifier for reference parameter ID
			(d d  = $0000 if  Referenced Parameter is not sublisted)
*/

#define SLCDL_PID_PARAMETER_DATA_QUALIFIER        0xF842
/*
$F8 $42	Parameter Data Qualifier

	Used to read limit, boundary and qualified information related to data 
	PIDs. The type of related information is defined by this parameter. 
	The structure of the indicated parameter defines size, type and 
	scaling of the exchanged information. This will support non-prebyte 
	PIDs, prebyte PIDs, and PIDs with sublist identifiers.

	Parameter Data Length:		8-27 Bytes
	Data Type:			Binary
	Resolution:			Binary
	Valid Data Range:		$00 to $FF 
	Data Order:			Special - Order within Def.
	Transmission Update Period:	As Needed
	Format:
		PID	Data
		$F8 $42	n a a b b c c d . . . d
		n - Byte count of data which follows
		a a - Limit/Qualifier Type Identifier
			$0003 = Maximum Possible Value (Used for Calibrations)
			$0004 = Minimum Possible Value (Used for Calibrations)
			$0005 = Nominal Value
			$0006 = Setpoint Value
			$0007 = Calibration Value
			$0008 = Maximum Actual Value
			$0009 = Minimum Actual Value
		b b - Parameter ID (MSB = $00 if non-PreByte PID)
		c c - Sublist Identifier for specified parameter ID
			(c c = $0000 if Parameter is not sublisted)
		d - Limit/Qualifier Data (scaled and sized as defined by specified PID)
*/


#endif /* SLCDL_PID_DEF_H_ */
