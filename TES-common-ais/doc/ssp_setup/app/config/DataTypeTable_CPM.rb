DataTypes["Types"].concat(
    [ 
        #######################
        ### TES Common Channels
    
        ### App Reg
        "AppReg",
 
        ### ACD
        "PartNumbers",
 
        ### Bmi
        "DataLinkData",
    
        ### Calibration
        "CalibrationRequestUI",
        "CalibrationResponseUI",
        "CalMgrCmdReqst",
        "CalMgrCmdResp",
 
        ### Coaching
        "CoachingShowHideStatus",
        "CoachingSummaryData",
        "Coaching3x3Data",
        "BreadcrumbLog",
    
        ### FileTransferBridgeApp
        "CreateFileRequest",
        "FileTransferBridgeIndication",
        "FileTransferBridgeRequest",
        "FileTransferBridgeResponse",
        "IoTHubCommsInboundMessage",
        "IoTHubCommsOutboundMessage",
        "IoTHubCommsOutboundReturn",
    
        ### I/O
        "OutputChannel",
        "PwmInputChannels",
        "SwitchInputScs",
    
        ### SerialPrinterApp
        "SerialPrinterRequest",
    
        ### VP3
        "VP3Record",
    
        #######################
        ### CPM App Channels
    
        # "Machine",
    ])
    
    ###########################
    ### TES Common Log Channels
    
    ### Uncomment the channels to add to ProductionLogger
    
    ### App Reg
    # AppReg = createLogChannel("AppReg")
    # AppReg["monitorSequenceNumber"] = false;
 
    ### ACD
    # PartNumbers = createLogChannel("PartNumbers")
 
    ### Bmi
    # DataLinkData = createLogChannel("DataLinkData")
    # DataLinkData["monitorSequenceNumber"] = false;
    
    ### Calibration
    # CalibrationRequestUI = createLogChannel("CalibrationRequestUI")
    # CalibrationResponseUI = createLogChannel("CalibrationResponseUI")
    # CalMgrCmdReqst = createLogChannel("CalMgrCmdReqst")
    # CalMgrCmdResp = createLogChannel("CalMgrCmdResp")
 
    ### Coaching
    # CoachingShowHideStatus = createLogChannel("CoachingShowHideStatus")
    # CoachingSummaryData = createLogChannel("CoachingSummaryData")
    # Coaching3x3Data = createLogChannel("Coaching3x3Data")
    # BreadcrumbLog = createLogChannel("BreadcrumbLog")
    
    ### FileTransferBridgeApp
    # CreateFileRequest = createLogChannel("CreateFileRequest")
    # FileTransferBridgeIndication = createLogChannel("FileTransferBridgeIndication")
    # FileTransferBridgeRequest = createLogChannel("FileTransferBridgeRequest")
    # FileTransferBridgeResponse = createLogChannel("FileTransferBridgeResponse")
    # IoTHubCommsInboundMessage = createLogChannel("IoTHubCommsInboundMessage")
    # IoTHubCommsOutboundMessage = createLogChannel("IoTHubCommsOutboundMessage")
    # IoTHubCommsOutboundReturn = createLogChannel("IoTHubCommsOutboundReturn")
    
    ### I/O
    # OutputChannel = createLogChannel("OutputChannel")
    # PwmInputChannels = createLogChannel("PwmInputChannels")
    # SwitchInputScs = createLogChannel("SwitchInputScs")
    
    ### SerialPrinterApp
    # SerialPrinterRequest = createLogChannel("SerialPrinterRequest")
    
    # VP3
    # VP3Record = createLogChannel("VP3Record")
    # VP3Record["monitorSequenceNumber"] = false;
    
    ###########################
    ### CPM App Log Channels
    # Machine = createLogChannel("Machine")
