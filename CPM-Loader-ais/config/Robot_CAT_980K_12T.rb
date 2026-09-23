##
## CAT 980K - 12 Ton
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-40.6100, 44.4400],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-40.6100, -35.0000, -30.0000, -25.0000, -20.0000, -15.0000, -10.0000, -5.00000, 0.00000, 5.00000, 10.0000, 15.0000, 20.0000, 25.0000, 30.0000, 35.0000, 40.0000, 44.4400],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1504.00, 1576.00, 1640.00, 1703.00, 1766.00, 1827.00, 1887.00, 1944.00, 2000.00, 2053.00, 2104.00, 2151.00, 2196.00, 2238.00, 2276.00, 2311.00, 2343.00, 2368.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0781802, 0.0779461, 0.0783572, 0.0792994, 0.0807505, 0.0827110, 0.0852019, 0.0882651, 0.0919654, 0.0963951, 0.101681, 0.107996, 0.115578, 0.124757, 0.136001, 0.149994, 0.167777, 0.188056],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1251.72, 1322.15, 1384.79, 1446.67, 1508.94, 1569.76, 1630.28, 1688.62, 1746.99, 1803.49, 1859.42, 1912.82, 1966.29, 2019.17, 2070.76, 2123.21, 2178.06, 2228.90],

# deg/s^2
"outLiftAngleAccel" => [-0.0661783, 0.0153020, 0.0798336, 0.141882, 0.205431, 0.274198, 0.352138, 0.443948, 0.555678, 0.695593, 0.875504, 1.11295, 1.43493, 1.88465, 2.53426, 3.51041, 5.04917, 7.25973],

