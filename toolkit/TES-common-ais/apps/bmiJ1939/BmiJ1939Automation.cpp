////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: BmiJ1939Automation
//
// File Name: BmiJ1939Automation.cpp
//
//  Abstract: Implementation of the class that handles
//            the SCS objects for this application
//
////////////////////////////////////////////////////////

#include "BmiJ1939Automation.h"


#include <string>
#include <time.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <sys/stat.h>

using namespace std;

#define GMT_YEAR_OFFSET  ((uint16_t)1900)
#define GMT_MONTH_OFFSET  ((unsigned_8)0x01)
#include <boost/lexical_cast.hpp>

/* Real Time */
time_t 	CurrentTime;
tm*		GMTime;
char ProductId[8];

#define F82D 63533
#define F84D 63565
#define FA27 64039

#define EEC_1	0xF004
#define EEC_2	0xF003
#define ETC_1	0xF002
#define ETC_2	0xF005
#define EBC_1	0xF001

std::string CSVFilePath = "/opt/tmp/outputFiles/AutomationData_J1939.csv";
static std::ofstream CSVFile;
size_t Num_Of_PIDs, Num_Of_PGNs;
static std::vector<uint32_t> PIDsList, ReqType;
typedef std::vector<BmiJ1939Config::PGNTableEntry_t> PGNTableEntries_t;
typedef std::vector<BmiJ1939Config::CDLPIDTableEntry_t> CDLPIDTableEntries_t;
PGNTableEntries_t PGNConfigTbl;
CDLPIDTableEntries_t ConfigPGBPidTbl, ConfigReadPollPidTbl, ConfigADTPidTbl, ConfigMapPidTbl;



void BmiJ1939Automation::AutomationInitialise(const BmiJ1939Config& appConfig)
{
	AIS_LOG_INFO("AutomationDataWriting Initialization");

	string Automation_CSV_Header;
	Automation_CSV_Header.append("TimeStamp,Request Type,Param Identifier,");

	PGNConfigTbl = appConfig.GetConfiguredPGNs();
	ConfigPGBPidTbl = appConfig.GetConfiguredPGBPIDs();
	ConfigReadPollPidTbl = appConfig.GetConfiguredReadPIDs();
	ConfigADTPidTbl = appConfig.GetConfiguredADTPIDs();
	ConfigMapPidTbl = appConfig.GetConfiguredMapPIDs();

	size_t PGBPidCount, MAPPidCount, ReadPollPidCount, ADTPidCount;

	PGBPidCount = ConfigPGBPidTbl.size();
	MAPPidCount = ConfigMapPidTbl.size();
	ReadPollPidCount = ConfigReadPollPidTbl.size();
	ADTPidCount = ConfigADTPidTbl.size();

	// Find the Total PIDs and PGNs count
	Num_Of_PIDs = PGBPidCount + MAPPidCount + ReadPollPidCount + ADTPidCount;
	Num_Of_PGNs = PGNConfigTbl.size();

	PIDsList.resize(Num_Of_PIDs + Num_Of_PGNs);
	ReqType.resize(Num_Of_PIDs);

	string strPGN;

	for (size_t Indx =0; Indx < PGBPidCount; Indx++)
	{
		uint32_t PIDVal;
		PIDsList[Indx] = PIDVal = ConfigPGBPidTbl.at(Indx).ParameterID;
		ReqType[Indx] = ConfigPGBPidTbl.at(Indx).RequestType;

		stringstream strem; strem <<hex << PIDVal;
		strPGN =  strem.str();
		Automation_CSV_Header.append(strPGN);
		Automation_CSV_Header.append(",");
	}

	for (size_t Indx = 0; Indx < MAPPidCount; Indx++)
	{
		uint32_t PIDVal;
		PIDsList[PGBPidCount+ Indx] = PIDVal = ConfigMapPidTbl.at(Indx).ParameterID;
		ReqType[PGBPidCount+ Indx] = ConfigMapPidTbl.at(Indx).RequestType;
		stringstream strem; strem <<hex << PIDVal;
		strPGN =  strem.str();
		Automation_CSV_Header.append(strPGN);
		Automation_CSV_Header.append(",");

	}

	for (size_t Indx = 0; Indx < ReadPollPidCount; Indx++)
	{
		uint32_t PIDVal;
		PIDsList[PGBPidCount + MAPPidCount+ Indx] = PIDVal = ConfigReadPollPidTbl.at(Indx).ParameterID;
		ReqType[PGBPidCount+ MAPPidCount + Indx] = ConfigReadPollPidTbl.at(Indx).RequestType;
		stringstream strem; strem <<hex << PIDVal;
		strPGN =  strem.str();
		Automation_CSV_Header.append(strPGN);
		Automation_CSV_Header.append(",");

	}

	for (size_t Indx = 0; Indx < ADTPidCount; Indx++)
	{
		uint32_t PIDVal;
		PIDsList[PGBPidCount + MAPPidCount+ Indx] = PIDVal = ConfigADTPidTbl.at(Indx).ParameterID;
		ReqType[PGBPidCount+ MAPPidCount + ReadPollPidCount + Indx] = ConfigADTPidTbl.at(Indx).RequestType;
		stringstream strem; strem <<hex << PIDVal;
		strPGN =  strem.str();
		Automation_CSV_Header.append(strPGN);
		Automation_CSV_Header.append(",");

	}

	for (size_t Indx = 0; Indx < Num_Of_PGNs; Indx++)
	{
		uint32_t PGNVal;
		PIDsList[Num_Of_PIDs + Indx] = PGNVal = PGNConfigTbl.at(Indx).ParameterGroupNumber;
		stringstream strem; strem <<hex << PGNVal;
		strPGN =  strem.str();

		Automation_CSV_Header.append(strPGN);
		Automation_CSV_Header.append(",");
	}


	cout << "Automation_CSV_Header: " <<Automation_CSV_Header<<"\n";
	if(std::remove(CSVFilePath.c_str()) != 0)
	{
		AIS_LOG_FATAL("Not able to delete AutomationData_J1939.csv");
	}
	else
	{
		AIS_LOG_INFO("Successfully deleted AutomationData_J1939.csv");
	}

	CSVFile.open(CSVFilePath.c_str(), std::ofstream::app);

	if (CSVFile.is_open())
	{
		CSVFile << Automation_CSV_Header <<"\n";
	}
	else
	{
		AIS_LOG_FATAL("Unable to open AutomationData_J1939.csv File.\n");
	}
	CSVFile.close();
}


