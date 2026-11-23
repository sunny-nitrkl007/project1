#ifndef SERIALPRINTERAPP_H
#define SERIALPRINTERAPP_H

#include <cstdint>
#include <string>
#include <sstream>
#include <future>
#include <atomic>

#include <deque>
#include <cmath>
#include <limits>
#include <type_traits>

#include "Ros2TaskWrapper.h"
#include <cpm_common_interfaces/msg/serial_printer_request.hpp>

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

class SerialPrinterApp: public ros2_wrapper::Ros2TaskWrapper
{
public:
    SerialPrinterApp(const std::string& taskName);
    virtual ~SerialPrinterApp();

    virtual bool initialize();
    virtual bool executive();
    virtual void cleanup();
    void startExecutiveTimer() override;

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

    using Request = cpm_common_interfaces::msg::SerialPrinterRequest;
    rclcpp::Subscription<Request>::SharedPtr requestInputChannel_;
    std::deque<Request> requests_;
    double cycleRateHz_ = 2.0;

    template<typename T>
    bool readConfig(const std::string& name, T& value, T fallback) {
        if constexpr (std::is_integral_v<T>) {
            const auto configured = declare_parameter<int64_t>(name, fallback);
            if (configured < 0 || configured > std::numeric_limits<T>::max()) {
                RCLCPP_ERROR(get_logger(), "Invalid parameter %s", name.c_str());
                return false;
            }
            value = static_cast<T>(configured);
        }
        else if constexpr (std::is_floating_point_v<T>) {
            const auto configured = declare_parameter<double>(name, fallback);
            if (!std::isfinite(configured) ||
                    std::abs(configured) > std::numeric_limits<T>::max()) {
                RCLCPP_ERROR(get_logger(), "Invalid parameter %s", name.c_str());
                return false;
            }
            value = static_cast<T>(configured);
        }
        else {
            value = declare_parameter<T>(name, fallback);
        }
        return true;
    }
    std::future<bool> printStatus_;
    std::atomic<bool> stopPrinting_;

    int fileDescriptor_;
    std::istringstream printStream_;

    bool printToStdOut_;
};

#endif
