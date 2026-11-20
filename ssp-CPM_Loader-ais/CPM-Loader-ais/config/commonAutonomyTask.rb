require "commonLoad.rb"
#common AutonomyTask interfaces.  

require "commonTaskParams.rb"  # load Task Interfaces
require "Minestar-MachineID.rb" if File.exists?("Minestar-MachineID.rb")
require "Robot.rb"             # load Robot related parameters
require "Site.rb"              # load Site related parameters
require "Robot_793FDB_00.rb"

# Interfaces related to AutonomyTasks
CommonTaskParams::Interfaces.update( {
    "LoggerCommentsOutput" => InterfaceDefs::LoggerCommentsOutput,
} )

