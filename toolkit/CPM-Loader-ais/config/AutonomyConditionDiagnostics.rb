require "commonAutonomyTask.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"
load "TaskPlugin_DataLinkDataReceiver.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
    "AutonomyConditionMessageInput" => InterfaceDefs::AutonomyConditionMessageInput,
    "AutonomyConditionDiagnosticsTxOutput" => InterfaceDefs_Loaders::AutonomyConditionDiagnosticsTxOutputChannel,
    "DiagnosticStatusOutput" => InterfaceDefs::DiagnosticStatusOutput,
    "SystemHardwareHealthInput" => InterfaceDefs::SystemHardwareHealthInput,
    "AisJhm2TxChannelInput" => InterfaceDefs_Loaders::AisJhm2TxChannelInput,
    "LpsSaWeighReqstChannelOutput" => InterfaceDefs_Loaders::LpsSaWeighReqstChannelOutput,##setCmd to weighing App
    "LpsSaWeighRespChannelInput" => InterfaceDefs_Loaders::LpsSaWeighRespChannelInput,##getRes from weighing App
    "LpsSaWeighTxChannelInput" => InterfaceDefs_Loaders::LpsSaWeighTxChannelInput,##get parameters from weighing app
    "CalMgrCmdReqstOutput" => InterfaceDefs_CpmCommon::CalMgrCmdReqstOutput,
    "CalMgrCmdRespInput" => InterfaceDefs_CpmCommon::CalMgrCmdRespInput,
    "LpsSaJobMgrReqstChannelOutput" => InterfaceDefs_Loaders::LpsSaJobMgrReqstChannelOutput,##setCmd to JobMgr App
    "LpsSaJobMgrRespChannelInput" => InterfaceDefs_Loaders::LpsSaJobMgrRespChannelInput,##getRes from JobMgr App
    "LpsSaJobMgrTxChannelInput" => InterfaceDefs_Loaders::LpsSaJobMgrTxChannelInput,##get parameters from JobMgr app
    "CycleSegTxInterfaceInputChannel" => InterfaceDefs_Loaders::CycleSegTxChannelInput, ##get parameters from cycleseg app
    "AutonomyConditionDiagnosticsRequestChannelInput"  => InterfaceDefs_Loaders::AutonomyConditionDiagnosticsRequestChannelInput,##receive cmd from UI
    "AutonomyConditionDiagnosticsResponseChannelOutput"  => InterfaceDefs_Loaders::AutonomyConditionDiagnosticsResponseChannelOutput, #send response to UI
    "SwitchInputScsInput" => InterfaceDefs_CpmCommon::SwitchInputScsInput,##get parameters from SwitchInput app
    "PartNumbersOutput" => InterfaceDefs_CpmCommon::PartNumbersOutput,
    "ShmClockOutput" => InterfaceDefs::ShmClockOutput,	
    "SEAStatusOutput" => InterfaceDefs::SEAStatusOutput,
    "TotalsInput" => InterfaceDefs_Loaders::LpsSaTotalsInputChannel,
    "TotalsRequestOutput" => InterfaceDefs_Loaders::LpsSaTotalsRequestOutputChannel,
    "DisplayStateInput" => InterfaceDefs_Loaders::LpsSaUIDisplayStateInputChannel,
    "DisplaySettingsOutput" => InterfaceDefs_Loaders::LpsSaUIDisplaySettingsOutputChannel,
    "PrinterCnfgInput" => InterfaceDefs_Loaders::LpsSaTotalsPrinterCnfgInputChannel,
    "PrinterCnfgOutput" => InterfaceDefs_Loaders::LpsSaTotalsWritePrinterCnfgOutputChannel,
    "CalibrationRequestUIInput" => InterfaceDefs_CpmCommon::CalibrationRequestUIInput,
    "CalibrationResponseUIOutput" => InterfaceDefs_CpmCommon::CalibrationResponseUIOutput,
    "DataLinkDataInput" => InterfaceDefs_CpmCommon::DataLinkDataInput, # This is the old one used for pre-plugin aware code.
    "DataLinkDataReceiverInput" => InterfaceDefs_CpmCommon::DataLinkDataInput, # This is the new one used by the DataLinkDataReceiver plugin.
    "DispatchSettingsInput" => InterfaceDefs_Loaders::WorkOrderAssistSettingsInputChannel,
    "DispatchSettingsWrOutput" => InterfaceDefs_Loaders::WorkOrderAssistSettingsWrOutputChannel,
    "BEMSimStateInput" => InterfaceDefs_Loaders::LpsSaUIBEMSimStateInputChannel,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
   "requireGPSTimeSynchronizationOnStart" => false, # ALLOW this process to start without synchronization
   "loggerThreshold" => "error",
   "cycleRate_hz" => 10,
   "EnableDiagnosticOutputFileWriter" => false,
   "DiagnosticOutputFile" => "/log/DiagnosticOutputFile.diag",
   "tempRoot" => "/tmp/appdata/CPM/AutonomyConditionDiagnostics", # JhmDataServer uses this location to read files from, if this changes, JhmDataServer will need changes
   "hostnameWhiteList" => ["auto1","auto4","A6N2"], # "auto2", "auto3", "auto4", "auto5"], # Listen to autonomy conditions from any of these hosts
   "storageRoot" => "/opt/appdata/CPM/ACD/nvm",

  # CAN port assigned to primary and secondary GPS receivers
  # Valid values:
  #     0 - can0 or CAN1 or CAN A
  #     1 - can1 or CAN2 or CAN B
  #
  "EDDT_CAN_port" => 0,

  # J1939 SID of Master ECM
  "ID_Master" => 0x1C,

  # J1939 MID for D6 Display, to set brightness PID
  "MID_D6_Display" => 0x54,

} )

