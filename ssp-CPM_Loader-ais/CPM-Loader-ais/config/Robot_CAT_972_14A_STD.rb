##
## CAT 972 - Standard
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
"outLiftPresNoBucket" => [1091.30, 1130.85, 1170.32, 1209.88, 1249.43, 1288.92, 1328.49, 1367.99, 1407.59, 1447.21, 1486.77, 1526.44, 1566.16, 1605.87, 1645.78, 1685.83, 1726.51],

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
"LiftCylBoreDia" => 170.000,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 90.0000,

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

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_MWL.json",

# Determines whether or not payload legal for trade is supported.
"LegalForTradeSupported" => true,

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
"KgPerLiftKpaAtMidExtension" => 0.925332,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1394.70,

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
    -67.9812, -118.472, -80.5736, 59.6995, 185.105, 191.867, 123.840, -1.69510, -156.554, -326.555, -509.038, -711.700, -938.378, -1191.66, -1496.67,
    -95.0562, -136.375, -96.8264, 44.3467, 201.458, 262.583, 252.685, 172.166, 35.1884, -135.343, -321.574, -521.175, -732.670, -954.985, -1203.89,
    -110.623, -147.622, -109.321, 25.8967, 192.474, 286.151, 325.242, 302.742, 212.049, 63.5294, -121.067, -326.226, -539.771, -755.689, -986.863,
    -119.900, -154.818, -118.723, 8.27671, 172.496, 281.473, 352.543, 379.498, 344.894, 243.134, 83.2938, -117.666, -336.461, -556.598, -785.985,
    -125.716, -159.592, -126.044, -8.09612, 147.591, 260.995, 350.272, 413.198, 430.029, 386.541, 276.499, 104.638, -106.695, -330.564, -565.077,
    -128.966, -162.376, -131.256, -21.8500, 122.868, 233.884, 330.357, 414.179, 467.724, 475.386, 422.853, 301.903, 121.829, -91.2712, -326.819,
    -130.569, -163.778, -134.915, -33.4690, 99.4081, 204.344, 301.181, 395.109, 472.064, 518.614, 518.718, 457.405, 329.776, 150.409, -69.7630,
    -130.965, -164.096, -137.152, -42.5513, 79.2545, 176.755, 270.054, 366.495, 455.417, 526.540, 565.446, 556.188, 485.647, 355.797, 171.035,
    -130.547, -163.634, -138.368, -49.8497, 61.6011, 151.163, 238.881, 333.401, 426.968, 512.389, 578.042, 609.913, 591.909, 517.199, 382.917,
    -129.528, -162.566, -138.745, -55.5734, 46.4609, 128.216, 209.457, 299.480, 392.821, 484.885, 566.939, 627.952, 652.108, 628.141, 548.784,
    -127.965, -160.921, -138.402, -60.1839, 32.9282, 106.905, 181.061, 264.895, 354.766, 448.195, 539.121, 619.709, 676.074, 695.539, 669.464,
    -125.904, -158.728, -137.368, -63.7182, 21.0429, 87.4901, 154.365, 231.032, 315.240, 406.116, 499.844, 591.486, 669.752, 722.447, 741.753,
    -123.219, -155.834, -135.551, -66.3386, 10.2379, 69.1395, 128.415, 197.028, 273.797, 359.048, 450.804, 546.618, 637.989, 714.269, 769.685,
    -119.471, -151.737, -132.523, -68.0162, -0.137184, 50.6388, 101.485, 160.692, 227.913, 304.339, 389.481, 482.985, 579.170, 669.626, 751.256,
    -113.488, -145.087, -127.015, -68.1022, -10.4809, 30.6861, 71.3550, 118.749, 173.154, 236.265, 308.714, 391.737, 482.400, 575.060, 669.479,
    -100.017, -129.748, -113.064, -62.7708, -20.2813, 7.05935, 32.9764, 62.7589, 97.0491, 137.465, 185.151, 242.017, 307.567, 379.408, 459.526,
    -83.3632, -110.278, -94.4561, -51.8503, -21.2187, -3.82951, 11.7293, 29.1134, 48.9145, 72.2728, 100.089, 133.809, 173.595, 218.510, 270.451,
    -63.4284, -86.3469, -71.4735, -37.1096, -16.5101, -6.33395, 2.17428, 11.3414, 21.5962, 33.6150, 47.9397, 65.4108, 86.2375, 110.072, 138.101,
    -34.8292, -50.5060, -38.5483, -17.3958, -7.73248, -3.72247, -0.628442, 2.56526, 6.06072, 10.1202, 14.9494, 20.8551, 27.9356, 36.1033, 45.8018,
    2.60088, 4.81242, 2.85372, 0.957196, 0.399304, 0.202893, 0.0589055, -0.0868096, -0.245350, -0.429572, -0.649479, -0.919689, -1.24545, -1.62344, -2.07508
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
  "InternalMsn" => "CAT72700",
  "Make" => "CAT",
  "Model" => "972",
  "ModelDetail" => "972",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}
