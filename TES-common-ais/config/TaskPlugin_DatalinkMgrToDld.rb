require "interfaces_CpmCommon.rb"

DatalinkMgrToDld = {
  "enabled" => true,
}

Interfaces.update( {
   "DataLinkDataPublisherOutput" => InterfaceDefs_CpmCommon::DataLinkDataOutput,
} )
