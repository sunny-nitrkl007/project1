##
## CAT 972M - Standard
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-39.4000, 48.7700],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-39.4000, -35.1100, -30.8100, -26.5000, -22.1500, -17.7300, -13.2200, -8.59000, -3.83000, 1.12000, 6.29000, 11.7500, 17.5700, 23.8800, 30.8800, 38.9100, 48.7700],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1443.00, 1495.10, 1547.10, 1599.20, 1651.30, 1703.30, 1755.40, 1807.40, 1859.50, 1911.60, 1963.60, 2015.70, 2067.80, 2119.80, 2171.90, 2223.90, 2276.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0826654, 0.0823798, 0.0825633, 0.0831783, 0.0842130, 0.0856809, 0.0876160, 0.0900821, 0.0931619, 0.0970141, 0.101846, 0.108009, 0.116051, 0.126977, 0.142772, 0.168041, 0.217682],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1250.66, 1295.99, 1341.23, 1386.56, 1431.89, 1477.14, 1522.49, 1567.77, 1613.14, 1658.54, 1703.88, 1749.35, 1794.87, 1840.38, 1886.12, 1932.02, 1978.64],

# deg/s^2
"outLiftAngleAccel" => [-0.0720023, -0.00574840, 0.0537641, 0.110049, 0.166356, 0.225729, 0.291323, 0.367145, 0.458177, 0.572743, 0.723020, 0.930697, 1.23499, 1.71850, 2.58042, 4.42280, 10.0662],

