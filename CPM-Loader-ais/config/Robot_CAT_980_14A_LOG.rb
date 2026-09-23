##
## CAT 980 - Logger
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
"outLiftPresNoBucket" => [1254.98, 1322.56, 1382.67, 1441.99, 1501.59, 1559.68, 1617.31, 1672.66, 1727.79, 1780.88, 1833.08, 1882.50, 1931.50, 1979.36, 2025.33, 2071.21, 2118.08, 2160.40],

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
"inTiltDc" => [0.00000, 6.66209, 11.5358, 15.7412, 19.8001, 23.8376, 28.0644, 32.5963, 37.6043, 43.2044, 49.5552, 56.7529, 64.8493, 73.7209, 82.9587, 91.9738, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [27.4000, 36.1800, 44.9600, 53.6800, 62.5000, 71.2800, 80.0600, 88.8300, 97.6100, 106.380, 115.160, 123.940, 132.710, 141.510, 150.270, 159.050, 167.820],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [27.0000, 32.5000, 40.0000, 58.5000, 66.5000, 73.5000, 80.5000, 87.0000, 93.0000, 99.0000, 104.500, 110.000, 116.000, 121.500, 127.500, 133.000, 138.500, 152.000, 157.500, 163.000, 168.000],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-41.0000, -37.0000, -35.0000, -32.5000, -28.0000, -24.0000, -19.5000, -14.5000, -10.0000, -5.00000, 0.00000, 5.00000, 10.5000, 16.0000, 22.5000, 29.5000, 37.5000, 47.5000],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1151.16, 1138.44, 1133.12, 1127.48, 1120.24, 1117.02, 1117.06, 1121.67, 1129.84, 1143.22, 1160.89, 1182.51, 1210.43, 1242.15, 1283.76, 1332.55, 1391.97, 1469.45,
    1164.48, 1152.51, 1147.58, 1142.43, 1136.08, 1133.65, 1134.58, 1140.13, 1149.12, 1163.35, 1181.78, 1204.10, 1232.68, 1264.95, 1307.10, 1356.33, 1416.08, 1493.74,
    1180.01, 1168.76, 1164.20, 1159.51, 1154.01, 1152.33, 1154.09, 1160.53, 1170.27, 1185.28, 1204.42, 1227.37, 1256.55, 1289.33, 1331.96, 1381.57, 1441.60, 1519.42,
    1215.81, 1205.86, 1201.95, 1198.10, 1194.09, 1193.73, 1196.92, 1204.89, 1215.92, 1232.24, 1252.57, 1276.56, 1306.73, 1340.34, 1383.74, 1433.97, 1494.45, 1572.49,
    1232.23, 1222.76, 1219.10, 1215.55, 1212.09, 1212.20, 1215.91, 1224.42, 1235.90, 1252.68, 1273.42, 1297.77, 1328.29, 1362.18, 1405.84, 1456.27, 1516.89, 1595.00,
    1247.74, 1238.68, 1235.22, 1231.93, 1228.92, 1229.43, 1233.57, 1242.53, 1254.38, 1271.54, 1292.62, 1317.26, 1348.05, 1382.17, 1426.04, 1476.63, 1537.37, 1615.53,
    1264.73, 1256.07, 1252.81, 1249.77, 1247.21, 1248.10, 1252.66, 1262.05, 1274.26, 1291.78, 1313.17, 1338.10, 1369.14, 1403.47, 1447.54, 1498.29, 1559.13, 1637.33,
    1282.18, 1273.89, 1270.83, 1268.01, 1265.86, 1267.11, 1272.04, 1281.82, 1294.35, 1312.20, 1333.88, 1359.05, 1390.32, 1424.84, 1469.08, 1519.95, 1580.89, 1659.12,
    1300.08, 1292.13, 1289.23, 1286.63, 1284.85, 1286.42, 1291.69, 1301.83, 1314.65, 1332.78, 1354.72, 1380.11, 1411.58, 1446.26, 1490.65, 1541.64, 1602.65, 1680.92,
    1320.02, 1312.41, 1309.68, 1307.30, 1305.89, 1307.77, 1313.38, 1323.86, 1336.96, 1355.38, 1377.55, 1403.15, 1434.82, 1469.65, 1514.19, 1565.28, 1626.36, 1704.66,
    1340.41, 1333.12, 1330.54, 1328.35, 1327.27, 1329.44, 1335.35, 1346.13, 1359.49, 1378.14, 1400.54, 1426.32, 1458.15, 1493.12, 1537.77, 1588.95, 1650.10, 1728.41,
    1363.13, 1356.14, 1353.72, 1351.71, 1350.96, 1353.40, 1359.60, 1370.68, 1384.27, 1403.16, 1425.75, 1451.70, 1483.69, 1518.78, 1563.54, 1614.81, 1676.00, 1754.34,
    1390.89, 1384.23, 1381.97, 1380.16, 1379.75, 1382.48, 1388.98, 1400.36, 1414.19, 1433.32, 1456.11, 1482.22, 1514.36, 1549.56, 1594.43, 1645.77, 1707.02, 1785.37,
    1419.35, 1412.97, 1410.85, 1409.20, 1409.09, 1412.07, 1418.82, 1430.45, 1444.48, 1463.80, 1486.74, 1512.99, 1545.24, 1580.53, 1625.47, 1676.87, 1738.15, 1816.51,
    1453.83, 1447.74, 1445.76, 1444.29, 1444.46, 1447.67, 1454.67, 1466.54, 1480.75, 1500.24, 1523.33, 1549.68, 1582.03, 1617.39, 1662.39, 1713.83, 1775.14, 1853.51,
    1488.57, 1482.71, 1480.84, 1479.50, 1479.90, 1483.30, 1490.47, 1502.52, 1516.86, 1536.46, 1559.64, 1586.07, 1618.47, 1653.87, 1698.90, 1750.35, 1811.67, 1890.04,
    1526.00, 1520.33, 1518.55, 1517.32, 1517.90, 1521.43, 1528.75, 1540.91, 1555.34, 1575.02, 1598.25, 1624.71, 1657.12, 1692.53, 1737.56, 1789.00, 1850.31, 1928.68,
    1624.50, 1619.10, 1617.44, 1616.34, 1617.13, 1620.80, 1628.22, 1640.44, 1654.88, 1674.52, 1697.68, 1724.05, 1756.34, 1791.63, 1836.51, 1887.84, 1949.05, 2027.39,
    1664.28, 1658.89, 1657.24, 1656.14, 1656.92, 1660.56, 1667.94, 1680.10, 1694.46, 1714.01, 1737.07, 1763.33, 1795.51, 1830.69, 1875.48, 1926.71, 1987.86, 2066.18,
    1701.69, 1696.29, 1694.62, 1693.50, 1694.22, 1697.80, 1705.10, 1717.15, 1731.41, 1750.83, 1773.76, 1799.90, 1831.95, 1867.01, 1911.67, 1962.80, 2023.88, 2102.16,
    1732.49, 1727.04, 1725.35, 1724.19, 1724.84, 1728.34, 1735.54, 1747.47, 1761.62, 1780.91, 1803.72, 1829.73, 1861.65, 1896.59, 1941.13, 1992.17, 2053.18, 2131.43
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [27.4000, 167.820],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-86.9300, 53.4900],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [27.4000, 167.820],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1193.00, 1729.00],

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
"TiltCylBoreDia" => 170.000,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 100.000,

