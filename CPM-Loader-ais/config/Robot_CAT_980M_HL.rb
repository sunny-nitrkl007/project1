##
## CAT 980M - High Lift
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-38.3000, 47.0700],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-38.3000, -34.3200, -30.3500, -26.3700, -22.3400, -18.2700, -14.1300, -9.91000, -5.57000, -1.09000, 3.55000, 8.39000, 13.4900, 18.9100, 24.7500, 31.1700, 38.4300, 47.0700],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1504.00, 1554.80, 1605.70, 1656.50, 1707.30, 1758.10, 1808.90, 1859.80, 1910.60, 1961.40, 2012.20, 2063.10, 2113.90, 2164.70, 2215.50, 2266.40, 2317.20, 2368.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0783738, 0.0781196, 0.0782484, 0.0787287, 0.0795534, 0.0807220, 0.0822568, 0.0841905, 0.0865895, 0.0895386, 0.0931560, 0.0976264, 0.103243, 0.110449, 0.120019, 0.133423, 0.153820, 0.189975],

# Lift cylinder pressure without bucket table, in kPa.
"outLiftPresNoBucket" => [1447.53, 1495.24, 1543.04, 1590.74, 1638.41, 1686.03, 1733.61, 1781.20, 1828.61, 1875.89, 1923.03, 1970.07, 2016.76, 2063.08, 2108.87, 2153.92, 2197.39, 2237.60],

# deg/s^2
"outLiftAngleAccel" => [-0.0677172, -0.00817353, 0.0453112, 0.0957941, 0.146012, 0.197880, 0.253890, 0.316616, 0.389809, 0.478228, 0.588731, 0.732348, 0.927846, 1.20815, 1.63893, 2.36894, 3.80329, 7.48085],

