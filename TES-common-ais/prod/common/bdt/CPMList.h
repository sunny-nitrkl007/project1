#ifndef BDT_CPMLIST_H
#define BDT_CPMLIST_H

#include <cstdint>

namespace tes_common_ais {
    enum class CPMListWeightUnits : uint8_t {
        TONNES, // Metric tonnes
        TONS, // English Tons
        KLBS, // Thousands of pounds
        KGS, // Kilograms
        LBS // Pounds
    };
}

#endif
