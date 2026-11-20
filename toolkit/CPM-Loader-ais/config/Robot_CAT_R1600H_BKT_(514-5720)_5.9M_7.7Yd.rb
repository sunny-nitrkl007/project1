##
## CAT R1600H_BKT_(514-5720)_5.9M_7.7Yd
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
"outLiftAngle" => [-26.07137508, -23.4933087, -21.70162156, -20.26189187, -19.03415545, -15.26359568, -12.45195656, -10.15133051, -8.177649602, -6.434139014, -4.862630543, -3.425038939, -2.094893034, -0.852962351, 0.315207974, 1.42078185, 2.4725742, 3.477674275, 4.441872664, 5.369962477, 8.792919396, 11.87178834, 14.70970969, 17.37056075, 19.89645224, 22.31645995, 24.6513887, 26.91655217, 29.12348268, 31.28102843, 33.39608272, 35.47408308, 37.51936153, 39.53539567, 41.52499211, 43.49042252],

# Lift angle axis of the lift cylinder length table, in degrees.
"inLiftAngle" => [-26.0659, -22.0425, -18.1737, -14.4332, -10.7922, -7.25682, -3.83448, -0.534036, 2.67649, 5.78958, 8.84206, 11.7813, 14.6448, 17.4248, 20.1660, 22.8084, 25.3985, 27.8684, 30.3309, 32.7181, 35.0189, 37.2202, 39.3857, 41.5099, 43.4971],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1390.00, 1450.46, 1506.92, 1559.89, 1609.85, 1656.82, 1700.79, 1741.77, 1780.24, 1816.22, 1850.19, 1881.67, 1911.15, 1938.63, 1964.62, 1988.60, 2011.09, 2031.57, 2051.06, 2069.05, 2085.54, 2100.53, 2114.52, 2127.51, 2139.00],

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-26.0659, 43.4971],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1390.00, 2139.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.000000, 2.81599, 5.95081, 9.84842, 16.9032, 22.0706, 26.2600, 30.1834, 33.9687, 37.8132, 41.6939, 45.7942, 50.1064, 54.8726, 60.2896, 67.7695, 77.8242, 83.1300, 87.2232, 90.5866, 93.3930, 95.7137, 97.5544, 99.0019, 100.000],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger
# angles are rack.
"outTiltAngle" => [32.7900, 36.2193, 41.1489, 48.7576, 65.1538, 77.5849, 87.1225, 95.3742, 102.661, 109.413, 115.628, 121.630, 127.416, 133.311, 139.526, 147.563, 158.066, 163.853, 168.675, 173.069, 177.248, 181.320, 185.285, 189.358, 193.430],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [32.7900, 36.2193, 41.1489, 48.7576, 65.1538, 77.5849, 87.1225, 95.3742, 102.661, 109.413, 115.628, 121.630, 127.416, 133.311, 139.526, 147.563, 158.066, 163.853, 168.675, 173.069, 177.248, 181.320, 185.285, 189.358, 193.430],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-26.0659, -24.2846, -22.4804, -20.6520, -18.7977, -16.9161, -14.9696, -12.9906, -10.9770, -8.88856, -6.72002, -4.50479, -2.19859, 0.206292, 2.76145, 5.43793, 8.29479, 11.4016, 14.8432, 18.8334, 23.8877, 30.6555, 35.5950, 39.7851, 43.4971],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [
    942.157, 947.340, 953.074, 959.369, 966.231, 973.672, 981.854, 990.655, 1000.09, 1010.35, 1021.50, 1033.37, 1046.20, 1060.07, 1075.30, 1091.73, 1109.76, 1129.87, 1152.64, 1179.56, 1214.21, 1261.08, 1295.27, 1324.05, 1349.27,
    953.405, 958.790, 964.722, 971.208, 978.258, 985.880, 994.241, 1003.22, 1012.81, 1023.24, 1034.54, 1046.56, 1059.54, 1073.54, 1088.90, 1105.45, 1123.59, 1143.80, 1166.66, 1193.66, 1228.38, 1275.27, 1309.43, 1338.17, 1363.33,
    967.009, 972.606, 978.743, 985.430, 992.675, 1000.49, 1009.03, 1018.19, 1027.95, 1038.55, 1050.01, 1062.18, 1075.30, 1089.44, 1104.93, 1121.61, 1139.86, 1160.17, 1183.13, 1210.20, 1244.98, 1291.88, 1326.02, 1354.71, 1379.80,
    985.413, 991.251, 997.625, 1004.54, 1012.01, 1020.03, 1028.79, 1038.15, 1048.11, 1058.89, 1070.53, 1082.87, 1096.16, 1110.46, 1126.09, 1142.90, 1161.28, 1181.70, 1204.76, 1231.92, 1266.75, 1313.67, 1347.76, 1376.38, 1401.40,
    1022.50, 1028.72, 1035.46, 1042.74, 1050.55, 1058.91, 1067.99, 1077.66, 1087.92, 1098.99, 1110.91, 1123.52, 1137.05, 1151.58, 1167.43, 1184.45, 1203.01, 1223.60, 1246.80, 1274.08, 1309.00, 1355.90, 1389.91, 1418.42, 1443.30,
    1052.35, 1058.80, 1065.78, 1073.27, 1081.29, 1089.86, 1099.14, 1108.99, 1119.43, 1130.67, 1142.76, 1155.52, 1169.20, 1183.86, 1199.85, 1216.98, 1235.65, 1256.34, 1279.62, 1306.96, 1341.92, 1388.81, 1422.76, 1451.19, 1475.99,
    1077.98, 1084.59, 1091.72, 1099.37, 1107.54, 1116.24, 1125.66, 1135.64, 1146.20, 1157.56, 1169.76, 1182.62, 1196.40, 1211.16, 1227.23, 1244.44, 1263.19, 1283.93, 1307.27, 1334.65, 1369.63, 1416.50, 1450.41, 1478.79, 1503.52,
    1102.98, 1109.73, 1116.98, 1124.75, 1133.04, 1141.85, 1151.38, 1161.46, 1172.12, 1183.58, 1195.87, 1208.81, 1222.67, 1237.49, 1253.63, 1270.91, 1289.70, 1310.50, 1333.87, 1361.29, 1396.28, 1443.14, 1477.02, 1505.35, 1530.02,
    1127.89, 1134.75, 1142.11, 1149.98, 1158.37, 1167.27, 1176.89, 1187.06, 1197.80, 1209.32, 1221.69, 1234.69, 1248.61, 1263.50, 1279.69, 1297.01, 1315.86, 1336.69, 1360.10, 1387.54, 1422.54, 1469.38, 1503.23, 1531.52, 1556.15,
    1153.88, 1160.84, 1168.29, 1176.24, 1184.71, 1193.69, 1203.38, 1213.63, 1224.43, 1236.02, 1248.44, 1261.51, 1275.48, 1290.42, 1306.65, 1324.01, 1342.89, 1363.76, 1387.19, 1414.65, 1449.66, 1496.49, 1530.30, 1558.56, 1583.16,
    1180.71, 1187.74, 1195.27, 1203.30, 1211.83, 1220.88, 1230.63, 1240.93, 1251.79, 1263.43, 1275.90, 1289.01, 1303.03, 1318.00, 1334.27, 1351.66, 1370.57, 1391.46, 1414.91, 1442.38, 1477.40, 1524.22, 1558.01, 1586.24, 1610.81,
    1209.58, 1216.68, 1224.27, 1232.36, 1240.95, 1250.05, 1259.85, 1270.20, 1281.10, 1292.79, 1305.30, 1318.44, 1332.49, 1347.49, 1363.79, 1381.21, 1400.13, 1421.04, 1444.51, 1471.99, 1507.01, 1553.82, 1587.60, 1615.81, 1640.35,
    1240.40, 1247.56, 1255.20, 1263.33, 1271.96, 1281.11, 1290.95, 1301.33, 1312.27, 1323.98, 1336.52, 1349.69, 1363.76, 1378.78, 1395.10, 1412.53, 1431.47, 1452.39, 1475.87, 1503.36, 1538.38, 1585.18, 1618.95, 1647.15, 1671.67,
    1274.86, 1282.06, 1289.73, 1297.90, 1306.57, 1315.74, 1325.60, 1336.01, 1346.97, 1358.70, 1371.25, 1384.44, 1398.52, 1413.55, 1429.88, 1447.32, 1466.27, 1487.19, 1510.67, 1538.17, 1573.19, 1619.99, 1653.75, 1681.94, 1706.46,
    1314.34, 1321.55, 1329.25, 1337.43, 1346.11, 1355.29, 1365.17, 1375.58, 1386.55, 1398.28, 1410.84, 1424.03, 1438.11, 1453.14, 1469.47, 1486.91, 1505.85, 1526.77, 1550.25, 1577.74, 1612.76, 1659.57, 1693.33, 1721.52, 1746.05,
    1368.99, 1376.20, 1383.89, 1392.06, 1400.73, 1409.90, 1419.76, 1430.15, 1441.09, 1452.81, 1465.34, 1478.51, 1492.56, 1507.57, 1523.88, 1541.29, 1560.22, 1581.12, 1604.58, 1632.06, 1667.08, 1713.89, 1747.67, 1775.89, 1800.44,
    1441.91, 1449.06, 1456.68, 1464.79, 1473.38, 1482.48, 1492.26, 1502.59, 1513.46, 1525.10, 1537.56, 1550.65, 1564.64, 1579.58, 1595.81, 1613.17, 1632.03, 1652.88, 1676.30, 1703.75, 1738.75, 1785.59, 1819.43, 1847.70, 1872.31,
    1479.81, 1486.90, 1494.46, 1502.51, 1511.04, 1520.08, 1529.81, 1540.07, 1550.88, 1562.47, 1574.87, 1587.91, 1601.84, 1616.73, 1632.91, 1650.22, 1669.05, 1689.86, 1713.24, 1740.66, 1775.66, 1822.51, 1856.38, 1884.70, 1909.35,
    1508.64, 1515.68, 1523.19, 1531.18, 1539.66, 1548.64, 1558.32, 1568.53, 1579.28, 1590.82, 1603.17, 1616.15, 1630.04, 1644.88, 1661.02, 1678.29, 1697.07, 1717.85, 1741.20, 1768.60, 1803.58, 1850.45, 1884.35, 1912.70, 1937.40,
    1532.03, 1539.02, 1546.47, 1554.41, 1562.85, 1571.78, 1581.40, 1591.56, 1602.27, 1613.75, 1626.06, 1638.99, 1652.84, 1667.64, 1683.73, 1700.96, 1719.71, 1740.46, 1763.78, 1791.16, 1826.13, 1873.01, 1906.93, 1935.31, 1960.05,
    1551.31, 1558.25, 1565.66, 1573.55, 1581.94, 1590.83, 1600.40, 1610.52, 1621.18, 1632.62, 1644.88, 1657.78, 1671.58, 1686.34, 1702.40, 1719.59, 1738.31, 1759.03, 1782.33, 1809.68, 1844.64, 1891.53, 1925.47, 1953.88, 1978.65,
    1567.08, 1573.97, 1581.34, 1589.20, 1597.54, 1606.39, 1615.92, 1626.00, 1636.63, 1648.03, 1660.25, 1673.11, 1686.87, 1701.60, 1717.63, 1734.79, 1753.48, 1774.17, 1797.45, 1824.79, 1859.73, 1906.63, 1940.59, 1969.02, 1993.82,
    1579.47, 1586.33, 1593.66, 1601.48, 1609.79, 1618.60, 1628.11, 1638.15, 1648.74, 1660.11, 1672.30, 1685.13, 1698.87, 1713.57, 1729.57, 1746.70, 1765.37, 1786.04, 1809.30, 1836.62, 1871.56, 1918.46, 1952.43, 1980.89, 2005.70,
    1589.13, 1595.96, 1603.27, 1611.06, 1619.34, 1628.13, 1637.60, 1647.62, 1658.18, 1669.53, 1681.69, 1694.50, 1708.21, 1722.89, 1738.86, 1755.98, 1774.63, 1795.28, 1818.52, 1845.83, 1880.76, 1927.66, 1961.65, 1990.12, 2014.95,
    1595.75, 1602.56, 1609.85, 1617.62, 1625.88, 1634.65, 1644.10, 1654.10, 1664.65, 1675.98, 1688.12, 1700.91, 1714.61, 1729.27, 1745.23, 1762.33, 1780.96, 1801.60, 1824.83, 1852.13, 1887.06, 1933.96, 1967.96, 1996.44, 2021.28
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [32.7900, 193.430],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-83.3861, 77.2539],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [32.7900, 193.430],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1118.50, 1625.00],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 190.500,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 88.8500,

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
"LoaderBktPayldTrgtWt" => 10.5020,