# mm/s
"liftRefVel" => 83.3000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 3066.00,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-39.4000, 48.7700],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1443.00, 2276.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 7.04867, 12.0300, 16.5717, 21.0483, 25.7041, 30.6691, 36.0899, 42.0967, 48.7547, 56.1615, 64.2357, 72.7657, 81.2958, 89.1421, 95.5885, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [8.15000, 18.9600, 29.7700, 40.5800, 51.3800, 62.1900, 73.0000, 83.8100, 94.6200, 105.420, 116.230, 127.040, 137.850, 148.650, 159.460, 170.270, 181.080],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [8.15000, 18.9600, 29.7700, 40.5800, 51.3800, 62.1900, 73.0000, 83.8100, 94.6200, 105.420, 116.230, 127.040, 137.850, 148.650, 159.460, 170.270, 181.080],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-39.4000, -35.1100, -30.8100, -26.5000, -22.1500, -17.7300, -13.2200, -8.59000, -3.83000, 1.12000, 6.29000, 11.7500, 17.5700, 23.8800, 30.8800, 38.9100, 48.7700],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    911.600, 904.100, 899.500, 898.000, 899.500, 904.300, 912.400, 923.900, 939.000, 957.800, 980.700, 1007.80, 1039.60, 1076.80, 1120.60, 1172.80, 1238.30,
    945.500, 939.300, 936.000, 935.700, 938.600, 944.500, 953.700, 966.300, 982.400, 1002.20, 1025.90, 1053.70, 1086.20, 1123.90, 1168.00, 1220.50, 1286.00,
    972.600, 967.200, 964.700, 965.300, 968.800, 975.500, 985.400, 998.700, 1015.40, 1035.70, 1059.80, 1088.10, 1120.90, 1158.90, 1203.20, 1255.90, 1321.40,
    999.100, 994.400, 992.600, 993.700, 997.900, 1005.20, 1015.60, 1029.40, 1046.50, 1067.20, 1091.70, 1120.30, 1153.40, 1191.60, 1236.10, 1288.80, 1354.40,
    1027.00, 1022.80, 1021.60, 1023.30, 1028.00, 1035.80, 1046.70, 1060.80, 1078.40, 1099.40, 1124.20, 1153.00, 1186.30, 1224.70, 1269.30, 1322.10, 1387.70,
    1057.30, 1053.70, 1053.00, 1055.20, 1060.40, 1068.60, 1079.90, 1094.40, 1112.30, 1133.60, 1158.70, 1187.70, 1221.20, 1259.70, 1304.50, 1357.30, 1422.80,
    1091.20, 1088.00, 1087.80, 1090.50, 1096.10, 1104.70, 1116.40, 1131.20, 1149.40, 1171.00, 1196.20, 1225.50, 1259.10, 1297.70, 1342.50, 1395.40, 1461.00,
    1129.50, 1126.90, 1127.10, 1130.10, 1136.10, 1145.10, 1157.00, 1172.20, 1190.60, 1212.40, 1237.80, 1267.20, 1300.90, 1339.70, 1384.50, 1437.50, 1503.00,
    1173.40, 1171.10, 1171.70, 1175.10, 1181.40, 1190.60, 1202.90, 1218.20, 1236.80, 1258.80, 1284.40, 1313.80, 1347.60, 1386.50, 1431.30, 1484.30, 1549.80,
    1223.50, 1221.60, 1222.50, 1226.20, 1232.70, 1242.20, 1254.60, 1270.10, 1288.80, 1310.90, 1336.50, 1366.00, 1399.90, 1438.70, 1483.60, 1536.60, 1602.10,
    1280.40, 1278.70, 1279.80, 1283.70, 1290.40, 1299.90, 1312.50, 1328.00, 1346.80, 1368.80, 1394.50, 1424.00, 1457.80, 1496.60, 1541.50, 1594.40, 1659.90,
    1343.30, 1341.70, 1342.90, 1346.90, 1353.60, 1363.20, 1375.70, 1391.30, 1410.00, 1432.00, 1457.50, 1486.90, 1520.70, 1559.40, 1604.20, 1657.10, 1722.60,
    1410.10, 1408.60, 1409.70, 1413.70, 1420.30, 1429.80, 1442.20, 1457.60, 1476.10, 1498.00, 1523.40, 1552.60, 1586.20, 1624.80, 1669.50, 1722.30, 1787.80,
    1476.70, 1475.10, 1476.10, 1479.90, 1486.40, 1495.70, 1507.80, 1523.00, 1541.30, 1562.90, 1588.00, 1617.00, 1650.30, 1688.70, 1733.30, 1786.00, 1851.60,
    1537.50, 1535.60, 1536.50, 1540.00, 1546.20, 1555.30, 1567.10, 1582.00, 1600.00, 1621.30, 1646.10, 1674.90, 1708.00, 1746.10, 1790.50, 1843.20, 1908.70,
    1586.70, 1584.60, 1585.20, 1588.50, 1594.50, 1603.20, 1614.80, 1629.40, 1647.10, 1668.10, 1692.70, 1721.20, 1754.00, 1792.00, 1836.20, 1888.70, 1954.20,
    1620.00, 1617.80, 1618.20, 1621.30, 1627.10, 1635.60, 1647.00, 1661.30, 1678.80, 1699.60, 1724.00, 1752.30, 1784.90, 1822.70, 1866.80, 1919.30, 1984.80
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [8.15000, 181.080],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-93.5500, 79.3800],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [8.15000, 181.080],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1080.00, 1620.00],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 158.800,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 88.9000,

##
## Tilt Cylinders
##

# Number of tilt cylinders.
"NoOfTiltCyls" => 1,

# Tilt cylinder bore diameter, in mm.
"TiltCylBoreDia" => 190.000,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 100.000,

##
## Tool
##

# Tool's length between B and C pins, in mm.
"ToolBcLen" => 434.015,

# Tool's angle between line BC and tool's X-axis, in deg.
"ToolBcAngle" => 101.698,

##
## Random Stuff
##

# The default hydraulic oil type index.
"HydOilType" => 0,

# Wait 6 time constants before using the output of some filter.
"FilterTauDelay" => 6,

# The sample rate of the PWM input signals, in Hz.
"PwmcycleRate_hz" => 50.0000,

# The default loader target weight used for overload detection, in tonnes.
"LoaderBktPayldTrgtWt" => 8.36600,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 11.5000,

# The CAT datalink configuration file.
"BMI_CDL_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiCdl_MWL-M.json",

# The BMI J1939 configuration file.
"BMI_J1939_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiJ1939_MWL_M_SA.json",

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_MWL.json",

# Determines whether or not hydraulic oil temperature is optional for this
# machine configuration.
"HydOilTempOptional" => true,

# Determines whether or not acceleration compensation is supported for this
# machine configuration
"AccelCompSupported" => true,

