#ifndef BMICDLCDL2DEF_H
#include "BmiCdlCdl2Def.h"
#endif

#ifndef Task_h
#include <ais/task/Task.h>
#endif

#ifndef BMICDLDEF_H
#include "BmiCdlCfg.h"
#endif

#ifndef BMICDLPIDDEF_H
#include "BmiCdlPidDef.h"
#endif

//#ifndef BMICDLDEF_H
#include "BmiCdlWrapper.h"
//#endif

#include "VarLengthDataLinkParamPool.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


const cdl2_cbs_system_cfg_t BmiCdlCbsSysTbl =
{
    {                             /* ======= CBS System Table Header ======== */
        _CBS_NOT_USED_,/* ID32_t Table ID */
        CBS_TABLE_VERSION2,    /* unsigned_8 Table Format Level */
        CBS_SYSTEM_ENABLED,    /* unsigned_8 Enabled */
        BMI_CDL_SYS_TBL_ENTRIES_COUNT	/* unsigned_16 Num_Table_Entries (always 1 for system table) */
    },
    {                             /* ======= CBS System Table ======== */
        CBS_CFG_TABLES_SORTED,          /* 1 = CBS Config entries are sorted, 0 = Entries are random
                   (NOTE: Must be sorted in CBS version 1) */
        CBS_PTR_USED_IN_ID_FIELD, //CBS_ID32_USED_IN_ID_FIELD,      /* 1 = ID32 used in pointer fields, 0 = Pointers are used */
        CBS_IMMEDIATE_DATA_FLAG_SETTING,  /* 1 = Delay setting data status flag on loss of ECM, 0 = No Delay) */
        0x80                            /* system_flag, 0x80 enable rx data store right alignment */
    }
};

BmiCdlCdl2CbsEcmApp_t BmiCdlCbsEcmTbl;
BmiCdlAppCfg_t BmiCdlAppCfgTbl;
std::vector<int> pie_data(BMI_CDL_MAX_NUM_PARAMETERS); // to get a pointer for pie_data_id32 for each parameter

/* We are populating the ECM table from exteral config file, which lets us to change the config file even after the compilation
 * Need to note that the file name should be BmiCdlCfg.json, to read json file this static method uses the BOOST:PTree library
 * */
