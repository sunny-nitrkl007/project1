/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 1994-1995 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***
*** DESCRIPTION :
*** BDT public defines and prototypes

*** LANGUAGE :
***    ANSI C
***
*** MACRO LIST:
***
*******************************************************************************/
#ifndef __PCS_BDT_PUBLIC_H__
#define __PCS_BDT_PUBLIC_H__



/*******************************************************************************
***
*** External function prototypes, data, & symbols
*** -- #Include's --
***
*******************************************************************************/

/*******************************************************************************
***
*** Constants defined for this file
*** -- #Define's --
***
*******************************************************************************/
/*******************************************************************************
***
*** Data types defined for this file
*** -- Struct's, Typedef's, Enum's --
***
*******************************************************************************/

/*******************************************************************************
***
*** File scope symbols defined for this file
*** -- Symbols --
***
*******************************************************************************/


/* These functions suppoet C820 and C830 Version 1 formats*/


unsigned_8 pcs_transmit_configuration_data_version_1(unsigned_32 data_index,			
   							 unsigned_32	size,
							 unsigned_8 write_data[],
							 unsigned_32* write_data_size);

unsigned_8 pcs_receive_configuration_data_version_1(unsigned_32 data_index, 
							unsigned_32 seq_no, 
							unsigned_32 size, 
							unsigned_8 read_data[], 
							unsigned_32 *read_data_size);

unsigned_32 pcs_transmit_configuration_data_size_version_1(unsigned_32 data_index ,
				 				   unsigned_8 access_mode,
								   unsigned_32 size);

unsigned_32 pcs_receive_configuration_data_size_version_1(unsigned_32 data_index ,
						          unsigned_8 access_mode,
						          unsigned_32 size);
unsigned_8 pcs_report_transmit_data_version_1(unsigned_32 data_index,			
							 	    unsigned_32	size,
							        unsigned_8 write_data[],
							        unsigned_32 * write_size);
							 
unsigned_32 pcs_report_data_size_version_1(unsigned_32 data_index,
						  		 unsigned_8 access_mode,
						         unsigned_32 size);	



/* These functions suppoet C820 and C830 Version 2 formats*/

unsigned_32 pcs_receive_configuration_data_size_version_2(unsigned_32 data_index,
						 		  unsigned_8 access_mode,
		  						  unsigned_32 size);

unsigned_8 pcs_receive_configuration_data_version_2(unsigned_32 data_index, unsigned_32 seq_no, unsigned_32 size,
                                                            unsigned_8 read_data[], unsigned_32 *read_data_size);

unsigned_32 pcs_transmit_configuration_data_size_version_2(unsigned_16 data_type, unsigned_32 data_index,
						 		   unsigned_8 access_mode,
		  						   unsigned_32 size);  

unsigned_8 pcs_transmit_configuration_data_version_2(unsigned_16 data_type,			
							 unsigned_32	size,
							 unsigned_8 write_data[],
							 unsigned_32 * write_data_size);

unsigned_32 pcs_report_data_size_version_2(unsigned_16 data_type, unsigned_32 data_index ,
				 				   unsigned_8 access_mode,
								   unsigned_32 size);

unsigned_8 pcs_report_transmit_data_version_2(unsigned_16 data_type,			
							 unsigned_32	size,
							 unsigned_8 write_data[],
							 unsigned_32 * write_data_size);

void pcs_bdt_receive_truck_list_info(void);
void pcs_bdt_send_truck_data(void);



#endif
