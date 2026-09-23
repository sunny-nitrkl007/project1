##
## CAT 972H - High Lift
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
"outLiftPresNoBucket" => [1456.98, 1507.73, 1558.39, 1609.12, 1659.80, 1710.32, 1760.82, 1811.10, 1861.29, 1911.26, 1960.83, 2010.10, 2058.78, 2106.52, 2152.93, 2196.61, 2233.89],

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
"TiltCylBoreDia" => 196.850,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 95.2500,

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
"LoaderBktPayldTrgtWt" => 7.83200,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 11.0000,

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
"KgPerLiftKpaAtMidExtension" => 0.741830,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1861.30,

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
"LiftCylExtPctAxis" => [0.00000, 10.5642, 27.3709, 51.7407, 63.8655, 71.7887, 77.6711, 82.3529, 86.1945, 89.4358, 92.1969, 94.5978, 96.6387, 98.4394, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 5.78662, 11.3924, 16.4557, 20.9765, 25.1356, 28.9331, 32.5497, 35.9855, 39.2405, 42.3146, 45.2080, 47.9204, 50.8137, 54.2495, 60.5787, 68.5353, 76.3110, 86.2568, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    296.183, -28.3422, -80.4550, 109.470, 15.2049, -187.166, -447.548, -868.264, -3060.73, -4206.35, -4930.36, -5458.43, -5871.19, -6223.89, -6527.13,
    -83.0840, -200.012, -127.670, 203.015, 283.507, 87.0403, -182.830, -466.741, -831.368, -1524.70, -2534.88, -3561.00, -4474.61, -5287.36, -5992.09,
    -242.065, -253.540, -153.999, 190.384, 441.411, 452.232, 196.265, -140.352, -460.051, -812.637, -1313.54, -2583.16, -4026.37, -5457.19, -6736.18,
    -278.112, -260.559, -168.046, 135.635, 430.479, 633.192, 604.535, 306.289, -85.9579, -450.597, -815.087, -1269.59, -2011.04, -6185.94, -9234.96,
    -276.473, -254.142, -174.945, 81.3141, 356.034, 626.422, 798.057, 734.553, 400.163, -40.2995, -447.339, -839.743, -1276.36, -1902.71, -3267.92,
    -264.327, -244.061, -177.630, 36.9104, 273.617, 541.211, 799.402, 947.247, 851.780, 482.327, 1.68846, -450.763, -864.037, -1314.50, -1891.69,
    -250.008, -233.444, -177.629, 3.52780, 202.575, 441.166, 711.191, 961.576, 1083.43, 950.941, 545.953, 23.7308, -457.032, -907.102, -1373.18,
    -235.560, -222.853, -175.858, -21.7461, 143.973, 347.125, 595.567, 872.253, 1114.79, 1213.53, 1048.23, 605.767, 59.6188, -465.465, -946.526,
    -221.880, -212.661, -172.855, -40.3619, 97.6559, 267.220, 482.719, 745.376, 1027.79, 1263.80, 1339.59, 1140.00, 676.215, 90.3623, -469.082,
    -209.244, -203.007, -169.018, -53.7505, 61.8774, 202.526, 384.401, 617.016, 893.468, 1182.78, 1410.13, 1461.99, 1236.15, 737.972, 124.240,
    -197.687, -193.928, -164.639, -63.1272, 34.6112, 151.428, 303.237, 502.508, 752.740, 1044.73, 1338.45, 1557.13, 1583.31, 1323.89, 799.597,
    -187.155, -185.425, -159.937, -69.4648, 14.0234, 111.592, 238.056, 406.264, 624.298, 894.651, 1200.45, 1499.89, 1701.48, 1700.39, 1408.79,
    -177.567, -177.483, -155.077, -73.5216, -1.40122, 80.7542, 186.453, 327.815, 514.458, 754.411, 1044.29, 1366.58, 1660.51, 1847.82, 1814.03,
    -167.614, -169.029, -149.461, -76.1188, -14.2950, 53.9400, 140.656, 256.687, 411.656, 615.877, 873.811, 1184.19, 1513.21, 1817.61, 2003.40,
    -156.105, -158.989, -142.268, -77.2266, -25.5658, 29.0587, 97.1257, 187.763, 309.562, 472.897, 685.991, 957.115, 1273.24, 1622.56, 1950.40,
    -135.554, -140.359, -127.683, -74.7610, -37.2721, -1.14937, 41.7005, 97.6007, 172.555, 274.340, 410.980, 593.767, 824.961, 1116.66, 1460.80,
    -110.289, -116.306, -107.089, -65.5225, -40.1129, -18.8078, 4.39146, 33.3692, 71.5327, 123.239, 193.326, 289.155, 414.884, 582.808, 798.831,
    -85.3530, -91.4732, -84.5153, -51.9110, -34.6473, -22.2364, -10.1440, 4.04106, 22.1747, 46.4696, 79.3737, 124.643, 184.773, 266.655, 375.028,
    -51.4116, -56.2132, -51.4823, -30.2019, -20.8725, -15.4434, -11.0437, -6.46306, -0.940080, 6.30422, 16.0892, 29.6299, 47.7961, 72.8531, 106.549,
    5.96771, 6.76825, 5.84160, 2.77716, 1.84060, 1.44785, 1.22226, 1.04538, 0.860397, 0.623244, 0.292461, -0.187101, -0.859748, -1.82396, -3.16376
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 7.83200,

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
  "InternalMsn" => "CAT72001",
  "Make" => "CAT",
  "Model" => "972H",
  "ModelDetail" => "972H",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
