require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update({
  "PostInput" => InterfaceDefs_Loaders::LpsSaListMgrPostInputChannel,
  "NotifyOutput" => InterfaceDefs_Loaders::LpsSaListMgrNotifyOutputChannel,
  "TxOutput" => InterfaceDefs_Loaders::LpsSaListMgrTxOutputChannel,
  "DisplayStateInput" => InterfaceDefs_Loaders::LpsSaUIDisplayStateInputChannel,
  "FileTransferBridgeRequestOutput" => InterfaceDefs_CpmCommon::FileTransferBridgeRequestOutput,
  "FileTransferBridgeResponseInput" => InterfaceDefs_CpmCommon::FileTransferBridgeResponseInput,
  "FileTransferBridgeIndicationInput" => InterfaceDefs_CpmCommon::FileTransferBridgeIndicationInput,
})

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update({
  "loggerThreshold" => "error", ##  All options listed in descending severity order
                               ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
  "cycleRate_hz" => 1.0,
  "fileTransferTxDir" => "/opt/appdata/CPM/FileTransferBridgeApp/TxFiles",
  "storageRoot" => "/opt/appdata/CPM/LpsSaListMgrApp/nvm",
  # Must match path in service_download_truck_list.cgi and service_download_material_list.cgi
  "tempRoot" => "/tmp/appdata/CPM/LpsSaListMgrApp"
})

Execution = {
  "executableName" => "LpsSaListMgrApp"
}

