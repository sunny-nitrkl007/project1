##
## CAT R2900G - BKT (249-4892) 8.3M / 10.9Yd
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Depending om which Pressure Sensor is installed...  the Slope & Intercept may change from the default
"hydPresSensorSlope" => 0.002535,
"hydPresSensorIntercept" => 5.0,

# Depending how the Rotation Sensor is mounter for LIFT & TILT, the DC may need to be inverted
#    0 = don't invert	//dc = sensorDc
#    1 = invert  		//dc = (100-sensorDc)
"invertLiftDc" => 0,
"invertTiltDc" => 1,

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0, 0.3125, 0.625, 0.9375, 1.25, 2.5, 3.75, 5, 6.25, 7.5, 8.75, 10, 11.25, 12.5, 13.75, 15, 16.25, 17.5, 18.75, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100],
# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" =>[-29.7591,-27.7233,-26.0827,-24.6805,-23.4422,
  -19.4767,-16.4185,-13.8779,-11.6807,-9.7310,-7.9696,-6.3567,
  -4.8644,-3.4719,-2.1637,-0.9274,0.2466,1.3663,2.4381,3.4675,
  7.2422,10.6053,13.6770,16.5327,19.2228,21.7824,24.2370,
  26.6053,28.9017,31.1373,33.3207,35.4590,37.5578,39.6215,
  41.6540,43.6582],

