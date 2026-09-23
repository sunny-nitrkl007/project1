require "commonLoad.rb"
require "commonTaskParams.rb"
require "Robot.rb"
#require "commonAutonomyTask.rb"
require "interfaces_Loaders.rb"
require "interfaces_CpmCommon.rb"

Interfaces = CommonTaskParams::Interfaces.dup;
Interfaces.update( {

} )

Parameters = CommonTaskParams::Parameters.dup;
Parameters.update( {
    # Weighing App 20 msec or 50.0 Hz execution rate should be in float data type
    "cycleRate_hz" => 50.0,
    "scheduler" => "SCHED_RR",
    "schedulerPriority" => 19,
    # Weighing library 20 msec execution rate 
    "CPMExecRate" => 0.02,
    # Weighing App Transmit optimized execution period in Seconds 
    "CPMExecTxPeriod" => 0.1, # (100 msec)
    "loggerThreshold" => "error",  ##  All options listed in descending severity order
                                   ##  - emerg, fatal, alert, crit, error, warn, notice, info, debug 
    "storageRoot" => "/opt/appdata/CPM/LpsSaWeighApp/nvm",
    "tempRoot" => "/tmp/appdata/CPM/LpsSaWeighApp",
} )

ScsRxTimeouts = {
  "SystemHardwareHealthRequestOutput_txRate_sec" => 0.5,
}

Execution = {
  "executableName" => "LpsSaWeighApp",
}

ConditionConfig =
{
"AutonomyConditions" => [
"TiltLinkVoltageAbove",
"TiltLinkVoltageBelow",
"TiltLinkFreqAbnormal",
"TiltLinkCalibrationOut",
"LiftLinkVoltageAbove",
"LiftLinkVoltageBelow",
"LiftLinkFreqAbnormal",
"LiftLinkCalibrationOut",
"LiftREVoltageAbove",
"LiftREVoltageBelow",
"LiftREFreqAbnormal",
"LiftHEVoltageAbove",
"LiftHEVoltageBelow",
"LiftHEFreqAbnormal",
"PayloadMonCalibrationOut"
        				],
}

ChassisIMU = {
  "BiasJerkFilterFactor" => 0.013245, # Jerk Filter Factor (1.5 second time constant)
  "BiasAngAccelFilterFactor" => 0.013245, # Angular Accel Filter Factor (1.5 second time constant)
  "BiasFilterFactor" => 0.006263, # Low pass filter factor for bias estimation (0.05 Hz, about 3 second time constant)
  "BiasSpeedThreshold" => 0.1, # Linear speed threshold to enable bias estimation (m/s)
  "BiasJerkThreshold" => 10.0, # Jerk threshold to enable bias estimation (m/s^3)
  "BiasAngAccelThreshold" => 2.0, # Angular acceleration threshold to enable bias estimation (rad/s^2)
  "BiasAngVelThreshold" => 0.07, # Angular velocity threshold to enable bias estimation (rad/s)
  "BiasDebounceTimeSeconds" => 0.3, # Time for conditions to be true before updating bias estimation (seconds)
  "AngFusionFilterFactor" => 1 - 0.01, # Angle Fusion (0.5 rad/s)
  "RollFilterFactor" => 0.672621, # Roll Filter (10Hz)
  "PitchNotchFrequency" => 7.5, # Pitch Notch Filter (rad/s, ~1.2 Hz)
  "PitchNotchDamping" => 0.75, # Pitch Notch Damping Ratio
  "PitchFilterFactor" => 0.672621, # Pitch Filter (10Hz)
  "VelFusionFilterFactor" => 1 - 0.058219, # Velocity Fusion (3 rad/s)
}
