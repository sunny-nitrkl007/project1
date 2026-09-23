##
## CAT 950K - High Lift
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-33.9285, 46.7300],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-33.9285, -31.3400, -28.8300, -26.3000, -23.7400, -21.1500, -18.5300, -15.8700, -13.1700, -10.4200, -7.62000, -4.75000, -1.82000, 1.20000, 4.31000, 7.52000, 10.8600, 14.3300, 17.9700, 21.8200, 25.9100, 30.3100, 35.1200, 40.5000, 46.7300],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1303.00, 1332.80, 1361.70, 1390.50, 1419.30, 1448.20, 1477.00, 1505.80, 1534.70, 1563.50, 1592.30, 1621.20, 1650.00, 1678.80, 1707.70, 1736.50, 1765.30, 1794.20, 1823.00, 1851.80, 1880.70, 1909.50, 1938.30, 1967.20, 1996.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0864134, 0.0869073, 0.0875266, 0.0882879, 0.0891972, 0.0902600, 0.0914832, 0.0928814, 0.0944675, 0.0962636, 0.0982903, 0.100589, 0.103184, 0.106146, 0.109531, 0.113422, 0.117952, 0.123255, 0.129576, 0.137265, 0.146805, 0.159043, 0.175481, 0.199111, 0.237008],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1483.05, 1523.85, 1563.54, 1603.25, 1643.15, 1683.40, 1723.78, 1764.45, 1805.60, 1847.01, 1888.86, 1931.39, 1974.38, 2018.09, 2062.81, 2108.39, 2155.21, 2203.75, 2254.09, 2307.01, 2363.62, 2425.03, 2494.03, 2576.07, 2682.79],

# deg/s^2
"outLiftAngleAccel" => [0.0671858, 0.0915879, 0.115103, 0.139038, 0.163863, 0.189976, 0.217810, 0.247964, 0.281022, 0.317814, 0.359214, 0.406654, 0.461428, 0.526061, 0.603276, 0.697058, 0.813771, 0.961530, 1.15461, 1.41611, 1.78431, 2.33344, 3.21940, 4.82492, 8.33922],