# Lift angle axis of the lift cylinder length table, in degrees.
"inLiftAngle" => [-29.7591, -22.6799, -17.5695, -13.1381, -9.11335, -5.38038, -1.86220, 1.47771, 4.67776, 7.73152, 10.6797, 13.5168, 16.2876, 18.9350, 21.5050, 23.9917, 26.4481, 28.8110, 31.1355, 33.3525, 35.5194, 37.6315, 39.6832, 41.6676, 43.6582],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1428.00, 1517.70, 1581.49, 1635.80, 1684.14, 1728.00, 1768.36, 1805.74, 1840.62, 1873.01, 1903.41, 1931.81, 1958.72, 1983.64, 2007.06, 2028.99, 2049.92, 2069.35, 2087.79, 2104.74, 2120.68, 2135.63, 2149.59, 2162.54, 2175.00],

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-29.7591, 43.6582],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1428.00, 2175.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.000000, 3.81310, 10.4261, 15.1582, 19.2021, 23.0118, 26.6816, 30.3564, 34.0204, 37.7794, 41.6199, 45.6757, 49.9444, 54.5910, 59.9003, 66.9749, 76.9583, 82.3267, 86.4511, 89.8214, 92.7007, 95.0940, 97.0788, 98.7072, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [32.2900, 39.8641, 55.4453, 67.0229, 76.5447, 84.9844, 92.5586, 99.5917, 106.084, 112.251, 118.094, 123.829, 129.456, 135.190, 141.358, 149.148, 159.860, 165.811, 170.681, 175.009, 179.120, 183.016, 186.803, 190.590, 194.485],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [32.2900, 39.8641, 55.4453, 67.0229, 76.5447, 84.9844, 92.5586, 99.5917, 106.084, 112.251, 118.094, 123.829, 129.456, 135.190, 141.358, 149.148, 159.860, 165.811, 170.681, 175.009, 179.120, 183.016, 186.803, 190.590, 194.485],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-29.7591, -27.8399, -25.9159, -23.9851, -22.0059, -20.0156, -17.9720, -15.8720, -13.7531, -11.5715, -9.32297, -7.00286, -4.60584, -2.08191, 0.533831, 3.29576, 6.21753, 9.36426, 12.8120, 16.6533, 21.1721, 27.4073, 34.3579, 39.3106, 43.6582],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1085.71, 1090.42, 1095.81, 1101.86, 1108.71, 1116.25, 1124.64, 1133.92, 1143.94, 1154.90, 1166.85, 1179.84, 1193.91, 1209.40, 1226.11, 1244.43, 1264.47, 1286.73, 1311.80, 1340.43, 1374.81, 1423.06, 1477.23, 1515.65, 1549.01,
    1101.45, 1106.49, 1112.19, 1118.54, 1125.69, 1133.52, 1142.19, 1151.75, 1162.04, 1173.26, 1185.46, 1198.69, 1212.99, 1228.70, 1245.62, 1264.13, 1284.36, 1306.79, 1332.02, 1360.78, 1395.28, 1443.61, 1497.78, 1536.14, 1569.42,
    1132.80, 1138.35, 1144.53, 1151.36, 1158.98, 1167.25, 1176.36, 1186.35, 1197.04, 1208.66, 1221.24, 1234.83, 1249.48, 1265.53, 1282.76, 1301.57, 1322.07, 1344.75, 1370.21, 1399.18, 1433.84, 1482.28, 1536.41, 1574.67, 1607.80,
    1158.09, 1163.95, 1170.45, 1177.57, 1185.48, 1194.03, 1203.41, 1213.67, 1224.61, 1236.47, 1249.28, 1263.10, 1277.96, 1294.21, 1311.63, 1330.62, 1351.28, 1374.11, 1399.71, 1428.78, 1463.54, 1512.03, 1566.13, 1604.32, 1637.35,
    1181.39, 1187.49, 1194.22, 1201.56, 1209.69, 1218.46, 1228.05, 1238.50, 1249.63, 1261.67, 1274.66, 1288.64, 1303.66, 1320.06, 1337.62, 1356.74, 1377.52, 1400.46, 1426.15, 1455.31, 1490.13, 1538.65, 1592.73, 1630.85, 1663.80,
    1204.60, 1210.91, 1217.83, 1225.37, 1233.68, 1242.63, 1252.39, 1263.01, 1274.29, 1286.48, 1299.62, 1313.74, 1328.89, 1345.41, 1363.09, 1382.31, 1403.19, 1426.22, 1451.99, 1481.21, 1516.08, 1564.63, 1618.67, 1656.74, 1689.62,
    1228.01, 1234.50, 1241.59, 1249.29, 1257.77, 1266.86, 1276.77, 1287.53, 1298.95, 1311.27, 1324.52, 1338.76, 1354.02, 1370.64, 1388.41, 1407.73, 1428.69, 1451.79, 1477.62, 1506.90, 1541.81, 1590.37, 1644.38, 1682.40, 1715.23,
    1252.38, 1259.02, 1266.27, 1274.11, 1282.72, 1291.95, 1301.98, 1312.87, 1324.40, 1336.84, 1350.20, 1364.53, 1379.89, 1396.60, 1414.46, 1433.84, 1454.87, 1478.04, 1503.92, 1533.25, 1568.19, 1616.76, 1670.75, 1708.72, 1741.49,
    1277.49, 1284.27, 1291.64, 1299.61, 1308.35, 1317.69, 1327.83, 1338.82, 1350.46, 1362.99, 1376.44, 1390.86, 1406.29, 1423.08, 1441.01, 1460.46, 1481.55, 1504.76, 1530.70, 1560.05, 1595.02, 1643.60, 1697.56, 1735.50, 1768.22,
    1303.98, 1310.89, 1318.38, 1326.46, 1335.30, 1344.74, 1354.98, 1366.07, 1377.79, 1390.40, 1403.93, 1418.42, 1433.93, 1450.78, 1468.76, 1488.27, 1509.41, 1532.67, 1558.64, 1588.02, 1623.01, 1671.60, 1725.54, 1763.44, 1796.12,
    1331.72, 1338.72, 1346.32, 1354.49, 1363.42, 1372.95, 1383.28, 1394.44, 1406.24, 1418.91, 1432.51, 1447.07, 1462.62, 1479.53, 1497.56, 1517.11, 1538.29, 1561.59, 1587.58, 1617.00, 1652.00, 1700.59, 1754.51, 1792.39, 1825.03,
    1361.62, 1368.72, 1376.40, 1384.65, 1393.66, 1403.26, 1413.66, 1424.89, 1436.75, 1449.48, 1463.13, 1477.74, 1493.34, 1510.29, 1528.36, 1547.95, 1569.16, 1592.48, 1618.50, 1647.93, 1682.95, 1731.54, 1785.45, 1823.30, 1855.92,
    1393.63, 1400.81, 1408.56, 1416.88, 1425.95, 1435.61, 1446.07, 1457.35, 1469.25, 1482.03, 1495.72, 1510.37, 1526.01, 1542.99, 1561.09, 1580.70, 1601.93, 1625.27, 1651.31, 1680.76, 1715.78, 1764.37, 1818.27, 1856.10, 1888.70,
    1428.97, 1436.21, 1444.01, 1452.39, 1461.51, 1471.21, 1481.71, 1493.02, 1504.96, 1517.77, 1531.49, 1546.16, 1561.82, 1578.82, 1596.94, 1616.57, 1637.81, 1661.17, 1687.21, 1716.66, 1751.69, 1800.29, 1854.18, 1892.00, 1924.59,
    1469.77, 1477.05, 1484.90, 1493.30, 1502.46, 1512.19, 1522.70, 1534.04, 1546.00, 1558.82, 1572.56, 1587.23, 1602.90, 1619.91, 1638.03, 1657.66, 1678.90, 1702.26, 1728.30, 1757.75, 1792.78, 1841.38, 1895.27, 1933.09, 1965.68,
    1524.48, 1531.77, 1539.63, 1548.04, 1557.20, 1566.93, 1577.44, 1588.77, 1600.72, 1613.54, 1627.25, 1641.92, 1657.57, 1674.55, 1692.66, 1712.26, 1733.49, 1756.82, 1782.85, 1812.29, 1847.30, 1895.90, 1949.80, 1987.65, 2020.26,
    1601.51, 1608.75, 1616.55, 1624.91, 1634.01, 1643.67, 1654.12, 1665.38, 1677.26, 1690.00, 1703.64, 1718.23, 1733.81, 1750.72, 1768.76, 1788.29, 1809.45, 1832.73, 1858.70, 1888.09, 1923.08, 1971.66, 2025.61, 2063.51, 2096.18,
    1642.47, 1649.66, 1657.41, 1665.70, 1674.74, 1684.34, 1694.73, 1705.93, 1717.74, 1730.42, 1744.00, 1758.53, 1774.04, 1790.90, 1808.87, 1828.35, 1849.46, 1872.69, 1898.62, 1927.97, 1962.93, 2011.51, 2065.48, 2103.42, 2136.15,
    1673.60, 1680.73, 1688.42, 1696.66, 1705.63, 1715.18, 1725.50, 1736.64, 1748.40, 1761.02, 1774.54, 1789.01, 1804.47, 1821.27, 1839.19, 1858.62, 1879.68, 1902.86, 1928.75, 1958.07, 1993.01, 2041.58, 2095.57, 2133.55, 2166.32,
    1698.75, 1705.83, 1713.46, 1721.64, 1730.56, 1740.06, 1750.32, 1761.41, 1773.11, 1785.67, 1799.14, 1813.56, 1828.96, 1845.71, 1863.58, 1882.97, 1903.99, 1927.13, 1952.98, 1982.27, 2017.19, 2065.75, 2119.76, 2157.77, 2190.57,
    1720.01, 1727.03, 1734.61, 1742.75, 1751.62, 1761.05, 1771.27, 1782.30, 1793.95, 1806.46, 1819.88, 1834.25, 1849.61, 1866.31, 1884.14, 1903.48, 1924.45, 1947.56, 1973.38, 2002.64, 2037.53, 2086.08, 2140.12, 2178.15, 2210.99,
    1737.51, 1744.48, 1752.02, 1760.10, 1768.92, 1778.32, 1788.49, 1799.47, 1811.07, 1823.54, 1836.91, 1851.24, 1866.55, 1883.21, 1901.00, 1920.30, 1941.24, 1964.31, 1990.10, 2019.34, 2054.21, 2102.75, 2156.80, 2194.86, 2227.73,
    1751.89, 1758.82, 1766.31, 1774.36, 1783.14, 1792.49, 1802.62, 1813.56, 1825.13, 1837.55, 1850.89, 1865.17, 1880.45, 1897.07, 1914.82, 1934.09, 1955.00, 1978.04, 2003.81, 2033.02, 2067.87, 2116.41, 2170.47, 2208.55, 2241.44,
    1763.59, 1770.49, 1777.95, 1785.96, 1794.70, 1804.02, 1814.11, 1825.02, 1836.55, 1848.94, 1862.24, 1876.49, 1891.74, 1908.33, 1926.05, 1945.29, 1966.18, 1989.19, 2014.93, 2044.13, 2078.97, 2127.49, 2181.56, 2219.66, 2252.58,
    1772.82, 1779.69, 1787.12, 1795.10, 1803.82, 1813.10, 1823.17, 1834.05, 1845.55, 1857.92, 1871.19, 1885.41, 1900.63, 1917.20, 1934.89, 1954.11, 1974.97, 1997.97, 2023.69, 2052.87, 2087.69, 2136.22, 2190.29, 2228.40, 2261.34
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [32.2900, 194.485],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-81.9529, 80.2421],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [32.2900, 194.485],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1297.00, 1843.00],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 230.050,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 110.000,

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
"LoaderBktPayldTrgtWt" => 14.7740,

