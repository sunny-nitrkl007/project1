##
## CAT 950H - Logger-Bucket
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-41.3100, 43.6300],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-41.3100, -37.8200, -34.3300, -30.8400, -27.3300, -23.8000, -20.2200, -16.6000, -12.9000, -9.13000, -5.26000, -1.28000, 0.00000, 2.85000, 7.13000, 11.6300, 16.3700, 21.4200, 26.8900, 32.9100, 43.6300],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1388.00, 1429.00, 1470.00, 1511.10, 1552.10, 1593.10, 1634.10, 1675.20, 1716.20, 1757.20, 1798.30, 1839.30, 1852.10, 1880.30, 1921.30, 1962.40, 2003.40, 2044.40, 2085.40, 2126.50, 2188.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0853952, 0.0850101, 0.0849607, 0.0852185, 0.0857680, 0.0866019, 0.0877299, 0.0891599, 0.0909291, 0.0930656, 0.0956320, 0.0986997, 0.0997859, 0.102392, 0.106839, 0.112302, 0.119095, 0.127771, 0.139302, 0.155439, 0.198569],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1054.29, 1084.57, 1114.85, 1145.20, 1175.47, 1205.71, 1235.93, 1266.19, 1296.33, 1326.42, 1356.51, 1386.45, 1395.77, 1416.28, 1445.97, 1475.57, 1504.86, 1533.84, 1562.34, 1590.16, 1628.79],

# deg/s^2
"outLiftAngleAccel" => [-0.0884867, -0.0329936, 0.0168421, 0.0631697, 0.107966, 0.152700, 0.199146, 0.248620, 0.303335, 0.365189, 0.437339, 0.523652, 0.554630, 0.630383, 0.765583, 0.944407, 1.18958, 1.54407, 2.09516, 3.03733, 6.71317],

