#include <ais/serialization/Datum.h> // For Boost serialization
#include <string>

#ifndef SSSCDATTIBRIDGEREQUEST_H
#define SSSCDATTIBRIDGEREQUEST_H

class FileTransferBridgeRequestStorage : public csvable
{
public:
   enum class FileType : unsigned int
   {
      VP3 = 10129,
      TPMS_CYCLE = 10354,
      TPMS_LOAD = 10355,
      TPMS_DIPPER = 10356,
      TPMS_MODE = 10357,
      TPMS_TKPH = 10446,	
      PCS_CYCLE = 10358,
      PRINT = 10425
   };

   typedef struct ScsCdaTtiBridgeFileAttr_s
   {
      unsigned int TelematicsFileNumber; // File Type
      unsigned int SizeInBytes;
      std::string Name;
      std::string DirPath;
      unsigned long int FidSource;
      unsigned long int FidDestination;

      ScsCdaTtiBridgeFileAttr_s( unsigned int telematicsFileNumber,
            unsigned int sizeInBytes,
            const std::string& fileName,
            const std::string& filePath,
            unsigned long int fidSource,
            unsigned long int fidDestination ):
               TelematicsFileNumber( telematicsFileNumber ),
               SizeInBytes( sizeInBytes ),
               Name( fileName ),
               DirPath( filePath ),
               FidSource( fidSource ),
               FidDestination( fidDestination ) { }
      ScsCdaTtiBridgeFileAttr_s(): ScsCdaTtiBridgeFileAttr_s( 0, 0, "", "", 0, 0 ) { }
   } ScsCdaTtiBridgeFileAttr_t;

   typedef struct ScsCdaTtiBridgeDateTime_s
   {
      int MilliSec{0};
      int Sec{0};
      int Min{0};
      int Hour{0};
      int Day{0};
      int Month{0};
      int Year{0};
   } ScsCdaTtiBridgeDateTime_t;

   ScsCdaTtiBridgeFileAttr_t fileAttr;

   FileTransferBridgeRequestStorage(): fileAttr() { }

   template <class Archive>
   void serialize(Archive &ar, unsigned int version)
   {
      /* Archive Fields Here */
      ar & fileAttr.TelematicsFileNumber;
      ar & fileAttr.Name;
      ar & fileAttr.SizeInBytes;
      ar & fileAttr.DirPath;
      ar & fileAttr.FidSource;
      ar & fileAttr.FidDestination;
   }
   void toCsv(CsvOutStream& out) const
   {
      out("fileAttr.TelematicsFileNumber", fileAttr.TelematicsFileNumber);
      out("fileAttr.Name", fileAttr.Name);
      out("fileAttr.SizeInBytes", fileAttr.SizeInBytes);
      out("fileAttr.DirPath", fileAttr.DirPath);
      out("fileAttr.FidSource", fileAttr.FidSource);
      out("fileAttr.FidDestination", fileAttr.FidDestination);
   }

   typedef struct TypeToExtension_s
   {
      unsigned int FileType;
      std::string  Ext;
   } TypeToExtension_t;


   /**
    * Generates file name based on Telematics requirement.
    * ProductIDYYMMDDHHMMSS_DQ1.vp3
    */
   ScsCdaTtiBridgeFileAttr_t GenerateFileNamev2(FileType fileType,
                                                const std::string &productid,
                                                std::string fileExtn = "")
   {
      return GenerateFileNamev2(static_cast<unsigned int>(fileType), productid, fileExtn);
   }

