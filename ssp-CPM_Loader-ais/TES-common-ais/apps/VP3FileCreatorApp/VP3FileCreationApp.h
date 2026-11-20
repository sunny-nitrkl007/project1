#ifndef VP3FILECREATIONAPP_H
#define VP3FILECREATIONAPP_H

#include <string>
#include <stdlib.h>
#include <stdio.h>

#include <boost/filesystem.hpp>
#include <boost/serialization/version.hpp>

#include <ais/task/Task.h>

#include <interfaces/VP3Record/InterfaceTypes.h>
#include <interfaces/CreateFileRequest/InterfaceTypes.h>
#include <interfaces/AppReg/InterfaceTypes.h>
#include <interfaces/FileTransferBridgeRequest/InterfaceTypes.h>
#include <interfaces/ShmClock/InterfaceTypes.h>
#include <interfaces/PartNumbers/InterfaceTypes.h>

#include "VP3RecordTypeContainer.h"
#include "VP3LastDownloadTimestampStorage.h"


class VP3FileCreationApp: public task::Task
{
public:
    VP3FileCreationApp( const std::string& taskName );
    virtual ~VP3FileCreationApp( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );

protected:
    inline std::string makeTempPath(const std::string& fileName) const {
        return (tempRoot_ / fileName).string();
    }

    inline std::string makeStoragePath(const std::string& fileName) const {
        return (storageRoot_ / fileName).string();
    }

private:
    boost::filesystem::path tempRoot_;
    boost::filesystem::path storageRoot_;
    VP3RecordInput* VP3_Rec_input_;
    CreateFileRequestInput* createFileRequestInput_;
    
    std::list<VP3RecordTypeContainer> myRecordTypeContainers;
    VP3Record latestStatusRecord;

    uint_least32_t totalReceivedRecordSize_;
    uint_least32_t totalReceivedRecordCount_;

    uint_least32_t recordDataSizeTxTrigger_;
    uint_least32_t recordCountTxTrigger_;

    bool resetLastDownloadTimestamp_;

    long int maxVP3StorageSize_;
    uint16_t maxVP3StorageFiles_;

    bool requireStatusRecord_;

    boost::filesystem::path vp3TempPath_;
    boost::filesystem::path vp3StoragePath_;
    boost::filesystem::path vp3TxPath_;

    bool AppRegistered;
    
    AppReg AppRegList;
    AppRegInput *AppRegInput_;
    AppRegOutput *AppRegOutput_;
    FileTransferBridgeRequestOutput *FileTransferBridgeRequestOutput_;
    const std::string vp3FilesDestinationApp;
    LastDownloadTimestampStorage LastDownloadTimestamp_;
    ShmClockInput * ShmClockInput_;
    PartNumbersInput * PartNumbersInput_;
    
    std::string productId_;
    std::string ecmPartNum_;
    std::string swGroupPartNum_;
    std::string modelNum_;
    uint32_t shmSeconds_;
    struct {
        int32_t offset;
        int32_t index;
    } tzInfo_;

    void saveVp3Record(const VP3Record& record, bool pushNewRecordTypeToFront = false);
    void createFile(const std::string& requestor);
    void processIncomingRecords();
    void UpdateRegistrations(void);
    void Add_VP3_header_block();
    void getACDscsObject();
    bool ReadPartNumsFromNVM();
    bool WritePartNumsToNVM();

    bool makeSpaceForNewVp3File(long int newVp3FileSize);
    
    static inline void uint_to_byteArr(unsigned short num, char *arr)
    {
        arr[1] = (char)(num & 0xFF);
        num = num >> 8;
        arr[0] = (char)(num & 0xFF);
    }
};

#endif
