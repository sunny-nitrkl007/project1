#pragma once

#ifndef LPSSATOTALSTELEMETRY_HPP
#define LPSSATOTALSTELEMETRY_HPP

#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>
#include <interfaces/DataLinkData/DataLinkData.h>
#include <interfaces/PartNumbers/InterfaceTypes.h>
#include <TMAC_Telemetry_Transfer.pb.h>

#include "LpsSaTotalsOperatorId.h"

class LpsSaTotalsTelemetry
{
public:
    LpsSaTotalsTelemetry()
    {
        initialize();
    };

    void initialize();
    void updateDataLinkData(const DataLinkData& dataLinkData);
    std::string generatePcsCycleMsg(const LpsSaLoadRecordChannelStorage &loadRecord,
            const LpsSaTotalsOperatorId& operatorId);

private:
    CAT::Telemetry::PcsCycle pcsCycle;
};

#endif
