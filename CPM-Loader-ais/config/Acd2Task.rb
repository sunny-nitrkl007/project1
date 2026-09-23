load "Acd2Task_Base.rb"

# Load run-time version metadata
# require "Version.rb"

# Add new interfaces
Interfaces.update( {
   # "MachineSNInput" => InterfaceDefs::MachineSNInput,
   # "SEAStatusOutput" => InterfaceDefs::SEAStatusOutput,
} )

# Update exisintg parameters/add new ones
Parameters.update( {
   # "loggerThreshold" => Logger::NOTICE,
   # "cycleRate_hz" => 10,
   # "EnableDiagnosticOutputFileWriter" => false,
   # "DiagnosticOutputFile" => "/log/DiagnosticOutputFile.diag",

   # Enable the SystemHardwareHealth input SCS channel. Default to true
   # "enableSystemHardwareHealth" => true,

   # Listen to AutonomyConditions from any of these hosts. If missing or empty, AutonomyConditions
   # for ALL hosts will be accepted.
   # IMPORTANT:Make sure that the hostname of the ECM running Acd2 is included in this list
   # or its AutonomyConditions will be ignored
   # "hostnameWhiteList" => ["auto1","A6N1","A6N1-0","A6N2","A6N2-0","D6CX-0"], 

   # Path to save NVM files, defaults to $APP_NVM_DIR/<TaskName>
   # "nvmPath" => getNvmDir(__FILE__)

   # Optional Prefix to use for NVM files
   # "nvmFilePrefix" => "",
   #List of sub-systems for which the AutonomyConditions are allowed (NOT CURRENTLY SUPPORTED)
   #"subSystemWhiteList" => [],
} )

###################
### OEL Tasks
###################

# Update settings
OelTaskManager.update( {
   # "InitTimeoutSec" => 5.0,
} )

# Add new tasks
OelTaskManager["OelTaskConfig"].update({
   "cal_task" => {
      "OelTaskType" => OelTaskType::CAL,
      "PeriodSec" => 0.100,
      "Priority" => -2,
   },
})

# Change attributes of existing tasks
OelTaskManager["OelTaskConfig"]["nvm_task"].update({
   "PeriodSec" => 5.00
})

# Remove tasks if desired
# OelTaskManager["OelTaskConfig"].delete("cdl_task")
# OelTaskManager["OelTaskConfig"].delete("cdl_cbs_task")

###################
### Built-in Task Plugins
###################

# Autonomy Condition Server
load "Acd2Task_AutonomyConditionServer.rb"

# Datalink Manager
load "Acd2Task_DatalinkManager.rb"

# System Info (ET communication)
load "Acd2Task_SystemInfo.rb"

# RTC/TZ and SHM Clock sync
load "Acd2Task_SyncClockManager.rb"

# Publish Rx parameters over application specific SCS channels
load "Acd2Task_DatalinkParameterPublisher.rb"

##########################################################################
# Optional Task Plugins
##########################################################################
# SEA (Premium Software Feature) Manager
load "Acd2Task_SEAManager.rb"

# Calibration Manager
load "Acd2Task_CalManager.rb"
CalManager.update({"enabled" => false,})

# MachineSN SCS Publisher
load "Acd2Task_MachineSNPublisher.rb"
MachineSNPublisher.update({"enabled" => false,})

# Trip Data Protocol Manager - See Acd2Task_TestTripDataManager.rb
TripDataManager = {
   "enabled" => false,
}

# Test Data Consumer, useful for logging Rx values
TestDatalinkManagerDataConsumer.update({
#   "enabled" => true,
})

# Test Data Producer, used for setting Tx values from Ruby or csv
# See TestDatalinkManager_Server00_Csv.rb for configuration examples
TestDatalinkManagerDataProducer.update({
   # "enabled" => true,
})

###################
### NVM Manager
###################

# The file will be save as "nvmPath"/<Key>".txt"
# Size - Size in bytes of the file. Optional for Diagnostics, BDT, NVM (will be calculated automatically if not included or set to 0)
# Type - Type of block, used to determine the Block ID (BID). NvmBlockType is defined in Acd2Task_NvmManager_Enums.rb
# Integrity - (Optional) How the data is stored in NVM, if not included RAW is used by default
NvmBlockConfig.update( { 
### Already included in Acd2Task_Base:

   # NvmKeys::Diagnostics_Events_Log  => { "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },
   # NvmKeys::Diagnostics_Crit_Info   => { "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },

   # NvmKeys::Service_Clock_Primary   => { "Size" => 532,   "Type" => NvmBlockType::CLOCK_1, "Integrity" => NvmBlockIntegrity::RAW, },
   # NvmKeys::Service_Clock_Secondary => { "Size" => 532,   "Type" => NvmBlockType::CLOCK_2, "Integrity" => NvmBlockIntegrity::RAW, },

   # NvmKeys::RTC_Time_Zone_Old       => { "Size" => 25,    "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },
   # NvmKeys::RTC_Time_Zone_New       => { "Size" => 25,    "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },
   # NvmKeys::RTC_Secure              => { "Size" => 13,    "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },

   # NvmKeys::ProductID               => { "Size" => 8,     "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },

   # NvmKeys::Ethernet_Diagnostics_BDT     => { "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },
   # NvmKeys::J1939_Diagnostics_BDT_CAN1   => { "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },

### New NVM entries:
   # NvmKeys::J1939_Diagnostics_BDT_CAN2   => { "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },
   # NvmKeys::J1939_Diagnostics_BDT_CAN3   => { "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },
   # NvmKeys::J1939_Diagnostics_BDT_CAN4   => { "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },

   # "AppSpecific1"  => { "Size" => 100,  "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },
   # "AppSpecific2"  => { "Size" => 200,  "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },
   # "AppSpecific3"  => { "Size" => 300,  "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },
   # "AppSpecific4"  => { "Size" => 400,  "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },
   # "AppSpecific5"  => { "Size" => 500,  "Type" => NvmBlockType::APP,     "Integrity" => NvmBlockIntegrity::RAW, },
} )

# If there's an auxiliary file, load it
# loadInstanceAuxFile(File.basename( __FILE__ ))
