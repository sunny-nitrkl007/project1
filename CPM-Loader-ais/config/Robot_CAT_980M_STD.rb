##
## CAT 980M - Standard
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
"outLiftPresNoBucket" => [1266.95, 1335.41, 1396.29, 1456.38, 1516.76, 1575.62, 1634.03, 1690.15, 1746.06, 1799.92, 1852.90, 1903.11, 1952.92, 2001.62, 2048.47, 2095.28, 2143.21, 2186.59],

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
"xTiltAngle" => [11.0000, 13.0000, 16.0000, 19.5000, 24.5000, 34.0000, 56.5000, 66.0000, 75.0000, 81.5000, 88.0000, 93.5000, 99.5000, 105.000, 110.500, 116.000, 121.000, 127.000, 133.000, 140.000, 153.000, 158.000, 162.000, 167.000, 172.000, 176.500, 181.500],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-41.0000, -37.0000, -33.0000, -29.0000, -25.0000, -20.5000, -16.0000, -11.5000, -6.50000, -1.50000, 3.50000, 9.00000, 14.5000, 20.5000, 27.5000, 35.0000, 44.5000],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1148.66, 1135.78, 1125.69, 1118.52, 1114.37, 1113.36, 1116.24, 1122.97, 1134.83, 1151.07, 1171.38, 1198.02, 1228.62, 1265.88, 1313.50, 1368.24, 1441.09,
    1155.77, 1143.32, 1133.69, 1126.99, 1123.30, 1122.81, 1126.20, 1133.42, 1145.79, 1162.50, 1183.24, 1210.29, 1241.25, 1278.82, 1326.73, 1381.68, 1454.68,
    1163.99, 1151.99, 1142.82, 1136.59, 1133.37, 1133.41, 1137.31, 1145.03, 1157.90, 1175.09, 1196.25, 1223.70, 1255.01, 1292.90, 1341.08, 1396.24, 1469.38,
    1171.94, 1160.34, 1151.57, 1145.74, 1142.93, 1143.42, 1147.76, 1155.89, 1169.21, 1186.79, 1208.31, 1236.11, 1267.70, 1305.85, 1354.27, 1409.60, 1482.85,
    1181.88, 1170.70, 1162.38, 1157.01, 1154.65, 1155.64, 1160.47, 1169.07, 1182.86, 1200.87, 1222.78, 1250.95, 1282.86, 1321.29, 1369.96, 1425.47, 1498.84,
    1198.85, 1188.33, 1180.68, 1175.98, 1174.29, 1176.02, 1181.56, 1190.82, 1205.30, 1223.94, 1246.42, 1275.12, 1307.48, 1346.31, 1395.33, 1451.09, 1524.62,
    1239.06, 1229.78, 1223.37, 1219.92, 1219.46, 1222.53, 1229.35, 1239.81, 1255.52, 1275.27, 1298.72, 1328.35, 1361.48, 1400.98, 1450.59, 1506.78, 1580.56,
    1258.41, 1249.61, 1243.68, 1240.70, 1240.71, 1244.29, 1251.58, 1262.49, 1278.66, 1298.81, 1322.61, 1352.57, 1385.97, 1425.72, 1475.53, 1531.86, 1605.72,
    1279.08, 1270.72, 1265.25, 1262.72, 1263.16, 1267.20, 1274.94, 1286.26, 1302.83, 1323.35, 1347.47, 1377.72, 1411.37, 1451.33, 1501.33, 1557.78, 1631.71,
    1295.85, 1287.83, 1282.68, 1280.47, 1281.22, 1285.59, 1293.64, 1305.25, 1322.11, 1342.88, 1367.22, 1397.68, 1431.50, 1471.60, 1521.72, 1578.26, 1652.24,
    1314.54, 1306.84, 1302.02, 1300.12, 1301.19, 1305.89, 1314.25, 1326.13, 1343.28, 1364.30, 1388.85, 1419.51, 1453.49, 1493.73, 1543.96, 1600.59, 1674.61,
    1332.11, 1324.69, 1320.15, 1318.52, 1319.84, 1324.82, 1333.43, 1345.56, 1362.93, 1384.15, 1408.88, 1439.70, 1473.81, 1514.16, 1564.48, 1621.17, 1695.22,
    1353.42, 1346.31, 1342.07, 1340.73, 1342.33, 1347.60, 1356.49, 1368.85, 1386.47, 1407.90, 1432.81, 1463.79, 1498.04, 1538.50, 1588.92, 1645.66, 1719.75,
    1375.21, 1368.37, 1364.39, 1363.32, 1365.16, 1370.70, 1379.82, 1392.40, 1410.23, 1431.85, 1456.91, 1488.03, 1522.38, 1562.94, 1613.43, 1670.23, 1744.34,
    1399.40, 1392.83, 1389.11, 1388.29, 1390.37, 1396.15, 1405.50, 1418.28, 1436.31, 1458.09, 1483.29, 1514.54, 1548.99, 1589.62, 1640.19, 1697.03, 1771.16,
    1426.22, 1419.91, 1416.44, 1415.85, 1418.16, 1424.17, 1433.72, 1446.69, 1464.90, 1486.82, 1512.14, 1543.50, 1578.03, 1618.73, 1669.35, 1726.22, 1800.37,
    1453.03, 1446.94, 1443.68, 1443.29, 1445.78, 1451.98, 1461.70, 1474.82, 1493.16, 1515.20, 1540.61, 1572.04, 1606.63, 1647.38, 1698.03, 1754.92, 1829.08,
    1488.32, 1482.46, 1479.42, 1479.24, 1481.92, 1488.31, 1498.20, 1511.45, 1529.92, 1552.07, 1577.56, 1609.05, 1643.68, 1684.46, 1735.13, 1792.03, 1866.19,
    1526.83, 1521.16, 1518.31, 1518.30, 1521.12, 1527.66, 1537.67, 1551.02, 1569.57, 1591.77, 1617.30, 1648.81, 1683.46, 1724.23, 1774.90, 1831.79, 1905.95,
    1575.13, 1569.63, 1566.93, 1567.05, 1569.99, 1576.62, 1586.70, 1600.10, 1618.68, 1640.88, 1666.39, 1697.88, 1732.49, 1773.22, 1823.84, 1880.70, 1954.83,
    1668.75, 1663.37, 1660.74, 1660.90, 1663.85, 1670.45, 1680.46, 1693.75, 1712.18, 1734.20, 1759.53, 1790.80, 1825.19, 1865.72, 1916.15, 1972.86, 2046.92,
    1703.40, 1698.00, 1695.35, 1695.46, 1698.35, 1704.88, 1714.80, 1727.99, 1746.30, 1768.20, 1793.40, 1824.55, 1858.83, 1899.24, 1949.56, 2006.20, 2080.22,
    1729.52, 1724.08, 1721.38, 1721.44, 1724.27, 1730.72, 1740.55, 1753.65, 1771.85, 1793.64, 1818.74, 1849.77, 1883.95, 1924.27, 1974.50, 2031.07, 2105.05,
    1759.37, 1753.87, 1751.10, 1751.08, 1753.81, 1760.15, 1769.86, 1782.83, 1800.89, 1822.54, 1847.49, 1878.38, 1912.43, 1952.62, 2002.74, 2059.23, 2133.16,
    1785.39, 1779.82, 1776.97, 1776.86, 1779.50, 1785.72, 1795.31, 1808.15, 1826.07, 1847.58, 1872.40, 1903.14, 1937.07, 1977.14, 2027.15, 2083.55, 2157.44,
    1805.08, 1799.44, 1796.52, 1796.33, 1798.89, 1805.01, 1814.49, 1827.23, 1845.03, 1866.42, 1891.13, 1921.76, 1955.58, 1995.56, 2045.48, 2101.82, 2175.66,
    1822.47, 1816.78, 1813.78, 1813.52, 1816.00, 1822.02, 1831.41, 1844.05, 1861.73, 1883.02, 1907.62, 1938.14, 1971.87, 2011.75, 2061.59, 2117.86, 2191.67
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [11.3400, 181.340],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-92.1100, 77.8900],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [11.3400, 181.340],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1242.00, 1824.00],

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
"TiltCylBoreDia" => 130.000,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 95.0000,

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
"LoaderBktPayldTrgtWt" => 9.96800,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 14.0000,

