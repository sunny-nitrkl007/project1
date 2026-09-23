##
## CAT 980G - High Lift
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-38.3000, 47.0700],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-38.3000, -34.3200, -30.3500, -26.3700, -22.3400, -18.2700, -14.1300, -9.91000, -5.57000, -1.09000, 3.55000, 8.39000, 13.4900, 18.9100, 24.7500, 31.1700, 38.4300, 47.0700],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1504.00, 1554.80, 1605.70, 1656.50, 1707.30, 1758.10, 1808.90, 1859.80, 1910.60, 1961.40, 2012.20, 2063.10, 2113.90, 2164.70, 2215.50, 2266.40, 2317.20, 2368.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0783738, 0.0781196, 0.0782484, 0.0787287, 0.0795534, 0.0807220, 0.0822568, 0.0841905, 0.0865895, 0.0895386, 0.0931560, 0.0976264, 0.103243, 0.110449, 0.120019, 0.133423, 0.153820, 0.189975],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1197.89, 1238.94, 1280.07, 1321.12, 1362.19, 1403.28, 1444.39, 1485.63, 1526.82, 1568.08, 1609.41, 1650.92, 1692.47, 1734.21, 1776.20, 1818.70, 1861.85, 1906.61],

# deg/s^2
"outLiftAngleAccel" => [-0.0677172, -0.00817353, 0.0453112, 0.0957941, 0.146012, 0.197880, 0.253890, 0.316616, 0.389809, 0.478228, 0.588731, 0.732348, 0.927846, 1.20815, 1.63893, 2.36894, 3.80329, 7.48085],