bool BmiCdlCfg::ReadConfigJsonFile()
{
	AIS_LOG_DEBUG("BmiCdlCfg::ReadConfigJsonFile");
	DataLinkParam dLinkParam;
	// Try reading the json file, boost ptree through errors
	try
	{
		// Short alias for this namespace
	    namespace pt = boost::property_tree;

		// Create a root
		pt::ptree tree;

		// Load the json file in this ptree
		pt::read_json(jsonFilePath, tree); // use jsonFilePath which we got from .rb file  ("/opt/CPM/config/BmiCdlCfg.json")
		// now 'tree' has complete json file in it with which we can populate ECM and param tables
		
		//int no_of_ecm_entrees                         = tree.get<int>("cdl2_cbs_ecm_header_t.num_table_entries");
		//int no_of_parm_entrees                        = tree.get<int>("cdl2_cbs_parm_header_t.num_table_entries");
		int no_of_ecm_entrees = std::stoi(tree.get<std::string>("cdl2_cbs_ecm_header_t.num_table_entries"), 0, 16);
		int no_of_parm_entrees = std::stoi(tree.get<std::string>("cdl2_cbs_parm_header_t.num_table_entries"), 0, 16);


		/* Below checks are to make sure parm and ecm tables can hold all the entrees given in json file
		   TODO: We need to check if there is anyway to build these tables dynamically
		   Right now we can't modify the strcut parameters as they should match to one in cdl2_struct.h file */
		if (no_of_ecm_entrees > BMI_CDL_MAX_NUM_ECM && no_of_parm_entrees > BMI_CDL_MAX_NUM_PARAMETERS)
		{
			AIS_LOG_ERROR("BMI_CDL_MAX_NUM_ECM and BMI_CDL_MAX_NUM_PARAMETERS defiend in BmiCdlCdl2Def.h is not macthed to parm and ecm count in json");
			return false;
		}
		else if (no_of_ecm_entrees > BMI_CDL_MAX_NUM_ECM)
		{
			AIS_LOG_ERROR("BMI_CDL_MAX_NUM_ECM defiend in BmiCdlCdl2Def.h is not macthed to count in json, please correct BMI_CDL_MAX_NUM_ECM value");
			return false;
		}
		else if(no_of_parm_entrees > BMI_CDL_MAX_NUM_PARAMETERS)
		{
			AIS_LOG_ERROR("BMI_CDL_MAX_NUM_PARAMETERS defiend in BmiCdlCdl2Def.h is not macthed to count in json, please correct BMI_CDL_MAX_NUM_PARAMETERS value");
			return false;
		}

		/*
		 * Must follow below rules for CDL app to work properly.
		 * 1) Sort by ECM MID
		 * */
		// Saving the ECM table header from Json file
		BmiCdlCbsEcmTbl.Header.table_id 			= std::stoi(tree.get<std::string>("cdl2_cbs_ecm_header_t.table_id"), 0, 16);
		BmiCdlCbsEcmTbl.Header.table_format_level 	= std::stoi(tree.get<std::string>("cdl2_cbs_ecm_header_t.table_format_level"), 0, 16);
		BmiCdlCbsEcmTbl.Header.enabled 				= std::stoi(tree.get<std::string>("cdl2_cbs_ecm_header_t.enabled"), 0, 16);
		BmiCdlCbsEcmTbl.Header.num_table_entries 	= no_of_ecm_entrees;

		// Looping number of entrees times to save all ECMs in structure
		for (int i = 0; i < no_of_ecm_entrees; i++)
		{
			std::string node_name = "ecm_" + std::to_string(i) + "."; // get the path for correct node

			BmiCdlCbsEcmTbl.table[i].ecm_id32 			= std::stoi(tree.get<std::string>(node_name + "ecm_id32"), 0, 16);
			BmiCdlCbsEcmTbl.table[i].mid 				= std::stoi(tree.get<std::string>(node_name + "mid"), 0, 16);
			BmiCdlCbsEcmTbl.table[i].ecm_control 		= std::stoi(tree.get<std::string>(node_name + "ecm_control"), 0, 16);
			BmiCdlCbsEcmTbl.table[i].cid 				= tree.get<int>(node_name + "cid");
			BmiCdlCbsEcmTbl.table[i].connect_fnc_id32 	= (cdl_ptr_idx_t)&BmiCdlWrapper::AppConnectFunc;
			BmiCdlCbsEcmTbl.table[i].periodic_fnc_id32 	= std::stoi(tree.get<std::string>(node_name + "periodic_fnc_id32"), 0, 16);
			BmiCdlCbsEcmTbl.table[i].periodic_interval 	= tree.get<int>(node_name + "periodic_interval");
		}

		/*
		* Must follow below rules for CDL app to work properly.
		* 1) Sort by ECM MID
		* 2) Sort by protocol SPB, PGB, ADT, Readpoll
		* 3) Sort by fastest rate first within protocol
		*/
		// Saving the parameter table header from Json file
		BmiCdlAppCfgTbl.Header.table_id 			= std::stoi(tree.get<std::string>("cdl2_cbs_parm_header_t.table_id"), 0, 16);
		BmiCdlAppCfgTbl.Header.table_format_level	= std::stoi(tree.get<std::string>("cdl2_cbs_parm_header_t.table_format_level"), 0, 16);
		BmiCdlAppCfgTbl.Header.enabled 				= std::stoi(tree.get<std::string>("cdl2_cbs_parm_header_t.enabled"), 0, 16);
		BmiCdlAppCfgTbl.Header.num_table_entries 	= no_of_parm_entrees;

		// Looping number of entrees times to save all parameters in structure
		for (int i = 0; i < no_of_parm_entrees; i++)
		{
			std::string node_name = "parameter_" + std::to_string(i) + "."; // get the path for correct node

			// Parameter table
			BmiCdlAppCfgTbl.ParamCfgTbl[i].parmName     = tree.get<std::string>(node_name + "param_name");
			BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.parm_id32 		= std::stoi(tree.get<std::string>(node_name + "cdl2_cbs_parm_cdl_id_t"), 0, 16);
			BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.parm.cdl_id32 	= std::stoi(tree.get<std::string>(node_name + "cdl2_cbs_parm_cdl_id_t"), 0, 16);

			unsigned_8 req = std::stoi(tree.get<std::string>(node_name + "parm_control_req"), 0, 16);
			unsigned_8 rev = std::stoi(tree.get<std::string>(node_name + "parm_control_rev"), 0, 16);
			BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.parm_control 	= req|rev;
			//LOG_DEBUG("req %x, rev %x parm_control %x", req, rev, BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.parm_control);

			unsigned char param_request = tree.get<int>(node_name + "parm_request_type");
			BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.parm_request_type = static_cast<cdl2_cbs_parm_request_type_e>(param_request);

			unsigned char param_type = tree.get<int>(node_name + "parameter_type");
			BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.parameter_type 	= static_cast<cdl2_parameter_type_e>(param_type);

			BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.mid 				= std::stoi(tree.get<std::string>(node_name + "mid"), 0, 16);
			BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.request_rate 	= tree.get<int>(node_name + "request_rate");
			BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.handler_fnc_id32 = (cdl_ptr_idx_t)&BmiCdlWrapper::AppPidHandler; // doesn't depend on json file
			pie_data[i] = i;																							// the channelIndex is same as the loop variable value
			BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.pie_data_id32 	= (cdl_ptr_idx_t)&pie_data[i];						// assigning it to the address of vector array

			// Conversion table
			BmiCdlAppCfgTbl.ParamCfgTbl[i].ConvTbl.Scaling 				= tree.get<float>(node_name + "Scaling");
			BmiCdlAppCfgTbl.ParamCfgTbl[i].ConvTbl.Offset 				= tree.get<float>(node_name + "Offset");
			BmiCdlAppCfgTbl.ParamCfgTbl[i].ConvTbl.Units 				= static_cast<DataLinkParamInfo::DlpUnits_t>(tree.get<int>(node_name + "Units"));
			BmiCdlAppCfgTbl.ParamCfgTbl[i].ConvTbl.VarLengthDataType 	= static_cast<VarLengthDataLinkParamPool::VarLengthParamType>(tree.get<int>(node_name + "VarLengthParamType"));
			//LOG_DEBUG("ParmDataType %d, ParmDataLength %d", BmiCdlAppCfgTbl.ParamCfgTbl[i].ConvTbl.ParmDataType, BmiCdlAppCfgTbl.ParamCfgTbl[i].ConvTbl.ParmDataLength);

			dLinkParam.SetDataLinkType(DataLinkParamInfo::DATA_LINK_PARAM_CDL);
			dLinkParam.SetParameterName(BmiCdlAppCfgTbl.ParamCfgTbl[i].parmName);
			dLinkParam.SetParamId(BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.parm_id32);
			dLinkParam.SetParameterType(BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.parameter_type);
			dLinkParam.SetVarLengthParamType(static_cast<VarLengthDataLinkParamPool::VarLengthParamType>(BmiCdlAppCfgTbl.ParamCfgTbl[i].ConvTbl.VarLengthDataType));
			dLinkParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);
			dLinkParam.SetSid(BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.mid);
			dLinkParam.SetScaling(BmiCdlAppCfgTbl.ParamCfgTbl[i].ConvTbl.Scaling);
			dLinkParam.SetOffset(BmiCdlAppCfgTbl.ParamCfgTbl[i].ConvTbl.Offset);
			dLinkParam.SetUnits(BmiCdlAppCfgTbl.ParamCfgTbl[i].ConvTbl.Units);
            if (false == CdlWrapper.AddDlParam(dLinkParam))
            {
                AIS_LOG_ERROR("ReadConfigJsonFile error: Failed to add ParamId %d", BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.parm_id32);
                return false;
            }
		}
		return true;
	}
	catch (std::exception const &e)
	{
		AIS_LOG_ERROR("ReadConfigJsonFile error: %s", e.what());
	}
	return false;
}

