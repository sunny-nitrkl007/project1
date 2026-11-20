#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <ais/log/Logger.h>

#include <chrono/print.hpp>
#include <fileio/sha1_fstream.hpp>
#include <fileio/oflocker.hpp>

#include "LpsSaTotalsLastLoad.h"

namespace fs = boost::filesystem;

/*
 * Load last load from storage
 */
bool LpsSaTotalsLastLoad::load(const fs::path& filePath) {
    bool success = false;
    tes_common_ais::sha1_ifstream ifs{ true }; // two_copy
    ifs.open(filePath.string(), std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia >> *this;
            AIS_LOG_INFO("Loaded last load from storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not deserialize last load from storage.");
            AIS_LOG_ERROR(e.what());
            reset();
        }
        catch (const std::exception& e) {
            AIS_LOG_ERROR("Could not deserialize last load from storage.");
            AIS_LOG_ERROR(e.what());
            reset();
        }
        catch (...) {
            AIS_LOG_ERROR("Could not deserialize last load from storage, unexpected error.");
            reset();
        }

        ifs.close();

        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                AIS_LOG_WARN("Last load file was corrupt... fixed it.");
            }
            else {
                AIS_LOG_ERROR("Last load file was corrupt... could not fix it.");
            }
        }
    }
    else {
        AIS_LOG_ERROR("Last load could not be opened from storage.");
    }

    return success;
}

/*
 * Save last load to storage
 */
bool LpsSaTotalsLastLoad::save(const fs::path& filePath) const {
    bool success = false;
    tes_common_ais::sha1_ofstream ofs{ true }; // two_copy
    ofs.open(filePath.string(), std::ios_base::out | std::ios_base::binary);
    if (ofs) {
        // Read the file in
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa << *this;
            AIS_LOG_INFO("Saved last load to storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not serialize last load to storage.");
            AIS_LOG_ERROR(e.what());
        }

        ofs.close();
    }
    else {
        AIS_LOG_ERROR("Last load could not be opened from storage.");
    }

    return success;
}

/*
 * Print to file
 */
bool LpsSaTotalsLastLoad::print(const boost::filesystem::path& filePath, const LpsSaTotalsPrinterInfo& printerInfo) const {
    bool success = false;

    { // Write to the file.
        tes_common_ais::OFlocker ofl(filePath);
        if (ofl) {
            toAscii(ofl.ofstream(), &printerInfo);
            ofl.close();
            success = true;
            AIS_LOG_INFO("Last load: printed ASCII file.");
        }
        else {
            AIS_LOG_ERROR("Last load: file could not be opened and locked for publishing.");
        }
    }

    if (!success) {
        try {
            if (boost::filesystem::is_regular_file(filePath)) {
                boost::filesystem::remove(filePath);
                AIS_LOG_WARN("Last load: file removed.");
            }
        }
        catch (const boost::filesystem::filesystem_error& e) {
            AIS_LOG_WARN("Last load: file could not be removed.");
        }
    }

    return success;
}

/*
 * Print to ASCII based on printer settings.
 */
void LpsSaTotalsLastLoad::toAscii(std::ostream& os, const LpsSaTotalsPrinterInfo* pPrinterInfo) const {
    const LpsSaTotalsPrinterInfo& printerInfo = (nullptr == pPrinterInfo) ? defaultPrinterInfo : *pPrinterInfo;
    printerInfo.loadRecordToAscii(loadRecord, os);
}

/*
 * Make last load printable to text.
 */
std::ostream& operator<<(std::ostream& os, const LpsSaTotalsLastLoad& o) {
    o.toAscii(os);
    return os;
}
