##
## CAT 966GC - Standard
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-42.0600, 45.2100],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-42.0600, -37.7600, -33.4700, -29.1600, -24.8200, -20.4100, -15.9100, -11.3000, -6.56000, -1.64000, 3.50000, 8.91000, 14.6800, 20.9100, 27.8000, 35.6600, 45.2100],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1443.00, 1495.10, 1547.10, 1599.20, 1651.30, 1703.30, 1755.40, 1807.40, 1859.50, 1911.60, 1963.60, 2015.70, 2067.80, 2119.80, 2171.90, 2223.90, 2276.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0827476, 0.0823904, 0.0825101, 0.0830658, 0.0840406, 0.0854467, 0.0873161, 0.0897042, 0.0926941, 0.0964307, 0.101119, 0.107073, 0.114829, 0.125286, 0.140262, 0.163819, 0.208490],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1119.96, 1163.52, 1206.98, 1250.56, 1294.23, 1337.93, 1381.88, 1425.97, 1470.43, 1515.27, 1560.51, 1606.50, 1653.44, 1701.67, 1752.27, 1806.97, 1871.76],

# deg/s^2
"outLiftAngleAccel" => [-0.0822510, -0.0145446, 0.0455734, 0.102184, 0.158326, 0.217177, 0.281845, 0.356066, 0.444765, 0.555662, 0.700448, 0.898715, 1.18735, 1.63978, 2.43233, 4.07637, 8.80342],

# mm/s
"liftRefVel" => 83.3000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 2935.80,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-42.0600, 45.2100],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1443.00, 2276.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 7.79221, 12.7075, 16.9653, 21.0751, 25.3000, 29.8208, 34.7855, 40.3748, 46.7204, 53.9536, 62.0746, 70.9025, 79.9112, 88.3117, 95.2491, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [11.7000, 22.3700, 33.0300, 43.7000, 54.3700, 65.0300, 75.7000, 86.3700, 97.0300, 107.700, 118.360, 129.030, 139.700, 150.360, 161.030, 171.690, 182.360],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [11.7000, 22.3700, 33.0300, 43.7000, 54.3700, 65.0300, 75.7000, 86.3700, 97.0300, 107.700, 118.360, 129.030, 139.700, 150.360, 161.030, 171.690, 182.360],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-42.0600, -37.7600, -33.4700, -29.1600, -24.8200, -20.4100, -15.9100, -11.3000, -6.56000, -1.64000, 3.50000, 8.91000, 14.6800, 20.9100, 27.8000, 35.6600, 45.2100],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    917.800, 908.900, 902.900, 899.900, 899.915, 903.200, 909.700, 919.700, 933.300, 950.600, 972.000, 997.700, 1028.10, 1063.90, 1106.20, 1156.80, 1219.90,
    955.100, 947.600, 943.000, 941.300, 942.800, 947.300, 955.100, 966.300, 981.000, 999.400, 1021.70, 1048.20, 1079.40, 1115.80, 1158.50, 1209.40, 1272.70,
    981.800, 975.000, 971.200, 970.300, 972.500, 977.700, 986.200, 998.000, 1013.30, 1032.20, 1055.00, 1081.90, 1113.40, 1150.10, 1193.10, 1244.20, 1307.50,
    1006.50, 1000.30, 997.100, 996.800, 999.500, 1005.30, 1014.30, 1026.60, 1042.40, 1061.70, 1084.80, 1112.00, 1143.80, 1180.70, 1223.80, 1275.00, 1338.30,
    1031.70, 1026.10, 1023.40, 1023.60, 1026.80, 1033.10, 1042.50, 1055.20, 1071.20, 1090.90, 1114.30, 1141.80, 1173.80, 1210.80, 1254.10, 1305.40, 1368.70,
    1058.80, 1053.70, 1051.40, 1052.10, 1055.80, 1062.40, 1072.20, 1085.30, 1101.70, 1121.60, 1145.30, 1172.90, 1205.10, 1242.30, 1285.70, 1337.00, 1400.40,
    1089.00, 1084.30, 1082.50, 1083.60, 1087.70, 1094.70, 1104.90, 1118.20, 1134.90, 1155.00, 1178.90, 1206.80, 1239.10, 1276.50, 1319.90, 1371.30, 1434.70,
    1123.40, 1119.20, 1117.80, 1119.30, 1123.70, 1131.10, 1141.60, 1155.20, 1172.10, 1192.50, 1216.50, 1244.60, 1277.00, 1314.40, 1358.00, 1409.40, 1472.80,
    1163.40, 1159.60, 1158.60, 1160.40, 1165.20, 1172.80, 1183.60, 1197.40, 1214.60, 1235.10, 1259.30, 1287.50, 1320.00, 1357.50, 1401.10, 1452.50, 1515.90,
    1210.20, 1206.70, 1206.10, 1208.20, 1213.20, 1221.10, 1232.10, 1246.10, 1263.40, 1284.10, 1308.40, 1336.60, 1369.20, 1406.70, 1450.30, 1501.80, 1565.20,
    1264.80, 1261.60, 1261.20, 1263.60, 1268.80, 1276.90, 1287.90, 1302.10, 1319.40, 1340.20, 1364.50, 1392.70, 1425.30, 1462.80, 1506.40, 1557.80, 1621.20,
    1327.20, 1324.20, 1323.90, 1326.40, 1331.70, 1339.90, 1351.00, 1365.10, 1382.50, 1403.10, 1427.40, 1455.60, 1488.10, 1525.50, 1569.00, 1620.40, 1683.80,
    1395.50, 1392.60, 1392.30, 1394.80, 1400.10, 1408.20, 1419.20, 1433.20, 1450.40, 1471.00, 1495.10, 1523.10, 1555.40, 1592.70, 1636.10, 1687.40, 1750.80,
    1465.30, 1462.30, 1461.90, 1464.30, 1469.40, 1477.30, 1488.10, 1502.00, 1518.90, 1539.20, 1563.10, 1590.80, 1622.90, 1660.00, 1703.20, 1754.40, 1817.80,
    1530.00, 1526.80, 1526.20, 1528.40, 1533.20, 1540.90, 1551.40, 1564.90, 1581.60, 1601.60, 1625.10, 1652.60, 1684.40, 1721.20, 1764.20, 1815.30, 1878.60,
    1582.60, 1579.10, 1578.40, 1580.30, 1584.90, 1592.20, 1602.50, 1615.70, 1632.00, 1651.70, 1675.00, 1702.10, 1733.70, 1770.30, 1813.10, 1864.00, 1927.30,
    1618.20, 1614.60, 1613.60, 1615.30, 1619.70, 1626.90, 1636.90, 1649.90, 1666.00, 1685.40, 1708.50, 1735.40, 1766.70, 1803.20, 1845.80, 1896.60, 1959.80
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [11.7000, 182.360],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-90.0000, 80.6600],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [11.7000, 182.360],

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
"TiltCylBoreDia" => 170.000,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 82.5000,

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
"LoaderBktPayldTrgtWt" => 7.12000,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 10.0000,

