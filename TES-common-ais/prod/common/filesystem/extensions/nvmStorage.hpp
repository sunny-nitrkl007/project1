///////////////////////////////////////////////////////////////////////////////
/// @file      nvmStorage.hpp
/// @author    Steve Machan <Machan_Steve@cat.com>
///
/// @brief     Wrapper class for a serializable object stored in NVM
///
/// @attention Copyright (C) 2021
/// @attention Caterpillar
/// @attention All rights reserved
///////////////////////////////////////////////////////////////////////////////

#ifndef NVMSTORAGE_H
#define NVMSTORAGE_H

#include <string>

#include <boost/serialization/access.hpp>
#include <boost/serialization/version.hpp>

#include <ais/config/TaskParser.h>
#include <ais/util/taskUtils.hpp>

#include "nvm.h"

namespace ros2_nvm {
namespace filesystem {

//////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Wrapper class for storing a serializable object in NVM
///        Object is stored as two-copy with sha1 (4 files total)
///        NOTE: Class T must provide a getFileName function and must be serializable using
///        boost::serialization
//////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
class NvmStorage : public T
{
public:
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Constructor
    ///
    /// @param[in] fileName fileName to store the serialized object
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    NvmStorage(const std::string& fileName) :
        m_fileName{fileName},
        m_saveNeeded{true}
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Default Constructor
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    NvmStorage() :
        m_saveNeeded{true}
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Virtual Destructor for abstract class
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ~NvmStorage()
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Set fileName
    ///
    /// @param[in] fileName fileName to store the serialized object
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    void setFileName(const std::string& fileName)
    {
        m_fileName = fileName;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Get fileName
    ///
    /// @return m_fileName
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    std::string getFileName() const
    {
        return m_fileName;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief operator= for assigning base class T to NvmStorage
    ///
    /// @param[in] base object of base type T
    /// @return NvmStorage<T>
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    NvmStorage<T>& operator=(const T& base)
    {
        T::operator=(base);
        return *this;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Configure based on TaskParser settings and load from NVM
    ///
    /// @param[in] taskParser TaskParser
    /// @param[in] folder folder in nvmPath to store the files, defaults to taskName
    /// @return true if NVM data was successfully read, false otherwise. Can be used to set default value.
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    bool initialize(const TaskParser& taskParser, const std::string& folder = "")
    {
        if (m_fileName.empty())
        {
            RCLCPP_ERROR(ROS2Logger::Instance().GetLogger(),"fileName must be set before initialization");
            return false;
        }

        // Replace spaces with underscores
        std::replace(m_fileName.begin(), m_fileName.end(), ' ', '_');

        ConfigSection taskConfig;
        std::string nvmPath;
        if (!taskParser.getTaskParameters(taskConfig) || (!taskConfig.get("nvmPath", nvmPath) && !taskConfig.get("storageRoot", nvmPath)))
        {
            nvmPath = getOutputFileDirectory();
            nvmPath += "nvm";
            RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"nvmPath not found, using default=%s", nvmPath.c_str());
        }
        else
        {
            RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"nvmPath=%s", nvmPath.c_str());
        }
        m_dirPath = nvmPath;
        m_dirPath /= folder.empty() ? taskParser.getTaskName() : folder;

        if (!isStored())
        {
            RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"NVM file from %s not found, defaults will be used", getFilePath().c_str());
            return false;
        }
        else if (!load())
        {
            RCLCPP_WARN(ROS2Logger::Instance().GetLogger(),"Failed to read NVM data from %s, defaults will be used", getFilePath().c_str());
            return false;
        }
        else
        {
            RCLCPP_INFO(ROS2Logger::Instance().GetLogger(),"NVM data successfully read from %s", getFilePath().c_str());
        }
        return true;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Get the full file path of the stored object
    ///
    /// @return std::string file path of the stored object
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    boost::filesystem::path getFilePath()
    {
        return m_dirPath / m_fileName;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Check if the stored object exists om NVM
    ///
    /// @return bool true if it exists, false otherwise
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    bool isStored()
    {
        auto stored = boost::filesystem::is_regular_file(getFilePath());
        m_saveNeeded |= !stored;
        return stored;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Load the stored object from NVM
    ///
    /// @return bool true if successfully loaded, false otherwise
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    bool load()
    { 
        bool result = ros2_nvm::filesystem::file::read(m_dirPath, m_fileName, *this);
        m_saveNeeded = !result;
        return result;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Delete the stored object in NVM
    ///
    /// @return bool true if successfully deleted, false otherwise
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    bool remove()
    {
        bool result = ros2_nvm::filesystem::sha1_fstream::remove_files(ros2_nvm::filesystem::nvm_dir::makeFilePath(m_dirPath, m_fileName));
        m_saveNeeded = true;
        return result;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Save the object in NVM if a save is needed. Can be called during cleanup.
    ///
    /// @param[in] force Set to true to force the NVM save regardless if it has changed
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    bool save(bool force = true) const
    {
        if (force || m_saveNeeded)
        {
            return ros2_nvm::filesystem::file::store(m_dirPath, m_fileName, *this);
        }
        return true;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Set the saveNeeded flag
    ///
    /// @param[in] saveNeeded Value to set the saveNeeded flag
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    void saveNeeded(bool saveNeeded)
    {
        m_saveNeeded = m_saveNeeded;
    }

private:
    std::string m_fileName;
    boost::filesystem::path m_dirPath;
    mutable bool m_saveNeeded;
};

}
}
#endif
