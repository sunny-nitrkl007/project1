#include <string>
#include <sstream>
#include <iomanip>

#include <hal_boot_proto.h>

#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/archive_exception.hpp>

#include <ais/log/Logger.h>

#include <chrono/print.hpp>
#include <fileio/sha1_fstream.hpp>

#include "LpsSaTotalsPrinterInfo.h"

namespace pu = LpsSaTotalsPrintUtils;
namespace fs = boost::filesystem;

static std::string applyStringSubstitutions(const std::string& templateStr,
        const LpsSaLoadRecordSubtotal& subtotal);

/*
 * Default printer info
 */
const LpsSaTotalsPrinterInfo defaultPrinterInfo = LpsSaTotalsPrinterInfo();

/*
 * Format the load record for printing to ascii
 */
void LpsSaTotalsPrinterInfo::loadRecordToAscii(const LpsSaLoadRecordChannelStorage& loadRecord,
        LpsSaTotalsPrinterInfo::AppendLineFunc appendLineFunc) const {
    using tes_common_ais::putLocalTime;

    // Determine weight units
    struct {
        LpsCommonWeightUnits units;
        int decimalPrecision;
        float interval;
    } wt = {
        loadRecord.weightUnits(),
        loadRecord.weightDecimalPrecision(),
        loadRecord.weightInterval()
    };

    // If the weigh units wasn't in the load record, use the current settings.
    if ((wt.interval <= 0) || (wt.decimalPrecision < 0)) {
        wt.units = weightUnits;
        wt.decimalPrecision = weightDecimalPrecision;
        wt.interval = weightInterval;
    }

    // Leading blank lines
    uint8_t leadingBlankLines = std::min(config.leadingBlankLines, uint8_t(3));
    for (uint8_t ii = 0; ii < leadingBlankLines; ++ii) {
        appendLineFunc("");
    }

    auto subtotalCount = loadRecord.subtotalCount();
    const auto& firstSubtotal = loadRecord.getSubtotalByIndex(1);
    const auto& lastSubtotal = loadRecord.getCurrentSubtotal();

    // Print the headers
    if (config.truckTicket.headerEnabled) {
        bool headerPrinted = false;

        if (!config.truckTicket.headerLine1.empty()) {
            appendLineFunc(applyStringSubstitutions(config.truckTicket.headerLine1, lastSubtotal));
            headerPrinted = true;
        }

        if (!config.truckTicket.headerLine2.empty()) {
            appendLineFunc(applyStringSubstitutions(config.truckTicket.headerLine2, lastSubtotal));
            headerPrinted = true;
        }

        if (!config.truckTicket.headerLine3.empty()) {
            appendLineFunc(applyStringSubstitutions(config.truckTicket.headerLine3, lastSubtotal));
            headerPrinted = true;
        }

        if (headerPrinted) {
            appendLineFunc("");
        }
    }

    { // Print the product identification number
        std::string str = loadRecord.productId();
        if (!str.empty()) {
            appendLineFunc("PIN: " + pu::leftPadString(str, 36 - 5));
        }
    }

    { // Print the equipment id
        std::string str = loadRecord.equipmentId();
        if (!str.empty()) {
            appendLineFunc("EQ ID: " + pu::leftPadString(str, 36 - 7));
        }
    }

    { // Print the ecm serial number
        hal_ecm_serialno_t serialNum = hal_boot_get_ecm_serialno();
        std::string str = std::string(reinterpret_cast<const char*>(serialNum.string), serialNum.length);
        appendLineFunc("ECM SN: " + pu::leftPadString(str, 36 - 8));
    }

    { // Print the ticket id
        std::string str = loadRecord.ticketId();
        appendLineFunc("ID: " + pu::leftPadString(str, 36 - 4));
    }

    // Print store time if enabled
    if (config.truckTicket.storeTimeEnabled) {
        { // Date
            std::string dateStr = putLocalTime(loadRecord.storeTime.utcTime, dateFormatString());
            appendLineFunc("Date: " + pu::leftPadString(dateStr, 36 - 6));
        }

        { // Time
            std::string timeStr = putLocalTime(loadRecord.storeTime.utcTime, tes_common_ais::date_time_formats::HH_MM_24HR);
            appendLineFunc("Time: " + pu::leftPadString(timeStr, 36 - 6));
        }
    }

    { // Print the ticket number
        std::string str = pu::uintToString(loadRecord.ticketNumber());
        appendLineFunc("Ticket Number: " + pu::leftPadString(str, 36 - 15));
    }

    { // Total pass count
        std::string str = pu::uintToString(loadRecord.passCount());
        appendLineFunc("Number of Passes: " + pu::leftPadString(str, 36 - 18));
    }

    // Blank line
    appendLineFunc("");

    // Print the horizontal rule
    if ((legalForTradeInstalled) &&
            (LpsSaLoadRecordStoreAction::TICKET_NOT_FOR_TRADE == loadRecord.storeAction())) {
        appendLineFunc("------- Not Legal for Trade --------");
    }
    else {
        appendLineFunc("------------------------------------");
    }

    // initialize with first subtotal
    std::string prevTruckName = firstSubtotal.truckName;
    std::string prevMaterialName = firstSubtotal.materialName;
    std::string prevTag1Name = firstSubtotal.tag1;
    std::string prevTag2Name = firstSubtotal.tag2;
    std::string prevTag3Name = firstSubtotal.tag3;
    std::string prevTag4Name = firstSubtotal.tag4;

    for (uint32_t x = 1; x <= subtotalCount; ++x) {
        const auto& subtotal = loadRecord.getSubtotalByIndex(x);

        // Print the tags if any is different from previous subtotal
        if ((1 == x) ||
                (prevTruckName.compare(subtotal.truckName) != 0) ||
                (prevMaterialName.compare(subtotal.materialName) != 0) ||
                (prevTag1Name.compare(subtotal.tag1) != 0) ||
                (prevTag2Name.compare(subtotal.tag2) != 0) ||
                (prevTag3Name.compare(subtotal.tag3) != 0) ||
                (prevTag4Name.compare(subtotal.tag4) != 0)) {

            if (x != 1) {
                // Print the horizontal rule if this is not the first subtotal
                appendLineFunc("------------------------------------");
            }

            // Print truck name if enabled
            if (config.truckTicket.truckIdEnabled) {
                std::string str = subtotal.truckName;
                prevTruckName = str;
                appendLineFunc("Truck: " + pu::leftPadString(str, 36 - 7));
            }

            // Print material name if enabled
            if (config.truckTicket.materialIdEnabled) {
                std::string str = subtotal.materialName;
                prevMaterialName = str;
                appendLineFunc("Material: " + pu::leftPadString(str, 36 - 10));
            }

            // Print Custom List 1 if enabled
            if (!firstSubtotal.customListName1.empty()) {
                std::string tag = subtotal.tag1;
                prevTag1Name = tag;
                std::string tagName = subtotal.customListName1;
                tagName = tagName.substr(0, 14);
                tag = tag.substr(0, (36 - tagName.length() - 2));
                appendLineFunc(tagName + ": " + pu::leftPadString(tag, (36 - tagName.length() - 2)));
            }

            // Print Custom List 2 if enabled
            if (!firstSubtotal.customListName2.empty()) {
                std::string tag = subtotal.tag2;
                prevTag2Name = tag;
                std::string tagName = subtotal.customListName2;
                tagName = tagName.substr(0, 14);
                tag = tag.substr(0, (36 - tagName.length() - 2));
                appendLineFunc(tagName + ": " + pu::leftPadString(tag, (36 - tagName.length() - 2)));
            }

            // Print Custom List 3 if enabled
            if (!firstSubtotal.customListName3.empty()) {
                std::string tag = subtotal.tag3;
                prevTag3Name = tag;
                std::string tagName = subtotal.customListName3;
                tagName = tagName.substr(0, 14);
                tag = tag.substr(0, (36 - tagName.length() - 2));
                appendLineFunc(tagName + ": " + pu::leftPadString(tag, (36 - tagName.length() - 2)));
            }

            // Print Custom List 4 if enabled
            if (!firstSubtotal.customListName4.empty()) {
                std::string tag = subtotal.tag4;
                prevTag4Name = tag;
                std::string tagName = subtotal.customListName4;
                tagName = tagName.substr(0, 14);
                tag = tag.substr(0, (36 - tagName.length() - 2));
                appendLineFunc(tagName + ": " + pu::leftPadString(tag, (36 - tagName.length() - 2)));
            }
        }

        // Print the individual bucket weights
        if ((config.truckTicket.bucketWeightsEnabled) ||
                (LpsSaLoadRecordStoreAction::TICKET_LEGAL_FOR_TRADE == loadRecord.storeAction())) {
            // Blank line
            appendLineFunc("");

            // Loop through only the last 25 passes
            auto size = subtotal.passCount();
            decltype(subtotal.passCount()) ii;

            if (size >= 25) {
                ii = size - 25;
            }
            else {
                ii = 0;
            }

            const auto& passes = subtotal.passes();
            for (; ii < size; ++ii) {
                std::string iiStr = pu::uintToString(ii+1, 2, '0');
                std::string weightStr = weightToString(passes[ii].weightTonnes, wt.units, wt.decimalPrecision, wt.interval);
                std::string unitsStr = weightUnitsString(wt.units);

                appendLineFunc("#" + iiStr + pu::leftPadString(weightStr, 36 - (3 + 1 + unitsStr.length())) + " " + unitsStr);
            }

            if (subtotalCount > 1) {
                std::string weightStr = weightToString(subtotal.weightTonnes(), wt.units, wt.decimalPrecision, wt.interval);
                std::string unitsStr = weightUnitsString(wt.units);
                appendLineFunc("Subtotal" + pu::leftPadString(weightStr, 36 - (8 + 1 + unitsStr.length())) + " " + unitsStr);
            }
        }
    }

    // Print truck weight if enabled
    if ((config.truckTicket.truckWeightEnabled) ||
            (LpsSaLoadRecordStoreAction::TICKET_LEGAL_FOR_TRADE == loadRecord.storeAction())) {
        // Print the horizontal rule
        appendLineFunc("");
        appendLineFunc("------------------------------------");
        std::string weightStr = weightToString(loadRecord.weightTonnes(), wt.units, wt.decimalPrecision, wt.interval);
        std::string unitsStr = weightUnitsString(wt.units);
        appendLineFunc("Receipt of: " + pu::leftPadString(weightStr, 36 - (12 + 1 + unitsStr.length())) + " " + unitsStr);
    }

    // Print the footer
    if (!config.truckTicket.footerLine1.empty()) {
        appendLineFunc("");
        appendLineFunc(applyStringSubstitutions(config.truckTicket.footerLine1, lastSubtotal));
    }

    // Trailing blank lines
    uint8_t trailingBlankLines = std::min(config.trailingBlankLines, uint8_t(3));
    for (uint8_t ii = 0; ii < trailingBlankLines; ++ii) {
        appendLineFunc("");
    }
}

