#ifndef FILETRANSFERBRIDGEAPP_CDAIOTHUBCOMMS_H
#define FILETRANSFERBRIDGEAPP_CDAIOTHUBCOMMS_H

#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <deque>
#include <unordered_set>
#include <functional>
#include <system_error>

#include <ais/log/AisLogger.h>

#include <interfaces/IoTHubCommsInboundMessage/InterfaceTypes.h>
#include <interfaces/IoTHubCommsOutboundMessage/InterfaceTypes.h>
#include <interfaces/IoTHubCommsOutboundReturn/InterfaceTypes.h>

#include <platform_comms.pb.h>
#include <CDAIOTHubComms.pb.h>
#include <CDAIOTHubComms.grpc.pb.h>

class CdaIoTHubComms {
public:
    typedef IoTHubCommsOutboundMessageStorage OutboundMessageData;
    typedef IoTHubCommsOutboundReturnStorage OutboundReturnData;

    CdaIoTHubComms() :
        stopThreads_(true),
        rpcStub_(),
        outboundMessageThread_(),
        outboundMessageRpcCanceller_(),
        outboundMessageQueueMaxSize_(20),
        outboundMessages_(),
        inboundMessageThread_(),
        inboundMessageRpcCanceller_(),
        inboundFileTypes_(),
        pInboundMessageOutput_(nullptr),
        pOutboundMessageInput_(nullptr),
        pOutboundReturnOutput_(nullptr) {}

    ~CdaIoTHubComms() {
        // Stop without blocking
        stop();

        try {
            // Let the thread die on its own
            outboundMessageThread_.detach();
        }
        catch (const std::system_error& e) {
            // No harm here
        }

        try {
            // Let the thread die on its own
            inboundMessageThread_.detach();
        }
        catch (const std::system_error& e) {
            // No harm here
        }
    }

    void installScsChannels(
            IoTHubCommsInboundMessageOutput* pInboundMessageOutput,
            IoTHubCommsOutboundMessageInput* pOutboundMessageInput,
            IoTHubCommsOutboundReturnOutput* pOutboundReturnOutput) {

        // Store the input channel for getting stuff.
        pOutboundMessageInput_ = pOutboundMessageInput;

        // Add listener to the incoming message requests.
        if (nullptr != pOutboundMessageInput_) {
            pOutboundMessageInput->addNewDataSlot([this] {
                if (nullptr != pOutboundMessageInput_) {
                    IoTHubCommsOutboundMessage scsMsg;
                    while (pOutboundMessageInput_->get(scsMsg)) {
                        // Queue new message.
                        queueOutboundMessage(std::move(scsMsg));
                    }
                }
            });
        }


        // Store the output channels for publishing stuff.
        pInboundMessageOutput_ = pInboundMessageOutput;
        pOutboundReturnOutput_ = pOutboundReturnOutput;
    }

    void setOutboundMessageQueueMaxSize(uint16_t maxSize) {
        if (maxSize > 0) {
            outboundMessageQueueMaxSize_ = maxSize;
        }
    }

    template <class InputIterator>
    void setInboundFileTypes(InputIterator first, InputIterator last) {
        { // lock the set for modification
            std::unique_lock<std::mutex> lck(inboundFileTypes_.mtx);
            inboundFileTypes_.s = std::unordered_set<uint32_t>(first, last);
            logInboundFileTypes();
        }

        // Interrupt the current input stream so that it can rebuild.
        interruptInboundThread();
    }

    void addInboundFileType(uint32_t fileType) {
        bool changed = false;
        { // lock the set for modification
            std::unique_lock<std::mutex> lck(inboundFileTypes_.mtx);
            if (0 == inboundFileTypes_.s.count(fileType)) {
                inboundFileTypes_.s.insert(fileType);
                logInboundFileTypes();
                changed = true;
            }
        }

        // Interrupt the current input stream so that it can rebuild.
        if (changed) {
            interruptInboundThread();
        }
    }

    void removeInboundFileType(uint32_t fileType) {
        bool changed = false;
        { // lock the set for modification
            std::unique_lock<std::mutex> lck(inboundFileTypes_.mtx);
            if (0 != inboundFileTypes_.s.count(fileType)) {
                inboundFileTypes_.s.erase(fileType);
                logInboundFileTypes();
                changed = true;
            }
        }

        // Interrupt the current input stream so that it can rebuild.
        if (changed) {
            interruptInboundThread();
        }
    }

