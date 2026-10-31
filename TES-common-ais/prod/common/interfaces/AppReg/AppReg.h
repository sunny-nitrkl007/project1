////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Caterpillar Inc.  All Rights Reserved.
//
//     Class: AppRegStorage
//
//
// File Name: AppRegStorage.cpp
//
//  Abstract: Manages app to app registration.
//
////////////////////////////////////////////////////////
#include <unordered_set>
#include <ais/serialization/Datum.h> // For Boost serialization

#ifndef Task_h
#include <ais/task/Task.h>
#endif

#ifndef APPREG_H
#define APPREG_H

class AppRegStorage;

typedef Datum<AppRegStorage> AppReg;

//This interface could have been split into two. Req and Resp,
// however team agreed to keep in one for now.
class AppRegStorage : public csvable
{
public:
    typedef enum {
        APP_REG_STATE_ACTIVE,
        APP_REG_STATE_INACTIVE
    } AppRegStates_t;

    typedef enum {
        APP_REG_APP_NAME_NOT_SET,
        APP_REG_DEST_APP_NAME_DID_NOT_MATCH,
        APP_REG_APP_NAME_EMPTY,
        APP_REG_APP_NAME_REGISTERED,
        APP_REG_APP_NAME_ALREADY_REGISTERED,
        APP_REG_APP_NAME_UNREGISTERED,
        APP_REG_UNKNOWN,
    } AppRegRet_t;

    typedef enum {
        APP_REG_REQ,
        APP_REG_RESP
    } AppRegMsgType_t;

    AppRegStorage() : AppRegStorage("", 0) {}

    //This constructor should be used for application registration.
    /////////////////////////////////////////////////////////////////////
    // Function        : AppRegStorage
    // Description     : Constructor for the app that manages registrations.
    //
    // Return Type     : void
    //
    //////////////////////////////////////////////////////////////////////
    AppRegStorage(const std::string& appName, unsigned int keyOffTimeOutMSec = 0) :
        appName_(appName),
        appState_(APP_REG_STATE_INACTIVE),
        destAppName_(),
        shutdownInitTime_(),
        keyOffTimeOutMSec_(keyOffTimeOutMSec),
        timeDiffMSec_(0),
        shutdownInit_(false),
        regStatus_(APP_REG_UNKNOWN),
        msgType_(APP_REG_REQ) {}

    const std::string& GetAppName(void) const {
        return appName_;
    }

    const std::string& GetDestAppName(void) const {
        return destAppName_;
    }

    AppRegStates_t GetAppState(void) const {
        return appState_;
    }

    /////////////////////////////////////////////////////////////////////
    // Function        : SetAppRegAttr
    // Description     : Set or reset AppRegStorage members with values.
    //
    // Return Type     : void
    //
    //////////////////////////////////////////////////////////////////////
    void SetAppRegAttr(const std::string& appName,
                       AppRegStates_t appState = APP_REG_STATE_INACTIVE,
                       const std::string& destAppName = "") {
        msgType_ = APP_REG_REQ;
        appName_ = appName;
        appState_ = appState;
        destAppName_ = destAppName;
    }

    /////////////////////////////////////////////////////////////////////
    // Function        : UpdateAppRegState
    // Description     : Register app name. This method called by the app
    //                   that manages registrations.
    //
    // Return Type     : AppReg - returns the
    //                   stream for the item.
    //
    //////////////////////////////////////////////////////////////////////
    void UpdateAppRegState(AppReg *regInfo) {
        if (nullptr == regInfo) {
            return;
        }

        // Validate Attributes
        // App name should have been set when creating class instance.
        if (appName_.empty()) {
            regInfo->regStatus_ = APP_REG_APP_NAME_NOT_SET;
            return;
        }

        if (regInfo->appName_.empty()) {
            regInfo->regStatus_ = APP_REG_APP_NAME_EMPTY;
            return;
        }

        if (0 != appName_.compare(regInfo->destAppName_)) {
            regInfo->regStatus_ = APP_REG_DEST_APP_NAME_DID_NOT_MATCH;
            return;
        }

        // Add app name to active list
        if (regInfo->appState_ == APP_REG_STATE_ACTIVE) {
            if (IsAppRegistered(regInfo->appName_)) {
                regInfo->regStatus_ = APP_REG_APP_NAME_ALREADY_REGISTERED;
            }
            else {
                activeAppNames_.insert(regInfo->appName_);
                regInfo->regStatus_ = APP_REG_APP_NAME_REGISTERED;
            }
        }
        else {
            // Remove app name from active list.
            activeAppNames_.erase(regInfo->appName_);
            regInfo->regStatus_ = APP_REG_APP_NAME_UNREGISTERED;
        }

        regInfo->BuildResponse();

        return;
    }