ECM_SUMMARY = {
#   ECM Name   		 Filename  				IP Address(optional)                               
#  ---------- 		 --------      			 	-----------------
  "Analysis Module"  => ["AnalysisModuleECMSummary.json",	""],
}

# Plugins
DataLinkDataDiagnostics = {
  "enabled" => true,

  "engCid" => 590,
  "analysisCid" => 1089,
  "displayCid" => 2448,
  "transCid" => 296,
  "implCid" => 596,
  
  "engSid" => 0x00,
  "analysisSid" => 0x25,
  "displaySid" => 0x28,
  "transSid" => 0x03,
  "implSid" => 0x2E,
}

EthernetPortStatistics = {
  "cycleRate_hz" => 2,

  # bdt_init 
  "numRxCon" => 4,
  "rxBufSize" => 240,  
  "numTxCon" => 4,
  "txBufSize" => 240,
  "numDataLinkCon" => 3,

  #bdt_action_init
  "maxSimultaneousClients" => 3,
}

# NOTE: Key for a given block must not change when adding/removing blocks. Changing
#	the Key will result in reading/writing a wrong nvm block since we are using
#	the Key to reference the blocks.
NVM = { 
#   Key   BlockID         BlockSize  BlockIntegrity  File1                               
#  -----  ----------      ---------  --------------  -----------
   "00"=> ["0x00010000",  "1560",    "0",            "A6N2_Diagnostics_Events_Log.txt", ],
   "01"=> ["0x00000010",  "532",     "0",            "A6N2_Service_Clock_Primary.txt",  ],
   "02"=> ["0x00000011",  "532",     "0",            "A6N2_Service_Clock_Secondary.txt",],
   "03"=> ["0x00010001",  "25",      "0",            "A6N2_RTC_Time_Zone_Old.txt",      ],
   "04"=> ["0x00010003",  "25",      "0",            "A6N2_RTC_Time_Zone_New.txt",      ],   
   "05"=> ["0x00010002",  "13",      "0",            "A6N2_RTC_Secure.txt",             ],
   "06"=> ["0x0001000a",  "8",       "0",            "A6N2_ProductID.txt",              ],
   "07"=> ["0x00010020",  "8",       "0",            "A6N2_SEA1.txt",                   ],
   "08"=> ["0x00010021",  "8",       "0",            "A6N2_SEA2.txt",                   ],
   "09"=> ["0x00010022",  "8",       "0",            "A6N2_SEA3.txt",                   ],
   "10"=> ["0x00010023",  "1560",    "0",            "A6N2_J39_Health_BDT_CAN_A.txt",   ],
   "11"=> ["0x00010024",  "1560",    "0",            "A6N2_J39_Health_BDT_CAN_B.txt",   ],
   "12"=> ["0x00010025",  "17",      "0",            "A6N2_EquipmentID.txt",            ],
}

