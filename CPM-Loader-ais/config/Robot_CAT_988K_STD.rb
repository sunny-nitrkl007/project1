##
## CAT 988K - Standard
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Depending on sensor mounting, sensor duty cycle increases or decreases with
# raise. 0 = not inverted (default), 1 = inverted
"invertLiftDc" => 0,

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.000000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-38.52, 42.97],

# Lift angle axis of the lift cylinder length table, in degrees.
"inLiftAngle" => [-38.52,-30.04,-23.29,-17.3,-11.72,-6.51,-1.47,3.39,8.13,12.75,17.23,21.66,26.03,30.34,34.58,38.75,42.97],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1980.0,2126.0,2239.0,2336.0,2423.0,2501.0,2573.0,2639.0,2700.0,2756.0,2807.0,2854.0,2897.0,2936.0,2971.0,3002.0,3030.0],

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-38.52, 42.97],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1980.0,3030.0],

##
## Tilt Kinematics
##

# Depending on sensor mounting, sensor duty cycle increases or decreases with
# rack. 0 = not inverted (default), 1 = inverted
"invertTiltDc" => 1,

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.00,3.858307001,7.417262598,10.92632629,14.73474139,20.08980542,28.92067188,34.60834858,40.36254781,46.71544986,54.21586562,63.97804756,81.87260935,90.10477299,94.99417928,98.10410777,100.00],

# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger 
# angles are rack.
"outTiltAngle" => [15.44,18.11,22.27,28.13,36.36,50.23,73.93,87.55,99.52,110.88,122.33,135.19,156.55,167.33,175.14,181.49,186.77],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [15.44,17.17,20.32,25.67,34.97,57.92,77.82,92.22,104.32,115.22,125.72,137.17,154.47,164.42,172.42,179.72,186.77],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-38.52,-34.27,-30.07,-25.92,-21.77,-17.62,-13.42,-9.17,-4.82,-0.32,4.33,9.23,14.43,20.03,26.28,33.53,42.97],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [1489.3,1478.3,1470.9,1467.1,1466.8,1469.9,1476.6,1486.9,1501,1519.1,1541.4,1568.4,1600.8,1639.2,1685.8,1743.7,1822.8,
    1505.7,1495.2,1488.3,1485,1485.1,1488.8,1495.9,1506.7,1521.1,1539.7,1562.3,1589.7,1622.4,1661.1,1708,1766,1845.3,
    1526.1,1516.2,1509.9,1507.1,1507.8,1511.9,1519.6,1530.8,1545.7,1564.7,1587.8,1615.6,1648.6,1687.6,1734.7,1793,1872.5,
    1551,1541.7,1536,1533.8,1535,1539.7,1547.9,1559.7,1575.1,1594.5,1618,1646.2,1679.5,1718.9,1766.3,1824.8,1904.5,
    1584.1,1575.5,1570.5,1569,1570.9,1576.2,1585,1597.3,1613.3,1633.2,1657.2,1685.8,1719.5,1759.3,1807,1865.8,1945.6,
    1653.1,1645.7,1641.8,1641.4,1644.4,1650.8,1660.6,1673.8,1690.6,1711.3,1736,1765.3,1799.7,1839.9,1888.1,1947.3,2027.3,
    1717.6,1711,1707.9,1708.3,1712,1719,1729.5,1743.3,1760.7,1781.9,1807.1,1836.8,1871.5,1912.1,1960.6,2019.9,2100.2,
    1773.9,1767.9,1765.3,1766.2,1770.4,1777.9,1788.7,1802.9,1820.7,1842.2,1867.7,1897.6,1932.6,1973.3,2022,2081.5,2161.8,
    1831.2,1825.6,1823.5,1824.8,1829.3,1837.2,1848.3,1862.8,1880.8,1902.6,1928.2,1958.3,1993.4,2034.3,2083,2142.6,2223,
    1893.2,1887.9,1886.2,1887.7,1892.6,1900.6,1912,1926.7,1944.9,1966.8,1992.5,2022.8,2058,2098.9,2147.7,2207.3,2287.6,
    1963.5,1958.6,1957.1,1958.8,1963.9,1972.1,1983.7,1998.5,2016.7,2038.7,2064.5,2094.8,2130,2170.9,2219.7,2279.3,2359.6,
    2051.9,2047.1,2045.8,2047.7,2052.8,2061.1,2072.7,2087.5,2105.7,2127.7,2153.4,2183.7,2218.8,2259.6,2308.3,2367.8,2448.1,
    2197.1,2192.3,2190.9,2192.7,2197.6,2205.8,2217.1,2231.6,2249.6,2271.3,2296.7,2326.6,2361.3,2401.9,2450.2,2509.5,2589.6,
    2274.9,2270,2268.4,2270,2274.7,2282.6,2293.7,2308,2325.7,2347.1,2372.2,2401.8,2436.3,2476.6,2524.7,2583.7,2663.7,
    2327.8,2322.7,2320.9,2322.3,2326.9,2334.5,2345.4,2359.5,2376.9,2398.1,2423,2452.4,2486.7,2526.7,2574.6,2633.5,2713.3,
    2365.6,2360.4,2358.4,2359.7,2364.1,2371.6,2382.3,2396.2,2413.5,2434.4,2459.2,2488.3,2522.4,2562.3,2610.1,2668.8,2748.5,
    2391.4,2386.1,2384,2385.1,2389.4,2396.8,2407.4,2421.1,2438.3,2459.1,2483.7,2512.7,2546.7,2586.5,2634.1,2692.8,2772.4
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [15.44,186.77],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [ -92.76,78.57],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [15.44,186.77],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1705.0,2390.0],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 209.55,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 127.0,

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
"LoaderBktPayldTrgtWt" => 19.1,

