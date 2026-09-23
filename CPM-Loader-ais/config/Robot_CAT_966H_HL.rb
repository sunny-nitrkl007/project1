##
## CAT 966H - High Lift
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-35.5400, 52.2700],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-35.5400, -31.2500, -26.9600, -22.6500, -18.2900, -13.8800, -9.37000, -4.76000, 0.00000, 4.94000, 10.1000, 15.5400, 21.3400, 27.6200, 34.5700, 42.5300, 52.2700],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1443.00, 1495.10, 1547.10, 1599.20, 1651.30, 1703.30, 1755.40, 1807.40, 1859.50, 1911.60, 1963.60, 2015.70, 2067.80, 2119.80, 2171.90, 2223.90, 2276.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0826957, 0.0823828, 0.0825410, 0.0831323, 0.0841469, 0.0855891, 0.0875006, 0.0899296, 0.0929789, 0.0967873, 0.101565, 0.107646, 0.115575, 0.126320, 0.141774, 0.166343, 0.213965],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1436.91, 1487.97, 1538.94, 1589.99, 1641.03, 1691.93, 1742.88, 1793.68, 1844.49, 1895.21, 1945.70, 1996.10, 2046.25, 2095.92, 2145.07, 2192.95, 2238.07],

# deg/s^2
"outLiftAngleAccel" => [-0.0759097, -0.00916495, 0.0504952, 0.106904, 0.163322, 0.222407, 0.287695, 0.362682, 0.452931, 0.566094, 0.714272, 0.918243, 1.21635, 1.68767, 2.52094, 4.28137, 9.54221],