# mm/s
"liftRefVel" => 86.4000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 3400.00,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-38.3000, 47.0700],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1504.00, 2368.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 6.28367, 12.5338, 18.7106, 24.9302, 31.1559, 37.3938, 43.6622, 49.9306, 56.1944, 62.4567, 68.7129, 74.9752, 81.2314, 87.4876, 93.7469, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [7.42000, 17.3500, 33.2600, 51.2900, 68.3800, 83.1800, 95.7100, 106.380, 115.590, 123.740, 131.160, 138.110, 144.870, 151.690, 158.950, 167.360, 179.250],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [7.42000, 17.3500, 33.2600, 51.2900, 68.3800, 83.1800, 95.7100, 106.380, 115.590, 123.740, 131.160, 138.110, 144.870, 151.690, 158.950, 167.360, 179.250],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-38.3000, -32.9600, -27.6300, -22.2800, -16.9600, -11.6200, -6.29000, -0.950000, 4.39000, 9.72000, 15.0600, 20.3900, 25.7300, 31.0600, 36.4000, 41.7400, 47.0700],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1372.50, 1359.70, 1351.90, 1349.10, 1351.30, 1358.70, 1371.00, 1387.80, 1409.30, 1434.60, 1463.50, 1495.50, 1530.10, 1567.00, 1605.60, 1645.50, 1686.30,
    1398.20, 1386.60, 1379.90, 1378.30, 1381.80, 1390.30, 1403.70, 1421.60, 1443.90, 1470.00, 1499.60, 1532.20, 1567.40, 1604.70, 1643.60, 1683.80, 1724.70,
    1427.90, 1417.50, 1411.90, 1411.40, 1415.90, 1425.40, 1439.70, 1458.50, 1481.50, 1508.40, 1538.50, 1571.70, 1607.30, 1644.90, 1684.00, 1724.30, 1765.30,
    1461.10, 1451.60, 1447.00, 1447.50, 1453.00, 1463.30, 1478.40, 1498.00, 1521.60, 1549.00, 1579.70, 1613.30, 1649.20, 1687.00, 1726.40, 1766.90, 1807.90,
    1497.60, 1489.00, 1485.40, 1486.70, 1493.00, 1504.10, 1519.90, 1540.10, 1564.30, 1592.10, 1623.20, 1657.00, 1693.20, 1731.30, 1770.80, 1811.40, 1852.50,
    1537.10, 1529.30, 1526.40, 1528.40, 1535.40, 1547.10, 1563.50, 1584.20, 1608.80, 1637.10, 1668.50, 1702.60, 1739.00, 1777.20, 1816.80, 1857.50, 1898.60,
    1579.20, 1572.00, 1569.70, 1572.30, 1579.80, 1592.10, 1609.00, 1630.10, 1655.10, 1683.60, 1715.30, 1749.60, 1786.20, 1824.50, 1864.30, 1904.90, 1946.10,
    1623.50, 1616.80, 1615.10, 1618.20, 1626.20, 1638.90, 1656.10, 1677.50, 1702.80, 1731.60, 1763.40, 1797.90, 1834.60, 1873.00, 1912.80, 1953.50, 1994.70,
    1669.50, 1663.30, 1662.00, 1665.50, 1673.80, 1686.80, 1704.30, 1725.90, 1751.40, 1780.30, 1812.30, 1846.90, 1883.60, 1922.10, 1961.90, 2002.70, 2043.90,
    1716.80, 1711.00, 1710.00, 1713.70, 1722.40, 1735.60, 1753.30, 1775.00, 1800.60, 1829.50, 1861.60, 1896.20, 1933.00, 1971.50, 2011.40, 2052.10, 2093.30,
    1765.20, 1759.60, 1758.70, 1762.70, 1771.40, 1784.80, 1802.60, 1824.40, 1850.00, 1879.00, 1911.00, 1945.70, 1982.50, 2021.00, 2060.80, 2101.50, 2142.80,
    1814.10, 1808.60, 1807.90, 1812.00, 1820.80, 1834.20, 1851.90, 1873.80, 1899.40, 1928.40, 1960.40, 1995.00, 2031.70, 2070.20, 2110.00, 2150.70, 2191.90,
    1863.50, 1858.10, 1857.40, 1861.50, 1870.30, 1883.60, 1901.30, 1923.10, 1948.60, 1977.60, 2009.50, 2044.00, 2080.60, 2119.00, 2158.80, 2199.50, 2240.70,
    1912.90, 1907.40, 1906.80, 1910.80, 1919.50, 1932.70, 1950.30, 1971.90, 1997.30, 2026.00, 2057.90, 2092.20, 2128.90, 2167.20, 2206.90, 2247.60, 2288.70,
    1962.10, 1956.60, 1955.70, 1959.70, 1968.20, 1981.30, 1998.70, 2020.10, 2045.30, 2073.90, 2105.60, 2139.80, 2176.20, 2214.50, 2254.10, 2294.70, 2335.80,
    2011.00, 2005.30, 2004.30, 2007.90, 2016.30, 2029.10, 2046.30, 2067.50, 2092.40, 2120.80, 2152.30, 2186.30, 2222.60, 2260.70, 2300.20, 2340.80, 2381.90,
    2059.30, 2053.40, 2052.20, 2055.50, 2063.60, 2076.10, 2092.90, 2113.80, 2138.50, 2166.70, 2197.90, 2231.70, 2267.80, 2305.70, 2345.20, 2385.60, 2426.70
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [7.42000, 179.250],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-96.0300, 75.8000],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [7.42000, 179.250],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1475.00, 2052.00],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 196.900,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 88.8500,

##
## Tilt Cylinders
##

# Number of tilt cylinders.
"NoOfTiltCyls" => 2,

# Tilt cylinder bore diameter, in mm.
"TiltCylBoreDia" => 158.800,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 76.2000,

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
"LoaderBktPayldTrgtWt" => 9.11500,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 12.0000,

