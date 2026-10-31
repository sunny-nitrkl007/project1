#ifndef BMIJ1939Automation_H
#define BMIJ1939Automation_H

#include "BmiJ1939Config.h"
#include <interfaces/DataLinkData/InterfaceTypes.h>


class BmiJ1939Automation
{
	public:
		BmiJ1939Automation( void );
		virtual ~BmiJ1939Automation( void ) { }

		static void AutomationInitialise(const BmiJ1939Config& appConfig);
		 static void AutomationDataWrite(DataLinkParam& dlParam);
	

protected:

private:

};

#endif // BMIJ1939Automation_H