   ScsCdaTtiBridgeFileAttr_t GenerateFileNamev2(unsigned int fileType,
                                                const std::string &productid,
                                                std::string fileExtn = "")
   {
       const TypeToExtension_t knownTypes[] = {
              {10008, "cl3"}, {10009, "dl3"}, {10010, "er3"}, {10011, "tr3"}, {10012, "cu3"}, {10013, "hs3"}, {10014, "ec3"}, {10049, "fb3"},
              {10050, "fd3"}, {10051, "fa3"}, {10052, "fl3"}, {10064, "fr3"}, {10067, "ff3"}, {10068, "gs3"}, {10069, "gu3"}, {10077, "mt4"},
              {10078, "mt5"}, {10081, "pl3"}, {10129, "VP3"}, {10143, "mt3"}, {10144, "og3"}, {10155, "vd3"}, {10156, "vd4"}, {10157, "vd5"},
              {10159, "mt1"}, {10160, "mt2"}, {10161, "mt6"}, {10164, "mt7"}, {10175, "th3"}, {10201, "pa3"}, {10202, "tdc"}, {10282, "fb4"},
              {10315, "mt8"}, {10316, "db3"}, {10321, "ff4"}, {10322, "bd"}, {10323, "dfc"}, {10334, "bd"}, {10354, "pb"}, {10355, "pb"}, 
              {10356, "pb"},  {10357, "pb"},  {10358, "pb"},  {10446, "pb"},  {10447, "pb"}
          };
         struct timespec ts;
         ScsCdaTtiBridgeDateTime_t dateTime;
         GetRtcTime(&ts);
         ConvertTimespecToDateTime(&ts, &dateTime);

         // Update file extension if it hasn't been set
         if ( "" == fileExtn )
         {
            for (unsigned short itr = 0; itr < ( sizeof( knownTypes ) / sizeof( TypeToExtension_t ) ); itr++ )
            {
               if ( knownTypes[itr].FileType == fileType )
               {
                  fileExtn = knownTypes[itr].Ext;
                  break;
               }
            }
         }

         std::stringstream sstream;
         sstream.str( std::string() );
         sstream.clear();
         //Good visual formatting.
         sstream << fileType
               << "_"
               << productid
               << std::setfill('0') << std::setw(2) << dateTime.Year % 100
               << std::setfill('0') << std::setw(2) << dateTime.Month
               << std::setfill('0') << std::setw(2) << dateTime.Day
               << std::setfill('0') << std::setw(2) << dateTime.Hour
               << std::setfill('0') << std::setw(2) << dateTime.Min
               << std::setfill('0') << std::setw(2) << dateTime.Sec
               << "_DQ1";


         if ( "" != fileExtn )
         {
            sstream << "." << fileExtn;
         }

         fileAttr.Name = sstream.str();
         fileAttr.TelematicsFileNumber = fileType;

         return fileAttr;
      }


   /**
    * Below function generated file name is not compliance to Telematics required name format.
    * Use below function if you are really sure.
    */
   ScsCdaTtiBridgeFileAttr_t GenerateFileName( unsigned int fileType, std::string fileExtn = "" )
   {
      const TypeToExtension_t knownTypes[] = {
            {10008, "cl3"}, {10009, "dl3"}, {10010, "er3"}, {10011, "tr3"}, {10012, "cu3"}, {10013, "hs3"}, {10014, "ec3"}, {10049, "fb3"},
            {10050, "fd3"}, {10051, "fa3"}, {10052, "fl3"}, {10064, "fr3"}, {10067, "ff3"}, {10068, "gs3"}, {10069, "gu3"}, {10077, "mt4"},
            {10078, "mt5"}, {10081, "pl3"}, {10129, "vp3"}, {10143, "mt3"}, {10144, "og3"}, {10155, "vd3"}, {10156, "vd4"}, {10157, "vd5"},
            {10159, "mt1"}, {10160, "mt2"}, {10161, "mt6"}, {10164, "mt7"}, {10175, "th3"}, {10201, "pa3"}, {10202, "tdc"}, {10282, "fb4"},
            {10315, "mt8"}, {10316, "db3"}, {10321, "ff4"}, {10322, "bd"}, {10323, "dfc"}, {10334, "bd"}, {10447, "pb"}
      };
      struct timespec ts;
      ScsCdaTtiBridgeDateTime_t dateTime;
      GetRtcTime(&ts);
      ConvertTimespecToDateTime(&ts, &dateTime);

      // Update file extension if it hasn't been set
      if ( "" == fileExtn )
      {
         for (unsigned short itr = 0; itr < ( sizeof( knownTypes ) / sizeof( TypeToExtension_t ) ); itr++ )
         {
            if ( knownTypes[itr].FileType == fileType )
            {
               fileExtn = knownTypes[itr].Ext;
               break;
            }
         }
      }

      std::stringstream sstream;
      sstream.str( std::string() );
      sstream.clear();
      //Good visual formatting.
      sstream << fileType
            << "_"
            << std::setfill('0') << std::setw(4) << dateTime.Year
            << std::setfill('0') << std::setw(2) << dateTime.Month
            << std::setfill('0') << std::setw(2) << dateTime.Day
            << "_"
            << std::setfill('0') << std::setw(2) << dateTime.Hour
            << std::setfill('0') << std::setw(2) << dateTime.Min
            << std::setfill('0') << std::setw(2) << dateTime.Sec
            << "_"
            << std::setfill('0') << std::setw(3) << dateTime.MilliSec;

      if ( "" != fileExtn )
      {
         sstream << "." << fileExtn;
      }

      fileAttr.Name = sstream.str();
      fileAttr.TelematicsFileNumber = fileType;

      return fileAttr;
   }