/*
 * To validate the ECM and Parameter tables with the following conditions
 * 1. ECM table MID's should be sorted order
 * 2. Parameter table
 *   i.   MID's should be sorted order
 *   ii.  Protocals should be orderd as SPB, PGB, ADT, Readpoll
 *   iii. With in protocal,  fastest rate should be first
 * 3. Now check if all MID's in parameter table have a entry in ECM table
 */
bool BmiCdlCfg::ValidateTables()
{
	int ecm_table_range = BmiCdlCbsEcmTbl.Header.num_table_entries;
	int parm_table_range = BmiCdlAppCfgTbl.Header.num_table_entries;
	if (ecm_table_range == 0 || parm_table_range == 0)
	{
		AIS_LOG_ERROR("ECM and Param table entrees are set to 0");
		publishDatalinkData = false;
	}
	AIS_LOG_DEBUG("BmiCdlCfg::ValidateTables ecm range %d, parm range %d", ecm_table_range, parm_table_range);

	// By default both tables are valid, if any sorting order error we make flag as FALSE
	bool isEcmTableValid = true;  // ECM table validation flag
	bool isParmTableValid = true; // Parm table validation flag

	// Validate ECM table
	// true corresponds to PASS and false corresponds to FAIL
	for (int i = 1; i < ecm_table_range; i++)
	{
		if (BmiCdlCbsEcmTbl.table[i-1].mid > BmiCdlCbsEcmTbl.table[i].mid)
		{ // check if previous MID is greater than current mid
			// if previous mid is larger, set the respective mask flag for idnicating FAILURE
			AIS_LOG_ERROR("ECM Table MID's are not in increasing order for rows %d and %d", i-1, i);
			isEcmTableValid = false;
		}
	}

	// Validate Parm atble
	// For the first row check if the MID present in the ECM table outside the loop
	unsigned_8 first_row_parm_mid = BmiCdlAppCfgTbl.ParamCfgTbl[0].CbsParamTbl.mid;
	if (parm_table_range > 0 && !ValidateParmTableMID(ecm_table_range, first_row_parm_mid))
	{
		// MID doesn't have an entry in ECM table, log the error and set the respective flag
		AIS_LOG_ERROR("Parm Table MID 0x%x in row 0 is not in ECM table", first_row_parm_mid);
		isParmTableValid = false;
	}

	for (int i = 1; i < parm_table_range; i++)
	{
		unsigned_8 previous_mid = BmiCdlAppCfgTbl.ParamCfgTbl[i-1].CbsParamTbl.mid;
		unsigned_8 current_mid = BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.mid;

		if (previous_mid > current_mid)
		{
			// If previous MID is larger, log the error and check if this MID exist in ECM table
			AIS_LOG_ERROR("Parm Table MID's are not in increasing order for rows %d and %d", i-1, i);
			if (!ValidateParmTableMID(ecm_table_range, current_mid))
			{
				// if MID doesn't exist in ECM table log the error
				AIS_LOG_ERROR("Parm Table MID 0x%x in row %d is not present in ECM table", current_mid, i);
			}
			isParmTableValid = false;
		}
		else if (previous_mid == current_mid)
		{
			// if previous and current MID's are equal then check the request protocals order. Protocals are enums defined in order, so just compare the enum value directly
			if (BmiCdlAppCfgTbl.ParamCfgTbl[i-1].CbsParamTbl.parm_request_type > BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.parm_request_type)
			{ // check protocal order
			    // if previous protocal is larger, log the error and set the repective flag
				AIS_LOG_ERROR("Parm Table protocals are not in correct order for rows %d and %d", i-1, i);
				isParmTableValid = false;
			}
			else if (BmiCdlAppCfgTbl.ParamCfgTbl[i-1].CbsParamTbl.parm_request_type == BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.parm_request_type)
			{
				// if previous and current protocals are euqal, then check the request rates
				if (BmiCdlAppCfgTbl.ParamCfgTbl[i-1].CbsParamTbl.request_rate > BmiCdlAppCfgTbl.ParamCfgTbl[i].CbsParamTbl.request_rate)
				{
					// if previous request rate is larger, log the error and set the repective flag
					AIS_LOG_ERROR("Parm Table protocal request rates are not in correct order for rows %d and %d", i-1, i);
					isParmTableValid = false;
				}
			}
		}
		else
		{ // if previous mid is smaller than current mid
			// Check if this MID exist in ECM table
			if (!ValidateParmTableMID(ecm_table_range, current_mid))
			{
				// if MID doesn't exist in ECM table log the error and set the flag.
				AIS_LOG_ERROR("Parm Table MID's 0x%x in row %d is not present in ECM table", current_mid, i);
				isParmTableValid = false;
			}
		}
	}

	AIS_LOG_DEBUG("isEcmTableValid = %d, isParmTableValid = %d", isEcmTableValid, isParmTableValid);
	return (isEcmTableValid && isParmTableValid);
}

