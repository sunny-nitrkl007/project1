##
## CAT 950K - Standard
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-38.8300, 40.6900],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-38.8300, -36.2900, -33.7400, -31.1800, -28.5900, -25.9800, -23.3400, -20.6600, -17.9500, -15.1900, -12.3800, -9.51000, -6.57000, -3.56000, -0.470000, 2.73000, 6.03000, 9.47000, 13.0600, 16.8400, 20.8300, 25.1100, 29.7500, 34.8700, 40.6900],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1275.90, 1304.70, 1333.50, 1362.20, 1391.00, 1419.80, 1448.60, 1477.40, 1506.10, 1534.90, 1563.70, 1592.50, 1621.30, 1650.00, 1678.80, 1707.60, 1736.40, 1765.20, 1793.90, 1822.70, 1851.50, 1880.30, 1909.10, 1937.80, 1966.60],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0881035, 0.0884236, 0.0888972, 0.0895212, 0.0903008, 0.0912362, 0.0923357, 0.0936120, 0.0950708, 0.0967367, 0.0986287, 0.100777, 0.103220, 0.105995, 0.109160, 0.112810, 0.117019, 0.121952, 0.127784, 0.134810, 0.143410, 0.154299, 0.168588, 0.188382, 0.218303],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1443.32, 1485.83, 1528.47, 1571.14, 1614.19, 1657.52, 1701.17, 1745.22, 1789.55, 1834.56, 1880.17, 1926.48, 1973.59, 2021.48, 2070.66, 2121.18, 2173.31, 2227.44, 2283.88, 2343.74, 2407.92, 2478.09, 2557.10, 2649.82, 2768.10],

# deg/s^2
"outLiftAngleAccel" => [0.0401061, 0.0658947, 0.0911498, 0.116313, 0.141997, 0.168523, 0.196431, 0.226315, 0.258614, 0.294222, 0.333949, 0.378950, 0.430704, 0.490927, 0.562098, 0.648152, 0.753380, 0.885742, 1.05591, 1.28216, 1.59305, 2.04462, 2.74406, 3.93392, 6.28274],