##
## Tool
##

# Tool's length between B and C pins, in mm.
"ToolBcLen" => 482.777,

# Tool's angle between line BC and tool's X-axis, in deg.
"ToolBcAngle" => 114.330,

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
"ScaleWeightCapacity" => 14.5000,

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_MWL.json",

# Determines whether or not payload legal for trade is supported.
"LegalForTradeSupported" => true,

# Determines whether or not acceleration compensation is supported for this
# machine configuration
"AccelCompSupported" => true,

# This selects the application number used for selecting the cycle segmentation
# data.
"CycleSegAppNumber" => 8000,

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
"KgPerLiftKpaAtMidExtension" => 0.992600,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1648.97,

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
"LiftCylExtPctAxis" => [0.00000, 9.60648, 23.4954, 43.2870, 58.1019, 67.3611, 74.1898, 79.6296, 84.1435, 87.8472, 91.0880, 93.8657, 96.1806, 98.2639, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 6.34328, 12.8731, 18.8433, 24.2537, 29.2910, 33.9552, 38.4328, 42.5373, 46.4552, 50.3731, 54.1045, 57.6493, 61.0075, 64.5522, 68.6567, 75.1866, 83.9552, 91.9776, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    182.684, 41.2439, -1.67594, 72.0164, 95.9358, 20.6150, -105.286, -290.166, -620.706, -2565.70, -3876.27, -4872.63, -5657.20, -6349.08, -6923.01,
    32.1077, -34.9882, -31.6354, 82.7623, 180.266, 148.423, 35.5847, -118.977, -322.733, -622.783, -1353.97, -2655.02, -3973.59, -5240.89, -6312.82,
    -46.0470, -70.8354, -51.4624, 68.8230, 221.707, 273.680, 208.232, 65.9831, -115.610, -329.087, -622.866, -1125.98, -3624.16, -5496.51, -7076.70,
    -73.0982, -83.0917, -63.4564, 44.2297, 210.668, 330.376, 350.954, 258.557, 89.8875, -110.327, -348.033, -645.681, -1064.25, -2006.98, -2764.39,
    -80.0784, -86.1234, -70.6778, 20.4177, 176.445, 324.394, 419.502, 412.655, 294.074, 107.565, -120.283, -378.509, -676.524, -1092.48, -1761.97,
    -79.6993, -85.5076, -74.9250, 0.512313, 137.655, 286.160, 421.078, 494.849, 461.704, 323.888, 111.666, -137.776, -406.735, -732.449, -1129.66,
    -76.5845, -83.3289, -77.0942, -14.8369, 102.672, 238.538, 383.445, 506.524, 557.834, 500.780, 337.066, 104.075, -156.657, -457.844, -789.374,
    -72.4146, -80.3673, -77.8260, -26.5772, 72.8132, 191.383, 329.197, 471.642, 582.357, 611.539, 529.941, 344.984, 101.906, -189.784, -500.683,
    -68.1139, -77.1549, -77.4927, -34.8741, 49.5215, 151.286, 274.963, 416.499, 555.076, 647.140, 652.323, 544.062, 345.101, 72.6766, -228.408,
    -63.8146, -73.7609, -76.3859, -40.7823, 31.0225, 117.512, 225.056, 355.591, 500.195, 627.927, 703.772, 682.681, 555.422, 328.128, 46.9712,
    -59.4355, -70.1064, -74.5879, -44.9253, 15.9693, 88.6395, 179.874, 294.598, 431.638, 572.298, 694.154, 751.536, 711.745, 560.554, 325.256,
    -55.2377, -66.4115, -72.2881, -47.4049, 4.54623, 65.6308, 142.340, 240.654, 363.489, 500.915, 642.445, 752.081, 790.016, 728.314, 565.070,
    -51.2407, -62.7175, -69.6082, -48.5746, -3.95532, 47.5429, 111.836, 194.969, 301.661, 427.472, 570.374, 706.042, 798.657, 818.465, 739.505,
    -47.4466, -59.0525, -66.6452, -48.7206, -10.1334, 33.4715, 87.3737, 157.226, 248.282, 359.247, 493.131, 635.304, 758.094, 837.961, 837.135,
    -43.4266, -55.0026, -63.0820, -47.9501, -14.9017, 21.4964, 65.8510, 123.183, 198.592, 292.592, 410.927, 546.437, 680.433, 799.154, 863.870,
    -38.7359, -50.0633, -58.4010, -45.9723, -18.4468, 10.8578, 45.8325, 90.6841, 149.882, 224.831, 322.195, 440.062, 567.958, 702.230, 811.585,
    -31.1313, -41.5757, -49.6888, -40.6362, -20.3742, -0.117303, 23.0772, 52.2013, 90.4479, 139.333, 204.516, 287.359, 384.693, 501.227, 620.482,
    -20.4403, -28.6439, -35.2470, -29.5516, -17.1412, -5.94019, 6.01103, 20.4086, 38.9355, 62.5141, 94.2694, 135.698, 186.651, 252.339, 327.747,
    -9.88793, -14.6343, -18.4868, -15.4826, -9.50970, -4.69894, 0.0423570, 5.47824, 12.2787, 20.8161, 32.2761, 47.3130, 66.0863, 90.9392, 120.672,
    1.67696, 2.69212, 3.50830, 2.85220, 1.76825, 1.00912, 0.328044, -0.407368, -1.29527, -2.38862, -3.84282, -5.74699, -8.13383, -11.3261, -15.2121
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
"FullRackBktAngleThreshold" => 10.0000,

# The bucket is considered partially dumped if the bucket angle is less than or
# equal to this value, as well as other conditions. Partial Dump = (Cyl% <= X)
# AND (ABC% <= Y) AND (Bucket Angle <= This Value)
"PartDumpBktAngleThreshold" => 15.0000,

# The bucket is considered fully dumped if the bucket angle is less than this
# value. Fully Dumped = (Bucket Angle <= This Value), in degrees.
"FullDumpBktAngleThreshold" => -35.0000,

# Used to determine if the bucket is fully racked back for LFT payload. LFT
# Fully Racked = Cyl% > This Value
"TiltCylExtThresholdStrict" => 97.8806,

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
  "InternalMsn" => "CAT80702",
  "Make" => "CAT",
  "Model" => "980",
  "ModelDetail" => "980",
  "Linkage" => "Logger",
  "LinkageConfigurationNumber" => 367
}
