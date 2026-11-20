##
## CAT 982 - Standard
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-34.1700, 45.0600],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-34.1700, -30.1700, -26.5300, -23.1400, -19.9800, -16.9200, -13.9500, -11.0700, -8.30000, -5.62000, -2.96000, -0.320000, 2.21000, 4.71000, 7.20000, 9.67000, 12.1100, 14.5300, 16.9300, 19.3100, 21.6600, 23.9900, 26.2900, 28.5500, 30.7900, 32.9900, 35.1500, 37.2600, 39.4900, 41.6900, 43.8300, 45.0600],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1616.00, 1672.00, 1722.00, 1768.00, 1810.00, 1850.00, 1888.00, 1924.00, 1958.00, 1990.00, 2021.00, 2051.00, 2079.00, 2106.00, 2132.00, 2157.00, 2181.00, 2204.00, 2226.00, 2247.00, 2267.00, 2286.00, 2304.00, 2321.00, 2337.00, 2352.00, 2366.00, 2379.00, 2392.00, 2404.00, 2415.00, 2421.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0710581, 0.0720568, 0.0732040, 0.0744793, 0.0758529, 0.0773607, 0.0790004, 0.0807668, 0.0826415, 0.0846321, 0.0867941, 0.0891397, 0.0915920, 0.0942311, 0.0970948, 0.100192, 0.103531, 0.107149, 0.111075, 0.115344, 0.119973, 0.125027, 0.130534, 0.136521, 0.143108, 0.150311, 0.158211, 0.166860, 0.177190, 0.188820, 0.201805, 0.210158],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1499.88, 1565.88, 1625.36, 1680.65, 1731.72, 1780.97, 1828.40, 1874.00, 1917.76, 1959.67, 2001.03, 2041.90, 2080.90, 2119.43, 2157.53, 2195.26, 2232.68, 2269.83, 2306.81, 2343.69, 2380.55, 2417.51, 2454.68, 2492.18, 2530.15, 2568.75, 2608.15, 2648.50, 2693.64, 2741.04, 2791.14, 2822.05],

# deg/s^2
"outLiftAngleAccel" => [0.0991086, 0.132591, 0.164392, 0.196008, 0.227940, 0.261823, 0.298208, 0.337542, 0.379943, 0.426099, 0.477893, 0.536355, 0.600280, 0.672545, 0.755306, 0.850214, 0.959132, 1.08527, 1.23214, 1.40415, 1.60592, 1.84503, 2.12901, 2.46683, 2.87509, 3.36774, 3.96636, 4.69540, 5.67283, 6.92097, 8.51139, 9.65076],

