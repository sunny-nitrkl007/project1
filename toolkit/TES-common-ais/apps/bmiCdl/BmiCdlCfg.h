#ifndef BMICDLCFG_H
#define BMICDLCFG_H

#ifndef BMICDLDEF_H
#include "BmiCdlDef.h"
#endif

#ifndef BMICDLCDL2DEF_H
#include "BmiCdlCdl2Def.h"
#endif

extern BmiCdlCdl2CbsEcmApp_t BmiCdlCbsEcmTbl;

class BmiCdlCfg
{
public:
	BmiCdlCfg();
	~BmiCdlCfg();
	Ret_t ParseConfig(ConfigSection *pRubyCfg);
	bool ReadJsonFilePath(ConfigSection *pRubyCfg);
	bool ReadConfigJsonFile();
	bool ValidateTables();
	bool ValidateParmTableMID(int ecm_entrees_count, unsigned_8 parm_mid);

	bool publishDatalinkData;
	unsigned short CycleRateHz;
    std::string jsonFilePath;
protected:

private:

};

#endif // BMICDLCFG_H
