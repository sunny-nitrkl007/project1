require "Acd2Task_AutonomyConditionServer_Base.rb"

# TaskPlugin configuration
AutonomyConditionServer.update({
  "enabled" => true,
  
  # Set to True to enable EDDT server on J1939 for supported ECMs. Defaults to true
  "j1939ServerEnabled" => true,
  
  # Set to True to enable EDDT server on CDL for supported ECMs. J1939 is supported by default.
  "cdlServerEnabled" => false,

  # (Optional) Size of the diagnostic ready list in NVM.
  # Set to <= 0 for max size (all diagnostics/events are stored)
  # Defaults to 20 if not set
  # "persistentReadyListSize" => -1,

  # (Optional) Size of the diagnostic fault list in NVM.
  # Set to <= 0 for max size (all diagnostics/events are stored)
  # Defaults to 20 if not set
  # "persistentFaultListSize" => -1,

  # (Optional) Size of event queue
  # Defaults to 20 if not set
  # "evtQueSize" => 20,

  # (Optional) Set to True to enable DM1 support. Defaults to false
  # "dm1Enabled" => false,

  # (Optional) The maximum number of DTCs which will be included in a J1939-73 DM fault. 
  # If this is set to 0 (default), the number of DTCs will not be limited.
  # "dmDtcMax" => 0,

  # (Optional) Set to True to publish Occurrence Info in DiagnosticStatus
  # "publishOccurrenceInfo" => false,
})

### Inhibit Conditions ###

# Which Inhibit Conditions to enable for this application
InhibitConditionConfig =
{
  # Which inhibits to use
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
                           "MachineSleepInhibit",
                           "EthernetSleepModeInhibit",
                          #  "AppSpecificInhibit",
                          ],
}

# Application specific Inhibit Conditions
InhibitConditions.update({
  # InhibitType - Must be either STARTUPINHIBIT or AUTONOMYCONDITION_INHIBIT
  # StartupInhibitTime_sec - For StartupInhibits, the amount of time after key-on that the inhibit is active
  # AutonomyConditions - AutonomyCondition(s) from AutonomyConditionType that trigger this inhibit. Must exactly match the name of the published AutonomyCondition
  "AppSpecificInhibit" =>
  {
    "InhibitType" => AUTONOMYCONDITION_INHIBIT,
    "AutonomyConditions" => ["AppSpecific"],
  },
})

# Run time configurable AutonomyConditions
# Key name is the conditionType
# Defaults:
#  conditionMessage => Key name
#  activationDebounce_ms => 0
#  deactivationDebounce_ms => 0
#  timeToLive_ms => 86400000   (24 hours)
AutonomyConditions.update({
  "AppSpecific" => {
    "conditionMessage" => "AppSpecific Autononmy Condition",
    # "qualifiedString" => "{0} and {1} detected {2} has stalled",
    # "activationDebounce_ms" => 0,
    # "deactivationDebounce_ms" => 0,
    # "timeToLive_ms" => 86400000,
  },

  # Autonomy Conditions for CDL diagnostics
  # "Imp_CID_596_FMI_9" => {},
  # "Imp_CID_596_FMI_14" => {},
})

# If multiple ACD2/AutonomyConditionServers are running on the same ECM, dissable MachineSleep on all but 1
# AutonomyConditions.delete("MachineSleep")

### Diagnostics and Events ###
# Which Diagnostics and Events to enable for this application
DiagnosticsAndEventsConfig = {
  "ConfiguredDiagnosticsAndEvents" => [
                           "ProductIDNotReceivedDiagnostic",
                           "RobotFileMissingDiagnostic",
                           "SoftwareVerMismatchDiagnostic",
                           "BatteryLowEvent",
                           "BatteryHighEvent",
                           "J1939_Data_Link_FMI_9_Diagnostic",
                           "J1939_Data_Link_FMI_14_Diagnostic",
                          #  "J1939_Data_Link2_FMI_9_Diagnostic",
                          #  "J1939_Data_Link2_FMI_14_Diagnostic",
                          #  "J1939_Data_Link3_FMI_9_Diagnostic",
                          #  "J1939_Data_Link3_FMI_14_Diagnostic",
                          #  "J1939_Data_Link4_FMI_9_Diagnostic",
                          #  "J1939_Data_Link4_FMI_14_Diagnostic",
                           "Ethernet_Data_Link_FMI_9_Diagnostic",
                           "Ethernet_Data_Link_FMI_14_Diagnostic",
                          #  "ActualEngineRPMOverload_Event",
                          #  "MachineControlModuleCommsLost_Diagnostic",
                          #  "MachineControlModuleParamMissing_Diagnostic",
                          # "Imp_CID_596_FMI_9_Diagnostic",
                          # "Imp_CID_596_FMI_14_Diagnostic",
                          "SyncClockManualAdjustmentRequiredEvent",
                          ],
  "DevelopmentOnlyDiagnosticsAndEvents" => [
                           "TaskStalledEvent",
                           "TaskCrashedEvent",
                           ],
}