# The CAT datalink configuration file.
"BMI_CDL_CONFIG_JSON_FILE_PATH" =>  ENV["CAT_CONFIG_DIR"] + "/BmiCdl_LHD_2900.json",

##
## Calibration Information
##
# Qualified Reads
# Hyd Oil Temp Min for Empty & Full calibrations
"QR_Min_HydOilTemp_celsius" => 40,
# Target Velocity for slow lower for Empty & Full calibrations
"QR_Min_LiftCylVelocity_mm_sec" => -25,
# Target Velocity for slow lift for Empty & Full calibrations
"QR_Max_LiftCylVelocity_mm_sec" => 25,

# The lift head-end cylinder gain. For each kPa of head-end pressure change, how
# many kg of payload weight does that correspond to? This assumes stationary
# linkage at full rack, at 50% lift cylinder extension, rod-end is at
# atmospheric pressure, and there is no friction. Used to estimate the empty
# bucket weight and the full bucket calibration weight.
"KgPerLiftKpaAtMidExtension" => 1.58406,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1743.77,

##
## Temperature Compensation
##

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylHeLineLoss2ndOrdrCoeff" => 13.570346349E-06,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3.
"LiftCylHeLineLoss1stOrdrCoeff" => 6.335360,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylReLineLoss2ndOrdrCoeff" => 10.9156E-06,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3
"LiftCylReLineLoss1stOrdrCoeff" => 7.4462,
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
"TiltCompGainScalar" => 0.00000,