# This selects the application number used for selecting the cycle segmentation
# data.
"CycleSegAppNumber" => 7200,

##
## Calibration Information
##

# Qualified Read - Hyd Oil Temp Min for Empty & Full calibrations
"QR_Min_HydOilTemp_celsius" => 40,

# Qualified Read - Target Velocity for slow lower for Empty & Full calibrations
"QR_Min_LiftCylVelocity_mm_sec" => -25,

# Qualified Read - Target Velocity for slow lift for Empty & Full calibrations
"QR_Max_LiftCylVelocity_mm_sec" => 25,

# The lift head-end cylinder gain. For each kPa of head-end pressure change, how
# many kg of payload weight does that correspond to? This assumes stationary
# linkage at full rack, at 50% lift cylinder extension, rod-end is at
# atmospheric pressure, and there is no friction. Used to estimate the empty
# bucket weight and the full bucket calibration weight.
"KgPerLiftKpaAtMidExtension" => 0.807423,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1598.37,

##
## Temperature Compensation
##

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylHeLineLoss2ndOrdrCoeff" => 2.34121E-06,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3.
"LiftCylHeLineLoss1stOrdrCoeff" => 4.00077,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylReLineLoss2ndOrdrCoeff" => 2.73489E-06,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3
"LiftCylReLineLoss1stOrdrCoeff" => 4.00208,

##
## Weigh Range Weigh
##

# The default start of weigh range, in %.
"StartOfWeigh" => 50.0000,

# The default end of weigh range, in %.
"EndOfWeigh" => 65.0000,

# The minimum weight range width, in %.
"WeighRangeMin" => 15.0000,

##
## Weight Filtering
##

# Weight filter corner frequency in rad/sec.
"WtCf" => 10.0000,

# Live weight filter factor when machine is not moving, in rad/sec.
"FastFiltWtCf" => 3.50000,

# Live weight filter factor when machine is moving, in rad/sec.
"SlowFiltWtCf" => 1.00000,

# Band stop filter stage 1 center frequency in rad/sec.
"StageOneCf" => 5.00000,

# Band stop filter stage 2 center frequency in rad/sec.
"StageTwoCf" => 7.50000,

# Band stop filter stage 3 center frequency in rad/sec.
"StageThreeCf" => 12.0000,

# Band stop filter dampening ratio.
"DampingRate" => 1.00000,

# Lift Angular Velocity low pass filter corner frequency in rad/sec.
"LiftAngVelFilterCf" => 31.4159,

##
## Low Lift Weigh
##

# The filter factors used to estimate the mean payload weight for the purposes
# of auto weigh range. (0.6 Hz @ T = 20 ms).
"FilterFactorMean" => 0.927407,

# The filter factor used to estimate the variance of the payload weight estimate
# for the purposes of auto weigh range. (0.6 Hz @ T = 20 ms).
"FilterFactorVariance" => 0.927407,

# The interval used to calculate the confidence in the estimate of the mean
# payload. We are X% confident that the estimated payload is within E% of the
# actual payload, where 'E' is this number. Used for auto weigh range.
"ErrorBand" => 1.00000,

# The minimum amount of time that all of the auto weigh range criterion are met
# prior to capturing a weight.
"MinimumConfidenceTime" => 1.25000,

# The confidence that must be reached to latch an auto weigh range weight. 1.0
# means 100% confident. 0.0 means 0% confident. We are X% confident that the
# estimated payload is within E% of the actual payload, where 'X' is this number
# represented as a percentage. Used for auto weigh range.
"AutoWeighRangeConfThr" => 0.997000,

# Auto weigh range will not capture a weigh below this height due to potential
# rack stop interference.
"AutoWeighMinLiftHt" => 30.0000,

##
## Zero Weight Configuration
##

# Which level of accuracy is required for a valid bucket zero (accuracy level 1,
# 2, or 3, etc.).
"ZeroBktWtAccuracyLimit" => 3,

# Maximum allowed ratio of calibration weight that is allowed for bucket zero.
"ZeroRangeLimit" => 0.665000,

# A zero will be requested this long after startup, in seconds.
"ZeroAdjInitTimeInterval" => 300,

