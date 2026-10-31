#include <hub/filesystem/extensions/nvm.h>
#include "CoachingTask.h"

namespace nvm = ais::filesystem::file;

///////////////////////////////////////////////////////////////////////////////
/// @Loads Initializes the coaching record objects
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::initCoachingRecords(void)
{
    // Clear all data
    coachingSummaryData = CoachingSummaryData();
    coaching3x3DataList.clear();
    breadcrumbLog.clear();

    // Reset application specific data
    coachingAppSpecific->reset();

    // Set video path and operator ID
    setMetadata();

    // Set max records for breadcrumbs
    breadcrumbLog.setMaxRecords(BreadcrumbRequestedRecords);
}

///////////////////////////////////////////////////////////////////////////////
/// @Loads the coaching records from NVM for the activeOperatorId.  Returns true if successful, false
/// otherwise
///////////////////////////////////////////////////////////////////////////////
bool CoachingTask::loadCoachingRecords(void)
{
    bool success = false;

    // If coaching records cannot be loaded, initialize them
    if (!nvm::read(coachingDataPath, activeOperatorId + NvmFileExtension, coachingSummaryData, coaching3x3DataList, breadcrumbLog))
    {
        AIS_LOG_WARN("Failed to load coaching records for operator: %s", activeOperatorId.c_str());
        initCoachingRecords();
    }
    else
    {
        AIS_LOG_NOTICE("Loaded coaching records for operator: %s", activeOperatorId.c_str());

        // Reset data if loaded differs from the app specific
        if (!coachingAppSpecific->isLoadedDataValid())
        {
            AIS_LOG_ERROR("Loaded coaching records are invalid");
            initCoachingRecords();
        }
        else
        {
            success = true;
        }
        
    }

    if(coaching3x3DataList.empty())     // fix old NVM if there is no 3x3 data
    {
        AIS_LOG_FATAL("no 3x3 found... initCoachingRecords():%d", coaching3x3DataList.empty());
        initCoachingRecords();
    }

    if(BreadcrumbGpsTimeSeconds != breadcrumbLog.maxTimeSeconds)
    {
        breadcrumbLog.maxTimeSeconds = BreadcrumbGpsTimeSeconds;   // adjust based on .rb
        AIS_LOG_ERROR("breadcrumbLog.maxTimeSeconds... setting to %d", BreadcrumbGpsTimeSeconds);
    }

    if(BreadcrumbGpsDistanceMeters != breadcrumbLog.maxDistanceMeters)
    {
        breadcrumbLog.maxDistanceMeters = BreadcrumbGpsDistanceMeters;   // adjust based on .rb
        AIS_LOG_ERROR("breadcrumbLog.maxDistanceMeters... setting to %d", BreadcrumbGpsDistanceMeters);
    }

    if(BreadcrumbRequestedRecords != breadcrumbLog.getMaxRecords())
    {
        breadcrumbLog.setMaxRecords(BreadcrumbRequestedRecords);	// default of 100 isn't enough records
        AIS_LOG_ERROR("breadcrumbLog.setMaxRecords... setting to %d", BreadcrumbRequestedRecords);
    }

    // set these to chmod 755 so FTP of NVM has access (No Longer needed with AIS 4.4)
    // boost::filesystem::permissions("/opt/appdata/CPM", boost::filesystem::perms::owner_all|boost::filesystem::perms::group_read|boost::filesystem::perms::group_exe|boost::filesystem::perms::others_read|boost::filesystem::perms::others_exe);
    // boost::filesystem::permissions("/opt/appdata/CPM/CoachingTask", boost::filesystem::perms::owner_all|boost::filesystem::perms::group_read|boost::filesystem::perms::group_exe|boost::filesystem::perms::others_read|boost::filesystem::perms::others_exe);

    return success;
}

///////////////////////////////////////////////////////////////////////////////
/// @Saves the coaching records in NVM.  Returns true if successful, false
/// otherwise
///////////////////////////////////////////////////////////////////////////////
bool CoachingTask::saveCoachingRecords(void)
{
    return nvm::store(coachingDataPath, activeOperatorId + NvmFileExtension, coachingSummaryData, coaching3x3DataList, breadcrumbLog);
}

///////////////////////////////////////////////////////////////////////////////
/// @Deletes oldest record if max is exceeded
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::manageOperatorIdList(void)
{
    // Add to the end of the operatorId list and delete oldest record if max is exceeded
    auto it = std::find(operatorList.begin(), operatorList.end(), activeOperatorId);
    if (it == operatorList.end())
    {
        if (operatorList.size() >= maxSavedOperators)
        {
            std::string fileToRemove = coachingDataPath.string() + "/" + *(operatorList.begin()) + NvmFileExtension;
            if(!ais::filesystem::sha1_fstream::remove_files(fileToRemove))
            {
                AIS_LOG_ERROR("Failed to remove file %s", fileToRemove.c_str());
            }
            operatorList.erase(operatorList.begin());
        }
    }
    else
    {
        // Remove operator from current place in list
        operatorList.erase(it);
    }
    operatorList.push_back(activeOperatorId);
}

///////////////////////////////////////////////////////////////////////////////
/// @Loads the Operator ID list and Tip History from NVM.  Returns true if successful, false
/// otherwise
///////////////////////////////////////////////////////////////////////////////
bool CoachingTask::loadOperatorIdList(void)
{
    // In a brand new ECM, there wil be no operatorIdlist
    if (!nvm::read(coachingDataPath, OperatorIdListFileName, operatorList)) return false;
    if (!nvm::read(coachingDataPath, CoachingTipHistoryFileName, coachingTipHistory)) return false;
    return true;
}

///////////////////////////////////////////////////////////////////////////////
/// @Saves the Operator ID list and Tip History in NVM.  Returns true if successful, false
/// otherwise
///////////////////////////////////////////////////////////////////////////////
bool CoachingTask::saveOperatorIdList(void)
{
    if (!nvm::store(coachingDataPath, OperatorIdListFileName, operatorList)) return false;
    if (!nvm::store(coachingDataPath, CoachingTipHistoryFileName, coachingTipHistory)) return false;
    return true;
}
