/***********************************************************************
***
*** FILE:
***     src_main/ecm_information.c
***
*** COPYRIGHT NOTICE:
***     Copyright 2014  Caterpillar Inc.  All Rights Reserved.
***     This work contains Caterpillar's proprietary information which
***     may constitute a trade secret and/or be confidential.  Copyright
***     notice is precautionary only and does not imply publication.
***
*** DESCRIPTION:
***     This file defines information about the ECM.
***
***********************************************************************/
#include <ecminfolib_public.h>

/* Identification Information
**     This variable contains various identification information.
*/
const char identification_information[] =
    "Test application for Printers [05JUN2014] People: BNC";

/* Software Group Part Number ECM Information
**     This macro is used to define the required information for the
**     software group part number.
**
**     Use of this macro makes the ECM Information Module retrieve
**     the software part number from the application token on startup.
**
**     This is the software part number that is available to the
**     dealers through Morton parts and can be flash programmed into
**     the control via the service tool.
**     NOTE:  This is for status only. It is not used for the
**            flashing protocol.
**
**     The information must be defined by the application so the
**     library module will not have to hard-code the data.
**
**     This macro defines the information areas, and initializes them
**     to the correct value.
*/
ECMINFO_SOFTWARE_GROUP_PN("1234567-01");

/* Software Group Date Code ECM Information
**     This macro is used to define the required information for the
**     software group part number.
**
**     The argument should be an constant character array.
**     It should be the desired software group date code for this ECM.
**     The data in the array should be in one of the following formats:
**          1) Exactly 5 ASCII characters representing the date.
**             Example:
**                  MAR99
**                       Could mean March 1999, March 2099,
**                       March 9999, or . . .
**          2) Exactly 7 ASCII characters representing the date.
**             Example:
**                  MAR2000
**                       Could mean March 2000, March 12000,
**                       March 92000, or . . .
**
**     The information must be defined by the application so the
**     library module will not have to hard-code the data.
**
**     This macro defines the information areas, and initializes them
**     to the correct value.
*/
ECMINFO_SOFTWARE_GROUP_DATE("TEST");
                           /*xxxxxxx<-------Must be 7 characters long */

/* Copyright Information
**     This variable contains the copyright information.
**     It will be included in ROM, so it will always be in the
**     software.
*/
const char copyright[] =
    "COPYRIGHT (C) 2014 CATERPILLAR INC.  ALL RIGHTS RESERVED."
    " This work contains proprietary information which may"
    " constitute a trade secret and/or be confidential.";
