##

## CAT 994H - Super High Lift
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
"outLiftAngle" => [-31.45, 50.93],

# Lift angle axis of the lift cylinder length table, in degrees.
"inLiftAngle" => [-31.45,-20.79,-13.88,-7.89,-2.40,2.79,7.73,12.48,17.07,21.59,25.98,30.30,34.54,38.75,42.87,46.96,50.93],


# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [2570.0,2851.0,3029.0,3179.0,3312.0,3433.0,3544.0,3646.0,3740.0,3828.0,3909.0,3984.0,4053.0,4117.0,4175.0,4228.0,4275.0],

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-31.45, 50.93],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [2570, 4275.0],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 

"inTiltDc" => [0.00,2.56,5.40,8.85,13.81,24.85,32.17,38.98,45.95,53.52,62.50,78.42,86.55,91.64,95.30,98.00,100.00],


# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger 
# angles are rack.

"outTiltAngle" => [2.79,5.63,9.7,15.6,25.17,47.55,61.75,74.11,85.89,97.79,110.94,133.03,144.7,152.73,159.23,164.77,169.60],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [2.79,7.30,19.25,34.10,46.95,58.65,69.55,79.85,89.80,99.70,110.00,122.30,139.00,148.55,156.25,163.15,169.60],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-31.45,-26.80,-22.25,-17.75,-13.25,-8.80,-4.30,0.20,4.80,9.50,14.30,19.30,24.55,30.15,36.20,43.00,50.93],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [2790.0,2763.8,2743.8,2729.9,2722.0,2720.1,2724.3,2734.4,2750.9,2773.9,2803.4,2840.4,2885.3,2939.4,3004.2,3083.4,3182.0,
2804.3,2779.3,2760.6,2748.0,2741.3,2740.7,2746.1,2757.5,2775.1,2799.3,2830.0,2868.0,2913.9,2969.0,3034.6,3114.6,3213.8,
2840.7,2817.9,2801.4,2791.0,2786.6,2788.2,2795.7,2809.3,2829.1,2855.2,2887.8,2927.6,2975.3,3032.0,3099.0,3180.3,3280.4,
2892.6,2871.9,2857.7,2849.4,2847.2,2851.0,2860.7,2876.3,2898.0,2926.1,2960.5,3002.0,3051.3,3109.4,3177.7,3260.1,3361.2,
2946.9,2928.0,2915.5,2909.0,2908.5,2913.9,2925.2,2942.4,2965.7,2995.2,3030.9,3073.7,3124.1,3183.3,3252.6,3335.8,3437.5,
3005.9,2988.5,2977.5,2972.5,2973.5,2980.3,2993.0,3011.5,3036.0,3066.7,3103.6,3147.4,3198.7,3258.8,3328.8,3412.6,3514.8,
3070.5,3054.5,3044.8,3041.1,3043.4,3051.4,3065.4,3084.9,3110.6,3142.3,3180.1,3224.7,3276.9,3337.7,3408.3,3492.7,3595.3,
3141.3,3126.5,3118.0,3115.5,3118.9,3128.0,3143.0,3163.5,3190.1,3222.7,3261.3,3306.7,3359.5,3420.9,3492.1,3576.8,3679.7,
3219.5,3205.8,3198.3,3196.8,3201.2,3211.3,3227.2,3248.6,3276.0,3309.3,3348.6,3394.6,3448.0,3509.9,3581.5,3666.7,3769.8,
3307.3,3294.6,3288.1,3287.5,3292.8,3303.7,3320.4,3342.6,3370.6,3404.6,3444.4,3491.0,3544.9,3607.1,3679.1,3764.5,3867.9,
3408.9,3397.1,3391.4,3391.7,3397.8,3409.4,3426.8,3449.6,3478.2,3512.7,3553.0,3600.0,3654.3,3716.9,3789.1,3874.8,3978.3,
3541.6,3530.6,3525.8,3526.8,3533.5,3545.8,3563.8,3587.1,3616.2,3651.1,3691.9,3739.2,3793.7,3856.5,3929.0,4014.8,4118.4,
3729.8,3719.5,3715.3,3716.8,3724.1,3736.8,3755.2,3778.8,3808.2,3843.4,3884.2,3931.7,3986.3,4049.2,4121.7,4207.5,4311.2,
3832.1,3822.0,3817.9,3819.5,3826.9,3839.7,3858.0,3881.7,3911.0,3946.2,3987.0,4034.4,4088.9,4151.8,4224.2,4309.9,4413.5,
3906.3,3896.2,3892.2,3893.8,3901.2,3913.9,3932.2,3955.8,3985.1,4020.1,4060.9,4108.2,4162.6,4225.4,4297.7,4383.3,4486.8,
3963.7,3953.6,3949.5,3951.1,3958.4,3971.1,3989.3,4012.8,4042.0,4077.0,4117.6,4164.8,4219.1,4281.8,4354.0,4439.6,4543.0,
4007.7,3997.6,3993.4,3995.0,4002.2,4014.8,4033.0,4056.4,4085.5,4120.3,4160.9,4208.0,4262.2,4324.8,4396.9,4482.4,4585.8],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [2.79, 169.60],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [ -95.93, 70.88],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [2.79, 169.60],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [2960.0, 4000.0],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 343,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 222,

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
"KgPerLiftKpaAtMidExtension" => 3.2232,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 4713.0,

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
"LiftCylExtPctAxis" => [0.00,17.13,39.18,62.11,76.25,81.47,84.75,87.45,89.85,92.02,93.96,95.72,97.30,98.71,100.00],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00,2.88,5.58,8.17,10.67,13.08,15.38,17.60,19.71,21.83,23.85,26.06,28.65,31.92,36.73,47.60,59.04,70.48,84.33,100.00],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [-31.8567,-48.6872,-28.2899,26.0708,69.2835,62.3702,26.0711,-37.6658,-126.9667,-260.7530,-878.1918,-1320.4933,-1691.6418,-2011.4904,-2302.6082,
-37.1434,-50.5175,-29.9775,23.2668,73.6787,83.0898,69.2684,29.7318,-38.8144,-132.7304,-262.9833,-627.2257,-978.0123,-1299.5455,-1595.3542,
-40.6433,-51.7180,-31.3727,20.1905,73.6406,92.2891,93.3855,75.4641,30.5410,-43.9062,-141.3783,-273.6167,-570.7138,-830.9587,-1075.6715,
-43.0503,-52.5067,-32.5487,17.0285,71.1958,95.0015,105.2862,102.8389,80.4667,29.7268,-49.1736,-151.5071,-284.5487,-536.8534,-751.4053,
-44.6844,-52.9862,-33.5232,13.9413,67.4289,93.8820,109.5363,116.8995,111.2270,83.9374,28.2490,-56.1055,-161.8721,-293.3481,-524.5214,
-45.7622,-53.2309,-34.3155,11.0213,63.0071,90.5629,109.1959,122.4514,127.6625,118.3657,86.4273,24.9559,-63.6725,-170.7450,-304.6864,
-46.4343,-53.2956,-34.9451,8.3178,58.3435,86.0492,106.1750,122.8230,134.7362,137.5137,124.4565,87.1607,20.6293,-70.3694,-181.6032,
-46.8076,-53.2220,-35.4313,5.8527,53.6924,80.9658,101.6573,120.1268,136.0167,146.4216,146.4224,129.0515,86.5930,16.5105,-79.1937,
-46.9594,-53.0421,-35.7921,3.6303,49.2072,75.7024,96.3820,115.6835,133.8150,148.8751,157.3413,154.1912,132.3056,85.5937,10.1376,
-46.9429,-52.7667,-36.0544,1.5533,44.7772,70.2508,90.5392,110.0477,129.3518,147.2423,161.2142,167.9003,161.7939,136.6158,85.3894,
-46.7936,-52.4235,-36.2160,-0.2865,40.6600,65.0077,84.6758,103.9696,123.6885,143.0805,160.3260,173.2239,177.7455,168.7341,139.4192,
-46.5021,-51.9658,-36.2972,-2.1372,36.3249,59.3357,78.1369,96.8739,116.4937,136.5885,155.8624,172.9994,185.2112,188.7239,178.4612,
-46.0143,-51.3294,-36.2700,-4.0889,31.5164,52.8882,70.5156,88.3150,107.3184,127.3830,147.6258,167.4001,184.9027,197.6121,202.4836,
-45.2120,-50.3903,-36.0572,-6.2113,25.9460,45.2355,61.2656,77.6315,95.3873,114.5881,134.6793,155.5028,176.0034,194.6478,210.1181,
-43.7231,-48.7609,-35.4066,-8.6790,18.7979,35.1388,48.7857,62.8472,78.3148,95.3796,113.7557,133.6194,154.4780,175.5387,196.7014,
-39.3459,-44.1423,-32.6209,-11.6924,7.1040,17.7924,26.6700,35.8547,46.0644,57.5226,70.1674,84.3047,99.8515,116.5703,134.9387,
-33.5737,-38.0214,-27.9892,-11.7519,0.4483,6.8631,12.0757,17.4196,23.3410,29.9949,37.3752,45.6979,54.9624,65.0839,76.4285,
-26.6811,-30.5560,-21.8247,-9.4976,-2.0068,1.5290,4.3044,7.0996,10.1642,13.5873,17.3744,21.6458,26.4112,31.6381,37.5294,
-16.3626,-19.0833,-12.3815,-4.8725,-1.5629,-0.2442,0.7358,1.6954,2.7296,3.8729,5.1307,6.5458,8.1240,9.8573,11.8153,
0.9881,1.2209,0.5092,0.1079,0.0168,-0.0126,-0.0340,-0.0550,-0.0780,-0.1038,-0.1326,-0.1656,-0.2028,-0.2442,-0.2915],

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
  "InternalMsn" => "CAT94008",
  "Make" => "CAT",
  "Model" => "994H",
  "ModelDetail" => "994H",
  "Linkage" => "Super High Lift",
  "LinkageConfigurationNumber" => 1255
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0001,
}
