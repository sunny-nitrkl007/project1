#ifndef SL_SCLJ1939_PROTO_H_
#define SL_SCLJ1939_PROTO_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. 2007 ALL RIGHTS RESERVED
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains externs for the blocks defining the J1939 Cat PPGN
message handlers.  These are static handlers that don't change based on model
configuration.

FILE NAME : sl_SclJ1939_proto.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <scl_j1939.h>
#include <sl_SclJ1939_types.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/
/* J1939 PPGN Handler definitions */
extern SCL_J1939_CAT_PPGN_ID_HDLR_t sl_SclJ1939_PPGN_HDLR_Device_ID;
extern SCL_J1939_CAT_PPGN_ID_HDLR_t sl_SclJ1939_PPGN_HDLR_Sw_Grp_Info;
extern SCL_J1939_CAT_PPGN_ID_HDLR_t sl_SclJ1939_PPGN_HDLR_ECM_Basic_Info;
extern SCL_J1939_CAT_PPGN_ID_HDLR_t sl_SclJ1939_PPGN_HDLR_SHM;
extern SCL_J1939_CAT_PPGN_ID_HDLR_t sl_SclJ1939_PPGN_HDLR_KHM;

/* Memory Access Override Handler prototypes */
scl_j1939_ma_ovr_wr_hdlr_t slSclJ1939_MaOvWrF_Hdlr;
scl_j1939_ma_ovr_wr_hdlr_t slSclJ1939_MaOvWrFr_Hdlr;
scl_j1939_ma_ovr_rd_hdlr_t slSclJ1939_MaOvTxF_Hdlr;
scl_j1939_ma_ovr_rd_hdlr_t slSclJ1939_MaOvTxFr_Hdlr;

scl_j1939_ma_ovr_chk_cond_t slSclJ1939_MaOvChk;

extern scl_j1939_param_data_t slSclJ1939_TxMsgSpnHdlr(void *);
extern scl_j1939_param_data_t slSclJ1939_TxMsgSpnHdlr_Sat(void *); 
extern void slSclJ1939_TxMsgSpnInit(scl_j1939_link_t,
                                    uint8_t,
                                    const sl_SclJ1939_TxSpnConfig_t *);
extern void slSclJ1939_RxMsgSpnHdlr(void *, scl_j1939_param_data_t);
extern void slSclJ1939_RxMsgSpnHdlr_Raw(void *, scl_j1939_param_data_t);
extern void slSclJ1939_RxMsgSpnInit(scl_j1939_link_t,
                                    uint8_t,
                                    const sl_SclJ1939_RxSpnConfig_t *);

extern void slSclJ1939_RxMsgSpnInit_FullName(scl_j1939_link_t,
                                    uint8_t,
                                    const sl_SclJ1939_RxSpnConfig_t_FullName *);
extern void slSclJ1939_RxMsgSpnHdlr_ctxtfunc(void *, scl_j1939_param_data_t);
extern void slSclJ1939_RxMsgSpnHdlr_ctxtfunc_Raw(void *, scl_j1939_param_data_t);
extern void slSclJ1939_RxMsgSpnHdlr_ctxtfunc_WOC(void *, scl_j1939_param_data_t);
extern void slSclJ1939_RxMsgSpnHdlr_ctxtfunc_WOC_Raw(void *, scl_j1939_param_data_t);
/******************************************************************************
** -- Function Prototypes --
******************************************************************************/

/******************************************************************************
** -- Data Declarations --
******************************************************************************/


#endif /* SLCSL_PROTO_H_ */
