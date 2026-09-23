##
## CAT 982M - High Lift
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-30.8400, 48.6500],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-30.8400, -28.4400, -26.0300, -23.5800, -21.1200, -18.6100, -16.0800, -13.5000, -10.8700, -8.20000, -5.47000, -2.67000, 0.200000, 3.16000, 6.20000, 9.36000, 12.6400, 16.0700, 19.6700, 23.4800, 27.5400, 31.9400, 36.7700, 42.2200, 48.6500],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1616.00, 1649.50, 1683.10, 1716.60, 1750.20, 1783.70, 1817.30, 1850.80, 1884.30, 1917.90, 1951.40, 1985.00, 2018.50, 2052.00, 2085.60, 2119.10, 2152.70, 2186.20, 2219.80, 2253.30, 2286.80, 2320.40, 2353.90, 2387.50, 2421.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0711709, 0.0717366, 0.0724044, 0.0731857, 0.0740748, 0.0750924, 0.0762339, 0.0775225, 0.0789714, 0.0805902, 0.0824095, 0.0844609, 0.0867752, 0.0894079, 0.0923998, 0.0958562, 0.0998674, 0.104593, 0.110236, 0.117119, 0.125716, 0.136894, 0.152118, 0.174555, 0.212375],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1785.63, 1829.59, 1873.86, 1918.21, 1962.94, 2007.80, 2053.12, 2098.66, 2144.61, 2191.17, 2238.13, 2285.85, 2334.15, 2383.31, 2433.62, 2485.01, 2538.05, 2592.80, 2650.12, 2710.43, 2775.10, 2846.30, 2927.16, 3025.50, 3159.37],

# deg/s^2
"outLiftAngleAccel" => [0.0991499, 0.119198, 0.139717, 0.161257, 0.183862, 0.208251, 0.234534, 0.263492, 0.295719, 0.331800, 0.372892, 0.420337, 0.475685, 0.541426, 0.620175, 0.717024, 0.837958, 0.993064, 1.19743, 1.47688, 1.87596, 2.48493, 3.49399, 5.40461, 9.95614],

