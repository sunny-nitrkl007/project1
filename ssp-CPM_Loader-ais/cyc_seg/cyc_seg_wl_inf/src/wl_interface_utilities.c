/*******************************************************************************
***
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*** %%                                                                        %%
*** %%  COPYRIGHT (C) 1994-2017 CATERPILLAR INC.   ALL RIGHTS RESERVED.       %%
*** %%      This work contains proprietary information which may              %%
*** %%      constitute a trade secret and/or be confidential.                 %%
*** %%                                                                        %%
*** %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
***
***
*** DESCRIPTION :
***	 WL_00_interface_utilities.c
***
*** LANGUAGE :
***    ANSI C
***
*** 
***
*******************************************************************************/

/*************Header Files**********************************************************/



#include <wl_interface_utilities.h >

#include <LIBINFO_WL_if.h>

#include <gps_public.h >

#include <oel_malloc.h>


/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

void Refresh_mdl_output(void);



/********************************************************************************/
/* GPS UIDs */
const pd_uid_info CS_SEGMENT_ID_UID =
    {
        CS_SEGMENT_ID_UID_UID,         
        CS_SEGMENT_ID_UID_ID,          
        CS_SEGMENT_ID_UID_SIZE,        
        CS_SEGMENT_ID_UID_DATATYPE,    
        CS_SEGMENT_ID_UID_COLOR,
        CS_SEGMENT_ID_UID_DATASOURCE	
    };

const pd_uid_info CS_SEGMENT_START_TIME_UTC_UID =
    {
	    CS_SEGMENT_START_TIME_UTC_UID_UID,          
        CS_SEGMENT_START_TIME_UTC_UID_ID,                  
        CS_SEGMENT_START_TIME_UTC_UID_SIZE,                  
        CS_SEGMENT_START_TIME_UTC_UID_DATATYPE,              
        CS_SEGMENT_START_TIME_UTC_UID_COLOR,                 
        CS_SEGMENT_START_TIME_UTC_UID_DATASOURCE            
	};
    
const pd_uid_info CS_SEGMENT_DURATION_UID = 
    {
	    CS_SEGMENT_DURATION_UID_UID,
        CS_SEGMENT_DURATION_UID_ID,
        CS_SEGMENT_DURATION_UID_SIZE,
        CS_SEGMENT_DURATION_UID_DATATYPE,
        CS_SEGMENT_DURATION_UID_COLOR,
        CS_SEGMENT_DURATION_UID_DATASOURCE
	};
	
const pd_uid_info CS_SEGMENT_FUEL_CONSUMED_UID =
    {
	    CS_SEGMENT_FUEL_CONSUMED_UID_UID,
        CS_SEGMENT_FUEL_CONSUMED_UID_ID,
        CS_SEGMENT_FUEL_CONSUMED_UID_SIZE,
        CS_SEGMENT_FUEL_CONSUMED_UID_DATATYPE,
        CS_SEGMENT_FUEL_CONSUMED_UID_COLOR,
        CS_SEGMENT_FUEL_CONSUMED_UID_DATASOURCE
	};
	
const pd_uid_info CS_SEGMENT_DISTANCE_TRAVELLED_UID =
    {
	    CS_SEGMENT_DISTANCE_TRAVELLED_UID_UID,
        CS_SEGMENT_DISTANCE_TRAVELLED_UID_ID,
        CS_SEGMENT_DISTANCE_TRAVELLED_UID_SIZE,
        CS_SEGMENT_DISTANCE_TRAVELLED_UID_DATATYPE,
        CS_SEGMENT_DISTANCE_TRAVELLED_UID_COLOR,
        CS_SEGMENT_DISTANCE_TRAVELLED_UID_DATASOURCE
	};
	
const pd_uid_info CS_SEGMENT_MACHINE_IDLE_DURATION_UID =
    {
	    CS_SEGMENT_MACHINE_IDLE_DURATION_UID_UID,
        CS_SEGMENT_MACHINE_IDLE_DURATION_UID_ID,
        CS_SEGMENT_MACHINE_IDLE_DURATION_UID_SIZE,
        CS_SEGMENT_MACHINE_IDLE_DURATION_UID_DATATYPE,
        CS_SEGMENT_MACHINE_IDLE_DURATION_UID_COLOR,
        CS_SEGMENT_MACHINE_IDLE_DURATION_UID_DATASOURCE  
	};
    