    //////////////////////////////////////////////////////////////////////////////
    // Function        : BuildResponse
    // Description     : Builds response to the registration request. This
    //                   function / method used by app that manages registrations.
    //
    // Return Type     : void
    //
    //////////////////////////////////////////////////////////////////////////////
    void BuildResponse(void) {
        destAppName_.swap(appName_);
        msgType_ = APP_REG_RESP;
    }

    /////////////////////////////////////////////////////////////////////
    // Function        : IsMsgAddressedToMe
    // Description     : Checks whether response is address to the appName
    //                   specified in the parameter.
    //
    // Return Type     : bool - true if appName matches otherwise false.
    //
    //////////////////////////////////////////////////////////////////////
    bool IsMsgAddressedToMe(const std::string& appName) const {
        return (0 == destAppName_.compare(appName));
    }

    unsigned int GetAppRegCount(void) {
        return activeAppNames_.size();
    }

    bool IsAppRegListEmpty(void) const {
        return activeAppNames_.empty();
    }

    const std::unordered_set<std::string>& GetActiveAppNames() const {
        return activeAppNames_;
    }

    bool IsAppRegistered(const std::string& appName) const {
        return activeAppNames_.count(appName) > 0;
    }

    ///////////////////////////////////////////////////////////////////
    // Function        : IsKeyOffTimeOut
    // Description     : Return whether met key off time out or not.
    //
    // Return Type     : bool - true if timed out, otherwise false
    //
    ///////////////////////////////////////////////////////////////////
    bool IsKeyOffTimeOut(void) {
        TimeStamp now = localhostNow();

        if (!shutdownInit_) {
            shutdownInitTime_ = now;
            shutdownInit_ = true;
        }

        timeDiffMSec_ = (unsigned int)((now - shutdownInitTime_).toDouble() * 1000);
        if (timeDiffMSec_ >= keyOffTimeOutMSec_) {
            return true;
        }
        else {
            usleep(20000); //enforcing minimum sleep time of 20 milliseconds.
            return false;
        }
    }

    unsigned int GetTimeDiffMSec(void) const {
        return timeDiffMSec_;
    }

    unsigned int GetKeyOffTimeOutMSec(void) const {
        return keyOffTimeOutMSec_;
    }

    void SetKeyOffTimeOutMSec(unsigned int keyOffTimeOutMSec) {
        keyOffTimeOutMSec_ = keyOffTimeOutMSec;
    }

    bool GetShutdownStatus(void) const {
        return shutdownInit_;
    }

    void ResetShutdownStatus(void) {
        shutdownInit_ = false;
    }

    AppRegMsgType_t GetMsgType(void) const {
        return msgType_;
    }

    void SetMsgType(AppRegMsgType_t msgType) {
        msgType_ = msgType;
    }

    AppRegRet_t GetRegStatus(void) const {
        return regStatus_;
    }

    template <class Archive>
    void serialize(Archive &ar, unsigned int version) {
        /* Archive Fields Here */
        ar & msgType_;
        ar & appName_;
        ar & appState_;
        ar & destAppName_;
        ar & regStatus_;
    }

    void toCsv(CsvOutStream& out) const {
        out("AppRegAttr.AppName", appName_);
        out("AppRegAttr.AppState", appState_);
        out("AppRegAttr.DestAppName", destAppName_);
    }

private:
    /* Add Fields Here */
    std::string appName_;
    AppRegStates_t appState_;
    std::string destAppName_;
    std::unordered_set<std::string> activeAppNames_;
    TimeStamp shutdownInitTime_;
    unsigned int keyOffTimeOutMSec_;
    unsigned int timeDiffMSec_;
    bool shutdownInit_;
    AppRegRet_t regStatus_;
    AppRegMsgType_t msgType_;
};


BOOST_CLASS_VERSION(AppRegStorage, 1);

#endif //APPREG_H

