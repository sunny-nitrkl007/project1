////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: csvToDldApp
//
// File Name: csvToDldApp.cpp
//
//  Abstract: SCS Input Simulator class implementation
//
////////////////////////////////////////////////////////

#include <math.h>
#include <ais/task/Task.h>
#include <catdllib_pid_def.h>
#include <boost/algorithm/string/trim.hpp>   // for trim()
#include <boost/math/special_functions/sign.hpp>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

#include "csvToDldApp.h"

#define BMI_DATA_STATUS_OK 0 // DSI value for "good" DL value
#define GOOD_DATA_MERIT 0x00

std::vector<csvToDldApp::CsvParamInfo> csvHeader;

void csvToDldApp::ReadCsvParamInfo()
{
   // read in Column Name and PID from .csv file
   for (int32_t csvColIndex = 0; csvColIndex < m_CsvReader.getNumColumns(); csvColIndex++)
   {
      CsvParamInfo columnData;
      columnData.name   = m_CsvReader.getColumnName(csvColIndex);
      // 2nd row is always (ParamIdType) for the first byte, Param ID for the last 3 bytes, MUST be HEX
      uint32_t paramTypeId = std::stoul(m_CsvReader.getTextValue(0, csvColIndex), 0, 16);
      columnData.PID = paramTypeId & 0xFFFFFF;
      columnData.paramIdType = static_cast<DataLinkParamInfo::DlpParamIdentifierType_t>((paramTypeId >> 24) & 0x00FF);
      csvHeader.push_back(columnData);
      AIS_LOG_FATAL("%d : Name:%s, ParamIdentifierType:%u, ID:0x%02X", csvColIndex, columnData.name.c_str(), columnData.paramIdType, columnData.PID);
   }
}

////////////////////////////////////////////////////////////////////////
// Function        : task::getTaskImplementation
// Description     : Wrapper for a task. Creates an instance of the app
//                   class and returns a context pointer
// Return Type     : task::AbstractTaskCore* - Task attributes
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////
task::AbstractTaskCore *task::getTaskImplementation(void)
{
   static csvToDldApp thisTask("csvToDldApp");
   return dynamic_cast<task::Task *>(&thisTask);
}

////////////////////////////////////////////////////////////////////////
// Function        : csvToDldApp::csvToDldApp
// Description     : Class constructor
// Return Type     : N/A
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////
csvToDldApp::csvToDldApp(const std::string &taskName) : task::Task(taskName),
                                                        m_pScsChannelOutputDataLink(nullptr),
                                                        m_CounterOutputCDL(0)
{
   m_OutputDataLinkTimer.connect(boost::bind(&csvToDldApp::PublishDatLinkData, this));
}

////////////////////////////////////////////////////////////////////////
// Function        : csvToDldApp::initialize
// Description     : Parses app configuration, initializes the SCS objects,
//                   and hooks the CSV spreadsheet with the data
// Return Type     : bool - 'true' if initialization was successful, 'false' otherwise
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////
#define FETCH_INTERFACE(pObj, ifName) (nullptr != (pObj = dynamic_cast<decltype(pObj)>(task::InterfaceDb::fetch(ifName))))
#define FETCH_OR_COMPLAIN(pObj, ifName, failStorage)      \
   if (!FETCH_INTERFACE(pObj, ifName))                    \
   {                                                      \
      failStorage = false;                                \
      AIS_LOG_FATAL("Failed to fetch interface '%s'", ifName) \
   }

