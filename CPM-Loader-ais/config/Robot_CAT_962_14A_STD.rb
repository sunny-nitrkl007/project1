##
## CAT 962 - Standard
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-37.3800, 44.4100],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-37.3800, -34.8600, -32.3300, -29.7700, -27.1900, -24.5800, -21.9400, -19.2500, -16.5300, -13.7600, -10.9300, -8.03000, -5.07000, -2.02000, 1.12000, 4.37000, 7.75000, 11.2600, 14.9600, 18.8600, 23.0100, 27.5000, 32.4200, 37.9400, 44.4100],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1302.60, 1331.50, 1360.40, 1389.30, 1418.20, 1447.00, 1475.90, 1504.80, 1533.70, 1562.60, 1591.50, 1620.40, 1649.30, 1678.20, 1707.00, 1735.90, 1764.80, 1793.70, 1822.60, 1851.50, 1880.40, 1909.30, 1938.20, 1967.10, 1995.90],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0870488, 0.0875194, 0.0881338, 0.0888972, 0.0898096, 0.0908792, 0.0921130, 0.0935314, 0.0951369, 0.0969571, 0.0990208, 0.101364, 0.104013, 0.107039, 0.110500, 0.114495, 0.119154, 0.124615, 0.131172, 0.139144, 0.149085, 0.161973, 0.179450, 0.204920, 0.247078],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1318.67, 1356.75, 1395.00, 1433.45, 1472.14, 1511.00, 1550.33, 1590.06, 1630.24, 1670.95, 1712.26, 1754.28, 1797.12, 1840.92, 1885.72, 1932.06, 1980.09, 2030.23, 2083.07, 2139.47, 2200.74, 2269.02, 2348.15, 2445.88, 2580.86],

# deg/s^2
"outLiftAngleAccel" => [0.0662089, 0.0904389, 0.114586, 0.139234, 0.164679, 0.191429, 0.219935, 0.250937, 0.284811, 0.322526, 0.365153, 0.414050, 0.470585, 0.537395, 0.617351, 0.714981, 0.836805, 0.991510, 1.19561, 1.47265, 1.86602, 2.46181, 3.43934, 5.25510, 9.44161],

