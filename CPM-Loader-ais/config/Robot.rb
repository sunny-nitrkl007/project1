###################################################################
#
#  Robot.rb : Read in the assigned site from robot (copied from $HOME/etc/robot)
# and load the associate Robot_XX.rb configuration file.
#
#  Robot specific information
#    - Vehicle Dimensions
#    - Transform Network
#    - Model parameters
#
#
#  NOTE:  Declaring "RobotType" and "Machine_name" as global variables so they can be 
#         referenced in other ruby config files
#
###################################################################
require "commonLoad.rb"

SUBSYSTEM_PATH = ENV["CAT_DIR"].to_s unless defined? SUBSYSTEM_PATH

robotFile = ENV["CAT_CONFIG_DIR"].to_s + "/robot"
puts "===== Robot file " + robotFile 


# First check to see if robot file exists or if it is empty(0 size)
if (!FileTest.size?(robotFile))
    
    #robot file is empty or does not exist
    puts "===== Robot file " + robotFile + " does not exist."
    puts "===== Most likely this is a brandNew computer. "
    Machine_name = "MSNNOTAVAIL"

# File exists and not empty
else
    
    # Read in the robot type
    file = File.new(robotFile , "r")
    RobotType = file.gets.chomp

    puts " machine serial number is '" + RobotType + "' without the quotes"

    binDir = ENV["CAT_DIR"].to_s + "/bin/"
    Machine_name = `#{binDir}convertMsnToMachName --msn #{RobotType} --subsys #{SUBSYSTEM_PATH} --terse`

    puts "Machine name is: " + Machine_name
    puts "End of machine name"

end

defaultFileName = "Robot_NOT_SET.rb"

if( (Machine_name == "MSNINVALID") or (Machine_name == "MSNUNSUPPORTED") or (Machine_name == "MSNNOTAVAIL") or (Machine_name.empty?) ) 
    puts "===== Retrieved MSN is either invalid or unsupported or unavailable. "
    puts "===== Simply load any application configuration to acquire a valid MSN. "
    puts "===== Note that an Unknown scenario will be loaded to limit system functionality. "
    fileName = defaultFileName
else
    fileName = "Robot_" + Machine_name + ".rb"
end

puts "File name is:" + fileName

begin
  load fileName
rescue LoadError
  puts "===== " + fileName + " was not found, a default scenario will be loaded with limited functionality."
  load defaultFileName
end

load "TargetVariantConfigRobot.rb"