/*
 * Date format string
 *  Get the date format string based on the current setting for format and separator.
 */
const char* LpsSaTotalsPrinterInfo::dateFormatString() const {
    const char* dateFormatStr = tes_common_ais::date_time_formats::YYYY_MM_DD_HYPHEN;

    if (LpsSaTotalsPrinterCnfgDateSeparator::HYPHEN == config.dateSeparator) {
        switch (config.dateFormat) {
        case (LpsSaTotalsPrinterCnfgDateFormat::YYYY_MM_DD): {
            dateFormatStr = tes_common_ais::date_time_formats::YYYY_MM_DD_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YYYY): {
            dateFormatStr = tes_common_ais::date_time_formats::MM_DD_YYYY_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YYYY): {
            dateFormatStr = tes_common_ais::date_time_formats::DD_MM_YYYY_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::YY_MM_DD): {
            dateFormatStr = tes_common_ais::date_time_formats::YY_MM_DD_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YY): {
            dateFormatStr = tes_common_ais::date_time_formats::MM_DD_YY_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YY): {
            dateFormatStr = tes_common_ais::date_time_formats::DD_MM_YY_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD): {
            dateFormatStr = tes_common_ais::date_time_formats::MM_DD_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM): {
            dateFormatStr = tes_common_ais::date_time_formats::DD_MM_HYPHEN;
            break;
        }
        }
    }
    else if (LpsSaTotalsPrinterCnfgDateSeparator::SLASH == config.dateSeparator) {
        switch (config.dateFormat) {
        case (LpsSaTotalsPrinterCnfgDateFormat::YYYY_MM_DD): {
            dateFormatStr = tes_common_ais::date_time_formats::YYYY_MM_DD_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YYYY): {
            dateFormatStr = tes_common_ais::date_time_formats::MM_DD_YYYY_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YYYY): {
            dateFormatStr = tes_common_ais::date_time_formats::DD_MM_YYYY_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::YY_MM_DD): {
            dateFormatStr = tes_common_ais::date_time_formats::YY_MM_DD_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YY): {
            dateFormatStr = tes_common_ais::date_time_formats::MM_DD_YY_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YY): {
            dateFormatStr = tes_common_ais::date_time_formats::DD_MM_YY_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD): {
            dateFormatStr = tes_common_ais::date_time_formats::MM_DD_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM): {
            dateFormatStr = tes_common_ais::date_time_formats::DD_MM_SLASH;
            break;
        }
        }
    }

    return dateFormatStr;
}

