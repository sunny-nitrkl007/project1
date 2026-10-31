#pragma once

#include <algorithm>
#include <string>
#include <exception>
#include <boost/filesystem.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include <ais/log/AisLogger.h>

#include "sha1_fstream.hpp"
#include "directory.hpp"

#ifndef FILEIO_NVM_HPP
#define FILEIO_NVM_HPP

namespace tes_common_ais
{
namespace nvm
{
namespace fs = boost::filesystem;

///////////////////////////////////////////////////////////////////////////////////////////////////
/// @Loads the nvmData object from NVM using two copy SHA-1.
///  Returns true if successful, false otherwise.
///  nvmData must either be POD or implement boost::serialize.
//////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool read(const fs::path &path, const std::string &fileName, T &nvmData) {
    bool success = false;

    if (!directory::create(path)) {
        return success;
    }

    std::string filePath = directory::makeFilePath(path, fileName);

    tes_common_ais::sha1_ifstream ifs{true}; // Two copy
    ifs.open(filePath, std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia &nvmData;
            AIS_LOG_INFO("Successfully loaded the data from %s", filePath.c_str());
            success = true;
        }
        catch (const boost::archive::archive_exception &e) {
            AIS_LOG_ERROR("Could not deserialize data from storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (const std::exception &e) {
            AIS_LOG_ERROR("Could not deserialize data from storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (...) {
            AIS_LOG_ERROR("Could not deserialize data from storage, unexpected error.");
        }
        ifs.close();
        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                AIS_LOG_WARN("The file was corrupt... fixed it.");
            } else {
                AIS_LOG_ERROR("The file was corrupt... could not fix it.");
            }
        }
    }
    else {
        AIS_LOG_ERROR("file could not be opened from storage.");
    }
    return success;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @Saves the provided nvmData to NVM using two copy SHA-1.
///  Returns true if successful, false otherwise.
///  nvmData must either be POD or implement boost::serialize.  It may also not be a literal.
/////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
inline bool store(const fs::path &path, const std::string &fileName, const T &nvmData) {
    bool success = false;

    if (!directory::create(path)) {
        return success;
    }

    std::string filePath = directory::makeFilePath(path, fileName);

    tes_common_ais::sha1_ofstream ofs{true};  // Two copy
    ofs.open(filePath, std::ios_base::out | std::ios_base::binary);
    if (ofs) {
        // Write to the file
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa &nvmData;
            AIS_LOG_INFO("Successfully saved the data to %s", filePath.c_str());
            success = true;
        }
        catch (const boost::archive::archive_exception &e) {
            AIS_LOG_ERROR("Could not serialize the data to storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (const std::exception &e) {
            AIS_LOG_ERROR("Could not serialize data from storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (...) {
            AIS_LOG_ERROR("Could not serialize data from storage, unexpected error.");
        }
        ofs.close();
    }
    else {
        AIS_LOG_ERROR(" file could not be saved to storage.");
    }
    return success;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/// @Loads the nvmData objects from NVM using two copy SHA-1.
///  Returns true if successful, false otherwise.
///  nvmData objects must either be POD or implement boost::serialize.
//////////////////////////////////////////////////////////////////////////////////////////////////
template <typename First, typename... Rest>
static bool read(const fs::path& path, const std::string& fileName, First&& first, Rest&&... rest) {
    bool success = false;

    if (!directory::create(path)) {
        return success;
    }

    std::string filePath = directory::makeFilePath(path, fileName);

    tes_common_ais::sha1_ifstream ifs{true}; // Two copy
    ifs.open(filePath, std::ios_base::in | std::ios_base::binary);
    if (ifs) {
        // Read the file in
        try {
            boost::archive::binary_iarchive ia(ifs);
            ia & std::forward<First>(first);
            using expander = int[];
            (void)expander{0, (void(ia & std::forward<Rest>(rest)), 0)...};
            AIS_LOG_INFO("Successfully loaded the data from %s", filePath.c_str());
            success = true;
        }
        catch (const boost::archive::archive_exception &e) {
            AIS_LOG_ERROR("Could not deserialize data from storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (const std::exception &e) {
            AIS_LOG_ERROR("Could not deserialize data from storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (...) {
            AIS_LOG_ERROR("Could not deserialize data from storage, unexpected error.");
        }
        ifs.close();
        if (ifs.is_corrupt()) {
            if (ifs.fix_it()) {
                AIS_LOG_WARN("The file was corrupt... fixed it.");
            } else {
                AIS_LOG_ERROR("The file was corrupt... could not fix it.");
            }
        }
    }
    else {
        AIS_LOG_ERROR("file could not be opened from storage.");
    }
    return success;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @Saves the provided nvmData objects to NVM using two copy SHA-1.
///  Returns true if successful, false otherwise.
///  nvmData objects must either be POD or implement boost::serialize.  They may also not be a literal.
/////////////////////////////////////////////////////////////////////////////////////////////////
template <typename First, typename... Rest>
static bool store(const fs::path& path, const std::string& fileName, First&& first, Rest&&... rest) {
    bool success = false;

    if (!directory::create(path)) {
        return success;
    }

    std::string filePath = directory::makeFilePath(path, fileName);

    tes_common_ais::sha1_ofstream ofs{true};  // Two copy
    ofs.open(filePath, std::ios_base::out | std::ios_base::binary);
    if (ofs) {
        // Write to the file
        try {
            boost::archive::binary_oarchive oa(ofs);
            oa & std::forward<First>(first);
            using expander = int[];
            (void)expander{0, (void(oa & std::forward<Rest>(rest)), 0)...};
            AIS_LOG_NOTICE("Successfully saved the data to %s", filePath.c_str());
            success = true;
        }
        catch (const boost::archive::archive_exception &e) {
            AIS_LOG_ERROR("Could not serialize the data to storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (const std::exception &e) {
            AIS_LOG_ERROR("Could not serialize data from storage.");
            AIS_LOG_ERROR(e.what());
        }
        catch (...) {
            AIS_LOG_ERROR("Could not serialize data from storage, unexpected error.");
        }
        ofs.close();
    }
    else {
        AIS_LOG_ERROR(" file could not be saved to storage.");
    }
    return success;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @Returns the number of nvm records stored in the provided path
///  Assumes that the path only contains nvm records and they are properly formed with 4 files each
/////////////////////////////////////////////////////////////////////////////////////////////////
inline uint32_t count(const fs::path &path) {
    uint32_t count = 0;
    try {
        if (fs::exists(path) && fs::is_directory(path)) {  // Check if the directory already exists
            for (fs::directory_iterator it{path}; it != fs::directory_iterator{}; ++it) {
                count++;
            }
        }
    }
    catch (const fs::filesystem_error &e) {
        AIS_LOG_ERROR(e.what());
    }

    return count / 4;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
/// @Deletes the oldest nvm records stored in the provided path
///  Assumes that the path only contains nvm records and they are properly formed with 4 files each
/////////////////////////////////////////////////////////////////////////////////////////////////
inline bool deleteOldest(const fs::path &path) {
    bool success  = false;
    try {
        if (fs::exists(path) && fs::is_directory(path)) {  // Check if the directory already exists
            // Sort files by date
            fs::directory_iterator dir_first{path}, dir_last;
            std::vector<fs::path> files;

            auto pred = [](const fs::directory_entry& p) {
                return fs::is_regular_file(p);
            };

            std::copy(boost::make_filter_iterator(pred, dir_first, dir_last),
                      boost::make_filter_iterator(pred, dir_last, dir_last),
                      std::back_inserter(files));

            std::sort(files.begin(), files.end(),
                      [](const fs::path &p1, const fs::path &p2) {
                          return fs::last_write_time(p1) < fs::last_write_time(p2);
                      });

            // Order the 4 oldest files by name
            if (files.size() >= 4) {
                std::sort(files.begin(), std::next(files.begin(), 4),
                        [](const fs::path &p1, const fs::path &p2) {
                            return p1.string().compare(p2.string()) < 0;
                        });

                // Check that the oldest 4 files are from the same record
                std::vector<std::string> nvmSuffixes{"", ".bak", ".bak.sha1", ".sha1"};
                bool suffixCheck = true;
                auto binName = files[0].string();
                for (size_t i = 1; i < 4; i++)  {
                    if (files[i].string().compare(binName + nvmSuffixes[i]) != 0) {
                        suffixCheck = false;
                        break;
                    }
                    
                }
                // If the check passes, delete all 4 files
                if (suffixCheck) {
                    sha1_fstream::remove_files(binName);
                }
            }
        }
    }
    catch (const fs::filesystem_error &e) {
        AIS_LOG_ERROR(e.what());
    }

    return success;
}

} // namespace nvm
}; // namespace tes_common_ais

#endif // FILEIO_NVM_HPP