bool csvToDldApp::initialize(void)
{
   std::lock_guard<std::mutex> lock(m_InputDataLock);

   bool initStatusOk = true; // Assume success

   ConfigSection cfgSection;

   AIS_LOG_WARN("App initialize() start");

   // Parse Ruby configuration file
   if (!getTaskParser().getSection("SimConfig", cfgSection))
   {
      AIS_LOG_FATAL("Unable to obtain configuration section 'SimConfig' from Ruby file");
      initStatusOk = false;
   }

   AIS_LOG_WARN("App initialize() start 1");

   if (!cfgSection.get("Input CSV Directory", m_csvFilePath))
   {
      AIS_LOG_FATAL("Unable to find parameter 'Input CSV file' in configuration section 'SimConfig'");
      initStatusOk = false;
   }

   AIS_LOG_WARN("App initialize() start 2");

   if (!cfgSection.get("CSV Buffer Size", m_CsvBufferSize))
   {
      AIS_LOG_FATAL("Unable to find parameter 'CSV Buffer Size' in configuration section 'SimConfig'");
      initStatusOk = false;
   }

   m_CsvFiles = ReadFilesFromDirectory(m_csvFilePath);
   AIS_LOG_DEBUG(".csv files found: %d", m_CsvFiles.size());      

   if (0 != m_CsvFiles.size())
   {
      for(size_t i=0; i<m_CsvFiles.size(); i++)
      {
         AIS_LOG_INFO("GOOD:%s", m_CsvFiles[i].c_str());   
      }

   }
   else
   {
      AIS_LOG_FATAL("No .csv files found: %d", m_CsvFiles.size());
      initStatusOk = false;
   } 

   AIS_LOG_WARN("App initialize() start 3");

    if (!cfgSection.get("NonStop", m_NonStop))
   {
      AIS_LOG_FATAL("Unable to find parameter 'NonStop' in configuration section 'SimConfig'");
      initStatusOk = false;
   }

    if (!cfgSection.get("CsvDataFormat", m_CsvDataFormat))
   {
      m_CsvDataFormat = 1; // default to Decimal Data in .csv file, backward compatible 
   }

   AIS_LOG_WARN("App initialize() start 4");

    if (!cfgSection.get("Output Rate (ms) SCS CDL", m_OutputRateChannelOutputDataLink))
   {
      AIS_LOG_FATAL("Unable to find parameter 'Output Rate (ms) SCS CDL' in configuration section 'SimConfig'");
      initStatusOk = false;
   }

   AIS_LOG_WARN("App initialize() start 5");

    if (!m_CsvReader.load(m_CsvFiles[0]))
   {
      AIS_LOG_FATAL("Unable to load CSV file %s", m_CsvFiles[0].c_str());
      initStatusOk = false;
   }
   else
   {
      AIS_LOG_FATAL("Loaded CSV File %s    size:%d", m_CsvFiles[0].c_str(), m_CsvReader.getNumRows());
   }
   

   AIS_LOG_WARN("App initialize() start 6");


    if (3 > m_CsvReader.getNumRows())
   {
      AIS_LOG_FATAL("Not enought Rows:%d ", m_CsvReader.getNumRows());
      initStatusOk = false;
   }

   // read in Column Name and PID from .csv file
   ReadCsvParamInfo();
   AIS_LOG_FATAL("Loaded CSV File %s    size:%d", m_CsvFiles[0].c_str(), m_CsvReader.getNumRows());  // reprint to see how many records

   // Fetch all interfaces
   //FETCH_OR_COMPLAIN(m_pScsChannelOutputDataLink, "DataLinkDataOutput", initStatusOk);

   AIS_LOG_WARN("App initialize() start 7");

   if (!task::InterfaceDb::bind("DataLinkDataOutput", m_pScsChannelOutputDataLink))
   {
      initStatusOk = false;
   }

   // Start the transmit threads/timers
   if (initStatusOk)
   {
      m_OutputDataLinkTimer.setInterval(m_OutputRateChannelOutputDataLink);
      m_OutputDataLinkTimer.start();

      AIS_LOG_WARN("App initialized successfully");
   }

   return initStatusOk;
}

