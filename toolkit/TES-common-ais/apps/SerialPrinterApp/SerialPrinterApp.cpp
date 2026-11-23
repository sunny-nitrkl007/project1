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

#include "ROS2Logger.hpp"

#include <fileio/iflocker.hpp>

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

int main(int argc, char** argv) {
    std::vector<char*> rosArguments{argv[0]};
    std::string instance = "SerialPrinterApp";
    for (int index = 1; index < argc; ++index) {
        const std::string argument(argv[index]);
        if (argument == "--instance" || argument == "--instanceName") {
            if (++index >= argc) {
                std::cerr << "Missing instance name\n";
                return 1;
            }
            instance = argv[index];
        }
        else if (argument.rfind("--instance=", 0) == 0) {
            instance = argument.substr(11);
        }
        else if (argument.rfind("--instanceName=", 0) == 0) {
            instance = argument.substr(15);
        }
        else {
            rosArguments.push_back(argv[index]);
        }
    }
    sigset_t signals;
    sigemptyset(&signals);
    sigaddset(&signals, SIGINT);
    sigaddset(&signals, SIGTERM);
    sigaddset(&signals, SIGQUIT);
    if (pthread_sigmask(SIG_BLOCK, &signals, nullptr) != 0) {
        std::cerr << "Cannot block shutdown signals\n";
        return 1;
    }
    rclcpp::init(static_cast<int>(rosArguments.size()), rosArguments.data(),
            rclcpp::InitOptions(), rclcpp::SignalHandlerOptions::None);
    std::atomic<bool> stopping{false};
    std::atomic<bool> signalThreadDone{false};
    std::shared_ptr<rclcpp::executors::SingleThreadedExecutor> executor;
    std::thread signalThread;
    std::shared_ptr<SerialPrinterApp> app;
    int result = 1;
    try {
        ROS2Logger::Instance().SetFeatureName(instance);
        app = std::make_shared<SerialPrinterApp>(instance);
        executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
        executor->add_node(app);
        signalThread = std::thread([&]() {
            unsigned int caught = 0;
            const timespec timeout{0, 100000000};
            while (!signalThreadDone) {
                const int signal = sigtimedwait(&signals, nullptr, &timeout);
                if (signal == SIGINT || signal == SIGTERM || signal == SIGQUIT) {
                    if (++caught >= 3) {
                        std::_Exit(1);
                    }
                    stopping = true;
                    executor->cancel();
                }
            }
        });
        if (app->initialize() && !stopping) {
            app->startExecutiveTimer();
            executor->spin();
            result = 0;
        }
    }
    catch (const std::exception& error) {
        RCLCPP_ERROR(rclcpp::get_logger("SerialPrinterApp"), "%s", error.what());
    }
    if (app) {
        app->cleanup();
    }
    signalThreadDone = true;
    if (signalThread.joinable()) {
        signalThread.join();
    }
    rclcpp::shutdown();
    return result;
}

/*
 * Constructor
 */
SerialPrinterApp::SerialPrinterApp(const std::string& taskName) :
    ros2_wrapper::Ros2TaskWrapper(taskName),
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
    cleanup();
}

/*
 * ROS2 Initializer
 */