# NOTE: Key for the SEA must match the Key for the NVM block (above)
SEA = { 
#   Key   ReasonCode  PermInstallPID  PermEnablePID  SecurityLvl  EncByte  EncBit  TempCounter  TempInstallPID  TempCounterPID  
#  -----  ----------  --------------  -------------  -----------  -------  ------  ----------   --------------  --------------
   "07"=> ["149",      "0xD10DA0",      "0xD10EE7",   "1",         "1",     "1",    "0",         "0xD10EE6",     "0x000000", ],
   "08"=> ["245",      "0xD11884",      "0x000000",   "1",         "1",     "2",    "250",       "0xD11887",     "0xD02654", ],
   "09"=> ["312",      "0xD11E8D",      "0xD11E8E",   "2",         "1",     "3",    "0",         "0xD11E8F",     "0xD02FD7", ],
   #"01"=> ["150",      "0xD10DA1",      "0xD114C4",   "0",         "1",     "2",    "0",         "0x000000",     "0x000000", ],
   #"02"=> ["151",      "0xD10DA2",      "0xD114C5",   "2",         "1",     "3",    "1",         "0xD10EE7",     "0xD01A49", ],
   #"03"=> ["152",      "0xD10DA3",      "0xD114C6",   "0",         "1",     "4",    "0",         "0x000000",     "0x000000", ],
   #"04"=> ["153",      "0xD10DA4",      "0xD114C7",   "2",         "1",     "5",    "1",         "0xD10EE8",     "0xD01A4A", ],
   #"05"=> ["154",      "0xD10DA5",      "0xD114C8",   "0",         "1",     "6",    "0",         "0x000000",     "0x000000", ],
   #"06"=> ["155",      "0xD10DA6",      "0xD114C9",   "0",         "1",     "7",    "0",         "0x000000",     "0x000000", ],
   #"07"=> ["156",      "0xD10DA7",      "0xD114CA",   "2",         "1",     "8",    "1",         "0xD10EE9",     "0xD01A4B", ],
   #"08"=> ["157",      "0xD10DA8",      "0xD114CB",   "0",         "2",     "1",    "0",         "0x000000",     "0x000000", ],
   #"09"=> ["158",      "0xD10DA9",      "0xD114CC",   "2",         "2",     "2",    "1",         "0xD10EEA",     "0xD01A4C", ],
   #"10"=> ["159",      "0xD10DB0",      "0xD114CD",   "0",         "2",     "3",    "0",         "0x000000",     "0x000000", ],
}

# ECM J1939 Name
Ecm_J1939_Name = {
  "Industry_Group"          => 3,
  "Vehicle_System"          => 0,
  "Vehicle_System_Instance" => 0,
  "Function"                => 145,
  "Function_Instance"       => 2,
  "ECU_Instance"            => 0,
  "Manufacturer_Code"       => 8,
  "Identity_Number"         => 0x230813,
  "Preferred_Address"       => 0xEC,
}

#These are the valid inhibit types
STARTUPINHIBIT = 0;
AUTONOMYCONDITION_INHIBIT = 1;

InhibitConditionConfig =
{
  "ConfiguredInhibits" => [
                           "StartupInhibit",
                           "StartupInhibit1",
                           "StartupInhibit2",
                           "StartupInhibit3",
                           "StartupInhibit4",
                           "StartupInhibit5",
                           "StartupInhibit6",
                           "NavigationResetInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"
                          ],
}