# mm/s
"liftRefVel" => 80.5000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 3901.92,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-30.8400, 48.6500],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1616.00, 2421.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 4.16724, 8.33295, 12.5002, 16.6674, 20.8331, 25.0004, 29.1661, 33.3333, 37.5006, 41.6663, 45.8335, 49.8466, 54.1665, 58.3337, 62.4994, 66.6667, 70.8339, 74.9996, 79.1669, 83.3326, 87.4998, 91.6670, 95.8328, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [10.8000, 15.7000, 22.4000, 30.3000, 38.8000, 47.5000, 56.1000, 64.4000, 72.4000, 79.9000, 87.1000, 93.8000, 100.030, 106.400, 112.200, 117.900, 123.400, 128.700, 134.100, 139.400, 144.900, 150.700, 157.000, 164.300, 174.000],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [10.8000, 15.7000, 22.4000, 30.3000, 38.8000, 47.5000, 56.1000, 64.4000, 72.4000, 79.9000, 87.1000, 93.8000, 100.300, 106.400, 112.200, 117.900, 123.400, 128.700, 134.100, 139.400, 144.900, 150.700, 157.000, 164.300, 174.000],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-30.8400, -28.4400, -26.0300, -23.5800, -21.1200, -18.6100, -16.0800, -13.5000, -10.8700, -8.20000, -5.47000, -2.67000, 0.200000, 3.16000, 6.20000, 9.36000, 12.6400, 16.0700, 19.6700, 23.4800, 27.5400, 31.9400, 36.7700, 42.2200, 48.6500],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1243.10, 1240.00, 1238.00, 1237.20, 1237.50, 1239.10, 1242.00, 1246.30, 1251.80, 1258.90, 1267.40, 1277.50, 1289.20, 1302.60, 1317.90, 1335.00, 1354.30, 1375.70, 1399.60, 1426.20, 1456.00, 1489.40, 1527.40, 1571.30, 1623.80,
    1268.20, 1265.70, 1264.30, 1264.00, 1265.00, 1267.20, 1270.60, 1275.40, 1281.60, 1289.20, 1298.20, 1308.80, 1321.00, 1334.90, 1350.60, 1368.20, 1387.90, 1409.70, 1434.00, 1461.00, 1491.00, 1524.70, 1562.80, 1606.90, 1659.50,
    1296.30, 1294.40, 1293.50, 1293.80, 1295.30, 1298.00, 1302.00, 1307.30, 1313.90, 1322.00, 1331.50, 1342.60, 1355.30, 1369.60, 1385.70, 1403.70, 1423.70, 1445.90, 1470.40, 1497.70, 1528.00, 1561.90, 1600.20, 1644.40, 1697.10,
    1327.30, 1325.80, 1325.40, 1326.20, 1328.20, 1331.30, 1335.80, 1341.50, 1348.60, 1357.10, 1367.10, 1378.60, 1391.60, 1406.30, 1422.80, 1441.10, 1461.40, 1483.90, 1508.70, 1536.20, 1566.70, 1600.80, 1639.20, 1683.50, 1736.30,
    1360.70, 1359.60, 1359.70, 1360.90, 1363.30, 1366.90, 1371.80, 1377.90, 1385.40, 1394.30, 1404.60, 1416.40, 1429.80, 1444.80, 1461.60, 1480.20, 1500.80, 1523.50, 1548.50, 1576.20, 1606.90, 1641.10, 1679.70, 1724.10, 1776.80,
    1396.30, 1395.70, 1396.10, 1397.70, 1400.50, 1404.40, 1409.60, 1416.10, 1424.00, 1433.20, 1443.80, 1455.90, 1469.60, 1484.90, 1501.90, 1520.70, 1541.50, 1564.40, 1589.70, 1617.50, 1648.40, 1682.70, 1721.40, 1765.80, 1818.60,
    1433.90, 1433.60, 1434.30, 1436.30, 1439.30, 1443.60, 1449.20, 1456.00, 1464.10, 1473.50, 1484.40, 1496.80, 1510.70, 1526.20, 1543.50, 1562.50, 1583.50, 1606.60, 1632.00, 1659.90, 1690.90, 1725.30, 1764.10, 1808.50, 1861.30,
    1473.10, 1473.10, 1474.20, 1476.40, 1479.70, 1484.30, 1490.10, 1497.10, 1505.50, 1515.20, 1526.30, 1538.90, 1553.00, 1568.70, 1586.10, 1605.30, 1626.40, 1649.60, 1675.10, 1703.20, 1734.20, 1768.70, 1807.60, 1852.10, 1904.90,
    1513.80, 1514.00, 1515.30, 1517.80, 1521.40, 1526.10, 1532.10, 1539.40, 1547.90, 1557.80, 1569.10, 1581.90, 1596.10, 1612.00, 1629.50, 1648.80, 1670.10, 1693.40, 1719.00, 1747.10, 1778.20, 1812.80, 1851.70, 1896.20, 1949.00,
    1555.70, 1556.10, 1557.60, 1560.20, 1564.00, 1569.00, 1575.20, 1582.60, 1591.30, 1601.30, 1612.80, 1625.60, 1640.00, 1656.00, 1673.60, 1693.00, 1714.30, 1737.70, 1763.40, 1791.60, 1822.70, 1857.30, 1896.20, 1940.80, 1993.60,
    1598.50, 1599.10, 1600.80, 1603.60, 1607.50, 1612.60, 1618.90, 1626.50, 1635.30, 1645.40, 1657.00, 1669.90, 1684.40, 1700.40, 1718.10, 1737.60, 1759.00, 1782.40, 1808.10, 1836.40, 1867.50, 1902.20, 1941.10, 1985.60, 2038.40,
    1642.10, 1642.90, 1644.70, 1647.60, 1651.60, 1656.80, 1663.20, 1670.90, 1679.80, 1690.00, 1701.60, 1714.60, 1729.10, 1745.20, 1763.00, 1782.50, 1803.90, 1827.30, 1853.10, 1881.30, 1912.50, 1947.10, 1986.00, 2030.60, 2083.40,
    1686.40, 1687.20, 1689.10, 1692.10, 1696.20, 1701.50, 1707.90, 1715.60, 1724.60, 1734.90, 1746.50, 1759.50, 1774.10, 1790.20, 1807.90, 1827.50, 1848.90, 1872.30, 1898.00, 1926.30, 1957.50, 1992.10, 2031.00, 2075.50, 2128.40,
    1731.00, 1731.90, 1733.80, 1736.90, 1741.00, 1746.30, 1752.80, 1760.60, 1769.50, 1779.80, 1791.50, 1804.50, 1819.10, 1835.20, 1852.90, 1872.40, 1893.80, 1917.20, 1942.90, 1971.20, 2002.30, 2036.90, 2075.80, 2120.40, 2173.20,
    1775.90, 1776.80, 1778.80, 1781.80, 1786.00, 1791.30, 1797.80, 1805.50, 1814.50, 1824.80, 1836.40, 1849.40, 1864.00, 1880.00, 1897.70, 1917.20, 1938.50, 1961.90, 1987.60, 2015.80, 2046.90, 2081.50, 2120.40, 2164.90, 2217.70,
    1820.90, 1821.80, 1823.70, 1826.80, 1831.00, 1836.30, 1842.70, 1850.40, 1859.40, 1869.60, 1881.20, 1894.20, 1908.60, 1924.60, 1942.30, 1961.70, 1983.00, 2006.30, 2031.90, 2060.10, 2091.20, 2125.70, 2164.50, 2209.00, 2261.90,
    1865.80, 1866.70, 1868.60, 1871.70, 1875.80, 1881.00, 1887.50, 1895.10, 1904.00, 1914.10, 1925.70, 1938.60, 1953.00, 1968.90, 1986.50, 2005.80, 2027.00, 2050.30, 2075.80, 2103.90, 2134.90, 2169.40, 2208.20, 2252.70, 2305.50,
    1910.60, 1911.40, 1913.30, 1916.30, 1920.30, 1925.50, 1931.90, 1939.40, 1948.20, 1958.30, 1969.70, 1982.60, 1996.90, 2012.70, 2030.20, 2049.40, 2070.60, 2093.70, 2119.20, 2147.20, 2178.10, 2212.50, 2251.30, 2295.70, 2348.50,
    1955.00, 1955.80, 1957.60, 1960.50, 1964.50, 1969.60, 1975.80, 1983.30, 1992.00, 2002.00, 2013.30, 2026.00, 2040.20, 2055.90, 2073.30, 2092.40, 2113.50, 2136.50, 2161.90, 2189.80, 2220.60, 2255.00, 2293.70, 2338.10, 2390.90,
    1999.10, 1999.80, 2001.50, 2004.30, 2008.20, 2013.20, 2019.30, 2026.60, 2035.20, 2045.10, 2056.30, 2068.90, 2082.90, 2098.50, 2115.80, 2134.80, 2155.70, 2178.60, 2203.90, 2231.70, 2262.40, 2296.70, 2335.30, 2379.60, 2432.40,
    2042.70, 2043.20, 2044.80, 2047.50, 2051.30, 2056.10, 2062.10, 2069.30, 2077.80, 2087.50, 2098.50, 2111.00, 2124.90, 2140.30, 2157.50, 2176.30, 2197.10, 2219.90, 2245.00, 2272.70, 2303.30, 2337.50, 2376.00, 2420.30, 2473.10,
    2085.60, 2086.10, 2087.50, 2090.10, 2093.70, 2098.40, 2104.20, 2111.30, 2119.60, 2129.10, 2140.00, 2152.30, 2166.00, 2181.40, 2198.30, 2217.00, 2237.60, 2260.30, 2285.20, 2312.80, 2343.30, 2377.40, 2415.80, 2460.10, 2512.80,
    2127.90, 2128.20, 2129.50, 2131.90, 2135.30, 2139.90, 2145.50, 2152.40, 2160.50, 2169.90, 2180.60, 2192.70, 2206.30, 2221.40, 2238.20, 2256.80, 2277.20, 2299.70, 2324.50, 2351.90, 2382.30, 2416.30, 2454.60, 2498.80, 2551.50,
    2169.40, 2169.50, 2170.60, 2172.80, 2176.10, 2180.50, 2186.00, 2192.70, 2200.60, 2209.80, 2220.30, 2232.20, 2245.60, 2260.60, 2277.20, 2295.50, 2315.80, 2338.10, 2362.80, 2390.00, 2420.30, 2454.10, 2492.30, 2536.40, 2589.10,
    2210.00, 2209.90, 2210.90, 2212.90, 2216.00, 2220.20, 2225.50, 2232.00, 2239.70, 2248.70, 2259.00, 2270.70, 2283.90, 2298.60, 2315.00, 2333.20, 2353.30, 2375.40, 2399.90, 2427.00, 2457.10, 2490.80, 2528.90, 2572.90, 2625.50
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [10.8000, 174.000],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-94.2000, 69.0000],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [10.8000, 174.000],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1475.20, 2217.30],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 190.000,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 100.000,

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
"ToolBcLen" => 509.998,

