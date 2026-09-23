puts "Loading 793FDB_00 Robot Configuration\n"

SensorConfiguration =
{
  "ConfigurationName" => "BRAVO",
  "Velodyne_FOVLeft_degrees" => 106,
  "Velodyne_FOVRight_degrees" => -84,
  "Velodyne_SpinRate_rpm" => 600,
}

#----------------------------------------------------------------------------
# Radar Definitions
#
# Includes radar source frame, 
# prefix used to determine interface/channel names for each radar (i.e.; FrontLeftUpper + RadarHealthInput),
# the common name for the radar,
# and the name associated with the Component ID (CID).
#----------------------------------------------------------------------------
Radars = {
  IPAddressMap.fetch("leftLowerRadar")  => [ "ESRFLLAssemblyRef", "FrontLeftLower", "Front Left Lower", "Long Range Object Detection Sensor #2"],
# IPAddressMap.fetch("leftUpperRadar")  => [ "ESRFLUAssemblyRef", "FrontLeftUpper", "Front Left Upper", "Long Range Object Detection Sensor #3" ],
  IPAddressMap.fetch("midLowerRadar")   => [ "ESRFCLAssemblyRef", "FrontMidLower", "Front Mid Lower", "Long Range Object Detection Sensor #4"],
# IPAddressMap.fetch("midUpperRadar")   => [ "ESRFCUAssemblyRef", "FrontMidUpper", "Front Mid Upper", "Long Range Object Detection Sensor #5" ],
  IPAddressMap.fetch("rightLowerRadar") => [ "ESRFRLAssemblyRef", "FrontRightLower", "Front Right Lower", "Long Range Object Detection Sensor #6" ],
# IPAddressMap.fetch("rightUpperRadar") => [ "ESRFRUAssemblyRef", "FrontRightUpper", "Front Right Upper", "Long Range Object Detection Sensor #7" ],

}

SensorPoses =
{
  "VelodyneRef" => [ 0.0, 0.0, 0.065, 0.0, 0.0, 180.0],
  "ESRFCLAssemblyRef" => [ -0.331, -0.985, -2.387, 0.0,  0.0,  0.0 ],
  "ESRFLLAssemblyRef" => [ -0.331, -0.585, -2.387, 0.0,  0.0,  16.0 ],
  "ESRFRLAssemblyRef" => [ -0.331, -1.385, -2.387, 0.0,  0.0, -16.0 ],
}

load "Vehicle_793FDB.rb"
load "Model_793FDB.rb"