# mm/s
"liftRefVel" => 86.4000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 3400.00,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-38.3000, 47.0700],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1504.00, 2368.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00000, 6.28367, 12.5338, 18.7106, 24.9302, 31.1559, 37.3938, 43.6622, 49.9306, 56.1944, 62.4567, 68.7129, 74.9752, 81.2314, 87.4876, 93.7469, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [7.42000, 17.3500, 33.2600, 51.2900, 68.3800, 83.1800, 95.7100, 106.380, 115.590, 123.740, 131.160, 138.110, 144.870, 151.690, 158.950, 167.360, 179.250],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [7.00000, 9.00000, 12.0000, 20.0000, 28.5000, 44.5000, 54.5000, 63.0000, 70.5000, 78.0000, 84.5000, 91.0000, 97.0000, 102.500, 108.000, 113.000, 118.000, 124.000, 130.000, 136.500, 150.000, 155.000, 159.500, 165.000, 170.000, 175.000, 179.500],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-38.5000, -34.5000, -30.5000, -26.5000, -24.0000, -22.0000, -17.5000, -13.0000, -8.50000, -3.50000, 1.50000, 6.50000, 12.0000, 18.0000, 24.0000, 30.5000, 38.0000, 47.5000],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    1366.00, 1355.50, 1347.90, 1343.10, 1341.60, 1341.20, 1343.00, 1348.40, 1357.50, 1371.60, 1389.80, 1411.80, 1439.90, 1474.70, 1513.20, 1558.30, 1613.60, 1686.80,
    1372.70, 1362.60, 1355.20, 1350.70, 1349.30, 1349.10, 1351.20, 1356.90, 1366.30, 1380.70, 1399.20, 1421.40, 1449.80, 1484.80, 1523.50, 1568.70, 1624.10, 1697.40,
    1381.00, 1371.10, 1364.10, 1359.90, 1358.70, 1358.60, 1361.00, 1367.10, 1376.80, 1391.60, 1410.40, 1432.80, 1461.40, 1496.70, 1535.60, 1581.00, 1636.50, 1709.90,
    1398.40, 1389.20, 1382.70, 1379.00, 1378.20, 1378.40, 1381.50, 1388.20, 1398.40, 1413.80, 1433.10, 1456.10, 1485.20, 1520.90, 1560.10, 1605.80, 1661.60, 1735.10,
    1414.20, 1405.40, 1399.40, 1396.20, 1395.70, 1396.10, 1399.70, 1406.90, 1417.60, 1433.40, 1453.10, 1476.50, 1505.90, 1541.90, 1581.40, 1627.30, 1683.30, 1756.90,
    1442.90, 1434.80, 1429.50, 1427.00, 1426.90, 1427.70, 1432.00, 1439.90, 1451.30, 1467.80, 1488.20, 1512.10, 1542.00, 1578.50, 1618.40, 1664.60, 1720.80, 1794.60,
    1462.10, 1454.40, 1449.40, 1447.40, 1447.60, 1448.50, 1453.20, 1461.50, 1473.30, 1490.20, 1510.90, 1535.10, 1565.30, 1602.10, 1642.20, 1688.60, 1744.90, 1818.70,
    1479.90, 1472.60, 1468.00, 1466.20, 1466.60, 1467.70, 1472.80, 1481.40, 1493.50, 1510.70, 1531.60, 1556.10, 1586.60, 1623.60, 1663.80, 1710.30, 1766.80, 1840.70,
    1497.40, 1490.30, 1486.00, 1484.50, 1485.10, 1486.30, 1491.70, 1500.60, 1512.90, 1530.40, 1551.60, 1576.30, 1606.90, 1644.10, 1684.50, 1731.10, 1787.70, 1861.60,
    1516.80, 1510.00, 1506.00, 1504.90, 1505.60, 1507.00, 1512.60, 1521.80, 1534.40, 1552.10, 1573.60, 1598.40, 1629.30, 1666.60, 1707.20, 1753.90, 1810.50, 1884.50,
    1535.60, 1529.10, 1525.40, 1524.50, 1525.30, 1526.80, 1532.80, 1542.20, 1555.00, 1573.00, 1594.60, 1619.60, 1650.70, 1688.10, 1728.80, 1775.60, 1832.30, 1906.30,
    1556.70, 1550.50, 1547.00, 1546.30, 1547.40, 1549.00, 1555.20, 1564.80, 1577.80, 1596.00, 1617.90, 1643.00, 1674.20, 1711.80, 1752.60, 1799.50, 1856.20, 1930.30,
    1578.50, 1572.50, 1569.30, 1568.80, 1570.00, 1571.70, 1578.20, 1588.00, 1601.20, 1619.60, 1641.60, 1666.90, 1698.30, 1736.00, 1776.80, 1823.80, 1880.60, 1954.70,
    1600.80, 1595.00, 1591.90, 1591.70, 1593.00, 1594.80, 1601.50, 1611.50, 1624.90, 1643.40, 1665.60, 1691.10, 1722.50, 1760.30, 1801.20, 1848.30, 1905.10, 1979.20,
    1625.50, 1619.90, 1617.00, 1617.00, 1618.40, 1620.30, 1627.20, 1637.40, 1650.90, 1669.60, 1691.90, 1717.50, 1749.00, 1786.90, 1827.90, 1875.00, 1931.90, 2006.00,
    1650.20, 1644.80, 1642.10, 1642.30, 1643.80, 1645.80, 1652.80, 1663.20, 1676.80, 1695.60, 1718.00, 1743.70, 1775.30, 1813.30, 1854.30, 1901.50, 1958.40, 2032.50,
    1677.30, 1672.00, 1669.50, 1669.80, 1671.40, 1673.50, 1680.60, 1691.20, 1704.90, 1723.90, 1746.40, 1772.10, 1803.80, 1841.80, 1882.90, 1930.00, 1986.90, 2061.10,
    1712.90, 1707.80, 1705.50, 1706.00, 1707.70, 1709.80, 1717.10, 1727.70, 1741.60, 1760.70, 1783.20, 1809.00, 1840.70, 1878.80, 1919.90, 1967.10, 2024.00, 2098.20,
    1751.70, 1746.80, 1744.70, 1745.30, 1747.00, 1749.20, 1756.60, 1767.40, 1781.30, 1800.40, 1823.00, 1848.90, 1880.60, 1918.70, 1959.80, 2006.90, 2063.90, 2138.00,
    1797.00, 1792.20, 1790.10, 1790.80, 1792.60, 1794.80, 1802.30, 1813.10, 1827.10, 1846.20, 1868.80, 1894.60, 1926.30, 1964.40, 2005.40, 2052.60, 2109.40, 2183.60,
    1895.30, 1890.50, 1888.50, 1889.20, 1891.00, 1893.20, 1900.60, 1911.30, 1925.20, 1944.10, 1966.60, 1992.20, 2023.70, 2061.50, 2102.40, 2149.40, 2206.20, 2280.20,
    1930.40, 1925.60, 1923.60, 1924.20, 1926.00, 1928.10, 1935.40, 1946.00, 1959.80, 1978.70, 2001.00, 2026.50, 2057.90, 2095.60, 2136.40, 2183.30, 2240.00, 2314.00,
    1960.10, 1955.20, 1953.10, 1953.70, 1955.40, 1957.50, 1964.80, 1975.30, 1988.90, 2007.70, 2029.90, 2055.30, 2086.60, 2124.20, 2164.80, 2211.70, 2268.30, 2342.30,
    1992.80, 1987.90, 1985.70, 1986.20, 1987.80, 1989.90, 1997.00, 2007.40, 2020.90, 2039.50, 2061.50, 2086.80, 2117.90, 2155.40, 2196.00, 2242.70, 2299.20, 2373.10,
    2018.40, 2013.40, 2011.10, 2011.50, 2013.10, 2015.20, 2022.10, 2032.40, 2045.80, 2064.20, 2086.20, 2111.30, 2142.30, 2179.70, 2220.10, 2266.70, 2323.20, 2397.10,
    2039.50, 2034.50, 2032.10, 2032.40, 2033.90, 2035.90, 2042.80, 2052.90, 2066.30, 2084.60, 2106.40, 2131.40, 2162.30, 2199.50, 2239.90, 2286.40, 2342.80, 2416.70,
    2054.40, 2049.30, 2046.90, 2047.10, 2048.60, 2050.60, 2057.40, 2067.40, 2080.70, 2098.90, 2120.60, 2145.60, 2176.40, 2213.50, 2253.80, 2300.30, 2356.60, 2430.50
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [7.42000, 179.250],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-96.0300, 75.8000],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [7.42000, 179.250],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1475.00, 2057.00],

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
"LoaderBktPayldTrgtWt" => 9.11500,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 12.5000,

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
"KgPerLiftKpaAtMidExtension" => 0.988977,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1838.20,

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
"LiftCylExtPctAxis" => [0.00000, 16.5509, 36.8056, 55.5556, 65.2778, 72.1065, 77.5463, 82.0602, 85.8796, 89.1204, 91.8981, 94.3287, 96.5278, 98.3796, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 6.18557, 11.5120, 16.3230, 20.7904, 24.9141, 28.8660, 32.6460, 36.2543, 39.6907, 42.9553, 46.0481, 49.1409, 52.4055, 56.5292, 64.0893, 71.8213, 79.5533, 89.0034, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -80.6066, -129.014, 4.92938, 218.296, 231.479, 112.368, -48.6735, -221.014, -418.320, -667.416, -1031.86, -1808.53, -2526.71, -3150.88, -3700.37,
    -132.268, -150.173, -23.1388, 227.236, 361.320, 344.265, 195.870, -2.29220, -203.890, -412.701, -651.644, -962.107, -1464.23, -2697.27, -3657.27,
    -146.695, -158.988, -48.5781, 188.603, 376.468, 477.221, 436.078, 261.280, 32.8759, -193.556, -418.007, -663.819, -972.291, -1379.72, -2072.45,
    -148.534, -162.443, -68.3497, 140.972, 333.855, 498.239, 578.294, 512.892, 313.699, 62.4891, -185.669, -429.943, -696.879, -993.309, -1367.82,
    -145.626, -163.086, -82.9453, 97.3914, 273.751, 454.270, 608.386, 668.943, 579.750, 361.099, 90.9870, -180.285, -453.474, -724.292, -1024.43,
    -140.950, -162.091, -93.1736, 61.8731, 215.720, 387.140, 567.162, 710.892, 749.447, 637.037, 400.976, 110.756, -191.051, -472.722, -757.802,
    -135.540, -160.040, -100.295, 33.2656, 164.497, 316.711, 493.954, 674.351, 806.892, 825.156, 694.479, 440.897, 121.849, -187.841, -487.676,
    -129.917, -157.269, -104.934, 10.9174, 121.960, 252.700, 413.440, 597.832, 777.281, 896.985, 897.949, 750.165, 470.698, 147.230, -180.014,
    -124.332, -154.008, -107.630, -6.18367, 87.7790, 198.384, 338.186, 509.380, 700.035, 875.260, 982.665, 967.883, 796.554, 513.049, 176.375,
    -118.906, -150.417, -108.823, -19.0480, 60.8301, 153.935, 273.035, 424.306, 605.820, 799.295, 969.254, 1065.66, 1031.70, 850.874, 557.444,
    -113.692, -146.612, -108.864, -28.5575, 39.8376, 118.283, 218.857, 349.160, 512.472, 701.458, 896.205, 1061.98, 1147.01, 1097.16, 905.285,
    -108.714, -142.681, -108.030, -35.4391, 23.6276, 90.0131, 174.787, 285.684, 428.303, 601.642, 796.746, 993.925, 1157.68, 1224.61, 1161.04,
    -103.700, -138.447, -106.434, -40.5151, 10.5547, 66.5640, 137.469, 230.525, 352.082, 504.582, 686.095, 888.540, 1093.61, 1245.48, 1304.66,
    -98.3614, -133.659, -104.000, -44.1682, -0.291237, 46.4126, 104.752, 181.182, 281.903, 410.958, 570.499, 760.257, 975.809, 1175.82, 1329.44,
    -91.5298, -127.139, -99.9229, -46.6356, -10.3122, 26.7212, 71.9698, 130.776, 208.527, 309.628, 438.264, 598.924, 797.093, 1008.40, 1218.27,
    -78.6177, -113.741, -89.8259, -46.1241, -20.2790, 3.74344, 31.5636, 66.7509, 112.880, 173.274, 251.854, 354.167, 489.519, 650.677, 840.621,
    -64.5732, -97.7667, -76.2171, -40.4267, -22.2725, -7.15158, 9.16982, 28.9875, 54.4327, 87.5052, 130.673, 187.625, 264.923, 360.816, 480.922,
    -49.1216, -78.6670, -59.1955, -30.8639, -18.6774, -9.68869, -0.769569, 9.51241, 22.3390, 38.7745, 60.1184, 88.3220, 126.905, 175.485, 237.737,
    -26.9536, -48.2137, -32.8560, -15.5638, -9.72965, -6.06904, -2.83295, 0.634321, 4.78823, 10.0056, 16.7237, 25.5833, 37.7338, 53.1305, 73.0652,
    5.44780, 18.2112, 7.50032, 2.62238, 1.60969, 1.08320, 0.664078, 0.237522, -0.264777, -0.895491, -1.71268, -2.79909, -4.30179, -6.22203, -8.72940
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 9.11500,

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
  "InternalMsn" => "CAT80401",
  "Make" => "CAT",
  "Model" => "980M",
  "ModelDetail" => "980M",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0002,
}
