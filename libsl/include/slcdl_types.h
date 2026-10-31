#ifndef SLCDL_TYPES_H_
#define SLCDL_TYPES_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains datatypes needed for the Simulink CDL blocks.

FILE NAME : slcdl_types.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>
#include <cdl2_struct.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
/* Transmit Parameter Information Entry Data with Status */
typedef struct {
   uint8_t len;
   uint8_t *pdata;
   uint8_t type;
   uint8_t *status;
} slcdl_gen_tx_status_pie_t;


/* Receive Parameter Information Entry Data without Status */
typedef struct {
   uint8_t  len;
   uint8_t  *pdata;
   uint8_t  type;
} slcdl_rx_pie_t;


/* Receive Parameter Information Entry Data with Status */
typedef struct {
   uint8_t  len;
   uint8_t  *pdata;
   uint8_t  type;
   uint8_t  *status;
} slcdl_rx_status_pie_t;


/* Transmit Parameter Information Entry for PID 0x80 - Device Identifier */
typedef struct {
   uint8_t  len;
   uint16_t *mid;
   uint16_t *servicetool_support_chng_level;
   uint16_t *application_type;
} slcdl_tx_pid80_pie_t;


typedef struct
{
   uint8_t len;
   uint8_t *pdata;
} slcdl_wr_pie_t;


/* Definitions needed for run-time addition/subtraction of CBS parameters */
/* Defines initialization state:
 *   SLCDL_CBS_INIT_OFF      - CBS not currently initialized/running.
 *   SLCDL_CBS_INIT_RUNNING  - CBS either initalizing or actively receiving data
 *   SLCDL_CBS_INIT_SHUTDOWN - CBS shutting down
 */
typedef enum {
  SLCDL_CBS_INIT_OFF,
  SLCDL_CBS_INIT_RUNNING,
  SLCDL_CBS_INIT_SHUTDOWN
} slcdl_cbs_init_state_t;


typedef enum {
  SLCDL_CBS_RUNTIME_INIT,
  SLCDL_CBS_RUNTIME_REINIT
} slcdl_cbs_init_type_t;


typedef struct {
  /* Used to indicate that a CBS ECM/Parameter has been added or removed
   * requiring re-initialization of the CBS System.
   */
  bool_least_t select_change;

  /* The startup initialization delay.  This is the time (in loops) which
   * must pass before the CBS System is initialized for the first time.
   * This delay is required to prevent the CBS System from requesting paramters
   * from another ECM prior to that ECM being fully initialized.
   */
  uint32_t init_delay_timer;

  /* Defines the initialization state of the CBS System */
  slcdl_cbs_init_state_t init_state;
} slcdl_cbs_runtime_init_work_t;


typedef struct {
  /* Used to set the initial value of the workspace time */
  uint32_t init_delay;

  /* CDL2 structure containing the CBS System overall configuraiton */
  const cdl2_cbs_system_cfg_t *system_config;

  /* CDL2 structure containing the list of all possible ECMs
   * from which parameters may be requested from.
   */
  const cdl2_cbs_ecm_cfg_t *ecm_config;

  /* CDL2 structure containing the list of all possible parameters
   * which may be requested.
   */
  const cdl2_cbs_parm_cfg_t *param_config;

  /* Determines if multiple run-time re-initializations are required
   * or only a single run-time initialization is required.
   */
  slcdl_cbs_init_type_t init_type;

  /* Start Run-Time Re-Initialization Related Elements
   *   These only need to be populated with valid addresses when the init_type
   *   is: SLCDL_CBS_RUNTIME_REINIT.  Thus, if run-time re-initialization is not
   *   required, then no ram need be allocated for these parameters, and null
   *   values may be set.
   */
  /* Array containing the enable count for each ECM.
   *   - The enable count indicates the number of parameters which are
   *     currently enabled which originate from the ECM located at this index.
   *   - The index  corresponds with the index  in the structure element:
   *     slcdl_cbs_ecm_config.table[].
   *   - When the value is 0, this means that no parameters are currently being
   *     received from that ECM, so the ECM may be omitted from the configuration
   *     used for re-initialization of CBS.
   */
  uint16_t *rx_ecm_enabled;

  /* Array containing the enable count for each parameter.
   *   - The enable count indicates the number of enabled block instances which
   *     use this parameter.
   *   - The index  corresponds with the index  in the structure element:
   *     slcdl_cbs_param_config.table[].
   *   - When the value is 0, this means that no blocks are enabled which need this
   *     parameter, so the parameter may be omitted from the configuration
   *     used for re-initialization of CBS.
   */
  uint8_t *rx_param_enabled;

  /* CDL2 structure containing the list of ECMs from which parameters
   * are being requested.
   */
  cdl2_cbs_ecm_cfg_t *ecm_ram_config;

  /* CDL2 structure containing the list of  parameters which are
   * being requested.
   */
  cdl2_cbs_parm_cfg_t *param_ram_config;
  /* End Run-Time Re-Initialization Related Elements */
} slcdl_cbs_runtime_init_cfg_t;


