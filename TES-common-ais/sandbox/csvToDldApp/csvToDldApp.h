////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Caterpillar Inc.  All Rights Reserved.
//
//     Class: csvToDldApp
//
// File Name: csvToDldApp.h
//
//  Abstract: SCS Input Simulator class declarations
//
////////////////////////////////////////////////////////

#ifndef CSVTODLDAPP_H
#define CSVTODLDAPP_H

#include <mutex>
#include <queue>
#include <cat_std_types.h>
#include <ais/time/EventTimer.h>
#include <csvUtil/CsvReader.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>

using ethS7ParamRow = std::vector<DataLinkParam>;

class csvToDldApp : public task::Task
{
public:
   struct CsvParamInfo
   {
      std::string name;
      unsigned_32 PID;
      DataLinkParamInfo::DlpParamIdentifierType_t paramIdType;
   };

   csvToDldApp(const std::string &taskName);
   virtual ~csvToDldApp() {}
   virtual bool initialize();
   virtual bool executive();
   virtual void cleanup();  

private:
   CsvReader m_CsvReader;
   unsigned_8 m_CsvBufferSize;
   unsigned_8 m_NonStop;
   unsigned_8 m_CsvDataFormat;
   std::string m_csvFilePath;
   std::mutex m_InputDataLock;
   DataLinkDataOutput *m_pScsChannelOutputDataLink;
   unsigned_32 m_CounterOutputCDL;
   std::queue<ethS7ParamRow> m_DataBuffer;
   EventTimer m_OutputDataLinkTimer;
   unsigned_32 m_OutputRateChannelOutputDataLink;
   std::vector<std::string> m_CsvFiles;
   std::vector<CsvParamInfo> m_CsvHeader;

   void PublishDatLinkData();
   void QueueDataLinkData(unsigned_32 pId, real_64 paramValue, std::string paramName);
   DataLinkParam CreateFloatParameter(unsigned_32 sourceId,
                                    const CsvParamInfo& paramStruct,
                                    real_64 paramValue,
                                    real_32 paramScaling,
                                    real_32 paramOffset);
   DataLinkParam CreateCDLOpIdParameter(unsigned_32 sourceId,
                                              unsigned_32 pId,
                                              std::string paramName,
                                              std::string operatorName);
   DataLinkParam CreateCDLProdIdParameter(unsigned_32 sourceId,
                                              unsigned_32 pId,
                                              std::string paramName,
                                              std::string productId);
   DataLinkParam CreateCDLGpsParameter(unsigned_32 sourceId,
                                              unsigned_32 pId,
                                              std::string paramName,
                                              uint8_t gpsStatus,
                                              double gpsLat,
                                              double gpsLong);
   std::vector<std::string> ReadFilesFromDirectory( const std::string& dirPath);
   void ReadCsvParamInfo();


};

#endif // INPUTSIM_H