# mm/s
"liftRefVel" => 69.3300,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 3074.16,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-37.3800, 44.4100],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1302.60, 1995.90],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 5.66685, 9.50878, 12.8019, 15.8480, 18.8117, 21.7755, 24.7942, 27.9089, 31.1745, 34.6048, 38.2547, 42.1652, 46.3502, 50.8370, 55.6394, 60.7574, 66.1498, 71.7344, 77.3875, 82.9446, 88.1998, 92.9199, 96.8990, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [11.6300, 18.4700, 25.3100, 32.1500, 39.0000, 45.8400, 52.6800, 59.5200, 66.3600, 73.2000, 80.0400, 86.8800, 93.7200, 100.560, 107.400, 114.240, 121.090, 127.930, 134.770, 141.610, 148.450, 155.290, 162.130, 168.970, 175.810],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [11.6300, 18.4700, 25.3100, 32.1500, 39.0000, 45.8400, 52.6800, 59.5200, 66.3600, 73.2000, 80.0400, 86.8800, 93.7200, 100.560, 107.400, 114.240, 121.090, 127.930, 134.770, 141.610, 148.450, 155.290, 162.130, 168.970, 175.810],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-37.3800, -34.8600, -32.3300, -29.7700, -27.1900, -24.5800, -21.9400, -19.2500, -16.5300, -13.7600, -10.9300, -8.03000, -5.07000, -2.02000, 1.12000, 4.37000, 7.75000, 11.2600, 14.9600, 18.8600, 23.0100, 27.5000, 32.4200, 37.9400, 44.4100],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1052.60, 1056.10, 1060.40, 1065.70, 1071.80, 1078.80, 1086.70, 1095.60, 1105.40, 1116.10, 1127.80, 1140.60, 1154.40, 1169.20, 1185.20, 1202.30, 1220.70, 1240.50, 1261.70, 1284.60, 1309.30, 1336.20, 1365.80, 1398.90, 1437.00,
    1085.90, 1089.80, 1094.70, 1100.30, 1106.90, 1114.30, 1122.70, 1131.90, 1142.10, 1153.20, 1165.20, 1178.30, 1192.40, 1207.50, 1223.70, 1241.10, 1259.70, 1279.60, 1301.00, 1323.90, 1348.70, 1375.70, 1405.20, 1438.20, 1476.20,
    1110.60, 1114.80, 1119.90, 1125.80, 1132.60, 1140.30, 1148.90, 1158.40, 1168.80, 1180.10, 1192.30, 1205.60, 1219.80, 1235.10, 1251.40, 1268.90, 1287.70, 1307.70, 1329.10, 1352.20, 1377.00, 1403.90, 1433.50, 1466.50, 1504.40,
    1132.80, 1137.20, 1142.50, 1148.70, 1155.70, 1163.60, 1172.30, 1182.00, 1192.50, 1204.00, 1216.40, 1229.80, 1244.10, 1259.50, 1276.00, 1293.60, 1312.40, 1332.50, 1354.00, 1377.00, 1401.90, 1428.90, 1458.40, 1491.30, 1529.10,
    1154.20, 1158.90, 1164.30, 1170.70, 1177.90, 1185.90, 1194.80, 1204.60, 1215.30, 1226.90, 1239.40, 1252.90, 1267.40, 1282.80, 1299.40, 1317.10, 1335.90, 1356.10, 1377.60, 1400.70, 1425.60, 1452.60, 1482.10, 1515.00, 1552.70,
    1175.80, 1180.60, 1186.20, 1192.70, 1200.00, 1208.20, 1217.30, 1227.20, 1238.00, 1249.70, 1262.30, 1275.90, 1290.40, 1306.00, 1322.60, 1340.40, 1359.30, 1379.50, 1401.10, 1424.20, 1449.10, 1476.10, 1505.60, 1538.40, 1576.10,
    1197.90, 1202.90, 1208.70, 1215.30, 1222.80, 1231.10, 1240.20, 1250.20, 1261.20, 1273.00, 1285.70, 1299.30, 1314.00, 1329.60, 1346.30, 1364.10, 1383.00, 1403.30, 1424.90, 1448.10, 1473.00, 1499.90, 1529.50, 1562.30, 1599.90,
    1221.10, 1226.20, 1232.10, 1238.80, 1246.40, 1254.80, 1264.10, 1274.20, 1285.20, 1297.10, 1309.90, 1323.60, 1338.30, 1354.00, 1370.80, 1388.60, 1407.60, 1427.90, 1449.50, 1472.70, 1497.60, 1524.60, 1554.10, 1586.90, 1624.50,
    1245.60, 1250.80, 1256.80, 1263.70, 1271.40, 1279.90, 1289.20, 1299.40, 1310.50, 1322.50, 1335.40, 1349.20, 1363.90, 1379.70, 1396.50, 1414.30, 1433.40, 1453.70, 1475.40, 1498.60, 1523.50, 1550.50, 1580.00, 1612.70, 1650.30,
    1271.70, 1277.00, 1283.10, 1290.10, 1297.90, 1306.50, 1315.90, 1326.20, 1337.40, 1349.40, 1362.40, 1376.20, 1391.00, 1406.80, 1423.60, 1441.60, 1460.60, 1481.00, 1502.70, 1525.90, 1550.80, 1577.80, 1607.30, 1640.00, 1677.50,
    1299.70, 1305.20, 1311.40, 1318.40, 1326.30, 1335.00, 1344.50, 1354.90, 1366.10, 1378.20, 1391.20, 1405.10, 1419.90, 1435.80, 1452.60, 1470.60, 1489.70, 1510.00, 1531.70, 1555.00, 1579.90, 1606.90, 1636.30, 1669.10, 1706.50,
    1330.00, 1335.50, 1341.80, 1349.00, 1356.90, 1365.70, 1375.20, 1385.60, 1396.90, 1409.10, 1422.10, 1436.00, 1450.90, 1466.80, 1483.70, 1501.60, 1520.80, 1541.10, 1562.90, 1586.10, 1611.00, 1638.00, 1667.50, 1700.20, 1737.60,
    1362.80, 1368.40, 1374.80, 1381.90, 1389.90, 1398.70, 1408.40, 1418.80, 1430.10, 1442.30, 1455.40, 1469.30, 1484.20, 1500.10, 1517.00, 1535.00, 1554.20, 1574.50, 1596.30, 1619.50, 1644.50, 1671.40, 1700.90, 1733.60, 1771.00,
    1398.30, 1403.90, 1410.40, 1417.60, 1425.60, 1434.50, 1444.10, 1454.60, 1465.90, 1478.10, 1491.20, 1505.20, 1520.10, 1536.00, 1552.90, 1570.90, 1590.10, 1610.50, 1632.20, 1655.40, 1680.40, 1707.30, 1736.80, 1769.50, 1806.90,
    1436.60, 1442.30, 1448.80, 1456.00, 1464.10, 1472.90, 1482.60, 1493.10, 1504.50, 1516.70, 1529.70, 1543.70, 1558.70, 1574.60, 1591.50, 1609.50, 1628.60, 1649.00, 1670.70, 1693.90, 1718.90, 1745.90, 1775.30, 1808.00, 1845.50,
    1477.90, 1483.60, 1490.00, 1497.30, 1505.30, 1514.20, 1523.90, 1534.40, 1545.70, 1557.90, 1570.90, 1584.90, 1599.80, 1615.70, 1632.60, 1650.60, 1669.70, 1690.10, 1711.80, 1735.00, 1760.00, 1786.90, 1816.40, 1849.10, 1886.60,
    1521.80, 1527.40, 1533.90, 1541.10, 1549.20, 1558.00, 1567.60, 1578.10, 1589.40, 1601.60, 1614.60, 1628.50, 1643.40, 1659.30, 1676.10, 1694.10, 1713.20, 1733.50, 1755.20, 1778.40, 1803.40, 1830.40, 1859.80, 1892.60, 1930.10,
    1567.80, 1573.40, 1579.90, 1587.00, 1595.00, 1603.80, 1613.40, 1623.80, 1635.10, 1647.20, 1660.20, 1674.00, 1688.90, 1704.70, 1721.50, 1739.40, 1758.50, 1778.80, 1800.50, 1823.60, 1848.60, 1875.60, 1905.00, 1937.80, 1975.30,
    1615.10, 1620.70, 1627.10, 1634.20, 1642.10, 1650.80, 1660.30, 1670.60, 1681.80, 1693.80, 1706.80, 1720.60, 1735.30, 1751.10, 1767.80, 1785.70, 1804.70, 1825.00, 1846.60, 1869.80, 1894.70, 1921.70, 1951.20, 1984.00, 2021.60,
    1662.50, 1668.00, 1674.20, 1681.20, 1689.00, 1697.70, 1707.10, 1717.30, 1728.40, 1740.30, 1753.10, 1766.90, 1781.50, 1797.20, 1813.90, 1831.70, 1850.60, 1870.80, 1892.40, 1915.60, 1940.50, 1967.40, 1996.90, 2029.80, 2067.50,
    1708.20, 1713.60, 1719.70, 1726.60, 1734.30, 1742.80, 1752.10, 1762.20, 1773.20, 1785.00, 1797.70, 1811.40, 1825.90, 1841.50, 1858.10, 1875.80, 1894.70, 1914.80, 1936.40, 1959.50, 1984.30, 2011.30, 2040.80, 2073.70, 2111.50,
    1750.60, 1755.80, 1761.80, 1768.60, 1776.20, 1784.50, 1793.70, 1803.70, 1814.60, 1826.30, 1838.90, 1852.40, 1866.80, 1882.30, 1898.80, 1916.40, 1935.20, 1955.30, 1976.80, 1999.80, 2024.70, 2051.60, 2081.20, 2114.10, 2152.00,
    1787.90, 1793.00, 1798.80, 1805.50, 1812.90, 1821.20, 1830.20, 1840.10, 1850.80, 1862.40, 1874.90, 1888.30, 1902.60, 1918.00, 1934.40, 1952.00, 1970.70, 1990.70, 2012.10, 2035.10, 2059.90, 2086.90, 2116.50, 2149.40, 2187.40,
    1818.70, 1823.70, 1829.40, 1836.00, 1843.30, 1851.40, 1860.30, 1870.10, 1880.70, 1892.20, 1904.60, 1917.90, 1932.10, 1947.40, 1963.70, 1981.20, 1999.80, 2019.80, 2041.20, 2064.10, 2088.90, 2115.80, 2145.40, 2178.40, 2216.40,
    1842.20, 1847.00, 1852.70, 1859.10, 1866.30, 1874.40, 1883.20, 1892.90, 1903.40, 1914.80, 1927.10, 1940.30, 1954.50, 1969.70, 1985.90, 2003.30, 2021.90, 2041.80, 2063.10, 2086.10, 2110.80, 2137.80, 2167.30, 2200.40, 2238.40
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [11.6300, 175.810],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-90.0700, 74.1100],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [11.6300, 175.810],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1300.40, 1876.20],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 150.000,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 85.0000,