# mm/s
"liftRefVel" => 80.5000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 3561.45,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-34.1700, 45.0600],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1616.00, 2421.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 2.07370, 4.67384, 7.38231, 10.3609, 13.9544, 19.7650, 27.5196, 32.9152, 38.0804, 43.3860, 49.0669, 55.3964, 62.9191, 74.9615, 84.6830, 90.0221, 93.7789, 96.5240, 98.5397, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [14.4200, 16.2000, 19.1500, 23.0400, 28.1600, 35.2300, 47.7700, 64.6400, 75.6400, 85.3800, 94.5700, 103.580, 112.770, 122.810, 137.770, 149.920, 157.240, 163.070, 168.020, 172.340, 176.150],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [14.1500, 15.4500, 17.7500, 21.0500, 25.8500, 33.2500, 48.4500, 60.9500, 71.1500, 80.2500, 88.6500, 96.6500, 104.450, 112.250, 120.650, 132.250, 143.450, 150.450, 156.350, 161.650, 166.650, 171.450, 176.150],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-34.1700, -29.9700, -25.6700, -21.3700, -17.0700, -12.6700, -8.17000, -3.57000, 1.33000, 6.43000, 11.9300, 18.0300, 24.9300, 33.4300, 45.1300],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1103.30, 1097.80, 1096.00, 1097.80, 1103.50, 1113.10, 1126.70, 1144.40, 1167.10, 1194.60, 1228.00, 1269.00, 1319.40, 1385.60, 1480.80,
    1113.20, 1108.20, 1106.70, 1109.10, 1115.20, 1125.20, 1139.20, 1157.20, 1180.30, 1208.00, 1241.80, 1283.00, 1333.60, 1400.00, 1495.30,
    1127.60, 1123.10, 1122.30, 1125.20, 1131.80, 1142.40, 1156.90, 1175.40, 1198.90, 1227.10, 1261.10, 1302.70, 1353.60, 1420.20, 1515.60,
    1144.80, 1141.00, 1140.80, 1144.30, 1151.60, 1162.60, 1177.70, 1196.70, 1220.60, 1249.20, 1283.60, 1325.60, 1376.70, 1443.50, 1539.00,
    1166.60, 1163.50, 1164.00, 1168.20, 1176.00, 1187.70, 1203.40, 1222.90, 1247.30, 1276.30, 1311.20, 1353.40, 1404.80, 1471.80, 1567.40,
    1197.00, 1194.70, 1196.00, 1201.00, 1209.60, 1222.00, 1238.30, 1258.40, 1283.40, 1312.90, 1348.20, 1390.80, 1442.50, 1509.80, 1605.50,
    1257.20, 1256.20, 1258.80, 1265.00, 1274.70, 1288.10, 1305.30, 1326.30, 1352.10, 1382.30, 1418.20, 1461.40, 1513.60, 1581.10, 1677.00,
    1309.70, 1309.60, 1313.00, 1319.90, 1330.30, 1344.40, 1362.20, 1383.70, 1410.00, 1440.60, 1476.80, 1520.30, 1572.70, 1640.50, 1736.30,
    1356.80, 1357.30, 1361.20, 1368.60, 1379.50, 1394.00, 1412.20, 1434.00, 1460.60, 1491.50, 1527.90, 1571.60, 1624.10, 1692.00, 1787.90,
    1403.20, 1404.10, 1408.40, 1416.30, 1427.50, 1442.30, 1460.70, 1482.80, 1509.60, 1540.60, 1577.20, 1621.00, 1673.60, 1741.50, 1837.40,
    1450.50, 1451.70, 1456.40, 1464.50, 1475.90, 1490.90, 1509.60, 1531.80, 1558.70, 1589.80, 1626.50, 1670.30, 1723.00, 1790.90, 1886.80,
    1500.00, 1501.50, 1506.40, 1514.70, 1526.30, 1541.40, 1560.20, 1582.50, 1609.40, 1640.60, 1677.30, 1721.10, 1773.80, 1841.70, 1937.70,
    1552.90, 1554.50, 1559.60, 1568.00, 1579.70, 1594.90, 1613.70, 1636.00, 1663.00, 1694.10, 1730.80, 1774.60, 1827.20, 1895.10, 1991.00,
    1610.40, 1612.10, 1617.20, 1625.70, 1637.40, 1652.60, 1671.40, 1693.70, 1720.50, 1751.60, 1788.20, 1831.90, 1884.40, 1952.20, 2048.20,
    1677.20, 1678.90, 1684.00, 1692.40, 1704.10, 1719.20, 1737.80, 1759.90, 1786.60, 1817.50, 1853.90, 1897.40, 1949.80, 2017.50, 2113.40,
    1775.50, 1777.00, 1781.80, 1790.00, 1801.30, 1816.10, 1834.30, 1856.10, 1882.40, 1912.90, 1949.00, 1992.10, 2044.20, 2111.60, 2207.40,
    1871.40, 1872.50, 1876.90, 1884.50, 1895.40, 1909.60, 1927.40, 1948.60, 1974.40, 2004.40, 2040.00, 2082.70, 2134.30, 2201.40, 2297.10,
    1927.90, 1928.70, 1932.80, 1940.10, 1950.60, 1964.50, 1981.80, 2002.70, 2028.10, 2057.80, 2093.00, 2135.30, 2186.70, 2253.50, 2349.00,
    1971.50, 1972.00, 1975.70, 1982.70, 1992.90, 2006.50, 2023.50, 2044.00, 2069.10, 2098.50, 2133.30, 2175.40, 2226.50, 2293.10, 2388.50,
    2006.20, 2006.50, 2010.00, 2016.70, 2026.60, 2039.80, 2056.60, 2076.90, 2101.70, 2130.70, 2165.30, 2207.20, 2258.00, 2324.40, 2419.70,
    2034.50, 2034.50, 2037.80, 2044.20, 2053.90, 2066.90, 2083.40, 2103.40, 2128.00, 2156.80, 2191.20, 2232.80, 2283.50, 2349.70, 2444.90,
    2057.10, 2056.90, 2060.00, 2066.20, 2075.70, 2088.50, 2104.80, 2124.60, 2149.00, 2177.60, 2211.80, 2253.20, 2303.70, 2369.80, 2464.90,
    2074.60, 2074.30, 2077.20, 2083.30, 2092.60, 2105.20, 2121.40, 2141.00, 2165.20, 2193.70, 2227.70, 2269.00, 2319.30, 2385.30, 2480.30
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [14.4200, 176.150],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-90.5800, 71.1500],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [14.4200, 176.150],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1340.00, 2082.00],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 190.000,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 100.000,

