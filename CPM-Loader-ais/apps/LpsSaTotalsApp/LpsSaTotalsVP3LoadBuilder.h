#pragma once

#ifndef LPSSATOTALSVP3LOADBUILDER_HPP
#define LPSSATOTALSVP3LOADBUILDER_HPP

#include <vector>
#include <array>
#include <chrono>

#include <chrono/print.hpp>
#include <chrono/convert.hpp>

#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>
#include <interfaces/VP3Record/VP3Record.h>
#include <interfaces/VP3Record/UID_Descriptions.h>

#include "LpsSaTotalsOperatorId.h"

namespace VP3LoadBuilder {

    inline VP3Record generateVP3StatusRecord(uint32_t serviceHourMeter,
            const LpsSaTotalsOperatorId& operatorId) {
        auto now = std::chrono::system_clock::now();
        uint32_t timeUtc = tes_common_ais::systemClockTimePointToUidTime(now);
        int16_t timeOffset = tes_common_ais::getLocalTimeOffset(now).count();

        /*
         * Return the Status Record
         */
        return VP3RecordBuilder::makeOperatorIdStatusRecord(
                timeUtc, timeOffset, serviceHourMeter,
                operatorId.getDescription());
    }

};

#endif
