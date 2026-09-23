require "commonLoad.rb"
# baseDiagManager
load "commonAutonomyTask.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
 "DiagnosticStatusInput" => InterfaceDefs::DiagnosticStatusInput,
 "AllEventDiagOutput" => InterfaceDefs::EventDiagnosticDataOutput,
 "FMSActiveEventsOutput" => InterfaceDefs::FMSActiveEventsOutput,
 "FMSActiveDiagnosticsOutput" => InterfaceDefs::FMSActiveDiagnosticsOutput,
 "FMSLoggedEventsOutput" => InterfaceDefs::FMSLoggedEventsOutput,
 "FMSLoggedDiagnosticsOutput" => InterfaceDefs::FMSLoggedDiagnosticsOutput,
 "FMSBaseMachineActiveEventsOutput" => InterfaceDefs::FMSBaseMachineActiveEventsOutput,
 "FMSBaseMachineActiveDiagnosticsOutput" => InterfaceDefs::FMSBaseMachineActiveDiagnosticsOutput,
 "FMSBaseMachineLoggedEventsOutput" => InterfaceDefs::FMSBaseMachineLoggedEventsOutput,
 "FMSBaseMachineLoggedDiagnosticsOutput" => InterfaceDefs::FMSBaseMachineLoggedDiagnosticsOutput,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "requireGPSTimeSynchronizationOnStart" => false, # ALLOW this process to start without synchronization
  "loggerThreshold" => "error",
  "cycleRate_hz" => 4,
  # CAN port assigned to Machine ECMs
  # Valid values:
  #     0 - can0 or CAN1 or CAN A
  #     1 - can1 or CAN2 or CAN B
  #     2 - can2 or CAN3 or CAN C
  #     3 - can3 or CAN4 or CAN D
  # 
  "CAN_port" => 0,
  
  "InactiveToActiveDebounce_s" => 5, # 5 times of 1 sec(EDDT heart beat)
  "ActiveToInactiveDebounce_s" => 1.5,
} )


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
  "Preferred_Address"       => 0xF2,
  "Address_List"            => [0xF1,0xF3,0xF4,0xF5,], # Maximum 5 entries supported; beyond ignored
}

# ECM CDL Name (This is the Module ID for baseDiagManager in CDL)
# This is needed only if we configure any EDDT server in CDL (ie. Data_Link "1" in EDDT_Servers)
Ecm_CDL_Name = 
{
  "MID"          => 0x7B,
}

Execution = {
  "executableName" => "baseDiagManager"
}

# If there's an auxiliary file, load it
loadInstanceAuxFile( File.basename( __FILE__ ) )

# If there's an auxiliary file specific to machine, load it
loadInstanceAuxFile("baseDiagManager_"+ Machine_name + ".rb")
