load "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"
require "commonLoad"
require "Robot.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
   "DataLinkDataOutput" => InterfaceDefs_CpmCommon::DataLinkDataOutput,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
   "cycleRate_hz" => 9, # Faster than the output, to be able to read inputs from CSV
   "loggerThreshold" => "warn",  ##  All options listed in descending severity order
                                 ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug
} )

Execution = {
  "executableName" => "csvToDldApp",
}

SimConfig = {
  "Input CSV Directory" => "/opt/test_data",
  "CSV Buffer Size" => 20,
  "NonStop" => 1,        ##  1= keep reading file forever,  0=stop at end of file
  "Output Rate (ms) SCS CDL" => 120,
  "CsvDataFormat" => 1,   ## 1 = Decimal data,   2 = 2 Byte Hex
}

# Load application specific Interfaces and Parameters
loadInstanceAuxFile( File.basename( __FILE__ ) )
