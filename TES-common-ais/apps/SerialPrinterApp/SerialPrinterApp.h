#ifndef SERIALPRINTERAPP_H
#define SERIALPRINTERAPP_H

#include <cstdint>
#include <string>
#include <sstream>
#include <future>
#include <atomic>

#include <ais/task/Task.h>

#include <interfaces/SerialPrinter/RequestInterfaceInputChannel.h>

enum class SerialPrinterBaudRate : uint8_t {
    BPS_300,
    BPS_600,
    BPS_1200,
    BPS_2400,
    BPS_4800,
    BPS_9600,
    BPS_19200,
    BPS_38400,
    BPS_57600,
    BPS_115200
};

enum class SerialPrinterParityBit : uint8_t {
    NONE,
    ODD,
    EVEN
};

class SerialPrinterApp: public task::Task
{
public:
    SerialPrinterApp(const std::string& taskName);
    virtual ~SerialPrinterApp();

    virtual bool initialize();
    virtual bool executive();
    virtual void cleanup();

protected:
    bool isPrinting();
    bool print(const std::string& str, uint8_t numberOfCopies = 1);
    void stopPrinting();

    bool printWorker(uint8_t numberOfCopies);

    static constexpr auto NEW_LINE = "\n";
    static constexpr auto FORM_FEED = "\f"; // Form Feed

private:
    std::string port_;
    SerialPrinterBaudRate baudRate_;
    SerialPrinterParityBit parityBit_;
    uint8_t stopBits_;
    uint8_t dataBits_;
    float secondsBetweenDocs_;
    float secondsPerCharacter_;

    SerialPrinterRequestInterfaceInputChannel* requestInputChannel_;
    std::future<bool> printStatus_;
    std::atomic<bool> stopPrinting_;

    int fileDescriptor_;
    std::istringstream printStream_;

    bool printToStdOut_;
};

#endif
