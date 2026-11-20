#ifndef SERIALPRINTERTESTAPP_H
#define SERIALPRINTERTESTAPP_H

#include <string>
#include <future>

#include <boost/filesystem.hpp>

#include <ais/task/Task.h>

#include <interfaces/SerialPrinter/RequestInterfaceOutputChannel.h>


class SerialPrinterTestApp: public task::Task
{
public:
    SerialPrinterTestApp(const std::string& taskName);
    virtual ~SerialPrinterTestApp();

    virtual bool initialize();
    virtual bool executive();
    virtual void cleanup();

protected:
    inline std::string makeTempPath(const std::string& fileName) const {
        return (tempRoot_ / fileName).string();
    }

private:
    std::future<std::string> kbInputFuture_;

    boost::filesystem::path tempRoot_;

    SerialPrinterRequestInterfaceOutputChannel* requestChannelOutput_;
};

#endif
