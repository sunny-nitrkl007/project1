##

## CAT 993 - High Lift
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.000000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-37.29, 44.56],

# Lift angle axis of the lift cylinder length table, in degrees.
"inLiftAngle" => [-37.29, -28.42, -21.63, -15.61, -10.04, -4.81, 0.21, 5.09, 9.82, 14.40, 18.93, 23.33, 27.67, 31.94, 36.21, 40.39, 44.56],


# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [2527.0, 2764.0, 2941.0, 3093.0, 3229.0, 3352.0, 3465.0, 3570.0, 3667.0, 3756.0, 3839.0, 3915.0, 3985.0, 4049.0, 4108.0, 4161.0, 4209.0],

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-37.29, 44.56],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [2527.0, 4209.0],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 

"inTiltDc" => [0.00, 3.11, 6.07, 9.14, 12.86, 20.73, 26.44, 31.63, 37.04, 43.02, 49.95, 58.45, 71.21, 86.99, 93.42, 97.45, 100.00],


# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger 
# angles are rack.

"outTiltAngle" => [2.68, 5.59, 10.02, 16.38, 25.98, 49.08, 64.96, 77.7, 89.25, 100.24, 111.12, 122.59, 137.57, 155.62, 164.31, 171.12, 176.77],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [2.68, 5.22, 10.02, 19.22, 43.17, 62.47, 77.12, 89.37, 100.17, 110.07, 119.62, 129.87, 145.62, 155.52, 163.22, 170.12, 176.77],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-37.29, -32.99, -28.79, -24.64, -20.49, -16.34, -12.14, -7.89, -3.54, 0.96, 5.61, 10.51, 15.71, 21.36, 27.61, 34.91, 44.56],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [2235.1, 2216.7, 2204.3, 2197.5, 2196.2, 2200.5, 2210.5, 2226.1, 2247.8, 2275.8, 2310.5, 2352.8, 2403.4, 2464.2, 2537.3, 2628.8, 2756.5,
2254.3, 2236.8, 2225.2, 2219.3, 2218.8, 2224.0, 2234.7, 2251.1, 2273.5, 2302.3, 2337.7, 2380.6, 2431.8, 2493.1, 2566.7, 2658.6, 2786.5,
2279.4, 2262.9, 2252.3, 2247.3, 2247.9, 2253.9, 2265.6, 2282.9, 2306.1, 2335.7, 2371.8, 2415.4, 2467.3, 2529.2, 2603.3, 2695.6, 2823.9,
2315.4, 2300.1, 2290.8, 2287.0, 2288.7, 2295.9, 2308.6, 2327.0, 2351.2, 2381.8, 2418.8, 2463.2, 2515.8, 2578.4, 2653.1, 2745.9, 2874.5,
2396.9, 2383.8, 2376.6, 2374.9, 2378.6, 2387.8, 2402.4, 2422.6, 2448.5, 2480.6, 2519.1, 2564.9, 2618.7, 2682.4, 2758.1, 2851.7, 2980.8,
2471.2, 2459.7, 2453.9, 2453.6, 2458.7, 2469.1, 2485.0, 2506.3, 2533.4, 2566.5, 2605.9, 2652.6, 2707.1, 2771.5, 2847.8, 2941.8, 3071.3,
2541.0, 2530.5, 2525.8, 2526.5, 2532.6, 2544.0, 2560.7, 2582.9, 2610.7, 2644.5, 2684.6, 2731.8, 2786.9, 2851.7, 2928.3, 3022.7, 3152.4,
2612.9, 2603.3, 2599.5, 2601.1, 2608.0, 2620.1, 2637.5, 2660.3, 2688.7, 2723.1, 2763.6, 2811.3, 2866.7, 2931.9, 3008.8, 3103.4, 3233.2,
2690.2, 2681.5, 2678.4, 2680.7, 2688.2, 2700.9, 2718.9, 2742.2, 2771.0, 2805.8, 2846.7, 2894.7, 2950.4, 3015.8, 3092.9, 3187.7, 3317.6,
2775.4, 2767.3, 2764.8, 2767.7, 2775.7, 2788.9, 2807.3, 2831.0, 2860.1, 2895.2, 2936.4, 2984.6, 3040.5, 3106.1, 3183.3, 3278.1, 3408.1,
2872.3, 2864.7, 2862.6, 2865.9, 2874.3, 2887.8, 2906.5, 2930.4, 2959.8, 2995.1, 3036.4, 3084.7, 3140.7, 3206.3, 3283.5, 3378.3, 3508.3,
2991.8, 2984.6, 2982.9, 2986.4, 2995.0, 3008.7, 3027.5, 3051.5, 3081.0, 3116.2, 3157.5, 3205.7, 3261.7, 3327.2, 3404.3, 3499.1, 3629.0,
3194.5, 3187.3, 3185.5, 3189.0, 3197.4, 3210.9, 3229.5, 3253.1, 3282.2, 3317.0, 3357.9, 3405.7, 3461.1, 3526.2, 3602.9, 3697.3, 3827.0,
3316.9, 3309.4, 3307.4, 3310.5, 3318.6, 3331.6, 3349.8, 3373.0, 3401.6, 3436.0, 3476.3, 3523.6, 3578.7, 3643.3, 3719.6, 3813.6, 3943.1,
3399.2, 3391.5, 3389.1, 3391.9, 3399.6, 3412.3, 3430.1, 3452.9, 3481.1, 3515.1, 3555.0, 3601.9, 3656.5, 3720.8, 3796.8, 3890.5, 4019.7,
3458.9, 3450.9, 3448.2, 3450.7, 3458.1, 3470.5, 3487.9, 3510.4, 3538.2, 3571.9, 3611.5, 3658.1, 3712.4, 3776.3, 3852.0, 3945.6, 4074.6,
3501.7, 3493.5, 3490.6, 3492.8, 3500.0, 3512.1, 3529.3, 3551.5, 3579.1, 3612.5, 3651.8, 3698.1, 3752.2, 3815.9, 3891.4, 3984.7, 4113.6],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [3.23, 177.32],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [ -94.01, 80.08],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [3.23, 177.32],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [2455.0, 3495.0 ],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 266.7,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 177.8,

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
"KgPerLiftKpaAtMidExtension" => 2.6047,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 3832.32,

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
"LiftCylExtPctAxis" => [0,16.409037,34.661118,53.032105,64.447087,71.581451,77.170036,81.747919,85.552913,88.822830,91.676576,94.173603,96.373365,98.335315,100],


# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0,5.769231,10.769231,15.384615,19.615385,23.557692,27.307692,30.865385,34.230769,37.403846,40.480769,43.365385,46.346154,49.807692,54.615385,62.980769,70.673077,78.653846,88.365385,100],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
-18.428689,-33.632450,-7.099555,49.427251,70.429536,49.450154,8.317292,-38.183118,-87.325937,-143.225558,-211.877432,-304.235672,-453.761490,-902.686812,-1245.084424,
-32.226407,-40.367343,-14.215408,47.236745,94.585014,103.556690,76.504048,27.169599,-27.270567,-82.597823,-141.469998,-208.373109,-290.593675,-404.120971,-583.609311,
-37.489133,-43.747664,-20.384295,37.687648,94.971360,128.802675,131.822181,99.285207,44.090866,-17.901682-80.016496,-143.203336,-211.810243,-292.522023,-389.471121,
-39.367767,-45.534406,-25.343094,26.723454,84.023318,130.138456,159.290272,157.664360,121.283122,60.710970,-8.299856,-76.874536,-145.151358,-217.586191,-295.015964,
-39.676231,-46.371113,-29.049853,16.831053,69.703644,118.518254,161.814947,186.968111,181.158738,140.733855,75.035279,0.100644,-74.687927,-149.056751,-222.165063,
-39.245615,-46.630281,-31.753855,8.542304,55.615359,102.153288,150.100704,191.164699,212.496044,202.788250,158.149413,87.995663,7.601403,-73.858238,-150.333960,
-38.437665,-46.508885,-33.688845,1.760410,42.960384,85.090023,132.091406,179.660840,218.388645,236.801878,223.478792,175.221211,100.997138,14.729251,-68.769479,
-37.438362,-46.122445,-34.999661,-3.629935,32.220791,69.374638,112.687676,160.602374,207.335946,244.507626,260.126467,243.359758,191.662180,112.865031,25.840760,
-36.351462,-45.551955,-35.815934,-7.828570,23.391285,55.770366,94.420334,139.419920,187.712815,	234.309181,269.946261,282.557635,262.303362,206.535133,127.903343,
-35.236551,-44.855906,-36.246849,-11.045404,16.268066,44.387887,78.333960,119.062371,165.288998,214.638636,261.107456,294.742868,304.107472,279.738926,223.354480,
-34.092370,-44.050730,-36.382161,-13.540214,10.422512,34.770292,64.263130,100.282711,142.629195,190.698374,241.225405,287.279364,319.122134,325.584660,299.752435,
-32.974519,-43.190027,-36.280194,-15.375712,5.819919,26.996204,52.595723,84.153978,122.066608,166.774207,216.905749,268.174240,313.535092,343.304617,346.701599,
-31.780437,-42.200882,-35.962913,-16.813318,1.873560,20.147797,42.098903,69.270528,102.381259,142.475151,189.471263,241.202144,293.354037,339.052492,367.107507,
-30.349213,-40.932287,-35.347580,-17.961911,-1.788792,13.568933,31.797529,54.345710,82.073624,116.316980,157.827801,206.061698,259.149611,313.443768,359.659145,
-28.285813,-38.965521,-34.093346,-18.751497,-5.462962,6.563919,20.507579,37.611088,58.713971,85.151667,118.079912,158.059713,205.172100,258.832837,313.239665,
-24.471766,-34.976433,-30.916688,-18.302812,-8.751768,-0.935866,7.621406,17.805576,30.233747,45.862760,65.674197,90.536547,121.411953,159.479452,202.777040,
-20.651317,-30.608267,-26.952870,-16.280396,-9.201701,-4.004508,1.305808,7.365021,14.592098,23.590942,34.993390,49.416449,67.624341,90.675421,117.907127,
-16.233674,-25.170242,-21.740883,-12.900909,-7.847273,-4.573655,-1.505979,1.800934,5.614299,10.275845,16.132306,23.528913,32.905481,44.891246,59.267547,
-9.860676,-16.610467,-13.532865,-7.382076,-4.558054,-3.013740,-1.731906,-0.461487,0.929798,2.581773,4.625995,7.191019,10.439665,14.605670,19.635843,
0.438143,1.049241,0.648283,	0.261607,0.152031,0.104939,	0.071117,0.040547,0.008710,-0.028245,-0.073641,-0.130636,-0.203137,-0.296689,-0.410449],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 24.5,

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
  "InternalMsn" => "CAT93201",
  "Make" => "CAT",
  "Model" => "993",
  "ModelDetail" => "993",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0001,
}