const pd_uid_info CS_SEGMENT_PAYLOAD_WEIGHT_UID =
    {
	    CS_SEGMENT_PAYLOAD_WEIGHT_UID_UID,                   
        CS_SEGMENT_PAYLOAD_WEIGHT_UID_ID,                    
        CS_SEGMENT_PAYLOAD_WEIGHT_UID_SIZE,                  
        CS_SEGMENT_PAYLOAD_WEIGHT_UID_DATATYPE,              
        CS_SEGMENT_PAYLOAD_WEIGHT_UID_COLOR,                 
        CS_SEGMENT_PAYLOAD_WEIGHT_UID_DATASOURCE            
	};
    
const pd_uid_info CS_SEGMENT_PAYLOAD_CALC_METHOD_UID =
    {
	    CS_SEGMENT_PAYLOAD_CALC_METHOD_UID_UID,
        CS_SEGMENT_PAYLOAD_CALC_METHOD_UID_ID,
        CS_SEGMENT_PAYLOAD_CALC_METHOD_UID_SIZE,
        CS_SEGMENT_PAYLOAD_CALC_METHOD_UID_DATATYPE,
        CS_SEGMENT_PAYLOAD_CALC_METHOD_UID_COLOR,  
        CS_SEGMENT_PAYLOAD_CALC_METHOD_UID_DATASOURCE
	};	
	
/*******************************************************************************/
/*******Initialization Function*************************************************/
/*******************************************************************************/
/*
***  FUNTION:INITIALIZE FUNCTION
***
**** DESCRIPTION :
***	 
*** CALLED BY
*** 
***
*** 
***
*******************************************************************************/

