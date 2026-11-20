require "commonLoad.rb"
load "commonAutonomyTask.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "loggerThreshold" => "error", # "fatal", "error", "warn", "notice", "info", "debug",
  "cycleRate_hz" => 5,  #5hz
} )


Execution = {
  "executableName" => "CANTestApp",
}