# mm/s
"liftRefVel" => 83.3000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 3340.00,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-35.5400, 52.2700],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1443.00, 2276.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 5.59252, 9.54864, 13.1271, 16.6697, 20.3740, 24.3481, 28.7538, 33.6990, 39.3814, 45.9450, 53.5335, 62.2370, 71.8756, 81.9817, 91.6921, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [5.27000, 15.8100, 26.3400, 36.8800, 47.4200, 57.9600, 68.5000, 79.0300, 89.5700, 100.110, 110.650, 121.190, 131.720, 142.260, 152.800, 163.340, 173.880],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [5.27000, 15.8100, 26.3400, 36.8800, 47.4200, 57.9600, 68.5000, 79.0300, 89.5700, 100.110, 110.650, 121.190, 131.720, 142.260, 152.800, 163.340, 173.880],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-35.5400, -31.2500, -26.9600, -22.6500, -18.2900, -13.8800, -9.37000, -4.76000, 0.00000, 4.94000, 10.1000, 15.5400, 21.3400, 27.6200, 34.5700, 42.5300, 52.2700],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1226.07, 1214.75, 1206.01, 1199.94, 1196.64, 1196.26, 1198.93, 1204.84, 1214.22, 1227.32, 1244.45, 1266.02, 1292.57, 1324.91, 1364.29, 1412.95, 1475.86,
    1241.83, 1231.27, 1223.32, 1218.06, 1215.58, 1216.01, 1219.52, 1226.24, 1236.42, 1250.29, 1268.16, 1290.43, 1317.63, 1350.56, 1390.45, 1439.52, 1502.71,
    1254.90, 1244.90, 1237.50, 1232.70, 1230.80, 1231.80, 1235.90, 1243.20, 1253.90, 1268.20, 1286.60, 1309.30, 1336.90, 1370.30, 1410.50, 1459.90, 1523.20,
    1268.00, 1258.40, 1251.50, 1247.20, 1245.80, 1247.30, 1251.80, 1259.60, 1270.70, 1285.50, 1304.30, 1327.40, 1355.40, 1389.00, 1429.50, 1479.10, 1542.60,
    1282.00, 1272.90, 1266.40, 1262.60, 1261.70, 1263.60, 1268.60, 1276.80, 1288.30, 1303.60, 1322.70, 1346.20, 1374.50, 1408.40, 1449.10, 1498.90, 1562.50,
    1297.80, 1289.10, 1283.00, 1279.70, 1279.20, 1281.60, 1287.00, 1295.60, 1307.60, 1323.20, 1342.70, 1366.50, 1395.10, 1429.30, 1470.30, 1520.30, 1584.00,
    1315.90, 1307.70, 1302.10, 1299.20, 1299.10, 1302.00, 1307.80, 1316.80, 1329.20, 1345.20, 1365.10, 1389.30, 1418.20, 1452.60, 1493.90, 1544.00, 1607.80,
    1337.30, 1329.50, 1324.40, 1322.00, 1322.40, 1325.70, 1332.00, 1341.40, 1354.20, 1370.60, 1390.90, 1415.30, 1444.60, 1479.30, 1520.70, 1571.00, 1635.00,
    1362.90, 1355.60, 1351.00, 1349.10, 1350.00, 1353.70, 1360.50, 1370.40, 1383.60, 1400.40, 1421.00, 1445.80, 1475.30, 1510.30, 1552.00, 1602.40, 1666.50,
    1394.20, 1387.40, 1383.20, 1381.80, 1383.20, 1387.40, 1394.60, 1405.00, 1418.60, 1435.80, 1456.70, 1481.90, 1511.70, 1546.90, 1588.80, 1639.40, 1703.50,
    1432.40, 1426.20, 1422.50, 1421.60, 1423.50, 1428.20, 1435.80, 1446.60, 1460.70, 1478.20, 1499.50, 1525.00, 1555.10, 1590.50, 1632.60, 1683.40, 1747.60,
    1479.30, 1473.50, 1470.40, 1469.90, 1472.30, 1477.40, 1485.50, 1496.70, 1511.10, 1529.00, 1550.60, 1576.30, 1606.70, 1642.40, 1684.60, 1735.50, 1799.70,
    1535.60, 1530.20, 1527.60, 1527.60, 1530.30, 1535.80, 1544.30, 1555.80, 1570.50, 1588.70, 1610.60, 1636.50, 1667.10, 1702.90, 1745.30, 1796.30, 1860.50,
    1600.50, 1595.60, 1593.30, 1593.60, 1596.70, 1602.50, 1611.20, 1623.00, 1637.90, 1656.30, 1678.30, 1704.40, 1735.00, 1771.00, 1813.40, 1864.40, 1928.70,
    1670.60, 1665.90, 1663.80, 1664.40, 1667.60, 1673.60, 1682.50, 1694.30, 1709.40, 1727.80, 1749.90, 1776.00, 1806.70, 1842.60, 1885.00, 1936.10, 2000.40,
    1739.10, 1734.50, 1732.50, 1733.10, 1736.40, 1742.40, 1751.30, 1763.20, 1778.20, 1796.60, 1818.70, 1844.70, 1875.30, 1911.20, 1953.50, 2004.50, 2068.80,
    1798.00, 1793.40, 1791.40, 1792.00, 1795.30, 1801.30, 1810.10, 1821.90, 1836.80, 1855.10, 1877.00, 1903.00, 1933.40, 1969.20, 2011.40, 2062.30, 2126.60
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [5.27000, 173.880],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-96.4300, 72.1800],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [5.27000, 173.880],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1245.00, 1798.00],

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
"TiltCylRodDia" => 82.5500,

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
"LoaderBktPayldTrgtWt" => 7.70300,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 10.5000,

# The CAT datalink configuration file.
"BMI_CDL_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiCdl_MWL_H.json",

# The BMI J1939 configuration file.
"BMI_J1939_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiJ1939_MWL_SA.json",

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_MWL.json",

# Determines whether or not hydraulic oil temperature is optional for this
# machine configuration.
"HydOilTempOptional" => true,

