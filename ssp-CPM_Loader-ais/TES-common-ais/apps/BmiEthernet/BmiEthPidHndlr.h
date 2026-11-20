#ifndef BMIETHPIDHNDLR_H
#define BMIETHPIDHNDLR_H

#include "cdl2_struct.h"

class BmiEthPidHndlr
{
public:
	BmiEthPidHndlr( );
    virtual ~BmiEthPidHndlr( );
    static int16_t  AppCsfPgtClientPidRxHndlrv2(uint8_t datalinkType,
    												uint8_t datalinkInstance,
    												uint32_t srcId,
    												uint32_t destId,
    												void* datalinkInfo,
    												uint8_t* data,
    												uint8_t dataLen ,
    												const cdl2_cmn_rx_pit_t  *pidConfig,
    												uint16_t dsiCode);

protected:

private:


};

#endif //BMIETHPIDHNDLR_H
