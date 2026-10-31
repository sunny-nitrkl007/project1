/*******************************************************************************
** COPYRIGHT (C) 2004 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar?s proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
**
** FILE NAME:
** product_id_tables.h
**
*******************************************************************************/
#ifndef APP_PRODUCT_ID_H_
#define APP_PRODUCT_ID_H_

#ifndef PRODUCT_ID_LIB_H_
#include <product_id_lib.h>
#endif

extern ProductIDObj_t product_id_obj;

extern int_16 app_product_id_tx_hdlr(void* pie, unsigned_8 *dest_data);
extern void app_product_id_init(void);

#endif /* APP_PRODUCT_ID_H_ */
