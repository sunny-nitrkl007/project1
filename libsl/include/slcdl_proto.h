#ifndef SLCDL_PROTO_H_
#define SLCDL_PROTO_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains prototypes needed for the Simulink CDL blocks.

FILE NAME : slcdl_proto.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <cdl2_struct.h>
#include <slcdl_types.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/

/******************************************************************************
** -- Function Prototypes --
******************************************************************************/


/* Standard Handlers */
Cdl_wr_hdlr_t cdl_wr_f_hdlr;
Cdl_wr_hdlr_t cdl_wr_fr_hdlr;
cdl2_tx_hdlr_t slcdl_tx_f_hdlr;
cdl2_tx_hdlr_t slcdl_tx_fr_hdlr;

cdl2_tx_hdlr_t slcdl_tx_status_f_hdlr;
cdl2_tx_hdlr_t slcdl_tx_status_fr_hdlr;

cdl2_tx_hdlr_t slcdl_tx_pid80_f_hdlr;
cdl2_tx_hdlr_t slcdl_tx_pid80_fr_hdlr;

Cdl_wr_hdlr_t slcdl_wr_f_hdlr;
Cdl_wr_hdlr_t slcdl_wr_fr_hdlr;

/* CBS Related Functions */
/* CAT Data Link CBS Sleeping MID Connect */
void slcdl_cbs_sleeping_connect_func(uint8_t mid, uint8_t status);

void slcdl_cbs_runtime_add_param_instance(
	slcdl_cbs_runtime_init_cfg_t *config,
	uint16_t param_idx,
	uint16_t ecm_idx);

void slcdl_cbs_runtime_remove_param_instance(
	slcdl_cbs_runtime_init_cfg_t *config,
	uint16_t param_idx,
	uint16_t ecm_idx);

void slcdl_cbs_set_select_change(slcdl_cbs_runtime_init_work_t *work,
		bool_least_t status);

slcdl_cbs_init_state_t slcdl_cbs_get_init_status(
	slcdl_cbs_runtime_init_work_t *work);

void slcdl_cbs_init(slcdl_cbs_runtime_init_work_t *work,
		slcdl_cbs_runtime_init_cfg_t *config);

void slcdl_cbs_runtime_init(slcdl_cbs_runtime_init_work_t *work,
		slcdl_cbs_runtime_init_cfg_t *config);


/* Diangostic Functions */
cdl2_deactivate_system_event_t slcdl_deactivate_diagnostic;

cdl2_activate_system_event_t slcdl_activate_diagnostic;

void slcdl_update_ecm_diag_status(uint16_t cid,
                                  uint8_t  fmi,
                                  uint8_t  status);

/* CDL Qualified read Functions */
uint8_t
slcdl_qual_read_add_entry(slcdl_qual_data_read_pie_t  *passed_pie);
/*BEFORE: This function adds a qualified data read entry.  After this
//        routine is called, this ECM will respond to qualified
//        data read requests for this parameter/type combination.
//
//        The data pointed to by passed_pie should be a properly
//        initialized structure of type slcdl_qual_data_read_pie_t.
//
//        passed_pie->pid
//             This is the PID which specifies the data that
//             is described by this entry.
//        passed_pie->type
//             This is the identifier which indicates which attribute
//             of the above PID is described by this entry.
//             Allowed values are as follows:
//                  SLCDL_QUAL_READ_MAX_POSSIBLE
//                  SLCDL_QUAL_READ_MIN_POSSIBLE
//                  SLCDL_QUAL_READ_NOMINAL
//                  SLCDL_QUAL_READ_SETPOINT
//                  SLCDL_QUAL_READ_CALIBRATION
//                  SLCDL_QUAL_READ_MAX_ACTUAL
//                  SLCDL_QUAL_READ_MIN_ACTUAL
//             NOTE:  Other values may be allowed if they are
//                    defined in the CAT Data Link Document.
//                    See that document for the latest information.
//        passed_pie->data_len
//             This is the length of the qualified read data.
//        passed_pie->data_dir
//             This is the data direction for this parameter.
//             Allowed values are as follows:
//                  CDL2_DATA_REV = reverse order (least significant byte first)
//                  CDL2_DATA_FWD = forward order (most  significant byte first)
//        passed_pie->data_ptr
//             This is an uint8_t pointer to the data for this parameter.
//
//        NOTE:  Extra calls to this routine with the same information
//               will not result in extra entires being generated.
//               Special provisions have been made to insure that critical
//               sections are guarded from tasking interrupts.
//AFTER:  Adds support for the indicated parameter/type combination
//        to the qualified read protocol.
//        
//        If there is space left, this entry is added to the first
//        availiable slot.
//        
//        Returns zero if the addition was successful.
//        Returns non-zero if the addition was not successful.
*/
/*****************************************************************************/

uint8_t
slcdl_qual_read_remove_entry(const slcdl_qual_data_read_pie_t  *passed_pie);
/*BEFORE: This function removes a qualified data read entry.  After this
//        routine is called, this ECM will not respond to qualified
//        data read requests for this parameter/type combination.
//
//        The data pointed to by passed_pie should be a properly
//        initialized structure of type slcdl_qual_data_read_pie_t and
//		  previously added with slcdl_qual_read_add_entry().
//
//        passed_pie->pid
//             This is the PID which specifies the data that
//             is described by this entry.
//        passed_pie->type
//             This is the identifier which indicates which attribute
//             of the above PID is described by this entry.
//             Allowed values are as follows:
//                  SLCDL_QUAL_READ_MAX_POSSIBLE
//                  SLCDL_QUAL_READ_MIN_POSSIBLE
//                  SLCDL_QUAL_READ_NOMINAL
//                  SLCDL_QUAL_READ_SETPOINT
//                  SLCDL_QUAL_READ_CALIBRATION
//                  SLCDL_QUAL_READ_MAX_ACTUAL
//                  SLCDL_QUAL_READ_MIN_ACTUAL
//             NOTE:  Other values may be allowed if they are
//                    defined in the CAT Data Link Document.
//                    See that document for the latest information.
//
//AFTER:  Removes support for the indicated parameter/type combination
//        to the qualified read protocol.
//        
//        If an entry is found that matches the passed_pie info, the entry is
//		  is set to initialized = FALSE to free the space
//        
//        Returns TRUE if the removal was successful.
//        Returns fALSE if the removal was not successful.
*/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/

#endif /* SLCDL_PROTO_H_ */
