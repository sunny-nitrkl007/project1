require "Acd2Task_DatalinkManager_Enums.rb"

SyncClockManager.update({
    "enabled" => true,                  # Flag for enabling/disabling the plugin
    "canPort" => Datalink::Port::CAN1,  # CAN port for SHM and RTC sync, Valid values: Datalink::Port::CAN1,2,3,4

    # Service Hour Meter config
    "SHM" => {
        "syncType" => Datalink::SHM::Type::J1939,   # J1939 / CDL / Disabled, defaults to J!939
        "master" => false,                          # Configure as the sync master, defaults to false
        "publishEnabled" => true,                   # Publish the ShmClock SCS object, defaults to true
        "publishRateSec" => 1.0,                    # Publish rate of ShmClock, defaults to 1.0 seconds, minimum valus is 0.001 seconds (1 millisecond)
        "savePeriod_ms" => 10000,                   # NVM save period value in milliseconds
        "useTelematicsReasonCode" => false,         # TRUE to use telematics RC_SHM 155, FALSE to use RC_SHM 55, defaults to true
    },

    # Realtime Clock / Timezone (commented out for backwards compatibility)
    "RTC_TZ" => {
        "RTC_Security"              => Datalink::RTC::Security::NonSecure,          # NonSecure / Secure
        "RTC_Type"                  => Datalink::RTC::Type::PIDClient,              # StandAlone / DistributedClient / DistributedServer / PIDClient / PIDServer
        "RTC_Master"                => 0x25,                                        # Relevant for RTC::Type DistributedClient or PIDClient
        "RTC_system_clock_update"   => Datalink::RTC::SystemClockUpdate::Threshold, # None / Threshold
        "RTC_threshold_s"           => 1,                                           # Time delta (in sec) criteria for updating System Clock for SystemClockUpdate::Threshold
        "RTC_sync_period_sec"       => 86400,                                       # Time duration (in sec) for the next synchronization
    },
})

