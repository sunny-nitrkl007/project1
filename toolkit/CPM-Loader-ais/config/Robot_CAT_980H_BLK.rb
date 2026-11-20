##
## CAT 980H - Block Handler
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
"outLiftPresNoBucket" => [1046.05, 1104.92, 1157.27, 1208.99, 1261.04, 1311.88, 1362.46, 1411.22, 1460.01, 1507.24, 1553.99, 1598.63, 1643.32, 1687.53, 1730.66, 1774.51, 1820.37, 1862.88],

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
"KnmaticsTiltCylLenMinMax" => [1249.00, 1828.00],

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
"TiltCylBoreDia" => 177.800,

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
"LoaderBktPayldTrgtWt" => 10.4130,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 13.5000,

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
"KgPerLiftKpaAtMidExtension" => 1.25069,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1393.40,

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
"LiftCylExtPctAxis" => [0.00000, 13.8889, 32.1759, 51.9676, 63.4259, 70.8333, 76.6204, 81.3657, 85.3009, 88.6574, 91.5509, 94.0972, 96.2963, 98.2639, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 6.04491, 11.2263, 16.0622, 20.5527, 24.6978, 28.6701, 32.4698, 36.0967, 39.5509, 42.8325, 45.9413, 49.0501, 52.3316, 56.6494, 64.4214, 72.1934, 79.9655, 89.2919, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -64.6166, -120.790, -47.0675, 129.357, 180.137, 107.730, -17.3869, -160.691, -325.273, -539.905, -883.378, -2022.67, -3252.72, -4465.98, -5564.45,
    -119.768, -139.373, -64.6611, 125.224, 257.787, 270.935, 174.877, 22.9981, -140.625, -315.825, -521.745, -804.423, -1297.73, -5474.65, -8571.29,
    -134.160, -144.600, -78.7151, 97.4414, 260.401, 353.562, 342.640, 224.465, 53.0097, -130.233, -319.326, -532.657, -795.998, -1196.04, -2125.78,
    -135.271, -145.054, -89.3912, 65.5114, 226.919, 361.197, 436.402, 406.019, 271.845, 82.8389, -118.189, -324.749, -544.125, -809.206, -1170.26,
    -131.517, -143.355, -96.8367, 37.1893, 183.133, 325.541, 450.212, 509.828, 462.675, 313.699, 109.657, -110.473, -329.727, -565.168, -836.099,
    -126.216, -140.673, -101.664, 14.4911, 141.713, 275.400, 415.757, 531.851, 575.044, 511.159, 347.930, 127.161, -105.477, -344.648, -595.212,
    -120.417, -137.423, -104.620, -3.55096, 105.445, 223.854, 360.292, 499.963, 606.418, 635.978, 558.039, 379.977, 149.052, -103.227, -359.773,
    -114.616, -133.853, -106.094, -17.4475, 75.4523, 177.335, 300.633, 441.379, 578.097, 676.569, 693.861, 601.946, 414.794, 167.063, -101.474,
    -109.022, -130.111, -106.417, -27.8922, 51.4252, 137.959, 245.262, 375.369, 518.099, 652.882, 743.399, 748.848, 646.447, 444.905, 183.670,
    -103.713, -126.289, -105.859, -35.5572, 32.5463, 105.764, 197.417, 312.371, 447.442, 593.050, 725.196, 808.322, 802.362, 686.469, 472.659,
    -98.7120, -122.446, -104.631, -41.0240, 17.9083, 79.9558, 157.630, 256.832, 378.214, 519.294, 666.968, 797.235, 870.650, 852.660, 723.571,
    -94.0144, -118.625, -102.905, -44.7713, 6.67921, 59.5101, 125.245, 209.905, 316.014, 445.095, 591.630, 742.448, 866.798, 931.727, 900.050,
    -89.3498, -114.633, -100.678, -47.2953, -2.29073, 42.5805, 97.8063, 169.081, 259.715, 373.298, 509.157, 662.365, 812.502, 935.937, 993.555,
    -84.4482, -110.230, -97.8266, -48.7949, -9.62265, 28.0782, 73.7477, 132.511, 207.831, 304.118, 423.498, 566.560, 722.023, 877.531, 1002.33,
    -78.0019, -104.127, -93.3448, -49.1915, -16.4252, 13.5020, 48.7950, 93.7412, 151.486, 226.362, 321.872, 442.001, 583.197, 744.136, 908.629,
    -66.2484, -92.1384, -83.3136, -46.1999, -22.2320, -2.59168, 19.1537, 45.9626, 80.0261, 124.433, 182.289, 258.052, 353.143, 473.308, 617.948,
    -53.9775, -78.5225, -70.7643, -39.4448, -21.9707, -9.31047, 3.62882, 18.8480, 37.7282, 62.1251, 93.9827, 136.224, 190.522, 261.824, 352.828,
    -40.6865, -62.5646, -55.3783, -29.7557, -17.5743, -9.85988, -2.68686, 5.26167, 14.8021, 26.9322, 42.6787, 63.5867, 90.6695, 126.752, 173.870,
    -22.2935, -38.1010, -31.8783, -15.2011, -8.99612, -5.70756, -3.01408, -0.266553, 2.88296, 6.79832, 11.8337, 18.5070, 27.1763, 38.8064, 54.1620,
    3.95572, 10.9871, 6.86745, 2.21105, 1.22925, 0.817398, 0.520019, 0.235698, -0.0827518, -0.477942, -0.989665, -1.67432, -2.57262, -3.78962, -5.41271
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
"TiltCylExtThresholdStrict" => 97.2729,

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
  "InternalMsn" => "CAT80005",
  "Make" => "CAT",
  "Model" => "980H",
  "ModelDetail" => "980H",
  "Linkage" => "Block Handler",
  "LinkageConfigurationNumber" => 369
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
