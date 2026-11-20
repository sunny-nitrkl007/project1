##
## CAT 962z - High Lift
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-35.6700, 49.2200],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-35.6700, -31.6600, -27.6600, -23.6500, -19.6200, -15.5300, -11.3800, -7.15000, -3.00000, 1.65000, 6.28000, 11.1100, 16.1800, 21.5600, 27.3500, 33.6900, 40.8200, 49.2200],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1388.00, 1435.10, 1482.10, 1529.20, 1576.20, 1623.30, 1670.40, 1717.40, 1762.50, 1811.50, 1858.60, 1905.70, 1952.70, 1999.80, 2046.80, 2093.90, 2140.90, 2188.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0854030, 0.0849846, 0.0850032, 0.0854188, 0.0862116, 0.0873869, 0.0889586, 0.0909617, 0.0933394, 0.0965264, 0.100307, 0.104985, 0.110839, 0.118329, 0.128235, 0.141985, 0.162598, 0.198076],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1708.31, 1748.47, 1788.66, 1828.81, 1868.53, 1907.78, 1946.25, 1983.62, 2018.27, 2054.21, 2086.59, 2116.23, 2142.16, 2163.11, 2176.71, 2178.91, 2161.25, 2101.70],

# deg/s^2
"outLiftAngleAccel" => [-0.0893035, -0.0259796, 0.0301484, 0.0824673, 0.133541, 0.186016, 0.242044, 0.304317, 0.372970, 0.462420, 0.569628, 0.708232, 0.895077, 1.16063, 1.56455, 2.23761, 3.52530, 6.66102],

# mm/s
"liftRefVel" => 80.0000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 3201.00,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-35.6700, 49.2200],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1388.00, 2188.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 3.32799, 9.77188, 16.2158, 22.6596, 29.1035, 35.5505, 41.9974, 48.4413, 54.8821, 61.3260, 67.7760, 74.2214, 80.6607, 87.1092, 93.5531, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [2.39000, 8.92000, 24.0300, 39.9100, 54.9200, 68.4900, 80.5800, 91.3500, 101.030, 109.860, 118.070, 125.880, 133.490, 141.150, 149.230, 158.360, 170.470],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [2.39000, 8.92000, 24.0300, 39.9100, 54.9200, 68.4900, 80.5800, 91.3500, 101.030, 109.860, 118.070, 125.880, 133.490, 141.150, 149.230, 158.360, 170.470],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-35.6700, -31.4000, -27.1600, -22.8900, -18.5900, -14.2400, -9.80000, -5.26000, -0.590000, 4.23000, 9.27000, 14.5600, 20.1800, 26.2300, 32.8600, 40.3400, 49.2200],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1259.21, 1261.33, 1266.03, 1273.31, 1283.14, 1295.52, 1310.55, 1328.23, 1348.65, 1371.85, 1398.14, 1427.62, 1460.66, 1497.74, 1539.58, 1587.51, 1644.31,
    1279.00, 1281.50, 1286.50, 1294.00, 1304.10, 1316.70, 1332.00, 1349.80, 1370.40, 1393.90, 1420.30, 1449.90, 1483.10, 1520.20, 1562.10, 1610.10, 1666.80,
    1319.30, 1322.30, 1327.80, 1335.80, 1346.30, 1359.40, 1375.00, 1393.20, 1414.10, 1437.80, 1464.50, 1494.30, 1527.60, 1564.90, 1606.80, 1654.80, 1711.50,
    1361.60, 1365.00, 1370.90, 1379.30, 1390.20, 1403.60, 1419.50, 1438.00, 1459.10, 1483.00, 1509.90, 1539.90, 1573.30, 1610.70, 1652.70, 1700.70, 1757.40,
    1405.50, 1409.20, 1415.50, 1424.20, 1435.40, 1449.00, 1465.20, 1483.90, 1505.20, 1529.30, 1556.30, 1586.40, 1619.90, 1657.30, 1699.40, 1747.40, 1804.00,
    1450.70, 1454.80, 1461.30, 1470.20, 1481.60, 1495.40, 1511.80, 1530.60, 1552.10, 1576.30, 1603.30, 1633.50, 1667.10, 1704.60, 1746.70, 1794.70, 1851.30,
    1497.00, 1501.20, 1507.90, 1517.00, 1528.60, 1542.50, 1559.00, 1577.90, 1599.50, 1623.70, 1650.90, 1681.10, 1714.70, 1752.20, 1794.30, 1842.30, 1898.90,
    1544.00, 1548.40, 1555.20, 1564.40, 1576.00, 1590.10, 1606.60, 1625.60, 1647.20, 1671.40, 1698.60, 1728.80, 1762.50, 1800.00, 1842.10, 1890.10, 1946.70,
    1591.40, 1595.90, 1602.80, 1612.10, 1623.70, 1637.80, 1654.30, 1673.30, 1694.90, 1719.20, 1746.30, 1776.50, 1810.10, 1847.60, 1889.70, 1937.80, 1994.30,
    1639.10, 1643.60, 1650.60, 1659.80, 1671.50, 1685.50, 1702.00, 1721.00, 1742.50, 1766.80, 1793.90, 1824.00, 1857.60, 1896.20, 1937.10, 1985.20, 2041.80,
    1686.90, 1691.40, 1698.20, 1707.50, 1719.10, 1733.00, 1749.50, 1768.40, 1789.80, 1814.00, 1841.00, 1871.10, 1904.60, 1942.00, 1984.10, 2032.10, 2088.70,
    1734.50, 1738.90, 1745.70, 1754.80, 1766.30, 1780.20, 1796.50, 1815.30, 1836.60, 1860.70, 1887.60, 1917.60, 1951.10, 1988.40, 2030.40, 2078.40, 2135.10,
    1781.70, 1786.00, 1792.60, 1801.60, 1813.00, 1826.80, 1842.90, 1861.60, 1882.80, 1906.70, 1933.50, 1963.40, 1996.80, 2034.00, 2076.00, 2124.00, 2180.70,
    1828.40, 1832.50, 1839.00, 1847.90, 1859.10, 1872.60, 1888.60, 1907.10, 1928.20, 1951.90, 1978.60, 2008.40, 2041.60, 2078.80, 2120.70, 2168.70, 2225.40,
    1874.40, 1878.40, 1884.70, 1893.30, 1904.30, 1917.70, 1933.50, 1951.80, 1972.60, 1996.20, 2022.70, 2052.30, 2085.40, 2122.50, 2164.30, 2212.30, 2269.10,
    1919.60, 1923.40, 1929.40, 1937.90, 1948.60, 1961.80, 1977.30, 1995.40, 2016.00, 2039.40, 2065.70, 2095.20, 2128.10, 2165.10, 2206.80, 2254.80, 2311.60,
    1963.90, 1967.40, 1973.20, 1981.40, 1991.90, 2004.80, 2020.10, 2037.90, 2058.30, 2081.50, 2107.50, 2136.80, 2169.60, 2206.40, 2248.10, 2296.00, 2352.80
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [2.39000, 170.470],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-89.5900, 78.4900],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [2.39000, 170.470],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1488.00, 2033.00],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 140.000,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 85.0000,