    void clearInboundFileTypes() {
        bool changed = false;
        { // lock the set for modification
            std::unique_lock<std::mutex> lck(inboundFileTypes_.mtx);
            if (!inboundFileTypes_.s.empty()) {
                inboundFileTypes_.s.clear();
                logInboundFileTypes();
                changed = true;
            }
        }

        // Interrupt the current input stream so that it can rebuild.
        if (changed) {
            interruptInboundThread();
        }
    }

    void queueOutboundMessage(OutboundMessageData&& msg) {
        OutboundReturnData returnData;

        AIS_LOG_NOTICE("IoTHubComms: Queueing outbound message (%d)", msg.fileType);

        { // All message queue modification is locked
            std::unique_lock<std::mutex> lck(outboundMessages_.mtx);

            // If it is a one-shot message, replace the oldest with this one.
            if (msg.oneShot) {
                for (auto it = outboundMessages_.q.cbegin(); it != outboundMessages_.q.cend(); ++it) {
                    if ((it->oneShot) && (it->fileType == msg.fileType)) {
                        // Drop this message to replace it with the most recent.
                        returnData.initFromOutboundMessage(*it);
                        returnData.returnState = OutboundReturnData::ReturnState::QUEUE_TIMEOUT;
                        outboundMessages_.q.erase(it);
                        AIS_LOG_NOTICE("IoTHubComms: Outbound message queue erasing previous one-shot message (%d)", returnData.fileType);
                        break;
                    }
                }
            }

            // If there are too many messages in the queue, drop the oldest.
            if (outboundMessages_.q.size() >= outboundMessageQueueMaxSize_) {
                // Drop the oldest message.
                const OutboundMessageData& oldMsg = outboundMessages_.q.front();
                returnData.initFromOutboundMessage(oldMsg);
                returnData.returnState = OutboundReturnData::ReturnState::QUEUE_TIMEOUT;
                outboundMessages_.q.pop_front();
                AIS_LOG_NOTICE("IoTHubComms: Outbound message queue is full, popped oldest (%d)", returnData.fileType);
            }

            // Now put the new message in the queue.
            outboundMessages_.q.push_back(std::move(msg));
            outboundMessages_.cv.notify_all();
        }

        // If we popped a message off to make room, let the application know about it.
        if (OutboundReturnData::ReturnState::STATE_INVALID != returnData.returnState) {
            IoTHubCommsOutboundReturn scsMsg;
            scsMsg.setData(std::move(returnData));
            if (nullptr != pOutboundReturnOutput_) {
                pOutboundReturnOutput_->publish(scsMsg);
            }
        }
    }

    bool start(const std::shared_ptr<grpc::ChannelInterface>& channel) {

        // Stop any previous stuff now, blocking.
        stop(true);

        if (nullptr == channel) {
            AIS_LOG_ERROR("IoTHubComms: null grpc channel given.");
            rpcStub_.reset();
            return false;
        }

        // Create new stub with channel provided.
        // The old stub will be deleted
        rpcStub_ = CDA::IOTHubComms::IOTHubComms::NewStub(channel);

        if (nullptr != rpcStub_) {
            // Allow the new threads to live.
            stopThreads_ = false;

            // Launch Threads
            outboundMessageThread_ = std::thread([this] {
                outboundThreadFunc();
            });

            inboundMessageThread_ = std::thread([this] {
                inboundThreadFunc();
            });

            AIS_LOG_NOTICE("IoTHubComms: started.");
            return true;
        }

        AIS_LOG_ERROR("IoTHubComms: failed to create to rpc stub.");
        return false;
    }

    void stop(bool block = false) {
        // Signal threads to stop
        stopThreads_ = true;
        interruptOutboundThread();
        interruptInboundThread();

        AIS_LOG_NOTICE("IoTHubComms: threads signaled to stop.");

        if (block) {
            try {
                // Wait for the thread to die.
                outboundMessageThread_.join();
            }
            catch (const std::system_error& e) {
                // Not joinable
            }

            try {
                // Wait for the thread to die.
                inboundMessageThread_.join();
            }
            catch (const std::system_error& e) {
                // Not joinable
            }

            AIS_LOG_NOTICE("IotHubComms: threads stopped.");
        }
    }

    void interruptOutboundThread() {
        { // Wake up the message queue
            std::unique_lock<std::mutex> lck(outboundMessages_.mtx);
            outboundMessages_.cv.notify_all();
        }

        { // Cancel potentially active rpc
            outboundMessageRpcCanceller_.call();
        }
    }

    void interruptInboundThread() {
        { // Cancel potentially active rpc
            inboundMessageRpcCanceller_.call();
        }
    }

