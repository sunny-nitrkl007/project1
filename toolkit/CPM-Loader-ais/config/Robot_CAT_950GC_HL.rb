##
## CAT 950GC - High Lift
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-34.3400, 52.0800],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-34.3400, -30.8500, -27.3700, -23.8700, -20.3600, -16.8100, -13.2200, -9.57000, -5.86000, -2.06000, 1.85000, 5.23000, 5.87000, 10.0400, 14.3900, 18.9600, 23.7800, 28.9500, 34.5600, 40.8000, 52.0800],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1388.00, 1429.00, 1470.00, 1511.10, 1552.10, 1593.10, 1634.10, 1675.20, 1716.20, 1757.20, 1798.30, 1832.80, 1839.30, 1880.30, 1921.30, 1962.40, 2003.40, 2044.40, 2085.40, 2126.50, 2188.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0852335, 0.0849594, 0.0850102, 0.0853622, 0.0860008, 0.0869275, 0.0881476, 0.0896822, 0.0915547, 0.0938157, 0.0965304, 0.0992219, 0.0997701, 0.103667, 0.108395, 0.114214, 0.121485, 0.130887, 0.143513, 0.161619, 0.212622],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1892.18, 1934.97, 1977.81, 2020.66, 2063.20, 2105.41, 2147.17, 2188.44, 2228.89, 2268.45, 2307.00, 2338.31, 2344.09, 2379.46, 2412.66, 2443.07, 2469.56, 2490.60, 2503.46, 2502.84, 2444.69],

# deg/s^2
"outLiftAngleAccel" => [-0.0700104, -0.0165584, 0.0318065, 0.0774871, 0.121964, 0.167051, 0.214141, 0.264996, 0.321352, 0.385850, 0.461797, 0.537638, 0.553273, 0.667148, 0.813529, 1.00883, 1.27990, 1.68024, 2.31619, 3.44843, 8.31289],

