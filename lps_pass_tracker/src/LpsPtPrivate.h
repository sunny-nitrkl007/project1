/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LpsPtPrivate.h
DESCRIPTION: Loader Payload System Pass Tracker private header file.
*******************************************************************************/
#ifndef __LPS_PT_PRIVATE_H__
#define __LPS_PT_PRIVATE_H__
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <math.h>
#include <string.h>
#include <LpsCommonTypeDef.h>
#include <LpsPtPublic.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
#define GET_ACCURACY(PAYLOAD_CALC_METHOD) ((PAYLOAD_CALC_METHOD & 0x0F00) >> 8)


typedef struct
{
    LpsPtOutputs_t lpsPtoutputs;

    boolean prev_unlatch_cmd;
    boolean disable_auto_tipoff_exit;

    /* The previous dig detected state so that we can look for new digs */
    boolean previous_dig_detected;

} LpsPtWrkTbl_t;

/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*LpsPtTruck*/
void pcs_truck_init(float initialWeight, unsigned_16 initialPassCount, boolean haveLastPass, float lastPassWeight, unsigned_8 lastPassAccuracy);
void pcs_truck_restore(float initialWeight, unsigned_16 initialPassCount, boolean haveLastPass, float lastPassWeight, unsigned_8 lastPassAccuracy);
void pcs_truck_clear(void);
void pcs_truck_keep_pass(void);
void pcs_truck_start_pass(float passWeight, unsigned_8 passAccuracy, boolean keepPass);
boolean pcs_truck_complete_pass(float passWeight, unsigned_8 passAccuracy);
boolean pcs_truck_recall_pass(void);
void pcs_truck_cancel_pass(void);
boolean pcs_truck_remove_last_pass();
void pcs_truck_update_pass(float passWeight, unsigned_8 passAccuracy);

void pcs_truck_display_pause_on_clear(void);
void pcs_truck_display_update(void);

boolean pcs_truck_is_pass_active(void);
boolean pcs_truck_is_keeping_pass(void);
boolean pcs_truck_has_recall_pass(void);
boolean pcs_truck_has_last_pass(void);
boolean pcs_truck_has_passes(void);

unsigned_16 pcs_truck_get_pass_count(void);
float pcs_truck_get_weight(void);
float pcs_truck_get_start_weight(void);
float pcs_truck_get_current_pass_weight(unsigned_8* accuracy);

unsigned_16 pcs_truck_display_get_pass_count(void);
float pcs_truck_display_get_weight(void);

// LpsPtBucket
void pcs_bucket_set_current_weight(unsigned_8 accuracy, float weight);
float pcs_bucket_get_current_weight(unsigned_8* accuracy);
void pcs_bucket_capture_start_weight(void);
float pcs_bucket_get_start_weight(unsigned_8* accuracy);
void pcs_bucket_capture_split_weight(void);
float pcs_bucket_get_split_weight(unsigned_8* accuracy);


/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/
extern LpsPtWrkTbl_t LpsPtWrkTbl;

#endif /* #ifndef __LPS_PT_PRIVATE_H__ */