    void outboundThreadFunc() {
        std::unique_lock<std::mutex> lck(outboundMessages_.mtx);

        while (!stopThreads_) {
            // Check for messages
            if (outboundMessages_.q.empty()) {
                // The queue will be unlocked, waiting for more.
                outboundMessages_.cv.wait(lck);
                // Now the queue is locked again.
            }
            else {
                bool error = false;

                // The queue is locked and not empty, grab the message
                const OutboundMessageData msg = std::move(outboundMessages_.q.front());
                outboundMessages_.q.pop_front();

                // Unlock the queue so that more messages can be queued up while we send this one
                lck.unlock();

                { // Transmit the message
                    grpc::ClientContext rpcContext;

                    // Set up the canceller to be able to cancel this request.
                    outboundMessageRpcCanceller_.set([&rpcContext] {
                        rpcContext.TryCancel();
                    });

                    // Build the outbound message
                    CDA::IOTHubComms::IOTHubMessageOutbound outMsg;
                    outMsg.set_platform(platform_comms::CAT_IOTHUB_GATEWAY);
                    outMsg.set_filetype(msg.fileType);
                    outMsg.set_messagecontents(msg.messageContents.data(), msg.messageContents.size());
                    if (!msg.correlationId.empty()) {
                        outMsg.set_correlationid(msg.correlationId);
                    }
                    outMsg.set_generatemessageidguid(msg.generateMessageId);

                    CDA::IOTHubComms::IOTHubMessageReturn rpcReturn;

                    // Set a deadline for the call.
                    rpcContext.set_deadline(std::chrono::system_clock::now() + std::chrono::minutes(1));

                    AIS_LOG_NOTICE("IoTHubComms: sending outbound message (%d).", msg.fileType);

                    // Make the RPC call
                    ::grpc::Status rpcStatus = rpcStub_->TransmitDirectSynchronous(&rpcContext, outMsg, &rpcReturn);

                    // If the RPC call was made
                    if (rpcStatus.ok()) {
                        CDA::IOTHubComms::IOTHubMessageReturn_TRANSFER_RETURN rState = rpcReturn.returnstate();
                        switch (rState) {
                        case (CDA::IOTHubComms::IOTHubMessageReturn_TRANSFER_RETURN_TRANSMIT_ACKNOWLEDGE_SUCCESS):
                        case (CDA::IOTHubComms::IOTHubMessageReturn_TRANSFER_RETURN_QUEUED_SUCCESS): {
                            // Worked!
                            // Give the result back to the calling application
                            AIS_LOG_NOTICE("IoTHubComms: outbound message sent (%d).", rState);
                            IoTHubCommsOutboundReturn scsMsg;
                            scsMsg.initFromOutboundMessage(msg);
                            scsMsg.returnState = static_cast<OutboundReturnData::ReturnState>(rState);
                            if (nullptr != pOutboundReturnOutput_) {
                                pOutboundReturnOutput_->publish(scsMsg);
                            }
                            break;
                        }
                        case (CDA::IOTHubComms::IOTHubMessageReturn_TRANSFER_RETURN_QUEUE_TIMEOUT):
                        case (CDA::IOTHubComms::IOTHubMessageReturn_TRANSFER_RETURN_CONNECTION_UNAVAILABLE):
                        case (CDA::IOTHubComms::IOTHubMessageReturn_TRANSFER_RETURN_HUB_NOT_INITIALIZED):
                        case (CDA::IOTHubComms::IOTHubMessageReturn_TRANSFER_RETURN_FATAL_ERROR): {
                            // May work if we try again.
                            AIS_LOG_ERROR("IoTHubComms: outbound message failure (%d), retrying.", rState);
                            error = true;
                            break;
                        }
                        case (CDA::IOTHubComms::IOTHubMessageReturn_TRANSFER_RETURN_STATE_INVALID):
                        case (CDA::IOTHubComms::IOTHubMessageReturn_TRANSFER_RETURN_HUB_SUBSCRIPTION_NOT_AUTHORIZED):
                        case (CDA::IOTHubComms::IOTHubMessageReturn_TRANSFER_RETURN_HUB_CONNECT_SECURITY_FAILURE):
                        case (CDA::IOTHubComms::IOTHubMessageReturn_TRANSFER_RETURN_FILE_TYPE_NOT_SUPPORTED):
                        case (CDA::IOTHubComms::IOTHubMessageReturn_TRANSFER_RETURN_FILE_SIZE_EXCEEDED):
                        default: {
                            // Will never work.
                            // Tell the calling application
                            AIS_LOG_ERROR("IoTHubComms: outbound message failure (%d).", rState);
                            IoTHubCommsOutboundReturn scsMsg;
                            scsMsg.initFromOutboundMessage(msg);
                            scsMsg.returnState = static_cast<OutboundReturnData::ReturnState>(rState);
                            if (nullptr != pOutboundReturnOutput_) {
                                pOutboundReturnOutput_->publish(scsMsg);
                            }
                            break;
                        }
                        }
                    }
                    else {
                        // RPC was cancelled, or otherwise not ok
                        AIS_LOG_ERROR("IoTHubComms: outbound TransmitDirectSynchronous not ok (%d) - %s", rpcStatus.error_code(), rpcStatus.error_message().c_str());
                        error = true;
                    }

                    // Clear the rpc canceller to turn in into a NOOP
                    outboundMessageRpcCanceller_.clr();
                }

                // If we had an error, then maybe we should throttle ourselves a little here
                // if we don't have a stop request.  Basically, do an interruptable sleep here?
                // TODO_NOW - Make this an interruptable sleep?
                if (error && !stopThreads_) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
//                    threadSleepFor(std::chrono::seconds(1));
                }

                // Lock the queue so that we can check it for more messages.
                lck.lock();

                if (error) {
                    if (stopThreads_) {
                        // We have been signaled to stop, but we can't drop the
                        // queued message... we have to re-queue it.
                        AIS_LOG_NOTICE("IoTHubComms: outbound thread signaled to stop, stash pending message.");
                    }

                    // Put it back into the queue at the front if we want to try again.
                    // But only if the queue still has room.  If it doesn't, we have to
                    // Drop the message and notify the app of it.
                    // If it is a "one-shot" message, drop it and notify the app of it.
                    if (msg.oneShot) {
                        // Unlock the queue so that we don't cause deadlock with SCS
                        lck.unlock();

                        { // Notify the app of the dropped message
                            AIS_LOG_ERROR("IoTHubComms: outbound message could not retry, one-shot");
                            IoTHubCommsOutboundReturn scsMsg;
                            scsMsg.initFromOutboundMessage(msg);
                            scsMsg.returnState = OutboundReturnData::ReturnState::QUEUE_TIMEOUT;
                            if (nullptr != pOutboundReturnOutput_) {
                                pOutboundReturnOutput_->publish(scsMsg);
                            }
                        }

                        // Re-Lock the queue
                        lck.lock();
                    }
                    else if (outboundMessages_.q.size() < outboundMessageQueueMaxSize_) {
                        outboundMessages_.q.push_front(std::move(msg));
                    }
                    else {
                        // Unlock the queue so that we don't cause deadlock with SCS
                        lck.unlock();

                        { // Notify the app of the dropped message
                            AIS_LOG_ERROR("IoTHubComms: outbound message could not retry, queue full");
                            IoTHubCommsOutboundReturn scsMsg;
                            scsMsg.initFromOutboundMessage(msg);
                            scsMsg.returnState = OutboundReturnData::ReturnState::QUEUE_TIMEOUT;
                            if (nullptr != pOutboundReturnOutput_) {
                                pOutboundReturnOutput_->publish(scsMsg);
                            }
                        }

                        // Re-Lock the queue
                        lck.lock();
                    }
                }
            }
        }

