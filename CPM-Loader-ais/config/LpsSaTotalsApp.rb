require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update({
  "LoadRecordInput" => InterfaceDefs_Loaders::LpsSaLoadRecordChannelInput,
  "RequestInput" => InterfaceDefs_Loaders::LpsSaTotalsRequestInputChannel,
  "ResponseOutput" => InterfaceDefs_Loaders::LpsSaTotalsResponseOutputChannel,
  "TotalsOutput" => InterfaceDefs_Loaders::LpsSaTotalsOutputChannel,
  "PrinterRequestOutput" => InterfaceDefs_CpmCommon::SerialPrinterRequestOutputChannel,
  "WritePrinterCnfgInput" => InterfaceDefs_Loaders::LpsSaTotalsWritePrinterCnfgInputChannel,
  "PrinterCnfgOutput" => InterfaceDefs_Loaders::LpsSaTotalsPrinterCnfgOutputChannel,
  "DisplayStateInput" => InterfaceDefs_Loaders::LpsSaUIDisplayStateInputChannel,
  "ShmClockInput" => InterfaceDefs::ShmClockInput,
  "VP3CreateRecordOutput" => InterfaceDefs_CpmCommon::VP3RecordOutput,
  "PartNumbersInput" => InterfaceDefs_CpmCommon::PartNumbersInput,
  "DataLinkDataInput" => InterfaceDefs_CpmCommon::DataLinkDataInput,
  "FileTransferBridgeRequestOutput" => InterfaceDefs_CpmCommon::FileTransferBridgeRequestOutput,
  "ListTxInput" => InterfaceDefs_Loaders::LpsSaListMgrTxInputChannel,
  "AutonomyConditionDiagnosticsTxChannelInput" => InterfaceDefs_Loaders::AutonomyConditionDiagnosticsTxInputChannel,
  "LpsSaTotalsUSBSaveProgressOutput" => InterfaceDefs_Loaders::LpsSaTotalsUSBSaveProgressOutputChannel,
  "LpsSaWeighReqstOutput" => InterfaceDefs_Loaders::LpsSaWeighReqstChannelOutput,
})

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update({
  "loggerThreshold" => "error", ##  All options listed in descending severity order
                               ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
  "cycleRate_hz" => 2.0,
  "storageRoot" => "/opt/appdata/CPM/LpsSaTotalsApp/nvm",
  "tempRoot" => "/tmp/appdata/CPM/LpsSaTotalsApp",
  "fileTransferTxDir" => "/opt/appdata/CPM/FileTransferBridgeApp/TxFiles",
  "cdaServerIpAddress" => "165.26.79.43",
  "cdaServerPort" => "50006",
})

Execution = {
  "executableName" => "LpsSaTotalsApp"
}



