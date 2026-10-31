/*******************************************************************************
** COPYRIGHT (C) 2018 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: ProdDataInf.cpp
DESCRIPTION:
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include "VP3RecMgr.h"

TABLE_ARRAY_T load;
TABLE_ARRAY_T cycle;
TABLE_ARRAY_T segment;
TABLE_ARRAY_T status;
TABLE_ARRAY_T payload;
TABLE_ARRAY_T gps;

/* Null, because instance will be initialized on demand. */
VP3RecMgr* VP3RecMgr::instance = 0;

uint8_t* ptr_to_temp_buffer;

VP3RecMgr::VP3RecMgr() {}

VP3RecMgr* VP3RecMgr::getInstance()
{
    if (instance == 0)
    {
        instance = new VP3RecMgr();
    }

    return instance;
}

VP3RecMgr* RecInstance = VP3RecMgr::getInstance();

#ifdef __cplusplus
extern "C" {
#endif

REG_RET_T register_to_provide_block_info(pd_uid_info uidInfo,
                                         BLOCK_TYPE_T blockType,
                                        PD_FUNC_PTR* pFunction)
{
    return RecInstance->registerToProvideBlockInfo(uidInfo, blockType, pFunction);
}

uint8_t send_gps_record_block()
{
    return RecInstance->sendGpsRecordBlock();
}

uint8_t send_segment_record_block()
{
    return RecInstance->sendSegmentRecordBlock();
}

uint8_t send_cycle_record_block()
{
    return RecInstance->sendCycleRecordBlock();
}

uint8_t send_payload_record_block()
{
    return RecInstance->sendPayloadRecordBlock();
}

uint8_t send_load_record_block()
{
    return RecInstance->sendLoadRecordBlock();
}

#ifdef __cplusplus

}
#endif /* #ifndef __PRODDATAINF_CPP__ */