# The CAT datalink configuration file.
"BMI_CDL_CONFIG_JSON_FILE_PATH" =>  ENV["CAT_CONFIG_DIR"] + "/BmiCdl_LHD.json",

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
"KgPerLiftKpaAtMidExtension" => 1.33528,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1326.00,

##
## Temperature Compensation
##

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylHeLineLoss2ndOrdrCoeff" => 2.34121E-06,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3.
"LiftCylHeLineLoss1stOrdrCoeff" => 4.00077,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylReLineLoss2ndOrdrCoeff" => 2.73489E-06,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3
"LiftCylReLineLoss1stOrdrCoeff" => 4.00208,

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
"LiftCylExtPctAxis" => [0.000000, 4.40587, 8.27770, 12.2830, 20.4272, 43.6582, 55.5407, 65.0200, 72.8972, 79.4393, 85.0467, 89.7196, 93.7250, 97.1963, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.000000, 7.89733, 15.0049, 21.7177, 27.8381, 33.5637, 39.0918, 44.2251, 48.9635, 53.5044, 57.8480, 62.5864, 69.8914, 81.3425, 91.2142, 94.2744, 95.4985, 96.8016, 98.2626, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -69.4864, -15.5343, 13.2567, 39.0430, 88.7856, 197.705, 145.109, 16.9814, -156.641, -533.241, -2115.10, -3982.09, -5778.47, -7404.65, -8731.68,
    -91.6107, -40.1531, -13.6014, 9.94686, 56.3608, 211.354, 253.213, 180.147, 27.9303, -165.586, -504.747, -2744.12, -5485.02, -8099.52, -10248.6,
    -107.781, -58.6887, -34.4653, -13.5719, 26.8027, 177.894, 274.482, 297.173, 203.474, 32.3609, -185.670, -513.098, -4989.64, -7713.39, -9733.04,
    -119.247, -72.0757, -49.7967, -31.1985, 3.49581, 133.735, 240.589, 327.957, 334.332, 225.079, 33.7214, -199.712, -530.726, -1589.30, -2647.16,
    -126.708, -80.9624, -60.1426, -43.2903, -13.0477, 95.4175, 191.598, 297.125, 374.910, 363.583, 235.491, 30.9066, -223.621, -575.247, -1296.46,
    -131.409, -86.7391, -67.0266, -51.5064, -24.6996, 65.1607, 145.425, 244.559, 349.295, 415.146, 385.932, 244.638, 23.0223, -257.454, -605.223,
    -134.108, -90.2780, -71.4340, -56.9612, -32.8652, 41.7542, 106.457, 190.340, 293.444, 394.602, 450.454, 408.393, 254.822, 13.6704, -271.252,
    -135.158, -91.9704, -73.7911, -60.1201, -38.0964, 24.8002, 76.6842, 144.781, 234.384, 338.988, 437.002, 480.205, 424.828, 254.996, 11.7719,
    -134.975, -92.2893, -74.6300, -61.5851, -41.1711, 12.7394, 54.5962, 109.174, 183.130, 276.936, 383.996, 473.734, 504.298, 431.885, 258.054,
    -133.802, -91.5378, -74.3150, -61.7936, -42.7123, 3.96604, 37.8000, 81.1391, 140.433, 218.926, 317.910, 422.123, 505.080, 523.009, 443.058,
    -131.765, -89.8713, -73.0292, -60.9608, -43.0148, -2.23438, 25.2134, 59.4971, 106.295, 169.542, 253.723, 353.030, 455.319, 531.170, 538.261,
    -128.477, -86.9755, -70.5320, -58.9309, -42.1272, -6.90259, 14.7868, 40.9432, 76.2342, 124.323, 190.430, 274.023, 372.924, 474.082, 543.932,
    -120.922, -80.0922, -64.3059, -53.4491, -38.3705, -10.5133, 4.21857, 20.8238, 42.5287, 71.9363, 113.141, 167.958, 239.644, 328.623, 420.773,
    -100.044, -61.1553, -47.0623, -37.9395, -26.3427, -9.21750, -2.34730, 4.42282, 12.6313, 23.3674, 38.3049, 58.5564, 86.4051, 124.503, 171.168,
    -55.5000, -25.7083, -17.3083, -12.7408, -7.94267, -2.75675, -1.21879, 0.100921, 1.57190, 3.40898, 5.90779, 9.27236, 13.9282, 20.4323, 28.7152,
    2.95042, 0.775332, 0.443562, 0.299971, 0.172612, 0.0575415, 0.0272794, 0.00246174, -0.0244300, -0.0574782, -0.102049, -0.161827, -0.244485, -0.360196, -0.508306,
    39.9076, 23.6574, 11.2573, 7.12505, 3.90170, 1.27137, 0.616195, 0.0885190, -0.476815, -1.16705, -2.09468, -3.33673, -5.05333, -7.45758, -10.5397,
    82.5084, 69.9888, 29.4340, 16.2428, 8.25174, 2.61113, 1.29196, 0.249524, -0.854029, -2.19206, -3.98355, -6.37785, -9.68495, -14.3186, -20.2668,
    132.797, 139.152, 147.205, 31.1207, 13.6942, 4.16246, 2.10173, 0.506795, -1.15958, -3.16448, -5.83758, -9.40267, -14.3232, -21.2193, -30.0830,
    194.708, 231.768, 240.804, 114.188, 21.1574, 6.05561, 3.12259, 0.904948, -1.37757, -4.09931, -7.71034, -12.5144, -19.1384, -28.4233, -40.3718
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 10.5020,

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
"FullRackBktAngleThreshold" => 15.0000,

# The bucket is considered partially dumped if the bucket angle is less than or
# equal to this value, as well as other conditions. Partial Dump = (Cyl% <= X)
# AND (ABC% <= Y) AND (Bucket Angle <= This Value)
"PartDumpBktAngleThreshold" => 20.0000,

# The bucket is considered fully dumped if the bucket angle is less than this
# value. Fully Dumped = (Bucket Angle <= This Value), in degrees.
"FullDumpBktAngleThreshold" => -35.0000,

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

# Default Auto Store value
"AutoStorePassCountDefault" => 1,

# This will define what UI configurable features are Enabled or Disabled.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" =>  ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_UGM.json",

}

MachineType = {
  "InternalMsn" => "CAT16023",
  "Make" => "CAT",
  "Model" => "R1600H",
  "ModelDetail" => "R1600H BKT (514-5720)",
  "Linkage" => "BKT (514-5720) 5.9M/ 7.7Yd",
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