void cs_interface_init(unsigned_8 buffer_size_pd_records)
{
	PD_buffer_size = buffer_size_pd_records;
	cs_get_shutdown_override_ptr 				 = cs_get_shutdown_override;

	/* Register CS keyswitch override for controlled shutdown of Implement */
	register_pd_shutdown_override(cs_get_shutdown_override_ptr);
	     
	model_outputs_buffer = oel_malloc(PD_buffer_size * sizeof(MODEL_OUTPUTS));
    
	model_outputs_buffer_address = (unsigned_32)&model_outputs_buffer;
	
	if(model_outputs_buffer != NULL)
	{
		/*Allocate Memory for Buffer*/
		memset( model_outputs_buffer,0x00,(PD_buffer_size * sizeof(MODEL_OUTPUTS))); 
	}

    /*segment - Function pointers for required UID's*/
     cs_get_segment_id_ptr                       = cs_get_segment_id;
     cs_get_segment_time_stamp_ptr               = cs_get_segment_time_stamp;
     cs_get_segment_duration_ptr                 = cs_get_segment_duration;
     cs_get_segment_fuel_consumed_ptr            = cs_get_segment_fuel_consumed;
     cs_get_segment_distance_travelled_ptr       = cs_get_segment_distance_travelled; 
    /*segment - Functional pointers for Optinal UID's*/
     cs_get_segment_machine_idle_duration_ptr    = cs_get_segment_machine_idle_duration;
     cs_get_segment_payload_wt_ptr               = cs_get_segment_payload_wt;
     cs_get_segment_payload_calc_method_ptr      = cs_get_segment_payload_calc_method;

    /*segment_block Registering Required and Optional UID's*/
    CS_SEGMENT_ID_UID_flag                     = register_to_provide_block_info(CS_SEGMENT_ID_UID,                   PROD_BLOCK_TYPE_SEGMENT,  cs_get_segment_id_ptr);
    CS_SEGMENT_START_TIME_UTC_UID_flag         = register_to_provide_block_info(CS_SEGMENT_START_TIME_UTC_UID,       PROD_BLOCK_TYPE_SEGMENT,  cs_get_segment_time_stamp_ptr);
    CS_SEGMENT_DURATION_UID_flag               = register_to_provide_block_info(CS_SEGMENT_DURATION_UID,             PROD_BLOCK_TYPE_SEGMENT,  cs_get_segment_duration_ptr);
    CS_SEGMENT_FUEL_CONSUMED_UID_flag          = register_to_provide_block_info(CS_SEGMENT_FUEL_CONSUMED_UID,        PROD_BLOCK_TYPE_SEGMENT,  cs_get_segment_fuel_consumed_ptr);
    CS_SEGMENT_DISTANCE_TRAVELLED_UID_flag     = register_to_provide_block_info(CS_SEGMENT_DISTANCE_TRAVELLED_UID,   PROD_BLOCK_TYPE_SEGMENT,  cs_get_segment_distance_travelled_ptr);
    /*Optinal*/
    CS_SEGMENT_MACHINE_IDLE_DURATION_flag      = register_to_provide_block_info(CS_SEGMENT_MACHINE_IDLE_DURATION_UID,PROD_BLOCK_TYPE_SEGMENT,  cs_get_segment_machine_idle_duration_ptr);
    CS_SEGMENT_PAYLOAD_WEIGHT_flag             = register_to_provide_block_info(CS_SEGMENT_PAYLOAD_WEIGHT_UID,       PROD_BLOCK_TYPE_SEGMENT,  cs_get_segment_payload_wt_ptr);
    CS_SEGMENT_PAYLOAD_CALCULATION_METHOD_flag = register_to_provide_block_info(CS_SEGMENT_PAYLOAD_CALC_METHOD_UID,  PROD_BLOCK_TYPE_SEGMENT,  cs_get_segment_payload_calc_method_ptr);

    /*Check if all UID's are Registered and make seg_registration_flag is succes */
    if(((CS_SEGMENT_ID_UID_flag == RET_SUCCESS) || (CS_SEGMENT_ID_UID_flag == RET_DUPLICATE_BLOCK)) &&
       ((CS_SEGMENT_START_TIME_UTC_UID_flag == RET_SUCCESS) || (CS_SEGMENT_START_TIME_UTC_UID_flag == RET_DUPLICATE_BLOCK)) &&
       ((CS_SEGMENT_DURATION_UID_flag == RET_SUCCESS) || (CS_SEGMENT_DURATION_UID_flag == RET_DUPLICATE_BLOCK)) &&
       ((CS_SEGMENT_FUEL_CONSUMED_UID_flag == RET_SUCCESS ) || (CS_SEGMENT_FUEL_CONSUMED_UID_flag == RET_DUPLICATE_BLOCK)) &&
       ((CS_SEGMENT_DISTANCE_TRAVELLED_UID_flag == RET_SUCCESS) || (CS_SEGMENT_DISTANCE_TRAVELLED_UID_flag == RET_DUPLICATE_BLOCK)) && 
       ((CS_SEGMENT_MACHINE_IDLE_DURATION_flag == RET_SUCCESS) || (CS_SEGMENT_MACHINE_IDLE_DURATION_flag == RET_DUPLICATE_BLOCK)) &&
       ((CS_SEGMENT_PAYLOAD_WEIGHT_flag == RET_SUCCESS) || (CS_SEGMENT_PAYLOAD_WEIGHT_flag == RET_DUPLICATE_BLOCK)) &&
       ((CS_SEGMENT_PAYLOAD_CALCULATION_METHOD_flag == RET_SUCCESS) || (CS_SEGMENT_PAYLOAD_CALCULATION_METHOD_flag == RET_DUPLICATE_BLOCK)) &&
       (model_outputs_buffer != NULL))
    {
        seg_registration_done=TRUE;
    }
    else
    {
        seg_registration_done=FALSE;
    }
}

/*******************************************************************************/
/*
***  FUNTION: UPDATE FUNCTION
***
**** DESCRIPTION :
***	 
*** CALLED BY
*** 
***
*** 
***
*******************************************************************************/
void Refresh_mdl_output(void)
{
    /*copy all the outputs from model to working structure*/
    model_outputs_work.segment_record_commit_seg_record       =  commit_segment_record;
    model_outputs_work.segment_record_identifier              =  segment_record_id;
    model_outputs_work.segment_record_start_sim_time          =  segment_rec_start_simTime;
    model_outputs_work.segment_record_duration                =  segment_rec_duration;
    model_outputs_work.segment_record_distance_travelled      =  segment_rec_distance;
    model_outputs_work.segment_record_start_real_time         =  segment_rec_start_real_time;
    model_outputs_work.segment_record_fuel_consumed           =  segment_rec_fuel_used;
    model_outputs_work.segment_record_machine_idle_time       =  segment_rec_idle_time;
    model_outputs_work.segment_record_service_hour_meter      =  segment_rec_hour_meter;
    model_outputs_work.segment_record_payload                 =  segment_rec_payload;
    model_outputs_work.segment_rec_payload_calc_method        =  segment_rec_payload_calc_method;
    model_outputs_work.segment_timezone_offset                =  LIBPROD_timezone_offset;
}




