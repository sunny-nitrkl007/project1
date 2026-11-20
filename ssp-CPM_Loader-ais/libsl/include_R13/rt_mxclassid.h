/* Copyright 1994-2002 The MathWorks, Inc.
 *
 * File    : rt_mxclassid.h
 * Abstract:
 *   Definition of enum mxClassID
 *
 */

/* $Revision: 1.3 $ */

#ifndef __rt_mxclassid_h__
#define __rt_mxclassid_h__

typedef enum {
	mxCELL_CLASS = 1,
	mxSTRUCT_CLASS,
	mxOBJECT_CLASS,
	mxCHAR_CLASS,
	mxRESERVED5_CLASS, /* keep enums correct (was used for sparse class) */
	mxDOUBLE_CLASS,
	mxSINGLE_CLASS,
	mxINT8_CLASS,
	mxUINT8_CLASS,
	mxINT16_CLASS,
	mxUINT16_CLASS,
	mxINT32_CLASS,
	mxUINT32_CLASS,
	mxINT64_CLASS,		/* place holder - future enhancements */
	mxUINT64_CLASS,		/* place holder - future enhancements */
	mxUNKNOWN_CLASS = -1
} mxClassID;

#endif /* __rt_mxclassid_h__ */

/* [EOF] rt_mxclass_id.h */
