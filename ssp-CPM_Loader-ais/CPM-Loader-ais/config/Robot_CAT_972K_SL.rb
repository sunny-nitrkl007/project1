##
## CAT 972K - Short Lift
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
"BMI_CDL_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiCdl_MWL-K-L.json",

# The BMI J1939 configuration file.
"BMI_J1939_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiJ1939_MWL_SA.json",

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_MWL.json",

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
"KgPerLiftKpaAtMidExtension" => 0.850701,

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
"LiftCylExtPctAxis" => [0.00000, 13.2053, 27.1309, 45.0180, 60.3842, 69.0276, 75.1501, 80.1921, 84.3938, 87.9952, 91.1164, 93.8776, 96.1585, 98.1993, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 5.92593, 11.1111, 15.9259, 20.3704, 24.4444, 28.3333, 32.0370, 35.5556, 38.8889, 42.0370, 45.1852, 48.5185, 52.5926, 58.8889, 67.5926, 75.1852, 82.9630, 92.0370, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -87.2380, -147.204, -106.757, 49.0280, 212.255, 242.144, 179.558, 56.4028, -95.8097, -263.175, -443.590, -644.351, -856.469, -1104.33, -1400.25,
    -120.384, -167.447, -126.822, 25.7987, 221.242, 319.262, 327.058, 251.020, 113.306, -58.3602, -246.073, -448.199, -652.312, -879.865, -1137.81,
    -136.513, -178.723, -141.556, 0.245856, 199.185, 334.972, 405.155, 398.701, 310.592, 158.446, -30.9951, -241.641, -450.835, -676.269, -922.169,
    -144.545, -185.181, -152.424, -23.4675, 164.853, 314.095, 424.257, 482.291, 464.459, 365.448, 200.277, -8.99139, -225.824, -458.280, -705.312,
    -147.958, -188.463, -159.982, -43.3285, 128.819, 276.135, 404.024, 505.208, 551.990, 523.473, 413.426, 232.392, 20.3198, -218.096, -472.434,
    -148.707, -189.634, -164.898, -59.0242, 96.1321, 234.014, 364.618, 487.446, 579.149, 615.209, 574.716, 449.757, 266.842, 36.8882, -220.971,
    -147.855, -189.379, -167.906, -71.5027, 67.2477, 192.469, 317.326, 446.703, 564.085, 648.647, 675.020, 622.035, 494.072, 297.512, 51.9143,
    -145.948, -188.061, -169.354, -81.0867, 42.7592, 154.592, 269.445, 395.656, 523.040, 637.022, 714.994, 731.833, 672.904, 534.534, 326.016,
    -143.344, -185.952, -169.547, -88.1841, 22.5673, 121.614, 224.926, 342.674, 469.494, 596.786, 707.630, 779.736, 787.916, 720.687, 572.573,
    -140.287, -183.261, -168.746, -93.2060, 6.25592, 93.7270, 185.517, 292.510, 412.642, 541.949, 669.345, 778.259, 840.529, 842.275, 766.324,
    -136.945, -180.149, -167.169, -96.5302, -6.70198, 70.6021, 151.679, 247.439, 357.916, 482.354, 614.445, 743.566, 843.136, 901.247, 895.222,
    -133.212, -176.519, -164.844, -98.5751, -17.4101, 50.5990, 121.528, 205.897, 305.061, 420.399, 549.270, 686.288, 808.663, 908.827, 964.016,
    -128.868, -172.136, -161.613, -99.4512, -26.4701, 32.6893, 93.7294, 166.494, 253.108, 356.274, 476.014, 611.144, 743.604, 871.017, 974.429,
    -123.048, -166.051, -156.640, -98.8708, -34.6502, 15.0409, 65.3464, 125.108, 196.818, 283.861, 388.114, 511.612, 641.617, 780.986, 917.404,
    -112.987, -155.085, -146.831, -94.7687, -41.8369, -4.15202, 32.4796, 75.3011, 126.709, 190.002, 267.949, 364.456, 472.679, 599.563, 741.403,
    -96.8526, -136.613, -129.057, -83.4922, -42.8987, -17.6131, 5.16543, 30.7426, 60.9409, 98.1405, 144.618, 203.797, 272.987, 358.938, 463.050,
    -80.2857, -116.760, -109.213, -68.9528, -37.3535, -20.0882, -5.77209, 9.51817, 27.0854, 48.4824, 75.2095, 109.530, 150.293, 202.109, 266.900,
    -60.0604, -91.4116, -83.6606, -49.8502, -27.1048, -16.3982, -8.35133, -0.287811, 8.63230, 19.2903, 32.5096, 49.5033, 69.8279, 95.9675, 129.202,
    -29.9406, -50.6766, -43.7224, -22.5035, -11.5631, -7.37488, -4.60162, -2.04533, 0.643443, 3.77400, 7.61663, 12.5508, 18.4785, 26.1640, 36.0455,
    5.43364, 14.4160, 10.0127, 3.63595, 1.68112, 1.08811, 0.732563, 0.421664, 0.102340, -0.267356, -0.722817, -1.31229, -2.02700, -2.96258, -4.17747
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
  "InternalMsn" => "CAT72203",
  "Make" => "CAT",
  "Model" => "972K",
  "ModelDetail" => "972K",
  "Linkage" => "Short Lift",
  "LinkageConfigurationNumber" => 138
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