////////////////////////////////////////////////////////////////////////
// Function        : csvToDldApp::executive
// Description     : Reads inputs from the CSV file
// Return Type     : bool - 'false' if there's no more data to process,
//                   'true' otherwise
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////
bool csvToDldApp::executive()
{
   bool execSuccessful = true;

   static unsigned_32 csvFileIndex = 0;
   static unsigned_32 csvFileCounter = 0;
   static unsigned_32 csvRowIndex = 1;
   unsigned_32 csvNumberOfRows = m_CsvReader.getNumRows();

   // PID: 63563 = gps_status, 63564 = gps_lat, 63565 = gps_long MUST be last in .csv file
   uint8_t gpsStstaus = 1; // default to invalid
   double  gpsLat = 0.0f; // default to 0.0
   double  gpsLong = 0.0f; // default to 0.0


   // Have we reached the end of CSV file?

   if ((m_DataBuffer.size() < m_CsvBufferSize) && (csvRowIndex < csvNumberOfRows))  // check buffer size AND Rows
   {
      ethS7ParamRow row;

      for (int32_t col = 0; col < m_CsvReader.getNumColumns(); col++)
      {
         if (0.0 != csvHeader[col].PID)   // ignore anything with 0 as ID
         {
		      if (61618 == csvHeader[col].PID)   // 0xF0B2 = 61618  OperatorID
		      {
               DataLinkParam ethS7ParamCol = CreateCDLOpIdParameter(0xFF, csvHeader[col].PID, csvHeader[col].name, m_CsvReader.getTextValue(csvRowIndex, col));
               row.push_back(ethS7ParamCol);
		         AIS_LOG_INFO("col:%d, row:%d : Name:%s, PID:%x  OpId:%s", col, csvRowIndex, csvHeader[col].name.c_str(), csvHeader[col].PID, m_CsvReader.getTextValue(csvRowIndex, col).c_str());
		      }
		      else if (63533 == csvHeader[col].PID)   // 0xF82D = 63533  ProductID
		      {
               DataLinkParam ethS7ParamCol = CreateCDLProdIdParameter(0xFF, csvHeader[col].PID, csvHeader[col].name, m_CsvReader.getTextValue(csvRowIndex, col));
               row.push_back(ethS7ParamCol);
		         AIS_LOG_INFO("col:%d, row:%d : Name:%s, PID:%x  ProdID:%s", col, csvRowIndex, csvHeader[col].name.c_str(), csvHeader[col].PID, m_CsvReader.getTextValue(csvRowIndex, col).c_str());
		      }
            else if( 63563 == csvHeader[col].PID)  // 0xF84B used for GPS - STATUS
            {
               gpsStstaus = static_cast<uint8_t>(m_CsvReader.getNumericalValue(csvRowIndex, col));
            }
            else if (63564 == csvHeader[col].PID)  // 0xF84C used for GPS - LAT
            {
               gpsLat = m_CsvReader.getNumericalValue(csvRowIndex, col);
            }
            else if (63565 == csvHeader[col].PID)  // 0xF84D = csvHeader[col].PID   GPS
            {
               gpsLong = m_CsvReader.getNumericalValue(csvRowIndex, col);
               DataLinkParam ethS7ParamCol = CreateCDLGpsParameter(0xFF, csvHeader[col].PID, csvHeader[col].name, gpsStstaus, gpsLat, gpsLong);
               row.push_back(ethS7ParamCol);
		         AIS_LOG_INFO("col:%d, row:%d : Name:%s, PID:%x  GPS:%d %f %f", col, csvRowIndex, csvHeader[col].name.c_str(), csvHeader[col].PID, gpsStstaus, gpsLat, gpsLong);
            }
		      else   // process as Float...   default
		      {
               double paramTypeId = 0.0f;  // default to 0.0

               if (1 == m_CsvDataFormat)  // decimal data format
               {
                  paramTypeId = m_CsvReader.getNumericalValue(csvRowIndex, col);
               }
               else if (2 == m_CsvDataFormat)   // 2 byte HEX data format
               {
                  //uint32_t temp;
                  //temp  = std::stoul(m_CsvReader.getTextValue(csvRowIndex, col), 0, 16);
                  AIS_LOG_INFO("value:%s", m_CsvReader.getTextValue(csvRowIndex, col).c_str());
                  uint32_t paramTypeId_int = std::stoul(m_CsvReader.getTextValue(csvRowIndex, col), 0, 16);
                  if (0x7FF < paramTypeId_int)
                  {
                     paramTypeId = static_cast<double>(0xFFFF - static_cast<uint16_t>(paramTypeId_int) +1);
                     paramTypeId *= -1.0f; // make it negative
                  }
                  else
                  {
                     paramTypeId = static_cast<double>(paramTypeId_int);
                  }
                  AIS_LOG_INFO("value:0x%x   = %f", paramTypeId_int, paramTypeId);
               }
               else
               {
                  AIS_LOG_ALERT("CsvDataFormat Not Supported: %d", m_CsvDataFormat);
               }

               DataLinkParam ethS7ParamCol = CreateFloatParameter(0xFF,
                                                            csvHeader[col],
                                                            paramTypeId,
                                                            1.0,
                                                            0.0);                  
               row.push_back(ethS7ParamCol);

		         AIS_LOG_INFO("col:%d, row:%d : Name:%s, PID:%x  Float:%2.2f", col, csvRowIndex, csvHeader[col].name.c_str(), csvHeader[col].PID, ethS7ParamCol.GetLastGoodValueEng());
		      }
         }
      }

      {
         std::lock_guard<std::mutex> lock(m_InputDataLock);
         m_DataBuffer.push(row);

         // Every once in a while print something to console
         if (0 == (csvRowIndex %50))
         {
            AIS_LOG_WARN("[%u ms] Processed %s %u/%u %u:loop  %u/%u rows in the CSV file. %u DL sets sent. Buffer has %u elements",
                     static_cast<unsigned_32>(commonNow().toDouble() * 1000),
                     m_CsvFiles[csvFileIndex].c_str(),
                     (csvFileIndex+1),
                     m_CsvFiles.size(),
                     csvFileCounter,
                     csvRowIndex,
                     csvNumberOfRows,
                     m_CounterOutputCDL,
                     m_DataBuffer.size());
         }
      }

   csvRowIndex++;

      if ((csvRowIndex == csvNumberOfRows))  // come to end of file, do we reset and keep going again?
      {
         csvFileIndex++;   // increment to next file
         if (csvFileIndex >= m_CsvFiles.size())
         {
            csvFileIndex = 0;
            if (0 == m_NonStop)
            {
               AIS_LOG_FATAL("Done processing all files");
               return false;
            }
         }

         if (!m_CsvReader.load(m_CsvFiles[csvFileIndex]))
         {
            AIS_LOG_FATAL("Unable to load CSV file %s", m_CsvFiles[csvFileIndex].c_str());
            return false;
         }
         else
         {
            csvNumberOfRows = m_CsvReader.getNumRows();
            AIS_LOG_FATAL("Loaded CSV File %s    size:%d", m_CsvFiles[csvFileIndex].c_str(), csvNumberOfRows);
         }
         
         if (3 > m_CsvReader.getNumRows())
         {
            AIS_LOG_FATAL("Not enought Rows:%d ", m_CsvReader.getNumRows());
            return false;
         }

         // read in Column Name and PID from next .csv file
         ReadCsvParamInfo();
         AIS_LOG_FATAL("Loaded CSV File %s    size:%d", m_CsvFiles[csvFileIndex].c_str(), csvNumberOfRows);  // reprint to see how many records

	      csvFileCounter++;
  	      csvRowIndex = 1;     // move index to starting row of data
      }
   }

   return execSuccessful;
}

