##

## CAT 988K - High Lift
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Depending how the Rotation Sensor is mounter for LIFT & TILT, the DC may need to be inverted
#    0 = don't invert	//dc = sensorDc
#    1 = invert  		//dc = (100-sensorDc)
"invertLiftDc" => 0,
"invertTiltDc" => 1,

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.000000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-35.39, 45.93],

# Lift angle axis of the lift cylinder length table, in degrees.
"inLiftAngle" => [-35.39,-26.91,-20.17,-14.18,-8.67,-3.46,1.57,6.42,11.14,15.75,20.21,24.62,28.97,33.26,37.47,41.74,45.93],


# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1980.0,2126.0,2239.0,2336.0,2423.0,2501.0,2573.0,2639.0,2700.0,2756.0,2807.0,2854.0,2897.0,2936.0,2971.0,3002.0,3030.0],

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-35.39, 45.93],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1980.0,3030.0],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 

"inTiltDc" => [0.00,3.19,6.36,9.75,13.88,22.79,29.74,35.80,42.02,48.84,56.76,67.26,83.71,90.62,95.05,98.02,100.00],


# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger 
# angles are rack.

"outTiltAngle" => [12.15,15.11,19.43,25.49,34.44,56.13,72.53,85.47,97.35,108.92,120.88,135.07,156.23,166.08,173.51,179.64,184.83],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [12.15,14.83,19.48,27.68,47.83,66.13,80.23,92.43,103.53,114.03,124.58,136.83,153.88,163.38,171.18,178.18,184.83],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-35.39,-31.04,-26.74,-22.49,-18.24,-13.99,-9.74,-5.44,-1.04,3.46,8.16,13.06,18.26,23.86,30.01,37.11,45.93],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [1523.4, 1510.6, 1501.6, 1496.2, 1494.4, 1496.3, 1501.8, 1511.0, 1524.0, 1541.0, 1562.4, 1588.5, 1619.8, 1657.3, 1702.3, 1758.2, 1831.5,
  1537.7, 1525.5, 1517.0, 1512.2, 1511.0, 1513.5, 1519.6, 1529.3, 1542.9, 1560.3, 1582.2, 1608.7, 1640.5, 1678.4, 1723.7, 1779.8, 1853.4,
  1556.2, 1544.7, 1536.9, 1532.7, 1532.2, 1535.3, 1542.0, 1552.4, 1566.5, 1584.5, 1607.0, 1633.9, 1666.1, 1704.5, 1750.1, 1806.6, 1880.4,
  1582.3, 1571.6, 1564.6, 1561.3, 1561.5, 1565.4, 1572.9, 1583.9, 1598.8, 1617.5, 1640.5, 1668.0, 1700.8, 1739.6, 1785.7, 1842.5, 1916.5,
  1639.4, 1630.2, 1624.6, 1622.7, 1624.4, 1629.6, 1638.3, 1650.6, 1666.6, 1686.3, 1710.4, 1738.8, 1772.4, 1812.0, 1858.8, 1916.1, 1990.6,
  1695.9, 1687.7, 1683.2, 1682.4, 1685.0, 1691.2, 1700.8, 1714.0, 1730.8, 1751.3, 1776.1, 1805.2, 1839.3, 1879.4, 1926.6, 1984.4, 2059.1,
  1747.1, 1739.7, 1736.0, 1735.8, 1739.2, 1746.1, 1756.3, 1770.0, 1787.4, 1808.4, 1833.7, 1863.2, 1897.8, 1938.2, 1985.7, 2043.7, 2118.5,
  1799.3, 1792.5, 1789.4, 1789.9, 1793.8, 1801.2, 1812.0, 1826.2, 1844.0, 1865.4, 1891.0, 1920.8, 1955.7, 1996.3, 2044.1, 2102.2, 2177.2,
  1854.9, 1848.7, 1846.1, 1847.0, 1851.5, 1859.3, 1870.5, 1885.0, 1903.1, 1924.9, 1950.7, 1980.9, 2015.9, 2056.8, 2104.7, 2162.9, 2238.0,
  1915.7, 1910.0, 1907.8, 1909.2, 1914.0, 1922.2, 1933.7, 1948.5, 1966.9, 1988.9, 2015.0, 2045.3, 2080.5, 2121.5, 2169.5, 2227.8, 2302.9,
  1985.4, 1980.0, 1978.3, 1980.0, 1985.1, 1993.5, 2005.3, 2020.3, 2038.9, 2061.0, 2087.3, 2117.7, 2153.0, 2194.0, 2242.1, 2300.5, 2375.6,
  2075.7, 2070.7, 2069.2, 2071.2, 2076.5, 2085.2, 2097.0, 2112.2, 2130.9, 2153.1, 2179.4, 2209.8, 2245.1, 2286.2, 2334.2, 2392.5, 2467.7,
  2208.4, 2203.5, 2202.1, 2204.1, 2209.5, 2218.1, 2229.9, 2245.0, 2263.6, 2285.7, 2311.8, 2342.0, 2377.2, 2418.0, 2465.9, 2524.1, 2599.1,
  2277.1, 2272.2, 2270.7, 2272.7, 2277.9, 2286.4, 2298.1, 2313.1, 2331.5, 2353.4, 2379.3, 2409.4, 2444.4, 2485.1, 2532.8, 2590.8, 2665.8,
  2326.1, 2321.0, 2319.5, 2321.3, 2326.4, 2334.8, 2346.4, 2361.2, 2379.5, 2401.2, 2427.0, 2456.9, 2491.7, 2532.3, 2579.8, 2637.8, 2712.6,
  2361.9, 2356.8, 2355.2, 2356.9, 2361.9, 2370.2, 2381.6, 2396.3, 2414.5, 2436.1, 2461.7, 2491.5, 2526.2, 2566.6, 2614.1, 2671.9, 2746.7,
  2387.8, 2382.6, 2380.9, 2382.5, 2387.4, 2395.6, 2407.0, 2421.5, 2439.6, 2461.1, 2486.6, 2516.3, 2550.9, 2591.3, 2638.6, 2696.4, 2771.1
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [12.15, 184.83],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [ -96.05, 76.63],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [12.15, 184.83],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1705.0,2390.0 ],

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
"KgPerLiftKpaAtMidExtension" => 1.291,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 3025.75,

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
"LiftCylExtPctAxis" => [0.0,13.619048,26.190476,40.285714,55.619048,68.095238,75.809524,81.238095,85.619048,89.142857,92.095238,94.571429,96.666667,98.476190,100.0],


# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00,5.55,10.51,14.89,18.98,22.63,26.13,29.34,32.41,35.33,38.25,41.46,45.26,50.22,59.27,67.74,75.62,83.94,93.58,100.00],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [39.745421, -12.643083, -29.007570, -11.544308, 36.823719, 80.524856, 85.409419, 60.593946, 15.096775, -42.108368, -109.448720, -187.114629, -277.435494, -385.691326, -514.098948,
  15.824416, -27.070313, -39.619291, -20.337524, 32.179992, 92.449712, 122.639932, 121.666934, 92.001618, 41.082228, -24.003575, -98.074888, -180.338818, -273.756322, -378.196823,
  1.196161, -36.306540, -47.216096, -28.230375, 23.813166, 90.868861, 138.161444, 160.891822, 156.470860, 124.187079, 68.649545, -2.210412, -82.636599, -171.865655, -267.776362, 
  -7.934662, -42.303653, -52.603314, -34.711944, 14.879420, 82.685288, 138.478672, 177.532348, 196.426115, 188.823547, 153.579030, 94.801946, 19.429624, -67.912633, -161.553420, 
  -14.132594, -46.487753, -56.633805, -40.112217, 6.250032, 71.692008, 130.371988, 178.894727, 215.113875, 230.780356, 221.021855, 184.221990, 123.588469, 43.827360, -46.771993, 
  -18.236733, -49.293323, -59.495392, -44.306550, -1.179361, 60.590575, 118.722061, 171.246530, 217.727424, 250.258200, 263.021535, 250.800031, 212.266862, 148.872823, 67.723971,
  -21.190880, -51.300488, -61.645798, -47.739796, -7.796077, 49.676100, 105.373535, 158.576826, 210.405419, 254.200055, 284.771204, 295.565362, 282.230964, 242.576785, 179.706192,
  -23.219188, -52.635886, -63.144703, -50.369582, -13.287718, 39.939625, 92.358849, 144.191337, 197.689536, 247.582902, 289.899997, 318.272395, 327.237644, 312.474423, 273.010671,
  -24.657720, -53.517813, -64.185178, -52.423922, -17.957033, 31.161267, 79.913503, 129.223458, 182.112896, 234.584077, 283.963106, 324.764954, 351.631373, 359.597021, 344.833037,
  -25.648315, -54.040427, -64.845329, -53.977102, -21.860148, 23.419057, 68.445668, 114.651470, 165.525155, 218.121358, 270.901449, 319.473557, 359.198915, 385.459734, 392.983663,
  -26.322722, -54.283561, -65.202441, -55.149837, -25.227928, 16.363406, 57.612120, 100.326475, 148.244371, 199.281818, 252.838257, 305.619771, 353.959542, 394.111866, 420.409361,
  -26.749482, -54.256659, -65.265207, -56.017330, -28.322658, 9.443267, 46.618779, 85.305864, 129.321809, 177.315062, 229.458869, 283.521575, 336.922282, 387.078171, 428.674276, 
  -26.886150, -53.860396, -64.918232, -56.497108, -31.182833, 2.417392, 35.025973, 68.971031, 107.979029, 151.315223, 199.747156, 252.020169, 306.648060, 362.327660, 414.664341, 
  -26.549101, -52.794196, -63.813355, -56.278995, -33.688810, -4.934253, 22.248004, 50.348278, 82.796113, 119.357834, 161.174464, 207.827407, 258.830041, 314.095792, 370.563635,
  -24.670338, -49.367278, -59.989057, -53.569233, -34.982130, -13.439807, 5.592054, 24.685406, 46.548182, 71.336709, 100.207088, 133.373799, 171.139372, 214.328250, 261.611901,
  -21.617038, -44.442692, -54.279726, -48.438047, -32.788552, -16.483170, -3.241830, 9.453025, 23.658592, 39.618581, 58.218062, 79.758969, 104.643708, 133.693282, 166.352264,
  -17.676259, -38.173566, -46.868497, -41.317267, -28.085235, -15.812654, -6.755867, 1.452349, 10.343000, 20.153484, 31.492063, 44.601642, 59.794636, 77.657713, 97.953194, 
  -12.246695, -29.218717, -36.141116, -30.907999, -20.457829, -12.099495, -6.628273, -2.021358, 2.747731, 7.867945, 13.694296, 20.377415, 28.101208, 37.190640, 47.556099, 
   -4.119392, -13.611866, -17.135544, -13.432654, -8.104237, -4.758986, -2.913096, -1.509748, -0.147392, 1.257546, 2.817989, 4.582808, 6.607001, 8.981095, 11.687310,
  0.150775, 5.268317, 6.927924, 4.452953, 2.308096, 1.297547, 0.814839, 0.474073, 0.157712, -0.159643, -0.506333, -0.894618, -1.337513, -1.855458, -2.445148
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

# This will define what UI configurable features are Enabled or Disabled.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" =>  ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_LWL.json",

}

MachineType = {
  "InternalMsn" => "CAT88201",
  "Make" => "CAT",
  "Model" => "988K",
  "ModelDetail" => "988K",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0001,
}
