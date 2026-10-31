#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <future>
#include <algorithm>
#include <thread>
#include <chrono>

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>

#include <ais/task/Task.h>
#include <ais/log/AisLogger.h>

#include <fileio/iflocker.hpp>

#include <interfaces/SerialPrinter/RequestInterface.hpp>

#include "SerialPrinterApp.h"

static constexpr auto TEST_STRING = R"(  @@@@@@@         @@@    @@@@@@@@@@@@
 @@@@@@@@@       @@@@@   @@@@@@@@@@@@
@@@@@@@@@@@      @@@@@   @@@@@@@@@@@@
@@@@@ @@@@@      @@@@@   @@@@@@@@@@@@
@@@@   @@@@     @@@@@@@     @@@@@
@@@@   @@@@     @@@@@@@     @@@@@
@@@@   @@@@    @@@@@@@@@    @@@@@
@@@@   @@@@    @@@@ @@@@    @@@@@
@@@@   @@@@    @@@   @@@    @@@@@
@@@@   @@@@   @@@@   @@@@   @@@@@
@@@@          @@@@@@@@@@@   @@@@@
@@@@          @@@@@@@@@@@   @@@@@
@@@@          @@@@@ @@@@@   @@@@@
@@@@         @@@@@   @@@@@  @@@@@
@@@@   @@@@  @@@@  :  @@@@  @@@@@
@@@@   @@@@  @@@  :::  @@@  @@@@@
@@@@   @@@@  @@ .:::::. @@  @@@@@
@@@@   @@@@  @ .:::::::. @  @@@@@
@@@@   @@@@   .:::::::::.   @@@@@
@@@@   @@@@  :::::::::::::  @@@@@
@@@@@ @@@@  :::::::::::::::  @@@@
@@@@@@@@@ .:::::::::::::::::. @@@
 @@@@@@@ .:::::::::::::::::::. @@
  @@@@@ ::::::::::::::::::::::: @)";

/*
 * main() will call this function in order to get the task instance.
 */
task::AbstractTaskCore* task::getTaskImplementation(void) {
    static SerialPrinterApp thisTask("SerialPrinterApp");
    return dynamic_cast<Task*>(&thisTask);
}

/*
 * Constructor
 */
SerialPrinterApp::SerialPrinterApp(const std::string& taskName) :
    task::Task(taskName),
    port_(""),
    baudRate_(SerialPrinterBaudRate::BPS_9600),
    parityBit_(SerialPrinterParityBit::NONE),
    stopBits_(1),
    dataBits_(8),
    secondsBetweenDocs_(0.0f),
    secondsPerCharacter_(0.0f),
    requestInputChannel_(nullptr),
    printStatus_(),
    stopPrinting_(false),
    fileDescriptor_(-1),
    printStream_(),
    printToStdOut_(false) {
}

/*
 * Destructor
 */
SerialPrinterApp::~SerialPrinterApp() {
}

/*
 * AIS Task Initializer
 */
