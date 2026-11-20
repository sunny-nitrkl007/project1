////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiCdlAutomation
//
// File Name: BmiCdlAutomation.cpp
//
//  Abstract: Handle incoming CDL data link parameters.
//
////////////////////////////////////////////////////////

#ifndef BMICDLAutomation_H
#include "BmiCdlAutomation.h"
#endif

#ifndef Task_h
#include <ais/task/Task.h>
#endif

#ifndef OEL_PACK_H_
#include <oel_pack.h>
#endif

#ifndef BMICDLCDL2DEF_H
#include "BmiCdlCdl2Def.h"
#endif

#ifndef BMICDLWRAPPER_H
#include "BmiCdlWrapper.h"
#endif

#ifndef BMICDLPIDDEF_H
#include "BmiCdlPidDef.h"
#endif

#include <string.h>
#include <sys/stat.h>

#include <fstream>
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
#include <time.h>
using namespace std;

#define F82D 63533
#define F84D 63565
#define FA27 64039

static std::ofstream CSVFile;
#define GMT_YEAR_OFFSET  ((uint16_t)1900)
#define PIDF954_YEAR_OFFSET  ((unsigned_16)1985)
#define GMT_MONTH_OFFSET  ((unsigned_8)0x01)
static std::vector<uint32_t> PIDsList;
size_t Num_Of_PIDs;

string CSVFilePath = "/opt/tmp/outputFiles/AutomationData.csv";

/* Real Time */
time_t 	CurrentTime;
tm*		GMTime;




void BmiCdlAutomation::AutomationInit(void)
{
	AIS_LOG_INFO("Initialize start");
	GMTime = NULL;

	Num_Of_PIDs = BmiCdlAppCfgTbl.Header.num_table_entries;

	PIDsList.resize(Num_Of_PIDs);

	string Automation_CSV_Header;
	Automation_CSV_Header.append("TimeStamp,");

	// Reading the PIDs from JSON file and Update the csv File Header.
	for (size_t indx = 0; indx < Num_Of_PIDs; indx++)
	{
		string strDta;
		uint32_t Pid;
		PIDsList[indx] = Pid = BmiCdlAppCfgTbl.ParamCfgTbl[indx].CbsParamTbl.parm_id32;
		stringstream strem; strem <<hex << Pid;

		strDta =  strem.str();
		AIS_LOG_INFO("Json PID: %x\n",PIDsList[indx]);
		Automation_CSV_Header.append(strDta);
		Automation_CSV_Header.append(",");
	}


	cout << "Automation_CSV_Header: " <<Automation_CSV_Header<<"\n";
	if(std::remove(CSVFilePath.c_str()) != 0)
	{
		AIS_LOG_INFO("Not able to delete AutomationData.csv");
	}
	else
	{
		AIS_LOG_INFO("Successfully deleted AutomationData.csv");
	}

	CSVFile.open(CSVFilePath.c_str(), std::ofstream::app);

	if (CSVFile.is_open())
	{
		CSVFile << Automation_CSV_Header <<"\n"; //" TimeStamp, F604, 0x18, F002, F525, 0XC8, 0X40, F82D, F84D, FA27 \n";
	}
	else
	{
		AIS_LOG_INFO("Unable to open AutomationData.csv File.\n");
	}
	CSVFile.close();

	AIS_LOG_INFO("Initialize Done");
}


