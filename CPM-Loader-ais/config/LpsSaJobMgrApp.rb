require "commonLoad.rb"
require "commonTaskParams.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"
require "Robot.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update({

})

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
  "loggerThreshold" => "error",  ##  All options listed in descending severity order
                                 ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 

  "cycleRate_hz" => 10.0, #every 100 ms changed to match with ACD App
  "scheduler" => "SCHED_RR",
  "schedulerPriority" => 1,
  "SimpleCalMaxTrucksSupported" => 15,  ## Maximum number of trucks supported for simple cal.
  "storageRoot" => "/opt/appdata/CPM/LpsSaJobMgrApp/nvm"
})

Execution = {
    "executableName" => "LpsSaJobMgrApp",
}

