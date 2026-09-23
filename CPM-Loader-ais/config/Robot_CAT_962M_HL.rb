##
## CAT 962M - High Lift
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
"outLiftPresNoBucket" => [1482.91, 1523.71, 1563.40, 1603.12, 1643.02, 1683.27, 1723.65, 1764.32, 1805.48, 1846.89, 1888.75, 1931.28, 1974.28, 2017.99, 2062.71, 2108.30, 2155.13, 2203.68, 2254.03, 2306.96, 2363.58, 2425.01, 2494.04, 2576.11, 2682.88],

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
"KnmaticsTiltCylLenMinMax" => [1471.00, 2047.00],

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
"LoaderBktPayldTrgtWt" => 5.66900,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 7.50000,

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
"KgPerLiftKpaAtMidExtension" => 0.591068,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1966.50,

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
"LiftCylExtPctAxis" => [0.00000, 21.2121, 44.5887, 60.0289, 68.1097, 73.8817, 78.6436, 82.8283, 86.4358, 89.4661, 92.2078, 94.5166, 96.5368, 98.4127, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 5.55556, 10.4167, 14.9306, 18.9236, 22.5694, 26.0417, 29.3403, 32.2917, 35.2431, 38.1944, 41.4931, 45.4861, 50.8681, 60.9375, 70.4861, 79.3403, 89.0625, 96.0590, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -78.8693, -7.27863, 122.426, 195.012, 181.746, 115.986, 4.88145, -148.359, -332.760, -539.581, -792.840, -1096.18, -1508.09, -2251.96, -5068.09,
    -98.2790, -26.7201, 109.415, 215.988, 248.507, 232.943, 170.291, 56.4286, -100.375, -282.932, -498.656, -733.892, -1005.36, -1357.78, -1814.00,
    -113.157, -43.7227, 90.4579, 211.713, 272.176, 294.729, 279.020, 215.938, 102.606, -49.8883, -242.864, -454.470, -688.603, -967.667, -1281.12,
    -125.094, -58.5685, 69.7869, 194.653, 270.046, 317.490, 337.930, 322.539, 261.742, 155.962, 0.189869, -186.313, -399.545, -650.757, -919.871,
    -134.126, -70.5129, 50.8149, 173.136, 254.306, 315.056, 358.048, 376.848, 360.541, 303.466, 196.739, 49.2611, -135.373, -363.872, -611.267,
    -141.133, -80.2466, 33.8776, 150.736, 232.567, 299.412, 355.342, 396.481, 412.892, 396.824, 339.110, 239.318, 96.5281, -97.4765, -319.961,
    -146.730, -88.3852, 18.6192, 128.526, 208.058, 276.535, 339.027, 393.840, 432.726, 447.856, 432.086, 379.496, 285.761, 139.891, -44.0713,
    -151.102, -95.0556, 5.21340, 107.616, 183.169, 250.426, 315.065, 377.040, 429.816, 466.313, 482.069, 468.836, 421.379, 328.261, 193.793,
    -154.256, -100.137, -5.73156, 89.6127, 160.653, 225.207, 289.239, 353.798, 413.757, 462.957, 499.257, 513.856, 502.129, 454.343, 368.150,
    -156.712, -104.384, -15.6048, 72.6169, 138.621, 199.453, 261.158, 325.560, 388.735, 445.482, 495.602, 530.544, 546.885, 537.662, 496.541,
    -158.489, -107.805, -24.3664, 56.8508, 117.571, 174.046, 232.245, 294.490, 357.847, 418.005, 476.241, 524.653, 561.125, 581.615, 577.928,
    -159.690, -110.668, -32.8276, 40.8541, 95.6247, 146.845, 200.264, 258.499, 319.479, 379.768, 441.755, 498.462, 549.037, 592.251, 619.389,
    -160.059, -112.809, -41.2068, 23.9173, 71.6964, 116.432, 163.476, 215.537, 271.306, 328.205, 389.350, 448.915, 507.160, 565.278, 615.052,
    -158.708, -113.461, -49.3722, 5.34740, 44.4198, 80.7784, 119.134, 162.026, 208.794, 257.723, 312.130, 367.610, 425.225, 487.849, 548.666,
    -150.413, -108.003, -55.6890, -16.9580, 8.66222, 31.7678, 55.8350, 82.7309, 112.339, 143.889, 179.938, 218.058, 259.498, 307.300, 357.390,
    -134.906, -94.7463, -52.0014, -25.0096, -8.85620, 4.98690, 18.9718, 34.3144, 51.0483, 68.8451, 89.2601, 111.039, 135.023, 163.182, 193.347,
    -111.860, -74.6479, -41.0623, -23.1355, -13.5610, -5.87181, 1.56245, 9.46724, 17.9045, 26.7555, 36.8271, 47.5313, 59.3150, 73.1821, 88.1079,
    -70.0380, -41.1841, -21.3318, -12.8661, -8.95562, -6.08251, -3.48105, -0.852781, 1.84498, 4.59572, 7.66155, 10.8714, 14.3679, 18.4513, 22.8234,
    -11.4497, -5.23531, -2.43406, -1.48192, -1.09083, -0.823632, -0.595160, -0.375161, -0.158094, 0.0565133, 0.289968, 0.529761, 0.787091, 1.08387, 1.39828,
    93.7604, 23.2258, 9.67170, 5.85938, 4.40053, 3.44498, 2.65569, 1.91862, 1.21052, 0.525642, -0.206002, -0.946358, -1.73120, -2.62668, -3.56636
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 5.66900,

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
"TiltCylExtThresholdStrict" => 95.8750,

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
  "InternalMsn" => "CAT62401",
  "Make" => "CAT",
  "Model" => "962M",
  "ModelDetail" => "962M",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