void BmiJ1939Automation::AutomationDataWrite(DataLinkParam& dlParam)
{
	AIS_LOG_INFO("AutomationDataWrite to csv file");
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
	//cout <<"Date==>" << strDate <<"\n"; cout <<"Time==>" << strTime <<"\n";

	strTimeStamp.append(strDate); strTimeStamp.append(" "); strTimeStamp.append(strTime);

	uint32_t CurrentPID = dlParam.GetParamId();
	string strPIDData;

	if ((CurrentPID == F82D) || (CurrentPID == F84D) || (CurrentPID == FA27) ||
			(CurrentPID == EEC_1) || (CurrentPID == EEC_2) || (CurrentPID == ETC_1) ||
			(CurrentPID == ETC_2) || (CurrentPID == EBC_1) )
	{
		const uint8_t* varParamBlock = dlParam.GetVarParamBlock();
		const unsigned_8 varParamBlockSize = dlParam.GetVarParamBlockLength();
		AIS_LOG_INFO("varParamBlockSize: %d\n", varParamBlockSize);
		if (varParamBlockSize != 0)
		{
			char chData[varParamBlockSize + 1];
			for (uint8_t i = 0; i < varParamBlockSize; i++)
			{
				chData[i] = varParamBlock[i];
				AIS_LOG_INFO("ChData: %x\n", varParamBlock[i]);
			}

			chData[varParamBlockSize] = '\0';
			strPIDData = string(chData);
			cout << "strPIDData: " << strPIDData <<"\n";
		}
		else
		{
			strPIDData.append("NA");
		}
	}
	else
	{
		strPIDData = boost::lexical_cast<string>(dlParam.GetLastValue<unsigned_32>());
		AIS_LOG_INFO("CSVWrite Data: Pid %x, Data: %d\n", dlParam.GetParamId(), dlParam.GetLastValue<unsigned_32>());
	}

	// File open in Append mode
	CSVFile.open(CSVFilePath.c_str() , std::ofstream::app);
	static bool skipDuplicateFlag =0;
	map<uint32_t, string>::iterator it;
	map<uint32_t, string>::iterator itr1;
	for (itr1 = m_pidDuplicate.begin(); itr1 != m_pidDuplicate.end(); ++itr1)
	{
		cout<<"522 before starting itr1->first   itr1->second "<<itr1->first<< itr1->second<<endl;
	}

	if (CSVFile.is_open())
	{
		string strCSVData, strReqType;
		size_t PIDIndex = 0;
		strCSVData.append(strTimeStamp);
		strCSVData.append(",");

		AIS_LOG_INFO("Num_Of_PIDs: %d Num_Of_PGNs: %d\n", Num_Of_PIDs, Num_Of_PGNs);
		// find the current PID index
		for (size_t indx = 0; indx < (Num_Of_PIDs + Num_Of_PGNs); indx++)
		{
			if (PIDsList[indx] == CurrentPID)
			{
				PIDIndex = indx;
			}
		}
		AIS_LOG_INFO("PIDIndex: %d", PIDIndex);

		if (dlParam.GetParamIdentifierType() == DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_PID)
		{

			uint32_t RequstType = ReqType[PIDIndex];
			if (RequstType == 0)
			{
				strCSVData.append("SPB_Request,");
			}
			else if (RequstType == 1)
			{
				strCSVData.append("PGB_Request,");
			}
			else if(RequstType == 2)
			{
				strCSVData.append("ADT_Request,");
			}
			else if(RequstType == 3)
			{
				strCSVData.append("Read_Poll_Request,");
			}
			else if(RequstType == 4)
			{
				strCSVData.append("MAP_Request,");
			}
			else
			{
				strCSVData.append("Invalid_Request,");
			}
			strCSVData.append("PID");
		}
		else if(dlParam.GetParamIdentifierType() == DataLinkParam::DATA_LINK_PARAM_IDENTIFIER_PUBLIC_PGN)
		{
			strCSVData.append(",Public PGN");
			AIS_LOG_INFO("Public PGN: %x\n",dlParam.GetParamId());
		}


		for (size_t indx = 0; indx <= PIDIndex; indx++)
		{
			strCSVData.append(",");
		}
		it = m_pidDuplicate.find(CurrentPID);
		if(it != m_pidDuplicate.end())
		{
			cout<<"548 newincome FIND PID  DATA  "<<CurrentPID<<" "<<strPIDData <<endl;
			cout<<"549 Old exist           data  "<<it->first<<" "<<it->second<<endl;
			if ((it->second == strPIDData ))
			{
				skipDuplicateFlag = 0;
				cout<<"553 Values are same setting flag it ->first"<<it->first<<"it->second  "<<it->second<<"CurrentPID "<<CurrentPID<<" strPIDData  "<<strPIDData<<endl;
			}
			else
			{
				skipDuplicateFlag = 1;
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
			skipDuplicateFlag =1;
			strCSVData.append(strPIDData);
			map<uint32_t, string>::iterator itr4;
			for (itr4 = m_pidDuplicate.begin(); itr4 != m_pidDuplicate.end(); ++itr4)
			{
				cout<<"578 newly write in MAP itr4->first"<<itr4->first<<" itr4->second "<<itr4->second<<endl;
			}
		}
		if(skipDuplicateFlag)
		{
			cout<<"613 writing into file "<<strCSVData<<endl;
			skipDuplicateFlag = 0;
			CSVFile << strCSVData <<"\n";
			cout <<  "strCSVData=>" << strCSVData << "\n";
		}
		else
		{
			AIS_LOG_INFO("skip writing into file");
		}
			// file writing


		CSVFile.close();
		map<uint32_t, string>::iterator itr;
		for (itr = m_pidDuplicate.begin(); itr != m_pidDuplicate.end(); ++itr)
		{
			cout<<"end starting itr->first"<<itr->first<<"  itr->second "<< itr->second<<endl;
		}

		ifstream f("/opt/tmp/outputFiles/AutomationData.csv");
		if(f.good())
		{
			f.close();
			struct stat fileStatus;
			stat("opt/tmp/outputFiles/AutomationData.csv",&fileStatus);
			if(fileStatus.st_size > 10)
			{
				AIS_LOG_INFO(" file %d",fileStatus.st_size);
				//system("rm /opt/appdata/OMMST/ommstLog.txt");
			}
			else
			{
				AIS_LOG_FATAL(" AutomationData not deleted, file size %d",fileStatus.st_size);
			}
		}
		else
		{
			AIS_LOG_FATAL("AutomationData file does not exist");
		}
	}
	else
	{
		AIS_LOG_FATAL("Unable to open AutomationData.csv.\n");
	}
}
