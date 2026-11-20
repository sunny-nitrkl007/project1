#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/archive_exception.hpp>

#include <ais/log/Logger.h>

#include <fileio/sha1_fstream.hpp>

#include "LpsSaTotalsLifetime.h"

namespace fs = boost::filesystem;

/*
 * Load lifetime totals from storage
 */
bool LpsSaTotalsLifetimeStorage::load(const fs::path& filePath) {
    bool success = false;
    tes_common_ais::sha1_ifstream ifs{ true }; // two_copy
    ifs.open(filePath.string(), std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia >> *this;
            AIS_LOG_INFO("Loaded lifetime totals from storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not deserialize lifetime totals from storage.");
            AIS_LOG_ERROR(e.what());
            reset();
        }
        catch (const std::exception& e) {
            AIS_LOG_ERROR("Could not deserialize lifetime totals from storage.");
            AIS_LOG_ERROR(e.what());
            reset();
        }
        catch (...) {
            AIS_LOG_ERROR("Could not deserialize lifetime totals from storage, unexpected error.");
            reset();
        }

        ifs.close();

        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                AIS_LOG_WARN("Lifetime totals file was corrupt... fixed it.");
            }
            else {
                AIS_LOG_ERROR("Lifetime totals file was corrupt... could not fix it.");
            }
        }
    }
    else {
        AIS_LOG_ERROR("Lifetime totals could not be opened from storage.");
    }

    return success;
}

/*
 * Save lifetime totals to storage
 */
bool LpsSaTotalsLifetimeStorage::save(const fs::path& filePath) {
    bool success = false;
    tes_common_ais::sha1_ofstream ofs{ true }; // two_copy
    ofs.open(filePath.string(), std::ios_base::out | std::ios_base::binary);
    if (ofs) {
        // Read the file in
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa << *this;
            AIS_LOG_INFO("Saved lifetime totals to storage.");
            success = true;
        }
        catch (const boost::archive::archive_exception& e) {
            AIS_LOG_ERROR("Could not serialize lifetime totals to storage.");
            AIS_LOG_ERROR(e.what());
        }

        ofs.close();
    }
    else {
        AIS_LOG_ERROR("Lifetime totals could not be opened from storage.");
    }

    return success;
}

/*
 * Make lifetime totals printable.
 */
std::ostream& operator<<(std::ostream& os, const LpsSaTotalsLifetimeStorage& o) {
    return os << "Totals (L: " << o.lifetime.loadCount << ", P: " << o.lifetime.passCount << ", W: " << o.lifetime.weightTonnes << ")";
}
