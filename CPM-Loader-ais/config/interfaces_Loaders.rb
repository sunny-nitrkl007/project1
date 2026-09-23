require "interfaces.rb"

module InterfaceDefs_Loaders

#Demo App Interfaces
DemoAppTxChannelInput = InterfaceDefs.createBasicInputInterface("DemoAppTxChannel")
DemoAppTxChannelInput["channel"]["queueSize"] = 20;
DemoAppTxChannelOutput = InterfaceDefs.createBasicOutputInterface("DemoAppTxChannel")

DemoAppReqstChannelInput = InterfaceDefs.createBasicInputInterface("DemoAppReqstChannel") 
DemoAppReqstChannelInput["channel"]["queueSize"] = 20;
DemoAppReqstChannelOutput = InterfaceDefs.createBasicOutputInterface("DemoAppReqstChannel")

#JOB MGR interfaces
LpsSaJobMgrTxChannelInput = InterfaceDefs.createBasicInputInterface("LpsSaJobMgrTxChannel")#get parameters from JobMgr
LpsSaJobMgrTxChannelInput["channel"]["queueSize"] = 20;
LpsSaJobMgrTxChannelOutput = InterfaceDefs.createBasicOutputInterface("LpsSaJobMgrTxChannel") #set parameters  from JM

LpsSaJobMgrReqstChannelInput = InterfaceDefs.createBasicInputInterface("LpsSaJobMgrReqstChannel") #getcmd from UI
LpsSaJobMgrReqstChannelInput["channel"]["queueSize"] = 20;
LpsSaJobMgrReqstChannelOutput = InterfaceDefs.createBasicOutputInterface("LpsSaJobMgrReqstChannel")#setcmd to JobMgr

LpsSaJobMgrRespChannelInput = InterfaceDefs.createBasicInputInterface("LpsSaJobMgrRespChannel")#getres from JobMgr
LpsSaJobMgrRespChannelInput["channel"]["queueSize"] = 20;
LpsSaJobMgrRespChannelOutput = InterfaceDefs.createBasicOutputInterface("LpsSaJobMgrRespChannel")#set res to UI App

LpsSaJobMgrDebugChannelInput = InterfaceDefs.createBasicInputInterface("LpsSaJobMgrDebugChannel")
LpsSaJobMgrDebugChannelOutput = InterfaceDefs.createBasicOutputInterface("LpsSaJobMgrDebugChannel")

# LpsSaTotalsApp Interfaces
LpsSaLoadRecordChannelInput = InterfaceDefs.createBasicInputInterface("LpsSaLoadRecordChannel")
LpsSaLoadRecordChannelInput["channel"]["queueSize"] = 10;
LpsSaLoadRecordChannelOutput = InterfaceDefs.createBasicOutputInterface("LpsSaLoadRecordChannel")

LpsSaTotalsInputChannel = InterfaceDefs.createBasicInputInterface("LpsSaTotals")
LpsSaTotalsInputChannel["channel"]["queueSize"] = 1;
LpsSaTotalsOutputChannel = InterfaceDefs.createBasicOutputInterface("LpsSaTotals")

LpsSaTotalsRequestInputChannel = InterfaceDefs.createBasicInputInterface("LpsSaTotalsRequest")
LpsSaTotalsRequestInputChannel["channel"]["queueSize"] = 10;
LpsSaTotalsRequestOutputChannel = InterfaceDefs.createBasicOutputInterface("LpsSaTotalsRequest")

LpsSaTotalsResponseInputChannel = InterfaceDefs.createBasicInputInterface("LpsSaTotalsResponse")
LpsSaTotalsResponseInputChannel["channel"]["queueSize"] = 10;
LpsSaTotalsResponseOutputChannel = InterfaceDefs.createBasicOutputInterface("LpsSaTotalsResponse")

LpsSaTotalsUSBSaveProgressInputChannel = InterfaceDefs.createBasicInputInterface("LpsSaTotalsUSBSaveProgress")
LpsSaTotalsUSBSaveProgressInputChannel["channel"]["queueSize"] = 10;
LpsSaTotalsUSBSaveProgressOutputChannel = InterfaceDefs.createBasicOutputInterface("LpsSaTotalsUSBSaveProgress")

