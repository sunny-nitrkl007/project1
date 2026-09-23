/*
 * TipoffAssistLogging.h
 *
 *  Created on: Mar 8, 2021
 *      Author: pf
 */

#ifndef TIPOFFASSISTLOGGING_H_
#define TIPOFFASSISTLOGGING_H_

#include <chrono>

#include <boost/filesystem.hpp>

#include <chrono/print.hpp>

#include "../../../../tipoff_assist/toa_wl00_x86_64-b/include/toa_wl00_types.h"

/*
IMPORTANT! Increment this version number whenever making changes to the TOA logger code.

This version number disambiguates the log data if errors are discovered in old log versions.
Knowing the logger version will allow data users to throw out known bad data or recover information.
Without the log version, data users would not be able to tell good data from bad.
*/
#define TIPOFF_ASSIST_LOGGING_VERSION (1)

class TipoffAssistLogging {
public:
    enum class BulkSpillMeasureState : uint_least8_t {
        INIT,
        WAIT,
        MEASURE,
        DONE
    };

    TipoffAssistLogging() :
        filePath_(),
        maxFileSize_(0),
        toaRecordOpen_(false),
        toaActive_(false),
        toaTipping_(false),
        bulkSpillMeasureState_(BulkSpillMeasureState::INIT),
        startRealTime_(),
        startTime_(),
        firstRackTime_(),
        truckStartWeight_(NAN),
        truckTargetWeight_(NAN),
        bucketStartWeight_(NAN),
        startLiftAngle_(NAN),
        bulkEndArbPayloadErrorNorm_(NAN),
        bulkEndPayloadStdevNorm_(NAN),
        bulkEndUnsecPayloadUpperNorm_(NAN),
        bulkEndUnsecPayloadLowerNorm_(NAN),
        dumpAngle_(NAN),
        numTips_(0) {}

    bool init(const std::string& filePath, int maxFileSize) {
        filePath_ = filePath;
        maxFileSize_ = maxFileSize;

        logInit();

        return true;
    }

