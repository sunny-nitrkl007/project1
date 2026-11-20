/******************************************************************************************************************
 Copyright 2018 Caterpillar Inc. All rights reserved.
-------------------------------------------------------------------------------------------------------------------
File name: scl_stat_db_tune.h

Description:Tune header for scl_stat_db
******************************************************************************************************************/
#ifndef SCL_STAT_DB_TUNE_H_
#define SCL_STAT_DB_TUNE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*--------------------------------------------------------------------------------------------------------------*/
/*          Select the proper Owner ECU Description Type(SCL_STAT_DB_OWNER_DESCRIPTION_TYPE)                    */
/*--------------------------------------------------------------------------------------------------------------*/
/*   ECU Description Type            ECU Description Type Description	     ECU Description Type Indication    */
/*--------------------------------------------------------------------------------------------------------------*/
/*             $01						CDL Component Identifier	            CID                             */
/*             $02						J1939 Component Identifier	            SPN                             */
/*             $04						Global Identifier	                    GID                             */
/*             $05						Name Code	                            Name Code                       */
/*--------------------------------------------------------------------------------------------------------------*/
#define SCL_STAT_DB_OWNER_DESCRIPTION_TYPE  0x04

/*Select the ID which describes the Owner ECU information and ID values relates to the Description type 
	that was selected in SCL_STAT_DB_OWNER_DESCRIPTION_TYPE macro.
	LL  -> means this Macro holds the 64-bit data (Don't consider LL as a data.This is just syntax to provide 64bit value)*/
#define SCL_STAT_DB_OWNER_DESCRIPTION_ID  0x00000000F1LL


#ifdef __cplusplus
}
#endif
#endif /* #ifndef SCL_STAT_DB_TUNE_H_ */