# mm/s
"liftRefVel" => 80.0000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 3267.50,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-34.3400, 52.0800],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1388.00, 2188.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 6.24247, 12.4956, 18.7518, 25.0050, 31.1116, 37.3770, 43.6728, 49.9413, 56.2066, 62.4903, 68.7434, 75.0118, 81.3046, 87.5853, 93.8262, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [-4.82000, 2.81911, 16.0688, 31.7067, 47.1927, 61.1201, 73.9052, 85.3029, 95.4277, 104.580, 113.036, 120.968, 128.678, 136.459, 144.675, 154.083, 167.390],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [-4.82000, 2.81911, 16.0688, 31.7067, 47.1927, 61.1201, 73.9052, 85.3029, 95.4277, 104.580, 113.036, 120.968, 128.678, 136.459, 144.675, 154.083, 167.390],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-34.3400, -30.8500, -27.3700, -23.8700, -20.3600, -16.8100, -13.2200, -9.57000, -5.86000, -2.06000, 1.85000, 5.23000, 5.87000, 10.0400, 14.3900, 18.9600, 23.7800, 28.9500, 34.5600, 40.8000, 52.0800],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1448.32, 1444.65, 1442.69, 1442.42, 1443.89, 1447.12, 1452.16, 1459.06, 1467.86, 1478.67, 1491.60, 1504.17, 1506.69, 1524.13, 1544.11, 1566.87, 1592.58, 1621.83, 1655.16, 1693.68, 1765.50,
    1473.61, 1470.56, 1469.21, 1469.57, 1471.64, 1475.48, 1481.11, 1488.59, 1497.95, 1509.31, 1522.76, 1535.76, 1538.36, 1556.28, 1576.70, 1599.86, 1625.95, 1655.53, 1689.13, 1727.86, 1799.84,
    1503.36, 1500.88, 1500.09, 1501.00, 1503.63, 1508.01, 1514.16, 1522.16, 1532.02, 1543.86, 1557.77, 1571.13, 1573.80, 1592.13, 1612.93, 1636.45, 1662.85, 1692.70, 1726.53, 1765.44, 1837.54,
    1537.10, 1535.12, 1534.83, 1536.24, 1539.34, 1544.19, 1550.81, 1559.25, 1569.54, 1581.78, 1596.09, 1609.77, 1612.49, 1631.16, 1652.29, 1676.09, 1702.76, 1732.84, 1766.85, 1805.90, 1878.08,
    1574.30, 1572.76, 1572.90, 1574.72, 1578.24, 1583.49, 1590.50, 1599.32, 1609.97, 1622.56, 1637.19, 1651.12, 1653.89, 1672.85, 1694.24, 1718.28, 1745.16, 1775.42, 1809.58, 1848.74, 1920.97,
    1613.50, 1612.32, 1612.81, 1614.99, 1618.84, 1624.42, 1631.74, 1640.86, 1651.80, 1664.66, 1679.55, 1693.69, 1696.49, 1715.67, 1737.26, 1761.49, 1788.53, 1818.93, 1853.21, 1892.44, 1964.71,
    1656.18, 1655.31, 1656.10, 1658.56, 1662.70, 1668.55, 1676.12, 1685.49, 1696.66, 1709.74, 1724.83, 1739.13, 1741.96, 1761.32, 1783.07, 1807.44, 1834.59, 1865.10, 1899.46, 1938.75, 2011.04,
    1701.09, 1700.46, 1701.49, 1704.18, 1708.53, 1714.59, 1722.36, 1731.91, 1743.25, 1756.49, 1771.73, 1786.14, 1788.99, 1808.47, 1830.34, 1854.80, 1882.05, 1912.62, 1947.04, 1986.37, 2058.68,
    1747.36, 1746.91, 1748.11, 1750.96, 1755.46, 1761.66, 1769.57, 1779.24, 1790.70, 1804.04, 1819.38, 1833.86, 1836.73, 1856.28, 1878.21, 1902.74, 1930.03, 1960.65, 1995.09, 2034.45, 2106.76,
    1794.70, 1794.37, 1795.68, 1798.64, 1803.24, 1809.52, 1817.51, 1827.25, 1838.77, 1852.17, 1867.55, 1882.07, 1884.94, 1904.53, 1926.48, 1951.03, 1978.33, 2008.96, 2043.42, 2082.77, 2155.08,
    1842.87, 1842.60, 1843.97, 1846.98, 1851.62, 1857.94, 1865.95, 1875.71, 1887.24, 1900.65, 1916.03, 1930.55, 1933.42, 1953.00, 1974.94, 1999.47, 2026.76, 2057.38, 2091.82, 2131.16, 2203.47,
    1891.10, 1890.85, 1892.22, 1895.22, 1899.85, 1906.16, 1914.15, 1923.89, 1935.38, 1948.75, 1964.10, 1978.58, 1981.44, 2000.97, 2022.87, 2047.35, 2074.60, 2105.17, 2139.58, 2178.90, 2251.20,
    1939.38, 1939.09, 1940.42, 1943.38, 1947.95, 1954.20, 1962.12, 1971.79, 1983.21, 1996.50, 2011.77, 2026.18, 2029.03, 2048.48, 2070.30, 2094.71, 2121.89, 2152.39, 2186.75, 2226.03, 2298.32,
    1987.45, 1987.08, 1988.32, 1991.18, 1995.66, 2001.80, 2009.62, 2019.18, 2030.48, 2043.66, 2058.81, 2073.12, 2075.96, 2095.30, 2117.00, 2141.31, 2168.39, 2198.81, 2233.09, 2272.32, 2344.59,
    2034.71, 2034.22, 2035.33, 2038.06, 2042.40, 2048.40, 2056.07, 2065.48, 2076.64, 2089.67, 2104.67, 2118.86, 2121.67, 2140.86, 2162.43, 2186.61, 2213.57, 2243.88, 2278.07, 2317.24, 2389.47,
    2080.69, 2080.04, 2080.99, 2083.55, 2087.72, 2093.54, 2101.04, 2110.26, 2121.24, 2134.09, 2148.91, 2162.95, 2165.73, 2184.76, 2206.16, 2230.18, 2257.00, 2287.19, 2321.27, 2360.36, 2432.55,
    2124.95, 2124.11, 2124.86, 2127.23, 2131.19, 2136.81, 2144.10, 2153.11, 2163.89, 2176.52, 2191.14, 2205.01, 2207.76, 2226.59, 2247.81, 2271.65, 2298.30, 2328.35, 2362.31, 2401.30, 2473.44
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [-4.82000, 167.390],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-96.8000, 75.4100],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [-4.82000, 167.390],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1580.00, 2125.00],

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
"TiltCylBoreDia" => 160.000,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 85.0000,

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
"LoaderBktPayldTrgtWt" => 5.87400,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 8.00000,

# The CAT datalink configuration file.
"BMI_CDL_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiCdl_MWL_GC.json",