bool SerialPrinterApp::initialize() {
    bool everythingOk = true;
    RCLCPP_INFO(get_logger(), "SerialPrinterApp::initialize");

    { // Get the configs and print it out.
        ROS2Logger::Instance().SetLogLevel(declare_parameter<std::string>("logger_threshold", "error"));
        cycleRateHz_ = declare_parameter<double>("cycle_rate_hz", 2.0);
        if (!std::isfinite(cycleRateHz_) || cycleRateHz_ <= 0.0 || cycleRateHz_ > 1000.0) {
            RCLCPP_ERROR(get_logger(), "Invalid cycle_rate_hz");
            return false;
        }
        const auto scheduler = declare_parameter<std::string>("scheduler", "SCHED_OTHER");
        const auto priority = declare_parameter<int>("scheduler_priority", 0);
        if (scheduler != "SCHED_OTHER" && scheduler != "SCHED_RR" && scheduler != "SCHED_FIFO") {
            RCLCPP_ERROR(get_logger(), "Invalid scheduler");
            return false;
        }
        if (!applyRealtimeScheduling(scheduler, priority)) {
            return false;
        }
        uint32_t bitsPerCharacter = 1; // Start with 1 for the start bit
        float bitsPerSecond;

        /*
         * Get Port, Baud Rate, Stop Bits, Data Bits,
         * Parity Bit, Line Rate (lines per second)
         */

        { // Get Port
            std::string devicePath;
            if (readConfig("device_path", devicePath, std::string{})) {
                if (devicePath.empty()) {
                    port_ = "";
                    printToStdOut_ = true;
                    RCLCPP_INFO(get_logger(), "Printing to std out");
                }
                else {
                    port_ = devicePath;
                    printToStdOut_ = false;
                    RCLCPP_INFO(get_logger(), "Serial port device path '%s'", devicePath.c_str());
                }
            }
            else {
                port_ = "";
                printToStdOut_ = true;
                RCLCPP_WARN(get_logger(), "Serial port device path not given");
            }
        }

        { // Get Baud Rate
            uint32_t baudRate = 9600;
            if (readConfig("baud_rate", baudRate, uint32_t{9600})) {
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

            RCLCPP_INFO(get_logger(), "Serial port baud rate set to %u", baudRate);
        }

        { // Get Number of Stop Bits
            uint32_t stopBits;
            if (readConfig("stop_bits", stopBits, uint32_t{1})) {
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

            RCLCPP_INFO(get_logger(), "Serial port stop bits set to %u", stopBits);
        }

        { // Get Number of Data Bits
            uint32_t dataBits;
            if (readConfig("data_bits", dataBits, uint32_t{8})) {
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

            RCLCPP_INFO(get_logger(), "Serial port data bits set to %u", dataBits);
        }

        { // Get Parity Bit Setting
            std::string parityBit;
            if (readConfig("parity_bit", parityBit, std::string{"none"})) {
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

            RCLCPP_INFO(get_logger(), "Serial port parity bit set to '%s'", parityBit.c_str());
        }

        { // Get seconds between documents
            /*
             * This is the amount of time to wait between printed documents.
             * The printer uses this delay in order to determine when to spool
             * the paper up when the document is complete.
             */
            float secondsBetweenDocs;
            if (readConfig("seconds_between_docs", secondsBetweenDocs, 1.0f)) {
                // Clip it to reasonable values
                secondsBetweenDocs = std::max(secondsBetweenDocs, 0.0f);
                secondsBetweenDocs = std::min(secondsBetweenDocs, 10.0f);
            }
            else {
                secondsBetweenDocs = 1.0f;
            }

            secondsBetweenDocs_ = secondsBetweenDocs;

            RCLCPP_INFO(get_logger(), "Seconds between printed documents is %f", secondsBetweenDocs);
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
            RCLCPP_ERROR(get_logger(), "Cannot open port '%s' - errno=%d", port_.c_str(), err);
            everythingOk = false;
        }
        else {
            // Configure the options
            struct termios options{};

            // Never apply settings derived from a failed attribute read.
            if (tcgetattr(fileDescriptor_, &options) != 0) {
                RCLCPP_ERROR(get_logger(), "Cannot read serial attributes: errno=%d", errno);
                return false;
            }

            // Set baud rate
            speed_t selectedSpeed = B9600;
            switch (baudRate_) {
            case (SerialPrinterBaudRate::BPS_300): {
                selectedSpeed = B300;
                break;
            }
            case (SerialPrinterBaudRate::BPS_600): {
                selectedSpeed = B600;
                break;
            }
            case (SerialPrinterBaudRate::BPS_1200): {
                selectedSpeed = B1200;
                break;
            }
            case (SerialPrinterBaudRate::BPS_2400): {
                selectedSpeed = B2400;
                break;
            }
            case (SerialPrinterBaudRate::BPS_4800): {
                selectedSpeed = B4800;
                break;
            }
            case (SerialPrinterBaudRate::BPS_9600): {
                selectedSpeed = B9600;
                break;
            }
            case (SerialPrinterBaudRate::BPS_19200): {
                selectedSpeed = B19200;
                break;
            }
            case (SerialPrinterBaudRate::BPS_38400): {
                selectedSpeed = B38400;
                break;
            }
            case (SerialPrinterBaudRate::BPS_57600): {
                selectedSpeed = B57600;
                break;
            }
            case (SerialPrinterBaudRate::BPS_115200): {
                selectedSpeed = B115200;
                break;
            }
            default: {
                selectedSpeed = B9600;
                break;
            }
            }

            if (cfsetispeed(&options, selectedSpeed) != 0 ||
                    cfsetospeed(&options, selectedSpeed) != 0) {
                RCLCPP_ERROR(get_logger(), "Cannot set serial speed: errno=%d", errno);
                return false;
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
            if (tcflush(fileDescriptor_, TCIOFLUSH) != 0) {
                RCLCPP_ERROR(get_logger(), "Cannot flush serial port: errno=%d", errno);
                return false;
            }

            // Apply the new settings
            if (tcsetattr(fileDescriptor_, TCSANOW, &options) != 0) {
                RCLCPP_ERROR(get_logger(), "Cannot configure serial port: errno=%d", errno);
                return false;
            }
        }
    }
    else {
        fileDescriptor_ = -1;
    }

    if (!everythingOk) {
        return false;
    }
    requestInputChannel_ = create_subscription<Request>(
            "serial_printer_request", rclcpp::QoS(rclcpp::KeepLast(2)).reliable().durability_volatile(),
            [this](const Request::SharedPtr request) {
                if (requests_.size() == 2) {
                    requests_.pop_front();
                }
                requests_.push_back(*request);
            });

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

    RCLCPP_WARN(get_logger(), "Start Printing.");

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
                    RCLCPP_ERROR(get_logger(), "Line not printed, write error.");
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

                        RCLCPP_WARN(get_logger(), "Last line printed.");
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

                    RCLCPP_INFO(get_logger(), "Part of the line printed.");
                    break; // out of inner while loop
                }
                else /* 0 == sizeWritten */ {
                    // None of the line was written.
                    // Keep current line and try again.
                    RCLCPP_WARN(get_logger(), "Line not printed, zero characters written.");
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

void SerialPrinterApp::startExecutiveTimer() {
    createExecutiveTimer(cycleRateHz_);
}

/*
 * Periodic executive
 */
bool SerialPrinterApp::executive() {
    RCLCPP_DEBUG(get_logger(), "SerialPrinterApp::executive");

    // Handle one request at a time
    if (!requests_.empty()) {
        const auto request = requests_.front();
        requests_.pop_front();
        switch (request.command) {
            case (Request::PRINT): {
                if (isPrinting()) {
                    RCLCPP_WARN(get_logger(), "Cannot process a print request when printing is in process.");
                }
                else {
                    tes_common_ais::IFlocker ifl(request.file_path);
                    if (ifl) {
                        std::ifstream& ifs = ifl.ifstream();

                        std::ostringstream oss;
                        oss << ifs.rdbuf();

                        print(oss.str(), std::min<uint8_t>(request.number_of_copies, 3));

                        ifl.close();
                    }
                    else {
                        RCLCPP_ERROR(get_logger(), "Cannot open and lock print request file for reading.");
                    }
                }
                break;
            }
            case (Request::TEST): {
                if (isPrinting()) {
                    RCLCPP_WARN(get_logger(), "Cannot process a print request when printing is in process.");
                }
                else {
                    print(TEST_STRING, std::min<uint8_t>(request.number_of_copies, 3));
                }
                break;
            }
            default: {
                RCLCPP_WARN(get_logger(), "Unsupported command.");
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
        RCLCPP_WARN(get_logger(), "not yet printed.");
        return false;
    }
    else if (printStatus_.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        RCLCPP_WARN(get_logger(), "done printing.");
        printStatus_.get();
        return false;
    }
    else {
        RCLCPP_WARN(get_logger(), "is printing now.");
        return true;
    }
}


/*
 * Print a string
 */
bool SerialPrinterApp::print(const std::string& str, uint8_t numberOfCopies) {

    RCLCPP_WARN(get_logger(), "Printing %d copies.", numberOfCopies);

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
    {
        stopPrinting_ = true;
        if(printStatus_.valid()) {
            printStatus_.wait();
            try {
                printStatus_.get();
            }
            catch (const std::exception& error) {
                RCLCPP_ERROR(get_logger(), "Print worker failed: %s", error.what());
            }
        }

        // Flush the output (discard data written but not transmitted)
        if (fileDescriptor_ >= 0) {
            tcflush(fileDescriptor_, TCOFLUSH);
        }
    }
}

/*
 * ROS2 Cleanup
 */
void SerialPrinterApp::cleanup() {
    RCLCPP_INFO(get_logger(), "SerialPrinterApp::cleanup");

    executiveTimer_.reset();
    requestInputChannel_.reset();
    requests_.clear();
    if (printStatus_.valid()) {
        stopPrinting();
    }

    if (fileDescriptor_ >= 0) {
        close(fileDescriptor_);
        fileDescriptor_ = -1;
    }
}
