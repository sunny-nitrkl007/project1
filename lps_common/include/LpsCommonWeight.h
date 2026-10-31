#ifndef LPSCOMMONWEIGHT_H_
#define LPSCOMMONWEIGHT_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    LPSCOMMONWEIGHT_UNITS_KILOGRAM = 0x03DB,
    LPSCOMMONWEIGHT_UNITS_POUND = 0x03DC,
    LPSCOMMONWEIGHT_UNITS_TON = 0x03DD,
    LPSCOMMONWEIGHT_UNITS_TONNE = 0x03DE,
    LPSCOMMONWEIGHT_UNITS_KILOPOUND = 0x07D7
} LpsCommonWeightUnits_t;

typedef enum {
    LPSCOMMONWEIGHT_PRECISION_HIGH = 0x0003,
    LPSCOMMONWEIGHT_PRECISION_MEDIUM = 0x0030,
    LPSCOMMONWEIGHT_PRECISION_STANDARD = 0x003D,
    LPSCOMMONWEIGHT_PRECISION_NOT_CONFIGURED = 0x002C
} LpsCommonWeightPrecision_t;

#define LPSCOMMONWEIGHT_TONS_PER_TONNE (1.10231)
#define LPSCOMMONWEIGHT_KLBS_PER_TONNE (2.20462)
#define LPSCOMMONWEIGHT_KGS_PER_TONNE  (1000.00)
#define LPSCOMMONWEIGHT_LBS_PER_TONNE  (2204.62)

#ifdef __cplusplus
extern "C" {
#endif

float lps_common_weight_from_tonnes_f(float weight, LpsCommonWeightUnits_t to_units);
float lps_common_weight_to_tonnes_f(float weight, LpsCommonWeightUnits_t from_units);

double lps_common_weight_from_tonnes_d(double weight, LpsCommonWeightUnits_t to_units);
double lps_common_weight_to_tonnes_d(double weight, LpsCommonWeightUnits_t from_units);

bool lps_common_weight_min_interval(float capacity, int max_num_intervals, int* p_decimal_precision, float* p_interval);
bool lps_common_weight_max_interval(float capacity, int min_num_intervals, int* p_decimal_precision, float* p_interval);
bool lps_common_weight_get_interval(float capacity, LpsCommonWeightPrecision_t precision, int* p_decimal_precision, float* p_interval);

float lps_common_weight_round_f(float weight, float interval);
double lps_common_weight_round_d(double weight, float interval);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

#include <string>
#include <sstream>
#include <iomanip>
#include <type_traits>

enum class LpsCommonWeightUnits : uint16_t {
    KG = LPSCOMMONWEIGHT_UNITS_KILOGRAM,
    LB = LPSCOMMONWEIGHT_UNITS_POUND,
    TON = LPSCOMMONWEIGHT_UNITS_TON,
    TONNE = LPSCOMMONWEIGHT_UNITS_TONNE,
    KLB = LPSCOMMONWEIGHT_UNITS_KILOPOUND
};

#define LpsCommonWeightUnits_Base_t(val) (static_cast<typename std::underlying_type<LpsCommonWeightUnits>::type>(val))

enum class LpsCommonWeightPrecision : uint16_t {
    HIGH = LPSCOMMONWEIGHT_PRECISION_HIGH,
    MEDIUM = LPSCOMMONWEIGHT_PRECISION_MEDIUM,
    STANDARD = LPSCOMMONWEIGHT_PRECISION_STANDARD,
    NOT_CONFIGURED = LPSCOMMONWEIGHT_PRECISION_NOT_CONFIGURED
};

#define LpsCommonWeightPrecision_Base_t(val) (static_cast<typename std::underlying_type<LpsCommonWeightPrecision>::type>(val))

inline double lps_common_weight_from_tonnes(double weight, LpsCommonWeightUnits toUnits) {
    return lps_common_weight_from_tonnes_d(weight, static_cast<LpsCommonWeightUnits_t>(toUnits));
}

inline float lps_common_weight_from_tonnes(float weight, LpsCommonWeightUnits toUnits) {
    return lps_common_weight_from_tonnes_f(weight, static_cast<LpsCommonWeightUnits_t>(toUnits));
}

inline double lps_common_weight_to_tonnes(double weight, LpsCommonWeightUnits fromUnits) {
    return lps_common_weight_to_tonnes_d(weight, static_cast<LpsCommonWeightUnits_t>(fromUnits));
}

inline float lps_common_weight_to_tonnes(float weight, LpsCommonWeightUnits fromUnits) {
    return lps_common_weight_to_tonnes_f(weight, static_cast<LpsCommonWeightUnits_t>(fromUnits));
}

inline bool lps_common_weight_get_interval(float capacity, LpsCommonWeightPrecision precision, int& decimalPrecision, float& interval) {
    return lps_common_weight_get_interval(capacity, static_cast<LpsCommonWeightPrecision_t>(precision), &decimalPrecision, &interval);
}

inline double lps_common_weight_round(double weight, float interval) {
    return lps_common_weight_round_d(weight, interval);
}

inline float lps_common_weight_round(float weight, float interval) {
    return lps_common_weight_round_f(weight, interval);
}

inline std::string lps_common_weight_to_string(double weight, int precision, float interval) {

    weight = lps_common_weight_round(weight, interval);

    std::stringstream ss;

    // Fixed number of decimal point precision
    ss << std::fixed << std::setprecision(precision) << weight;

    return ss.str();
}

inline std::string lps_common_weight_to_string(float weight, int precision, float interval) {

    weight = lps_common_weight_round(weight, interval);

    std::stringstream ss;

    // Fixed number of decimal point precision
    ss << std::fixed << std::setprecision(precision) << weight;

    return ss.str();
}

#endif

#endif /* LPSCOMMONWEIGHT_H_ */
