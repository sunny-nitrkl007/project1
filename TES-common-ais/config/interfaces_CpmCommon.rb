require "interfaces.rb"

module InterfaceDefs_CpmCommon

#PWM Input APP
PwmInputChannelsInput = InterfaceDefs.createBasicInputInterface("PwmInputChannels")
PwmInputChannelsInput["channel"]["queueSize"] = 30; 
PwmInputChannelsOutput = InterfaceDefs.createBasicOutputInterface("PwmInputChannels")

##############################################
# CPM File Transfer Bridge App
##############################################
FileTransferBridgeRequestInput = InterfaceDefs.createBasicInputInterface("FileTransferBridgeRequest")
FileTransferBridgeRequestInput["channel"]["queueSize"] = 20;
FileTransferBridgeRequestOutput = InterfaceDefs.createBasicOutputInterface("FileTransferBridgeRequest")

FileTransferBridgeResponseInput = InterfaceDefs.createBasicInputInterface("FileTransferBridgeResponse")
FileTransferBridgeResponseInput["channel"]["queueSize"] = 20;
FileTransferBridgeResponseOutput = InterfaceDefs.createBasicOutputInterface("FileTransferBridgeResponse")

FileTransferBridgeReadParamResponseInput = InterfaceDefs.createBasicInputInterface("FileTransferBridgeReadParamResponse")
FileTransferBridgeReadParamResponseInput["channel"]["queueSize"] = 20;
FileTransferBridgeReadParamResponseOutput = InterfaceDefs.createBasicOutputInterface("FileTransferBridgeReadParamResponse")

FileTransferBridgeIndicationInput = InterfaceDefs.createBasicInputInterface("FileTransferBridgeIndication")
FileTransferBridgeIndicationInput["channel"]["queueSize"] = 20;
FileTransferBridgeIndicationOutput = InterfaceDefs.createBasicOutputInterface("FileTransferBridgeIndication")

IoTHubCommsInboundMessageInput = InterfaceDefs.createBasicInputInterface("IoTHubCommsInboundMessage")
IoTHubCommsInboundMessageInput["channel"]["queueSize"] = 20;
IoTHubCommsInboundMessageOutput = InterfaceDefs.createBasicOutputInterface("IoTHubCommsInboundMessage")

IoTHubCommsOutboundMessageInput = InterfaceDefs.createBasicInputInterface("IoTHubCommsOutboundMessage")
IoTHubCommsOutboundMessageInput["channel"]["queueSize"] = 20;
IoTHubCommsOutboundMessageOutput = InterfaceDefs.createBasicOutputInterface("IoTHubCommsOutboundMessage")

IoTHubCommsOutboundReturnInput = InterfaceDefs.createBasicInputInterface("IoTHubCommsOutboundReturn")
IoTHubCommsOutboundReturnInput["channel"]["queueSize"] = 20;
IoTHubCommsOutboundReturnOutput = InterfaceDefs.createBasicOutputInterface("IoTHubCommsOutboundReturn")

##############################################
# App to App Reg
##############################################
AppRegInput = InterfaceDefs.createBasicInputInterface("AppReg")
AppRegInput["channel"]["queueSize"] = 20;
AppRegOutput = InterfaceDefs.createBasicOutputInterface("AppReg")

#VP3 File Creation  APP
VP3RecordInput = InterfaceDefs.createBasicInputInterface("VP3Record")
VP3RecordInput["channel"]["queueSize"] = 100; # How many records per store maximum?
VP3RecordOutput = InterfaceDefs.createBasicOutputInterface("VP3Record")

#Create File Request  APP
CreateFileRequestInput = InterfaceDefs.createBasicInputInterface("CreateFileRequest")
CreateFileRequestInput["channel"]["queueSize"] = 10; 
CreateFileRequestOutput = InterfaceDefs.createBasicOutputInterface("CreateFileRequest")

