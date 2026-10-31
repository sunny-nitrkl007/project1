#ifndef BMICDLAutomation_H
#define BMICDLAutomation_H

#ifndef COMMTASK_H_
#include <commTask/commTask.h>
#endif

#include <interfaces/DataLinkData/InterfaceTypes.h>


class BmiCdlAutomation : public commTask
{
public:
	BmiCdlAutomation();
	~BmiCdlAutomation();
	void Initialize(void);
	static void AutomationInit();
	static void AutomationDataWriting(DataLinkParam& dlParam,unsigned_16 rx_data_dsi_code,unsigned_8 data_len);
	

protected:

private:

};

#endif // BMICDLAutomation_H