StartupInhibit = 
{
  "InhibitType" => STARTUPINHIBIT,
  "StartupInhibitTime_sec" => 90.0,
}

StartupInhibit1 = 
{
  "InhibitType" => STARTUPINHIBIT,
  "StartupInhibitTime_sec" => 10.0,
}

StartupInhibit2 = 
{
  "InhibitType" => STARTUPINHIBIT,
  "StartupInhibitTime_sec" => 225.0,
}

StartupInhibit3 = 
{
  "InhibitType" => STARTUPINHIBIT,
  "StartupInhibitTime_sec" => 240.0,
}

StartupInhibit4 = 
{
  "InhibitType" => STARTUPINHIBIT,
  "StartupInhibitTime_sec" => 280.0,
}

StartupInhibit5 = 
{
  "InhibitType" => STARTUPINHIBIT,
  "StartupInhibitTime_sec" => 290.0,
}

StartupInhibit6 = 
{
  "InhibitType" => STARTUPINHIBIT,
  "StartupInhibitTime_sec" => 295.0,
}

TimeSyncCommsLostDiagnostics=["TimeSync1CommsLostDiagnostic",
                              "TimeSync2CommsLostDiagnostic",
                              "TimeSync3CommsLostDiagnostic",
                              "TimeSync4CommsLostDiagnostic",
                              "TimeSync5CommsLostDiagnostic",]



NavigationResetInhibit =
{
  "InhibitType" => AUTONOMYCONDITION_INHIBIT,
  "AutonomyConditions" => ["ApplanixNavigationResetInProgress"],
}

MachinePowerInhibit =
{
  "InhibitType" => AUTONOMYCONDITION_INHIBIT,
  "AutonomyConditions" => ["MachinePowerOff"],
}

MachineSleepInhibit =
{
  "InhibitType" => AUTONOMYCONDITION_INHIBIT,
  "AutonomyConditions" => ["MachineSleep"],
}

# Startup In Progress event configuration (181- Limited Mobility Mode)
StartupInProgress = 
{
  "AutonomyConditions" => [],   #This Event is triggered internally from the ACD module based on startup inihibit being active, so no autonomy condition is needed
  "InhibitConditions"  => [],   #or'ed list of inhibit Condition for this event
}

# Task Stalled event configuration (10013)
TaskStalledEvent = 
{
  "AutonomyConditions" => ["TaskStalled"],                  #AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => [],               # or'ed list of inhibit Condition for this event
}

# Task Crashed event configuration (also PCM Watchdog: 10012)
TaskCrashedEvent =
{
  "AutonomyConditions" => ["TaskCrashed"], 									# AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => [],    # or'ed list of inhibit Condition for this event
}

#Product ID not received (967-9)