##
## Tilt Cylinders
##

# Number of tilt cylinders.
"NoOfTiltCyls" => 1,

# Tilt cylinder bore diameter, in mm.
"TiltCylBoreDia" => 158.800,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 82.5000,

##
## Tool
##

# Tool's length between B and C pins, in mm.
"ToolBcLen" => 433.260,

# Tool's angle between line BC and tool's X-axis, in deg.
"ToolBcAngle" => 91.9840,

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
"LoaderBktPayldTrgtWt" => 5.42900,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 7.50000,

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_MWL.json",

# Determines whether or not payload legal for trade is supported.
"LegalForTradeSupported" => true,

# Determines whether or not acceleration compensation is supported for this
# machine configuration
"AccelCompSupported" => true,

# This selects the application number used for selecting the cycle segmentation
# data.
"CycleSegAppNumber" => 6200,

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
"KgPerLiftKpaAtMidExtension" => 0.593271,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 2032.90,

##
## Temperature Compensation
##

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylHeLineLoss2ndOrdrCoeff" => 1.04892E-06,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3.
"LiftCylHeLineLoss1stOrdrCoeff" => 3.86759,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylReLineLoss2ndOrdrCoeff" => 5.60694E-06,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3
"LiftCylReLineLoss1stOrdrCoeff" => 4.40827,

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
"LiftCylExtPctAxis" => [0.00000, 15.1250, 34.5000, 52.6250, 65.5000, 72.3750, 77.5000, 81.7500, 85.5000, 88.7500, 91.6250, 94.1250, 96.3750, 98.3750, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 5.13761, 9.90826, 14.3119, 18.3486, 22.0183, 25.5046, 28.8073, 31.9266, 35.0459, 38.1651, 41.6514, 45.8716, 51.7431, 61.8349, 70.6422, 79.2661, 87.7064, 95.6330, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -109.994, -88.0297, 42.1068, 234.075, 362.398, 361.563, 278.409, 130.091, -63.0828, -268.734, -476.301, -680.895, -893.516, -1116.90, -1333.85,
    -128.127, -106.788, 16.6106, 209.670, 379.147, 439.798, 426.515, 339.755, 180.310, -26.1170, -252.870, -477.358, -703.462, -932.225, -1147.46,
    -141.226, -121.493, -6.57017, 177.931, 363.605, 463.120, 506.552, 488.397, 396.246, 232.106, 12.9886, -227.488, -476.098, -723.121, -948.416,
    -150.463, -132.605, -26.2377, 145.571, 331.725, 450.697, 530.855, 566.905, 544.000, 448.938, 279.198, 54.8487, -204.508, -473.582, -718.189,
    -156.764, -140.710, -42.2090, 115.935, 294.183, 419.478, 519.409, 590.950, 621.786, 593.861, 493.927, 322.578, 87.1680, -186.300, -448.263,
    -160.853, -146.390, -54.7796, 90.3465, 257.059, 380.992, 489.035, 580.608, 647.131, 670.869, 636.118, 532.151, 352.425, 108.152, -151.408,
    -163.407, -150.350, -64.9187, 67.9182, 221.504, 339.806, 448.822, 550.054, 638.526, 698.807, 716.610, 677.056, 566.713, 381.217, 154.289,
    -164.712, -152.860, -72.8934, 48.7018, 188.952, 299.405, 404.963, 508.666, 608.486, 691.821, 747.161, 759.443, 714.334, 598.860, 428.448,
    -165.009, -154.164, -78.9905, 32.5182, 160.013, 261.741, 361.370, 462.962, 566.681, 662.611, 742.164, 791.790, 799.121, 748.585, 642.072,
    -164.443, -154.473, -83.7333, 18.2948, 133.295, 225.689, 317.766, 414.219, 516.811, 618.043, 712.048, 787.454, 834.901, 839.492, 794.493,
    -163.050, -153.819, -87.1700, 6.02118, 109.059, 191.989, 275.630, 364.978, 462.856, 563.795, 664.224, 755.063, 830.049, 876.471, 882.829,
    -160.545, -151.984, -89.5304, -5.45305, 85.0473, 157.654, 231.495, 311.603, 401.463, 497.392, 597.789, 695.918, 788.523, 865.841, 914.074,
    -156.207, -148.245, -90.3996, -16.3300, 60.3231, 121.198, 183.377, 251.649, 329.746, 415.531, 508.995, 605.711, 705.103, 800.726, 878.562,
    -147.797, -140.320, -88.2067, -26.4070, 33.4568, 79.8635, 127.163, 179.505, 240.344, 308.829, 386.047, 469.751, 561.428, 658.019, 747.504,
    -126.470, -119.090, -75.8900, -31.8512, 5.17830, 32.0700, 58.9166, 88.5293, 123.241, 163.044, 209.205, 261.202, 321.109, 388.562, 456.426,
    -99.1385, -91.5435, -56.8099, -26.6120, -4.77471, 9.88074, 24.0481, 39.4467, 57.4126, 78.0656, 102.219, 129.796, 162.163, 199.496, 238.148,
    -60.0316, -53.1683, -30.6028, -14.6561, -4.98216, 0.926976, 6.40862, 12.2386, 18.9658, 26.6675, 35.6829, 46.0241, 58.2575, 72.5237, 87.4900,
    6.24197, 4.89107, 2.34141, 1.06989, 0.444618, 0.0988385, -0.208469, -0.527859, -0.891778, -1.30588, -1.78972, -2.34532, -3.00474, -3.77767, -4.59374,
    68.3291, 37.7172, 33.1424, 14.3833, 6.45845, 2.27491, -1.38345, -5.15782, -9.44544, -14.3219, -20.0258, -26.5893, -34.4013, -43.5898, -53.3284,
    103.144, 52.1111, -35.0150, 15.2606, 7.54620, 2.67168, -1.80342, -6.53218, -11.9793, -18.2293, -25.5829, -34.0809, -44.2289, -56.1985, -68.9148
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 5.42900,

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
"TiltCylExtThresholdStrict" => 86.1560,

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
  "InternalMsn" => "CAT62709",
  "Make" => "CAT",
  "Model" => "962z",
  "ModelDetail" => "962z",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}