/* This method takes the number of entrees in parm table and a MID to check if that MID
 * is present in ECM table or not*/
bool BmiCdlCfg::ValidateParmTableMID(int ecm_entrees_count, unsigned_8 parm_mid)
{
	for (int i = 0; i < ecm_entrees_count; i++)
	{
		if (BmiCdlCbsEcmTbl.table[i].mid == parm_mid)
		{
			return true;
		}
	}
	// MID is not found in ECM table
	return false;
}

BmiCdlCfg::BmiCdlCfg() :
   publishDatalinkData(true)
{
}

BmiCdlCfg::~BmiCdlCfg()
{
}


Ret_t BmiCdlCfg::ParseConfig(ConfigSection *pRubyCfg)
{
	//cycleRate_hz
    pRubyCfg->get("cycleRate_hz", CycleRateHz);
    AIS_LOG_INFO("*** cycleRate_hz %d", CycleRateHz);

	return (RET_SUCCESS);
}

bool BmiCdlCfg::ReadJsonFilePath(ConfigSection *pRubyCfg)
{
	// get JSON file path
	if (pRubyCfg->get("BMI_CDL_CONFIG_JSON_FILE_PATH", jsonFilePath))
	{
    	AIS_LOG_INFO("jsonFilePath read success: %s", jsonFilePath.c_str());
		return true;
	}

	AIS_LOG_ERROR("unable find the json file path");
	return false;
}