////////////////////////////////////////////////////////////////////////
// Function        : csvToDldApp::CreateFloatParameter
// Description     : Assembles parameter with the provided data
// Return Type     : DataLinkParam - Assembled parameter
// Argument [in]   : Provided data
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////
DataLinkParam csvToDldApp::CreateFloatParameter(unsigned_32 sourceId,
                                              const CsvParamInfo& paramStruct,
                                              real_64 paramValue,
                                              real_32 paramScaling,
                                              real_32 paramOffset)
{
   DataLinkParam dlParam;
   double intPart = 0;
   double fractionalPart = 0.0;
   

   dlParam.SetParameterName(paramStruct.name);
   dlParam.SetSid(sourceId);
   dlParam.SetParamId(paramStruct.PID);
   
   if(boost::math::signbit(paramValue))
   {
      dlParam.SetParameterType(CDL2_I32_NO_DSI);
   }
   else
   {
      dlParam.SetParameterType(CDL2_U32_NO_DSI);
   }
   dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::NOT_APPLICABLE);
   dlParam.SetParamIdentifierType(paramStruct.paramIdType);
   dlParam.SetScaling(paramScaling);   
   dlParam.SetUnits(DataLinkParam::DATA_LINK_PARAM_CDL_UNITS_NO_UNIT);
   fractionalPart = modf(paramValue, &intPart);
   // dlParam.SetOffset(fractionalPart);
   dlParam.SetOffset(paramOffset);
   dlParam.SetLastValue(intPart, BMI_DATA_STATUS_OK, true);

   AIS_LOG_DEBUG("%s: input value : %f, datatype %d, dl param value eng: %f last good eng: %f",
            paramStruct.name.c_str(),
            paramValue, 
            dlParam.GetParameterType(),
            dlParam.GetLastValueEng(),
            dlParam.GetLastGoodValueEng());

   return dlParam;
}