bool SerialPrinterApp::initialize() {
    bool everythingOk = true;
    AIS_LOG_INFO("SerialPrinterApp::initialize");

    { // Get the configs and print it out.
        ConfigSection& configs = getTaskConfig();
        uint32_t bitsPerCharacter = 1; // Start with 1 for the start bit
        float bitsPerSecond;

        /*
         * Get Port, Baud Rate, Stop Bits, Data Bits,
         * Parity Bit, Line Rate (lines per second)
         */

        { // Get Port
            std::string devicePath;
            if (configs.get("devicePath", devicePath)) {
                if (devicePath.empty()) {
                    port_ = "";
                    printToStdOut_ = true;
                    AIS_LOG_INFO("Printing to std out");
                }
                else {
                    port_ = devicePath;
                    printToStdOut_ = false;
                    AIS_LOG_INFO("Serial port device path '%s'", devicePath.c_str());
                }
            }
            else {
                port_ = "";
                printToStdOut_ = true;
                AIS_LOG_WARN("Serial port device path not given");
            }
        }

        { // Get Baud Rate
            uint32_t baudRate;
            if (configs.get("baudRate", baudRate)) {
                if (baudRate <= 300) {
                    bitsPerSecond = 300.0f;
                    baudRate_ = SerialPrinterBaudRate::BPS_300;
                }
                else if (baudRate <= 600) {
                    bitsPerSecond = 600.0f;
                    baudRate_ = SerialPrinterBaudRate::BPS_600;
                }
                else if (baudRate <= 1200) {
                    bitsPerSecond = 1200.0f;
                    baudRate_ = SerialPrinterBaudRate::BPS_1200;
                }
                else if (baudRate <= 2400) {
                    bitsPerSecond = 2400.0f;
                    baudRate_ = SerialPrinterBaudRate::BPS_2400;
                }
                else if (baudRate <= 4800) {
                    bitsPerSecond = 4800.0f;
                    baudRate_ = SerialPrinterBaudRate::BPS_4800;
                }
                else if (baudRate <= 9600) {
                    bitsPerSecond = 9600.0f;
                    baudRate_ = SerialPrinterBaudRate::BPS_9600;
                }
                else if (baudRate <= 19200) {
                    bitsPerSecond = 19200.0f;
                    baudRate_ = SerialPrinterBaudRate::BPS_19200;
                }
                else if (baudRate <= 38400) {
                    bitsPerSecond = 38400.0f;
                    baudRate_ = SerialPrinterBaudRate::BPS_38400;
                }
                else if (baudRate <= 57600) {
                    bitsPerSecond = 57600.0f;
                    baudRate_ = SerialPrinterBaudRate::BPS_57600;
                }
                else {
                    bitsPerSecond = 115200.0f;
                    baudRate_ = SerialPrinterBaudRate::BPS_115200;
                }
            }
            else {
                bitsPerSecond = 9600.0f;
                baudRate_ = SerialPrinterBaudRate::BPS_9600;
            }

            AIS_LOG_INFO("Serial port baud rate set to %u", baudRate);
        }

        { // Get Number of Stop Bits
            uint32_t stopBits;
            if (configs.get("stopBits", stopBits)) {
                if (stopBits > 1) {
                    stopBits = 2;
                }
                else {
                    stopBits = 1;
                }
            }
            else {
                stopBits = 1;
            }

            bitsPerCharacter += stopBits;

            stopBits_ = stopBits;

            AIS_LOG_INFO("Serial port stop bits set to %u", stopBits);
        }

        { // Get Number of Data Bits
            uint32_t dataBits;
            if (configs.get("dataBits", dataBits)) {
                if (dataBits > 7) {
                    dataBits = 8;
                }
                else {
                    dataBits = 7;
                }
            }
            else {
                dataBits = 8;
            }

            bitsPerCharacter += dataBits;

            dataBits_ = dataBits;

            AIS_LOG_INFO("Serial port data bits set to %u", dataBits);
        }

        { // Get Parity Bit Setting
            std::string parityBit;
            if (configs.get("parityBit", parityBit)) {
                if ("none" == parityBit) {
                    parityBit_ = SerialPrinterParityBit::NONE;
                }
                else if ("even" == parityBit) {
                    bitsPerCharacter++;
                    parityBit_ = SerialPrinterParityBit::EVEN;
                }
                else if ("odd" == parityBit) {
                    bitsPerCharacter++;
                    parityBit_ = SerialPrinterParityBit::ODD;
                }
                else {
                    parityBit = "none";
                    parityBit_ = SerialPrinterParityBit::NONE;
                }
            }
            else {
                parityBit = "none";
                parityBit_ = SerialPrinterParityBit::NONE;
            }

            AIS_LOG_INFO("Serial port parity bit set to '%s'", parityBit.c_str());
        }

        { // Get seconds between documents
            /*
             * This is the amount of time to wait between printed documents.
             * The printer uses this delay in order to determine when to spool
             * the paper up when the document is complete.
             */
            float secondsBetweenDocs;
            if (configs.get("secondsBetweenDocs", secondsBetweenDocs)) {
                // Clip it to reasonable values
                secondsBetweenDocs = std::max(secondsBetweenDocs, 0.0f);
                secondsBetweenDocs = std::min(secondsBetweenDocs, 10.0f);
            }
            else {
                secondsBetweenDocs = 1.0f;
            }

            secondsBetweenDocs_ = secondsBetweenDocs;

            AIS_LOG_INFO("Seconds between printed documents is %f", secondsBetweenDocs);
        }

        /*
         * Seconds per character is used to determine how long to wait before
         * sending the next file to be printed.
         */
        secondsPerCharacter_ = static_cast<float>(bitsPerCharacter) / bitsPerSecond;
    }

    if (everythingOk && !port_.empty()) {
        // Set up the serial port
        fileDescriptor_ = open(port_.c_str(), O_RDWR | O_NOCTTY);
        if (fileDescriptor_ < 0) {
            int err = errno;
            AIS_LOG_ERROR("Cannot open port '%s' - errno=%d", port_.c_str(), err);
            everythingOk = false;
        }
        else {
            // Configure the options
            struct termios options;

            // Get the current options for this port
            tcgetattr(fileDescriptor_, &options);

            // Set baud rate
            switch (baudRate_) {
            case (SerialPrinterBaudRate::BPS_300): {
                cfsetispeed(&options, B300);
                cfsetospeed(&options, B300);
                break;
            }
            case (SerialPrinterBaudRate::BPS_600): {
                cfsetispeed(&options, B600);
                cfsetospeed(&options, B600);
                break;
            }
            case (SerialPrinterBaudRate::BPS_1200): {
                cfsetispeed(&options, B1200);
                cfsetospeed(&options, B1200);
                break;
            }
            case (SerialPrinterBaudRate::BPS_2400): {
                cfsetispeed(&options, B2400);
                cfsetospeed(&options, B2400);
                break;
            }
            case (SerialPrinterBaudRate::BPS_4800): {
                cfsetispeed(&options, B4800);
                cfsetospeed(&options, B4800);
                break;
            }
            case (SerialPrinterBaudRate::BPS_9600): {
                cfsetispeed(&options, B9600);
                cfsetospeed(&options, B9600);
                break;
            }
            case (SerialPrinterBaudRate::BPS_19200): {
                cfsetispeed(&options, B19200);
                cfsetospeed(&options, B19200);
                break;
            }
            case (SerialPrinterBaudRate::BPS_38400): {
                cfsetispeed(&options, B38400);
                cfsetospeed(&options, B38400);
                break;
            }
            case (SerialPrinterBaudRate::BPS_57600): {
                cfsetispeed(&options, B57600);
                cfsetospeed(&options, B57600);
                break;
            }
            case (SerialPrinterBaudRate::BPS_115200): {
                cfsetispeed(&options, B115200);
                cfsetospeed(&options, B115200);
                break;
            }
            default: {
                cfsetispeed(&options, B9600);
                cfsetospeed(&options, B9600);
                break;
            }
            }

            // Set parity bits
            switch (parityBit_) {
            case (SerialPrinterParityBit::NONE): {
                options.c_cflag &= ~PARENB;
                break;
            }
            case (SerialPrinterParityBit::EVEN): {
                options.c_cflag |= PARENB;
                options.c_cflag &= ~PARODD;
                break;
            }
            case (SerialPrinterParityBit::ODD): {
                options.c_cflag |= PARENB;
                options.c_cflag |= PARODD;
                break;
            }
            default: {
                options.c_cflag &= ~PARENB;
                break;
            }
            }

            // Set stop bits
            switch (stopBits_) {
            case (1): {
                options.c_cflag &= ~CSTOPB;
                break;
            }
            case (2): {
                options.c_cflag |= CSTOPB;
                break;
            }
            default: {
                options.c_cflag &= ~CSTOPB;
                break;
            }
            }

            // Set data bits
            options.c_cflag &= ~CSIZE;
            switch (dataBits_) {
            case (8): {
                options.c_cflag |= CS8;
                break;
            }
            case (7): {
                options.c_cflag |= CS7;
                break;
            }
            default: {
                options.c_cflag |= CS8;
                break;
            }
            }

            // Set echo off
            options.c_lflag &= ~ECHO;

            // Don't mess with CRLF
            options.c_iflag &= ~(ISTRIP | INLCR | IGNCR | ICRNL);
            options.c_oflag &= ~(ONLCR | OCRNL | ONOCR | ONLRET);

            // No flow control
            options.c_iflag &= ~(IXON | IXOFF);

            // Ignore input errors
            options.c_iflag |= (IGNPAR);
            options.c_iflag &= ~(PARMRK | INPCK);

            // Ignore input BREAK
            options.c_iflag |= (IGNBRK);
            options.c_iflag &= ~(BRKINT);

            // Discard all pending I/O
            tcflush(fileDescriptor_, TCIOFLUSH);

            // Apply the new settings
            tcsetattr(fileDescriptor_, TCSANOW, &options);
        }
    }
    else {
        fileDescriptor_ = -1;
    }

    // Initialize input and output channels
    requestInputChannel_ = dynamic_cast<SerialPrinterRequestInterfaceInputChannel*>(task::InterfaceDb::fetch("RequestInput"));
    if (nullptr == requestInputChannel_) {
        AIS_LOG_ERROR("No request input channel defined.");
        everythingOk = false;
    }

    printStream_.str("");
    printStream_.clear();
    printStream_.seekg(0);

    stopPrinting_ = false;

    return everythingOk;
}