ProdIDNotRecdDiagnostic =
{
  "AutonomyConditions" => ["ProductIDNotReceived"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit"],    # or'ed list of inhibit Condition for this event
}

#Robot File Missing (967-2)

RobotFileMissingDiagnostic =
{
  "AutonomyConditions" => ["RobotFileMissing"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit"],    # or'ed list of inhibit Condition for this event
}


Battery_Low_Event = 
{
  "AutonomyConditions" => ["BatteryLow"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit"],
}

Battery_High_Event = 
{
  "AutonomyConditions" => ["BatteryHigh"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit"],
}


#CPM is triggering lift pressures and lift/tilt position diagnostics when implement is being flashed. Power for the sensors is coming from the implement, implement sends out DM13 messages and CPM should inhibit the diagnostics during flashing. 
TiltLinkVoltageAboveDiagnostic =
{
  "AutonomyConditions" => ["TiltLinkVoltageAbove"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",   
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event                            
}

TiltLinkVoltageBelowDiagnostic =
{
  "AutonomyConditions" => ["TiltLinkVoltageBelow"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event                           
}

TiltLinkFreqAbnormalDiagnostic =
{
  "AutonomyConditions" => ["TiltLinkFreqAbnormal"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event                           
}

TiltLinkCalibrationOutDiagnostic =
{
  "AutonomyConditions" => ["TiltLinkCalibrationOut"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => [],    # or'ed list of inhibit Condition for this event
}


#CPM is triggering lift pressures and lift/tilt position diagnostics when implement is being flashed. Power for the sensors is coming from the implement, implement sends out DM13 messages and CPM should inhibit the diagnostics during flashing. 
LiftLinkVoltageAboveDiagnostic =
{
  "AutonomyConditions" => ["LiftLinkVoltageAbove"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event                           
}

LiftLinkVoltageBelowDiagnostic =
{
  "AutonomyConditions" => ["LiftLinkVoltageBelow"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event                           
}

LiftLinkFreqAbnormalDiagnostic =
{
  "AutonomyConditions" => ["LiftLinkFreqAbnormal"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event                           
}

LiftLinkCalibrationOutDiagnostic =
{
  "AutonomyConditions" => ["LiftLinkCalibrationOut"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => [],    # or'ed list of inhibit Condition for this event
}

#CPM is triggering lift pressures and lift/tilt position diagnostics when implement is being flashed. Power for the sensors is coming from the implement, implement sends out DM13 messages and CPM should inhibit the diagnostics during flashing. 
LiftREVoltageAboveDiagnostic =
{
  "AutonomyConditions" => ["LiftREVoltageAbove"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event                           
}

LiftREVoltageBelowDiagnostic =
{
  "AutonomyConditions" => ["LiftREVoltageBelow"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event                           
}

LiftREFreqAbnormalDiagnostic =
{
  "AutonomyConditions" => ["LiftREFreqAbnormal"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event                           
}

#CPM is triggering lift pressures and lift/tilt position diagnostics when implement is being flashed. Power for the sensors is coming from the implement, implement sends out DM13 messages and CPM should inhibit the diagnostics during flashing. 
LiftHEVoltageAboveDiagnostic =
{
  "AutonomyConditions" => ["LiftHEVoltageAbove"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event                           
}

LiftHEVoltageBelowDiagnostic =
{
  "AutonomyConditions" => ["LiftHEVoltageBelow"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event                           
}

LiftHEFreqAbnormalDiagnostic =
{
  "AutonomyConditions" => ["LiftHEFreqAbnormal"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event                           
}

MachineModelNotSetOutDiagnostic =
{
  "AutonomyConditions" => ["MachineModelNotSetOut"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => [],    # or'ed list of inhibit Condition for this event
}

PayloadMonCalibrationOutDiagnostic =
{
  "AutonomyConditions" => ["PayloadMonCalibrationOut"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => [],    # or'ed list of inhibit Condition for this event
}

PayLdOverLdLimitExceededEvent =
{
  "AutonomyConditions" => ["PayLdOverLdLimitExceeded"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => [],    # or'ed list of inhibit Condition for this event
}

BEMSimDerateEvent =
{
  "AutonomyConditions" => ["BEMSimDerate"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => [],    # or'ed list of inhibit Condition for this event
}

BEMSimLevelWarningEvent =
{
  "AutonomyConditions" => ["BEMSimLevelWarning"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => [],    # or'ed list of inhibit Condition for this event
}

PayloadMemoryLowEvent =
{
  "AutonomyConditions" => ["PayloadMemoryLow"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => [],    # or'ed list of inhibit Condition for this event
}

PayloadMemoryFullEvent =
{
  "AutonomyConditions" => ["PayloadMemoryFull"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => [],    # or'ed list of inhibit Condition for this event
}

PayloadLegalForTradeNotSealedEvent =
{
  "AutonomyConditions" => ["PayloadLegalForTradeNotSealed"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => [],    # or'ed list of inhibit Condition for this event
}

TiltREVoltageAboveDiagnostic =
{
  "AutonomyConditions" => ["TiltREVoltageAbove"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit"],    # or'ed list of inhibit Condition for this event
}

TiltREVoltageBelowDiagnostic =
{
  "AutonomyConditions" => ["TiltREVoltageBelow"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit"],    # or'ed list of inhibit Condition for this event
}

TiltREFreqAbnormalDiagnostic =
{
  "AutonomyConditions" => ["TiltREFreqAbnormal"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit"],    # or'ed list of inhibit Condition for this event
}

TiltHEVoltageAboveDiagnostic =
{
  "AutonomyConditions" => ["TiltHEVoltageAbove"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit"],    # or'ed list of inhibit Condition for this event
}

TiltHEVoltageBelowDiagnostic =
{
  "AutonomyConditions" => ["TiltHEVoltageBelow"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit"],    # or'ed list of inhibit Condition for this event
}

TiltHEFreqAbnormalDiagnostic =
{
  "AutonomyConditions" => ["TiltHEFreqAbnormal"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit"],    # or'ed list of inhibit Condition for this event
}

DL_ETHERNET_1_CID_3900_FMI_9_Diagnostic = 
{
  "AutonomyConditions" => ["DL_ETHERNET_1_CID_3900_FMI_9"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event
}

DL_ETHERNET_1_CID_3900_FMI_14_Diagnostic = 
{
  "AutonomyConditions" => ["DL_ETHERNET_1_CID_3900_FMI_14"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event
}

DL_J1939_1_CID_247_FMI_9_Diagnostic = 
{
  "AutonomyConditions" => ["DL_J1939_1_CID_247_FMI_9"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event
}

DL_J1939_3_CID_5856_FMI_9_Diagnostic = 
{
  "AutonomyConditions" => ["DL_J1939_3_CID_5856_FMI_9"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event
                           
}

DL_J1939_2_CID_2348_FMI_9_Diagnostic = 
{
  "AutonomyConditions" => ["DL_J1939_2_CID_2348_FMI_9"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event
                           
}

DL_CDL_CID_248_FMI_9_Diagnostic = 
{
  "AutonomyConditions" => ["DL_CDL_CID_248_FMI_9"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event
}

DL_J1939_1_CID_247_FMI_14_Diagnostic = 
{
  "AutonomyConditions" => ["DL_J1939_1_CID_247_FMI_14"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event
                           
}

DL_J1939_3_CID_5856_FMI_14_Diagnostic = 
{
  "AutonomyConditions" => ["DL_J1939_3_CID_5856_FMI_14"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event
}

DL_J1939_2_CID_2348_FMI_14_Diagnostic = 
{
  "AutonomyConditions" => ["DL_J1939_2_CID_2348_FMI_14"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event
}

DL_CDL_CID_248_FMI_14_Diagnostic = 
{
  "AutonomyConditions" => ["DL_CDL_CID_248_FMI_14"],    # AutonomyCondition(s) from AutonomyConditionType that trigger this event
  "InhibitConditions"  => ["StartupInhibit",
                           "MachinePowerInhibit",
                           "MachineSleepInhibit"],    # or'ed list of inhibit Condition for this event
                           
}

Execution = {
  "executableName" => "autonomyConditionDiagnostics",
}

# If there's AutoGenDiagnostics.rb, load it
if(FileTest.exists?(ENV["CAT_CONFIG_DIR"].to_s + "/AutoGenDiagnostics.rb"))
    puts "-----CONFIG: Updating AutonomyConditionDiagnostics.rb with AutoGenDiagnostics.rb"
    load "AutoGenDiagnostics.rb"
end

# If there's an auxiliary file, load it
if(FileTest.exists?(ENV["CAT_CONFIG_DIR"].to_s + "/AutonomyConditionDiagnostics_aux.rb"))
    puts "-----CONFIG: Updating AutonomyConditionDiagnostics.rb with mods from AutonomyConditionDiagnostics_aux.rb"
    load "AutonomyConditionDiagnostics_aux.rb"
end