# mm/s
"liftRefVel" => 69.3000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 3351.48,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-33.9285, 46.7300],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1303.00, 1996.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 5.18874, 8.99108, 12.3267, 15.4701, 18.5450, 21.6335, 24.7907, 28.0439, 31.4619, 35.0446, 38.8469, 42.8964, 47.2066, 51.8051, 56.6781, 61.8394, 67.2203, 72.7522, 78.2979, 83.7062, 88.7714, 93.2876, 97.0899, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [11.3600, 18.2200, 25.0800, 31.9300, 38.7900, 45.6500, 52.5100, 59.3700, 66.2200, 73.0800, 79.9400, 86.8000, 93.6600, 100.510, 107.370, 114.230, 121.090, 127.950, 134.800, 141.660, 148.520, 155.380, 162.240, 169.090, 175.950],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [11.3600, 18.2200, 25.0800, 31.9300, 38.7900, 45.6500, 52.5100, 59.3700, 66.2200, 73.0800, 79.9400, 86.8000, 93.6600, 100.510, 107.370, 114.230, 121.090, 127.950, 134.800, 141.660, 148.520, 155.380, 162.240, 169.090, 175.950],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-33.9285, -31.3400, -28.8300, -26.3000, -23.7400, -21.1500, -18.5300, -15.8700, -13.1700, -10.4200, -7.62000, -4.75000, -1.82000, 1.20000, 4.31000, 7.52000, 10.8600, 14.3300, 17.9700, 21.8200, 25.9100, 30.3100, 35.1200, 40.5000, 46.7300],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1248.56, 1252.00, 1256.20, 1261.10, 1267.00, 1273.70, 1281.30, 1289.70, 1299.10, 1309.40, 1320.70, 1333.00, 1346.20, 1360.60, 1376.00, 1392.60, 1410.50, 1429.70, 1450.40, 1472.70, 1496.80, 1523.10, 1552.00, 1584.30, 1621.40,
    1276.83, 1280.70, 1285.20, 1290.60, 1296.80, 1303.90, 1311.80, 1320.60, 1330.30, 1340.90, 1352.50, 1365.00, 1378.50, 1393.10, 1408.80, 1425.60, 1443.70, 1463.00, 1483.80, 1506.20, 1530.50, 1556.80, 1585.70, 1618.00, 1655.00,
    1299.46, 1303.60, 1308.40, 1314.00, 1320.40, 1327.70, 1335.90, 1344.90, 1354.80, 1365.60, 1377.40, 1390.10, 1403.80, 1418.50, 1434.40, 1451.30, 1469.50, 1489.00, 1509.90, 1532.30, 1556.60, 1583.00, 1611.90, 1644.10, 1681.10,
    1320.51, 1324.80, 1329.90, 1335.70, 1342.30, 1349.80, 1358.10, 1367.30, 1377.40, 1388.40, 1400.30, 1413.20, 1427.00, 1441.90, 1457.80, 1474.80, 1493.10, 1512.70, 1533.60, 1556.10, 1580.50, 1606.90, 1635.80, 1668.00, 1704.80,
    1341.34, 1345.90, 1351.00, 1357.00, 1363.90, 1371.50, 1380.00, 1389.30, 1399.60, 1410.70, 1422.70, 1435.70, 1449.60, 1464.60, 1480.60, 1497.80, 1516.10, 1535.70, 1556.70, 1579.30, 1603.70, 1630.10, 1659.00, 1691.20, 1728.00,
    1362.59, 1367.30, 1372.60, 1378.80, 1385.70, 1393.50, 1402.20, 1411.60, 1422.00, 1433.20, 1445.40, 1458.40, 1472.50, 1487.50, 1503.60, 1520.90, 1539.30, 1559.00, 1580.00, 1602.60, 1627.00, 1653.40, 1682.40, 1714.50, 1751.20,
    1384.70, 1389.50, 1395.00, 1401.30, 1408.40, 1416.30, 1425.10, 1434.70, 1445.10, 1456.50, 1468.70, 1481.90, 1496.00, 1511.20, 1527.40, 1544.60, 1563.10, 1582.80, 1604.00, 1626.60, 1651.00, 1677.40, 1706.40, 1738.50, 1775.20,
    1407.99, 1413.00, 1418.60, 1425.00, 1432.20, 1440.30, 1449.10, 1458.80, 1469.40, 1480.80, 1493.20, 1506.40, 1520.70, 1535.90, 1552.10, 1569.50, 1588.00, 1607.80, 1628.90, 1651.60, 1676.00, 1702.40, 1731.40, 1763.50, 1800.10,
    1432.74, 1437.90, 1443.60, 1450.20, 1457.50, 1465.70, 1474.60, 1484.40, 1495.10, 1506.60, 1519.00, 1532.40, 1546.70, 1561.90, 1578.20, 1595.60, 1614.20, 1634.00, 1655.20, 1677.90, 1702.30, 1728.80, 1757.70, 1789.80, 1826.40,
    1459.31, 1464.60, 1470.40, 1477.10, 1484.50, 1492.80, 1501.80, 1511.70, 1522.50, 1534.10, 1546.60, 1560.00, 1574.30, 1589.70, 1606.00, 1623.50, 1642.10, 1661.90, 1683.10, 1705.90, 1730.30, 1756.80, 1785.70, 1817.80, 1854.30,
    1487.92, 1493.30, 1499.20, 1506.00, 1513.50, 1521.90, 1531.00, 1541.00, 1551.80, 1563.50, 1576.00, 1589.50, 1603.90, 1619.30, 1635.70, 1653.20, 1671.90, 1691.70, 1713.00, 1735.70, 1760.20, 1786.60, 1815.50, 1847.60, 1884.10,
    1518.83, 1524.30, 1530.30, 1537.20, 1544.80, 1553.20, 1562.40, 1572.50, 1583.40, 1595.10, 1607.70, 1621.20, 1635.70, 1651.10, 1667.60, 1685.10, 1703.80, 1723.70, 1744.90, 1767.70, 1792.20, 1818.60, 1847.50, 1879.60, 1916.10,
    1552.29, 1557.80, 1563.90, 1570.90, 1578.50, 1587.00, 1596.30, 1606.40, 1617.40, 1629.20, 1641.80, 1655.40, 1669.90, 1685.30, 1701.80, 1719.40, 1738.10, 1758.00, 1779.30, 1802.00, 1826.50, 1853.00, 1881.90, 1913.90, 1950.40,
    1588.42, 1594.00, 1600.20, 1607.20, 1615.00, 1623.50, 1632.80, 1643.00, 1654.00, 1665.80, 1678.50, 1692.10, 1706.60, 1722.10, 1738.60, 1756.20, 1774.90, 1794.80, 1816.10, 1838.90, 1863.40, 1889.80, 1918.70, 1950.70, 1987.20,
    1627.41, 1633.10, 1639.30, 1646.30, 1654.10, 1662.70, 1672.10, 1682.20, 1693.20, 1705.10, 1717.80, 1731.40, 1746.00, 1761.50, 1778.00, 1795.50, 1814.30, 1834.20, 1855.50, 1878.30, 1902.80, 1929.20, 1958.10, 1990.10, 2026.60,
    1669.16, 1674.80, 1681.10, 1688.20, 1696.00, 1704.50, 1713.90, 1724.10, 1735.10, 1747.00, 1759.70, 1773.30, 1787.80, 1803.30, 1819.90, 1837.40, 1856.10, 1876.10, 1897.40, 1920.20, 1944.60, 1971.10, 2000.00, 2032.00, 2068.50,
    1713.39, 1719.10, 1725.30, 1732.40, 1740.20, 1748.80, 1758.10, 1768.30, 1779.30, 1791.20, 1803.90, 1817.50, 1832.00, 1847.50, 1864.00, 1881.50, 1900.20, 1920.20, 1941.40, 1964.20, 1988.70, 2015.10, 2044.00, 2076.10, 2112.50,
    1759.54, 1765.20, 1771.40, 1778.40, 1786.20, 1794.80, 1804.10, 1814.30, 1825.20, 1837.10, 1849.70, 1863.30, 1877.80, 1893.20, 1909.70, 1927.20, 1945.90, 1965.80, 1987.10, 2009.80, 2034.30, 2060.80, 2089.70, 2121.70, 2158.20,
    1806.62, 1812.30, 1818.50, 1825.40, 1833.20, 1841.70, 1851.00, 1861.10, 1872.00, 1883.80, 1896.40, 1909.90, 1924.30, 1939.70, 1956.20, 1973.70, 1992.30, 2012.20, 2033.40, 2056.10, 2080.60, 2107.10, 2136.00, 2168.00, 2204.50,
    1853.50, 1859.10, 1865.20, 1872.10, 1879.80, 1888.20, 1897.40, 1907.50, 1918.30, 1930.00, 1942.60, 1956.00, 1970.40, 1985.70, 2002.10, 2019.50, 2038.10, 2058.00, 2079.20, 2101.90, 2126.30, 2152.80, 2181.70, 2213.80, 2250.30,
    1898.55, 1904.00, 1910.10, 1916.90, 1924.50, 1932.80, 1941.90, 1951.90, 1962.70, 1974.30, 1986.70, 2000.10, 2014.40, 2029.70, 2046.00, 2063.40, 2081.90, 2101.70, 2122.80, 2145.50, 2169.90, 2196.40, 2225.30, 2257.40, 2294.00,
    1940.07, 1945.40, 1951.40, 1958.10, 1965.60, 1973.80, 1982.90, 1992.70, 2003.40, 2014.90, 2027.30, 2040.60, 2054.80, 2070.00, 2086.20, 2103.50, 2122.00, 2141.70, 2162.80, 2185.50, 2209.90, 2236.30, 2265.20, 2297.40, 2334.10,
    1976.45, 1981.70, 1987.60, 1994.20, 2001.50, 2009.70, 2018.70, 2028.40, 2039.00, 2050.40, 2062.70, 2075.90, 2090.00, 2105.20, 2121.30, 2138.50, 2157.00, 2176.60, 2197.70, 2220.30, 2244.70, 2271.10, 2300.00, 2332.20, 2368.90,
    2006.35, 2011.50, 2017.30, 2023.80, 2031.10, 2039.20, 2048.00, 2057.70, 2068.20, 2079.50, 2091.70, 2104.90, 2118.90, 2134.00, 2150.10, 2167.20, 2185.60, 2205.20, 2226.20, 2248.80, 2273.10, 2299.50, 2328.50, 2360.70, 2397.50,
    2029.01, 2034.10, 2039.80, 2046.20, 2053.50, 2061.50, 2070.20, 2079.80, 2090.20, 2101.50, 2113.70, 2126.70, 2140.70, 2155.70, 2171.70, 2188.90, 2207.20, 2226.80, 2247.70, 2270.30, 2294.60, 2321.00, 2349.90, 2382.10, 2419.00
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [11.3600, 175.950],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-90.3400, 74.2500],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [11.3600, 175.950],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1471.00, 2049.00],

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
"LoaderBktPayldTrgtWt" => 5.05500,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 7.00000,

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
"KgPerLiftKpaAtMidExtension" => 0.591807,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1966.60,

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
"LiftCylExtPctAxis" => [0.00000, 20.6349, 44.0115, 59.7403, 67.9654, 73.8817, 78.7879, 82.9726, 86.5801, 89.6104, 92.3521, 94.6609, 96.6811, 98.5570, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 5.70934, 10.5536, 15.0519, 19.0311, 22.8374, 26.2976, 29.5848, 32.5260, 35.4671, 38.5813, 42.0415, 46.1938, 52.0761, 62.8028, 71.9723, 80.9689, 90.6574, 96.5398, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -75.8696, -9.45462, 114.946, 187.718, 176.305, 111.993, 0.645460, -149.085, -329.163, -531.522, -780.374, -1080.62, -1493.76, -2265.86, -4896.05,
    -95.1970, -28.8199, 101.351, 207.059, 241.096, 227.695, 166.128, 55.6517, -96.8247, -274.605, -484.964, -714.733, -980.529, -1326.90, -1726.95,
    -109.526, -45.1368, 82.8025, 201.797, 262.293, 286.021, 271.182, 210.126, 100.033, -48.4176, -236.575, -443.207, -672.255, -945.987, -1222.39,
    -121.016, -59.3205, 62.8905, 184.748, 259.168, 306.949, 327.943, 313.203, 254.242, 151.325, -0.547919, -182.681, -391.245, -637.463, -875.154,
    -129.705, -70.6957, 44.7587, 163.768, 243.394, 303.913, 347.187, 365.602, 349.885, 294.397, 190.343, 46.2717, -134.396, -358.378, -576.891,
    -136.735, -80.3535, 27.9023, 141.078, 221.000, 287.409, 343.859, 384.734, 402.075, 388.207, 334.134, 238.931, 101.358, -86.9369, -281.830,
    -142.064, -88.0116, 13.4914, 119.738, 197.123, 264.779, 327.396, 381.161, 419.893, 435.938, 422.369, 373.099, 283.653, 142.986, -16.8256,
    -146.216, -94.2641, 0.880178, 99.7559, 173.078, 239.285, 303.771, 364.188, 416.034, 452.437, 469.121, 457.879, 413.464, 324.526, 209.097,
    -149.200, -99.0066, -9.38101, 82.6165, 151.439, 214.829, 278.530, 341.245, 399.786, 448.203, 484.487, 499.986, 490.125, 445.337, 372.600,
    -151.512, -102.948, -18.6075, 66.4845, 130.342, 189.961, 251.216, 313.617, 375.059, 430.531, 479.909, 514.847, 531.993, 524.559, 491.252,
    -153.248, -106.260, -27.2127, 50.7209, 109.099, 164.095, 221.535, 281.551, 342.925, 401.568, 458.847, 507.135, 544.452, 567.064, 567.864,
    -154.336, -108.920, -35.3594, 34.9632, 87.2482, 136.744, 189.060, 244.788, 303.422, 361.750, 422.224, 478.195, 528.971, 573.669, 601.501,
    -154.501, -110.727, -43.1956, 18.6168, 63.8645, 106.698, 152.326, 201.645, 254.698, 309.119, 368.011, 425.908, 483.197, 541.337, 587.795,
    -152.630, -110.775, -50.8082, 0.254638, 36.4196, 70.3508, 106.557, 146.077, 189.329, 234.810, 285.721, 338.074, 393.007, 453.523, 507.529,
    -142.731, -103.475, -54.9836, -19.7373, 3.08844, 23.6877, 45.2786, 68.7421, 94.5864, 122.184, 153.829, 187.453, 224.224, 266.964, 307.628,
    -126.766, -89.4975, -49.6428, -24.9029, -10.4514, 1.90167, 14.4211, 27.7441, 42.2502, 57.6729, 75.3790, 94.3008, 115.192, 139.804, 163.606,
    -101.914, -67.8046, -37.2043, -21.2907, -13.0610, -6.50897, -0.187384, 6.30745, 13.2083, 20.4281, 28.6333, 37.3526, 46.9588, 58.2825, 69.2629,
    -56.1737, -32.1534, -16.2967, -9.81191, -6.92998, -4.84126, -2.96378, -1.13867, 0.720290, 2.60542, 4.69867, 6.88513, 9.26407, 12.0416, 14.7166,
    0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
    125.560, 26.1002, 10.6451, 6.37964, 4.77576, 3.72508, 2.85509, 2.06669, 1.30943, 0.576877, -0.206081, -0.999002, -1.84050, -2.80207, -3.71162
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 5.05500,

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
"TiltCylExtThresholdStrict" => 95.5398,

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
  "InternalMsn" => "CAT50201",
  "Make" => "CAT",
  "Model" => "950K",
  "ModelDetail" => "950K",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
