/*
 * LpsSaTotalsPrintUtils.h
 *
 *  Created on: Jan 17, 2023
 *      Author: pf
 */

#ifndef LPSSATOTALSPRINTUTILS_H_
#define LPSSATOTALSPRINTUTILS_H_

#include <string>

#include <LpsCommonWeight.h>

#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>

namespace LpsSaTotalsPrintUtils {

    // Printer formatting helper functions
    std::string& rightPadString(std::string& str, std::string::size_type length, std::string::value_type pad = ' ');
    std::string& leftPadString(std::string& str, std::string::size_type length, std::string::value_type pad = ' ');
    std::string& centerString(std::string& str, std::string::size_type width);
    std::string uintToString(uint32_t num, std::string::size_type length = 0, std::string::value_type pad = ' ');
    std::string floatToString(float num, std::string::size_type length = 0, int precision = 2);
    std::string floatToString(double num, std::string::size_type length = 0, int precision = 2);
    std::string stringReplaceAll(std::string str, const std::string& from, const std::string& to);
    bool stringContains(const std::string& str, char c);
    bool stringContains(const std::string& str, const std::string& sub);

    const char* weightUnitsString(const LpsCommonWeightUnits& weightUnits);

    template<typename T, typename std::enable_if<std::is_floating_point<T>::value, bool>::type = true>
    inline std::string weightToString(T weight, std::string::size_type length,
            const LpsCommonWeightUnits& weightUnits, int weightDecimalPrecision, float weightInterval) {
        weight = lps_common_weight_from_tonnes(weight, weightUnits);
        weight = lps_common_weight_round(weight, weightInterval);
        return floatToString(weight, length, weightDecimalPrecision);
    }
};

#endif /* LPSSATOTALSPRINTUTILS_H_ */