/*******************************************************************************/
/*
***  FUNTION: UPDATE FUNCTION
***
**** DESCRIPTION : This function collects all the data from the model and do some processing to make it ready and available for CA14's call-back functions. 
****				If the real time is not available at the model input all the data will be stored in a buffer with a time counter( from common cs library). 
****				These segment will be sent once real time is available at the model input(after calculating the lost time using time counter attached with each segment and duration).
****				The maximum size of the buffer is 5. We should not bother if real time is not available for more than 5 segment( means buffer is full) anytime.
***	 
*** CALLED BY
*** 
***
*** 
***
*******************************************************************************/

void cs_interface_update(void)
{
    
    
     
	/*update the model output*/
	Refresh_mdl_output();
	
    /* Check if this is the first time real time became available. Important for the first segment after buffer flush
     or first segment after keyon */
    if(realtime_first_available == FALSE && LIBPROD_realTime_status == STATUS_REALTIME_AVAILABLE)
    {
        realtime_first_available = TRUE;
        /*capture time at first realtime available for segment(s) immediately when time is available*/
        first_valid_realtime = LIBPROD_real_time;
    }
    else if(realtime_first_available == FALSE) /* Realtime is still not available */
    {
        /* Save previous bad (stale) time for back calculation of time. Important for first segment after buffer flush
        or first segment after keyon */
        previous_stale_time = LIBPROD_real_time;
    }
    
    /* if initialization did not complete, don't run the update */
    if( TRUE == seg_registration_done )
    {  
        /* check if we have anything in the buffer */           
        if((model_outputs_buffer != NULL) && (buffer_empty == FALSE))
        { 
			/*Check if the time is available from appside to the model or even if the key switch has been turned off, 
			  then we need to send all the records that we have to PD library*/
			if((LIBPROD_realTime_status == STATUS_REALTIME_AVAILABLE) || (keyswitch_override_flag == FALSE))
			{
				if(PD_buffer_size != 0)
				{
					/* send all the buffered segment data before the current one */
					while(seg_count > 0)
					{
                        /* If keyswitch happened we do not want to backdate, skip the following adjustment */
                        if(keyswitch_override_flag == TRUE)
                        {
						    /* Adjust/calculate time stamp - previously saved timestamp is back dated from when time became available (minus the last known stale time)*/
                            model_outputs_buffer[curr_buff].segment_record_start_real_time = LIBPROD_real_time - (previous_stale_time - model_outputs_buffer[curr_buff].segment_record_start_real_time);
                        }
				   
						segment_block.seg_id                           = model_outputs_buffer[curr_buff].segment_record_identifier; 
						segment_block.segment_block_time.start_tm_utc  = model_outputs_buffer[curr_buff].segment_record_start_real_time + REAL_TIME_OFFSET;					
						segment_block.segment_block_time.tmZoneOffset  = model_outputs_buffer[curr_buff].segment_timezone_offset;
						segment_block.segment_block_time.start_shm     = model_outputs_buffer[curr_buff].segment_record_service_hour_meter;
						segment_block.seg_duration                     = model_outputs_buffer[curr_buff].segment_record_duration;
						segment_block.distance_traveled                = model_outputs_buffer[curr_buff].segment_record_distance_travelled;
						segment_block.fuel_consumed                    = model_outputs_buffer[curr_buff].segment_record_fuel_consumed;
						segment_block.payload                          = model_outputs_buffer[curr_buff].segment_record_payload;
						segment_block.payload_method                   = model_outputs_buffer[curr_buff].segment_rec_payload_calc_method;
											
						/*Trigger function from productivity data*/
						send_segment_record_block();
						seg_count--;
						curr_buff++;
						if(seg_count == 0)
						{
							buffer_empty = TRUE;
							/*buffer is empty, reset the index */
							curr_buff = 0;
						}
					}
				}
			}
		}
			
		/*If there is a segment commit any time, check two different time status flags; time status flag for model input and time status flag for model output*/
        if( commit_segment_record == 1 )/*Check is segment is done */
		{ 
            if(LIBPROD_realTime_status == STATUS_REALTIME_AVAILABLE)
			{   
                /* is this the first record since time became available? */
                if(first_record_when_time_available == FALSE)
                {
				    /* This is the first record since time was available. Need to adjust timestamp */
                    /* Adjust/calculate time stamp - previously saved timestamp is back dated from when time became available (minus the last known stale time)*/
                    first_rec_after_buff_start_time = model_outputs_work.segment_record_start_real_time;
                    model_outputs_work.segment_record_start_real_time = first_valid_realtime - (previous_stale_time - model_outputs_work.segment_record_start_real_time);
                    first_record_when_time_available = TRUE;
                }
                
				// !!!! need to change the flag once model provide a status flag for time. Jeff suggest to add a story for model change!!!! 03-14-2016..Rahul
				/*If the time from model output is valid, send that value for CA14 else calculate from model segment start time for that segment */
				else /*(segment_rec_start_real_time > previous_stale_time)*/
				{
                    model_outputs_work.segment_record_start_real_time  = segment_rec_start_real_time;/* Directly from Model*/
				}
				
				/*copy from model to segment block*/   
				segment_block.seg_id                          = model_outputs_work.segment_record_identifier;
				segment_block.segment_block_time.start_tm_utc = model_outputs_work.segment_record_start_real_time + REAL_TIME_OFFSET;
				segment_block.segment_block_time.tmZoneOffset = model_outputs_work.segment_timezone_offset;
				segment_block.segment_block_time.start_shm    = model_outputs_work.segment_record_service_hour_meter;                
				segment_block.seg_duration                    = model_outputs_work.segment_record_duration;
				segment_block.distance_traveled               = model_outputs_work.segment_record_distance_travelled;
				segment_block.fuel_consumed                   = model_outputs_work.segment_record_fuel_consumed;   
				segment_block.payload                         = model_outputs_work.segment_record_payload;
				segment_block.payload_method                  = model_outputs_work.segment_rec_payload_calc_method;
				send_segment_record_block();
				/* trigger a GPS block every time we have a seg record commit, regardless of real time */
				gps_ext_trigger();
			}
			else
			{
				//we don't have real time available,
				//just save the data in the buffer.
                if(model_outputs_buffer != NULL)
			    { 
				    /*move the data in to the buffer if room*/
				    if(seg_count < PD_buffer_size)
				    {
                        model_outputs_buffer[seg_count] = model_outputs_work; /*current data*/
				    	seg_count++;
				    	buffer_empty = FALSE;
				    }
                    
				    else
				    {
				    	if(PD_buffer_size != 0)
				    	{
				    		unsigned_8 local_buffer_counter = 0; 
				    					
				    		/*Here we are copying the oldest record stored in the buffer and sending it to PD library*/
				    		segment_block.seg_id                           = model_outputs_buffer[0].segment_record_identifier; 
				    		segment_block.segment_block_time.start_tm_utc  = model_outputs_buffer[0].segment_record_start_real_time + REAL_TIME_OFFSET;					
				    		segment_block.segment_block_time.tmZoneOffset  = model_outputs_buffer[0].segment_timezone_offset;
				    		segment_block.segment_block_time.start_shm     = model_outputs_buffer[0].segment_record_service_hour_meter;
				    		segment_block.seg_duration                     = model_outputs_buffer[0].segment_record_duration;
				    		segment_block.distance_traveled                = model_outputs_buffer[0].segment_record_distance_travelled;
				    		segment_block.fuel_consumed                    = model_outputs_buffer[0].segment_record_fuel_consumed;
				    		segment_block.payload                          = model_outputs_buffer[0].segment_record_payload;
				    		segment_block.payload_method                   = model_outputs_buffer[0].segment_rec_payload_calc_method;
                    
				    		/*Trigger function from productivity data*/
				    		send_segment_record_block();
                    
				    		/*We have to keep the buffer correctly arranged in the order of oldest record first, so the next 
				    		  time we try to send the entire data out, we would send in the correct order to PD library*/
				    		while(local_buffer_counter < (PD_buffer_size - 1))
				    		{
				    			model_outputs_buffer[local_buffer_counter] = model_outputs_buffer[local_buffer_counter + 1];
                                local_buffer_counter++;
				    		}
                    
				    		/*here we are loading the current record information from the model into the buffer space*/
                            model_outputs_buffer[PD_buffer_size - 1] = model_outputs_work; /*current data*/
				    		buffer_empty = FALSE;
                    
				    	}
				    }
			    }
			}
            
			/* trigger a GPS block every time we have a seg record commit, regardless of real time */
            gps_ext_trigger();
				
		}
	}
}