##
## Tilt Cylinders
##

# Number of tilt cylinders.
"NoOfTiltCyls" => 2,

# Tilt cylinder bore diameter, in mm.
"TiltCylBoreDia" => 130.000,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 95.0000,

##
## Tool
##

# Tool's length between B and C pins, in mm.
"ToolBcLen" => 509.998,

# Tool's angle between line BC and tool's X-axis, in deg.
"ToolBcAngle" => 105.000,

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
"LoaderBktPayldTrgtWt" => 10.8580,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 15.0000,

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_MWL.json",

# Determines whether or not payload legal for trade is supported.
"LegalForTradeSupported" => true,

# Determines whether or not acceleration compensation is supported for this
# machine configuration
"AccelCompSupported" => true,

# This selects the application number used for selecting the cycle segmentation
# data.
"CycleSegAppNumber" => 8200,

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
"KgPerLiftKpaAtMidExtension" => 1.06545,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1982.13,

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
"LiftCylExtPctAxis" => [0.00000, 13.4161, 27.5776, 44.9689, 61.2422, 70.5590, 76.7702, 81.6149, 85.7143, 89.1925, 92.0497, 94.5342, 96.6460, 98.5093, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 5.52561, 10.3774, 14.8248, 18.8679, 22.6415, 26.1456, 29.3801, 32.4798, 35.4447, 38.5445, 41.9137, 45.8221, 50.9434, 60.1078, 69.1375, 77.0889, 85.5795, 94.8113, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -33.0359, -62.4288, -48.7462, 10.6417, 78.7954, 92.6709, 65.9322, 7.80769, -78.5630, -187.477, -309.869, -450.894, -609.487, -797.588, -1003.40,
    -50.4883, -75.9715, -60.4492, 2.25334, 86.9180, 128.451, 132.577, 104.345, 43.4705, -46.6802, -155.732, -284.169, -427.059, -591.012, -761.656,
    -62.1356, -85.7691, -70.2741, -8.22741, 82.7955, 141.132, 168.946, 169.103, 138.438, 75.2848, -13.6707, -127.313, -258.514, -410.005, -565.551,
    -70.3642, -93.1339, -78.4742, -18.9275, 72.5623, 139.549, 183.099, 205.681, 203.437, 171.063, 109.739, 19.0632, -95.0189, -233.060, -377.384,
    -76.1505, -98.5665, -85.0387, -28.6969, 60.0278, 130.015, 182.384, 220.043, 239.880, 235.287, 203.285, 141.353, 51.8357, -66.1920, -195.991,
    -80.3080, -102.616, -90.2941, -37.3550, 46.9776, 116.526, 172.905, 219.672, 254.996, 272.497, 266.961, 234.777, 174.596, 83.7846, -24.7652,
    -83.2314, -105.545, -94.3760, -44.7241, 34.5797, 101.700, 158.857, 210.187, 255.142, 288.277, 303.611, 297.589, 266.431, 206.097, 124.210,
    -85.2189, -107.579, -97.4482, -50.8107, 23.4218, 87.1263, 143.098, 195.889, 246.014, 289.139, 319.351, 333.811, 327.631, 296.327, 242.581,
    -86.5459, -108.956, -99.7665, -55.9244, 13.3054, 73.0664, 126.669, 178.931, 231.190, 280.190, 320.490, 350.232, 364.309, 358.607, 331.896,
    -87.3320, -109.775, -101.419, -60.1208, 4.34815, 59.9915, 110.561, 161.006, 213.252, 264.976, 311.376, 351.576, 380.771, 395.692, 392.410,
    -87.6881, -110.135, -102.567, -63.7655, -4.13466, 47.0549, 93.9559, 141.544, 192.159, 244.305, 293.901, 340.998, 381.398, 412.936, 429.909,
    -87.5746, -109.976, -103.160, -66.8653, -12.2419, 34.1210, 76.7443, 120.526, 168.061, 218.554, 268.686, 319.306, 366.995, 410.782, 444.010,
    -86.8346, -109.106, -103.022, -69.3542, -20.1355, 20.8319, 58.4161, 97.3268, 140.248, 186.969, 234.945, 285.652, 336.548, 387.804, 432.562,
    -84.9415, -106.894, -101.540, -70.8752, -28.0227, 6.41803, 37.6620, 70.0734, 106.232, 146.381, 188.783, 235.301, 284.331, 337.017, 387.084,
    -79.0896, -99.9938, -95.3392, -68.9641, -35.5633, -10.9426, 10.4955, 32.3996, 56.8564, 84.3827, 114.159, 147.944, 185.144, 227.389, 270.283,
    -70.2137, -89.3853, -84.7722, -61.6828, -35.6830, -18.5394, -4.54047, 9.26822, 24.4141, 41.3709, 59.7906, 80.9287, 104.612, 132.131, 160.842,
    -59.4681, -76.3841, -71.4348, -51.0342, -30.7093, -18.7959, -9.76781, -1.26788, 7.78687, 17.7571, 28.5106, 40.8449, 54.7235, 70.9804, 88.1238,
    -43.8613, -57.2369, -51.8831, -35.1750, -21.0555, -13.9197, -9.01121, -4.68033, -0.267195, 4.45392, 9.46175, 15.1585, 21.5519, 29.0518, 36.9939,
    -18.1624, -24.7458, -20.5762, -12.1693, -6.82304, -4.62483, -3.28715, -2.20138, -1.15908, -0.0887879, 1.01792, 2.25842, 3.64003, 5.25610, 6.96799,
    6.16066, 9.35715, 6.56784, 3.23262, 1.68844, 1.14380, 0.834910, 0.595060, 0.371841, 0.147384, -0.0817569, -0.336770, -0.619794, -0.950460, -1.30082
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 10.8580,

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
"TiltCylExtThresholdStrict" => 97.9218,

# Used to determine if the bucket is near the end of tilt cylinder extension.
# Used to determine fully racked and partial dump status. Fully Racked = ((Cyl%
# > This Value) OR (ABC% > Y)) AND (Bucket Angle > Z). Partial Dump = (Cyl% <=
# This Value) AND (ABC% <= Y) AND (Bucket Angle <= Z)
"TiltCylExtThreshold" => 90.0000,

# Used to determine if the tilt angle is near the rack stops. Used to determine
# fully racked and partial dump status. Fully Racked = ((Cyl% > X) OR (ABC% >
# This Value)) AND (Bucket Angle > Z). Partial Dump = (Cyl% <= X) AND (ABC% <=
# This Value) AND (Bucket Angle <= Z)
"TiltAngleABCThreshold" => 90.0000,

}

MachineType = {
  "InternalMsn" => "CAT82700",
  "Make" => "CAT",
  "Model" => "982",
  "ModelDetail" => "982",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}
