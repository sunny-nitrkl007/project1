require "interfaces_CpmCommon.rb"

Interfaces.update( {
    # Add new interface definitions here
    "DataLinkDataInput" => InterfaceDefs_CpmCommon::DataLinkDataInput,
    "PwmInputChannelsOutput" => InterfaceDefs_CpmCommon::PwmInputChannelsOutput,
})
  
Parameters.update({
    "Tabs" => Parameters["Tabs"] += [
        "DataLinkDataPlugin",
        "PWMInputPlugin",
    ]
})
