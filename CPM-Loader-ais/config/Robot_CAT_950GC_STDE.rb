##
## CAT 950 GC ELECTRIC - Standard
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-39.5900, 47.0400],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-39.5900, -36.1000, -32.6200, -29.1200, -25.6100, -22.0600, -18.4700, -14.8200, -11.1000, -7.29000, -3.39000, 0.00000, 0.640000, 4.82000, 9.18000, 13.7500, 18.5900, 23.7700, 29.4100, 35.6700, 47.0400],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1388.00, 1429.00, 1470.00, 1511.10, 1552.10, 1593.10, 1634.10, 1675.20, 1716.20, 1757.20, 1798.30, 1832.80, 1839.30, 1880.30, 1921.30, 1962.40, 2003.40, 2044.40, 2085.40, 2126.50, 2188.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0852142, 0.0849551, 0.0850195, 0.0853842, 0.0860350, 0.0869735, 0.0882056, 0.0897525, 0.0916433, 0.0939254, 0.0966499, 0.0993652, 0.0999166, 0.103846, 0.108615, 0.114471, 0.121823, 0.131315, 0.144124, 0.162489, 0.214759],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1543.11, 1584.78, 1626.45, 1668.20, 1709.78, 1751.26, 1792.61, 1833.88, 1874.83, 1915.51, 1955.96, 1989.59, 1995.89, 2035.31, 2074.07, 2112.05, 2148.78, 2183.85, 2216.42, 2244.94, 2269.91],

# deg/s^2
"outLiftAngleAccel" => [-0.0675317, -0.0143416, 0.0338544, 0.0794392, 0.123883, 0.168992, 0.216160, 0.267152, 0.323873, 0.388859, 0.465045, 0.541598, 0.557341, 0.672360, 0.820376, 1.01762, 1.29292, 1.69946, 2.34939, 3.50892, 8.57591],

