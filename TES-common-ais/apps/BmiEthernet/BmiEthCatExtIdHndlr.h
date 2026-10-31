#ifndef BMIETHCATEXTIDHNDLR_H
#define BMIETHCATEXTIDHNDLR_H

#include "scl_pdb.h"

class BmiEthCatExtIdHndlr
{
public:
	BmiEthCatExtIdHndlr( );
    virtual ~BmiEthCatExtIdHndlr( );
    static void AppCsfPgtClientCatExtIdRxHdlr(uint8_t datalinkType,
    							uint8_t datalinkInstance,
    							uint32_t srcId,
    							uint32_t destId,
    							void* datalinkInfo,
    							uint8_t* data,
    							uint16_t dataSize,
    							const scl_pdb_cat_ext_id_rx_config_t* catExtIdConfig,
								scl_pdb_param_status_t dataStatus);

protected:

private:


};

#endif //BMIETHCATEXTIDHNDLR_H
