Interfaces.update( {
    # Application specific channels
    # "MySubsystem_DatalinkParameterDataOutput" => InterfaceDefs::MySubsystem_DatalinkParameterDataOutput,
    "RpaClientDatalinkParameterDataOutput" => InterfaceDefs::RpaClientDatalinkParameterDataOutput,
} )

# Update Settings if necessary
DatalinkParameterPublisher["Settings"].update({
    ### Threshold in milliseconds above which passive timers will be used instead of callback timers, to prevent Acd2Task from stalling.
    ### Defaults to 250 milliseconds
    # "PassiveTimerThresholdMs" => 250,

    ### SCS Channel name for publishing all Rx parameter data
    ### Defaults to "Acd2RxDatalinkParameterData"
    # "AllRxChannelName" => "Acd2RxDatalinkParameterData",

    ### SCS Channel name for publishing all Wr parameter data
    ### Defaults to "Acd2WrDatalinkParameterData"
    # "AllWrChannelName" => "Acd2WrDatalinkParameterData",
})

# Add app-specific channels
DatalinkParameterPublisher["Channels"].update({
    ### Subsystem and/or Task specific channels
    # "MySubsystem_DatalinkParameterData" => {  # SCS Channel name
    #     "Parameters" => {
    #         "Desired Engine RPM" => {
    #             Datalink::Keys::ID              => 0x46,
    #             Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    #         },

    #         "Chassis Rollover Hoist" => {
    #             Datalink::Keys::ID              => 0x00,
    #             Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::CAT_EXT_ID,
    #             Datalink::Keys::SERVER_NAME     => "Chassis",                           # Only required if there are multiple sources of the same parameter
    #         },

    #         "Product ID" => {
    #             Datalink::Keys::ID              => 0xF82D,
    #             Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
    #             Datalink::Keys::WRITE_METHOD    => Datalink::WriteMethod::DATALINK_WR,  # Only required if the same parameter is configured for DATALINK_RX and DATALINK_WR
    #         },
    #     },
    # },

    ### PID(s) for RpaClientTask to determine "Ready to Flash"
    "RpaClientDatalinkParameterData" => {  # SCS Channel name
        "Parameters" => {
            "Actual Engine RPM" => {
                Datalink::Keys::ID              => 0x40,
                Datalink::Keys::PARAMETER_TYPE  => Datalink::ParameterType::PID,
            },
        },
    },
})

### For multi-app, load staged Acd2Task_DatalinkParameterPublisher_aux*.rb files
# loadInstanceStagedFiles(File.basename( __FILE__ ) + "_aux")