bool SerialPrinterApp::printWorker(uint8_t numberOfCopies) {
    std::string currentLine = "";
    bool lastLine = false;
    uint8_t currentCopy = 1;
    bool totallyDone = false;

    if (0 == numberOfCopies) {
        totallyDone = true;
    }

    AIS_LOG_NOTICE("Start Printing.");

    /*
     * The outer while loop keeps running the inner while loop until printing is
     * totally done, or we are told to stop printing.
     */
    while (!stopPrinting_ && !totallyDone) {
        // Grab the start time of the inner loop and initialize waitTime to 0
        auto startTime = std::chrono::steady_clock::now();
        float waitTime = 0.f;

        /*
         * The inner loop prints line by line until we encounter one of the following:
         *  - Error calling "write"
         *      in which case, we are totally done.
         *  - The last line for the current copy of the document was written
         *      in which case, we wait to start printing the next copy.
         *  - None, or only some, of the current line was written (write buffer full)
         *      in which case, we wait for the write buffer to clear out a bit.
         *  - There is nothing left to write
         *      in which case, we are totally done.
         */
        while (!stopPrinting_) {
            // If we aren't continuing a previous line, get the next line
            if (currentLine.empty()) {
                // See if we have another line to print.
                if (std::getline(printStream_, currentLine)) {
                    currentLine.append(NEW_LINE);  // Add CR back on
                    lastLine = false;
                }
                else {
                    // There are no more lines to print.
                    // Add the line feeds at the end.
                    currentLine = FORM_FEED;
                    lastLine = true;
                }
            }

            // Is there anything to print?
            if (!currentLine.empty()) {

                // Try to print the whole line
                std::size_t sizeToWrite = currentLine.size();
                ssize_t sizeWritten;

                if (fileDescriptor_ < 0) {
                    sizeWritten = sizeToWrite;
                }
                else {
                    // write it
                    sizeWritten = write(fileDescriptor_, currentLine.data(), sizeToWrite);
                }

                if (sizeWritten < 0) {
                    // We failed, bail, but give at least enough time to start a new fresh document.
                    waitTime += secondsBetweenDocs_;
                    totallyDone = true;
                    AIS_LOG_ERROR("Line not printed, write error.");
                    break; // out of inner while loop
                }
                else if (static_cast<std::size_t>(sizeWritten) >= sizeToWrite) {
                    // The whole line was printed
                    if (printToStdOut_) {
                        std::cout << currentLine << std::flush;
                    }

                    // Clear the current line so that the next line is read
                    //  at the beginning of the next loop.
                    currentLine.clear();

                    waitTime += static_cast<float>(sizeWritten) * secondsPerCharacter_;

                    if (lastLine) {
                        // The last line was printed, wait for next document.
                        waitTime += secondsBetweenDocs_;

                        lastLine = false;

                        // Was this the last copy?
                        if (currentCopy >= numberOfCopies) {
                            // We just printed the last line of the last copy.
                            //  We are totally done.
                            totallyDone = true;
                        }
                        else {
                            // Advance to next copy
                            ++currentCopy;

                            // Rewind the print stream for another copy
                            printStream_.clear();
                            printStream_.seekg(0);
                        }

                        AIS_LOG_NOTICE("Last line printed.");
                        break; // out of inner while loop
                    }
                    else {
                        // ... keep going to print the next line.
                    }
                }
                else if (sizeWritten > 0) {
                    // Only a portion of the line was printed
                    if (printToStdOut_) {
                        std::cout << currentLine.substr(0, sizeWritten);
                    }
                    currentLine = currentLine.substr(sizeWritten);
                    waitTime += static_cast<float>(sizeWritten) * secondsPerCharacter_;

                    AIS_LOG_INFO("Part of the line printed.");
                    break; // out of inner while loop
                }
                else /* 0 == sizeWritten */ {
                    // None of the line was written.
                    // Keep current line and try again.
                    AIS_LOG_WARN("Line not printed, zero characters written.");
                    break; // out of inner while loop
                }
            }
            else {
                // We don't have anything left to print.
                //  We are totally done.
                totallyDone = true;
                break; // out of inner while loop
            }
        }

        // Sleep for some time to let the previous work from the inner loop complete.
        std::this_thread::sleep_until(startTime + std::chrono::duration<float>(waitTime));
    }

    stopPrinting_ = false;

    return true;
}

