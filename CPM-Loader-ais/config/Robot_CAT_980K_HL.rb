##
## CAT 980K - High Lift
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
"outLiftPresNoBucket" => [1448.35, 1496.08, 1543.90, 1591.62, 1639.30, 1686.95, 1734.54, 1782.15, 1829.57, 1876.88, 1924.04, 1971.09, 2017.78, 2064.12, 2109.92, 2154.96, 2198.42, 2238.60],

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
"KnmaticsTiltCylLenMinMax" => [1475.00, 2057.00],

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
"TiltCylBoreDia" => 140.000,

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
"LoaderBktPayldTrgtWt" => 9.11500,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 12.0000,

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
"KgPerLiftKpaAtMidExtension" => 0.988977,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1839.16,

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
"TiltCylExtPctAxis" => [0.00000, 6.18557, 11.5120, 16.3230, 20.7904, 24.9141, 28.8660, 32.6460, 36.2543, 39.6907, 42.9553, 46.0481, 48.9691, 52.2337, 56.1856, 63.4021, 71.1340, 78.8660, 88.1443, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -65.3088, -124.935, -8.80584, 195.720, 209.405, 93.7552, -61.2206, -226.524, -418.469, -662.601, -1042.79, -1867.64, -2628.49, -3289.51, -3913.43,
    -125.829, -149.375, -35.3148, 206.802, 339.538, 319.588, 173.324, -15.0615, -207.834, -409.399, -652.626, -960.097, -1462.38, -2739.34, -3803.49,
    -144.149, -159.376, -59.3237, 171.146, 358.592, 455.442, 410.028, 240.438, 22.4632, -194.291, -420.315, -660.311, -962.504, -1362.26, -2121.15,
    -147.829, -163.289, -77.9625, 126.084, 319.451, 481.529, 555.897, 488.529, 296.474, 56.3198, -192.102, -428.648, -688.120, -976.431, -1372.72,
    -145.875, -164.106, -91.6697, 84.5672, 261.902, 441.607, 591.440, 646.082, 558.252, 348.896, 78.8424, -182.787, -447.141, -709.549, -1024.05,
    -141.724, -163.168, -101.210, 50.6576, 205.691, 377.163, 554.534, 691.463, 726.963, 619.562, 383.371, 103.490, -187.855, -460.261, -757.545,
    -136.632, -161.128, -107.779, 23.3443, 155.837, 308.530, 484.289, 658.350, 785.498, 804.029, 673.425, 428.531, 121.106, -177.888, -489.664,
    -131.213, -158.352, -111.975, 2.03524, 114.352, 245.748, 405.703, 584.627, 757.904, 874.245, 876.020, 733.363, 465.098, 153.971, -185.588,
    -125.767, -155.085, -114.316, -14.2297, 80.9960, 192.309, 331.720, 498.332, 682.915, 852.684, 961.640, 948.031, 785.362, 514.975, 166.592,
    -120.440, -151.492, -115.224, -26.4179, 54.7045, 148.517, 267.444, 414.917, 590.876, 778.066, 949.977, 1044.36, 1015.09, 845.973, 543.865,
    -115.302, -147.694, -115.036, -35.3772, 34.2436, 113.376, 213.902, 341.068, 499.491, 682.176, 878.944, 1040.64, 1126.28, 1084.53, 889.194,
    -110.385, -143.779, -114.020, -41.8079, 18.4687, 85.5171, 170.318, 278.625, 417.030, 584.488, 781.482, 973.548, 1134.73, 1205.26, 1143.89,
    -105.703, -139.812, -112.386, -46.2730, 6.40669, 63.5909, 135.292, 227.147, 346.262, 494.705, 678.894, 876.152, 1075.23, 1222.99, 1282.74,
    -100.421, -135.080, -109.854, -49.6484, -4.23490, 43.5378, 102.607, 178.141, 276.962, 402.732, 564.947, 750.456, 960.403, 1155.17, 1314.80,
    -93.9451, -128.931, -105.881, -51.7654, -13.6923, 24.6649, 71.0561, 129.913, 207.160, 306.878, 439.199, 597.982, 792.566, 998.804, 1217.46,
    -81.7844, -116.459, -96.2942, -51.0881, -23.2656, 2.30900, 31.6420, 67.8864, 115.077, 176.416, 259.682, 363.888, 500.748, 662.402, 866.763,
    -67.9980, -101.037, -82.8919, -45.3004, -25.3879, -9.04490, 8.37737, 29.0171, 55.3239, 89.2663, 135.510, 194.222, 273.454, 371.160, 503.191,
    -52.9278, -82.7867, -66.1574, -35.5733, -21.7575, -11.7515, -1.98506, 8.97100, 22.5168, 39.7292, 63.0484, 92.7036, 133.058, 183.597, 253.611,
    -31.9649, -54.8907, -40.7904, -20.1240, -12.6707, -8.08479, -4.11729, -0.00124746, 4.86723, 10.9148, 19.0242, 29.3081, 43.3335, 61.0111, 85.7709,
    2.73078, 7.46477, 3.80881, 1.36416, 0.832244, 0.571374, 0.375491, 0.187976, -0.0260937, -0.289405, -0.643256, -1.09509, -1.71660, -2.50705, -3.62506
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
  "InternalMsn" => "CAT80201",
  "Make" => "CAT",
  "Model" => "980K",
  "ModelDetail" => "980K",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