# Application specific Diagnostics and Events
DiagnosticsAndEvents.update({
  # AutonomyConditions - AutonomyCondition(s) from AutonomyConditionType that trigger this event. Must exactly match the name of the published AutonomyCondition
  # InhibitConditions - (Optional) OR'd list of inhibit Condition for this diagnostic/event. Must exactly match the name of the InhibitCondition(s)
  # Description - (Optional) Text displayed in ET/Service Tool if the CID/EID is not recognized. Max 20 characters, will be truncated if too long
  # CID - The CDL Component Identifier (CID), must be included for Diagnostics ONLY. 16 bits
  # EID - The CDL Event Identifier (EID), must be included for Events ONLY. 16 bits
  # FMI - (Optional) The CDL Failure Mode Identifier (FMI). Value: 0-15 (defaults to 0)
  # WCI - The CDL Warning Category Indicator (WCI), mandatory unless ACI is provided . Value: 0-3
  # ConfigFlags - Persistency configuration. Defaults to EventSystem::ConfigFlags::CONFIG_ACTIVE_LOGGED_INIT
  # ACI - (Optional) Annunciation Category Indicator (ACI) or Annunciation Level. Used to determine WCI if it is not provied. Value EventSystem::ACI
  # PID - (Optional) The associated CDL PID,
  # CDA_UID - (Optional) The associated CDA param ID which will be published to raise or clear the fault to CDA server. (mandatory for EventSystem::Protocol::CDA)
  # ETN_UID - (Optional) The associated ETN global unique identifier / trigger-id. (mandatory for EventSystem::Protocol::ETN)
  # Protocol - (Optional) EventSystem::Protocol::EDDT (default), EventSystem::Protocol::CDA and/or EventSystem::Protocol::ETN
  # WorstCaseDirection - Used for Additional Information 7 (AI7), optional. Value EventSystem::WorstCaseDirection
  # Debounce_I2A_sec - (Optional) Inactive-to-Active debounce time in seconds, the amount of time the condition must be active before the diagnostic/event is set
  # Debounce_A2I_sec - (Optional) Active-to-Inactive debounce time in seconds, the amount of time the condition must be inactive before the diagnostic/event is cleared
  # InstanceName - (Optional) Name of the instance of the AutonomyConditions
  # LatchUntilNewAssignment - (Optional) Latch the diagnostic until a new assignment number is received. Defaults to false.
  # WriteToLogfile - (Optional) Whether or not the diagnostic/event is logged to the Diagnostic Output File. Defaults to false.
  #
  # NOTE: For internal events (e.g. StartupInProgress), CID and EID must not be included
  # Avoid using StartupInhibit for Events that must activate immediately

  #ConfigFlags Usage:
  #Diagnostics : CONFIG_ACTIVE_LOGGED_INIT (persistent across reboots)
  #Events : CONFIG_ACTIVE_LOGGED (clears on key-off; re-evaluated on key-on)

### Old style diagnostics are needed for CDL (CID is the ECM)

  # #Implement FMI 9 (596-9)
  # "Imp_CID_596_FMI_9_Diagnostic" =>
  # {
  #   "AutonomyConditions" => ["Imp_CID_596_FMI_9"],
  #   "InhibitConditions"  => ["StartupInhibit",
  #                           "MachinePowerInhibit"],
  #   "Description"        => "Imp_CID_596_FMI_9",
  #   "CID"                => 596,
  #   "FMI"                => 9,
  #   "WCI"                => 2,
  #   "ConfigFlags"        => EventSystem::ConfigFlags::CONFIG_ACTIVE_LOGGED_INIT,
  #   "Protocol"           => EventSystem::Protocol::EDDT | EventSystem::Protocol::CDA | EventSystem::Protocol::ETN,
  #   "CDA_UID"            => 0x12345,
  #   "ETN_UID"            => 0x1051,
  # },

  # #Implement FMI 14 (596-14)
  # "Imp_CID_596_FMI_14_Diagnostic" =>
  # {
  #   "AutonomyConditions" => ["Imp_CID_596_FMI_14"],
  #   "InhibitConditions"  => ["StartupInhibit",
  #                           "MachinePowerInhibit"],
  #   "Description"        => "Imp_CID_596_FMI_14",
  #   "CID"                => 596,
  #   "FMI"                => 14,
  #   "WCI"                => 2,
  #   "ConfigFlags"        => EventSystem::ConfigFlags::CONFIG_ACTIVE_LOGGED_INIT,
  #   "Protocol"           => EventSystem::Protocol::EDDT | EventSystem::Protocol::CDA | EventSystem::Protocol::ETN,
  #   "CDA_UID"            => 0x12346,
  #   "ETN_UID"            => 0x1052,
  # },

  #ActualEngineRPMOverload
  # "ActualEngineRPMOverload_Event" =>
  # {
  #   "AutonomyConditions" => ["ActualEngineRPMOverload"],
  #   "InhibitConditions"  => ["StartupInhibit",
  #                           "MachinePowerInhibit"],
  #   "Description"        => "EngineRPMOverload",
  #   "EID"                => 333,
  #   "WCI"                => 1,
  #   "PID"                => 0x40,
  #   "WorstCaseDirection" => EventSystem::WorstCaseDirection::GREATER,
  #   "Protocol"           => EventSystem::Protocol::EDDT | EventSystem::Protocol::CDA | EventSystem::Protocol::ETN,
  #   "CDA_UID"            => 0x12347,
  #   "ETN_UID"            => 0x1053,
  # },

})

# Update base Diagnostic/Event settings
DiagnosticsAndEvents["J1939_Data_Link2_FMI_9_Diagnostic"].update({
  "Debounce_I2A_sec" => 5,   # debounce diagnostics from CSNS
})

# If there's an auxiliary file, load it
# loadInstanceAuxFile(File.basename( __FILE__ ))