# mm/s
"liftRefVel" => 86.4000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 3240.00,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-40.6100, 44.4400],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1504.00, 2368.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 6.24399, 12.4910, 18.7503, 24.9973, 31.2566, 37.5006, 43.6133, 49.8878, 56.1624, 62.4369, 68.7114, 74.9889, 81.2482, 87.5227, 93.7819, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [11.3400, 19.0100, 32.7600, 50.0400, 67.2900, 82.6400, 95.7200, 106.610, 116.270, 124.770, 132.480, 139.670, 146.610, 153.590, 161.000, 169.510, 181.340],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [11.3400, 19.0100, 32.7600, 50.0400, 67.2900, 82.6400, 95.7200, 106.610, 116.270, 124.770, 132.480, 139.670, 146.610, 153.590, 161.000, 169.510, 181.340],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-40.6100, -35.2900, -29.9800, -24.6600, -19.3500, -14.0300, -8.72000, -3.40000, 1.92000, 7.23000, 12.5500, 17.8600, 23.1800, 28.4900, 33.8100, 39.1300, 44.4400],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1153.90, 1138.37, 1127.50, 1121.90, 1121.10, 1126.57, 1136.75, 1152.00, 1171.90, 1195.90, 1224.00, 1255.20, 1289.10, 1325.30, 1363.50, 1402.90, 1443.50,
    1175.10, 1160.93, 1151.60, 1147.60, 1148.80, 1155.27, 1166.86, 1183.50, 1204.50, 1229.70, 1258.50, 1290.50, 1325.20, 1362.10, 1400.70, 1440.60, 1481.30,
    1201.10, 1187.70, 1180.50, 1177.80, 1180.50, 1188.23, 1201.06, 1218.80, 1240.90, 1266.90, 1296.50, 1329.10, 1364.40, 1401.70, 1440.60, 1480.70, 1521.50,
    1231.60, 1220.00, 1213.40, 1212.10, 1216.00, 1224.30, 1238.50, 1257.50, 1280.40, 1307.20, 1337.50, 1370.60, 1406.30, 1443.90, 1483.10, 1523.30, 1564.30,
    1265.90, 1255.50, 1250.10, 1249.90, 1254.90, 1264.90, 1279.70, 1299.20, 1322.80, 1349.00, 1379.80, 1413.40, 1449.50, 1487.40, 1526.80, 1567.20, 1608.20,
    1303.80, 1294.40, 1290.00, 1290.80, 1296.60, 1307.40, 1321.90, 1342.10, 1366.30, 1394.20, 1425.50, 1459.50, 1495.70, 1533.90, 1573.40, 1613.90, 1655.00,
    1344.70, 1336.10, 1332.60, 1333.00, 1339.60, 1351.30, 1367.50, 1388.20, 1413.00, 1441.30, 1472.90, 1507.10, 1543.60, 1581.90, 1621.50, 1662.10, 1703.10,
    1387.00, 1379.20, 1376.40, 1378.60, 1385.90, 1398.10, 1414.80, 1436.00, 1461.10, 1489.70, 1521.50, 1555.90, 1592.50, 1630.90, 1670.60, 1711.20, 1752.40,
    1432.50, 1425.30, 1423.10, 1425.90, 1433.70, 1446.30, 1463.40, 1484.80, 1510.20, 1539.00, 1571.00, 1605.50, 1642.20, 1680.70, 1720.40, 1761.10, 1802.10,
    1479.90, 1473.10, 1471.30, 1474.60, 1482.60, 1495.40, 1512.90, 1534.50, 1560.00, 1588.90, 1621.00, 1655.60, 1692.30, 1730.90, 1770.60, 1811.20, 1852.40,
    1528.50, 1522.00, 1520.50, 1524.00, 1532.30, 1545.30, 1562.90, 1584.60, 1610.10, 1639.10, 1671.10, 1705.80, 1742.60, 1781.00, 1820.80, 1861.40, 1902.50,
    1577.90, 1571.70, 1570.40, 1574.00, 1582.40, 1595.50, 1613.00, 1634.80, 1660.30, 1689.30, 1721.30, 1756.00, 1792.70, 1831.10, 1870.90, 1911.40, 1952.50,
    1627.90, 1621.80, 1620.50, 1624.30, 1632.70, 1645.70, 1663.20, 1685.00, 1710.40, 1739.30, 1771.20, 1805.70, 1842.40, 1880.80, 1920.40, 1961.10, 2002.10,
    1678.00, 1672.00, 1670.80, 1674.40, 1682.70, 1695.70, 1713.10, 1734.70, 1760.10, 1788.80, 1820.60, 1855.00, 1891.50, 1929.80, 1969.40, 2010.00, 2051.10,
    1728.30, 1722.10, 1720.80, 1724.20, 1732.50, 1745.30, 1762.50, 1783.90, 1808.90, 1837.50, 1869.20, 1903.40, 1939.80, 1978.00, 2017.50, 2058.00, 2099.00,
    1778.10, 1771.90, 1770.30, 1773.70, 1781.50, 1794.20, 1811.10, 1832.10, 1857.10, 1885.40, 1916.80, 1950.90, 1987.10, 2025.20, 2064.60, 2105.10, 2146.10,
    1827.50, 1821.00, 1819.30, 1822.20, 1830.00, 1842.20, 1858.80, 1879.60, 1904.20, 1932.20, 1963.40, 1997.20, 2033.20, 2071.10, 2110.40, 2150.80, 2191.70
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [11.3400, 181.340],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-92.1100, 77.8900],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [11.3400, 181.340],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1242.00, 1824.00],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 180.000,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 90.0000,

##
## Tilt Cylinders
##

# Number of tilt cylinders.
"NoOfTiltCyls" => 2,

# Tilt cylinder bore diameter, in mm.
"TiltCylBoreDia" => 150.000,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 100.000,

##
## Tool
##

# Tool's length between B and C pins, in mm.
"ToolBcLen" => 472.969,

# Tool's angle between line BC and tool's X-axis, in deg.
"ToolBcAngle" => 103.449,

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
"LoaderBktPayldTrgtWt" => 10.4130,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 13.5000,

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
"KgPerLiftKpaAtMidExtension" => 1.04521,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1667.28,