////////////////////////////////////////////////////////////////////////
// Function        : csvToDldApp::CreateCDLOpIdParameter
// Description     : Assembles CDL parameter with the provided data
// Return Type     : DataLinkParam - Assembled parameter
// Argument [in]   : Provided data
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////
DataLinkParam csvToDldApp::CreateCDLOpIdParameter(unsigned_32 sourceId,
                                              unsigned_32 pId,
                                              std::string paramName,
                                              std::string operatorName)
{
   std::vector<uint8_t> genericOpId = {0xF0, 0xB2, 0x01, 0x01, 0x00, 0x00, 0x00, 0x07, 0x00, 0x96, 0xBC, 0x5C, 0x64, 0x4A, 0x88, 0xCC};

   DataLinkParam dlParam;  

   dlParam.SetParameterName(paramName);
   dlParam.SetSid(sourceId);
   dlParam.SetParamId(pId);
   dlParam.SetScaling(1.0);   
   dlParam.SetOffset(0.0);  
   dlParam.SetParameterType(CDL2_VAR_NO_DSI);
	dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::CAT_EXT);
   dlParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_CAT_EXT);

   AIS_LOG_DEBUG("length:%d  name:%s", operatorName.size(), operatorName.c_str());
   boost::algorithm::trim(operatorName);  // remove any White Space bytes
   genericOpId[8] = operatorName.size();  // update string length
   genericOpId.insert(genericOpId.end(), operatorName.begin(), operatorName.end()); // append name string to the end

	dlParam.SetVarLengthParamValue(genericOpId, 0);

   return dlParam;
}

////////////////////////////////////////////////////////////////////////
// Function        : csvToDldApp::CreateCDLProdIdParameter
// Description     : Assembles CDL parameter with the provided data
// Return Type     : DataLinkParam - Assembled parameter
// Argument [in]   : Provided data
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////
DataLinkParam csvToDldApp::CreateCDLProdIdParameter(unsigned_32 sourceId,
                                              unsigned_32 pId,
                                              std::string paramName,
                                              std::string productId)
{
   std::vector<uint8_t> genericProdId;

   DataLinkParam dlParam;  

   dlParam.SetParameterName(paramName);
   dlParam.SetSid(sourceId);
   dlParam.SetParamId(pId);
   dlParam.SetScaling(1.0);   
   dlParam.SetOffset(0.0);  
   dlParam.SetParameterType(CDL2_VAR_NO_DSI);
	dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::PRODUCT_ID);
   dlParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);

   boost::algorithm::trim(productId);  // remove any White Space bytes
   productId.append(8 - productId.length(), ' ');  // append 0x20 if not 8 bytes long

   genericProdId.insert(genericProdId.end(), productId.begin(), productId.end()); // append name string to the end

	dlParam.SetVarLengthParamValue(genericProdId, 0);

   AIS_LOG_DEBUG("length:%d  name:%s", productId.size(), productId.c_str());

   return dlParam;
}