   std::string GetDateTimeNow(void)
   {
      struct timespec ts;
      ScsCdaTtiBridgeDateTime_t dateTime;
      GetRtcTime(&ts);
      ConvertTimespecToDateTime(&ts, &dateTime);

      std::stringstream sstream;
      sstream.str( std::string() );
      sstream.clear();
      //Good visual formatting.
      sstream << std::setfill('0') << std::setw(4) << dateTime.Year
            << std::setfill('0') << std::setw(2) << dateTime.Month
            << std::setfill('0') << std::setw(2) << dateTime.Day
            << "_"
            << std::setfill('0') << std::setw(2) << dateTime.Hour
            << std::setfill('0') << std::setw(2) << dateTime.Min
            << std::setfill('0') << std::setw(2) << dateTime.Sec
            << "_"
            << std::setfill('0') << std::setw(3) << dateTime.MilliSec;

      return sstream.str();
   }

   void GetRtcTime(timespec *ts)
   {
      if(0 != clock_gettime(CLOCK_REALTIME, ts))
      {
         //how to handle in failure case?
      }

      return;
   }

   void ConvertTimespecToDateTime(struct timespec *timeSpec, ScsCdaTtiBridgeDateTime_t *dateTime)
   {
      struct tm tmTimeDate;
      if ((timeSpec == NULL ) || (dateTime == NULL))
      {
         return;
      }

      /*
        The gmtime() function converts the calendar time timep to broken-down time representation,
        expressed in Coordinated Universal Time (UTC). It may return NULL when the year does not
        fit into an integer. The return value points to a statically allocated struct which might
        be overwritten by subsequent calls to any of the date and time functions. The gmtime_r()
        function does the same, but stores the data in a user-supplied struct.
       */
      //struct tm *gmtime_r(const time_t *timep, struct tm *result);
      gmtime_r(&timeSpec->tv_sec, &tmTimeDate);

      dateTime->MilliSec = timeSpec->tv_nsec/1000000L;
      dateTime->Sec = tmTimeDate.tm_sec;
      dateTime->Min = tmTimeDate.tm_min;
      dateTime->Hour = tmTimeDate.tm_hour;
      dateTime->Day = tmTimeDate.tm_mday;
      dateTime->Month = tmTimeDate.tm_mon + 1; // .tm_mon is 0 indexed
      dateTime->Year = tmTimeDate.tm_year + 1900; // tm_year is from 1900
   }

private:
   /* Add Fields Here */
};

typedef Datum<FileTransferBridgeRequestStorage> FileTransferBridgeRequest;

BOOST_CLASS_VERSION(FileTransferBridgeRequestStorage, 1);

#endif //SSSCDATTIBRIDGEREQUEST_H

