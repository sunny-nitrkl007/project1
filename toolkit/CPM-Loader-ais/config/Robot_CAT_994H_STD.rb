##

## CAT 994H - Std Lift
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
"outLiftAngle" => [-39.7, 44.59],

# Lift angle axis of the lift cylinder length table, in degrees.
"inLiftAngle" => [-39.70,-26.40,-18.66,-12.45,-6.94,-1.84,3.02,7.63,12.08,16.41,20.63,24.77,28.85,32.86,36.78,40.69,44.59],


# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [2460.0,2780.0,2964.0,3108.0,3232.0,3343.0,3445.0,3538.0,3624.0,3704.0,3778.0,3847.0,3911.0,3970.0,4024.0,4074.0,4120.0],

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-39.7, 44.59],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [2460.0,4120],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 

"inTiltDc" => [0.00,3.31,7.21,14.94,22.62,28.65,34.74,41.33,48.82,57.99,75.13,85.48,91.21,94.97,97.45,99.04,100.00],


# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger 
# angles are rack.

"outTiltAngle" => [11.07,16.66,24.84,43.59,62.09,75.20,86.99,98.24,109.50,121.67,142.09,154.81,163.00,169.55,175.04,179.70,183.61],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [11.07,18.06,33.01,53.56,68.06,80.36,91.36,101.51,111.31,121.41,134.66,148.71,157.16,164.36,170.96,177.31,183.61],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-39.70,-35.40,-31.20,-27.05,-22.90,-18.75,-14.60,-10.35,-6.00,-1.50,3.15,8.10,13.40,19.20,25.70,33.50,44.59],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [1834.2,1814.1,1800.1,1791.9,1789.5,1792.8,1801.8,1816.8,1838.0,1865.9,1900.4,1943.1,1994.7,2057.3,2133.5,2231.2,2376.8,
1869.4,1850.9,1838.5,1831.8,1830.9,1835.6,1846.0,1862.4,1884.9,1913.9,1949.6,1993.3,2045.8,2109.2,2186.1,2284.5,2430.5,
1936.1,1919.9,1909.8,1905.4,1906.6,1913.5,1925.9,1944.2,1968.6,1999.3,2036.5,2081.6,2135.5,2200.0,2277.8,2377.0,2523.4,
2032.3,2018.7,2011.0,2008.9,2012.5,2021.6,2036.1,2056.3,2082.4,2114.8,2153.5,2200.0,2255.1,2320.6,2399.4,2499.2,2646.1,
2112.6,2100.5,2094.4,2093.8,2098.7,2109.1,2124.8,2146.2,2173.3,2206.6,2246.2,2293.4,2349.2,2415.3,2494.5,2594.7,2741.8,
2193.4,2182.6,2177.6,2178.1,2184.1,2195.5,2212.1,2234.3,2262.2,2296.2,2336.3,2384.1,2440.3,2506.9,2586.4,2686.8,2834.0,
2278.7,2268.9,2264.9,2266.3,2273.2,2285.3,2302.6,2325.4,2353.9,2388.3,2428.9,2477.1,2533.6,2600.4,2680.1,2780.7,2928.0,
2370.6,2361.7,2358.4,2360.6,2368.0,2380.8,2398.6,2421.9,2450.7,2485.5,2526.4,2574.8,2631.5,2698.4,2778.3,2878.9,3026.2,
2472.9,2464.6,2462.0,2464.7,2472.6,2485.8,2503.9,2527.5,2556.6,2591.6,2632.6,2681.1,2737.8,2804.8,2884.7,2985.3,3132.6,
2592.4,2584.6,2582.4,2585.4,2593.6,2607.0,2625.3,2649.0,2678.2,2713.2,2754.2,2802.6,2859.3,2926.1,3005.9,3106.4,3253.7,
2766.2,2758.6,2756.5,2759.7,2767.9,2781.2,2799.4,2822.8,2851.7,2886.5,2927.1,2975.2,3031.5,3098.0,3177.4,3277.6,3424.7,
2954.4,2946.5,2944.1,2946.8,2954.6,2967.4,2985.0,3007.9,3036.1,3070.2,3110.1,3157.5,3213.1,3278.9,3357.7,3457.4,3604.2,
3057.1,3048.9,3046.1,3048.4,3055.8,3068.1,3085.2,3107.6,3135.4,3168.9,3208.3,3255.2,3310.3,3375.6,3454.0,3553.3,3699.9,
3131.9,3123.4,3120.3,3122.3,3129.2,3141.2,3157.9,3179.9,3207.2,3240.3,3279.3,3325.7,3380.4,3445.3,3523.3,3622.3,3768.7,
3187.3,3178.5,3175.1,3176.8,3183.4,3195.0,3211.4,3233.0,3260.0,3292.7,3331.4,3377.5,3431.8,3496.4,3574.1,3672.9,3819.1,
3227.1,3218.1,3214.5,3215.9,3222.3,3233.6,3249.8,3271.1,3297.8,3330.3,3368.7,3414.5,3468.6,3533.0,3610.4,3709.0,3855.0,
3253.0,3243.8,3240.0,3241.3,3247.5,3258.7,3274.6,3295.8,3322.3,3354.6,3392.8,3438.4,3492.4,3556.6,3633.9,3732.3,3878.3],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [11.07, 183.61],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [ -89.59, 82.95],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [11.07, 183.61],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [2130.0, 3270.0],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 318,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 203,

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
"LoaderBktPayldTrgtWt" => 34.5,

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
"KgPerLiftKpaAtMidExtension" => 3.4967,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 3512.7,

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
"LiftCylExtPctAxis" => [0.00,12.41,24.52,39.88,56.02,68.31,75.12,80.00,84.10,87.65,90.78,93.49,95.90,98.07,100.00],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00,4.60,8.84,12.80,16.48,19.98,23.30,26.43,29.47,32.41,35.45,38.77,42.73,48.34,57.46,65.47,73.30,81.95,92.54,100.00],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [-17.5488,-29.9416,-27.7136,-8.6386,23.6382,49.9026,54.7356,45.6462,25.5524,-2.2271,-34.3527,-68.0352,-103.7469,-142.8025,-186.4185,
-21.7704,-32.4037,-30.0544,-11.8467,20.0857,51.4878,65.3845,66.4719,55.5402,33.4694,3.1927,-30.8056,-66.9507,-105.1443,-145.5549,
-24.2050,-33.9201,-31.7627,-14.6964,15.7377,48.8593,68.4188,77.8399,76.9380,64.2065,40.1253,8.4324,-27.8469,-66.7685,-107.0591,
-25.6068,-34.8430,-33.0020,-17.1238,11.3307,44.0887,66.4853,81.5283,89.0372,86.4053,71.8617,46.6221,13.1523,-25.6128,-66.6955,
-26.3641,-35.3610,-33.8678,-19.1083,7.2701,38.5392,61.7908,79.9742,93.3357,99.2141,94.7760,78.8714,52.0924,16.5586,-24.0430,
-26.7201,-35.6037,-34.4532,-20.7204,3.6319,32.8622,55.7451,75.2736,92.1941,104.3009,108.6600,102.7515,85.4200,56.9006,19.9041,
-26.8059,-35.6445,-34.8108,-21.9940,0.4783,27.4802,49.2912,68.9471,87.6104,103.6769,114.6217,117.4804,110.1610,91.2077,61.3731,
-26.7093,-35.5370,-34.9852,-22.9715,-2.1930,22.6028,42.9974,62.0372,81.1737,99.3652,114.6625,124.2159,125.7317,116.8374,96.4755,
-26.4812,-35.3129,-35.0132,-23.7169,-4.4820,18.1796,36.9919,54.9759,73.7595,92.7693,110.6330,124.8776,133.4484,133.7567,123.6054,
-26.1548,-34.9946,-34.9161,-24.2560,-6.4121,14.2480,31.4433,48.1401,66.0485,84.9536,103.9788,121.1102,134.7266,142.4755,141.7209,
-25.7261,-34.5714,-34.6958,-24.6317,-8.1093,10.5967,26.1215,41.3503,58.0049,76.1407,95.2941,113.9199,130.8963,144.3476,151.7024,
-25.1667,-34.0086,-34.3246,-24.8444,-9.6340,7.0939,20.8587,34.4370,49.5015,66.3028,84.7084,103.6188,122.4073,139.7856,153.5838,
-24.3894,-33.2084,-33.7127,-24.8458,-11.0348,3.5572,15.3654,27.0212,40.0840,54.9323,71.6869,89.6606,108.6795,128.0757,146.3004,
-23.1093,-31.8498,-32.5491,-24.4134,-12.3061,-0.3244,9.0446,18.2173,28.5438,40.4554,54.2393,69.5848,86.6920,105.4863,125.1855,
-20.6374,-29.1114,-29.9624,-22.7384,-12.8331,-4.1643,2.1032,8.0477,14.6714,22.3423,31.3650,41.6955,53.6887,67.6248,83.3861,
-18.0710,-26.1401,-26.9764,-20.3664,-12.0054,-5.5201,-1.2303,2.6628,6.9020,11.7622,17.4760,24.0659,31.8246,41.0308,51.7426,
-15.1637,-22.6400,-23.3457,-17.2727,-10.2560,-5.4669,-2.6074,-0.1549,2.4278,5.3323,8.7159,12.6117,17.2165,22.7279,29.2247,
-11.3588,-17.8462,-18.2912,-12.9168,-7.4447,-4.2559,-2.5823,-1.2525,0.0816,1.5369,3.2030,5.1058,7.3510,10.0458,13.2430,
-5.4248,-9.6926,-9.7108,-6.0185,-3.1072,-1.7900,-1.2135,-0.8021,-0.4173,-0.0161,0.4315,0.9362,1.5292,2.2418,3.0911,
0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000,0.0000],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 34.5,

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
  "InternalMsn" => "CAT94000",
  "Make" => "CAT",
  "Model" => "994H",
  "ModelDetail" => "994H",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0001,
}
