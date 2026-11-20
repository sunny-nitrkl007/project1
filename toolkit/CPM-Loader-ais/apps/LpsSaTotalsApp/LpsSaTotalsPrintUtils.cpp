/*
 * LpsSaTotalsPrintUtils.cpp
 *
 *  Created on: Jan 17, 2023
 *      Author: pf
 */
#include <string>

#include "LpsSaTotalsPrintUtils.h"

namespace pu = LpsSaTotalsPrintUtils;

static constexpr const char* TONNES_STR = "tonnes";
static constexpr const char* KG_STR =     "kg";
static constexpr const char* TONS_STR =   "Tons";
static constexpr const char* KLBS_STR =   "lbsx1000";
static constexpr const char* LBS_STR =    "lbs";

const char* pu::weightUnitsString(const LpsCommonWeightUnits& weightUnits) {
    const char* str;
    switch (weightUnits) {
    case(LpsCommonWeightUnits::TONNE): {
        str = TONNES_STR;
        break;
    }
    case (LpsCommonWeightUnits::TON): {
        str = TONS_STR;
        break;
    }
    case (LpsCommonWeightUnits::KLB): {
        str = KLBS_STR;
        break;
    }
    case (LpsCommonWeightUnits::KG): {
        str = KG_STR;
        break;
    }
    case (LpsCommonWeightUnits::LB): {
        str = LBS_STR;
        break;
    }
    default: {
        str = TONNES_STR;
        break;
    }
    }
    return str;
}

/*
 * Helper functions for printing strings
 */
std::string& pu::rightPadString(std::string& str, std::string::size_type length, std::string::value_type pad) {
    auto currentLength = str.length();
    if (currentLength > length) {
        str.erase(length);
    }
    else {
        str.append(length - currentLength, pad);
    }
    return str;
}

std::string& pu::leftPadString(std::string& str, std::string::size_type length, std::string::value_type pad) {
    auto currentLength = str.length();
    if (currentLength > length) {
        str.erase(length);
    }
    else {
        str.insert(std::string::size_type(0), length - currentLength, pad);
    }
    return str;
}

std::string& pu::centerString(std::string& str, std::string::size_type width) {
    auto currentLength = str.length();
    if (currentLength > width) {
        str.erase(width);
    }
    else {
        std::string::size_type left = (width - currentLength) / 2; // integer divide truncate
        str.insert(std::string::size_type(0), left, ' ');
    }
    return str;
}

std::string pu::uintToString(uint32_t num, std::string::size_type length, std::string::value_type pad) {
    std::string str = std::to_string(num);
    if (0 == length) {
        // leave it, no length limit
    }
    else if (str.length() > length) {
        // too big already
        str.assign(length, '?');
    }
    else if (str.length() == length) {
        // leave it, already the right length
    }
    else {
        // not big enough, pad it
        pu::leftPadString(str, length, pad);
    }

    return str;
}

std::string pu::floatToString(float num, std::string::size_type length, int precision) {
    return pu::floatToString(static_cast<double>(num), length, precision);
}

std::string pu::floatToString(double num, std::string::size_type length, int precision) {
    std::stringstream ss;

    // Fixed number of decimal point precision
    ss << std::fixed << std::setprecision(precision) << num;

    std::string str = ss.str();

    if (0 == length) {
        // leave it, no length limit
    }
    else if (str.length() > length) {
        // too big already
        str.assign(length, '?');
    }
    else if (str.length() == length) {
        // leave it, already the right length
    }
    else {
        pu::leftPadString(str, length, ' ');
    }

    return str;
}

std::string pu::stringReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t startPos = 0;
    while ((startPos = str.find(from, startPos)) != std::string::npos) {
        str.replace(startPos, from.length(), to);
        startPos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

bool pu::stringContains(const std::string& str, char c) {
    return (str.find(c) != std::string::npos);
}

bool pu::stringContains(const std::string& str, const std::string& sub) {
    return (str.find(sub) != std::string::npos);
}