# The CAT datalink configuration file.
"BMI_CDL_CONFIG_JSON_FILE_PATH" =>  ENV["CAT_CONFIG_DIR"] + "/BmiCdl_PID_LWL.json",

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_LWL.json",

# Determines whether or not hydraulic oil temperature is optional for this
# machine configuration.
"HydOilTempOptional" => true,

# Determines whether or not acceleration compensation is supported for this
# machine configuration
"AccelCompSupported" => false,

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
"KgPerLiftKpaAtMidExtension" => 1.351,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 2815.23,

##
## Temperature Compensation
##

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylHeLineLoss2ndOrdrCoeff" => 0,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3.
"LiftCylHeLineLoss1stOrdrCoeff" => 0,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylReLineLoss2ndOrdrCoeff" => 0,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3
"LiftCylReLineLoss1stOrdrCoeff" => 0,

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
"AutoWeighMinLiftHt" => 15.0000,

##
## Zero Weight Configuration
##

# Which level of accuracy is required for a valid bucket zero (accuracy level 1,
# 2, or 3, etc.).
"ZeroBktWtAccuracyLimit" => 3,

# Maximum allowed ratio of calibration weight that is allowed for bucket zero.
"ZeroRangeLimit" => 0.15,

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
"LiftCylExtPctAxis" => [0.0,15.047619,28.190476,43.428571,57.904762,68.47619,75.238095,80.571429,84.857143,88.47619,91.52381,94.095238,96.380952,98.285714,100.0],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.0,5.839416,10.948905,15.620438,19.854015,23.79562,27.591241,31.094891,34.452555,37.664234,40.729927,43.941606,47.591241,52.70073,61.021898,68.321168,75.474453,83.50365,93.430657,100.0],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [-13.3635,-59.044812,-54.561524,-0.797796,79.198612,125.100639,117.458831,74.55957,12.645462,-60.356587,-140.342778,-226.850768,-326.139626,-433.925812,-561.731111,
    -34.614449,-72.037949,-66.510394,-13.742159,74.506772,151.73218,181.53807,168.145743,119.714197,48.655077,-33.63071,-121.677647,-219.574464,-322.351096,-440.585839,
    -45.444408,-79.459543,-75.058011,-26.566943,59.363242,150.103967,208.949736,232.527645,214.705187,160.678367,83.058416,-6.4153,-106.800853,-210.221456,-326.056247,
    -51.174901,-83.856454,-81.180679,-37.681735,41.563994,133.615743,207.882057,261.443887,280.24474,258.673205,200.925476,119.023391,18.909171,-86.645888,-203.921799,
    -54.054491,-86.327303,-85.364109,-46.497656,25.030742,112.051048,190.627017,261.378829,309.82473,324.669144,299.5142,239.155708,149.471855,46.200962,-72.193353,
    -55.357964,-87.598539,-88.170179,-53.369132,10.673902,90.091795,166.45745,243.842626,310.912224,356.348692,367.433125,339.832944,274.182664,183.381804,69.683173,
    -55.705176,-88.053276,-89.964704,-58.710405,-1.584752,69.41383,140.130983,217.054537,292.753386,358.932261,401.769286,410.877503,380.590225,315.382007,217.681026,
    -55.432286,-87.908106,-90.902751,-62.555782,-11.316252,51.803267,115.731272,188.229303,265.055886,341.453348,405.704776,445.821598,452.754128,421.605095,351.707874,
    -54.75525,-87.329238,-91.212852,-65.316963,-19.17518,36.734751,93.656837,159.848982,233.378977,312.486216,388.63088,451.118614,490.903616,496.249711,462.826731,
    -53.80095,-86.419144,-91.015777,-67.169847,-25.386902,24.145487,74.430179,133.723773,201.611459,278.462492,358.758248,434.318867,498.312002,535.91937,540.899405,
    -52.657034,-85.256598,-90.412118,-68.272656,-30.192072,13.807809,58.09069,110.631594,171.942641,243.728619,322.854252,403.738394,482.503292,544.262736,583.168477,
    -51.249474,-83.755346,-89.374734,-68.783565,-34.133338,4.672806,43.171234,88.873774,142.857687,207.616871,281.845382,362.318654,448.138693,526.251483,593.022879,
    -49.42214,-81.720321,-87.724753,-68.627195,-37.372112,-3.745043,28.88737,67.416453,113.220915,169.143322,235.200482,310.126585,395.584598,481.517688,567.648836,
    -46.500618,-78.313117,-84.622562,-67.209223,-39.936269,-12.390202,13.296949,43.129225,78.558877,122.336483,175.351186,237.879407,313.433985,395.871852,488.76066,
    -40.902918,-71.390988,-77.67649,-62.223174,-39.965959,-19.957033,-2.802253,16.239046,38.401825,65.749143,99.343499,140.134644,191.737749,251.823809,325.868057,
    -35.114465,-63.80904,-69.602565,-55.348752,-36.527794,-21.407169,-9.560096,2.874133,16.88265,33.899655,54.733413,80.190735,112.890987,151.896751,201.636532,
    -28.513073,-54.699996,-59.617871,-46.373541,-30.57031,-19.296397,-11.306505,-3.471474,4.977516,14.983983,27.08233,41.815522,60.807723,83.677618,113.291128,
    -19.684258,-41.662102,-45.133362,-33.376336,-21.269969,-13.839053,-9.191392,-5.023258,-0.796715,4.020231,9.717844,16.582772,25.404225,36.051524,49.933142,
    -5.913859,-17.472141,-18.449544,-11.693365,-6.652721,-4.254507,-2.996484,-1.997704,-1.068843,-0.06757,1.07863,2.436208,4.167614,6.254575,8.983282,
    -1.691804,19.421256,17.630347,7.398012,3.581489,2.219229,1.587848,1.119663,0.702929,0.26516,-0.229385,-0.81206,-1.554619,-2.451209,-3.627172
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 11.3,

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
  "InternalMsn" => "CAT88200",
  "Make" => "CAT",
  "Model" => "988K",
  "ModelDetail" => "988K",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}