void BmiCdlAutomation::AutomationDataWriting(DataLinkParam& dlParam,unsigned_16 rx_data_dsi_code,unsigned_8 data_len)
{
	static map<uint32_t, string> m_pidDuplicate;
	// For TimeStamp
	CurrentTime = time(0); /* Read real time */
	GMTime = gmtime(&CurrentTime);

	int Seconds = 0, Minutes = 0, Hours = 0, Month = 0, Day = 0, Year = 0;
	Seconds = GMTime->tm_sec;
	Minutes = GMTime->tm_min;
	Hours = GMTime->tm_hour;
	Month = (GMTime->tm_mon + GMT_MONTH_OFFSET); /* Adding month offset (1) to avoid month mismatch */
	Day = GMTime->tm_mday;
	Year = (GMTime->tm_year + GMT_YEAR_OFFSET);

	// GMT time is 5.30 hours lower than IST time.
	int GmtHour = 5;
	Minutes = (Minutes + 29);
	if (Minutes >= 60)
	{
		Hours += (GmtHour + 1);
		Minutes = (Minutes - 60);
	}
	else
	{
		Hours += GmtHour;
	}

	AIS_LOG_INFO("IST Time: %d-%d-%d: %d:%d:%d\n",Day, Month, Year,Hours, Minutes, Seconds);


	string strYear, strMon, strDay, strHour, strMin, strSec, strDate, strTime, strTimeStamp;

	strDay = boost::lexical_cast<string>(Day);
	strMon = boost::lexical_cast<string>(Month);
	strYear = boost::lexical_cast<string>(Year);
	strHour = boost::lexical_cast<string>(Hours);
	strMin = boost::lexical_cast<string>(Minutes);
	strSec = boost::lexical_cast<string>(Seconds);

	//Appending the Day, month, year for strDate and Hours, Min, Sec for str Time.
	strDate.append(strDay); strDate.append(":"); strDate.append(strMon); strDate.append(":"); strDate.append(strYear);
	strTime.append(strHour); strTime.append(":"); strTime.append(strMin); strTime.append(":"); strTime.append(strSec);

	strTimeStamp.append(strDate); strTimeStamp.append(" "); strTimeStamp.append(strTime);
	uint32_t CurrentPID = dlParam.GetParamId();
	string strPIDData;
	stringstream strem; strem <<hex << rx_data_dsi_code;  // Dsi code Coverting to Hex.
	string strDSI_Code = strem.str();
	static uint32_t PrevPID = 0;
	static unsigned_32 PrevData = 0;

	if (((CurrentPID == F82D) || (CurrentPID == F84D) || (CurrentPID == FA27)) && (rx_data_dsi_code == 0))
	{
		const uint8_t* varParamBlock = dlParam.GetVarParamBlock();
		const unsigned_8 varParamBlockSize = dlParam.GetVarParamBlockLength();
		char chData[varParamBlockSize + 1];
		for (size_t i = 0; i < varParamBlockSize; i++)
		{
			chData[i] = varParamBlock[i];
		}
		AIS_LOG_INFO(" ------- chData: %s  %d",chData,varParamBlockSize);
		chData[varParamBlockSize] = '\0';
		strPIDData = string(chData);

		cout << "strPIDData: " << strPIDData <<"\n";
		AIS_LOG_INFO("Pid %s data %u",strPIDData,CurrentPID);
	}
	else
	{
		strPIDData = boost::lexical_cast<string>(dlParam.GetLastValue<unsigned_32>());
		cout<<"513 PrevsData "<< PrevData<<"currepidData %u "<<strPIDData <<"PrevPID "<< PrevPID<<" pid "<<dlParam.GetParamId()<<" data_len "<<data_len <<" rx_data_dsi_code "<<rx_data_dsi_code <<" Data: "<< strPIDData<<endl;
	}

	CSVFile.open(CSVFilePath.c_str() , std::ofstream::app);
	static bool skipDupliateFlag =0;
	map<uint32_t, string>::iterator it;
	map<uint32_t, string>::iterator itr1;
	for (itr1 = m_pidDuplicate.begin(); itr1 != m_pidDuplicate.end(); ++itr1)
	{
		cout<<"522 before starting itr1->first   itr1->second "<<itr1->first<< itr1->second<<endl;
	}
	if (CSVFile.is_open())
	{
		string strCSVData;
		strCSVData.append(strTimeStamp);
		size_t PIDIndex = 0;

		// find the current PID index
		for (size_t indx = 0; indx < Num_Of_PIDs; indx++)
		{
			if (PIDsList[indx] == CurrentPID)
			{
				PIDIndex = indx;
			}
		}

		for (size_t indx = 0; indx <= PIDIndex; indx++)
		{
			strCSVData.append(",");
		}

		if(rx_data_dsi_code == 0)
		{

			it = m_pidDuplicate.find(CurrentPID);
			if(it != m_pidDuplicate.end())
			{
				cout<<"548 newincome FIND PID  DATA  "<<CurrentPID<<" "<<strPIDData <<endl;
				cout<<"549 Old exist           data  "<<it->first<<" "<<it->second<<endl;
				if ((it->second == strPIDData ))
				{
					skipDupliateFlag = 0;
					cout<<"553 Values are same setting flag it ->first"<<it->first<<"it->second  "<<it->second<<"CurrentPID "<<CurrentPID<<" strPIDData  "<<strPIDData<<endl;
				}
				else
				{
					skipDupliateFlag = 1;
					strCSVData.append(strPIDData);
					it->second = strPIDData;

					cout<<"563 values are different it ->first "<<it->first<<" it->second  "<<it->second<<"CurrentPID  "<<CurrentPID<<"strPIDData "<<strPIDData<<endl;
				}
				map<uint32_t, string>::iterator itr4;
				for (itr4 = m_pidDuplicate.begin(); itr4 != m_pidDuplicate.end(); ++itr4)
				{
					cout<<"568 After udpate in MAP itr4->first  "<<itr4->first<<" itr4->second "<<itr4->second<<endl;
				}
			}
			else
			{
				m_pidDuplicate.insert(pair<uint32_t, string>(CurrentPID,strPIDData));
				skipDupliateFlag =1;
				strCSVData.append(strPIDData);
				map<uint32_t, string>::iterator itr4;
				for (itr4 = m_pidDuplicate.begin(); itr4 != m_pidDuplicate.end(); ++itr4)
				{
					cout<<"578 newly write in MAP itr4->first"<<itr4->first<<" itr4->second "<<itr4->second<<endl;
				}
			}

		}
		else
		{
			it = m_pidDuplicate.find(CurrentPID);
			if(it != m_pidDuplicate.end())
			{
				if ((it->second == strDSI_Code )) //PrevData == dlParam.GetLastValue<unsigned_32>() ) && (PrevPID == CurrentPID))
				{
					skipDupliateFlag = 0;
					cout<<"591 Values are same setting flag it ->first "<<it->first<<" it->second "<<it->second<<" CurrentPID "<<CurrentPID<<"strDSI "<<strDSI_Code<<endl;
				}
				else
				{
					skipDupliateFlag = 1;
					strCSVData.append(strDSI_Code);
					it->second = strDSI_Code;
				}
			}
			else
			{
				m_pidDuplicate.insert(pair<uint32_t, string>(CurrentPID,strDSI_Code));
				skipDupliateFlag =1;
				strCSVData.append(strDSI_Code);
			}

		}

		// file writing

		if(skipDupliateFlag)
		{
			cout<<"613 writing into file "<<strCSVData<<endl;
			skipDupliateFlag = 0;
			CSVFile << strCSVData <<"\n";
		}
		else
		{
			AIS_LOG_INFO("skip writing into file");
		}

		CSVFile.close();
		map<uint32_t, string>::iterator itr;
		for (itr = m_pidDuplicate.begin(); itr != m_pidDuplicate.end(); ++itr)
		{
			cout<<"end starting itr->first"<<itr->first<<"  itr->second "<< itr->second<<endl;
		}

		ifstream f("/opt/tmp/outputFiles/AutomationData.csv");
		if(f.good())
		{
			//f.close();
			struct stat fileStatus;
			if(!stat("/opt/tmp/outputFiles/AutomationData.csv",&fileStatus))
			{
				AIS_LOG_INFO("--++--  file %d",fileStatus.st_size);
			}
			else
			{
				AIS_LOG_INFO("--- ---failed file size");
			}
		}
		else
		{
			AIS_LOG_INFO("AutomationData file does not exist");
		}
	}

	else
	{
		AIS_LOG_INFO("Unable to open AutomationData.csv.\n");
	}
}