# mm/s
"liftRefVel" => 80.0000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 2795.00,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-41.3100, 43.6300],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1388.00, 2188.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 6.24857, 12.4987, 18.7457, 24.9958, 31.2551, 37.3587, 43.6332, 49.9199, 56.2219, 62.4842, 68.7465, 75.0332, 81.2955, 87.5700, 93.8170, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [0.850000, 10.9600, 26.0200, 42.5500, 58.2200, 72.1700, 84.0900, 94.7800, 104.250, 112.760, 120.530, 127.880, 135.030, 142.250, 149.950, 158.910, 171.870],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [0.850000, 10.9600, 26.0200, 42.5500, 58.2200, 72.1700, 84.0900, 94.7800, 104.250, 112.760, 120.530, 127.880, 135.030, 142.250, 149.950, 158.910, 171.870],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-41.3100, -36.0000, -30.6900, -25.3800, -20.0700, -14.7700, -9.46000, -4.15000, 1.16000, 6.47000, 11.7800, 17.0900, 22.4000, 27.7000, 33.0100, 38.3200, 43.6300],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1062.00, 1055.00, 1052.10, 1053.80, 1059.50, 1069.40, 1083.10, 1100.50, 1121.20, 1144.90, 1171.30, 1199.80, 1230.20, 1262.00, 1294.90, 1328.50, 1362.50,
    1089.10, 1083.30, 1081.70, 1084.30, 1091.10, 1102.00, 1116.70, 1134.90, 1156.40, 1180.70, 1207.60, 1236.60, 1267.30, 1299.40, 1332.50, 1366.20, 1400.20,
    1120.30, 1115.60, 1115.00, 1118.60, 1126.40, 1138.10, 1153.60, 1172.50, 1194.60, 1219.50, 1246.80, 1276.10, 1307.10, 1339.40, 1372.60, 1406.40, 1440.50,
    1155.20, 1151.40, 1151.70, 1156.20, 1164.70, 1177.20, 1193.30, 1212.80, 1235.40, 1260.70, 1288.30, 1318.00, 1349.20, 1380.60, 1414.00, 1447.80, 1482.90,
    1193.20, 1190.20, 1191.20, 1196.40, 1205.60, 1218.60, 1235.30, 1254.20, 1277.30, 1302.90, 1330.90, 1360.80, 1392.20, 1424.70, 1458.10, 1492.10, 1526.20,
    1233.90, 1231.40, 1233.10, 1237.80, 1247.60, 1261.20, 1278.20, 1298.50, 1321.90, 1347.80, 1375.80, 1405.90, 1437.50, 1470.00, 1503.60, 1537.50, 1571.60,
    1275.60, 1273.80, 1275.90, 1282.10, 1292.20, 1306.10, 1323.40, 1344.10, 1367.60, 1393.70, 1421.80, 1452.10, 1483.80, 1516.40, 1549.90, 1583.90, 1617.90,
    1320.00, 1318.60, 1321.20, 1327.70, 1338.00, 1352.20, 1369.60, 1390.50, 1414.10, 1440.20, 1468.60, 1498.70, 1530.50, 1563.00, 1596.60, 1630.50, 1664.60,
    1365.80, 1364.60, 1367.30, 1374.00, 1384.60, 1398.70, 1416.40, 1437.20, 1460.90, 1487.10, 1515.40, 1545.60, 1577.20, 1609.90, 1643.50, 1677.40, 1711.50,
    1412.40, 1411.20, 1414.00, 1420.70, 1431.40, 1445.70, 1463.30, 1484.10, 1507.70, 1533.90, 1562.20, 1592.30, 1624.00, 1656.60, 1690.10, 1724.00, 1758.10,
    1459.00, 1458.00, 1460.90, 1467.60, 1478.20, 1492.40, 1510.00, 1530.70, 1554.30, 1580.30, 1608.60, 1638.60, 1670.10, 1702.80, 1736.20, 1770.20, 1804.30,
    1505.80, 1504.70, 1507.50, 1514.20, 1524.70, 1538.70, 1556.10, 1576.80, 1600.20, 1626.10, 1654.20, 1684.20, 1715.70, 1748.20, 1781.70, 1815.60, 1849.70,
    1552.50, 1551.20, 1553.80, 1560.30, 1570.50, 1584.50, 1601.70, 1622.10, 1645.30, 1671.10, 1699.00, 1728.90, 1760.20, 1792.70, 1826.10, 1859.90, 1894.00,
    1598.50, 1597.00, 1599.30, 1605.70, 1615.70, 1629.30, 1646.20, 1666.40, 1689.50, 1714.90, 1742.70, 1772.30, 1803.60, 1836.00, 1869.30, 1903.10, 1937.20,
    1643.60, 1641.90, 1644.00, 1650.00, 1659.70, 1673.00, 1689.70, 1709.50, 1732.20, 1757.50, 1785.10, 1814.50, 1845.60, 1877.90, 1911.10, 1944.90, 1978.90,
    1687.70, 1685.70, 1687.50, 1693.10, 1702.50, 1715.30, 1731.60, 1751.20, 1773.60, 1798.60, 1825.90, 1855.10, 1886.10, 1918.10, 1951.30, 1985.00, 2019.10,
    1730.70, 1728.20, 1729.60, 1734.80, 1743.70, 1756.30, 1772.20, 1791.30, 1813.40, 1838.00, 1865.10, 1894.10, 1923.90, 1956.70, 1989.70, 2023.40, 2057.40
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [0.850000, 171.870],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-91.1300, 79.8900],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [0.850000, 171.870],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1188.00, 1733.00],

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
"TiltCylBoreDia" => 190.500,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 88.9000,

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
"KgPerLiftKpaAtMidExtension" => 0.735013,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1328.10,

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
"LiftCylExtPctAxis" => [0.00000, 13.8750, 29.2500, 48.6250, 61.7500, 69.5000, 75.6250, 80.6250, 84.7500, 88.2500, 91.2500, 93.8750, 96.1250, 98.1250, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 6.05505, 11.3761, 16.1468, 20.3670, 24.4037, 28.0734, 31.5596, 34.8624, 37.9817, 40.9174, 43.8532, 46.9725, 50.6422, 55.9633, 65.3211, 73.5780, 82.0183, 91.9266, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    11.7582, -75.4623, -31.9843, 133.664, 210.392, 152.518, 13.6446, -163.940, -365.513, -603.804, -905.537, -1346.55, -2211.64, -2946.20, -3647.42,
    -39.8215, -108.501, -59.8226, 124.678, 278.105, 311.534, 236.038, 73.1128, -129.107, -348.948, -589.612, -872.560, -1223.64, -1737.88, -2891.49,
    -68.3424, -129.838, -83.7847, 96.4312, 281.164, 383.519, 401.073, 311.394, 133.333, -90.9152, -330.772, -586.082, -862.349, -1191.44, -1649.06,
    -85.1373, -144.084, -102.921, 64.6089, 253.015, 389.385, 477.179, 480.661, 380.552, 189.858, -51.8467, -314.266, -580.910, -868.659, -1217.14,
    -95.1729, -153.496, -117.338, 35.9929, 215.470, 361.846, 487.124, 560.387, 549.296, 436.930, 234.462, -25.4589, -301.456, -589.180, -912.374,
    -101.657, -160.120, -128.742, 10.4126, 175.603, 319.222, 459.831, 576.039, 637.643, 616.794, 496.867, 283.659, 15.6759, -281.349, -609.673,
    -105.515, -164.389, -137.093, -10.4075, 139.671, 274.410, 416.015, 551.470, 657.600, 708.473, 677.170, 546.548, 328.330, 45.0836, -290.876,
    -107.745, -167.086, -143.320, -27.6887, 107.654, 230.972, 366.074, 506.220, 635.447, 734.084, 776.027, 735.585, 600.387, 372.500, 56.4240,
    -108.792, -168.547, -147.771, -41.7281, 80.0875, 191.465, 316.473, 452.623, 589.762, 714.737, 806.662, 841.149, 794.607, 652.252, 398.833,
    -108.974, -169.042, -150.759, -52.9313, 56.8733, 156.854, 270.556, 398.191, 533.808, 669.558, 790.394, 877.110, 904.413, 851.371, 689.697,
    -108.523, -168.787, -152.560, -61.7216, 37.6226, 127.237, 229.745, 346.992, 475.887, 612.428, 746.556, 864.745, 944.457, 965.943, 899.067,
    -107.535, -167.882, -153.440, -68.9005, 20.8638, 100.719, 192.135, 297.934, 417.005, 548.103, 685.175, 819.828, 933.894, 1012.14, 1029.87,
    -105.955, -166.251, -153.423, -74.8720, 5.68063, 75.9831, 156.159, 249.575, 356.475, 477.536, 609.822, 749.223, 882.336, 999.564, 1085.14,
    -103.458, -163.498, -152.221, -79.8723, -8.93923, 51.2789, 119.302, 198.705, 290.640, 397.046, 517.358, 650.885, 788.936, 927.621, 1061.20,
    -98.7145, -157.975, -148.342, -83.5978, -24.5092, 23.2605, 76.0375, 137.257, 208.575, 292.557, 390.309, 503.641, 628.448, 766.002, 920.130,
    -87.3334, -143.929, -135.719, -81.3817, -38.3281, -7.07246, 25.4640, 62.0536, 104.255, 154.237, 213.547, 284.611, 366.725, 463.488, 582.939,
    -73.9448, -126.514, -118.350, -71.4656, -39.1748, -18.2613, 2.00299, 23.7903, 48.3078, 77.0383, 111.106, 152.222, 200.412, 258.423, 332.265,
    -56.2679, -102.304, -93.4662, -54.4386, -31.6823, -18.7809, -7.35109, 4.20717, 16.7313, 31.0983, 47.9585, 68.2485, 92.0941, 121.011, 158.273,
    -27.7190, -59.2505, -50.3291, -25.7983, -14.9322, -9.80219, -5.77804, -2.05054, 1.76333, 5.98907, 10.8514, 16.6445, 23.4284, 31.6619, 42.3184,
    2.80861, 16.0637, 10.2496, 3.89120, 2.12760, 1.43516, 0.944095, 0.520234, 0.106161, -0.339993, -0.845380, -1.44274, -2.14002, -2.98606, -4.08294
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
"TiltCylExtThresholdStrict" => 97.8991,

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
  "InternalMsn" => "CAT50002",
  "Make" => "CAT",
  "Model" => "950H",
  "ModelDetail" => "950H",
  "Linkage" => "Logger-Bucket",
  "LinkageConfigurationNumber" => 367
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
