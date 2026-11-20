#ifndef LpsSaTotalsTelemetryTest_H
#define LpsSaTotalsTelemetryTest_H

#include <ais/task/Task.h>

#include <interfaces/LpsSaLoadRecordChannel/Channel/Output/channel.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#include <interfaces/PartNumbers/InterfaceTypes.h>
#include <interfaces/FileTransferBridgeRequest/InterfaceTypes.h>
#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>
#include <interfaces/DataLinkData/DataLinkData.h>
#include <interfaces/PartNumbers/InterfaceTypes.h>
#include <TMAC_Telemetry_Transfer.pb.h>

class LpsSaTotalsTelemetryTest: public task::Task
{
public:
    LpsSaTotalsTelemetryTest( const std::string& taskName );
    virtual ~LpsSaTotalsTelemetryTest( );

    virtual bool initialize( );
    virtual bool executive( );
    virtual void cleanup( );

protected:
private:
    DataLinkDataOutput* dataLinkDataOutput_;
    PartNumbersOutput* partNumbersOutput_;
    FileTransferBridgeRequestInput* fileTransferBridgeRequestInput_;
    LpsSaLoadRecordChannelOutputChannel* lpsSaLoadRecordChannelOutput_;

    DataLinkData can1DlData;
    DataLinkParam gpsParam;

    DataLinkData intDlData;
    DataLinkParam operatorIdParam;
};

#endif //OPERATORIDTEST_H