# OutputApp Creation 
OutputChannelInput = InterfaceDefs.createBasicInputInterface("OutputChannel")
OutputChannelInput["channel"]["queueSize"] = 20;
OutputChannelOutput = InterfaceDefs.createBasicOutputInterface("OutputChannel")

#Switch Input Scs interfaces
SwitchInputScsInput = InterfaceDefs.createBasicInputInterface("SwitchInputScs") 
SwitchInputScsOutput = InterfaceDefs.createBasicOutputInterface("SwitchInputScs")

# Part Numbers and Product ID
PartNumbersOutput = InterfaceDefs.createBasicOutputInterface("PartNumbers")
PartNumbersInput = InterfaceDefs.createBasicInputInterface("PartNumbers")


##################################################################################
# CDL DataLinkData Interface
##################################################################################
DataLinkDataInput = InterfaceDefs.createBasicInputInterface("DataLinkData")
DataLinkDataInput["channel"]["queueSize"] = 30;
DataLinkDataOutput = InterfaceDefs.createBasicOutputInterface("DataLinkData")

################################################################################
# Serial Printer Interface
################################################################################
SerialPrinterRequestInputChannel = InterfaceDefs.createBasicInputInterface("SerialPrinterRequest")
SerialPrinterRequestInputChannel["channel"]["queueSize"] = 2;
SerialPrinterRequestOutputChannel = InterfaceDefs.createBasicOutputInterface("SerialPrinterRequest")

################################################################################
# Calibrations  ACD to Weigh-App  (CalMgr)
################################################################################
CalMgrCmdReqstInput = InterfaceDefs.createBasicInputInterface("CalMgrCmdReqst")
CalMgrCmdReqstInput["channel"]["queueSize"] = 5;
CalMgrCmdReqstOutput = InterfaceDefs.createBasicOutputInterface("CalMgrCmdReqst")

CalMgrCmdRespInput = InterfaceDefs.createBasicInputInterface("CalMgrCmdResp")
CalMgrCmdRespInput["channel"]["queueSize"] = 5;
CalMgrCmdRespOutput = InterfaceDefs.createBasicOutputInterface("CalMgrCmdResp")

################################################################################
# UI Calibrations
################################################################################
CalibrationRequestUIInput = InterfaceDefs.createBasicInputInterface("CalibrationRequestUI")
CalibrationRequestUIInput["channel"]["queueSize"] = 5;
CalibrationRequestUIOutput = InterfaceDefs.createBasicOutputInterface("CalibrationRequestUI")

CalibrationResponseUIInput = InterfaceDefs.createBasicInputInterface("CalibrationResponseUI")
CalibrationResponseUIInput["channel"]["queueSize"] = 5;
CalibrationResponseUIOutput = InterfaceDefs.createBasicOutputInterface("CalibrationResponseUI")

################################################################################
# Coaching
################################################################################
CoachingShowHideStatusInput = InterfaceDefs.createBasicInputInterface("CoachingShowHideStatus")
CoachingShowHideStatusOutput = InterfaceDefs.createBasicOutputInterface("CoachingShowHideStatus")

CoachingSummaryDataInput = InterfaceDefs.createBasicInputInterface("CoachingSummaryData")
CoachingSummaryDataInput["channel"]["queueSize"] = 5;
CoachingSummaryDataOutput = InterfaceDefs.createBasicOutputInterface("CoachingSummaryData")

Coaching3x3DataInput = InterfaceDefs.createBasicInputInterface("Coaching3x3Data")
Coaching3x3DataInput["channel"]["queueSize"] = 5;
Coaching3x3DataOutput = InterfaceDefs.createBasicOutputInterface("Coaching3x3Data")

CoachingTipHistoryInput = InterfaceDefs.createBasicInputInterface("CoachingTipHistory")
CoachingTipHistoryOutput = InterfaceDefs.createBasicOutputInterface("CoachingTipHistory")

BreadcrumbLogInput = InterfaceDefs.createBasicInputInterface("BreadcrumbLog")
BreadcrumbLogOutput = InterfaceDefs.createBasicOutputInterface("BreadcrumbLog")

end
