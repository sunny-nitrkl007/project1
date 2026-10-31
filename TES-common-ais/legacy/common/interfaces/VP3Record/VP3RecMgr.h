#ifndef _VP3RecMgr_h_
#define _VP3RecMgr_h_

#include <ais/task/Task.h>
#include <ais/serialization/csvable.h>
#include <ais/log/AisLogger.h>
#include <ais/serialization/Datum.h> // For Boost serialization
#include <algorithm>
#include <cstring>
#include <sstream>
#include <iostream>
#include "InterfaceTypes.h"
#include "ProdDataPublic.h"

extern uint8_t* ptr_to_temp_buffer;

class VP3RecMgr
{  
public:

     /* Static access method */
     static VP3RecMgr* getInstance();

     /* Declaring Vp3 record buffer vector */
     std::vector<VP3Record> vp3RecObjbuffer;

    bool Vp3RecBufferinit(uint16_t bufferSize)
    {
        vp3RecObjbuffer.resize(bufferSize);

        FirstAvailIndex = 0;

        VP3RecordOutputInf = dynamic_cast<VP3RecordOutput*>( task::InterfaceDb::fetch( "VP3RecordOutput" ) );

        if (!VP3RecordOutputInf )
        {
            AIS_LOG_ERROR( "Interface VP3RecordOutputInf not configured.\n " );
            return false;
        }

        return true;
    }
    