/*******************************************************************************
*
*  UTC time in seconds after 1/6/1980
*******************************************************************************/
void cs_get_segment_time_stamp(unsigned_8* pLocation, unsigned_16 size)
{
    memset(pLocation, 0x0, size);
    memcpy( pLocation, &segment_block.segment_block_time ,size);
    return;	
}

/*******************************************************************************
*
*  one byte identifier as listed in CA14 BDT doc
*******************************************************************************/
void cs_get_segment_id(unsigned_8* pLocation, unsigned_16 size)
{  
    unsigned_8 id = (unsigned_8)segment_block.seg_id;
	memset(pLocation, 0x0, size);	
    memcpy(pLocation, &id, size);
    return; 
}
/*******************************************************************************
*
*  duration of segment in seconds, as a float
*******************************************************************************/
void cs_get_segment_duration(unsigned_8* pLocation, unsigned_16 size)
{
  //duration from model is 20 ms count, 50 counts/sec; BDT needs seconds in float
    float duration = ((float)segment_block.seg_duration)/50.0;
    memset(pLocation, 0x0, size);	
    memcpy(pLocation, &duration, size);
    return; 
}

/*******************************************************************************
*
*   liters of fuel consumed during segment as a float
*******************************************************************************/
void cs_get_segment_fuel_consumed(unsigned_8* pLocation, unsigned_16 size)
{
    float fuel = (float)segment_block.fuel_consumed;
    memset(pLocation, 0x0, size);	
    memcpy(pLocation, &fuel, size);
    return; 
}