    void update(
            bool toaActive, uint_fast16_t toaActiveEid,
            float truckStartWeight, float truckTargetWeight,
            float bucketWeight, bool bucketWeightIsOk,
            float tiltValveCommand, float liftAngle, float bucketAngle,
            uint_fast8_t toaPayloadStatus, float toaArbPayloadErrorNorm, float toaPayloadStdevNorm,
            uint_fast8_t toaUnsecPfwStatus, float toaUnsecPayloadUpperBoundNorm, float toaUnsecPayloadLowerBoundNorm) {

        bool openRecord = (toaActive && !toaActive_);
        bool closeRecord = false;

        if (toaRecordOpen_) {
            bool toaRacking = (tiltValveCommand > 0.f) && toaActive;
            bool toaDumping = (tiltValveCommand < 0.f) && toaActive;

            // Count the number of racks, which means the end of a tip and beginning of check
            if (toaDumping) {
                toaTipping_ = true;
            }
            else if (toaRacking && toaTipping_) {
                toaTipping_ = false;

                if (0 == numTips_) {
                    firstRackTime_ = std::chrono::steady_clock::now();
                }

                ++numTips_;
            }

            // Wait for the bulk spill to end...
            if (BulkSpillMeasureState::INIT == bulkSpillMeasureState_) {
                // If we just finished the first spill and rack...
                if ((1 == numTips_) && !toaRacking) {
                    bulkSpillMeasureState_ = BulkSpillMeasureState::WAIT;
                }
            }

            // Wait for a measurement to be valid...
            if (BulkSpillMeasureState::WAIT == bulkSpillMeasureState_) {
                if ((TipAssistUnsecPfwStatus_t_VALID == toaUnsecPfwStatus) ||
                        (TipAssistSecPfwStatus_t_VALID_MEASURING == toaPayloadStatus) ||
                        (TipAssistSecPfwStatus_t_VALID_NOT_MEASURING == toaPayloadStatus)) {
                    bulkSpillMeasureState_ = BulkSpillMeasureState::MEASURE;
                }
            }

            // Wait for measurements to be invalid...
            if (BulkSpillMeasureState::MEASURE == bulkSpillMeasureState_) {
                bool validMeasurement = false;

                if (TipAssistUnsecPfwStatus_t_VALID == toaUnsecPfwStatus) {
                    // Capture unsecured
                    bulkEndUnsecPayloadUpperNorm_ = toaUnsecPayloadUpperBoundNorm;
                    bulkEndUnsecPayloadLowerNorm_ = toaUnsecPayloadLowerBoundNorm;
                    validMeasurement = true;
                }

                if ((TipAssistSecPfwStatus_t_VALID_MEASURING == toaPayloadStatus) ||
                        (TipAssistSecPfwStatus_t_VALID_NOT_MEASURING == toaPayloadStatus)) {
                    // Capture secured
                    bulkEndArbPayloadErrorNorm_ = toaArbPayloadErrorNorm;
                    bulkEndPayloadStdevNorm_ = toaPayloadStdevNorm;
                    validMeasurement = true;
                }

                if (!validMeasurement) {
                    bulkSpillMeasureState_ = BulkSpillMeasureState::DONE;
                }
            }

            // Record minimum bucket angle during tip-off
            if (bucketAngle < dumpAngle_) {
                dumpAngle_ = bucketAngle;
            }

            // Figure out if we need to close the record
            if (0 != toaActiveEid) {
                // We have an active event, see if is a completion event
                // 63038   Tip-Off Assist Disarmed Due to Time Out
                // 63039   Tip-Off Assist Disarmed Due to Payload Not Achievable
                // 63040   Tip-Off Assist Disarmed Due to Tilt Lever Racked
                // 63041   Tip-Off Assist Disarmed Due to Not in Stockpile Tip-Off Mode
                // 63042   Tip-Off Assist Disarmed Due to Truck Target Not Set
                // 63043   Tip-Off Assist Disarmed Due to Tilt Lever Released
                // 63044   Tip-Off Assist Disarmed Due to End of Travel
                // 63045   Tip-Off Assist Armed
                // 63046   Tip-Off Assist Complete
                // 63078   Tip-Off Assist Disarmed Due to Excessive Machine Speed
                if (63046 == toaActiveEid) {
                    // Tip-Off Assist Complete
                    closeRecord = true;
                }
                else if (63045 == toaActiveEid) {
                    // Tip-Off Assist Armed - no action
                }
                else {
                    // Tip-Off Assist Disarmed Due to ????
                    closeRecord = true;
                }
            }

            // If a new record is going to open, then we have to close the existing record.
            if (openRecord) {
                closeRecord = true;
            }
        }

        toaActive_ = toaActive;

        if (closeRecord) {
            // Make the record and add it to the file.
            auto endTime = std::chrono::steady_clock::now();
            float duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime_).count() / 1000.f;
            float bulkSpillDuration = std::chrono::duration_cast<std::chrono::milliseconds>(firstRackTime_ - startTime_).count() / 1000.f;
            uint_fast16_t reasonEid = toaActiveEid;

            logAppendResult(
                    startRealTime_,
                    truckStartWeight_, truckTargetWeight_, bucketStartWeight_,
                    startLiftAngle_,
                    duration, bulkSpillDuration,
                    bulkEndArbPayloadErrorNorm_, bulkEndPayloadStdevNorm_,
                    bulkEndUnsecPayloadUpperNorm_, bulkEndUnsecPayloadLowerNorm_,
                    dumpAngle_,
                    numTips_, reasonEid);

            /* toa cycle has been closed */
            toaRecordOpen_ = false;
        }

        if (openRecord) {
            toaRecordOpen_ = true;
            toaTipping_ = false;
            bulkSpillMeasureState_ = BulkSpillMeasureState::INIT;
            startRealTime_ = std::chrono::system_clock::now();
            startTime_ = std::chrono::steady_clock::now();
            firstRackTime_ = startTime_;
            truckStartWeight_ = truckStartWeight;
            truckTargetWeight_ = truckTargetWeight;
            bucketStartWeight_ = bucketWeightIsOk ? bucketWeight : NAN;
            startLiftAngle_ = liftAngle;
            bulkEndArbPayloadErrorNorm_ = NAN;
            bulkEndPayloadStdevNorm_ = NAN;
            bulkEndUnsecPayloadUpperNorm_ = NAN;
            bulkEndUnsecPayloadLowerNorm_ = NAN;
            dumpAngle_ = bucketAngle;
            numTips_ = 0;
        }
    }