# The CAT datalink configuration file.
"BMI_CDL_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiCdl_966_980_MWL_GC.json",

# The BMI J1939 configuration file.
"BMI_J1939_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiJ1939_966_980_MWL_GC_SA.json",

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_MWL_GC.json",

# Determines whether or not payload legal for trade is supported.
"LegalForTradeSupported" => true,

# Determines whether or not hydraulic oil temperature is optional for this
# machine configuration.
"HydOilTempOptional" => true,

# Determines whether or not acceleration compensation is supported for this
# machine configuration
"AccelCompSupported" => true,

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
"KgPerLiftKpaAtMidExtension" => 0.850236,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1449.50,

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
"LiftCylExtPctAxis" => [0.00000, 13.2053, 27.0108, 44.7779, 60.1441, 68.9076, 75.1501, 80.1921, 84.3938, 87.9952, 91.1164, 93.8776, 96.1585, 98.1993, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 5.92593, 11.1111, 15.9259, 20.3704, 24.4444, 28.3333, 32.0370, 35.5556, 38.8889, 42.0370, 45.1852, 48.5185, 52.5926, 58.8889, 67.5926, 75.1852, 82.9630, 92.0370, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -73.6861, -130.704, -96.3320, 42.9161, 191.473, 220.408, 163.011, 51.2670, -86.7279, -238.623, -402.696, -585.676, -779.382, -1006.09, -1277.11,
    -104.638, -149.613, -114.836, 21.7534, 198.997, 289.978, 297.452, 228.039, 102.851, -53.0275, -223.566, -407.482, -593.552, -801.358, -1037.29,
    -119.884, -160.241, -128.427, -1.42371, 178.786, 304.038, 369.165, 362.815, 282.313, 143.825, -28.4123, -219.980, -410.453, -616.034, -840.646,
    -127.635, -166.418, -138.472, -22.9118, 147.654, 285.038, 387.208, 439.614, 422.854, 332.321, 181.815, -8.65643, -206.034, -417.828, -643.209,
    -131.091, -169.650, -145.486, -40.9091, 115.066, 250.599, 369.274, 461.186, 503.301, 476.750, 376.066, 210.959, 17.7521, -199.459, -431.352,
    -132.053, -170.920, -150.078, -55.1379, 85.5326, 212.397, 333.684, 445.551, 528.771, 561.064, 523.540, 409.169, 242.218, 32.5429, -202.572,
    -131.516, -170.865, -152.923, -66.4570, 59.4404, 174.709, 290.756, 408.802, 515.652, 592.308, 615.718, 566.730, 449.546, 270.004, 45.8841,
    -129.986, -169.821, -154.339, -75.1569, 37.3177, 140.331, 247.174, 362.497, 478.678, 582.374, 652.965, 667.612, 613.171, 486.376, 295.772,
    -127.796, -168.038, -154.602, -81.6051, 19.0729, 110.382, 206.573, 314.296, 430.136, 546.183, 646.960, 712.131, 718.860, 656.755, 520.951,
    -125.170, -165.709, -153.952, -86.1722, 4.33071, 85.0402, 170.578, 268.568, 378.436, 496.503, 612.591, 711.537, 767.710, 768.491, 698.336,
    -122.268, -162.984, -152.588, -89.1992, -7.38325, 64.0120, 139.632, 227.421, 328.569, 442.333, 562.892, 680.488, 770.870, 823.175, 816.784,
    -119.001, -159.780, -150.540, -91.0649, -17.0649, 45.8101, 112.024, 189.446, 280.331, 385.896, 503.675, 628.683, 740.086, 830.950, 880.518,
    -115.178, -155.891, -147.665, -91.8687, -25.2565, 29.5007, 86.5400, 153.381, 232.850, 327.384, 436.956, 560.428, 681.256, 797.227, 891.015,
    -110.033, -150.467, -143.213, -91.3481, -32.6496, 13.4146, 60.4828, 115.449, 181.330, 261.199, 356.738, 469.762, 588.575, 715.746, 839.974,
    -101.096, -140.645, -134.386, -87.6194, -39.1290, -4.10315, 30.2441, 69.7100, 117.038, 175.238, 246.825, 335.346, 434.493, 550.591, 680.201,
    -86.6940, -124.024, -118.310, -77.3300, -40.0154, -16.4167, 5.01311, 28.6604, 56.5516, 90.8665, 133.684, 188.134, 251.718, 330.615, 426.075,
    -71.8561, -106.095, -100.292, -64.0186, -34.8708, -18.6888, -5.17280, 9.01036, 25.2899, 45.0918, 69.7909, 101.462, 139.029, 186.725, 246.296,
    -53.7063, -83.1427, -77.0114, -46.4598, -25.3819, -15.2923, -7.65954, -0.147031, 8.15574, 18.0607, 30.3246, 46.0632, 64.8572, 88.9947, 119.643,
    -26.6711, -46.1564, -40.4451, -21.1457, -10.9149, -6.92872, -4.27491, -1.87373, 0.648692, 3.57891, 7.16655, 11.7621, 17.2710, 24.4002, 33.5513,
    4.71107, 13.1654, 9.39891, 3.48526, 1.61632, 1.03974, 0.692988, 0.396089, 0.0923087, -0.257699, -0.686892, -1.24009, -1.90856, -2.78119, -3.91169
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 7.12000,

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
"TiltCylExtThresholdStrict" => 97.7037,

# Used to determine if the bucket is near the end of tilt cylinder extension.
# Used to determine fully racked and partial dump status. Fully Racked = ((Cyl%
# > This Value) OR (ABC% > Y)) AND (Bucket Angle > Z). Partial Dump = (Cyl% <=
# This Value) AND (ABC% <= Y) AND (Bucket Angle <= Z)
"TiltCylExtThreshold" => 80.0000,

# Used to determine if the tilt angle is near the rack stops. Used to determine
# fully racked and partial dump status. Fully Racked = ((Cyl% > X) OR (ABC% >
# This Value)) AND (Bucket Angle > Z). Partial Dump = (Cyl% <= X) AND (ABC% <=
# This Value) AND (Bucket Angle <= Z)
"TiltAngleABCThreshold" => 90.0000,

}

MachineType = {
  "InternalMsn" => "CAT66300",
  "Make" => "CAT",
  "Model" => "966GC",
  "ModelDetail" => "966GC",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}