/*******************************************************************************
*
*   distance traveled in meters, as a float
*******************************************************************************/
void cs_get_segment_distance_travelled(unsigned_8* pLocation, unsigned_16 size)
{
    float distance = ((float)segment_block.distance_traveled) * 1000;
    memset(pLocation, 0x0, size);	
    memcpy(pLocation, &distance, size);
    return; 
}

/*******************************************************************************
*
*  idle duration of segment in seconds, as a float
*******************************************************************************/
void cs_get_segment_machine_idle_duration(unsigned_8* pLocation, unsigned_16 size)
{
	float idle_duration = (float)segment_block.machine_idle_time;
    memset(pLocation, 0x0, size);	
    memcpy(pLocation, &idle_duration, size);
    return; 
}

/*******************************************************************************
*
*  payload weight in tonnes, as a float
*******************************************************************************/
void cs_get_segment_payload_wt(unsigned_8* pLocation, unsigned_16 size)
{
    float weight = (float)segment_block.payload;
    memset(pLocation, 0x0, size);	
    memcpy(pLocation, &weight, size);
    return; 
}

/*******************************************************************************
*
*   payload calculation method, 2 bytes
*******************************************************************************/
void cs_get_segment_payload_calc_method(unsigned_8* pLocation, unsigned_16 size)
{
    unsigned_16 payload_calc_method;
    unsigned_8 *des_lu8 = (unsigned_8 *)&payload_calc_method;
    unsigned_8 *src_lu8 = (unsigned_8 *)&(segment_block.payload_method);
    memset(pLocation, 0x0, size);	
	
    /*Swap to LSB because back office goes by PID definition for this UID */
    des_lu8 +=1;
    *des_lu8-- = *src_lu8++;
    *des_lu8 = *src_lu8;	
    memcpy(pLocation, &payload_calc_method, size);
    return;
}

/*******************************************************************************
*    Monitor keyswitch override flag from model, so that Implement is shutdown 
*    only after getting the Key-off Engine-off Segment
*******************************************************************************/

boolean cs_get_shutdown_override()
{
	if ((FALSE == keyswitch_override_flag) && buffer_empty == TRUE)
	{
		/* Commit has been done for the Key-Off Engine-Off Segment and buffers from RTC UNAVAILABLE TIME also have
		   been sent to PD library for NVM storage,
		   we can now ask Implement to shut down */
		return KSO_RET_SUCCESS;
	}
	/* We are not ready to shut down the implement yet, waiting for some more data */
	return KSO_RET_ERROR;
}