/*
 * Date/Time format string
 *  Get the date/time format string based on the current setting for format and separator.
 */
const char* LpsSaTotalsPrinterInfo::dateTimeFormatString() const {
    const char* dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_YYYY_MM_DD_HYPHEN;

    if (LpsSaTotalsPrinterCnfgDateSeparator::HYPHEN == config.dateSeparator) {
        switch (config.dateFormat) {
        case (LpsSaTotalsPrinterCnfgDateFormat::YYYY_MM_DD): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_YYYY_MM_DD_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YYYY): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_MM_DD_YYYY_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YYYY): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_DD_MM_YYYY_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::YY_MM_DD): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_YY_MM_DD_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YY): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_MM_DD_YY_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YY): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_DD_MM_YY_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_MM_DD_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_DD_MM_HYPHEN;
            break;
        }
        }
    }
    else if (LpsSaTotalsPrinterCnfgDateSeparator::SLASH == config.dateSeparator) {
        switch (config.dateFormat) {
        case (LpsSaTotalsPrinterCnfgDateFormat::YYYY_MM_DD): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_YYYY_MM_DD_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YYYY): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_MM_DD_YYYY_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YYYY): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_DD_MM_YYYY_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::YY_MM_DD): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_YY_MM_DD_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YY): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_MM_DD_YY_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YY): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_DD_MM_YY_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_MM_DD_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_DD_MM_SLASH;
            break;
        }
        }
    }

    return dateTimeFormatStr;
}