# These are the interfaces for reading the printer config
LpsSaTotalsPrinterCnfgInputChannel = InterfaceDefs.deepCopy(InterfaceDefs::ExampleInput)
LpsSaTotalsPrinterCnfgInputChannel["interface"] = "LpsSaTotalsPrinterCnfg.Channel.Input"
LpsSaTotalsPrinterCnfgInputChannel["channel"]["name"] = "LpsSaTotalsPrinterCnfg.Channel"
LpsSaTotalsPrinterCnfgInputChannel["channel"]["queueSize"] = 1

LpsSaTotalsPrinterCnfgOutputChannel = InterfaceDefs.deepCopy(InterfaceDefs::ExampleOutput)
LpsSaTotalsPrinterCnfgOutputChannel["interface"] = "LpsSaTotalsPrinterCnfg.Channel.Output"
LpsSaTotalsPrinterCnfgOutputChannel["channel"]["name"] = "LpsSaTotalsPrinterCnfg.Channel"

# These are the interfaces for writing the printer config
LpsSaTotalsWritePrinterCnfgInputChannel = InterfaceDefs.deepCopy(InterfaceDefs::ExampleInput)
LpsSaTotalsWritePrinterCnfgInputChannel["interface"] = "LpsSaTotalsPrinterCnfg.Channel.Input"
LpsSaTotalsWritePrinterCnfgInputChannel["channel"]["name"] = "LpsSaTotalsWritePrinterCnfg.Channel"
LpsSaTotalsWritePrinterCnfgInputChannel["channel"]["queueSize"] = 1

LpsSaTotalsWritePrinterCnfgOutputChannel = InterfaceDefs.deepCopy(InterfaceDefs::ExampleOutput)
LpsSaTotalsWritePrinterCnfgOutputChannel["interface"] = "LpsSaTotalsPrinterCnfg.Channel.Output"
LpsSaTotalsWritePrinterCnfgOutputChannel["channel"]["name"] = "LpsSaTotalsWritePrinterCnfg.Channel"

# These are the interfaces for reading the display state
LpsSaUIDisplayStateInputChannel = InterfaceDefs.createBasicInputInterface("LpsSaUIDisplayState")
LpsSaUIDisplayStateInputChannel["channel"]["queueSize"] = 1;
LpsSaUIDisplayStateOutputChannel = InterfaceDefs.createBasicOutputInterface("LpsSaUIDisplayState")

# These are the interfaces for writing the display settings
LpsSaUIDisplaySettingsInputChannel = InterfaceDefs.createBasicInputInterface("LpsSaUIDisplaySettings")
LpsSaUIDisplaySettingsInputChannel["channel"]["queueSize"] = 1;
LpsSaUIDisplaySettingsOutputChannel = InterfaceDefs.createBasicOutputInterface("LpsSaUIDisplaySettings")

# These are the interfaces for reading the BEM Simulator state
LpsSaUIBEMSimStateInputChannel = InterfaceDefs.createBasicInputInterface("LpsSaUIBEMSimState")
LpsSaUIBEMSimStateInputChannel["channel"]["queueSize"] = 1;
LpsSaUIBEMSimStateOutputChannel = InterfaceDefs.createBasicOutputInterface("LpsSaUIBEMSimState")

#Weigh App interfaces
LpsSaWeighTxChannelInput = InterfaceDefs.createBasicInputInterface("LpsSaWeighTxChannel")
LpsSaWeighTxChannelInput["channel"]["queueSize"] = 20;
LpsSaWeighTxChannelOutput = InterfaceDefs.createBasicOutputInterface("LpsSaWeighTxChannel")

LpsSaWeighReqstChannelInput = InterfaceDefs.createBasicInputInterface("LpsSaWeighReqstChannel")
LpsSaWeighReqstChannelInput["channel"]["queueSize"] = 20;
LpsSaWeighReqstChannelOutput = InterfaceDefs.createBasicOutputInterface("LpsSaWeighReqstChannel")