/*
 * AIS Task Executive
 */
bool SerialPrinterApp::executive() {
    AIS_LOG_DEBUG("SerialPrinterApp::executive");

    // Handle one request at a time
    SerialPrinterRequestInterface request;

    if (requestInputChannel_->get(request)) {
        switch (request.command) {
            case (SerialPrinterRequestInterfaceCommand::PRINT): {
                if (isPrinting()) {
                    AIS_LOG_WARN("Cannot process a print request when printing is in process.");
                }
                else {
                    tes_common_ais::IFlocker ifl(request.filePath());
                    if (ifl) {
                        std::ifstream& ifs = ifl.ifstream();

                        std::ostringstream oss;
                        oss << ifs.rdbuf();

                        print(oss.str(), request.numberOfCopies());

                        ifl.close();
                    }
                    else {
                        AIS_LOG_ERROR("Cannot open and lock print request file for reading.");
                    }
                }
                break;
            }
            case (SerialPrinterRequestInterfaceCommand::TEST): {
                if (isPrinting()) {
                    AIS_LOG_WARN("Cannot process a print request when printing is in process.");
                }
                else {
                    print(TEST_STRING, request.numberOfCopies());
                }
                break;
            }
            default: {
                AIS_LOG_WARN("Unsupported command.");
                break;
            }
        }
    }

    return true;
}


