#include "CoachingTask.h"


enum class gpsTypes : uint8_t
{
    GPS_GOOD,
    GPS_GOOD_TIME,
    GPS_GOOD_DISTANCE,
    GPS_UNKOWN,
    GPS_BAD_DSI,
    GPS_BAD_STATUS,
    GPS_BAD_TIMESTAMP,
    GPS_BAD_LAT_LONG,
};

///////////////////////////////////////////////////////////////////////////////
/// @Loads check GPS, to add Record to breadcrumbLog: BAD-GPS (DSI, Status, Time, Lat-Long) GOOD, TIME, DISTANCE
///////////////////////////////////////////////////////////////////////////////
void CoachingTask::checkGPS(DataLinkParam *dlParam)
{
    int8_t          gpsBadThresholdCounter = 25;    // 3 seconds = 8.3333Hz X 3,  BAD GPS records in a row before announcing GPS-BAD

    static int64_t  lastRecordedGoodSecondsSinceEpoch = 0;
    static double   lastRecordedGoodLatitude  = 0.0;
    static double   lastRecordedGoodLongitude = 0.0;
    static gpsTypes previousGpsState = gpsTypes::GPS_UNKOWN;
    static int8_t   gpsBadCounter = 0;              // accumulated count of consecutive GPS-BAD samples

    int64_t         currentSecondsSinceEpoch;
    gpsTypes        currentGpsState = gpsTypes::GPS_UNKOWN;
    double          currentGoodLatitude  = 0.0;
    double          currentGoodLongitude = 0.0;

    const GPSDataLinkParam gpsParam(*dlParam);  // convert PID data to GPS-object

    currentSecondsSinceEpoch = std::time(NULL); // get current Time

    // check Validity of GPS data
    if (0 != dlParam->GetVarLengthParamDsi())    // we have BAD dataLinkData
    {
        currentGpsState = gpsTypes::GPS_BAD_DSI;
    }
    else if(GPSDataLinkParam::GpsPositionStatusType::POSITION_VALID != gpsParam.GetGpsStatus())
    {
        currentGpsState = gpsTypes::GPS_BAD_STATUS;
    }
    else if (gpsParam.isNotValidTimestamp())    // check all timestamp bytes
    {
        currentGpsState = gpsTypes::GPS_BAD_TIMESTAMP;
    }
    else if (gpsParam.isNotValidLatLong())      // check all Lat-Long bytes are not 0xFF
    {
        currentGpsState = gpsTypes::GPS_BAD_LAT_LONG;
    }
    else    // GPS data is Good
    {
        currentGpsState = gpsTypes::GPS_GOOD;
        breadcrumbLog.setGpsStatus(gpsParam);       // write new GOOD GPS to BreadcrumbLog for Tips and other records to use
        coachingTipHistory.setGpsStatus(gpsParam);
        currentGoodLatitude  = gpsParam.GetGpsLatitude(false);
        currentGoodLongitude = gpsParam.GetGpsLongitude(true);
        gpsBadCounter = 0;
    }

    // check for any state changes and add a record...  might be more than needed, but UI can filter out
    if (currentGpsState != previousGpsState)
    {
        if (gpsTypes::GPS_GOOD == currentGpsState)  // reset last recorded Time & Lat-Long
        {
            breadcrumbLog.commandReceived(BreadcrumbStatus::Type::GPS_GOOD, (uint32_t)currentGpsState); // whatever the current State is

            lastRecordedGoodSecondsSinceEpoch = currentSecondsSinceEpoch;
            lastRecordedGoodLatitude  = currentGoodLatitude;
            lastRecordedGoodLongitude = currentGoodLongitude;
            AIS_LOG_INFO("GPS-GOOD Transition:%d  %f-%f   %f-%f", currentGpsState, currentGoodLatitude, currentGoodLongitude, lastRecordedGoodLatitude, lastRecordedGoodLongitude);
            previousGpsState = currentGpsState; // save last State
            gpsBadCounter = 0;
        }
        else
        {
            AIS_LOG_INFO("GPS-BAD:%d", currentGpsState);
            gpsBadCounter++;
            if (gpsBadThresholdCounter <= gpsBadCounter)
            {
                breadcrumbLog.commandReceived(BreadcrumbStatus::Type::GPS_BAD, (uint32_t)currentGpsState); // whatever the current State is
                AIS_LOG_ALERT("GPS-BAD Transition:%d-%d, %f-%f   %f-%f", currentGpsState, gpsBadCounter, currentGoodLatitude, currentGoodLongitude, lastRecordedGoodLatitude, lastRecordedGoodLongitude);

                previousGpsState = currentGpsState; // save last State
                gpsBadCounter = 0;
                gpsParam.SetGpsStatus(GPSDataLinkParam::GpsPositionStatusType::POSITION_INVALID); // set to INVALID, when BAD
                breadcrumbLog.setGpsStatus(gpsParam);       // write new BAD GPS to BreadcrumbLog for Tips and other records to use
                coachingTipHistory.setGpsStatus(gpsParam);
            }
        }
    }


    if(gpsTypes::GPS_GOOD == currentGpsState)
    {
        double distanceMetersDiff = gpsParam.getDistanceMeters(lastRecordedGoodLatitude, lastRecordedGoodLongitude);
        uint64_t timeSecondsDiff  = static_cast<uint64_t>(currentSecondsSinceEpoch - lastRecordedGoodSecondsSinceEpoch);

        AIS_LOG_INFO("GPS TimeDiff:%d DistDiff:%f  %f-%f   %f-%f", timeSecondsDiff, distanceMetersDiff, currentGoodLatitude, currentGoodLongitude, lastRecordedGoodLatitude, lastRecordedGoodLongitude);

        // check TIME is configured
        if ((0 != breadcrumbLog.getMaxTimeSeconds()) && (breadcrumbLog.getMaxTimeSeconds() <= timeSecondsDiff))
        {
            breadcrumbLog.commandReceived(BreadcrumbStatus::Type::GPS_GOOD, (uint32_t)gpsTypes::GPS_GOOD_TIME);
            lastRecordedGoodSecondsSinceEpoch = currentSecondsSinceEpoch;
            lastRecordedGoodLatitude  = currentGoodLatitude;
            lastRecordedGoodLongitude = currentGoodLongitude;
            AIS_LOG_INFO("GPS-Time-Thresh:%d     state:%d", breadcrumbLog.getMaxTimeSeconds(), (uint32_t)gpsTypes::GPS_GOOD_TIME);
        }
        else    // check DISTANCE
        {
            if(breadcrumbLog.getMaxDistanceMeters() <= distanceMetersDiff)
            {
                breadcrumbLog.commandReceived(BreadcrumbStatus::Type::GPS_GOOD, (uint32_t)gpsTypes::GPS_GOOD_DISTANCE);
                lastRecordedGoodSecondsSinceEpoch = currentSecondsSinceEpoch;
                lastRecordedGoodLatitude  = currentGoodLatitude;
                lastRecordedGoodLongitude = currentGoodLongitude;
                AIS_LOG_INFO("GPS-Distance-Thresh:%d     state:%d", breadcrumbLog.getMaxDistanceMeters(), (uint32_t)gpsTypes::GPS_GOOD_DISTANCE);
            }
        }

    }
}
