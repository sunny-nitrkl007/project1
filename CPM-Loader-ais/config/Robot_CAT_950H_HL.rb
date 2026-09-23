##
## CAT 950H - High Lift
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
"outLiftPresNoBucket" => [1568.27, 1605.12, 1642.00, 1678.84, 1715.29, 1751.30, 1786.60, 1820.89, 1852.68, 1885.65, 1915.36, 1942.55, 1966.32, 1985.52, 1997.96, 1999.94, 1983.66, 1928.88],

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
    1639.10, 1643.60, 1650.60, 1659.80, 1671.50, 1685.50, 1702.00, 1721.00, 1742.50, 1766.80, 1793.90, 1824.00, 1857.60, 1895.00, 1937.10, 1985.20, 2041.80,
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
"LiftCylBoreDia" => 146.150,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 82.5000,

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
"LoaderBktPayldTrgtWt" => 5.51800,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 7.50000,

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
"KgPerLiftKpaAtMidExtension" => 0.646468,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1866.10,

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
    -97.2758, -77.8924, 37.3208, 207.304, 320.904, 320.135, 246.486, 115.158, -55.8730, -237.956, -421.751, -602.935, -791.245, -989.102, -1181.27,
    -113.348, -94.5131, 14.7412, 185.705, 335.767, 389.448, 377.657, 300.811, 159.621, -23.1583, -223.934, -422.718, -622.951, -825.557, -1016.19,
    -124.960, -107.543, -5.79012, 157.606, 322.027, 410.134, 448.569, 432.463, 350.838, 205.482, 11.4543, -201.484, -421.633, -640.393, -839.927,
    -133.151, -117.392, -23.2113, 128.950, 293.810, 399.159, 470.125, 502.022, 481.709, 397.502, 247.178, 48.5084, -181.158, -419.436, -636.059,
    -138.740, -124.576, -37.3597, 102.705, 260.573, 371.530, 460.015, 523.350, 550.629, 525.869, 437.344, 285.589, 77.1154, -165.057, -397.044,
    -142.369, -129.613, -48.4964, 80.0430, 227.701, 337.459, 433.136, 514.218, 573.107, 594.100, 563.293, 471.195, 312.015, 95.6849, -134.178,
    -144.638, -133.125, -57.4799, 60.1780, 196.214, 300.992, 397.537, 487.181, 565.515, 618.876, 634.611, 599.549, 501.802, 337.507, 136.530,
    -145.801, -135.352, -64.5463, 43.1567, 167.386, 265.216, 358.704, 450.542, 538.934, 612.718, 661.701, 672.546, 632.564, 530.268, 379.329,
    -146.070, -136.513, -69.9498, 28.8211, 141.755, 231.861, 320.103, 410.076, 501.928, 586.873, 657.306, 701.228, 707.687, 662.896, 568.536,
    -145.574, -136.790, -74.1538, 16.2212, 118.091, 199.932, 281.488, 366.915, 457.774, 547.421, 630.660, 697.420, 739.411, 743.442, 703.557,
    -144.346, -136.215, -77.2010, 5.34778, 96.6235, 170.084, 244.171, 323.308, 409.997, 499.391, 588.327, 668.761, 735.148, 776.230, 781.829,
    -142.134, -134.595, -79.2951, -4.81810, 75.3540, 139.673, 205.081, 276.039, 355.630, 440.592, 529.505, 616.404, 698.403, 766.856, 809.546,
    -138.299, -131.289, -80.0692, -14.4558, 53.4520, 107.380, 162.462, 222.938, 292.114, 368.096, 450.876, 536.531, 624.551, 709.226, 778.142,
    -130.859, -124.276, -78.1322, -23.3863, 29.6504, 70.7642, 112.668, 159.036, 212.929, 273.593, 341.990, 416.128, 497.325, 582.869, 662.115,
    -111.986, -105.484, -67.2302, -28.2157, 4.59394, 28.4212, 52.2077, 78.4440, 109.197, 144.459, 185.352, 231.413, 284.478, 344.227, 404.337,
    -87.7909, -81.0918, -50.3333, -23.5789, -4.22814, 8.75875, 21.3128, 34.9572, 50.8758, 69.1747, 90.5743, 115.006, 143.679, 176.752, 210.991,
    -53.1649, -47.1039, -27.1184, -12.9884, -4.41476, 0.822393, 5.68050, 10.8471, 16.8085, 23.6331, 31.6214, 40.7842, 51.6230, 64.2625, 77.5218,
    5.52883, 4.33428, 2.07545, 0.948457, 0.394160, 0.0876294, -0.184779, -0.467879, -0.790424, -1.15742, -1.58620, -2.07855, -2.66287, -3.34775, -4.07082,
    60.5245, 33.4743, 29.4107, 12.7607, 5.73014, 2.01962, -1.22450, -4.57099, -8.37206, -12.6947, -17.7504, -23.5676, -30.4908, -38.6335, -47.2634,
    91.3625, 46.2678, -30.7438, 13.5608, 6.70357, 2.37700, -1.59312, -5.78702, -10.6171, -16.1581, -22.6768, -30.2093, -39.2036, -49.8118, -61.0812
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 5.51800,

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
  "InternalMsn" => "CAT50001",
  "Make" => "CAT",
  "Model" => "950H",
  "ModelDetail" => "950H",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