        AIS_LOG_NOTICE("IoTHubComms: outboundThreadFunc() done.");
    }

    void inboundThreadFunc() {
        while (!stopThreads_) {
            bool error = false;
            grpc::ClientContext rpcContext;

            // Set up the canceller to be able to cancel this stream.
            inboundMessageRpcCanceller_.set([&rpcContext] {
                rpcContext.TryCancel();
            });

            CDA::IOTHubComms::IOTHubInboundFilter outMsg;
            outMsg.set_platform(platform_comms::CAT_IOTHUB_GATEWAY);
            { // Set file types
                std::unique_lock<std::mutex> lck(inboundFileTypes_.mtx);
                for (const auto& fileType : inboundFileTypes_.s) {
                    outMsg.add_filetypeset(fileType);
                }
            }

            //std::unique_ptr<grpc::ClientReader<CDA::IOTHubComms::IOTHubMessageInbound>> reader =
            //        rpcStub_->GetInboundStream(&rpcContext, outMsg);
            auto reader = rpcStub_->GetInboundStream(&rpcContext, outMsg);

            if (reader) {
                AIS_LOG_NOTICE("IoTHubComms: inbound message stream reader created.");

                while (!stopThreads_) {
                    // Read messages one by one
                    CDA::IOTHubComms::IOTHubMessageInbound inMsg;
                    if (reader->Read(&inMsg)) {
                        // Got a new message... publish it.
                        AIS_LOG_NOTICE("IoTHubComms: received inbound message (%d)", inMsg.filetype());

                        IoTHubCommsInboundMessage scsMsg;
                        scsMsg.fileType = inMsg.filetype();
                        { // Get message contents
                            const std::string& contents = inMsg.messagecontents();
                            scsMsg.messageContents.assign(contents.cbegin(), contents.cend());
                        }
                        scsMsg.messageId = inMsg.messageid();
                        scsMsg.correlationId = inMsg.correlationid();

                        if (nullptr != pInboundMessageOutput_) {
                            pInboundMessageOutput_->publish(scsMsg);
                        }
                    }
                    else {
                        // There will be no more incoming messages, either because
                        // the other side has called WritesDone() or the stream has failed
                        // (or been cancelled).
                        AIS_LOG_WARN("IoTHubComms: inbound message stream reader is finished.");
                        (void)reader->Finish();
                        error = true;
                        break;
                    }
                }

                AIS_LOG_NOTICE("IoTHubComms: exited inbound message stream reader loop.");
            }
            else {
                AIS_LOG_ERROR("IoTHubComms: could not create inbound message stream reader.");
                error = true;
            }

            // Clear the rpc canceller to turn in into a NOOP
            inboundMessageRpcCanceller_.clr();

            // If an error has occurred, then we should wait a little before
            //  trying the whole thing again to throttle the infinite retry
            //  loop back a little bit.
            if (error && !stopThreads_) {
                // TODO_NOW - Make this an interruptable sleep?
                std::this_thread::sleep_for(std::chrono::seconds(1));
                //threadSleepFor(std::chrono::seconds(5));
            }
        }

        AIS_LOG_NOTICE("IoTHubComms: inboundThreadFunc() done.");
    }