# The CAT datalink configuration file.
"BMI_CDL_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiCdl_MWL-M.json",

# The BMI J1939 configuration file.
"BMI_J1939_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiJ1939_MWL_M_SA.json",

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_MWL.json",

# Determines whether or not hydraulic oil temperature is optional for this
# machine configuration.
"HydOilTempOptional" => true,

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
"KgPerLiftKpaAtMidExtension" => 1.04521,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1666.40,

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
"LiftCylExtPctAxis" => [0.00000, 13.7731, 32.1759, 52.0833, 63.4259, 70.8333, 76.6204, 81.3657, 85.3009, 88.6574, 91.5509, 94.0972, 96.2963, 98.2639, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 6.18557, 11.5120, 16.3230, 20.7904, 25.0859, 29.0378, 32.8179, 36.4261, 39.8625, 43.1271, 46.2199, 49.3127, 52.5773, 56.5292, 63.5739, 71.4777, 79.0378, 87.9725, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -75.1850, -144.277, -53.1913, 160.768, 211.748, 115.950, -37.8957, -212.717, -416.775, -690.785, -1159.79, -3948.63, -6046.38, -7899.03, -9519.30,
    -144.926, -167.411, -74.7278, 159.005, 315.005, 321.871, 196.495, 9.16070, -189.730, -404.306, -661.205, -1025.62, -1719.69, -2481.45, -3188.88,
    -162.261, -173.555, -92.2162, 124.734, 321.404, 431.180, 409.599, 257.724, 46.0822, -176.812, -407.339, -670.555, -1002.10, -1526.88, -2963.51,
    -163.001, -173.800, -105.100, 85.8462, 281.746, 444.168, 529.595, 481.423, 308.287, 74.6047, -169.700, -420.902, -690.738, -1022.95, -1490.32,
    -158.112, -171.567, -114.125, 51.1768, 228.874, 402.997, 552.176, 615.725, 544.398, 351.395, 98.6412, -168.841, -435.048, -723.980, -1062.46,
    -151.195, -168.061, -120.208, 22.2254, 176.447, 340.208, 511.475, 650.218, 695.004, 605.454, 396.570, 123.266, -160.219, -451.005, -757.783,
    -144.033, -164.044, -123.768, 0.169612, 132.350, 277.642, 444.986, 614.732, 739.826, 765.242, 656.023, 427.287, 140.842, -166.846, -478.828,
    -136.932, -159.678, -125.558, -16.8595, 95.8265, 220.998, 372.734, 545.277, 710.363, 823.496, 831.085, 702.050, 460.602, 152.501, -175.513,
    -130.119, -155.129, -125.972, -29.7000, 66.5142, 172.929, 305.292, 465.652, 640.248, 801.559, 902.491, 892.419, 748.167, 486.978, 161.119,
    -123.675, -150.499, -125.329, -39.1644, 43.4344, 133.534, 246.788, 388.991, 555.501, 732.938, 889.266, 978.218, 951.297, 787.468, 509.211,
    -117.619, -145.855, -123.884, -45.9561, 25.4952, 101.883, 197.987, 321.029, 471.434, 645.154, 824.101, 975.872, 1050.05, 1004.73, 821.858,
    -111.939, -141.247, -121.840, -50.6545, 11.6933, 76.7502, 158.161, 263.373, 395.332, 555.358, 735.332, 916.660, 1058.73, 1118.79, 1053.09,
    -106.307, -136.437, -119.195, -53.8693, 0.627580, 55.8859, 124.334, 213.051, 326.084, 467.599, 635.979, 823.494, 1002.43, 1140.48, 1187.96,
    -100.395, -131.138, -115.801, -55.8500, -8.46380, 37.9566, 94.5932, 167.837, 261.995, 382.438, 531.400, 708.632, 898.338, 1082.36, 1219.63,
    -93.2495, -124.399, -110.920, -56.5606, -16.4243, 21.0932, 65.8043, 123.145, 197.110, 293.136, 415.387, 568.191, 745.535, 943.043, 1136.42,
    -80.3901, -111.402, -100.242, -54.0211, -23.9723, 1.55337, 30.3709, 66.3592, 112.442, 172.755, 251.387, 354.057, 481.979, 641.455, 829.084,
    -65.4077, -94.9406, -85.2708, -46.5525, -24.9029, -8.63138, 8.37363, 28.6963, 54.1698, 87.2995, 130.722, 188.389, 262.466, 359.430, 482.363,
    -49.9680, -76.5569, -67.6687, -35.8424, -20.6367, -10.5920, -0.978772, 9.90814, 23.1630, 40.1659, 62.3592, 91.9229, 130.276, 181.371, 247.964,
    -29.1755, -49.2557, -41.4393, -19.7753, -11.5572, -6.96646, -3.05702, 1.05586, 5.86617, 11.9171, 19.7516, 30.1746, 43.7445, 61.9660, 86.0229,
    5.54932, 16.5098, 9.94864, 3.07987, 1.69199, 1.08919, 0.638753, 0.193984, -0.315078, -0.954458, -1.78750, -2.90556, -4.37492, -6.36739, -9.02618
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 9.96800,

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
"TiltCylExtThresholdStrict" => 96.9381,

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
  "InternalMsn" => "CAT80400",
  "Make" => "CAT",
  "Model" => "980M",
  "ModelDetail" => "980M",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
