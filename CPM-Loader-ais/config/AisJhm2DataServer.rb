require "commonLoad.rb"
require "commonTaskParams.rb"
require "Robot.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
    "LoadRecordInput" => InterfaceDefs_Loaders::LpsSaLoadRecordChannelInput,    
    "LpsSaJobMgrTxChannelInput" => InterfaceDefs_Loaders::LpsSaJobMgrTxChannelInput,
    "LpsSaWeighTxChannelInput" => InterfaceDefs_Loaders::LpsSaWeighTxChannelInput,
    "LpsSaJobMgrReqstChannelOutput" => InterfaceDefs_Loaders::LpsSaJobMgrReqstChannelOutput,
    "LpsSaJobMgrRespChannelInput" => InterfaceDefs_Loaders::LpsSaJobMgrRespChannelInput,
    "AutonomyConditionDiagnosticsRequestChannelOutput"  => InterfaceDefs_Loaders::AutonomyConditionDiagnosticsRequestChannelOutput,
    "AutonomyConditionDiagnosticsResponseChannelInput"  => InterfaceDefs_Loaders::AutonomyConditionDiagnosticsResponseChannelInput,
    "AutonomyConditionDiagnosticsTxChannelInput"  => InterfaceDefs_Loaders::AutonomyConditionDiagnosticsTxInputChannel,
    "LpsSaWeighReqstChannelOutput" => InterfaceDefs_Loaders::LpsSaWeighReqstChannelOutput,
    "LpsSaWeighRespChannelInput" => InterfaceDefs_Loaders::LpsSaWeighRespChannelInput,
    "LpsSaWeighTxChannelInput" => InterfaceDefs_Loaders::LpsSaWeighTxChannelInput,
    "AisJhm2TxChannelOutput" => InterfaceDefs_Loaders::AisJhm2TxChannelOutput,
    "AisJhm2TxChannelInput" => InterfaceDefs_Loaders::AisJhm2TxChannelInput,
    "MachineSNOutput" => InterfaceDefs::MachineSNOutput,
    "PartNumbersInput" => InterfaceDefs_CpmCommon::PartNumbersInput,
    "ListTxInput" => InterfaceDefs_Loaders::LpsSaListMgrTxInputChannel,
    "ListPostOutput" => InterfaceDefs_Loaders::LpsSaListMgrPostOutputChannel,
    "ListNotifyInput" => InterfaceDefs_Loaders::LpsSaListMgrNotifyInputChannel,
    "TotalsInput" => InterfaceDefs_Loaders::LpsSaTotalsInputChannel,
    "TotalsRequestOutput" => InterfaceDefs_Loaders::LpsSaTotalsRequestOutputChannel,
    "TotalsResponseInput" => InterfaceDefs_Loaders::LpsSaTotalsResponseInputChannel,
    "PrinterCnfgInput" => InterfaceDefs_Loaders::LpsSaTotalsPrinterCnfgInputChannel,
    "WritePrinterCnfgOutput" => InterfaceDefs_Loaders::LpsSaTotalsWritePrinterCnfgOutputChannel,
    "PrinterRequestOutput" => InterfaceDefs_CpmCommon::SerialPrinterRequestOutputChannel,
    "DisplayStateOutput" => InterfaceDefs_Loaders::LpsSaUIDisplayStateOutputChannel,
    "DisplaySettingsInput" => InterfaceDefs_Loaders::LpsSaUIDisplaySettingsInputChannel,
    "ShmClockInput" => InterfaceDefs::ShmClockInput,
    "CalibrationRequestUIOutput" => InterfaceDefs_CpmCommon::CalibrationRequestUIOutput,
    "CalibrationResponseUIInput" => InterfaceDefs_CpmCommon::CalibrationResponseUIInput,
    "DataLinkDataInput" => InterfaceDefs_CpmCommon::DataLinkDataInput,
    "DataLinkDataOutput" => InterfaceDefs_CpmCommon::DataLinkDataOutput,
    "SystemRestartRequestOutput" => InterfaceDefs::SystemRestartRequestOutput,
    "DemoAppReqstChannelOutput" => InterfaceDefs_Loaders::DemoAppReqstChannelOutput,
    "DemoAppTxChannelInput" => InterfaceDefs_Loaders::DemoAppTxChannelInput,
    "EventDiagnosticDataInput" => InterfaceDefs::EventDiagnosticDataInput,
    "DispatchTxInput" => InterfaceDefs_Loaders::WorkOrderAssistTxInputChannel,
    "DispatchSettingsInput" => InterfaceDefs_Loaders::WorkOrderAssistSettingsInputChannel,
    "BEMSimStateOutput" => InterfaceDefs_Loaders::LpsSaUIBEMSimStateOutputChannel,
    "LpsSaTotalsUSBSaveProgressInput" => InterfaceDefs_Loaders::LpsSaTotalsUSBSaveProgressInputChannel,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
    "cycleRate_hz" => 20.0,
    "scheduler" => "SCHED_RR",
    "schedulerPriority" => 1,
    "loggerThreshold" => "error",  
    # Must match path in service_download_operator_id_list.cgi
    "storageRoot" => "/opt/appdata/CPM/AisJhm2DataServer/nvm",
    "tempRoot" => "/tmp/appdata/CPM/AisJhm2DataServer",
    "msnLinkageMappingAU2020Path" => "/opt/CPM/config/msn_linkage_mapping_au2020.json",
} )

ScsRxTimeouts = {
  "LpsSaJobMgrTxChannelInput_rxTimeout_sec" => 5.0,
  "DemoAppTxChannelInput_rxTimeout_sec" => 5.0,
  "LpsSaWeighTxChannelInput_rxTimeout_sec" => 5.0,
  "LpsSaJobMgrRespChannelInput_rxTimeout_sec" => 5.0,
  "AisJhm2TxChannelInput_rxTimeout_sec" => 5.0,
  "EventDiagnosticDataInput_rxTimeout_sec" => 5.0,
  "DispatchTxInput_rxTimeout_sec" => 10.0,
}

ScsTxRates = {
  "AisJhm2TxChannelOutput_txRate_sec" => -1,
  "MachineSNOutput_txRate_sec" => -1,
}
Execution = {
  "executableName" => "aisJhm2DataServer",
}