##
## Tilt Cylinders
##

# Number of tilt cylinders.
"NoOfTiltCyls" => 1,

# Tilt cylinder bore diameter, in mm.
"TiltCylBoreDia" => 170.000,

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
"LoaderBktPayldTrgtWt" => 5.87400,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 8.00000,

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_MWL.json",

# Determines whether or not payload legal for trade is supported.
"LegalForTradeSupported" => true,

# Determines whether or not acceleration compensation is supported for this
# machine configuration
"AccelCompSupported" => true,

# This selects the application number used for selecting the cycle segmentation
# data.
"CycleSegAppNumber" => 6200,

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
"KgPerLiftKpaAtMidExtension" => 0.642637,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1780.60,

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
"LiftCylExtPctAxis" => [0.00000, 18.0297, 36.6364, 55.0988, 64.7627, 71.3977, 76.8787, 81.4943, 85.3887, 88.7062, 91.5909, 94.1872, 96.3508, 98.2259, 99.9567],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 6.07850, 11.2886, 15.9778, 20.3196, 24.3140, 27.9611, 31.4345, 34.5606, 37.6867, 40.9865, 44.6336, 49.1490, 56.2695, 66.6898, 75.3734, 84.0570, 92.0458, 96.0229, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -65.3031, -11.6369, 85.1421, 187.274, 200.257, 158.247, 69.8731, -55.4311, -206.192, -376.801, -570.272, -800.664, -1061.09, -1377.56, -1820.19,
    -86.4375, -33.2119, 65.2351, 192.625, 247.740, 253.283, 212.347, 124.674, -1.62874, -156.009, -333.226, -538.254, -757.498, -1003.63, -1308.13,
    -102.241, -51.2074, 43.7960, 178.407, 256.465, 295.925, 298.921, 258.242, 172.808, 47.8549, -110.206, -300.611, -504.040, -726.460, -989.523,
    -114.472, -66.1001, 23.6065, 156.329, 244.424, 304.138, 339.085, 340.268, 300.946, 219.106, 95.7190, -69.7283, -256.812, -465.101, -709.443,
    -124.077, -78.3727, 5.50669, 131.825, 222.031, 291.800, 346.679, 378.644, 379.367, 342.877, 264.940, 140.258, -17.1570, -204.322, -431.252,
    -131.462, -88.1923, -9.94734, 108.118, 195.892, 268.839, 334.034, 385.301, 414.922, 416.046, 382.291, 305.392, 190.250, 37.8702, -160.777,
    -137.017, -95.8560, -22.7180, 86.7757, 169.899, 241.959, 310.990, 372.620, 420.484, 448.380, 450.000, 416.886, 346.927, 238.186, 80.4956,
    -141.280, -101.978, -33.5271, 67.4510, 144.819, 213.693, 282.598, 348.694, 407.081, 452.743, 480.457, 483.199, 454.717, 391.402, 282.653,
    -144.283, -106.505, -42.0582, 51.2715, 122.852, 187.574, 254.092, 320.696, 383.720, 439.323, 483.562, 511.297, 514.472, 489.282, 426.288,
    -146.514, -110.113, -49.4296, 36.4581, 102.014, 161.850, 224.514, 289.176, 353.228, 413.918, 468.565, 513.957, 541.513, 548.093, 526.606,
    -148.050, -112.937, -55.9511, 22.4383, 81.6358, 135.917, 193.521, 254.299, 316.539, 378.452, 438.504, 495.251, 540.408, 571.944, 585.739,
    -148.786, -114.905, -61.6743, 8.95189, 61.3497, 109.381, 160.791, 215.932, 273.834, 333.520, 394.425, 456.585, 512.563, 561.570, 602.523,
    -148.312, -115.693, -66.6577, -4.81138, 39.7279, 80.2710, 123.821, 171.085, 221.704, 275.374, 332.307, 393.676, 453.361, 511.751, 570.502,
    -144.423, -113.289, -69.9972, -20.1621, 13.5473, 43.5093, 75.4771, 110.336, 148.211, 189.318, 234.377, 285.171, 337.550, 392.786, 454.399,
    -131.241, -101.578, -65.5096, -29.9436, -8.65644, 9.16589, 27.5797, 47.3531, 68.7826, 92.2177, 118.324, 148.494, 180.652, 215.978, 257.481,
    -111.758, -83.4939, -53.5880, -28.1730, -14.7667, -4.30748, 6.02109, 16.7863, 28.2441, 40.6575, 54.4459, 70.4165, 87.5516, 106.565, 129.212,
    -79.9314, -55.3304, -33.9432, -18.7710, -11.8655, -6.92974, -2.34635, 2.21996, 6.92814, 11.9204, 17.3879, 23.6648, 30.3682, 37.7958, 46.6517,
    -25.1305, -14.5023, -8.01547, -4.39606, -2.99293, -2.07923, -1.28776, -0.541539, 0.196145, 0.954251, 1.76548, 2.68061, 3.64528, 4.70400, 5.95687,
    38.7302, 16.6459, 8.28728, 4.43953, 3.08205, 2.24093, 1.53955, 0.898949, 0.281707, -0.339990, -0.994861, -1.72433, -2.48560, -3.31438, -4.28829,
    102.583, 67.9330, 27.2357, 14.0477, 9.87494, 7.41646, 5.44456, 3.70314, 2.07217, 0.467136, -1.19187, -3.01092, -4.88463, -6.90242, -9.25020
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
"TiltCylExtThresholdStrict" => 92.9562,

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
  "InternalMsn" => "CAT62700",
  "Make" => "CAT",
  "Model" => "962",
  "ModelDetail" => "962",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}
