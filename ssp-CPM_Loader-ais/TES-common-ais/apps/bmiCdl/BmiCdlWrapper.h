#ifndef BMICDLWRAPPER_H
#define BMICDLWRAPPER_H

#ifndef COMMTASK_H_
#include <commTask/commTask.h>
#endif
#ifndef BMICDLAutomation_H
#include "BmiCdlAutomation.h"
#endif
#include <interfaces/DataLinkData/InterfaceTypes.h>


class BmiCdlWrapper : public commTask
{
public:
	BmiCdlWrapper();
	~BmiCdlWrapper();
	void Initialize(void);
	static void AppConnectFunc(unsigned_8 mid, unsigned_8 status);
	static int_16 AppPidHandler
							(   unsigned_8 *data, /* pointer to message receive data */
								unsigned_8 data_len, /* message data length */
								void  *pie, /* pointer to pie or data */
								unsigned_16 rx_data_dsi_code /* receive data DSI */
							);
	void PublishCdlData(DataLinkDataOutput* pDataLinkDataOutput);
	bool AddDlParam(DataLinkParam dlParam);
	static void UpdateDlpDiag( uint16_t cid, uint8_t mid, DataLinkData::DldFmiCode_t fmi, DataLinkData::DldFmiStatus_t status );
#ifdef WRITE_AUTOMATION_DATA
	static BmiCdlAutomation CDL_Aut;
#endif
protected:

private:

};

#endif // BMICDLWRAPPER_H