////////////////////////////////////////////////////////////////////////
// Function        : csvToDldApp::CreateCDLGpsParameter
// Description     : Assembles CDL parameter with the provided data
// Return Type     : DataLinkParam - Assembled parameter
// Argument [in]   : Provided data
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////
DataLinkParam csvToDldApp::CreateCDLGpsParameter(unsigned_32 sourceId,
                                              unsigned_32 pId,
                                              std::string paramName,
                                              uint8_t gpsStatus,
                                              double gpsLat,
                                              double gpsLong)
{
   std::vector<uint8_t>  GPS_s = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

   DataLinkParam dlParam;
   uint32_t convertedIntLat  = static_cast<uint32_t>(gpsLat / 0.0000107288360596f);
   uint32_t convertedIntLong = static_cast<uint32_t>(gpsLong / 0.0000214576721191f);

   dlParam.SetParameterName(paramName);
   dlParam.SetSid(sourceId);
   dlParam.SetParamId(0xF84D);   // Product Link Module GPS Position Status
   dlParam.SetScaling(1.0);   
   dlParam.SetOffset(0.0); 
   dlParam.SetParameterType(CDL2_VAR_NO_DSI);
	dlParam.SetVarLengthParamType(VarLengthDataLinkParamPool::GPS);
   dlParam.SetParamIdentifierType(DataLinkParamInfo::DATA_LINK_PARAM_IDENTIFIER_PID);

   GPS_s[7] = gpsStatus;  // GPS-Status

    if (4 == gpsStatus)	// make TIME stamp all 0xFFs
    {
       GPS_s[1] = 0xFF;
       GPS_s[2]  = 0xFF;
       GPS_s[3]  = 0xFF;
       GPS_s[4] = 0xFF;
       GPS_s[5]  = 0xFF;
       GPS_s[6]  = 0xFF;
    
       GPS_s[7] = 2;           // GPS-Status,   2 = POSITION_CALCULATION_INCOMPLETE
    }
    else if (5 == gpsStatus)	// make LAT & LONG all 0xFFs
    {
       GPS_s[10] = 0xFF;
       GPS_s[9]  = 0xFF;
       GPS_s[8]  = 0xFF;
       GPS_s[13] = 0xFF;
       GPS_s[12]  = 0xFF;
       GPS_s[11]  = 0xFF;

       GPS_s[7] = 2;           // GPS-Status,   2 = POSITION_CALCULATION_INCOMPLETE
    }
    else if (6 == gpsStatus)	// make ALL  0xFFs
    {
       GPS_s[0] = 0xFF;
       GPS_s[1] = 0xFF;
       GPS_s[2]  = 0xFF;
       GPS_s[3]  = 0xFF;
       GPS_s[4] = 0xFF;
       GPS_s[5]  = 0xFF;
       GPS_s[6]  = 0xFF;
       GPS_s[7]  = 0xFF;
       GPS_s[10] = 0xFF;
       GPS_s[9]  = 0xFF;
       GPS_s[8]  = 0xFF;
       GPS_s[13] = 0xFF;
       GPS_s[12]  = 0xFF;
       GPS_s[11]  = 0xFF;
    }
    else
    {
       GPS_s[10] = (convertedIntLat & 0x000000ff);
       GPS_s[9]  = (convertedIntLat & 0x0000ff00) >> 8;
       GPS_s[8]  = (convertedIntLat & 0x00ff0000) >> 16;
       //GPS_s[10] = (convertedIntLat & 0xff000000) >> 24;   // only uses 3 bytes

       GPS_s[13] = (convertedIntLong & 0x000000ff);
       GPS_s[12] = (convertedIntLong & 0x0000ff00) >> 8;
       GPS_s[11] = (convertedIntLong & 0x00ff0000) >> 16;
       //GPS_s[13] = (convertedIntLong & 0xff000000) >> 24;   // only uses 3 bytes
    }

    dlParam.SetVarLengthParamValue(GPS_s, 0);

    AIS_LOG_FATAL("GPS: %x %x %x %x %x %x %x %x %x %x %x %x %x %x", GPS_s[0], GPS_s[1], GPS_s[2], GPS_s[3], GPS_s[4], GPS_s[5], GPS_s[6], GPS_s[7], GPS_s[8], GPS_s[9], GPS_s[10], GPS_s[11], GPS_s[12], GPS_s[13]); 

   return dlParam;
}