# mm/s
"liftRefVel" => 80.0000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 2895.00,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-39.5900, 47.0400],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1388.00, 2188.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 6.24247, 12.4956, 18.7518, 25.0050, 31.1116, 37.3770, 43.6728, 49.9413, 56.2066, 62.4903, 68.7434, 75.0118, 81.3046, 87.5853, 93.8262, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [-2.05000, 10.3000, 26.7500, 43.6100, 59.0500, 72.3200, 84.1300, 94.5000, 103.590, 111.800, 119.370, 126.520, 133.490, 140.570, 148.130, 156.860, 169.410],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [-2.05000, 10.3000, 26.7500, 43.6100, 59.0500, 72.3200, 84.1300, 94.5000, 103.590, 111.800, 119.370, 126.520, 133.490, 140.570, 148.130, 156.860, 169.410],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-39.5900, -34.1800, -28.7600, -23.3500, -17.9300, -12.5200, -7.10000, -1.69000, 3.73000, 9.14000, 14.5500, 19.9700, 25.3800, 30.8000, 36.2100, 41.6300, 47.0400],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1210.47, 1204.40, 1203.30, 1206.20, 1213.40, 1224.60, 1239.70, 1258.40, 1280.30, 1305.30, 1332.70, 1362.40, 1393.80, 1426.60, 1460.40, 1494.80, 1529.50,
    1239.60, 1235.00, 1234.60, 1238.40, 1246.40, 1258.50, 1274.30, 1293.70, 1316.30, 1341.80, 1369.70, 1399.70, 1431.30, 1464.30, 1498.30, 1532.80, 1567.60,
    1272.60, 1268.80, 1269.20, 1273.90, 1282.60, 1295.40, 1311.90, 1331.90, 1355.00, 1380.80, 1409.10, 1439.40, 1471.30, 1504.50, 1538.50, 1573.10, 1607.80,
    1308.60, 1305.60, 1306.80, 1312.10, 1321.50, 1334.90, 1351.90, 1372.40, 1394.80, 1421.10, 1449.70, 1480.20, 1512.30, 1545.60, 1579.70, 1614.40, 1649.10,
    1347.40, 1345.00, 1346.80, 1352.70, 1361.70, 1375.50, 1393.00, 1413.90, 1437.70, 1464.20, 1493.00, 1523.70, 1556.00, 1589.40, 1623.60, 1658.20, 1692.90,
    1387.50, 1385.60, 1387.90, 1394.30, 1404.60, 1418.90, 1436.80, 1457.90, 1482.00, 1508.70, 1537.70, 1568.50, 1600.80, 1634.30, 1668.50, 1703.10, 1737.90,
    1430.30, 1428.90, 1431.60, 1438.40, 1449.10, 1463.60, 1481.60, 1503.00, 1527.20, 1554.10, 1583.00, 1614.00, 1646.40, 1679.90, 1714.10, 1748.80, 1783.60,
    1474.80, 1473.60, 1476.50, 1483.60, 1494.40, 1509.10, 1527.40, 1548.80, 1573.10, 1600.00, 1629.00, 1660.00, 1692.40, 1725.90, 1760.20, 1794.90, 1829.60,
    1520.00, 1519.00, 1522.20, 1529.30, 1540.40, 1555.10, 1573.40, 1594.80, 1619.20, 1646.10, 1675.10, 1706.10, 1738.50, 1772.10, 1806.20, 1840.90, 1875.70,
    1565.80, 1565.00, 1568.20, 1575.40, 1586.50, 1601.20, 1619.50, 1640.90, 1665.20, 1692.10, 1721.20, 1752.00, 1784.40, 1817.90, 1852.10, 1886.80, 1921.60,
    1611.90, 1611.10, 1614.30, 1621.40, 1632.50, 1647.20, 1665.30, 1686.70, 1710.90, 1737.70, 1766.70, 1797.50, 1829.80, 1863.20, 1897.50, 1932.10, 1966.90,
    1657.90, 1657.10, 1660.20, 1667.20, 1678.00, 1692.60, 1710.60, 1731.90, 1756.00, 1782.60, 1811.50, 1842.20, 1874.50, 1907.90, 1942.00, 1976.70, 2011.40,
    1703.50, 1702.60, 1705.60, 1712.40, 1723.10, 1737.50, 1755.20, 1776.30, 1800.30, 1826.70, 1855.40, 1886.10, 1918.20, 1951.50, 1985.60, 2020.20, 2055.10,
    1748.70, 1747.40, 1750.10, 1756.70, 1767.20, 1781.30, 1798.90, 1819.70, 1843.40, 1869.70, 1898.30, 1928.70, 1960.70, 1994.00, 2028.00, 2062.60, 2097.30,
    1793.00, 1791.30, 1793.80, 1800.10, 1810.30, 1824.20, 1841.30, 1861.90, 1885.40, 1911.40, 1939.80, 1970.00, 2001.90, 2035.00, 2069.00, 2103.50, 2138.30,
    1836.00, 1834.20, 1836.20, 1842.20, 1852.00, 1865.60, 1882.50, 1902.60, 1925.80, 1951.60, 1979.70, 2009.80, 2041.50, 2074.50, 2108.40, 2142.90, 2177.60,
    1877.90, 1875.60, 1877.30, 1882.90, 1892.40, 1905.50, 1922.10, 1941.90, 1964.70, 1990.20, 2018.00, 2047.90, 2079.40, 2112.20, 2146.10, 2180.50, 2215.30
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [-2.05000, 169.410],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-94.0300, 77.4300],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [-2.05000, 169.410],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1337.00, 1882.00],

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
"BMI_CDL_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiCdl_966_980_MWL_GC.json",

