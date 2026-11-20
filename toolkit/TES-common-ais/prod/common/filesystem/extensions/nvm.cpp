#include "ROS2Logger.hpp"
#include "nvm.h"
#include "sha1_fstream.hpp"

namespace ros2_nvm {
namespace filesystem {
namespace file {

namespace fs = boost::filesystem;

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
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"file::count: %s for path=%s", e.what(), path.c_str());
    }

    return count / 4;
}

//cppcheck-suppress unusedFunction
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
        RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"file::deleteOldest: %s for path=%s", e.what(), path.c_str());
    }

    return success;
}

}
}
}