# Tool's angle between line BC and tool's X-axis, in deg.
"ToolBcAngle" => 105.000,

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
"LoaderBktPayldTrgtWt" => 10.8580,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 15.0000,

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
"CycleSegAppNumber" => 8200,

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
"KgPerLiftKpaAtMidExtension" => 0.970904,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 2335.36,

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
"LiftCylExtPctAxis" => [0.00000, 14.2857, 30.6832, 50.5590, 67.0807, 75.2795, 80.4969, 84.4720, 87.8261, 90.6832, 93.1677, 95.2795, 97.1429, 98.7578, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 4.71615, 8.89332, 12.6662, 16.1697, 19.4036, 22.3680, 25.1977, 27.8927, 30.7224, 33.6868, 37.0555, 40.9632, 46.0836, 55.3811, 66.0262, 75.0542, 84.3518, 94.4578, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -41.4207, -68.6653, -47.8126, 24.4727, 95.3095, 101.174, 65.1077, -4.42860, -106.110, -233.588, -383.865, -551.910, -748.347, -981.756, -1235.48,
    -55.6227, -79.5820, -57.2098, 17.8558, 104.860, 137.336, 132.852, 96.9730, 27.2520, -74.8971, -206.134, -356.947, -529.775, -723.558, -916.151,
    -65.7702, -87.8109, -65.1994, 9.63039, 104.135, 152.943, 170.827, 162.844, 125.555, 55.4889, -48.6270, -179.604, -336.418, -512.935, -684.106,
    -73.2700, -94.1428, -71.9159, 1.16499, 98.0514, 156.190, 188.729, 201.033, 190.522, 151.832, 80.1357, -22.8736, -157.684, -317.524, -475.348,
    -79.0032, -99.1321, -77.5969, -7.03018, 89.2183, 152.150, 193.863, 220.129, 229.719, 217.292, 176.967, 106.197, 1.37652, -134.200, -275.408,
    -83.3630, -103.011, -82.2930, -14.5439, 79.3095, 144.011, 190.944, 226.178, 249.729, 256.995, 242.561, 201.931, 129.730, 24.9934, -92.9081,
    -86.6513, -105.979, -86.0972, -21.1858, 69.3715, 133.945, 183.412, 224.007, 256.714, 277.797, 282.810, 266.788, 224.231, 151.417, 60.9673,
    -89.2136, -108.310, -89.2613, -27.1786, 59.5447, 122.798, 173.073, 216.662, 255.277, 285.992, 305.402, 308.749, 291.325, 248.245, 186.195,
    -91.1709, -110.090, -91.8401, -32.4889, 50.1661, 111.345, 161.238, 206.108, 248.190, 285.246, 314.799, 332.557, 334.922, 316.902, 280.720,
    -92.7553, -111.514, -94.0869, -37.5856, 40.5339, 98.9137, 147.478, 192.389, 236.261, 277.473, 314.389, 343.292, 361.785, 365.335, 352.775,
    -93.9330, -112.535, -95.9334, -42.3505, 30.8823, 85.8680, 132.293, 176.148, 220.292, 263.634, 305.245, 342.004, 372.626, 393.293, 400.454,
    -94.7126, -113.132, -97.4060, -47.0102, 20.6602, 71.4515, 114.816, 156.489, 199.455, 243.089, 287.071, 328.885, 368.239, 402.150, 425.419,
    -94.9219, -113.102, -98.2918, -51.3780, 9.99798, 55.7436, 95.0716, 133.366, 173.606, 215.552, 259.370, 303.129, 347.333, 389.834, 424.500,
    -94.1432, -111.934, -98.1437, -55.4021, -1.80311, 37.4101, 71.1639, 104.339, 139.738, 177.437, 217.965, 259.977, 304.554, 350.363, 391.070,
    -89.8886, -106.662, -94.1935, -57.9105, -16.6678, 11.8064, 35.9303, 59.6562, 85.2313, 112.964, 143.547, 176.309, 212.534, 251.721, 288.661,
    -80.6402, -95.6126, -83.9429, -53.6845, -23.8558, -5.24553, 9.86232, 24.4443, 40.0580, 57.0143, 75.8601, 96.3137, 119.329, 144.776, 169.352,
    -68.7689, -81.5368, -70.2174, -44.6587, -22.8783, -10.7466, -1.42975, 7.29477, 16.4729, 26.3449, 37.2750, 49.1427, 62.5455, 77.4571, 91.9676,
    -51.4014, -60.9905, -50.3313, -30.5113, -16.4677, -9.69030, -4.86007, -0.532208, 3.89258, 8.56451, 13.6788, 19.1978, 25.4149, 32.3326, 39.0769,
    -21.8645, -26.0576, -19.1544, -10.1155, -5.34728, -3.44904, -2.22057, -1.18233, -0.161640, 0.887702, 2.01632, 3.22070, 4.56838, 6.06251, 7.51705,
    6.83318, 8.27782, 4.98637, 2.23404, 1.13465, 0.746963, 0.508189, 0.311973, 0.122541, -0.0698905, -0.275274, -0.493411, -0.736829, -1.00629, -1.26845
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 10.8580,

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
"TiltCylExtThresholdStrict" => 97.9045,

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
  "InternalMsn" => "CAT82401",
  "Make" => "CAT",
  "Model" => "982M",
  "ModelDetail" => "982M",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
