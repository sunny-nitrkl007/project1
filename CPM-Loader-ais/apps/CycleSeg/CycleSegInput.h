#include <chrono>

#include <interfaces/ShmClock/InterfaceTypes.h>
#include <interfaces/LpsSaWeighTxChannel/InterfaceTypes.h>
#include <interfaces/LpsSaJobMgrTxChannel/InterfaceTypes.h>
#include <interfaces/DataLinkData/InterfaceTypes.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <gps_public.h>
#ifdef __cplusplus
}
#endif
#include <clock_proto.h>

class CycleSegInput {
public:
    CycleSegInput();

    bool initialize(uint16_t appNumber, ConfigSection taskCfg);
    void update();

private:
    bool Initialize_GPS();
    static constexpr unsigned_32 DefaultGpsDistanceThreshold = 20; // meters
    static constexpr unsigned_32 DefaultGpsTimeThreshold     = 60; // seconds
    gps_config              gpsConfig;
    GPS_FUNC_INFO           gpsAccessorFunctions;
    unsigned_8              previousPositionStatus;
    ConfigSection           rubyCfg;

    typedef std::chrono::steady_clock SteadyClock;
    typedef SteadyClock::time_point TimePoint;

    TimePoint lastShmClockTime_;
    ShmClockInput* shmClockInputChannel_;
    ShmClockStorage shmClockChannelData_;

    TimePoint lastWeighTxTime_;
    LpsSaWeighTxChannelInput* weighTxInputChannel_;
    LpsSaWeighTxChannelStorage weighTxChannelData_;

    DataLinkDataInput *dataLinkDataInputChannel_;
};