void csvToDldApp::PublishDatLinkData()
{
   std::lock_guard<std::mutex> lock(m_InputDataLock);

   if (m_DataBuffer.size() > 0)
   {
      ethS7ParamRow dlParamRow = m_DataBuffer.front();

      //std::cout << "\n";

      DataLinkData dlData;
      for (DataLinkParam dlParam : dlParamRow)
      {
         dlData.AddDataLinkParam(dlParam);
         //std::cout << dlParam.GetLastValueEng() << " ";
      }
            
      m_pScsChannelOutputDataLink->publish(dlData);
      m_CounterOutputCDL++;

      m_DataBuffer.pop();

      if (m_CounterOutputCDL % 500 == 0)
      {
         AIS_LOG_WARN("Quesize %d Publish count %d", m_DataBuffer.size(), m_CounterOutputCDL);
      }
   }
   else
   {
      AIS_LOG_WARN("DLD Queue is empty.");
   }
}

////////////////////////////////////////////////////////////////////////
// Function        : csvToDldApp::cleanup
// Description     : Runs the clean-up routines for the app
// Return Type     : None
// Argument [in]   : None
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////
void csvToDldApp::cleanup()
{
   // Stop the transmission timer (and join threads)
   m_OutputDataLinkTimer.stop();
}

////////////////////////////////////////////////////////////////////////////
// Function        : csvToDldApp::ReadFilesFromDirectory
// Description     : Reads the list of the files and their properties in a directory
// Return Type     : std::vector<FileInfo_t> - Container with the obtained files
// Argument [in]   : const std::string& dirPath - The path of the directory to read
//                   CdaFileType_t fileType - Type of files that are of interest
// Argument [out]  : None
// Argument [I/O]  : None
////////////////////////////////////////////////////////////////////////////
std::vector<std::string> csvToDldApp::ReadFilesFromDirectory( const std::string& dirPath)
{
   struct dirent* pDirEntry;
   std::vector<std::string> files;
   DIR* pDirHandle = opendir( dirPath.c_str() );

   if ( nullptr == pDirHandle )
   {
      AIS_LOG_FATAL("Error:%d opening:%s ", errno, dirPath.c_str());
      return files;
   }

   // Read files one by one
   while ( nullptr != ( pDirEntry = readdir( pDirHandle ) ) )
   {
      std::string fileName(pDirEntry->d_name);
      std::string fullPath = dirPath + '/' + fileName;

      if (fileName.find(".csv") != std::string::npos)
      {
         AIS_LOG_INFO("GOOD FILE:%s ", fullPath.c_str());
         files.push_back( fullPath );
      }
      else
      {
         AIS_LOG_INFO("BAD FILE:%s ", fullPath.c_str());
      }
   }

   closedir( pDirHandle );

   return files;
}


