#ifndef SLCSL_TYPES_H_
#define SLCSL_TYPES_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains datatypes needed for the Simulink CDL blocks.

FILE NAME : slcdl_defs.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
/* Define the maximum character supported by the Software Group Description
 *   CDL PID 0xF84A
 */
#define SLCSL_CDL_SW_GROUP_DESCR_MAX_CHARS       26

/* Structure containing information which specifies the identity of an
 * application on the Cat Data Link.
 */
typedef struct {
	uint_least16_t mid;
	uint_least16_t servicetool_support_chng_level;
	uint_least16_t application_type;
	char software_group_description[SLCSL_CDL_SW_GROUP_DESCR_MAX_CHARS];
} slcsl_cdl_application_identity_t;

/* Define the maximum character supported by the Software Group Description
 *   J1939 PPGN 0xF019
 */
#define SLCSL_J1939_SW_GROUP_DESCR_MAX_CHARS     100

/* Structure containing information which specifies the identity of an
 * application on the J1939 Data Link.
 */
typedef struct {
	uint_least16_t mid;
	uint_least16_t servicetool_support_chng_level;
	uint_least16_t application_type;
	char software_group_description[SLCSL_J1939_SW_GROUP_DESCR_MAX_CHARS];
} slcsl_j1939_application_identity_t;

/* Structure containing Software Group Release Date as string w/length */
#define SLCSL_SW_GROUP_RELEASEDATE_MAX_CHARS  7
typedef struct {
	uint_least8_t length;
	char string[SLCSL_SW_GROUP_RELEASEDATE_MAX_CHARS];
} slcsl_software_group_release_date_t;

/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SLCSL_TYPES_H_ */