/*
 * Are we currently printing
 */
bool SerialPrinterApp::isPrinting() {
    if (!printStatus_.valid()) {
        AIS_LOG_NOTICE("not yet printed.");
        return false;
    }
    else if (printStatus_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        AIS_LOG_NOTICE("done printing.");
        printStatus_.get();
        return false;
    }
    else {
        AIS_LOG_NOTICE("is printing now.");
        return true;
    }
}


/*
 * Print a string
 */
bool SerialPrinterApp::print(const std::string& str, uint8_t numberOfCopies) {

    AIS_LOG_NOTICE("Printing %d copies.", numberOfCopies);

    if (str.empty() || (numberOfCopies == 0)) {
        // Print nothing?  OK
        printStream_.str("");
        numberOfCopies = 0;
    }
    else {
        // Kick off printing the first copy
        printStream_.str(str);
    }

    // Rewind the print stream to the beginning
    printStream_.clear();
    printStream_.seekg(0);

    // Handle periodic line printing
    printStatus_ = std::async(std::launch::async, &SerialPrinterApp::printWorker, this, numberOfCopies);

    return true;
}

/*
 * Stop the printing
 */
void SerialPrinterApp::stopPrinting() {
    if (fileDescriptor_) {
        stopPrinting_ = true;
        if(printStatus_.valid()) {
            printStatus_.wait();
        }

        // Flush the output (discard data written but not transmitted)
        tcflush(fileDescriptor_, TCOFLUSH);
    }
}

/*
 * AIS Task Cleanup
 */
void SerialPrinterApp::cleanup() {
    AIS_LOG_INFO("SerialPrinterApp::cleanup");

    if (isPrinting()) {
        stopPrinting();
    }

    if (fileDescriptor_ >= 0) {
        close(fileDescriptor_);
        fileDescriptor_ = 0;
    }
}