LpsSaWeighRespChannelInput = InterfaceDefs.createBasicInputInterface("LpsSaWeighRespChannel")
LpsSaWeighRespChannelInput["channel"]["queueSize"] = 20;
LpsSaWeighRespChannelOutput = InterfaceDefs.createBasicOutputInterface("LpsSaWeighRespChannel")

LpsSaWeighDebugChannelInput = InterfaceDefs.createBasicInputInterface("LpsSaWeighDebugChannel")
LpsSaWeighDebugChannelOutput = InterfaceDefs.createBasicOutputInterface("LpsSaWeighDebugChannel")

LpsSaWeighInitDebugChannelInput = InterfaceDefs.createBasicInputInterface("LpsSaWeighInitDebugChannel")
LpsSaWeighInitDebugChannelOutput = InterfaceDefs.createBasicOutputInterface("LpsSaWeighInitDebugChannel")

LpsSaNvmCalDataChannelInput = InterfaceDefs.createBasicInputInterface("LpsSaNvmCalDataChannel")
LpsSaNvmCalDataChannelInput["channel"]["queueSize"] = 1;
LpsSaNvmCalDataChannelOutput = InterfaceDefs.createBasicOutputInterface("LpsSaNvmCalDataChannel")

LpsSaNvmCalOnTheFlyDataChannelInput = InterfaceDefs.createBasicInputInterface("LpsSaNvmCalOnTheFlyDataChannel")
LpsSaNvmCalOnTheFlyDataChannelInput["channel"]["queueSize"] = 3;
LpsSaNvmCalOnTheFlyDataChannelOutput = InterfaceDefs.createBasicOutputInterface("LpsSaNvmCalOnTheFlyDataChannel")

MachineOutput = InterfaceDefs.createBasicOutputInterface("Machine")
MachineInput = InterfaceDefs.createBasicInputInterface("Machine")

# List Mgr Interfaces
LpsSaListMgrPostInputChannel = InterfaceDefs.deepCopy(InterfaceDefs::ExampleInput)
LpsSaListMgrPostInputChannel["interface"] = "LpsSaListMgrPost.Channel.Input"
LpsSaListMgrPostInputChannel["channel"]["name"] = "LpsSaListMgrPost.Channel"
LpsSaListMgrPostInputChannel["channel"]["queueSize"] = 5

LpsSaListMgrPostOutputChannel = InterfaceDefs.deepCopy(InterfaceDefs::ExampleOutput)
LpsSaListMgrPostOutputChannel["interface"] = "LpsSaListMgrPost.Channel.Output"
LpsSaListMgrPostOutputChannel["channel"]["name"] = "LpsSaListMgrPost.Channel"

LpsSaListMgrNotifyInputChannel = InterfaceDefs.deepCopy(InterfaceDefs::ExampleInput)
LpsSaListMgrNotifyInputChannel["interface"] = "LpsSaListMgrNotify.Channel.Input"
LpsSaListMgrNotifyInputChannel["channel"]["name"] = "LpsSaListMgrNotify.Channel"
LpsSaListMgrNotifyInputChannel["channel"]["queueSize"] = 5

LpsSaListMgrNotifyOutputChannel = InterfaceDefs.deepCopy(InterfaceDefs::ExampleOutput)
LpsSaListMgrNotifyOutputChannel["interface"] = "LpsSaListMgrNotify.Channel.Output"
LpsSaListMgrNotifyOutputChannel["channel"]["name"] = "LpsSaListMgrNotify.Channel"

LpsSaListMgrTxOutputChannel = InterfaceDefs.deepCopy(InterfaceDefs::ExampleOutput)
LpsSaListMgrTxOutputChannel["interface"] = "LpsSaListMgrTx.Channel.Output"
LpsSaListMgrTxOutputChannel["channel"]["name"] = "LpsSaListMgrTx.Channel"

LpsSaListMgrTxInputChannel = InterfaceDefs.deepCopy(InterfaceDefs::ExampleInput)
LpsSaListMgrTxInputChannel["interface"] = "LpsSaListMgrTx.Channel.Input"
LpsSaListMgrTxInputChannel["channel"]["name"] = "LpsSaListMgrTx.Channel"
LpsSaListMgrTxInputChannel["channel"]["queueSize"] = 5

