require "commonLoad"
require "commonTaskParams.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {
   "AppRegInput" => InterfaceDefs_CpmCommon::AppRegInput,
   "AppRegOutput" => InterfaceDefs_CpmCommon::AppRegOutput,

} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "loggerThreshold" => "info",  ##  All options listed in descending severity order
                                 ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug
  "cycleRate_hz" => 1,
  "AppName" => "AppRegTest_A",
  "DestAppName" => "AppRegTest_B",
  "KeyOffTimeOutMsec"=>4000,

} )

Execution = {
  "executableName" => "AppRegTest",
}