# mm/s
"liftRefVel" => 69.0700,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 2976.55,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-38.8300, 40.6900],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1275.90, 1966.60],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 6.75250, 10.7520, 13.9981, 16.9429, 19.7507, 22.5175, 25.3253, 28.2153, 31.2423, 34.4336, 37.8441, 41.5012, 45.4595, 49.7329, 54.3624, 59.3617, 64.6898, 70.2917, 76.0581, 81.7970, 87.3031, 92.3161, 96.6032, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [14.9400, 21.7000, 28.4600, 35.2200, 41.9900, 48.7500, 55.5100, 62.2700, 69.0300, 75.8000, 82.5600, 89.3200, 96.0800, 102.850, 109.610, 116.370, 123.130, 129.890, 136.660, 143.420, 150.180, 156.940, 163.700, 170.470, 177.230],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [14.9400, 21.7000, 28.4600, 35.2200, 41.9900, 48.7500, 55.5100, 62.2700, 69.0300, 75.8000, 82.5600, 89.3200, 96.0800, 102.850, 109.610, 116.370, 123.130, 129.890, 136.660, 143.420, 150.180, 156.940, 163.700, 170.470, 177.230],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-38.8300, -36.2900, -33.7400, -31.1800, -28.5900, -25.9800, -23.3400, -20.6600, -17.9500, -15.1900, -12.3800, -9.51000, -6.57000, -3.56000, -0.470000, 2.73000, 6.03000, 9.47000, 13.0600, 16.8400, 20.8300, 25.1100, 29.7500, 34.8700, 40.6900],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    987.900, 990.300, 993.600, 997.800, 1002.90, 1009.00, 1016.00, 1023.90, 1032.80, 1042.70, 1053.60, 1065.50, 1078.50, 1092.50, 1107.60, 1123.90, 1141.40, 1160.30, 1180.50, 1202.30, 1225.80, 1251.30, 1279.10, 1309.90, 1344.70,
    1023.90, 1026.90, 1030.90, 1035.70, 1041.50, 1048.20, 1055.80, 1064.30, 1073.70, 1084.10, 1095.50, 1107.80, 1121.20, 1135.60, 1151.10, 1167.80, 1185.60, 1204.70, 1225.20, 1247.10, 1270.80, 1296.40, 1324.20, 1355.00, 1389.60,
    1047.70, 1051.20, 1055.50, 1060.70, 1066.70, 1073.70, 1081.60, 1090.40, 1100.10, 1110.80, 1122.40, 1135.00, 1148.50, 1163.10, 1178.80, 1195.60, 1213.60, 1232.80, 1253.40, 1275.50, 1299.20, 1324.80, 1352.70, 1383.40, 1417.90,
    1068.50, 1072.20, 1076.80, 1082.20, 1088.50, 1095.70, 1103.80, 1112.80, 1122.70, 1133.60, 1145.30, 1158.10, 1171.80, 1186.60, 1202.40, 1219.30, 1237.40, 1256.70, 1277.30, 1299.50, 1323.20, 1348.90, 1376.70, 1407.40, 1441.90,
    1088.20, 1092.10, 1096.90, 1102.50, 1109.00, 1116.40, 1124.70, 1133.80, 1143.90, 1154.90, 1166.80, 1179.70, 1193.60, 1208.40, 1224.30, 1241.30, 1259.50, 1278.90, 1299.60, 1321.80, 1345.60, 1371.20, 1399.10, 1429.80, 1464.20,
    1107.80, 1111.80, 1116.80, 1122.60, 1129.30, 1136.80, 1145.30, 1154.60, 1164.80, 1175.90, 1187.90, 1200.90, 1214.90, 1229.80, 1245.80, 1262.90, 1281.20, 1300.60, 1321.40, 1343.60, 1367.40, 1393.10, 1420.90, 1451.60, 1486.00,
    1127.70, 1132.00, 1137.10, 1143.10, 1149.90, 1157.60, 1166.10, 1175.60, 1185.90, 1197.10, 1209.30, 1222.40, 1236.40, 1251.50, 1267.50, 1284.70, 1303.00, 1322.50, 1343.30, 1365.50, 1389.40, 1415.00, 1442.90, 1473.60, 1507.90,
    1148.50, 1152.90, 1158.20, 1164.30, 1171.30, 1179.10, 1187.80, 1197.30, 1207.80, 1219.10, 1231.40, 1244.50, 1258.70, 1273.80, 1289.90, 1307.10, 1325.50, 1345.00, 1365.90, 1388.10, 1412.00, 1437.70, 1465.60, 1496.20, 1530.50,
    1170.50, 1175.10, 1180.50, 1186.70, 1193.80, 1201.70, 1210.50, 1220.20, 1230.70, 1242.20, 1254.50, 1267.80, 1282.00, 1297.20, 1313.40, 1330.60, 1349.00, 1368.60, 1389.50, 1411.70, 1435.60, 1461.30, 1489.20, 1519.80, 1554.10,
    1194.00, 1198.70, 1204.30, 1210.60, 1217.80, 1225.90, 1234.80, 1244.50, 1255.20, 1266.70, 1279.10, 1292.40, 1306.70, 1321.90, 1338.20, 1355.50, 1373.90, 1393.60, 1414.50, 1436.80, 1460.70, 1486.40, 1514.20, 1544.80, 1579.00,
    1219.40, 1224.30, 1229.90, 1236.40, 1243.70, 1251.80, 1260.80, 1270.70, 1281.40, 1293.00, 1305.50, 1318.90, 1333.20, 1348.50, 1364.80, 1382.10, 1400.60, 1420.30, 1441.20, 1463.50, 1487.40, 1513.10, 1541.00, 1571.60, 1605.80,
    1247.10, 1252.00, 1257.80, 1264.30, 1271.70, 1280.00, 1289.10, 1299.00, 1309.80, 1321.40, 1334.00, 1347.40, 1361.80, 1377.10, 1393.50, 1410.90, 1429.30, 1449.00, 1470.00, 1492.30, 1516.20, 1541.90, 1569.80, 1600.40, 1634.50,
    1277.30, 1282.30, 1288.10, 1294.80, 1302.30, 1310.60, 1319.80, 1329.70, 1340.60, 1352.30, 1364.90, 1378.40, 1392.80, 1408.20, 1424.60, 1442.00, 1460.50, 1480.20, 1501.10, 1523.50, 1547.40, 1573.10, 1601.00, 1631.50, 1665.70,
    1310.30, 1315.40, 1321.40, 1328.10, 1335.70, 1344.00, 1353.30, 1363.30, 1374.20, 1385.90, 1398.60, 1412.10, 1426.50, 1442.00, 1458.40, 1475.80, 1494.30, 1514.00, 1535.00, 1557.40, 1581.30, 1607.00, 1634.90, 1665.40, 1699.50,
    1346.60, 1351.80, 1357.70, 1364.50, 1372.10, 1380.60, 1389.80, 1399.90, 1410.80, 1422.60, 1435.30, 1448.80, 1463.30, 1478.70, 1495.10, 1512.50, 1531.10, 1550.80, 1571.80, 1594.10, 1618.10, 1643.80, 1671.60, 1702.20, 1736.30,
    1386.20, 1391.40, 1397.40, 1404.20, 1411.90, 1420.30, 1429.60, 1439.70, 1450.60, 1462.40, 1475.10, 1488.60, 1503.10, 1518.50, 1534.90, 1552.40, 1570.90, 1590.60, 1611.60, 1634.00, 1657.90, 1683.60, 1711.50, 1742.00, 1776.10,
    1429.00, 1434.30, 1440.30, 1447.10, 1454.80, 1463.20, 1472.50, 1482.60, 1493.50, 1505.30, 1518.00, 1531.50, 1546.00, 1561.40, 1577.80, 1595.20, 1613.70, 1633.40, 1654.40, 1676.70, 1700.60, 1726.40, 1754.20, 1784.80, 1818.90,
    1474.80, 1480.10, 1486.10, 1492.90, 1500.60, 1509.00, 1518.20, 1528.30, 1539.20, 1550.90, 1563.60, 1577.10, 1591.50, 1606.90, 1623.20, 1640.60, 1659.10, 1678.80, 1699.70, 1722.10, 1746.00, 1771.70, 1799.60, 1830.10, 1864.30,
    1522.90, 1528.10, 1534.00, 1540.80, 1548.40, 1556.80, 1566.00, 1576.00, 1586.80, 1598.50, 1611.10, 1624.50, 1638.90, 1654.20, 1670.50, 1687.90, 1706.30, 1726.00, 1746.90, 1769.20, 1793.10, 1818.80, 1846.70, 1877.20, 1911.50,
    1571.80, 1577.00, 1582.90, 1589.60, 1597.10, 1605.40, 1614.50, 1624.40, 1635.20, 1646.80, 1659.20, 1672.60, 1686.90, 1702.20, 1718.40, 1735.70, 1754.10, 1773.70, 1794.50, 1816.80, 1840.70, 1866.40, 1894.30, 1924.90, 1959.10,
    1620.00, 1625.10, 1630.90, 1637.50, 1644.80, 1653.00, 1662.00, 1671.90, 1682.50, 1694.00, 1706.40, 1719.70, 1733.90, 1749.00, 1765.20, 1782.40, 1800.80, 1820.30, 1841.10, 1863.30, 1887.20, 1912.90, 1940.70, 1971.40, 2005.70,
    1665.40, 1670.30, 1676.00, 1682.50, 1689.80, 1697.80, 1706.70, 1716.40, 1727.00, 1738.40, 1750.60, 1763.80, 1777.90, 1793.00, 1809.00, 1826.10, 1844.40, 1863.90, 1884.60, 1906.80, 1930.60, 1956.30, 1984.20, 2014.80, 2049.20,
    1706.00, 1710.80, 1716.40, 1722.70, 1729.80, 1737.80, 1746.50, 1756.10, 1766.50, 1777.80, 1790.00, 1803.00, 1817.00, 1832.00, 1848.00, 1865.00, 1883.20, 1902.50, 1923.20, 1945.40, 1969.20, 1994.80, 2022.70, 2053.40, 2087.80,
    1740.10, 1744.80, 1750.20, 1756.40, 1763.50, 1771.30, 1779.90, 1789.40, 1799.70, 1810.80, 1822.90, 1835.80, 1849.70, 1864.60, 1880.50, 1897.40, 1915.50, 1934.80, 1955.50, 1977.60, 2001.30, 2026.90, 2054.80, 2085.50, 2120.00,
    1766.60, 1771.10, 1776.40, 1782.60, 1789.50, 1797.20, 1805.80, 1815.10, 1825.30, 1836.40, 1848.30, 1861.20, 1875.00, 1889.80, 1905.60, 1922.50, 1940.50, 1959.80, 1980.40, 2002.40, 2026.10, 2051.70, 2079.60, 2110.30, 2144.90
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [14.9400, 177.230],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-86.7600, 75.5300],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [14.9400, 177.230],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1217.90, 1795.50],

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
"ToolBcLen" => 434.015,

