require "StopPrograms_Base.rb"
require "commonLoad.rb"

# Add TES Common specific processes to monitor for termination
Parameters["processesToMonitor"].concat([
    "Acd2Task",
    "bmiCdl",
    "bmiEthernet",
    "bmiJ1939",
    "CoachingTask",
    "FileTransferBridgeApp",
    "OutputApp",
    "PwmInput",
    "RemotePrinterApp",
    "SerialPrinterApp",
    "SwitchInputApp",
    "aisXcpServer"
])

Parameters.update({
    # Process name of pcm that will receive a SIGTERM.
    # "pcmTaskName" => "pcm",

    # Amount of time in seconds StopPrograms will wait for pcm to stop after receiving SIGTERM.
    # "pcmStopTime_sec" => 8,

    # List of process names to terminate, limited to 15 characters. For all processes in this list, SIGTERM will be sent after pcmStopTime_sec has elapsed. Note that any processes launched by pcm should under normal circumstances be terminated by pcm.
    # "processesToTerminate" => [
    #     "timeSyncObject",
    # ],

    # Amount of time in seconds StopPrograms will wait for processesToTerminate to stop after receiving SIGTERM. When this value expires, any remaining active processes will be sent SIGKILL.
    # "processStopTime_sec" => 2,

    # Process name(s) of scs processes that will be sent 3 SIGTERM events followed by 3 SIGKILl events after processStopTime_sec has elapsed.
    # "scsTaskNames" => [ "scs", ],

    # File the contains the key switch override state, written to in case PCM was force killed before it could release the key switch override.
    # "keySwitchOverrideFile" => "/dev/shm/AHS_GPIO/KeySwitchOverrideAHS",
})

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( __FILE__)
