DataTypes["Types"].concat(
[ 
    #######################
    ### TES Common Channels

    # App Reg
    "AppReg",

    # Bmi
    "DataLinkData",

    # Calibration
    "CalibrationRequestUI",
    "CalibrationResponseUI",
    "CalMgrCmdReqst",
    "CalMgrCmdResp",

    # FileTransferBridgeApp
    "CreateFileRequest",
    "FileTransferBridgeRequest",
    "FileTransferBridgeResponse",

    # I/O
    "OutputChannel",
    "PwmInputChannels",
    "SwitchInputScs",

    # SerialPrinterApp
    "SerialPrinterRequest",

    # VP3
    "VP3Record",

    #######################
    ### CPM App Channels

    "LpsSaJobMgrTxChannel",
    "LpsSaJobMgrReqstChannel",
    "LpsSaJobMgrRespChannel",
    "LpsSaJobMgrDebugChannel",
    "LpsSaLoadRecordChannel",
    "LpsSaTotals",
    "LpsSaTotalsRequest",
    "LpsSaTotalsResponse",
    "LpsSaTotalsPrinterCnfg",
    "LpsSaTotalsWritePrinterCnfg",
    "LpsSaUIDisplayState",
    "LpsSaUIDisplaySettings",
    "LpsSaWeighTxChannel",
    "LpsSaWeighReqstChannel",
    "LpsSaWeighRespChannel",
    "LpsSaWeighDebugChannel",
    "LpsSaWeighInitDebugChannel",
    "LpsSaNvmCalDataChannel",
    "LpsSaNvmCalOnTheFlyDataChannel",
    "Machine",
    "LpsSaListMgrPost",
    "LpsSaListMgrNotify",
    "LpsSaListMgrTx",
    "AisJhm2TxChannel",
    "WorkOrderAssistSettings",
    "CycleSegTx",
    "WorkOrderAssistTx",
    "WidgetsDebugData",
    "TipoffModelTestPoints"
])

###########################
### TES Common Log Channels

# App Reg
AppReg = createLogChannel("AppReg")
AppReg["monitorSequenceNumber"] = false;

# Bmi
DataLinkData = createLogChannel("DataLinkData")
DataLinkData["monitorSequenceNumber"] = false;

# Calibration
CalibrationRequestUI = createLogChannel("CalibrationRequestUI")
CalibrationResponseUI = createLogChannel("CalibrationResponseUI")
CalMgrCmdReqst = createLogChannel("CalMgrCmdReqst")
CalMgrCmdResp = createLogChannel("CalMgrCmdResp")

# FileTransferBridgeApp
CreateFileRequest = createLogChannel("CreateFileRequest")
FileTransferBridgeRequest = createLogChannel("FileTransferBridgeRequest")
FileTransferBridgeResponse = createLogChannel("FileTransferBridgeResponse")
FileTransferBridgeIndication = createLogChannel("FileTransferBridgeIndication")

# I/O
OutputChannel = createLogChannel("OutputChannel")
PwmInputChannels = createLogChannel("PwmInputChannels")
SwitchInputScs = createLogChannel("SwitchInputScs")

# SerialPrinterApp
SerialPrinterRequest = createLogChannel("SerialPrinterRequest")

# VP3
VP3Record = createLogChannel("VP3Record")
VP3Record["monitorSequenceNumber"] = false;

###########################
### CPM App Log Channels

LpsSaJobMgrTxChannel = createLogChannel("LpsSaJobMgrTxChannel")
LpsSaJobMgrReqstChannel = createLogChannel("LpsSaJobMgrReqstChannel")
LpsSaJobMgrRespChannel = createLogChannel("LpsSaJobMgrRespChannel")
LpsSaJobMgrDebugChannel = createLogChannel("LpsSaJobMgrDebugChannel")
LpsSaLoadRecordChannel = createLogChannel("LpsSaLoadRecordChannel")
LpsSaTotals = createLogChannel("LpsSaTotals")
LpsSaTotalsRequest = createLogChannel("LpsSaTotalsRequest")
LpsSaTotalsResponse = createLogChannel("LpsSaTotalsResponse")
LpsSaTotalsPrinterCnfg = createLogChannel("LpsSaTotalsPrinterCnfg")
LpsSaTotalsWritePrinterCnfg = createLogChannel("LpsSaTotalsWritePrinterCnfg")
LpsSaUIDisplayState = createLogChannel("LpsSaUIDisplayState")
LpsSaUIDisplaySettings = createLogChannel("LpsSaUIDisplaySettings")
LpsSaWeighTxChannel = createLogChannel("LpsSaWeighTxChannel")
LpsSaWeighReqstChannel = createLogChannel("LpsSaWeighReqstChannel")
LpsSaWeighRespChannel = createLogChannel("LpsSaWeighRespChannel")
LpsSaWeighDebugChannel = createLogChannel("LpsSaWeighDebugChannel")
LpsSaWeighInitDebugChannel = createLogChannel("LpsSaWeighInitDebugChannel")
LpsSaNvmCalDataChannel = createLogChannel("LpsSaNvmCalDataChannel")
LpsSaNvmCalOnTheFlyDataChannel = createLogChannel("LpsSaNvmCalOnTheFlyDataChannel")
Machine = createLogChannel("Machine")
LpsSaListMgrPost = createLogChannel("LpsSaListMgrPost")
LpsSaListMgrNotify = createLogChannel("LpsSaListMgrNotify")
LpsSaListMgrTx = createLogChannel("LpsSaListMgrTx")
AisJhm2TxChannel = createLogChannel("AisJhm2TxChannel")
WorkOrderAssistSettings = createLogChannel("WorkOrderAssistSettings")
CycleSegTx = createLogChannel("CycleSegTx")
WorkOrderAssistTx = createLogChannel("WorkOrderAssistTx")
WidgetsDebugData = createLogChannel("WidgetsDebugData")
TipoffModelTestPoints = createLogChannel("TipoffModelTestPoints")

ShmClock = createLogChannel("ShmClock")