private:
    class Canceller {
    public:
        Canceller() :
            mtx_(),
            func_(noop()) {}

        inline void set(std::function<void(void)>&& func) {
            std::unique_lock<std::mutex> lck(mtx_);
            func_ = std::move(func);
        }

        inline void clr() {
            std::unique_lock<std::mutex> lck(mtx_);
            func_ = noop();
        }

        inline void call() {
            std::unique_lock<std::mutex> lck(mtx_);
            func_();
        }

    private:
        static const std::function<void(void)>& noop() {
            static const std::function<void(void)> noop_ = [](){};
            return noop_;
        }

        std::mutex mtx_;
        std::function<void(void)> func_;
    };

//    void threadSleepFor(std::chrono::seconds duration) {
//        /*
//         * A cheap and easy interruptable sleep
//         *  This breaks the sleep into smaller chunks and
//         *  checks to see if it should be interrupted
//         *  after every bit of time.
//         */
//        static constexpr auto aBitOfTime = std::chrono::seconds(1);
//        while (!stopThreads_) {
//            if (duration > aBitOfTime) {
//                std::this_thread::sleep_for(aBitOfTime);
//                duration -= aBitOfTime;
//            }
//            else {
//                std::this_thread::sleep_for(duration);
//                break;
//            }
//        }
//    }

    bool stopThreads_;
    std::unique_ptr<CDA::IOTHubComms::IOTHubComms::Stub> rpcStub_;

    std::thread outboundMessageThread_;
    Canceller outboundMessageRpcCanceller_;

    uint16_t outboundMessageQueueMaxSize_;
    struct {
        std::mutex mtx;
        std::condition_variable cv;
        std::deque<OutboundMessageData> q;
    } outboundMessages_;

    std::thread inboundMessageThread_;
    Canceller inboundMessageRpcCanceller_;

    struct {
        std::mutex mtx;
        std::unordered_set<uint32_t> s;
    } inboundFileTypes_;

    // Log supported inbound file types.
    // Assumes the inbound file types set is locked.
    void logInboundFileTypes() {
        std::stringstream ss;
        ss << "IoTHubComms: Supported file types:";
        for (const auto& ft : inboundFileTypes_.s) {
            ss << " " << ft;
        }
        AIS_LOG_NOTICE(ss.str().c_str());
    }

    IoTHubCommsInboundMessageOutput* pInboundMessageOutput_;
    IoTHubCommsOutboundMessageInput* pOutboundMessageInput_;
    IoTHubCommsOutboundReturnOutput* pOutboundReturnOutput_;

};

#endif