##
## Temperature Compensation
##

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylHeLineLoss2ndOrdrCoeff" => 1.17428E-06,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3.
"LiftCylHeLineLoss1stOrdrCoeff" => 2.74818,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylReLineLoss2ndOrdrCoeff" => 1.65276E-06,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3
"LiftCylReLineLoss1stOrdrCoeff" => 2.78360,

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
"LiftCylExtPctAxis" => [0.00000, 12.9630, 30.5556, 50.8102, 62.6157, 70.2546, 76.1574, 81.0185, 85.0694, 88.5417, 91.5509, 94.0972, 96.2963, 98.2639, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 6.18557, 11.5120, 16.3230, 20.7904, 25.0859, 29.0378, 32.8179, 36.4261, 39.8625, 43.1271, 46.2199, 49.3127, 52.5773, 56.5292, 63.5739, 71.4777, 79.0378, 87.9725, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -54.4650, -136.326, -65.7520, 137.823, 190.896, 100.980, -45.1170, -215.371, -419.554, -703.100, -1227.29, -1708.40, -2141.39, -2532.99, -2878.73,
    -136.510, -165.303, -86.8845, 137.792, 292.646, 300.507, 180.876, -0.0104651, -195.583, -411.541, -678.326, -1054.35, -1822.16, -2489.59, -3095.68,
    -159.144, -173.452, -103.257, 106.235, 301.115, 409.303, 388.946, 241.712, 34.2189, -187.478, -421.760, -683.609, -1018.79, -1565.16, -3275.37,
    -162.241, -174.403, -115.061, 69.8229, 264.106, 424.257, 507.856, 461.209, 290.610, 58.1758, -187.804, -433.592, -700.339, -1032.42, -1507.34,
    -158.488, -172.401, -123.167, 37.2164, 213.673, 385.583, 531.575, 594.397, 523.571, 329.984, 74.7569, -185.281, -445.410, -729.852, -1065.66,
    -152.171, -168.941, -128.481, 9.97377, 163.360, 325.210, 492.939, 629.768, 673.938, 582.409, 368.513, 101.571, -174.294, -458.200, -759.258,
    -145.330, -164.901, -131.437, -10.7462, 120.956, 264.684, 428.647, 596.037, 720.175, 743.811, 628.538, 401.961, 122.260, -177.345, -481.788,
    -138.421, -160.492, -132.737, -26.6911, 85.8243, 209.768, 358.492, 528.633, 692.723, 805.058, 808.160, 676.686, 438.689, 138.056, -181.382,
    -131.730, -155.901, -132.758, -38.6519, 57.6501, 163.136, 292.922, 451.041, 624.694, 786.130, 885.375, 870.271, 725.642, 469.405, 151.848,
    -125.369, -151.239, -131.800, -47.4006, 35.4998, 124.927, 236.029, 376.244, 541.896, 720.027, 877.158, 960.549, 930.675, 768.627, 496.960,
    -119.373, -146.576, -130.103, -53.6073, 18.3214, 94.2527, 188.589, 309.921, 459.564, 634.232, 815.580, 962.331, 1032.49, 986.421, 807.679,
    -113.742, -141.961, -127.860, -57.8247, 5.14522, 69.9249, 149.900, 253.672, 384.970, 546.002, 729.153, 906.302, 1044.25, 1102.04, 1038.10,
    -108.153, -137.158, -125.049, -60.6194, -5.37459, 49.7625, 117.071, 204.606, 317.085, 459.561, 631.341, 815.514, 990.678, 1125.72, 1173.02,
    -102.284, -131.881, -121.513, -62.2127, -13.9638, 32.4771, 88.2482, 160.560, 254.276, 375.583, 527.804, 702.444, 888.909, 1069.72, 1205.40,
    -95.1901, -125.194, -116.501, -62.5183, -21.4011, 16.2806, 60.4060, 117.080, 190.735, 287.493, 412.581, 563.503, 738.276, 932.780, 1123.67,
    -82.4338, -112.358, -105.684, -59.3866, -28.1922, -2.30947, 26.3005, 61.9942, 107.974, 168.828, 249.432, 351.097, 477.490, 634.849, 819.992,
    -67.6010, -96.2138, -90.6786, -51.3742, -28.4494, -11.6800, 5.39779, 25.7098, 51.2580, 84.8136, 129.480, 186.785, 260.227, 356.187, 477.720,
    -52.3645, -78.3355, -73.1423, -40.1727, -23.6185, -13.0021, -3.15242, 7.89396, 21.3418, 38.7276, 61.7532, 91.3763, 129.710, 180.676, 246.999,
    -31.9483, -52.1407, -47.0760, -23.3910, -13.8362, -8.66806, -4.43278, -0.0571301, 5.02737, 11.4495, 19.8713, 30.6855, 44.7259, 63.5383, 88.3324,
    2.75426, 6.82573, 4.99655, 1.64167, 0.898166, 0.592320, 0.378432, 0.176430, -0.0492573, -0.331361, -0.702306, -1.18228, -1.81121, -2.66238, -3.79659
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 10.4130,

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
"TiltCylExtThresholdStrict" => 97.9691,

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
  "InternalMsn" => "CAT80204",
  "Make" => "CAT",
  "Model" => "980K",
  "ModelDetail" => "980K",
  "Linkage" => "12 Ton",
  "LinkageConfigurationNumber" => 136
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
