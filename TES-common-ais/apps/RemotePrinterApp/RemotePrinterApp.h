#ifndef REMOTEPRINTERAPP_H
#define REMOTEPRINTERAPP_H

#include <cstdint>
#include <string>

#include <boost/filesystem.hpp>

#include <ais/task/Task.h>

#include <interfaces/SerialPrinter/RequestInterfaceInputChannel.h>
#include <interfaces/FileTransferBridgeRequest/InterfaceTypes.h>

class RemotePrinterApp: public task::Task
{
public:
    RemotePrinterApp(const std::string& taskName);
    virtual ~RemotePrinterApp();

    virtual bool initialize();
    virtual bool executive();
    virtual void cleanup();

protected:
    bool print(const std::string& str, uint8_t numberOfCopies = 1);

    static constexpr auto NEW_LINE = '\n';
    static constexpr auto FORM_FEED = '\f'; // Form Feed

private:
    uint32_t destinationFid_;

    SerialPrinterRequestInterfaceInputChannel* requestInputChannel_;
    FileTransferBridgeRequestOutput* fileTransferBridgeRequestOutput_;

    boost::filesystem::path tempRoot_;
};

#endif
