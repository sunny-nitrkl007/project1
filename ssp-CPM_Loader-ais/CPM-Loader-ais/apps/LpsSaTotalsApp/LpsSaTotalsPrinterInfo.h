#ifndef LPSSATOTALSPRINTERINFO_H
#define LPSSATOTALSPRINTERINFO_H

#include <cstdint>
#include <string>
#include <type_traits>
#include <functional>

#include <boost/filesystem.hpp>
#include <boost/serialization/version.hpp>

#include <LpsCommonWeight.h>

#include <interfaces/LpsSaTotals/PrinterCnfg.hpp>
#include <interfaces/LpsSaUI/DisplaySettings.hpp>

#include "LpsSaTotalsPrintUtils.h"

struct LpsSaTotalsPrinterInfo {
public:
    LpsSaTotalsPrinterCnfg config;

    struct Totals {
        uint32_t numTruckTickets; // Do extra copies go here?
        uint32_t numAdditionalTruckTickets; // Or here?
        uint32_t numTruckReports;
        uint32_t numMaterialReports;
        uint32_t numTruckTotals;
        uint32_t numTag1Reports;
        uint32_t numTag2Reports;
        uint32_t numTag3Reports;
        uint32_t numTag4Reports;
    } totals;

    bool legalForTradeInstalled;
    LpsCommonWeightUnits weightUnits;
    int weightDecimalPrecision;
    float weightInterval;

    LpsSaTotalsPrinterInfo() :
        config(),
        totals(),
        legalForTradeInstalled(false),
        weightUnits(LpsCommonWeightUnits::TONNE),
        weightDecimalPrecision(2),
        weightInterval(0.01f) {}

    typedef std::function<void(const std::string& line)> AppendLineFunc;

    void loadRecordToAscii(const LpsSaLoadRecordChannelStorage& loadRecord, AppendLineFunc appendLineFunc) const;

    inline void loadRecordToAscii(const LpsSaLoadRecordChannelStorage& loadRecord, std::ostream& os) const {
        loadRecordToAscii(loadRecord, [&os](const std::string& line) {
            os << line << "\n";
        });
    }

    static inline const char* weightUnitsString(const LpsCommonWeightUnits& weightUnits) {
        return LpsSaTotalsPrintUtils::weightUnitsString(weightUnits);
    }

    inline const char* weightUnitsString() const {
        return LpsSaTotalsPrintUtils::weightUnitsString(weightUnits);
    }

    const char* dateFormatString() const;
    const char* dateTimeFormatString() const;
    const char* dateFormatStringShort() const;
    const char* dateTimeFormatStringShort() const;

    template<typename T, typename std::enable_if<std::is_floating_point<T>::value, bool>::type = true>
    static inline std::string weightToString(T weight, const LpsCommonWeightUnits& weightUnits,
            int weightDecimalPrecision, float weightInterval, std::string::size_type length = 0) {
        return LpsSaTotalsPrintUtils::weightToString(weight, length, weightUnits, weightDecimalPrecision, weightInterval);
    }

    template<typename T, typename std::enable_if<std::is_floating_point<T>::value, bool>::type = true>
    inline std::string weightToString(T weight, std::string::size_type length = 0) const {
        return LpsSaTotalsPrintUtils::weightToString(weight, length, weightUnits, weightDecimalPrecision, weightInterval);
    }

    inline void reset() {
        *this = LpsSaTotalsPrinterInfo();
    }

    bool load(const boost::filesystem::path& filePath);
    bool save(const boost::filesystem::path& filePath) const;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & config;

        ar & totals.numTruckTickets;
        ar & totals.numAdditionalTruckTickets;
        ar & totals.numTruckReports;
        ar & totals.numMaterialReports;

        if (version >= 1) {
            ar & weightUnits;
        }

        if (version >= 2) {
            ar & totals.numTag1Reports;
            ar & totals.numTag2Reports;
            ar & totals.numTag3Reports;
            ar & totals.numTag4Reports;
            ar & totals.numTruckTotals;
        }

        if (version >= 3) {
            ar & weightDecimalPrecision;
            ar & weightInterval;
        }

        if (version >= 4) {
            ar & legalForTradeInstalled;
        }
    }
};

BOOST_CLASS_VERSION(LpsSaTotalsPrinterInfo, 4);

// Default printer info
extern const LpsSaTotalsPrinterInfo defaultPrinterInfo;

#endif