# The gain applied to the empty bucket portion of the tilt compensation
# adjustment.
"TiltCompEmptyBktWtGain" => 0.400000,

# The maximum allowed tilt compensation factor.
"TiltCompMaxGain" => 0.500000,

# Lift cylinder extension axis for the tilt compensation gain table, in %.
"LiftCylExtPctAxis" => [0.000000, 10.9772, 23.8286, 43.9090, 56.4926, 63.9893, 70.2811, 75.7697, 80.5890, 84.8728, 88.6212, 91.9679, 94.9130, 97.5904, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.000000, 6.04396, 11.5385, 16.8498, 21.7949, 26.3736, 30.7692, 34.9817, 39.0110, 42.8571, 46.5201, 50.0000, 53.8462, 58.7912, 68.6813, 79.3040, 86.9963, 90.2930, 96.0989, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -55.1892, -0.0242347, 60.4013, 179.142, 214.111, 143.774, 14.4071, -146.820, -497.699, -767.290, -977.984, -1149.14, -1290.62, -1415.23, -1526.25,
    -64.7368, -13.8191, 40.0221, 156.561, 240.912, 243.251, 161.122, 16.4946, -159.517, -472.574, -755.411, -1014.85, -1242.99, -1449.00, -1633.77,
    -71.6206, -24.2302, 23.5259, 128.663, 227.154, 276.783, 265.889, 169.587, 10.6823, -181.358, -481.356, -835.573, -1192.07, -1532.58, -1843.58,
    -76.7260, -32.3142, 10.0651, 101.516, 196.752, 266.180, 307.507, 285.841, 177.832, 5.21871, -197.022, -490.078, -1045.80, -1675.94, -2277.03,
    -80.2209, -38.1936, -0.212301, 78.5938, 163.793, 235.590, 300.476, 334.055, 300.642, 179.431, -2.72299, -217.956, -506.026, -1782.26, -2700.46,
    -82.4684, -42.3424, -7.90192, 60.1715, 134.044, 200.599, 270.925, 331.954, 356.115, 308.780, 176.160, -18.1971, -242.470, -541.601, -1430.82,
    -83.8027, -45.2593, -13.7757, 45.1459, 108.128, 166.713, 233.602, 303.480, 359.786, 374.296, 315.336, 171.035, -31.1107, -271.206, -579.993,
    -84.3749, -47.1587, -18.1519, 33.0830, 86.3847, 136.588, 196.301, 264.598, 333.125, 384.254, 389.125, 319.000, 167.044, -48.7028, -302.927,
    -84.3076, -48.2174, -21.3012, 23.5084, 68.5226, 110.954, 162.509, 224.447, 293.411, 360.166, 404.645, 400.389, 321.624, 157.927, -69.9278,
    -83.7002, -48.5801, -23.4487, 15.9829, 54.0303, 89.6582, 133.379, 187.369, 250.999, 320.352, 383.218, 421.429, 408.639, 319.088, 144.451,
    -82.6328, -48.3649, -24.7789, 10.1274, 42.3644, 72.2074, 108.937, 154.985, 211.068, 276.268, 343.796, 403.062, 434.123, 412.121, 311.595,
    -81.1711, -47.6689, -25.4433, 5.62499, 33.0256, 58.0211, 88.7376, 127.543, 175.729, 233.911, 298.645, 364.606, 418.592, 442.729, 410.410,
    -79.0275, -46.3483, -25.5410, 1.72130, 24.4656, 44.8037, 69.6625, 101.166, 140.780, 189.877, 247.174, 310.972, 373.863, 425.958, 447.549,
    -75.3886, -43.7864, -24.7385, -1.83979, 15.8275, 31.1485, 49.6640, 73.0870, 102.758, 140.226, 185.510, 239.133, 298.181, 359.653, 413.536,
    -64.3886, -35.4461, -20.1351, -4.87762, 4.97149, 12.8854, 22.1325, 33.6464, 48.1990, 66.7826, 89.8675, 118.600, 153.003, 194.318, 241.579,
    -42.6966, -19.9123, -10.5574, -3.38457, 0.299924, 2.97557, 5.95447, 9.56146, 14.0527, 19.7576, 26.8683, 35.8328, 46.8336, 60.5955, 77.4065,
    0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
    19.2286, 14.7862, 5.68532, 1.86814, 0.414519, -0.525621, -1.51499, -2.67292, -4.08541, -5.85833, -8.05542, -10.8236, -14.2357, -18.5487, -23.9134,
    53.8440, 34.6490, 16.9594, 5.38564, 1.61554, -0.709510, -3.09739, -5.84924, -9.17349, -13.3205, -18.4408, -24.8800, -32.8141, -42.8550, -55.3816,
    77.5039, 46.0035, 2.47802, 7.41244, 2.51141, -0.518508, -3.61172, -7.15663, -11.4211, -16.7256, -23.2627, -31.4745, -41.5884, -54.3908, -70.3784
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 14.7740,

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
"FullDumpBktAngleThreshold" => -30.0000,

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


# Default Auto Store value
"AutoStorePassCountDefault" => 1,

# This will define what UI configurable features are Enabled or Disabled.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" =>  ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_UGM.json",

}

MachineType = {
  "InternalMsn" => "CAT29627",
  "Make" => "CAT",
  "Model" => "R2900G",
  "ModelDetail" => "R2900G BKT (249-4892)",
  "Linkage" => "BKT (249-4892) 8.3M / 10.9Yd",
  "LinkageConfigurationNumber" => 52
}

DeviceID_J1939 = {
  #Analysis  : 0x9601 0100 B001
  #Analysis  : 0x9601 0000 B001
  #Analysis  : 0x9601 0F00 0000 <<
  #Autonomous: 0x6004 2400 0000
 
  "MID" => 0x0196,
  "ST_app_num" => 0x0157, 
  "ST_chg_lvl" => 0x0000,
}