# A zero will be requested this long after the last zero, in seconds.
"ZeroAdjAutoTimeInterval" => 14400,

# A zero will be requested this long after the last zero, in seconds, if
# hydraulic oil temperature is disabled.
"ZeroAdjAutoTimeIntervalFast" => 900,

# Nobody knows what this means, in degrees C.
"ZeroAdjOilTempWarnThreshold" => 30.0000,

# If hydraulic oil temperature changes by this much, in degrees C, a zero is
# requested.
"ZeroAdjOilTempDelta" => 10.0000,

##
## Tilt Compensation Configuration
##

# The gain applied to tilt compensation. 1.0 is full tilt compensation, 0.0 is
# none.
"TiltCompGainScalar" => 1.00000,

# The gain applied to the empty bucket portion of the tilt compensation
# adjustment.
"TiltCompEmptyBktWtGain" => 0.400000,

# The maximum allowed tilt compensation factor.
"TiltCompMaxGain" => 0.500000,

# Lift cylinder extension axis for the tilt compensation gain table, in %.
"LiftCylExtPctAxis" => [0.00000, 12.7251, 27.3709, 47.1789, 63.0252, 71.1885, 76.9508, 81.7527, 85.7143, 89.0756, 91.9568, 94.4778, 96.6387, 98.4394, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 5.92593, 11.1111, 15.7407, 20.1852, 24.2593, 28.1481, 31.6667, 35.0000, 38.1481, 41.2963, 44.4444, 47.7778, 51.6667, 56.8519, 66.1111, 75.0000, 83.3333, 92.2222, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -77.9087, -135.773, -92.3400, 68.4176, 212.136, 219.886, 141.924, -1.94264, -179.416, -374.242, -583.374, -815.631, -1075.41, -1365.68, -1715.23,
    -108.937, -156.290, -110.966, 50.8227, 230.877, 300.928, 289.585, 197.308, 40.3271, -155.108, -368.534, -597.283, -839.663, -1094.44, -1379.70,
    -126.777, -169.179, -125.285, 29.6785, 220.581, 327.938, 372.738, 346.952, 243.015, 72.8067, -138.747, -373.865, -618.595, -866.044, -1130.98,
    -137.409, -177.427, -136.060, 9.48537, 197.686, 322.578, 404.026, 434.917, 395.260, 278.639, 95.4574, -134.849, -385.595, -637.880, -900.764,
    -144.075, -182.898, -144.450, -9.27842, 169.144, 299.108, 401.423, 473.538, 492.827, 442.989, 316.877, 119.919, -122.275, -378.837, -647.596,
    -147.800, -186.088, -150.424, -25.0409, 140.811, 268.039, 378.600, 474.662, 536.026, 544.807, 484.603, 345.991, 139.620, -104.600, -374.546,
    -149.636, -187.695, -154.617, -38.3565, 113.925, 234.185, 345.163, 452.808, 541.001, 594.348, 594.468, 524.201, 377.934, 172.374, -79.9507,
    -150.090, -188.059, -157.180, -48.7652, 90.8282, 202.567, 309.490, 420.015, 521.923, 603.432, 648.020, 637.410, 556.568, 407.755, 196.012,
    -149.611, -187.530, -158.575, -57.1293, 70.5968, 173.237, 273.765, 382.089, 489.319, 587.215, 662.454, 698.980, 678.347, 592.727, 438.835,
    -148.444, -186.306, -159.006, -63.6889, 53.2456, 146.940, 240.044, 343.213, 450.186, 555.694, 649.731, 719.654, 747.337, 719.870, 628.924,
    -146.652, -184.421, -158.613, -68.9727, 37.7368, 122.517, 207.502, 303.578, 406.574, 513.645, 617.850, 710.206, 774.803, 797.110, 767.228,
    -144.290, -181.908, -157.429, -73.0231, 24.1159, 100.267, 176.907, 264.770, 361.275, 465.421, 572.837, 677.861, 767.557, 827.947, 850.073,
    -141.213, -178.591, -155.345, -76.0262, 11.7329, 79.2361, 147.167, 225.800, 313.780, 411.481, 516.636, 626.442, 731.155, 818.576, 882.084,
    -136.918, -173.896, -151.876, -77.9487, -0.157218, 58.0337, 116.305, 184.158, 261.196, 348.782, 446.358, 553.517, 663.747, 767.413, 860.964,
    -130.061, -166.274, -145.563, -78.0473, -12.0114, 35.1673, 81.7751, 136.091, 198.440, 270.768, 353.796, 448.943, 552.846, 659.037, 767.245,
    -114.623, -148.696, -129.575, -71.9373, -23.2431, 8.09025, 37.7920, 71.9237, 111.221, 157.539, 212.189, 277.359, 352.481, 434.814, 526.632,
    -95.5369, -126.383, -108.250, -59.4222, -24.3173, -4.38874, 13.4422, 33.3649, 56.0576, 82.8269, 114.705, 153.350, 198.946, 250.419, 309.946,
    -72.6910, -98.9563, -81.9109, -42.5289, -18.9211, -7.25891, 2.49179, 12.9977, 24.7499, 38.5239, 54.9404, 74.9629, 98.8310, 126.146, 158.268,
    -39.9153, -57.8815, -44.1776, -19.9362, -8.86167, -4.26607, -0.720214, 2.93987, 6.94578, 11.5980, 17.1325, 23.9006, 32.0151, 41.3755, 52.4904,
    2.98070, 5.51518, 3.27046, 1.09698, 0.457616, 0.232522, 0.0675076, -0.0994866, -0.281179, -0.492303, -0.744324, -1.05399, -1.42733, -1.86052, -2.37810
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 8.36600,

# Maximum duration to consider a valid dig, in seconds.
"DigDurationMaxLimit" => 45.0000,

# Minimum duration to consider a valid dig, in seconds.
"DigDurationMinLimit" => 0.500000,

# Dig is triggered when the rate of material loss, in terms of normalized
# payload, exceeds this rate (negative means material gain), in ratio/second.
"DigStartLimit" => -0.150000,

# Dig is cancelled or ended when the rate of material loss, in terms of
# normalized payload, exceeds this rate (positive means material loss), in
# ratio/second.
"DigEndLimit" => 0.0250000,

# If you are lowering the bucket, you won't trigger a start of dig. The lift
# linkage velocity needs to be higher than this to trigger a dig., nobody knows
# units, maybe mm/s.
"LiftLowerVelocityLimit" => -1.00000,

##
## Dump State Configuration
##

# The bucket is considered fully racked if the bucket angle is greater than this
# value, as well as other conditions. Fully Racked = ((Cyl% > X) OR (ABC% > Y))
# AND (Bucket Angle > This Value)
"FullRackBktAngleThreshold" => 35.0000,

# The bucket is considered partially dumped if the bucket angle is less than or
# equal to this value, as well as other conditions. Partial Dump = (Cyl% <= X)
# AND (ABC% <= Y) AND (Bucket Angle <= This Value)
"PartDumpBktAngleThreshold" => 40.0000,

# The bucket is considered fully dumped if the bucket angle is less than this
# value. Fully Dumped = (Bucket Angle <= This Value), in degrees.
"FullDumpBktAngleThreshold" => -35.0000,

# Used to determine if the bucket is fully racked back for LFT payload. LFT
# Fully Racked = Cyl% > This Value
"TiltCylExtThresholdStrict" => 98.4444,

# Used to determine if the bucket is near the end of tilt cylinder extension.
# Used to determine fully racked and partial dump status. Fully Racked = ((Cyl%
# > This Value) OR (ABC% > Y)) AND (Bucket Angle > Z). Partial Dump = (Cyl% <=
# This Value) AND (ABC% <= Y) AND (Bucket Angle <= Z)
"TiltCylExtThreshold" => 85.0000,

# Used to determine if the tilt angle is near the rack stops. Used to determine
# fully racked and partial dump status. Fully Racked = ((Cyl% > X) OR (ABC% >
# This Value)) AND (Bucket Angle > Z). Partial Dump = (Cyl% <= X) AND (ABC% <=
# This Value) AND (Bucket Angle <= Z)
"TiltAngleABCThreshold" => 90.0000,

}

MachineType = {
  "InternalMsn" => "CAT72400",
  "Make" => "CAT",
  "Model" => "972M",
  "ModelDetail" => "972M",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