# The BMI J1939 configuration file.
"BMI_J1939_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiJ1939_950_MWL_GC_SA.json",

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_MWL_950GC.json",

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
"KgPerLiftKpaAtMidExtension" => 0.569730,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 2303.70,

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
"LiftCylExtPctAxis" => [0.00000, 15.6250, 36.2500, 56.3750, 66.0000, 72.8750, 78.2500, 82.6250, 86.3750, 89.5000, 92.2500, 94.6250, 96.6250, 98.3750, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 6.42202, 11.7431, 16.5138, 20.7339, 24.7706, 28.4404, 31.9266, 35.2294, 38.3486, 41.2844, 44.0367, 46.9725, 50.2752, 54.4954, 62.2018, 71.9266, 80.7339, 90.6422, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -12.9339, -85.7856, 29.7620, 204.364, 172.861, 1.58033, -247.983, -553.743, -974.156, -1697.51, -2413.60, -3068.51, -3630.48, -4124.29, -4583.12,
    -71.5278, -123.929, 1.65643, 242.395, 330.053, 277.495, 86.0789, -190.874, -518.643, -896.660, -1422.39, -2416.38, -3267.71, -4036.21, -4755.58,
    -103.720, -148.537, -27.1624, 227.130, 377.367, 434.686, 363.069, 154.140, -155.981, -500.793, -891.611, -1368.42, -2039.52, -3517.18, -4747.16,
    -123.742, -165.740, -52.7210, 193.197, 367.180, 490.198, 527.773, 441.167, 210.439, -115.673, -493.382, -898.403, -1344.98, -1917.09, -2899.28,
    -136.274, -177.520, -73.3193, 156.310, 332.650, 484.907, 589.529, 608.910, 500.987, 256.419, -98.4939, -499.604, -909.215, -1357.66, -1933.02,
    -144.733, -186.082, -90.5167, 119.923, 288.246, 448.941, 589.038, 680.783, 686.350, 567.131, 303.375, -68.8556, -477.595, -906.165, -1393.60,
    -150.013, -191.797, -103.778, 88.2957, 244.409, 401.625, 554.554, 684.941, 766.069, 756.594, 618.625, 338.880, -36.3323, -463.473, -940.889,
    -153.266, -195.577, -114.235, 60.6869, 203.112, 350.997, 504.083, 651.560, 777.188, 845.963, 823.014, 670.692, 389.631, 3.82433, -468.835,
    -155.002, -197.804, -122.254, 37.2365, 166.095, 302.135, 448.346, 599.179, 746.365, 862.750, 923.140, 887.510, 730.725, 443.977, 22.6291,
    -155.595, -198.797, -128.208, 17.6966, 133.911, 257.532, 393.492, 539.748, 693.530, 834.551, 947.120, 997.376, 953.722, 791.271, 478.194,
    -155.331, -198.816, -132.442, 1.65054, 106.483, 218.157, 342.690, 480.289, 631.737, 782.119, 923.171, 1028.68, 1069.22, 1018.78, 836.650,
    -154.428, -198.077, -135.270, -11.3688, 83.4274, 184.132, 297.309, 424.553, 568.830, 719.210, 872.707, 1009.82, 1105.77, 1139.41, 1075.05,
    -152.824, -196.527, -137.132, -23.1818, 61.6833, 151.236, 252.273, 367.304, 500.675, 644.708, 800.357, 954.081, 1086.40, 1182.89, 1219.01,
    -150.286, -193.888, -137.883, -34.0522, 40.6386, 118.548, 206.448, 307.379, 426.416, 558.513, 707.359, 864.469, 1015.63, 1153.10, 1264.88,
    -145.990, -189.198, -136.905, -44.4954, 18.7062, 83.3063, 155.784, 239.380, 339.275, 452.622, 584.719, 731.363, 883.446, 1039.20, 1198.17,
    -135.272, -176.944, -129.955, -54.7887, -8.63452, 36.1852, 85.3179, 141.686, 209.571, 288.094, 382.513, 492.267, 613.583, 749.322, 907.677,
    -116.396, -154.455, -112.388, -54.4505, -24.1580, 2.78377, 30.8921, 62.3513, 99.9117, 143.485, 196.531, 259.530, 331.306, 414.898, 517.882,
    -93.1964, -125.945, -88.0859, -44.0586, -24.6124, -8.95414, 6.39531, 22.9602, 42.3516, 64.6524, 91.7701, 124.119, 161.310, 205.195, 260.243,
    -56.4654, -79.2827, -49.7342, -23.6878, -14.5543, -8.10256, -2.30242, 3.62936, 10.3570, 17.9624, 27.1365, 38.0571, 50.6365, 65.5534, 84.4108,
    1.41695, 2.33558, 1.04345, 0.424223, 0.265954, 0.168019, 0.0870183, 0.00832436, -0.0783074, -0.174695, -0.290092, -0.427096, -0.584968, -0.772588, -1.01063
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 5.87400,

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
"TiltCylExtThresholdStrict" => 98.8165,

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

##
## BEM Simulation
##

# Battery Capacity in kWh
"BEMSimBatteryCapacity" => 256.000,

# Specific Fuel Consumption, Ksfc in kWh/L
"BEMSimKsfc" => 3.10000,

# Battery Model is either NMC for Nickel Manganese Cobalt or LINEAR for an ideal
# model.
"BEMSimBatteryModel" => "NMC",

}

MachineType = {
  "InternalMsn" => "CAT50301",
  "Make" => "CAT",
  "Model" => "950GC",
  "ModelDetail" => "950GC",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}