/*
 * Date format string short
 *  Get the short date format string based on the current setting for format and separator.
 */
const char* LpsSaTotalsPrinterInfo::dateFormatStringShort() const {
    const char* dateFormatStr = tes_common_ais::date_time_formats::MM_DD_HYPHEN;

    if (LpsSaTotalsPrinterCnfgDateSeparator::HYPHEN == config.dateSeparator) {
        switch (config.dateFormat) {
        case (LpsSaTotalsPrinterCnfgDateFormat::YYYY_MM_DD):
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YYYY):
        case (LpsSaTotalsPrinterCnfgDateFormat::YY_MM_DD):
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YY):
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD): {
            dateFormatStr = tes_common_ais::date_time_formats::MM_DD_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YYYY):
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YY):
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM): {
            dateFormatStr = tes_common_ais::date_time_formats::DD_MM_HYPHEN;
            break;
        }
        }
    }
    else if (LpsSaTotalsPrinterCnfgDateSeparator::SLASH == config.dateSeparator) {
        switch (config.dateFormat) {
        case (LpsSaTotalsPrinterCnfgDateFormat::YYYY_MM_DD):
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YYYY):
        case (LpsSaTotalsPrinterCnfgDateFormat::YY_MM_DD):
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YY):
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD): {
            dateFormatStr = tes_common_ais::date_time_formats::MM_DD_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YYYY):
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YY):
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM): {
            dateFormatStr = tes_common_ais::date_time_formats::DD_MM_SLASH;
            break;
        }
        }
    }

    return dateFormatStr;
}

