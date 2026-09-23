#include "OperatorIdTest.h"

#include <time.h>
#include <fileio/iflocker.hpp>
#include <fileio/oflocker.hpp>
#include <fileio/sha1_fstream.hpp>

using namespace task;

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// #define RAPIDJSON_NAMESPACE rapidjson110
// #define RAPIDJSON_HAS_STDSTRING 1
// #include <rapidjson-1.1.0/document.h>
// #include <rapidjson-1.1.0/writer.h>
// #include <rapidjson-1.1.0/prettywriter.h>
// #include <rapidjson-1.1.0/stringbuffer.h>

#include <../../prod/infrastructure/aisJhm/aisJhm2/AisJhm2RequestProcessor/AisJhm2MultiParam.h>
#include <jhm2/Jhm2Param/Jhm2ParamMsg.h>
#include <jhm2/Jhm2Param/Jhm2SimpleParam.h>

void OperatorIdTest::ExportToJSON(OperatorIdStatus& operatorIdStatus, int32_t passcode) {
    Jhm2ParamMsg* resp = new Jhm2ParamMsg();
    auto operatorIdParam = new AisJhm2MultiParam("OperatorID");
    operatorIdParam->addParameter(Jhm2SimpleParam("name", operatorIdStatus.operatorName));
    operatorIdParam->addParameter(Jhm2SimpleParam("state", toString(operatorIdStatus.state)));
    operatorIdParam->addParameter(Jhm2SimpleParam("fileStatus", toString(operatorIdStatus.fileStatus)));
    resp->insertParam(operatorIdParam);

    namespace fs = boost::filesystem;
    tes_common_ais::OFlocker ofl;
    ofl.open(JsonOutFile + std::to_string(passcode) + ".json");
    resp->getResponse(Jhm2ParamMsgRequest::JSON_FORMAT, ofl.ofstream());
    ofl.close();
}

AbstractTaskCore* task::getTaskImplementation(void) {
    static OperatorIdTest thisTask("OperatorIdTest");
    return dynamic_cast<Task*>(&thisTask);
}

OperatorIdTest::OperatorIdTest(const std::string& taskName) : Task(taskName),
                                                              operatorIdList(),
                                                              logPrefix_{"OperatorIdTest: "} {
}

OperatorIdTest::~OperatorIdTest() {}

bool OperatorIdTest::initialize() {
    AIS_LOG_INFO("OperatorIdTest::initialize");

    // Initialize the list locations input channel.
    listLocationsKnown_ = false;
    listTxInputChannel_ = dynamic_cast<LpsSaListMgrTxInterfaceInputChannel*>(task::InterfaceDb::fetch("ListTxInput"));
    if (nullptr == listTxInputChannel_) {
        AIS_LOG_ERROR("No list tx input channel defined.");
        return false;
    }
    return true;
}

void OperatorIdTest::getOperatorNameTest(int32_t passcode) {
    operatorIdListMgr.setOperatorId(passcode);
    auto status = operatorIdListMgr.getOperatorIdStatus();
    //tes_common_ais::CPMOperatorIdListEntry operatorId;
    AIS_LOG_ERROR("Retreived name: %s | passcode: %i | state: %u | fileStatus: %u", status.operatorName.c_str(), passcode, status.state, status.fileStatus);
    ExportToJSON(status, passcode);
}

bool OperatorIdTest::executive() {
    while (listTxInputChannel_->get(listTx_)) {
        listLocationsKnown_ = true;
        AIS_LOG_ERROR("Location received: %s", listTx_.basePath.c_str());
    }

    if (listLocationsKnown_) {
        operatorIdListMgr.initialize(listTx_.basePath);
        auto status = operatorIdListMgr.getOperatorIdStatus();

        AIS_LOG_ERROR("Default name: %s passcode: %i", operatorId.name.c_str(), operatorId.passcode);

        getOperatorNameTest(-1);
        getOperatorNameTest(1111);
        getOperatorNameTest(0);
        getOperatorNameTest(3333);
        getOperatorNameTest(56413); 
        getOperatorNameTest(-2);
        getOperatorNameTest(1234); 
        getOperatorNameTest(4444);
        return false;
    }

    return true;
}

void OperatorIdTest::cleanup() {
    AIS_LOG_INFO("OperatorIdTest::cleanup");
    operatorIdListMgr.publish(LpsSaListMgrInterfaceListFormat::CSV, CsvOutFile);
}
