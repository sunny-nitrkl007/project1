#ifndef BMIETHSPNHNDLR_H
#define BMIETHSPNHNDLR_H

#include "scl_pdb.h"

class BmiEthSpnHndlr
{
public:
	BmiEthSpnHndlr( );
    virtual ~BmiEthSpnHndlr( );
    static void AppCsfPgtClientSpnRxHdlr(uint8_t datalinkType,
    							uint8_t datalinkInstance,
    							uint32_t srcId,
    							uint32_t destId,
    							void* datalinkInfo,
    							uint8_t* data,
    							uint16_t dataSize,
    							uint8_t* rawData,
    							const struct scl_pdb_spn_rx_config_s* spnConfig,
    							scl_pdb_param_status_t dataStatus);

protected:

private:


};

#endif //BMIETHSPNHNDLR_H
