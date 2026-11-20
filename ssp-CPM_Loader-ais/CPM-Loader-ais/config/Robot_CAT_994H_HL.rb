##

## CAT 994H - High Lift
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
"outLiftAngle" => [-36.43, 43.23],

# Lift angle axis of the lift cylinder length table, in degrees.
"inLiftAngle" => [-36.43,-26.13,-19.43,-13.62,-8.30,-3.29,1.48,6.09,10.53,14.89,19.13,23.32,27.43,31.50,35.46,39.37,43.23],


# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [2538.0,2819.0,2998.0,3149.0,3283.0,3405.0,3517.0,3621.0,3717.0,3807.0,3890.0,3968.0,4040.0,4107.0,4168.0,4224.0,4275.0],

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-36.43, 43.23],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [2538.0,4275.0],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 

"inTiltDc" => [0.00,7.66,15.60,21.78,27.92,34.40,41.53,49.75,60.20,78.08,86.04,91.08,94.52,96.87,98.43,99.42,100.00],


# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger 
# angles are rack.

"outTiltAngle" => [12.44,30.52,49.16,62.47,74.44,85.79,96.97,108.51,121.76,143.05,153.28,160.78,166.93,172.15,176.63,180.45,183.64],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [12.44,33.54,49.04,62.19,73.84,84.49,94.54,104.29,114.29,126.29,142.14,151.09,158.49,165.14,171.44,177.54,183.64],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-36.43,-32.18,-27.98,-23.83,-19.73,-15.58,-11.43,-7.23,-2.93,1.52,6.12,10.92,16.02,21.52,27.57,34.52,43.23],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [2297.4,2279.7,2267.5,2260.8,2259.5,2263.5,2272.9,2287.7,2308.3,2335.0,2368.0,2408.0,2455.9,2513.2,2581.8,2666.4,2778.4,
2384.1,2368.9,2359.2,2354.9,2355.9,2362.3,2373.9,2390.9,2413.5,2442.1,2477.0,2518.7,2568.2,2626.9,2696.7,2782.4,2895.2,
2458.0,2444.4,2436.2,2433.5,2436.0,2443.9,2456.8,2475.1,2499.0,2528.8,2564.8,2607.4,2657.8,2717.3,2787.9,2874.2,2987.5,
2531.9,2519.6,2512.7,2511.2,2514.9,2523.8,2537.9,2557.2,2582.0,2612.7,2649.5,2692.8,2743.9,2804.0,2875.1,2961.8,3075.4,
2608.8,2597.6,2591.8,2591.3,2595.9,2605.8,2620.7,2640.7,2666.3,2697.7,2735.1,2779.1,2830.7,2891.2,2962.7,3049.7,3163.5,
2690.7,2680.4,2675.4,2675.8,2681.2,2691.8,2707.4,2728.1,2754.3,2786.2,2824.1,2868.5,2920.5,2981.4,3053.2,3140.4,3254.4,
2779.7,2770.2,2766.0,2767.0,2773.1,2784.3,2800.5,2821.7,2848.3,2880.7,2919.0,2963.7,3016.0,3077.1,3149.0,3236.4,3350.5,
2878.1,2869.2,2865.6,2867.2,2873.8,2885.5,2902.1,2923.7,2950.6,2983.2,3021.8,3066.7,3119.2,3180.4,3252.5,3340.0,3454.1,
2991.3,2982.9,2979.8,2981.8,2988.8,3000.8,3017.6,3039.5,3066.6,3099.4,3138.1,3183.1,3235.6,3296.9,3369.0,3456.5,3570.6,
3141.0,3133.0,3130.2,3132.4,3139.6,3151.7,3168.7,3190.5,3217.6,3250.4,3289.0,3333.9,3386.3,3447.5,3519.4,3606.8,3720.8,
3347.2,3339.1,3336.2,3338.3,3345.2,3357.1,3373.8,3395.3,3422.0,3454.3,3492.5,3536.9,3588.8,3649.5,3721.0,3808.0,3921.7,
3456.0,3447.7,3444.5,3446.4,3453.0,3464.6,3480.9,3502.0,3528.4,3560.3,3598.1,3642.2,3693.7,3754.0,3825.2,3911.8,4025.3,
3535.2,3526.6,3523.2,3524.8,3531.2,3542.4,3558.4,3579.2,3605.2,3636.9,3674.3,3718.0,3769.2,3829.2,3900.1,3986.4,4099.7,
3594.9,3586.1,3582.4,3583.8,3589.9,3600.8,3616.5,3637.1,3662.8,3694.2,3731.3,3774.7,3825.6,3885.4,3956.0,4042.1,4155.2,
3639.5,3630.6,3626.7,3627.8,3633.7,3644.5,3659.9,3680.3,3705.8,3736.9,3773.7,3816.9,3867.6,3927.1,3997.5,4083.5,4196.5,
3670.8,3661.7,3657.7,3658.7,3664.4,3675.0,3690.3,3710.5,3735.8,3766.7,3803.4,3846.4,3896.9,3956.3,4026.6,4112.4,4225.2,
3690.1,3680.9,3676.8,3677.7,3683.3,3693.8,3709.0,3729.0,3754.2,3785.0,3821.6,3864.5,3914.9,3974.2,4044.3,4130.1,4242.9],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [12.44, 183.64],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [ -88.22, 82.98],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [12.44, 183.64],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [2560.0, 3700.0],

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
"LoaderBktPayldTrgtWt" => 31.8,

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
"KgPerLiftKpaAtMidExtension" => 3.4577,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 3931.6,

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
"LiftCylExtPctAxis" => [0.00,13.36,22.45,33.97,42.66,58.78,70.81,79.56,84.40,87.91,90.96,93.61,95.97,98.10,100.00],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00,3.77,7.19,10.44,13.51,16.40,19.21,22.11,25.44,29.65,36.40,47.11,56.14,65.44,76.40,89.91,96.70,98.54,99.32,100.00],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [-17.2830,-34.1050,-34.8676,-24.7930,-13.7808,14.0362,42.3333,62.1554,64.8940,55.9852,34.9421,3.8371,-33.1156,-72.1505,-111.5405,
-20.4783,-36.0103,-36.5603,-26.7036,-16.1294,10.6496,39.6523,64.7855,75.5663,76.7515,67.5453,46.4016,13.9932,-25.8515,-67.8291,
-22.5222,-37.2572,-37.7407,-28.1837,-18.0868,7.3564,35.8346,63.3719,78.9647,87.0934,87.6784,78.1111,56.3027,22.2737,-19.6169,
-23.8942,-38.1005,-38.5910,-29.3646,-19.7501,4.2396,31.5350,59.7282,77.9861,90.5857,98.2250,98.4205,88.4978,65.9028,30.9605,
-24.7975,-38.6468,-39.1827,-30.2851,-21.1303,1.4147,27.2049,54.9603,74.3860,89.5640,101.7848,108.9922,108.8999,98.4776,75.4372,
-25.3696,-38.9727,-39.5714,-30.9837,-22.2521,-1.0734,23.1012,49.7900,69.4060,85.8350,100.7626,112.5659,119.5333,119.0588,108.1992,
-25.7139,-39.1374,-39.8066,-31.5106,-23.1721,-3.2870,19.2366,44.4920,63.6794,80.4825,96.8301,111.4783,123.2445,130.1375,129.4508,
-25.8900,-39.1709,-39.9160,-31.9059,-23.9504,-5.3432,15.4625,38.9921,57.3000,73.8532,90.7105,106.9573,121.8642,134.0378,141.2820,
-25.9066,-39.0589,-39.8893,-32.1850,-24.6384,-7.4135,11.4606,32.8539,49.8037,65.5218,82.0997,98.9228,115.6580,131.4689,144.7460,
-25.6949,-38.7160,-39.6437,-32.2853,-25.2042,-9.5721,7.0061,25.6729,40.6462,54.8176,70.1943,86.4340,103.5374,121.1646,138.2979,
-24.9297,-37.7639,-38.8102,-31.9099,-25.4599,-12.0187,1.3233,15.9239,27.6620,38.9454,51.4904,65.2045,80.3432,96.9922,114.7312,
-22.9122,-35.4008,-36.5215,-30.1228,-24.4232,-13.6425,-4.2588,5.2067,12.6082,19.7121,27.6916,36.5889,46.7002,58.2693,71.2534,
-20.5920,-32.6684,-33.7410,-27.5967,-22.3599,-13.2549,-6.2872,0.0857,4.8390,9.3197,14.3186,19.8935,26.2651,33.6324,42.0271,
-17.6402,-29.1168,-30.0379,-24.0537,-19.2146,-11.5323,-6.4483,-2.3430,0.5134,3.1219,5.9820,9.1424,12.7424,16.9093,21.6790,
-13.2803,-23.6878,-24.2983,-18.4901,-14.1738,-8.1481,-4.8674,-2.6414,-1.2503,-0.0457,1.2340,2.6208,4.1833,5.9824,8.0398,
-5.7773,-13.4801,-13.4943,-8.5590,-5.6700,-2.6862,-1.5550,-0.9645,-0.6481,-0.3933,-0.1334,0.1421,0.4494,0.8022,1.2065,
-0.5615,-3.3991,-3.1719,-1.2699,-0.6474,-0.2455,-0.1391,-0.0901,-0.0642,-0.0428,-0.0205,0.0039,0.0319,0.0648,0.1032,
-0.3150,0.0916,2.6630,0.5626,0.2600,0.1013,0.0610,0.0413,0.0300,0.0201,0.0092,-0.0030,-0.0174,-0.0346,-0.0550,
-5.0620,1.6038,5.1392,0.3412,0.3172,0.1591,0.1048,0.0739,0.0543,0.0362,0.0156,-0.0081,-0.0364,-0.0707,-0.1115,
-8.7860,2.8985,7.2564,-4.8865,-0.0150,0.1477,0.1172,0.0881,0.0657,0.0434,0.0169,-0.0146,-0.0527,-0.0994,-0.1555],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 31.8,

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
  "InternalMsn" => "CAT94001",
  "Make" => "CAT",
  "Model" => "994H",
  "ModelDetail" => "994H",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0001,
}