/*
 * Date/Time format string short
 *  Get the short date/time format string based on the current setting for format and separator.
 */
const char* LpsSaTotalsPrinterInfo::dateTimeFormatStringShort() const {
    const char* dateTimeFormatStr = tes_common_ais::date_time_formats::MM_DD_HYPHEN;

    if (LpsSaTotalsPrinterCnfgDateSeparator::HYPHEN == config.dateSeparator) {
        switch (config.dateFormat) {
        case (LpsSaTotalsPrinterCnfgDateFormat::YYYY_MM_DD):
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YYYY):
        case (LpsSaTotalsPrinterCnfgDateFormat::YY_MM_DD):
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YY):
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_MM_DD_HYPHEN;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YYYY):
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YY):
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_DD_MM_HYPHEN;
            break;
        }
        }
    }
    else if (LpsSaTotalsPrinterCnfgDateSeparator::SLASH == config.dateSeparator) {
        switch (config.dateFormat) {
        case (LpsSaTotalsPrinterCnfgDateFormat::YYYY_MM_DD):
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YYYY):
        case (LpsSaTotalsPrinterCnfgDateFormat::YY_MM_DD):
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD_YY):
        case (LpsSaTotalsPrinterCnfgDateFormat::MM_DD): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_MM_DD_SLASH;
            break;
        }
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YYYY):
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM_YY):
        case (LpsSaTotalsPrinterCnfgDateFormat::DD_MM): {
            dateTimeFormatStr = tes_common_ais::date_time_formats::HH_MM_24HR_DD_MM_SLASH;
            break;
        }
        }
    }

    return dateTimeFormatStr;
}

/*
 * Load printer info from storage
 */
bool LpsSaTotalsPrinterInfo::load(const fs::path& filePath) {
    bool success = false;
    tes_common_ais::sha1_ifstream ifs{ true }; // two_copy
    ifs.open(filePath.string(), std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia >> *this;
            AIS_LOG_INFO("Loaded printer info from storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not deserialize printer info from storage.");
            AIS_LOG_ERROR(e.what());
            reset();
        }
        catch (const std::exception& e) {
            AIS_LOG_ERROR("Could not deserialize printer info from storage.");
            AIS_LOG_ERROR(e.what());
            reset();
        }
        catch (...) {
            AIS_LOG_ERROR("Could not deserialize printer info from storage, unexpected error.");
            reset();
        }

        ifs.close();

        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                AIS_LOG_WARN("Printer info file was corrupt... fixed it.");
            }
            else {
                AIS_LOG_ERROR("Printer info file was corrupt... could not fix it.");
            }
        }
    }
    else {
        AIS_LOG_ERROR("Printer info could not be opened from storage.");
    }

    return success;
}

/*
 * Save printer info to storage
 */
bool LpsSaTotalsPrinterInfo::save(const fs::path& filePath) const {
    bool success = false;
    tes_common_ais::sha1_ofstream ofs{ true }; // two_copy
    ofs.open(filePath.string(), std::ios_base::out | std::ios_base::binary);
    if (ofs) {
        // Read the file in
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa << *this;
            AIS_LOG_INFO("Saved printer info to storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not serialize printer info to storage.");
            AIS_LOG_ERROR(e.what());
        }

        ofs.close();
    }
    else {
        AIS_LOG_ERROR("Printer info could not be opened from storage.");
    }

    return success;
}

/*
 * Do all string substitutions.
 */
static std::string applyStringSubstitutions(const std::string& templateStr,
        const LpsSaLoadRecordSubtotal& subtotal) {
    std::string str(templateStr);
    boost::replace_all(str, "&(t)", subtotal.truckName);
    boost::replace_all(str, "&(T)", subtotal.truckName);
    boost::replace_all(str, "&(m)", subtotal.materialName);
    boost::replace_all(str, "&(M)", subtotal.materialName);
    boost::replace_all(str, "&(1)", subtotal.tag1);
    boost::replace_all(str, "&(2)", subtotal.tag2);
    boost::replace_all(str, "&(3)", subtotal.tag3);
    boost::replace_all(str, "&(4)", subtotal.tag4);
    return str;
}