protected:
    bool logInit() const {
        // Delete the file and get ready for a new one.
        std::ofstream ofs(filePath_, std::ios::out | std::ios::trunc);
        if (ofs) {
            ofs << "Version," << TIPOFF_ASSIST_LOGGING_VERSION << "\n";
            ofs << "Start Datetime (UTC),";
            ofs << "Truck Start Weight (t),";
            ofs << "Truck Target Weight (t),";
            ofs << "Bucket Start Weight (t),";
            ofs << "Start Lift Angle (deg),";
            ofs << "Duration (s),";
            ofs << "Bulk Spill Duration (s),";
            ofs << "Bulk End Secured Payload Error Normalized (% of rated payload),";
            ofs << "Bulk End Secured Payload Stdev Normalized (% of rated payload),";
            ofs << "Bulk End Unsecured Payload Error Upper Bound Normalized (% of rated payload),";
            ofs << "Bulk End Unsecured Payload Error Lower Bound Normalized (% of rated payload),";
            ofs << "Bucket Angle Minimum (deg),";
            ofs << "Number of Racks (count),";
            ofs << "Deactivation Reason (OID/EID)";
            ofs << std::endl;
            ofs.close();
        }
        else {
            AIS_LOG_ERROR("Cannot create %s file for logging.", filePath_);
            return false;
        }

        return true;
    }

    void logAppendResult(
            const std::chrono::system_clock::time_point& startRealTime,
            float truckStartWeight, float truckTargetWeight, float bucketStartWeight,
            float startLiftAngle,
            float duration, float bulkSpillDuration,
            float bulkEndArbPayloadErrorNorm, float bulkEndPayloadStdevNorm,
            float bulkEndUnsecPayloadUpperNorm, float bulkEndUnsecPayloadLowerNorm,
            float dumpAngle,
            uint_fast16_t numTips, uint_fast16_t reasonEid) const {

        boost::system::error_code ec;

        boost::uintmax_t filesize = boost::filesystem::file_size(filePath_, ec);
        if (ec || (filesize >= maxFileSize_)) {
            logInit();
        }

        std::ofstream ofs(filePath_, std::ios::out | std::ios::app);
        if (ofs) {
            // Log the start time
            ofs << tes_common_ais::putTime(startRealTime, tes_common_ais::date_time_formats::ISO_DATE_TIME_LOCAL) << ",";

            // Truck Start Weight
            ofs << std::fixed << std::setprecision(3) << truckStartWeight << ",";

            // Truck Target Weight
            ofs << std::fixed << std::setprecision(3) << truckTargetWeight << ",";

            // Bucket Start Weight
            if (std::isfinite(bucketStartWeight)) {
                ofs << std::fixed << std::setprecision(3) << bucketStartWeight << ",";
            }
            else {
                ofs << "?,";
            }

            // Start Lift Angle
            if (std::isfinite(startLiftAngle)) {
                ofs << std::fixed << std::setprecision(1) << startLiftAngle << ",";
            }
            else {
                ofs << "?,";
            }

            // Duration
            ofs << std::fixed << std::setprecision(2) << duration << ",";

            // Bulk Spill Duration
            ofs << std::fixed << std::setprecision(2) << bulkSpillDuration << ",";

            // Bulk Spill End Arbitrated Payload Error Normalized
            if (std::isfinite(bulkEndArbPayloadErrorNorm)) {
                ofs << std::fixed << std::setprecision(3) << bulkEndArbPayloadErrorNorm << ",";
            }
            else {
                ofs << "?,";
            }

            // Bulk Spill End Payload Standard Deviation Normalized
            if (std::isfinite(bulkEndPayloadStdevNorm)) {
                ofs << std::fixed << std::setprecision(3) << bulkEndPayloadStdevNorm << ",";
            }
            else {
                ofs << "?,";
            }

            // Bulk Spill End Unsecured Payload Upper Bound Normalized
            if (std::isfinite(bulkEndUnsecPayloadUpperNorm)) {
                ofs << std::fixed << std::setprecision(3) << bulkEndUnsecPayloadUpperNorm << ",";
            }
            else {
                ofs << "?,";
            }

            // Bulk Spill End Unsecured Payload Lower Bound Normalized
            if (std::isfinite(bulkEndUnsecPayloadLowerNorm)) {
                ofs << std::fixed << std::setprecision(3) << bulkEndUnsecPayloadLowerNorm << ",";
            }
            else {
                ofs << "?,";
            }

            // Dump Angle
            if (std::isfinite(dumpAngle)) {
                ofs << std::fixed << std::setprecision(1) << dumpAngle << ",";
            }
            else {
                ofs << "?,";
            }

            // Number of Tips
            ofs << numTips << ",";

            // Reason
            ofs << reasonEid << ",";

            // Next record
            ofs << std::endl;

            ofs.close();
        }
    }

private:
    std::string filePath_;
    int maxFileSize_;
    bool toaRecordOpen_;
    bool toaActive_;
    bool toaTipping_;
    BulkSpillMeasureState bulkSpillMeasureState_;
    std::chrono::system_clock::time_point startRealTime_;
    std::chrono::steady_clock::time_point startTime_;
    std::chrono::steady_clock::time_point firstRackTime_;
    float truckStartWeight_;
    float truckTargetWeight_;
    float bucketStartWeight_;
    float startLiftAngle_;
    float bulkEndArbPayloadErrorNorm_;
    float bulkEndPayloadStdevNorm_;
    float bulkEndUnsecPayloadUpperNorm_;
    float bulkEndUnsecPayloadLowerNorm_;
    float dumpAngle_;
    uint_fast16_t numTips_;
};


#endif /* TIPOFFASSISTLOGGING_H_ */
