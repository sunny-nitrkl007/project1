#include <ais/serialization/Datum.h> // For Boost serialization
#include <string>
#include <interfaces/FileTransferBridgeRequest/FileTransferBridgeRequest.h>

#ifndef _FileTransferBridgeIndication_h_
#define _FileTransferBridgeIndication_h_
class FileTransferBridgeIndicationStorage : public FileTransferBridgeRequestStorage
{
public:
   FileTransferBridgeIndicationStorage() /* Initialize Fields Here */ { }
private:
   /* Add Fields Here */
};

typedef Datum<FileTransferBridgeIndicationStorage> FileTransferBridgeIndication;

BOOST_CLASS_VERSION(FileTransferBridgeIndicationStorage, 1);
#endif