/*---------------------------------------------------------------------------*/
/*----             CAT Data Link Qualifed Read Definitions               ----*/

/*---------------------------------------------------------------------------*/
/*----              CAT Data Link Qualifed Read Structures               ----*/

/*CAT Data Link Qualified Read Parameter Information Entry Structure
//     This structure holds the information needed for one qualified 
//     read parameter.
*/
typedef struct
{
     /*Parameter Identifier
     //     This is the PID which specifies the data that
     //     is described by this entry.
     */
     uint32_t  pid;

     /*Type Identifier
     //     This is the identifier which indicates which attribute
     //     of the above PID is described by this entry.
     //     Allowed values are as follows:
     //          SLCDL_QUAL_READ_MAX_POSSIBLE
     //          SLCDL_QUAL_READ_MIN_POSSIBLE
     //          SLCDL_QUAL_READ_NOMINAL
     //          SLCDL_QUAL_READ_SETPOINT
     //          SLCDL_QUAL_READ_CALIBRATION
     //          SLCDL_QUAL_READ_MAX_ACTUAL
     //          SLCDL_QUAL_READ_MIN_ACTUAL
     //     NOTE:  Other values may be allowed if they are
     //            defined in the CAT Data Link Document.
     //            See that document for the latest information.
     */
     uint16_t  type; 

     /*Data Length
     //     This is the length of the qualified read data.
     */
     uint8_t   data_len;

     /*Data Direction
     //     This is the data direction for this parameter.
     //     Allowed values are as follows:
     //          CDL2_DATA_REV = reverse order (least significant byte first)
     //          CDL2_DATA_FWD = forward order (most  significant byte first)
     */
     uint8_t   data_dir;

     /*Data Pointer
     //     This is a pointer to the data for this parameter.
     */
     uint8_t  *data_ptr;
}  slcdl_qual_data_read_pie_t;

/*CAT Data Link Qualified Read Parameter Information Array Element Structure
//     This structure holds pointers to all of the qual_data_read_pie_t
//     structures initialized by this ECM.  The structure also contains
//     flags so that the qualified read module knows what elements
//     have been initialized and what elements have not been intialized.
*/
typedef struct 
{
     uint8_t                   initialized;   /*Initialized Flag */
     slcdl_qual_data_read_pie_t  *pie_ptr;       /*Pointer to Entry */
} slcdl_qual_data_array_t;

/*---------------------------------------------------------------------------*/
/*----               CAT Data Link Qualifed Read Variables               ----*/

/*CAT Data Link Qualified Read Parameter Entry Array
//    This array holds pointers to all of the qualified read
//    parameters initialized by this ECM.
//
//    IMPORTANT NOTE:
//         This should be defined by the application.
//         This is required so that the application
//         may customize the library.
*/
extern slcdl_qual_data_array_t  slcdl_qual_read_array[];

/*CAT Data Link Qualified Read Maximum Number Of Entries
//     This variable contains the maximum number of qualified
//     reads that will ever be supported by this ECM.
//
//    IMPORTANT NOTE:
//         This should be defined by the application.
//         This is required so that the application
//         may customize the library.
*/
extern const uint16_t        slcdl_qual_read_max_entries;


/*---------------------------------------------------------------------------*/
/*----                CAT Data Link Qualifed Read Prototypes             ----*/

void
slcdl_qual_read_init(void);
/*BEFORE: This function initializes the qualified read module.
//AFTER:  The qualified read module is initialized.  The list
//        of qualified reads supported by this module is cleared.
*/
cdl2_rx_hdlr_t slcdl_qual_read_BF_receive;
/*BEFORE: This function is a custom handler for the qualified read request.
//        It will be called by the core CDL2 receive routines.
//AFTER:  Process the qualified read request.
//
//        Note that only the qualified data read request is supported by this
//        handler.  The qualified access security level request is not
//        supported(although it may be added to this function in the future).
//        
//        Returns zero if the receive was successful.
//        Returns non-zero if the receive was not successful.
//
//        NOTE:
//             This function will generate compiler warnings because much
//             of the data that is passed to this function is not used.
//             Those unused parameters are necessary because they are passed
//             by the CDL2 subsystem.
*/

int16_t
slcdl_qual_data_read_proc(uint8_t  *buff_ptr,
                          uint8_t   sid
                         );
/*BEFORE: This function is a custom handler for the qualified data read
//        request.  
//        It may only be called by the slcdl_qual_read_BF_receive().
//AFTER:  Process the qualified data read request.
//
//        Searches the qualified data request table, and generates
//        a response if a match is found.
//
//        Returns zero if the request was successful.
//        Returns non-zero if the request was not successful.
*/
/*****************************************************************************/


/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SLCDL_TYPES_H_ */