    /******************************************************************************
    Function Name:      PROD_REG_RET_T register_to_provide_uid_info(pd_uid_info uid_info,
                                PROD_BLOCK_TYPE_T block_type,
                                FUNC_PTR* ptr_to_func)
    I/O Parameters:     
    
    Name                  I/O Type                Parameter Description / Contents      
    -------------------            --- ----------          ---------------------------------- 
    pd_uid_info uid_info            I/P                associated uid of data        
    PROD_BLOCK_TYPE_T block_type    I/P            block type
    PD_FUNC_PTR* ptr_to_func      I/P            callback function pointer
        
    Functions Called: call by apps

    Description: Function registers app call and make entry into appropriate PD registration table. 
    ******************************************************************************/
    REG_RET_T registerToProvideBlockInfo(pd_uid_info uidInfo,
                                BLOCK_TYPE_T blockType,
                                PD_FUNC_PTR* pFunction)
    {
        AIS_LOG_DEBUG("Entered register to provide block info \n");

        TABLE_ARRAY_T *pTableArray;
        TABLE_T *pTable;
        int8_t i=0;

        if(pFunction == NULL)
        {
            return REG_NULL_FUNC_PTR;
        }
    
        switch(blockType)
        {
        case PROD_BLOCK_TYPE_LOAD:
            pTableArray = &load;
            break;
        case PROD_BLOCK_TYPE_CYCLE:
            pTableArray = &cycle;
            break;
        case PROD_BLOCK_TYPE_SEGMENT:
            pTableArray = &segment;
            break;
        case PROD_BLOCK_TYPE_STATUS:    
            pTableArray = &status;
            break;
        case PROD_BLOCK_TYPE_PAYLOAD:
            pTableArray = &payload;
            break;    
        case PROD_BLOCK_TYPE_GPS:
            pTableArray = &gps;
            break;
        default:
            return (REG_INVALID_BLOCK);
            break;
        }

        AIS_LOG_DEBUG("ptable array size =%d \n", pTableArray->curr_array_size);

        if(pTableArray->curr_array_size >= TABLE_SIZE)
        {
        	return REG_SIZE_OVER_FLOW;
        }

        /*     case 1: uid is not assigned yet, add it to the right slot in the table.
            case 2: uid already exists and matches perfectly, reject it. 
            case 3: uid doesn't match exactly, put it in the data block section */
        
        for(i=0; i < pTableArray->curr_array_size; i++)
        {
            pTable = &pTableArray->table_array[i];
        
            if(pTable->block_uid.uid == uidInfo.uid && 
               pTable->block_uid.uid_id == uidInfo.uid_id && 
               pTable->block_uid.uid_size == uidInfo.uid_size && 
               pTable->block_uid.uid_dataype == uidInfo.uid_dataype &&
               pTable->block_uid.uid_color == uidInfo.uid_color)
            {
                if(pTable->func_ptr == NULL)
                {              
                    pTable->func_ptr = pFunction;
                    return (REG_SUCCESS);
                }
                else
                {
                    return (REG_DUPLICATE_BLOCK);
                }
            }
        }
    
        pTable = &pTableArray->table_array[pTableArray->curr_array_size]; 
        pTable->block_uid = uidInfo;
        pTable->func_ptr = pFunction;
        pTableArray->curr_array_size++;

        return (REG_SUCCESS);
}

/******************************************************************************
send_segment_record_block - This function creates a segment data block with the 
        corresponding UIDs and publishes the Segment record scs object to VP3 app.
******************************************************************************/
uint8_t sendSegmentRecordBlock(void)
{
    AIS_LOG_DEBUG("Entered send segment record block\n");
    
    uint16_t CurrUidSize = 0;
    uint16_t mem_block_size = 0;
    TABLE_ARRAY_T *pTableArray;
    TABLE_T *pTable;
    uint8_t* pBuffer;
    uint8_t retVal;
    char tempBuffer[10];

    pTableArray = &segment;

    if(FirstAvailIndex >= vp3RecObjbuffer.size())
    {
        retVal = BUFFER_SIZE_EXCEEDED_ERROR;
        return retVal;
    }
    else
    {
        for(int8_t i=0; i < pTableArray->curr_array_size; i++)
        {
            pTable = &pTableArray->table_array[i];

            CurrUidSize = pTable->block_uid.uid_size;

            /* to check for the largest size of the uid data */
            if(CurrUidSize > mem_block_size)
            { 
                mem_block_size = CurrUidSize;
            }
        }

        AIS_LOG_DEBUG("size of the pbuffer = %d \n", mem_block_size);

        ptr_to_temp_buffer = (uint8_t*)malloc(mem_block_size);

        memset(ptr_to_temp_buffer, 0, mem_block_size);
        pBuffer =  ptr_to_temp_buffer;

        vp3RecObjbuffer[FirstAvailIndex].setRecordType(SEGMENT);

        for(int8_t i=0; i < pTableArray->curr_array_size; i++)
        {
            char UID_Segment[] = {RECORD_ID, RECORD_SIZE, static_cast<char>(segment.table_array[i].block_uid.uid[0]), static_cast<char>(segment.table_array[i].block_uid.uid[1]), static_cast<char>(segment.table_array[i].block_uid.uid[2]), static_cast<char>(segment.table_array[i].block_uid.uid[3]), static_cast<char>(segment.table_array[i].block_uid.uid_id), static_cast<char>(segment.table_array[i].block_uid.uid_size), static_cast<char>(segment.table_array[i].block_uid.uid_dataype), static_cast<char>(segment.table_array[i].block_uid.uid_color), static_cast<char>(segment.table_array[i].block_uid.uid_dataSource[0]), static_cast<char>(segment.table_array[i].block_uid.uid_dataSource[1])};

            pTable = &pTableArray->table_array[i];

            if(pTable->func_ptr != NULL)
            {
                (pTable->func_ptr)(pBuffer, pTable->block_uid.uid_size);
            }
            else 
            {
                retVal = NULL_POINTER_ERROR;
                return retVal;
            }

            if((segment.table_array[i].block_uid.uid[0] == TIMESTAMP_UID_FIRST_BYTE) &&
            (segment.table_array[i].block_uid.uid[1] == TIMESTAMP_UID_SECOND_BYTE) &&
            (segment.table_array[i].block_uid.uid[2] == TIMESTAMP_UID_THIRD_BYTE) &&
            (segment.table_array[i].block_uid.uid[3] == TIMESTAMP_UID_FOURTH_BYTE))
            {
                /* Getting UTC time */
                unsigned int tempUTC = 0;
                memcpy(&tempUTC, pBuffer, SIZE_OF_UTC);
                pBuffer += SIZE_OF_UTC;

                /* Getting TZ offset */
                int16_t tempTZOffset;
                memcpy(&tempTZOffset, pBuffer, SIZE_OF_TZOFFSET);
                pBuffer += SIZE_OF_TZOFFSET;

                /* Getting SHM */
                unsigned int tempSHM;
                memcpy(&tempSHM, pBuffer, SIZE_OF_SHM);

                vp3RecObjbuffer[FirstAvailIndex].add_timestamp(std::string(&UID_Segment[0], RECORD_MAX_SIZE), tempUTC, tempTZOffset, tempSHM, true);
            }
            else
            {
                for(int8_t j=0; j < segment.table_array[i].block_uid.uid_size; j++)
                {
                    tempBuffer[j] = *(pBuffer+j);
                }

                vp3RecObjbuffer[FirstAvailIndex].add_string_to_record(std::string(&UID_Segment[0], RECORD_MAX_SIZE), std::string(&tempBuffer[0], segment.table_array[i].block_uid.uid_size));
            }

            /* deallocating pBuffer for next values */
            memset(ptr_to_temp_buffer, 0, mem_block_size);
            pBuffer =  ptr_to_temp_buffer;
        }

        FirstAvailIndex++;
        free(ptr_to_temp_buffer);

        retVal = SEND_REC_SUCCESS;
        return retVal;
    }
}

/******************************************************************************
send_cycle_record_block - This function creates a cycle data block with the 
        corresponding UIDs
 ******************************************************************************/
uint8_t sendCycleRecordBlock(void)
{
    AIS_LOG_DEBUG("Entered send cycle record block\n");

    uint16_t CurrUidSize = 0;
    uint16_t mem_block_size = 0;
    TABLE_ARRAY_T *pTableArray;
    TABLE_T *pTable;
    uint8_t* pBuffer;
    uint8_t retVal;
    char tempBuffer[10];

    pTableArray = &cycle;

    if(FirstAvailIndex >= vp3RecObjbuffer.size())
    {
        retVal = BUFFER_SIZE_EXCEEDED_ERROR;
        return retVal;
    }
    else
    {
        for(int8_t i=0; i < pTableArray->curr_array_size; i++)
        {
            pTable = &pTableArray->table_array[i];

            CurrUidSize = pTable->block_uid.uid_size;

            /* to check for the largest size of the uid data */
            if(CurrUidSize > mem_block_size)
            { 
                mem_block_size = CurrUidSize;
            }
        }

        ptr_to_temp_buffer = (uint8_t*)malloc(mem_block_size);

        memset(ptr_to_temp_buffer, 0, mem_block_size);
        pBuffer =  ptr_to_temp_buffer;

        vp3RecObjbuffer[FirstAvailIndex].setRecordType(CYCLE);

        for(int8_t i=0; i < pTableArray->curr_array_size; i++)
        {
            char UID_Cycle[] = {RECORD_ID, RECORD_SIZE, static_cast<char>(cycle.table_array[i].block_uid.uid[0]), static_cast<char>(cycle.table_array[i].block_uid.uid[1]), static_cast<char>(cycle.table_array[i].block_uid.uid[2]), static_cast<char>(cycle.table_array[i].block_uid.uid[3]), static_cast<char>(cycle.table_array[i].block_uid.uid_id), static_cast<char>(cycle.table_array[i].block_uid.uid_size), static_cast<char>(cycle.table_array[i].block_uid.uid_dataype), static_cast<char>(cycle.table_array[i].block_uid.uid_color), static_cast<char>(cycle.table_array[i].block_uid.uid_dataSource[0]), static_cast<char>(cycle.table_array[i].block_uid.uid_dataSource[1])};
        
            pTable = &pTableArray->table_array[i];

            if(pTable->func_ptr != NULL)
            {
                (pTable->func_ptr)(pBuffer, pTable->block_uid.uid_size);
            }
            else 
            {
                retVal = NULL_POINTER_ERROR;
                return retVal;
            }

            if((cycle.table_array[i].block_uid.uid[0] == TIMESTAMP_UID_FIRST_BYTE) &&
            (cycle.table_array[i].block_uid.uid[1] == TIMESTAMP_UID_SECOND_BYTE) &&
            (cycle.table_array[i].block_uid.uid[2] == TIMESTAMP_UID_THIRD_BYTE) &&
            (cycle.table_array[i].block_uid.uid[3] == TIMESTAMP_UID_FOURTH_BYTE))
            {
                /* Getting UTC time */
                unsigned int tempUTC = 0;
                memcpy(&tempUTC, pBuffer, SIZE_OF_UTC);
                pBuffer += SIZE_OF_UTC;

                /* Getting TZ offset */
                int16_t tempTZOffset;
                memcpy(&tempTZOffset, pBuffer, SIZE_OF_TZOFFSET);
                pBuffer += SIZE_OF_TZOFFSET;

                /* Getting SHM */
                unsigned int tempSHM;
                memcpy(&tempSHM, pBuffer, SIZE_OF_SHM);

                vp3RecObjbuffer[FirstAvailIndex].add_timestamp(std::string(&UID_Cycle[0], RECORD_MAX_SIZE), tempUTC, tempTZOffset, tempSHM, true);
            }
            else
            {
                for(int8_t j=0; j < cycle.table_array[i].block_uid.uid_size; j++)
                {
                    tempBuffer[j] = *(pBuffer+j);
                }

                vp3RecObjbuffer[FirstAvailIndex].add_string_to_record(std::string(&UID_Cycle[0], RECORD_MAX_SIZE), std::string(&tempBuffer[0], cycle.table_array[i].block_uid.uid_size));
            }

            /* deallocating pBuffer for next values */
            memset(ptr_to_temp_buffer, 0, mem_block_size);
            pBuffer =  ptr_to_temp_buffer;
        }

        FirstAvailIndex++;
        free(ptr_to_temp_buffer);

        retVal = SEND_REC_SUCCESS;
        return retVal;
    }
}

/******************************************************************************
send_load_record_block - This function creates a load data block with the 
        corresponding UIDs
 ******************************************************************************/
uint8_t sendLoadRecordBlock(void)
{
    AIS_LOG_DEBUG("Entered send load record block\n");
    
    uint16_t CurrUidSize = 0;
    uint16_t mem_block_size = 0;
    TABLE_ARRAY_T *pTableArray;
    TABLE_T *pTable;
    uint8_t* pBuffer;
    uint8_t retVal;    
    char tempBuffer[10];

    pTableArray = &load;

    if(FirstAvailIndex >= vp3RecObjbuffer.size())
    {
        retVal = BUFFER_SIZE_EXCEEDED_ERROR;
        return retVal;
    }
    else
    {
        for(int8_t i=0; i < pTableArray->curr_array_size; i++)
        {
            pTable = &pTableArray->table_array[i];

            CurrUidSize = pTable->block_uid.uid_size;

            /* to check for the largest size of the uid data */
            if(CurrUidSize > mem_block_size)
            { 
                mem_block_size = CurrUidSize;
            }
        }

        ptr_to_temp_buffer = (uint8_t*)malloc(mem_block_size);

        memset(ptr_to_temp_buffer, 0, mem_block_size);
        pBuffer =  ptr_to_temp_buffer;

        vp3RecObjbuffer[FirstAvailIndex].setRecordType(LOAD);

        for(int8_t i=0; i < pTableArray->curr_array_size; i++)
        {
            char UID_Load[] = {RECORD_ID, RECORD_SIZE, static_cast<char>(load.table_array[i].block_uid.uid[0]), static_cast<char>(load.table_array[i].block_uid.uid[1]), static_cast<char>(load.table_array[i].block_uid.uid[2]), static_cast<char>(load.table_array[i].block_uid.uid[3]), static_cast<char>(load.table_array[i].block_uid.uid_id), static_cast<char>(load.table_array[i].block_uid.uid_size), static_cast<char>(load.table_array[i].block_uid.uid_dataype), static_cast<char>(load.table_array[i].block_uid.uid_color), static_cast<char>(load.table_array[i].block_uid.uid_dataSource[0]), static_cast<char>(load.table_array[i].block_uid.uid_dataSource[1])};

            pTable = &pTableArray->table_array[i];

            if(pTable->func_ptr != NULL)
            {
                (pTable->func_ptr)(pBuffer, pTable->block_uid.uid_size);
            }
            else 
            {
                retVal = NULL_POINTER_ERROR;
                return retVal;
            }

            if((load.table_array[i].block_uid.uid[0] == TIMESTAMP_UID_FIRST_BYTE) &&
            (load.table_array[i].block_uid.uid[1] == TIMESTAMP_UID_SECOND_BYTE) &&
            (load.table_array[i].block_uid.uid[2] == TIMESTAMP_UID_THIRD_BYTE) &&
            (load.table_array[i].block_uid.uid[3] == TIMESTAMP_UID_FOURTH_BYTE))
            {
                /* Getting UTC time */
                unsigned int tempUTC = 0;
                memcpy(&tempUTC, pBuffer, SIZE_OF_UTC);
                pBuffer += SIZE_OF_UTC;

                /* Getting TZ offset */
                int16_t tempTZOffset;
                memcpy(&tempTZOffset, pBuffer, SIZE_OF_TZOFFSET);
                pBuffer += SIZE_OF_TZOFFSET;

                /* Getting SHM */
                unsigned int tempSHM;
                memcpy(&tempSHM, pBuffer, SIZE_OF_SHM);

                vp3RecObjbuffer[FirstAvailIndex].add_timestamp(std::string(&UID_Load[0], RECORD_MAX_SIZE), tempUTC, tempTZOffset, tempSHM, true);
            }
            else
            {
                for(int8_t j=0; j < load.table_array[i].block_uid.uid_size; j++)
                {
                    tempBuffer[j] = *(pBuffer+j);
                }
                
                vp3RecObjbuffer[FirstAvailIndex].add_string_to_record(std::string(&UID_Load[0], RECORD_MAX_SIZE), std::string(&tempBuffer[0], load.table_array[i].block_uid.uid_size));
            }

            /* deallocating pBuffer for next values */
            memset(ptr_to_temp_buffer, 0, mem_block_size);
            pBuffer =  ptr_to_temp_buffer;
        }

        FirstAvailIndex++;
        free(ptr_to_temp_buffer);

        retVal = SEND_REC_SUCCESS;
        return retVal;
    }
}

/******************************************************************************
send_payload_record_block - This function creates a payload data block with the 
        corresponding UIDs
 ******************************************************************************/
uint8_t sendPayloadRecordBlock(void)
{
    AIS_LOG_DEBUG("Entered send payload record block\n");
    
    uint16_t CurrUidSize = 0;
    uint16_t mem_block_size = 0;
    TABLE_ARRAY_T *pTableArray;
    TABLE_T *pTable;
    uint8_t* pBuffer;
    uint8_t retVal;
    char tempBuffer[10];

    pTableArray = &payload;

    if(FirstAvailIndex >= vp3RecObjbuffer.size())
    {
        retVal = BUFFER_SIZE_EXCEEDED_ERROR;
        return retVal;
    }
    else
    {
        for(int8_t i=0; i < pTableArray->curr_array_size; i++)
        {
            pTable = &pTableArray->table_array[i];

            CurrUidSize = pTable->block_uid.uid_size;

            /* to check for the largest size of the uid data */
            if(CurrUidSize > mem_block_size)
            { 
                mem_block_size = CurrUidSize;
            }
        }

        ptr_to_temp_buffer = (uint8_t*)malloc(mem_block_size);

        memset(ptr_to_temp_buffer, 0, mem_block_size);
        pBuffer =  ptr_to_temp_buffer;

        vp3RecObjbuffer[FirstAvailIndex].setRecordType(PAYLOAD);

        for(int8_t i=0; i < pTableArray->curr_array_size; i++)
        {
            char UID_Payload[] = {RECORD_ID, RECORD_SIZE, static_cast<char>(payload.table_array[i].block_uid.uid[0]), static_cast<char>(payload.table_array[i].block_uid.uid[1]), static_cast<char>(payload.table_array[i].block_uid.uid[2]), static_cast<char>(payload.table_array[i].block_uid.uid[3]), static_cast<char>(payload.table_array[i].block_uid.uid_id), static_cast<char>(payload.table_array[i].block_uid.uid_size), static_cast<char>(payload.table_array[i].block_uid.uid_dataype), static_cast<char>(payload.table_array[i].block_uid.uid_color), static_cast<char>(payload.table_array[i].block_uid.uid_dataSource[0]), static_cast<char>(payload.table_array[i].block_uid.uid_dataSource[1])};

            pTable = &pTableArray->table_array[i];

            if(pTable->func_ptr != NULL)
            {
                (pTable->func_ptr)(pBuffer, pTable->block_uid.uid_size);
            }
            else 
            {
                retVal = NULL_POINTER_ERROR;
                return retVal;
            }

            if((payload.table_array[i].block_uid.uid[0] == TIMESTAMP_UID_FIRST_BYTE) &&
            (payload.table_array[i].block_uid.uid[1] == TIMESTAMP_UID_SECOND_BYTE) &&
            (payload.table_array[i].block_uid.uid[2] == TIMESTAMP_UID_THIRD_BYTE) &&
            (payload.table_array[i].block_uid.uid[3] == TIMESTAMP_UID_FOURTH_BYTE))
            {
                /* Getting UTC time */
                unsigned int tempUTC = 0;
                memcpy(&tempUTC, pBuffer, SIZE_OF_UTC);
                pBuffer += SIZE_OF_UTC;

                /* Getting TZ offset */
                int16_t tempTZOffset;
                memcpy(&tempTZOffset, pBuffer, SIZE_OF_TZOFFSET);
                pBuffer += SIZE_OF_TZOFFSET;

                /* Getting SHM */
                unsigned int tempSHM;
                memcpy(&tempSHM, pBuffer, SIZE_OF_SHM);

                vp3RecObjbuffer[FirstAvailIndex].add_timestamp(std::string(&UID_Payload[0], RECORD_MAX_SIZE), tempUTC, tempTZOffset, tempSHM, true);
            }
            else
            {
                for(int8_t j=0; j < payload.table_array[i].block_uid.uid_size; j++)
                {
                    tempBuffer[j] = *(pBuffer+j);
                }

                vp3RecObjbuffer[FirstAvailIndex].add_string_to_record(std::string(&UID_Payload[0], RECORD_MAX_SIZE), std::string(&tempBuffer[0], payload.table_array[i].block_uid.uid_size));
            }

            /* deallocating pBuffer for next values */
            memset(ptr_to_temp_buffer, 0, mem_block_size);
            pBuffer =  ptr_to_temp_buffer;
        }

        FirstAvailIndex++;
        free(ptr_to_temp_buffer);

        retVal = SEND_REC_SUCCESS;
        return retVal;
    }
}

/******************************************************************************
send_gps_record_block - This function creates a gps data block with the 
        corresponding UIDs
 ******************************************************************************/
uint8_t sendGpsRecordBlock(void)
{
    AIS_LOG_DEBUG("Entered send gps record block\n");
    
    uint16_t CurrUidSize = 0;
    uint16_t mem_block_size = 0;
    TABLE_ARRAY_T *pTableArray;
    TABLE_T *pTable;
    uint8_t* pBuffer;
    uint8_t retVal;
    char tempBuffer[10];

    pTableArray = &gps;

    if(FirstAvailIndex >= vp3RecObjbuffer.size())
    {
        retVal = BUFFER_SIZE_EXCEEDED_ERROR;
        return retVal;
    }
    else
    {
        for(int8_t i=0; i < pTableArray->curr_array_size; i++)
        {
            pTable = &pTableArray->table_array[i];

            CurrUidSize = pTable->block_uid.uid_size;

            /* to check for the largest size of the uid data */
            if(CurrUidSize > mem_block_size)
            { 
                mem_block_size = CurrUidSize;
            }
        }

        ptr_to_temp_buffer = (uint8_t*)malloc(mem_block_size);

        memset(ptr_to_temp_buffer, 0, mem_block_size);
        pBuffer =  ptr_to_temp_buffer;

        vp3RecObjbuffer[FirstAvailIndex].setRecordType(GPS);

        for(int8_t i=0; i < pTableArray->curr_array_size; i++)
        {
            char UID_Gps[] = {RECORD_ID, RECORD_SIZE, static_cast<char>(gps.table_array[i].block_uid.uid[0]), static_cast<char>(gps.table_array[i].block_uid.uid[1]), static_cast<char>(gps.table_array[i].block_uid.uid[2]), static_cast<char>(gps.table_array[i].block_uid.uid[3]), static_cast<char>(gps.table_array[i].block_uid.uid_id), static_cast<char>(gps.table_array[i].block_uid.uid_size), static_cast<char>(gps.table_array[i].block_uid.uid_dataype), static_cast<char>(gps.table_array[i].block_uid.uid_color), static_cast<char>(gps.table_array[i].block_uid.uid_dataSource[0]), static_cast<char>(gps.table_array[i].block_uid.uid_dataSource[1])};

            pTable = &pTableArray->table_array[i];

            if(pTable->func_ptr != NULL)
            {
                (pTable->func_ptr)(pBuffer, pTable->block_uid.uid_size);
            }
            else 
            {
                retVal = NULL_POINTER_ERROR;
                return retVal;
            }

            if((gps.table_array[i].block_uid.uid[0] == TIMESTAMP_UID_FIRST_BYTE) &&
            (gps.table_array[i].block_uid.uid[1] == TIMESTAMP_UID_SECOND_BYTE) &&
            (gps.table_array[i].block_uid.uid[2] == TIMESTAMP_UID_THIRD_BYTE) &&
            (gps.table_array[i].block_uid.uid[3] == TIMESTAMP_UID_FOURTH_BYTE))
            {
                /* Getting UTC time */
                unsigned int tempUTC = 0;
                memcpy(&tempUTC, pBuffer, SIZE_OF_UTC);
                pBuffer += SIZE_OF_UTC;

                /* Getting TZ offset */
                int16_t tempTZOffset;
                memcpy(&tempTZOffset, pBuffer, SIZE_OF_TZOFFSET);
                pBuffer += SIZE_OF_TZOFFSET;

                /* Getting SHM */
                unsigned int tempSHM;
                memcpy(&tempSHM, pBuffer, SIZE_OF_SHM);

                vp3RecObjbuffer[FirstAvailIndex].add_timestamp(std::string(&UID_Gps[0], RECORD_MAX_SIZE), tempUTC, tempTZOffset, tempSHM, true);
            }
            else
            {
                for(int8_t j=0; j < gps.table_array[i].block_uid.uid_size; j++)
                {
                    tempBuffer[j] = *(pBuffer+j);
                }

                vp3RecObjbuffer[FirstAvailIndex].add_string_to_record(std::string(&UID_Gps[0], RECORD_MAX_SIZE), std::string(&tempBuffer[0], gps.table_array[i].block_uid.uid_size));
            }

            /* deallocating pBuffer for next values */
            memset(ptr_to_temp_buffer, 0, mem_block_size);
            pBuffer =  ptr_to_temp_buffer;
        }

        FirstAvailIndex++;
        free(ptr_to_temp_buffer);

        retVal = SEND_REC_SUCCESS;
        return retVal;
    }
}

/******************************************************************************
VP3RecMgrUpdate - This function publishes the VP3 record objects in the vp3 rec
         obj buffer
 ******************************************************************************/
bool VP3RecMgrUpdate()
{
    AIS_LOG_DEBUG("Entered VP3 rec publish function \n ");

    for(int8_t i=0; i< FirstAvailIndex; i++)
    {
        bool scsCmdStat = VP3RecordOutputInf->publish(vp3RecObjbuffer[i]);
        AIS_LOG_DEBUG("Vp3 record Publish status from the buffer = %d \n", scsCmdStat);

        if(scsCmdStat != true)
        {
            AIS_LOG_DEBUG("VP3 record scs publish return %d \n ", scsCmdStat);
            return false;
        }
    }

    /* Cleanup function to be called to destroy the */
    cleanup();
    return true;    
}

 private:

     /* Here will be the instance stored */
     static VP3RecMgr* instance;

     /* Private constructor to prevent instancing */
     VP3RecMgr();

     uint8_t FirstAvailIndex;
     VP3RecordOutput  *VP3RecordOutputInf;

    /* Cleanup function */
    void cleanup()
    {
        AIS_LOG_DEBUG("Entered cleanup function to clear the VP3Record objects \n");

        /* To reset VP3Record object to zero */
        for(int8_t i=0; i < FirstAvailIndex; i++)
        {
            AIS_LOG_DEBUG("First avail index = %d \n", FirstAvailIndex);

            /*Clearing VP3rec object contents */    
            vp3RecObjbuffer[i].clearUIDList();
            vp3RecObjbuffer[i].clearSizeOfRecord();
            vp3RecObjbuffer[i].clearNumOfUIDs();
            vp3RecObjbuffer[i].clearRBlockData();
        
            AIS_LOG_DEBUG("size of buffer object = %d \n", sizeof vp3RecObjbuffer[i]);
        }
        FirstAvailIndex = 0;
    }

};

typedef Datum<VP3RecMgr> VP3RecordManager;

BOOST_CLASS_VERSION(VP3RecMgr, 1);
#endif