#D6 Display Brightness
AisJhm2TxChannelInput = InterfaceDefs.createBasicInputInterface("AisJhm2TxChannel")
AisJhm2TxChannelInput["channel"]["queueSize"] = 20;
AisJhm2TxChannelOutput = InterfaceDefs.createBasicOutputInterface("AisJhm2TxChannel")

# Work Order Assist Interfaces
WorkOrderAssistSettingsInputChannel = InterfaceDefs.createBasicInputInterface("WorkOrderAssistSettings")
WorkOrderAssistSettingsInputChannel["channel"]["queueSize"] = 1;
WorkOrderAssistSettingsOutputChannel = InterfaceDefs.createBasicOutputInterface("WorkOrderAssistSettings")

WorkOrderAssistSettingsWrInputChannel = InterfaceDefs.createBasicInputInterface("WorkOrderAssistSettings")
WorkOrderAssistSettingsWrInputChannel["channel"]["name"] = "WorkOrderAssistSettingsWr.Channel"
WorkOrderAssistSettingsWrInputChannel["channel"]["queueSize"] = 1;
WorkOrderAssistSettingsWrOutputChannel = InterfaceDefs.createBasicOutputInterface("WorkOrderAssistSettings")
WorkOrderAssistSettingsWrOutputChannel["channel"]["name"] = "WorkOrderAssistSettingsWr.Channel"

WorkOrderAssistTxInputChannel = InterfaceDefs.createBasicInputInterface("WorkOrderAssistTx")
WorkOrderAssistTxInputChannel["channel"]["queueSize"] = 5;
WorkOrderAssistTxOutputChannel = InterfaceDefs.createBasicOutputInterface("WorkOrderAssistTx")

# Autonomy Condition Diagnostics Interfaces
AutonomyConditionDiagnosticsTxInputChannel = InterfaceDefs.createBasicInputInterface("AutonomyConditionDiagnosticsTx")
AutonomyConditionDiagnosticsTxInputChannel["channel"]["queueSize"] = 5;
AutonomyConditionDiagnosticsTxOutputChannel = InterfaceDefs.createBasicOutputInterface("AutonomyConditionDiagnosticsTx")

AutonomyConditionDiagnosticsRequestChannelInput = InterfaceDefs.createBasicInputInterface("AutonomyConditionDiagnosticsRequest") #getcmd from UI
AutonomyConditionDiagnosticsRequestChannelInput["channel"]["queueSize"] = 20;
AutonomyConditionDiagnosticsRequestChannelOutput = InterfaceDefs.createBasicOutputInterface("AutonomyConditionDiagnosticsRequest")#setcmd to ACD

AutonomyConditionDiagnosticsResponseChannelInput = InterfaceDefs.createBasicInputInterface("AutonomyConditionDiagnosticsResponse")#getres from JobMgr
AutonomyConditionDiagnosticsResponseChannelInput["channel"]["queueSize"] = 20;
AutonomyConditionDiagnosticsResponseChannelOutput = InterfaceDefs.createBasicOutputInterface("AutonomyConditionDiagnosticsResponse")#set res to UI App

# Cycle Segmentation Interfaces
CycleSegTxChannelInput = InterfaceDefs.createBasicInputInterface("CycleSegTx")
CycleSegTxChannelInput["channel"]["queueSize"] = 1;
CycleSegTxChannelOutput = InterfaceDefs.createBasicOutputInterface("CycleSegTx")

# Widgets App Interfaces
WidgetsDebugDataInput = InterfaceDefs.createBasicInputInterface("WidgetsDebugData")
WidgetsDebugDataInput["channel"]["queueSize"] = 20;
WidgetsDebugDataOutput = InterfaceDefs.createBasicOutputInterface("WidgetsDebugData")


#TipOff Assits
TipoffModelTestPointsInput = InterfaceDefs.createBasicInputInterface("TipoffModelTestPoints")
TipoffModelTestPointsInput["channel"]["queueSize"] = 20;
TipoffModelTestPointsOutput = InterfaceDefs.createBasicOutputInterface("TipoffModelTestPoints")

end