# The CAT datalink configuration file.
"BMI_CDL_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiCdl_MWL_G.json",

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
"KgPerLiftKpaAtMidExtension" => 1.18340,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1537.00,

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
"LiftCylExtPctAxis" => [0.00000, 15.7407, 35.4167, 54.5139, 64.6991, 71.7593, 77.3148, 81.8287, 85.6481, 88.8889, 91.7824, 94.2130, 96.4120, 98.2639, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 6.23917, 11.6118, 16.4645, 20.9705, 25.1300, 29.1161, 32.9289, 36.5685, 40.0347, 43.3276, 46.4471, 49.3934, 52.6863, 56.6724, 63.9515, 71.7504, 79.3761, 88.5615, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -54.5789, -104.409, -7.35909, 163.564, 175.001, 78.3518, -51.1624, -189.308, -349.717, -553.740, -871.465, -1560.80, -2195.49, -2746.60, -3266.67,
    -105.156, -124.834, -29.5128, 172.826, 283.754, 267.082, 144.848, -12.5870, -173.688, -342.138, -545.404, -802.359, -1222.12, -2289.28, -3178.52,
    -120.466, -133.192, -49.5771, 143.028, 299.678, 380.615, 342.663, 200.935, 18.7726, -162.370, -351.260, -551.826, -804.370, -1138.45, -1772.66,
    -123.542, -136.462, -65.1537, 105.369, 266.967, 402.417, 464.567, 408.267, 247.765, 47.0668, -160.541, -358.224, -575.066, -816.009, -1147.19,
    -121.908, -137.145, -76.6089, 70.6734, 218.873, 369.054, 494.270, 539.934, 466.535, 291.574, 65.8891, -152.756, -373.678, -592.974, -855.805,
    -118.439, -136.361, -84.5821, 42.3349, 171.897, 315.198, 463.427, 577.860, 607.527, 517.772, 320.386, 86.4871, -156.992, -384.643, -633.085,
    -114.184, -134.656, -90.0719, 19.5090, 130.234, 257.840, 404.723, 550.187, 656.446, 671.932, 562.785, 358.126, 101.209, -148.662, -409.215,
    -109.656, -132.336, -93.5783, 1.70086, 95.5650, 205.373, 339.049, 488.577, 633.385, 730.612, 732.095, 612.876, 388.685, 128.674, -155.097,
    -105.104, -129.605, -95.5343, -11.8918, 67.6888, 160.714, 277.220, 416.459, 570.716, 712.593, 803.649, 792.276, 656.332, 430.368, 139.222,
    -100.652, -126.603, -96.2931, -22.0776, 45.7168, 124.116, 223.505, 346.749, 493.799, 650.234, 793.901, 872.781, 848.314, 706.985, 454.511,
    -96.3588, -123.429, -96.1367, -29.5649, 28.6176, 94.7492, 178.759, 285.033, 417.427, 570.098, 734.538, 869.670, 941.243, 906.347, 743.105,
    -92.2497, -120.157, -95.2875, -34.9391, 15.4344, 71.4671, 142.336, 232.849, 348.515, 488.460, 653.089, 813.600, 948.301, 1007.25, 955.960,
    -88.3363, -116.842, -93.9217, -38.6707, 5.35411, 53.1433, 113.065, 189.828, 289.373, 413.428, 567.356, 732.205, 898.579, 1022.06, 1072.00,
    -83.9225, -112.887, -91.8061, -41.4914, -3.53914, 36.3848, 85.7497, 148.874, 231.459, 336.565, 472.130, 627.160, 802.615, 965.386, 1098.79,
    -78.5105, -107.749, -88.4852, -43.2607, -11.4428, 20.6126, 59.3821, 108.569, 173.125, 256.460, 367.041, 499.737, 662.353, 834.707, 1017.44,
    -68.3477, -97.3256, -80.4736, -42.6947, -19.4432, 1.92965, 26.4434, 56.7330, 96.1706, 147.432, 217.018, 304.104, 418.478, 553.573, 724.359,
    -56.8264, -84.4373, -69.2733, -37.8578, -21.2169, -7.55888, 7.00102, 24.2497, 46.2345, 74.6004, 113.246, 162.312, 228.527, 310.181, 420.520,
    -44.5278, -69.5571, -55.6318, -29.9390, -18.2897, -9.82837, -1.55218, 7.74448, 19.2473, 33.8696, 53.6831, 78.8810, 113.167, 156.098, 215.551,
    -27.4284, -46.8807, -34.9783, -17.3409, -10.9184, -6.94164, -3.48517, 0.111573, 4.37301, 9.67089, 16.7775, 25.7906, 38.0820, 53.5714, 75.2609,
    0.0458481, 0.113946, 0.0621923, 0.0231171, 0.0141335, 0.00966120, 0.00628290, 0.00304506, -0.000646626, -0.00517822, -0.0112556, -0.0190025, -0.0296434, -0.0431613, -0.0622622
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 9.11500,

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
"TiltCylExtThresholdStrict" => 98.8267,

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
  "InternalMsn" => "CAT80601",
  "Make" => "CAT",
  "Model" => "980G",
  "ModelDetail" => "980G",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
