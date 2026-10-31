#include <ais/serialization/Datum.h> // For Boost serialization
#include <string>

using namespace std;

#ifndef SCSCDATTIBRIDGERESPONSE_H
#define SCSCDATTIBRIDGERESPONSE_H

typedef enum
{
   SCS_CDA_TTI_BRIDGE_SUCCESS = 0,
   SCS_CDA_TTI_BRIDGE_SERVER_NOT_READY,
   SCS_CDA_TTI_BRIDGE_FILE_NOT_FOUND,
   SCS_CDA_TTI_BRIDGE_FILE_TYPE_NOT_SUPPORTED,
   SCS_CDA_TTI_BRIDGE_FILE_SIZE_MISMATCH,
   SCS_CDA_TTI_BRIDGE_FILE_TYPE_MISMATCH,
   SCS_CDA_TTI_BRIDGE_FILE_SIZE_LIMIT,
   SCS_CDA_TTI_BRIDGE_FILE_NOT_QUEUED // Catch all
} ScsCdaTtiBridgeRet_t;

class FileTransferBridgeResponseStorage : public csvable
{
public:
   typedef struct
   {
      ScsCdaTtiBridgeRet_t Ret{SCS_CDA_TTI_BRIDGE_SERVER_NOT_READY};
      string FileName;
      string Msg;
   }FileTransferBridgeResponse_t;

   FileTransferBridgeResponse_t Response;

   FileTransferBridgeResponseStorage() { }

   template <class Archive>
   void serialize(Archive &ar, unsigned int version)
   {
      ar & Response.Ret & Response.Msg & Response.FileName;
   }
   void toCsv(CsvOutStream& out) const
   {
      out("Response.Ret", Response.Ret);
      out("Response.ErrorMsg", Response.Msg);
      out("Response.FileName", Response.FileName);
   }

private:
   // Nothing here yet
};

typedef Datum<FileTransferBridgeResponseStorage> FileTransferBridgeResponse;

BOOST_CLASS_VERSION(FileTransferBridgeResponseStorage, 1);

#endif  //SCSCDATTIBRIDGERESPONSE_H

