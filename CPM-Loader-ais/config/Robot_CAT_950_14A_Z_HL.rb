##
## CAT 950z - High Lift
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
"outLiftPresNoBucket" => [1709.05, 1749.21, 1789.40, 1829.56, 1869.28, 1908.53, 1947.00, 1984.38, 2019.03, 2054.96, 2087.34, 2116.97, 2142.89, 2163.82, 2177.39, 2179.55, 2161.83, 2102.16],

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
"LoaderBktPayldTrgtWt" => 5.05520,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 7.00000,

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_MWL.json",

# Determines whether or not payload legal for trade is supported.
"LegalForTradeSupported" => true,

# Determines whether or not acceleration compensation is supported for this
# machine configuration
"AccelCompSupported" => true,

# This selects the application number used for selecting the cycle segmentation
# data.
"CycleSegAppNumber" => 5000,

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
"KgPerLiftKpaAtMidExtension" => 0.593206,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 2033.65,

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
    -106.010, -84.8861, 40.6717, 225.917, 349.717, 348.879, 268.617, 125.497, -60.8897, -259.321, -459.619, -657.070, -862.288, -1077.91, -1287.34,
    -123.525, -102.999, 16.0647, 202.379, 365.914, 424.415, 411.566, 327.820, 173.952, -25.2376, -244.041, -460.672, -678.884, -899.681, -1107.43,
    -136.180, -117.199, -6.31000, 171.757, 350.940, 446.959, 488.844, 471.292, 382.339, 223.931, 12.4827, -219.575, -459.490, -697.892, -915.341,
    -145.106, -127.932, -25.2954, 140.529, 320.190, 434.999, 512.336, 547.097, 524.960, 433.193, 269.371, 52.8638, -197.423, -457.096, -693.169,
    -151.197, -135.761, -40.7141, 111.927, 283.969, 404.889, 501.319, 570.340, 600.068, 573.085, 476.612, 311.231, 84.0393, -179.876, -432.693,
    -155.152, -141.250, -52.8508, 87.2298, 248.145, 367.759, 472.026, 560.388, 624.565, 647.442, 613.870, 513.502, 340.030, 104.276, -146.225,
    -157.625, -145.078, -62.6409, 65.5812, 213.832, 328.017, 433.231, 530.923, 616.291, 674.443, 691.590, 653.381, 546.857, 367.811, 148.789,
    -158.892, -147.505, -70.3417, 47.0316, 182.415, 289.029, 390.911, 490.995, 587.323, 667.732, 721.113, 732.932, 689.360, 577.879, 413.387,
    -159.185, -148.770, -76.2304, 31.4089, 154.483, 252.679, 348.844, 446.896, 546.994, 639.567, 716.323, 764.189, 771.228, 722.415, 619.583,
    -158.645, -149.072, -80.8119, 17.6776, 128.694, 217.883, 306.762, 399.859, 498.876, 596.572, 687.285, 760.039, 805.800, 810.194, 766.727,
    -157.306, -148.446, -84.1326, 5.82794, 105.299, 185.355, 266.094, 352.337, 446.809, 544.230, 641.151, 728.807, 801.154, 845.926, 852.027,
    -154.896, -146.680, -86.4148, -5.25070, 82.1198, 152.214, 223.495, 300.823, 387.561, 480.151, 577.047, 671.749, 761.110, 835.709, 882.233,
    -150.716, -143.077, -87.2584, -15.7537, 58.2513, 117.022, 177.049, 242.955, 318.342, 401.146, 491.359, 584.705, 680.628, 772.905, 848.009,
    -142.609, -135.435, -85.1475, -25.4861, 32.3127, 77.1178, 122.784, 173.316, 232.048, 298.158, 372.696, 453.491, 541.978, 635.203, 721.565,
    -122.040, -114.955, -73.2665, -30.7491, 5.00642, 30.9730, 56.8953, 85.4873, 119.002, 157.429, 201.994, 252.191, 310.021, 375.134, 440.641,
    -95.6734, -88.3727, -54.8526, -25.6959, -4.60777, 9.54517, 23.2264, 38.0959, 55.4438, 75.3856, 98.7067, 125.332, 156.580, 192.622, 229.936,
    -57.9384, -51.3332, -29.5533, -14.1546, -4.81115, 0.896233, 6.19054, 11.8210, 18.3176, 25.7551, 34.4606, 44.4461, 56.2581, 70.0324, 84.4822,
    6.02525, 4.72345, 2.26180, 1.03362, 0.429550, 0.0954973, -0.201370, -0.509888, -0.861393, -1.26134, -1.72862, -2.26518, -2.90196, -3.64833, -4.43632,
    65.9588, 36.4799, 32.0514, 13.9064, 6.24463, 2.20096, -1.33444, -4.98140, -9.12376, -13.8345, -19.3441, -25.6836, -33.2284, -42.1023, -51.5070,
    99.5657, 50.4220, -33.5042, 14.7784, 7.30547, 2.59043, -1.73616, -6.30662, -11.5703, -17.6089, -24.7129, -32.9217, -42.7236, -54.2843, -66.5655
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 5.05520,

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
  "InternalMsn" => "CAT50709",
  "Make" => "CAT",
  "Model" => "950z",
  "ModelDetail" => "950z",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}
