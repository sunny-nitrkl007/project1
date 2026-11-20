require "commonLoad"
require "interfaces_CpmCommon.rb"
load "commonTaskParams.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
     "DataLinkDataInput" => InterfaceDefs_CpmCommon::DataLinkDataInput,
} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "loggerThreshold" => "error",   ##  All options listed in descending severity order
                                 ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug
  "cycleRate_hz" => 8.33,
  "MaxRecordsToCreateFile" =>5,

  "initialValuesFromConfig" => 0,    #In case initial values aren't available, initialize to 0?
  "gpsDistanceThreshold" => 20,      # meters
  "gpsTimeThreshold"     => 60,      # seconds
  # Uncomment these to test model integration
  #"modelInputTestCsvFilePath" => "/media/sf_My_Shared_Folder/mtp_cycle_seg_input_data.csv",
  #"modelOutputTestCsvFilePath" => "/media/sf_My_Shared_Folder/mtp_cycle_seg_output_data.csv",
  #"printModelTestPoints" => true,
} )

Execution = {
  "executableName" => "DatalinkTestApp",
}