# Tool's angle between line BC and tool's X-axis, in deg.
"ToolBcAngle" => 101.698,

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
"KgPerLiftKpaAtMidExtension" => 0.581243,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1955.80,

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
"LiftCylExtPctAxis" => [0.00000, 16.9393, 36.6295, 52.7002, 61.6766, 68.4813, 74.1277, 79.0502, 83.2489, 87.0132, 90.3431, 93.2387, 95.7000, 97.8717, 99.8987],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 5.71330, 10.7341, 15.4086, 19.7368, 23.7188, 27.5277, 30.9903, 34.2798, 37.3961, 40.5125, 43.8019, 47.6108, 52.8047, 61.9806, 70.2909, 78.2548, 87.0845, 94.7715, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -56.2357, -0.287050, 121.898, 220.582, 228.183, 177.454, 81.5739, -49.5089, -202.495, -382.235, -591.623, -837.451, -1130.68, -1520.40, -2172.86,
    -80.6788, -25.8176, 100.127, 231.962, 287.950, 289.747, 238.596, 137.531, 1.11042, -165.894, -356.580, -568.012, -799.196, -1068.09, -1417.58,
    -99.2529, -47.8398, 73.3407, 216.076, 300.668, 345.079, 344.037, 290.848, 189.310, 43.8551, -133.775, -332.239, -543.113, -776.023, -1055.96,
    -113.916, -66.6227, 46.3694, 187.635, 285.153, 356.789, 396.788, 394.543, 342.838, 238.703, 88.5841, -93.6334, -292.601, -510.488, -763.890,
    -125.228, -81.9379, 22.0136, 155.537, 255.397, 340.185, 406.350, 444.335, 441.731, 389.858, 285.289, 135.613, -43.1718, -247.231, -486.362,
    -133.771, -94.0396, 1.29080, 124.678, 221.020, 309.362, 388.703, 452.404, 487.564, 484.280, 432.188, 329.754, 186.661, 7.63505, -213.297,
    -140.348, -103.770, -16.4653, 96.0109, 185.846, 272.074, 355.793, 433.420, 493.806, 528.798, 525.625, 476.164, 381.696, 243.489, 55.1635,
    -145.041, -111.059, -30.6329, 71.6994, 154.168, 235.422, 317.960, 400.552, 474.334, 533.851, 567.073, 563.287, 517.782, 427.918, 284.942,
    -148.422, -116.645, -42.2809, 50.6537, 125.577, 200.526, 278.865, 361.042, 440.349, 513.951, 571.899, 603.523, 601.063, 559.627, 468.982,
    -150.701, -120.775, -51.6893, 32.7850, 100.501, 168.762, 241.406, 319.969, 399.516, 479.311, 551.760, 607.549, 638.114, 638.173, 597.986,
    -152.118, -123.815, -59.5509, 17.0168, 77.7370, 139.096, 205.141, 278.083, 354.418, 434.981, 514.401, 585.230, 639.413, 672.521, 676.950,
    -152.714, -125.888, -66.2315, 2.65360, 56.4020, 110.598, 169.308, 235.105, 305.634, 382.822, 463.238, 541.413, 610.523, 667.665, 708.352,
    -152.284, -126.889, -71.9912, -11.1338, 35.2082, 81.5776, 131.891, 188.831, 250.976, 320.914, 396.859, 475.268, 550.957, 622.821, 689.893,
    -149.808, -125.931, -76.6462, -25.3074, 12.1854, 49.0204, 88.7555, 133.899, 183.810, 241.254, 305.778, 375.657, 447.630, 522.346, 602.164,
    -140.073, -117.930, -76.6893, -38.7736, -13.5851, 9.92165, 34.5551, 62.1891, 92.7687, 128.427, 169.508, 215.723, 265.820, 321.387, 386.300,
    -124.778, -103.620, -68.5927, -40.2118, -23.2277, -8.37736, 6.50932, 22.7311, 40.3864, 60.8388, 84.4445, 111.248, 140.763, 174.225, 214.479,
    -102.718, -82.7270, -54.0147, -33.6890, -22.8269, -14.0307, -5.70774, 2.98228, 12.1643, 22.6008, 34.5178, 47.9962, 62.8593, 79.8057, 100.394,
    -64.5688, -48.3865, -29.8188, -18.8802, -13.7985, -10.0670, -6.80702, -3.61636, -0.407517, 3.11112, 7.02951, 11.3906, 16.1556, 21.5656, 28.1347,
    -2.60115, -1.64246, -0.897931, -0.554180, -0.415702, -0.323071, -0.248352, -0.180164, -0.115466, -0.0477075, 0.0251568, 0.104245, 0.189193, 0.284536, 0.399397,
    209.690, 52.6357, 23.7585, 14.0823, 10.6209, 8.45389, 6.80246, 5.37274, 4.07872, 2.77664, 1.42116, -0.0142596, -1.52880, -3.20696, -5.20906
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
"TiltCylExtThresholdStrict" => 93.8753,

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
  "InternalMsn" => "CAT50200",
  "Make" => "CAT",
  "Model" => "950K",
  "ModelDetail" => "950K",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