# The BMI J1939 configuration file.
"BMI_J1939_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiJ1939_950_MWL_GC_BEV_SA.json",

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_MWL_GC.json",

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
"KgPerLiftKpaAtMidExtension" => 0.642572,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1920.70,

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
"LiftCylExtPctAxis" => [0.00000, 15.6250, 33.5000, 53.2500, 64.6250, 71.8750, 77.5000, 82.1250, 86.0000, 89.2500, 92.0000, 94.3750, 96.5000, 98.3750, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 6.23853, 11.5596, 16.3303, 20.7339, 24.7706, 28.4404, 31.9266, 35.2294, 38.3486, 41.2844, 44.2202, 47.3394, 51.0092, 56.1468, 65.5046, 73.9450, 82.3853, 92.6606, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    17.3002, -78.6861, 7.46131, 217.331, 257.967, 142.417, -48.9069, -271.465, -525.303, -826.430, -1209.30, -1770.86, -2993.21, -4014.19, -4915.35,
    -40.6987, -116.920, -26.7715, 220.813, 375.821, 380.086, 244.133, 15.0351, -245.495, -516.860, -811.428, -1156.84, -1611.92, -2295.09, -3721.31,
    -72.3188, -141.680, -57.7477, 187.773, 394.311, 501.370, 486.516, 330.956, 72.4676, -218.853, -512.381, -818.758, -1170.01, -1596.62, -2152.09,
    -91.3298, -158.625, -83.3467, 145.450, 363.655, 525.905, 613.394, 582.059, 408.961, 130.721, -185.318, -505.628, -841.320, -1207.09, -1623.41,
    -103.324, -170.466, -103.838, 103.981, 313.938, 495.898, 643.348, 717.341, 671.713, 487.359, 196.408, -143.637, -502.008, -867.344, -1247.91,
    -110.830, -178.533, -119.579, 67.7581, 261.334, 442.483, 615.104, 753.173, 813.943, 755.723, 563.457, 259.997, -112.476, -504.017, -894.285,
    -115.400, -183.835, -131.319, 37.8906, 213.252, 384.032, 560.812, 729.035, 856.950, 903.141, 832.791, 630.066, 303.196, -96.1125, -512.045,
    -118.135, -187.278, -140.275, 12.8298, 170.097, 326.434, 496.272, 673.534, 837.474, 954.963, 990.159, 910.875, 692.048, 346.268, -70.7303,
    -119.524, -189.251, -146.890, -7.75735, 132.772, 273.618, 431.071, 604.639, 782.221, 940.040, 1048.71, 1075.94, 985.160, 752.063, 395.475,
    -119.918, -190.067, -151.571, -24.3992, 101.229, 227.139, 370.226, 533.392, 710.605, 885.953, 1037.86, 1140.36, 1159.98, 1057.07, 814.963,
    -119.578, -189.979, -154.676, -37.6688, 74.9846, 187.257, 315.934, 465.822, 634.871, 813.039, 985.560, 1133.82, 1232.70, 1242.39, 1129.39,
    -118.623, -189.118, -156.600, -48.7432, 52.0474, 151.476, 265.796, 400.819, 557.111, 728.968, 907.152, 1079.80, 1230.96, 1327.51, 1333.25,
    -116.999, -187.407, -157.430, -58.2628, 31.1550, 118.030, 217.783, 336.622, 476.771, 635.690, 808.477, 988.943, 1169.48, 1326.13, 1427.87,
    -114.352, -184.401, -156.909, -66.7323, 10.8627, 84.5287, 168.552, 269.051, 389.187, 528.698, 686.007, 859.484, 1048.51, 1238.86, 1408.62,
    -109.417, -178.468, -153.645, -74.1356, -10.5364, 47.4317, 112.424, 189.932, 283.361, 393.921, 522.398, 670.463, 842.600, 1033.85, 1233.29,
    -96.9509, -162.568, -140.646, -76.2852, -32.0418, 4.57688, 43.5853, 88.9895, 143.420, 208.423, 285.632, 377.775, 490.502, 625.150, 780.452,
    -81.6976, -142.058, -121.248, -67.8716, -36.4321, -13.0834, 10.2032, 36.2715, 66.8875, 103.168, 146.319, 198.261, 262.801, 341.702, 435.626,
    -61.7373, -113.802, -93.6339, -51.2600, -30.3398, -16.6387, -4.06138, 9.28283, 24.4587, 42.1310, 62.9871, 88.0581, 119.323, 157.852, 204.282,
    -27.5753, -60.2553, -44.1098, -21.4107, -13.0077, -8.39240, -4.62988, -0.949858, 3.02480, 7.51565, 12.7298, 18.9494, 26.6877, 36.2405, 47.8080,
    4.26032, 23.5301, 11.9917, 4.64502, 2.76283, 1.86453, 1.19145, 0.569915, -0.0772255, -0.793056, -1.61492, -2.59007, -3.80117, -5.29684, -7.11131
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
"TiltCylExtThresholdStrict" => 97.7156,

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

}

MachineType = {
  "InternalMsn" => "CAT50312",
  "Make" => "CAT",
  "Model" => "950 GC ELECTRIC",
  "ModelDetail" => "950 GC ELECTRIC",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}
