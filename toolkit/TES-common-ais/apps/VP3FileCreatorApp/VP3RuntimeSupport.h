#ifndef VP3RUNTIMESUPPORT_H
#define VP3RUNTIMESUPPORT_H

#include <array>
#include <cstdint>
#include <ctime>
#include <sstream>
#include <rclcpp/rclcpp.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <fileio/sha1_fstream.hpp>

namespace vp3 {
template <class Reader>
bool readStorage(const std::string& path, Reader reader)
{
    try {
        tes_common_ais::sha1_ifstream stream(true);
        stream.open(path, std::ios::in | std::ios::binary);
        if (!stream) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Cannot open archive %s", path.c_str());
            return false;
        }
        bool success = false;
        try {
            boost::archive::binary_iarchive archive(stream);
            reader(archive);
            success = true;
        } catch (const std::exception& error) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Cannot read %s: %s", path.c_str(), error.what());
        }
        stream.close();
        if (stream.is_corrupt()) {
            const bool repaired = stream.fix_it();
            RCLCPP_WARN(rclcpp::get_logger("VP3FileCreationApp"), "Archive %s repair: %s", path.c_str(), repaired ? "success" : "failure");
        }
        return success;
    } catch (const std::exception& error) {
        RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Storage read %s: %s", path.c_str(), error.what());
        return false;
    }
}

template <class Writer>
bool writeStorage(const std::string& path, Writer writer)
{
    try {
        tes_common_ais::sha1_ofstream stream(true);
        stream.open(path, std::ios::out | std::ios::binary);
        if (!stream) {
            RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Cannot save archive %s", path.c_str());
            return false;
        }
        {
            boost::archive::binary_oarchive archive(stream);
            writer(archive);
        }
        stream.close();
        return true;
    } catch (const std::exception& error) {
        RCLCPP_ERROR(rclcpp::get_logger("VP3FileCreationApp"), "Storage write %s: %s", path.c_str(), error.what());
        return false;
    }
}

inline std::string timezoneString(const std::array<std::uint8_t, 20>& data)
{
    auto bias = [&data](std::size_t i) {
        const auto bits = (static_cast<std::uint16_t>(data[i]) << 8) | data[i + 1];
        return bits >= 32768 ? static_cast<int>(bits) - 65536 : static_cast<int>(bits);
    };
    std::ostringstream out;
    auto offset = [&out](int value) {
        if (value > 0) out << '-';
        else value = -value;
        out << value / 60;
        if (value % 60) out << ':' << value % 60;
    };
    auto rule = [&out, &data](std::size_t i) {
        out << ',';
        if (data[i] == 0) {
            out << 'M' << static_cast<unsigned>(data[i + 1]) << '.'
                << static_cast<unsigned>(data[i + 2]) << '.' << static_cast<unsigned>(data[i + 3]);
        } else {
            static constexpr unsigned days[] = {0,31,59,90,120,151,181,212,243,273,304,334};
            const auto month = data[i + 1];
            out << 'J' << (month >= 1 && month <= 12 ? days[month - 1] + data[i + 2] : 0);
        }
        if (data[i + 4] != 2 || data[i + 5] != 0) {
            out << '/' << static_cast<unsigned>(data[i + 4]);
            if (data[i + 5]) out << ':' << static_cast<unsigned>(data[i + 5]);
        }
    };
    out << "LST";
    offset(bias(1) + bias(3));
    out << "LDT";
    offset(bias(1) + bias(11));
    rule(13);
    rule(5);
    return out.str();
}
}

#endif