# Determines whether or not hydraulic oil temperature enabled by default for
# this machine configuration.
"HydOilTempEnabledDefault" => false,

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
"KgPerLiftKpaAtMidExtension" => 0.739992,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1844.50,

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
"LiftCylExtPctAxis" => [0.00000, 10.4442, 26.8908, 51.2605, 63.6255, 71.6687, 77.6711, 82.3529, 86.1945, 89.4358, 92.1969, 94.5978, 96.6387, 98.4394, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 5.78662, 11.3924, 16.4557, 20.9765, 25.1356, 28.9331, 32.5497, 35.9855, 39.2405, 42.3146, 45.2080, 47.9204, 50.8137, 54.2495, 60.3978, 68.5353, 76.3110, 86.0759, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    307.811, -3.61498, -67.9335, 101.285, 20.0089, -163.295, -406.609, -798.470, -2846.67, -3917.06, -4593.42, -5086.58, -5471.94, -5801.18, -6084.23,
    -52.8490, -171.300, -115.858, 184.105, 263.948, 85.2789, -164.896, -426.318, -765.959, -1415.48, -2361.88, -3323.41, -4179.59, -4941.25, -5601.70,
    -208.703, -226.097, -141.926, 171.890, 408.610, 421.091, 181.334, -127.393, -422.073, -750.338, -1219.92, -2413.41, -3770.70, -5116.52, -6319.58,
    -246.861, -235.301, -155.620, 121.916, 398.956, 589.704, 560.991, 283.175, -78.3585, -415.137, -754.507, -1180.71, -1878.73, -5811.04, -8682.88,
    -248.009, -230.876, -162.361, 72.3623, 330.787, 585.112, 745.982, 682.725, 370.452, -36.9957, -413.808, -779.450, -1189.04, -1779.24, -3067.99,
    -238.414, -222.508, -165.081, 31.7745, 254.968, 507.255, 751.696, 885.977, 792.654, 447.017, 1.13781, -418.658, -804.152, -1226.96, -1771.23,
    -226.243, -213.334, -165.254, 1.18327, 189.372, 414.953, 672.044, 904.134, 1013.79, 885.670, 506.358, 20.8162, -426.177, -846.536, -1284.35,
    -213.655, -204.019, -163.759, -22.0393, 135.081, 327.730, 565.316, 823.940, 1048.27, 1135.98, 976.969, 562.090, 53.2780, -435.861, -885.757,
    -201.583, -194.963, -161.102, -39.1916, 92.0323, 253.314, 460.177, 707.049, 970.677, 1188.49, 1254.43, 1063.05, 627.661, 80.8392, -441.249,
    -190.345, -186.325, -157.655, -51.5629, 58.6723, 192.849, 368.030, 587.614, 847.158, 1116.86, 1326.17, 1369.35, 1153.20, 684.981, 111.155,
    -180.013, -178.164, -153.690, -60.2535, 33.1678, 144.932, 291.617, 480.417, 716.376, 990.200, 1263.64, 1464.36, 1483.28, 1235.29, 741.996,
    -170.561, -170.492, -149.411, -66.1472, 13.8474, 107.458, 230.017, 389.909, 596.260, 850.909, 1137.35, 1415.67, 1600.03, 1593.00, 1314.53,
    -161.932, -163.305, -144.973, -69.9356, -0.677139, 78.3585, 181.083, 315.861, 493.073, 719.906, 992.634, 1294.12, 1566.85, 1737.30, 1699.29,
    -152.952, -155.636, -139.830, -72.3772, -12.8660, 52.9718, 137.508, 248.490, 396.122, 589.868, 833.521, 1125.33, 1432.93, 1715.15, 1883.90,
    -142.544, -146.505, -133.226, -73.4430, -23.5784, 29.3173, 95.9257, 182.957, 299.451, 455.043, 657.217, 913.379, 1210.72, 1537.57, 1842.04,
    -124.430, -129.997, -120.189, -71.3311, -34.6495, 0.986012, 43.7994, 98.6561, 171.939, 271.034, 403.471, 579.797, 801.664, 1079.91, 1405.70,
    -100.910, -107.472, -100.713, -62.6089, -37.8328, -16.8686, 6.25428, 34.6160, 71.8174, 121.990, 189.692, 281.873, 402.347, 562.670, 768.198,
    -78.1472, -84.6355, -79.7049, -49.8273, -32.9138, -20.5873, -8.38081, 5.70230, 23.6343, 47.5283, 79.7103, 123.758, 181.994, 260.967, 365.095,
    -47.6856, -52.7314, -49.3837, -29.6367, -20.3067, -14.7455, -10.1109, -5.32652, 0.433755, 7.93710, 17.9876, 31.7844, 50.1628, 75.3557, 109.052,
    5.45659, 6.28316, 5.59692, 2.74992, 1.80944, 1.40177, 1.15501, 0.957470, 0.749046, 0.486588, 0.129734, -0.375702, -1.07153, -2.05451, -3.40477
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 7.70300,

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
"TiltCylExtThresholdStrict" => 97.7342,

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
  "InternalMsn" => "CAT66001",
  "Make" => "CAT",
  "Model" => "966H",
  "ModelDetail" => "966H",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
