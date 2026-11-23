#ifndef VP3FILECREATIONAPP_H
#define VP3FILECREATIONAPP_H

#include <string>
#include <stdlib.h>
#include <stdio.h>

#include <boost/filesystem.hpp>
#include <boost/serialization/version.hpp>

#include <deque>
#include <list>
#include <unordered_set>
#include <functional>
#include <ros2wrapper/Ros2TaskWrapper.h>
#include <cpm_common_interfaces/msg/vp3_record.hpp>
#include <cpm_common_interfaces/msg/create_file_request.hpp>
#include <cpm_common_interfaces/msg/app_reg.hpp>
#include <cpm_common_interfaces/msg/file_transfer_bridge_request.hpp>
#include <cpm_common_interfaces/msg/shm_clock_input.hpp>
#include <weigh_app_interfaces/msg/part_numbers.hpp>

using AppReg = cpm_common_interfaces::msg::AppReg;
using CreateFileRequest = cpm_common_interfaces::msg::CreateFileRequest;
using FileTransferBridgeRequest = cpm_common_interfaces::msg::FileTransferBridgeRequest;
using ShmClock = cpm_common_interfaces::msg::ShmClockInput;
using PartNumbers = weigh_app_interfaces::msg::PartNumbers;

#include "VP3RecordTypeContainer.h"
#include "VP3LastDownloadTimestampStorage.h"


class VP3FileCreationApp: public ros2_wrapper::Ros2TaskWrapper
{
public:
    VP3FileCreationApp( const std::string& taskName );
    virtual ~VP3FileCreationApp( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );
    void startExecutiveTimer() override;
    void setReceivePump(std::function<void()> pump) { receivePump_ = std::move(pump); }

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
    std::deque<VP3Record> recordQueue_;
    std::deque<CreateFileRequest> requestQueue_;
    std::deque<AppReg> registrationQueue_;
    std::deque<PartNumbers> partQueue_;
    std::deque<ShmClock> clockQueue_;
    std::vector<rclcpp::SubscriptionBase::SharedPtr> subscriptions_;
    std::function<void()> receivePump_;
    bool initialized_ = false;
    bool cleaned_ = false;
    double cycleRateHz_ = 1.0;
    std::uint32_t keyoffTimeoutMs_ = 0;
    
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
    
    std::unordered_set<std::string> activeProducers_;
    rclcpp::Publisher<AppReg>::SharedPtr AppRegOutput_;
    rclcpp::Publisher<FileTransferBridgeRequest>::SharedPtr FileTransferBridgeRequestOutput_;
    vp3::archive::Record statusArchive_;
    const std::string vp3FilesDestinationApp;
    LastDownloadTimestampStorage LastDownloadTimestamp_;
    void pumpFor(std::chrono::milliseconds duration);
    void publishRegistration(std::uint8_t state);

    template <class Message, class Value, class Convert>
    void subscribeQueue(const std::string& topic, std::size_t depth,
                        std::deque<Value>& queue, Convert convert)
    {
        subscriptions_.push_back(create_subscription<Message>(topic,
            rclcpp::QoS(rclcpp::KeepLast(depth)).reliable().durability_volatile(),
            [this, &queue, depth, convert, topic](const typename Message::SharedPtr message) {
                if (queue.size() == depth) {
                    queue.pop_front();
                    RCLCPP_WARN(get_logger(), "Oldest intake dropped on %s", topic.c_str());
                }
                queue.push_back(convert(*message));
            }));
    }
    
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
