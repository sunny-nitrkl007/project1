#include <stddef.h>
#include <math.h>

#include "../include/LpsCommonWeight.h"

static const struct { float interval; int precision; } format_intervals[] = {
        { 0.01, 2 },
        { 0.02, 2 },
        { 0.05, 2 },
        {  0.1, 1 },
        {  0.2, 1 },
        {  0.5, 1 },
        {    1, 0 },
        {    2, 0 },
        {    5, 0 },
        {   10, 0 },
        {   20, 0 },
        {   50, 0 },
        {  100, 0 },
        {  200, 0 },
        {  500, 0 },
};


float lps_common_weight_from_tonnes_f(float weight, LpsCommonWeightUnits_t to_units)
{
    float convertedWeight;
    switch (to_units) {
    case (LPSCOMMONWEIGHT_UNITS_KILOGRAM): {
        convertedWeight = weight * (float)LPSCOMMONWEIGHT_KGS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_POUND): {
        convertedWeight = weight * (float)LPSCOMMONWEIGHT_LBS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_TON): {
        convertedWeight = weight * (float)LPSCOMMONWEIGHT_TONS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_KILOPOUND): {
        convertedWeight = weight * (float)LPSCOMMONWEIGHT_KLBS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_TONNE):
    default: {
        convertedWeight = weight;
        break;
    }
    }
    return convertedWeight;
}

float lps_common_weight_to_tonnes_f(float weight, LpsCommonWeightUnits_t from_units)
{
    float convertedWeight;
    switch (from_units) {
    case (LPSCOMMONWEIGHT_UNITS_KILOGRAM): {
        convertedWeight = weight / (float)LPSCOMMONWEIGHT_KGS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_POUND): {
        convertedWeight = weight / (float)LPSCOMMONWEIGHT_LBS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_TON): {
        convertedWeight = weight / (float)LPSCOMMONWEIGHT_TONS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_KILOPOUND): {
        convertedWeight = weight / (float)LPSCOMMONWEIGHT_KLBS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_TONNE):
    default: {
        convertedWeight = weight;
        break;
    }
    }
    return convertedWeight;
}

double lps_common_weight_from_tonnes_d(double weight, LpsCommonWeightUnits_t to_units)
{
    double convertedWeight;
    switch (to_units) {
    case (LPSCOMMONWEIGHT_UNITS_KILOGRAM): {
        convertedWeight = weight * (double)LPSCOMMONWEIGHT_KGS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_POUND): {
        convertedWeight = weight * (double)LPSCOMMONWEIGHT_LBS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_TON): {
        convertedWeight = weight * (double)LPSCOMMONWEIGHT_TONS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_KILOPOUND): {
        convertedWeight = weight * (double)LPSCOMMONWEIGHT_KLBS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_TONNE):
    default: {
        convertedWeight = weight;
        break;
    }
    }
    return convertedWeight;
}

double lps_common_weight_to_tonnes_d(double weight, LpsCommonWeightUnits_t from_units)
{
    double convertedWeight;
    switch (from_units) {
    case (LPSCOMMONWEIGHT_UNITS_KILOGRAM): {
        convertedWeight = weight / (double)LPSCOMMONWEIGHT_KGS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_POUND): {
        convertedWeight = weight / (double)LPSCOMMONWEIGHT_LBS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_TON): {
        convertedWeight = weight / (double)LPSCOMMONWEIGHT_TONS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_KILOPOUND): {
        convertedWeight = weight / (double)LPSCOMMONWEIGHT_KLBS_PER_TONNE;
        break;
    }
    case (LPSCOMMONWEIGHT_UNITS_TONNE):
    default: {
        convertedWeight = weight;
        break;
    }
    }
    return convertedWeight;
}

bool lps_common_weight_min_interval(float capacity, int max_num_intervals, int* p_decimal_precision, float* p_interval)
{
    bool success = false;

    if (max_num_intervals > 0) {
        // Do not let the interval get smaller than this
        float min_interval = capacity / max_num_intervals;

        // Loop through the intervals in ascending order, finding the first (smallest) interval
        // that is greater than or equal to the minimum interval.
        for (int ii = 0; ii < sizeof(format_intervals)/sizeof(format_intervals[0]); ++ii) {
            float interval = format_intervals[ii].interval;
            if (interval >= min_interval) {
                // Found it, break;
                if (NULL != p_decimal_precision) {
                    *p_decimal_precision = format_intervals[ii].precision;
                }

                if (NULL != p_interval) {
                    *p_interval = interval;
                }

                success = true;
                break;
            }
        }
    }

    return success;
}

bool lps_common_weight_max_interval(float capacity, int min_num_intervals, int* p_decimal_precision, float* p_interval)
{
    bool success = false;

    if (min_num_intervals > 0) {
        // Do not let the interval get larger than this
        float max_interval = capacity / min_num_intervals;

        // Loop through the intervals in descending order, finding the first (largest) interval
        // that is less than or equal to the maximum interval.
        for (int ii = sizeof(format_intervals)/sizeof(format_intervals[0]); ii > 0; --ii) {
            float interval = format_intervals[ii-1].interval;
            if (interval <= max_interval) {
                // Found it, break;
                if (NULL != p_decimal_precision) {
                    *p_decimal_precision = format_intervals[ii-1].precision;
                }

                if (NULL != p_interval) {
                    *p_interval = interval;
                }

                success = true;
                break;
            }
        }
    }

    return success;
}

bool lps_common_weight_get_interval(float capacity, LpsCommonWeightPrecision_t precision, int* p_decimal_precision, float* p_interval)
{
    if (precision == LPSCOMMONWEIGHT_PRECISION_HIGH) {
        // For high precision, we want the smallest interval that doesn't result in over 1000 intervals.
        return lps_common_weight_min_interval(capacity, 1000, p_decimal_precision, p_interval);
    }
    else if (precision == LPSCOMMONWEIGHT_PRECISION_MEDIUM) {
        // For medium precision, we want the largest interval that doesn't result in under 500 intervals.
        return lps_common_weight_max_interval(capacity, 500, p_decimal_precision, p_interval);
    }
    else if (precision == LPSCOMMONWEIGHT_PRECISION_STANDARD) {
        // For standard precision, we want the largest interval that doesn't result in under 100 intervals.
        return lps_common_weight_max_interval(capacity, 100, p_decimal_precision, p_interval);
    }
    else {
        int decimal_precision;
        float interval;

        // If precision is not configured, it is legacy
        if (capacity < 100.f) {
            interval = 0.1f;
            decimal_precision = 1;
        }
        else if (capacity < 1000.f) {
            interval = 1.f;
            decimal_precision = 0;
        }
        else if (capacity < 10000.f) {
            interval = 10.f;
            decimal_precision = 0;
        }
        else {
            interval = 100.f;
            decimal_precision = 0;
        }

        if (NULL != p_decimal_precision) {
            *p_decimal_precision = decimal_precision;
        }

        if (NULL != p_interval) {
            *p_interval = interval;
        }

        return true;
    }
}

float lps_common_weight_round_f(float weight, float interval)
{
    if (interval > 0) {
        return floorf((weight / interval) + 0.5f) * interval;
    }
    else {
        return weight;
    }
}

double lps_common_weight_round_d(double weight, float interval)
{
    if (interval > 0) {
        return floor((weight / interval) + 0.5) * interval;
    }
    else {
        return weight;
    }
}
