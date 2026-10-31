#ifndef CALIBRATIONUICLIENTINF_HPP
#define CALIBRATIONUICLIENTINF_HPP

#include <chrono>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include <boost/signals2.hpp>

#include <ais/task/InterfaceDb.h>
#include <ais/log/AisLogger.h>

#include "../CalibrationRequestUI/InterfaceTypes.h"
#include "../CalibrationResponseUI/InterfaceTypes.h"

class CalibrationUIClientInf {
public:
    static constexpr std::chrono::milliseconds timeoutDurationDefault() { return std::chrono::milliseconds(300); }

    CalibrationUIClientInf() :
        mtx_(),
        pendingResponse_(true),
        nextHandshakeNumber_(0),
        lastHandshakeNumber_(0),
        responseDataCv_(),
        responseData_(),
        requestOutput_(nullptr),
        responseInput_(nullptr),
        responseInputConnection_() {
    }

    virtual ~CalibrationUIClientInf() {
        stop();
    }

    bool start(const std::string& requestOutputName,
            const std::string& responseInputName) {
        bool everythingOk = true;

        CalibrationRequestUIOutput* requestOutput = nullptr;
        if (!task::InterfaceDb::bind(requestOutputName, requestOutput)) {
            AIS_LOG_ERROR("%s Interface not configured.", requestOutputName.c_str());
            everythingOk = false;
        }

        CalibrationResponseUIInput* responseInput = nullptr;
        if (!task::InterfaceDb::bind(responseInputName, responseInput)) {
            AIS_LOG_ERROR("%s Interface not configured.", responseInputName.c_str());
            everythingOk = false;
        }

        if (everythingOk) {
            if (!start(requestOutput, responseInput)) {
                AIS_LOG_ERROR("Failed to start calibration UI interface.");
                everythingOk = false;
            }
        }

        return everythingOk;
    }

    /*
     * Start the interface service.
     */
    bool start(CalibrationRequestUIOutput* requestOutput,
            CalibrationResponseUIInput* responseInput) {

        stop();

        // Reinitialize these if this is a "restart"
        pendingResponse_ = true;
        lastHandshakeNumber_ = 0;

        requestOutput_ = requestOutput;
        responseInput_ = responseInput;

        // Attach a listener to the responseInput channel
        if (nullptr != responseInput_) {
            responseInputConnection_ = responseInput_->addNewDataSlot([this]{
                notifyResponseInput();
            });
        }

        // Everything is successful if we connected our listeners and have a requestOutput
        return (nullptr != requestOutput) && (responseInputConnection_.connected());
    }

    /*
     * Stop the interface service.
     */
    bool stop() {
        // Disconnect the responseInput listener if connected.
        if (nullptr != responseInput_) {
            if (responseInputConnection_.connected()) {
                responseInput_->removeNewDataSlot(responseInputConnection_);
            }
        }

        return true;
    }

    /*
     * Send a request.
     */
    bool sendRequest(CalibrationRequestUI& request) {
        bool success = false;
        std::unique_lock<std::mutex> lck(mtx_);
        if (0xF000 == request.CalibParam.InputAction) /* CAL_ACT_INIT */ {
            // Reset next handshake number when initializing a calibration
            request.CalibParam.HandshakeNumber = 0;
            nextHandshakeNumber_ = 1;
        }
        else if ((0x0000 == request.CalibParam.InputAction) /* CAL_ACT_IDLE */ &&
                (0x80 == request.CalibParam.ControlBits)) /* CAL_CMD_CTRL_ENABLED */ {
            if (0 != nextHandshakeNumber_) {
                // Reuse handshake number to allow IDLE message filtering
                // on the receiving side of this request.
                request.CalibParam.HandshakeNumber = nextHandshakeNumber_ - 1;
            }
            else {
                // Don't reuse handshake number 0 due to common services bug
                request.CalibParam.HandshakeNumber = 0;
                nextHandshakeNumber_ = 1;
            }
        }
        else {
            request.CalibParam.HandshakeNumber = nextHandshakeNumber_;
            ++nextHandshakeNumber_;
        }
        lck.unlock();

        if (nullptr != requestOutput_) {
            if (requestOutput_->publish(request)) {
                lck.lock();
                pendingResponse_ = true;
                lastHandshakeNumber_ = request.CalibParam.HandshakeNumber;
                lck.unlock();
                success = true;
            }
        }

        return success;
    }

    /*
     * Wait for a response to the most recent request.
     */
    bool waitForResponse(const std::chrono::milliseconds& timeoutDuration = timeoutDurationDefault()) {
        bool success = false;
        std::unique_lock<std::mutex> lck(mtx_);
        if (pendingResponse_) {
            // We are awaiting a response, use a condition variable to wait for the new
            // data or a timeout.
            if (std::cv_status::no_timeout == responseDataCv_.wait_for(lck, timeoutDuration)) {
                success = true;
            }
        }
        else {
            success = true;
        }

        return success;
    }

    /*
     * Get the last received response.
     */
    void getLastResponse(CalibrationResponseUI& response) {
        std::lock_guard<std::mutex> lck(mtx_);
        response = responseData_;
    }

protected:

    void notifyResponseInput() {
        if (nullptr != responseInput_) {
            CalibrationResponseUI response;
            while (responseInput_->get(response)) {
                std::unique_lock<std::mutex> lck(mtx_);
                responseData_ = response;
                if ((pendingResponse_) && (response.HandshakeNumber == lastHandshakeNumber_)) {
                    pendingResponse_ = false;
                    lck.unlock();
                    responseDataCv_.notify_all();
                }
            }
        }
    }

private:
    std::mutex mtx_;
    bool pendingResponse_;
    uint8_t nextHandshakeNumber_;
    uint8_t lastHandshakeNumber_;
    std::condition_variable responseDataCv_;
    CalibrationResponseUI responseData_;

    CalibrationRequestUIOutput* requestOutput_;
    CalibrationResponseUIInput* responseInput_;

    boost::signals2::connection responseInputConnection_;
};

#endif
