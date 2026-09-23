##

## CAT 994H - Extended High Lift
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
"outLiftAngle" => [-31.16, 49.54],

# Lift angle axis of the lift cylinder length table, in degrees.
"inLiftAngle" => [-31.16,-22.33,-15.61,-9.69,-4.22,0.95,5.89,10.68,15.33,19.86,24.28,28.63,32.91,37.11,41.29,45.46,49.54],


# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [2655.00,2890.00,3064.00,3213.00,3346.00,3467.00,3578.00,3681.00,3776.00,3864.00,3945.00,4020.00,4089.00,4152.00,4210.00,4263.00,4310.00],

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-31.16, 49.54],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [2655.0, 4310.0],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 

"inTiltDc" => [0.00,3.14,7.12,15.93,23.86,30.32,36.74,43.52,51.05,60.07,76.47,85.20,90.49,94.19,96.83,98.71,100.00],


# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger 
# angles are rack.

"outTiltAngle" => [5.96,11.10,18.79,37.68,54.47,67.17,78.77,89.98,101.34,113.84,135.02,146.71,154.62,161.01,166.43,171.12,175.20],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [5.96,14.6,33.35,47.8,60.25,71.5,81.95,91.9,101.7,111.9,124.5,140.2,149.05,156.4,163,169.2,175.2],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-31.16,-26.81,-22.56,-18.31,-14.11,-9.86,-5.61,-1.31,3.09,7.59,12.29,17.19,22.34,27.89,33.99,40.94,49.54],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [2698.6,2681.0,2669.0,2662.5,2661.3,2665.5,2675.2,2690.3,2711.2,2738.1,2771.6,2812.0,2860.0,2917.4,2986.1,3070.2,3180.5,
2736.5,2720.3,2709.8,2704.7,2705.0,2710.6,2721.7,2738.1,2760.4,2788.4,2823.1,2864.7,2913.8,2972.1,3041.7,3126.5,3237.4,
2818.2,2804.5,2796.3,2793.6,2796.2,2804.1,2817.3,2835.9,2860.2,2890.2,2926.7,2970.0,3020.7,3080.4,3151.3,3237.3,3349.0,
2890.5,2878.3,2871.7,2870.5,2874.6,2884.0,2898.7,2918.6,2944.1,2975.3,3013.0,3057.4,3109.0,3169.7,3241.3,3328.0,3440.2,
2963.0,2952.2,2946.9,2946.9,2952.2,2962.7,2978.4,2999.4,3025.9,3058.1,3096.6,3141.8,3194.1,3255.4,3327.7,3414.8,3527.4,
3039.1,3029.3,3025.1,3026.1,3032.4,3043.9,3060.5,3082.4,3109.7,3142.6,3181.8,3227.6,3280.6,3342.4,3415.1,3502.6,3615.4,
3120.4,3111.5,3108.2,3110.2,3117.3,3129.6,3147.0,3169.5,3197.5,3231.0,3270.8,3317.1,3370.5,3432.8,3505.8,3593.6,3706.6,
3208.5,3200.5,3198.0,3200.7,3208.5,3221.5,3239.5,3262.6,3291.2,3325.1,3365.4,3412.2,3465.9,3528.5,3601.8,3689.8,3803.0,
3306.4,3299.1,3297.2,3300.5,3308.9,3322.5,3341.0,3364.6,3393.5,3427.9,3468.5,3515.6,3569.6,3632.4,3705.9,3794.0,3907.3,
3419.5,3412.8,3411.5,3415.3,3424.2,3438.2,3457.1,3481.0,3510.3,3544.9,3585.8,3633.0,3687.3,3750.2,3823.8,3912.0,4025.4,
3572.2,3565.9,3565.0,3569.3,3578.4,3592.7,3611.9,3636.0,3665.4,3700.2,3741.2,3788.5,3842.7,3905.7,3979.3,4067.5,4180.8,
3768.5,3762.4,3761.6,3765.9,3775.1,3789.3,3808.4,3832.4,3861.7,3896.3,3937.1,3984.2,4038.2,4100.9,4174.3,4262.4,4375.5,
3871.9,3865.7,3864.8,3868.9,3878.0,3892.0,3910.9,3934.8,3963.8,3998.2,4038.7,4085.6,4139.4,4201.9,4275.1,4363.0,4476.0,
3948.1,3941.7,3940.7,3944.7,3953.5,3967.4,3986.1,4009.7,4038.6,4072.7,4113.0,4159.7,4213.3,4275.6,4348.6,4436.3,4549.2,
4006.1,3999.7,3998.4,4002.3,4011.0,4024.7,4043.2,4066.6,4095.3,4129.2,4169.3,4215.8,4269.2,4331.3,4404.2,4491.7,4604.5,
4050.0,4043.5,4042.1,4045.8,4054.3,4067.9,4086.2,4109.5,4138.0,4171.8,4211.7,4258.0,4311.3,4373.2,4445.9,4533.4,4646.1,
4081.8,4075.1,4073.6,4077.2,4085.6,4099.0,4117.2,4140.4,4168.7,4202.4,4242.2,4288.4,4341.5,4403.4,4476.0,4563.3,4676.0],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [5.96, 175.20],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [ -94.7, 74.54],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [5.96, 175.20],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [2950.0, 4090.0],

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
"KgPerLiftKpaAtMidExtension" => 3.4168,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 4371.0,

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
"LiftCylExtPctAxis" => [0.00,13.90,28.40,47.43,64.35,75.77,81.33,85.02,88.04,90.69,92.99,95.05,96.86,98.49,100.00],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00,3.51,6.75,9.74,12.54,15.26,17.81,20.26,22.63,25.09,27.81,30.96,35.00,41.49,52.19,61.14,70.26,80.88,93.42,100.00],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [-15.0670,-27.1550,-24.3556,-4.7763,23.6455,43.3030,42.8519,30.2217,6.7990,-26.1703,-64.5906,-108.3510,-159.0120,-225.0645,-335.6293,
-18.6510,-29.2900,-26.1026,-6.8592,21.9895,46.7770,54.5035,51.5637,38.3848,13.7505,-19.9084,-60.2719,-104.7437,-155.0752,-218.1781,
-21.1193,-30.7992,-27.4599,-8.8032,19.5824,46.9077,59.8007,63.9475,60.0089,45.7770,20.7024,-14.4277,-55.9261,-102.1170,-154.7909,
-22.8298,-31.8625,-28.5021,-10.5277,16.9378,45.1718,61.0526,69.8250,72.6676,67.6099,52.6208,26.3129,-9.6644,-52.9186,-102.4348,
-24.0504,-32.6251,-29.3144,-12.0528,14.2628,42.4326,59.9013,71.5653,79.0462,80.9596,75.0060,58.9010,31.8740,-5.4333,-51.7610,
-24.9395,-33.1745,-29.9545,-13.4140,11.6254,39.1205,57.2583,70.6295,81.1640,88.0512,89.2110,82.4643,65.8087,37.9319,-1.7253,
-25.5540,-33.5413,-30.4299,-14.5694,9.1963,35.6772,53.8594,68.0666,80.4090,90.5211,96.6464,97.0681,89.5689,71.9969,42.1031,
-25.9791,-33.7757,-30.7818,-15.5692,6.9367,32.2013,50.0332,64.5142,77.8445,89.9902,99.5024,105.1591,104.9570,96.7498,77.6799,
-26.2549,-33.9017,-31.0268,-16.4220,4.8697,28.8206,46.0510,60.4227,74.1604,87.4682,99.1568,108.4236,113.5908,112.8761,103.6382,
-26.4205,-33.9386,-31.1880,-17.1899,2.8650,25.3712,41.7884,55.7629,69.4960,83.3673,96.4135,108.1800,117.3234,122.5230,121.7285,
-26.4797,-33.8782,-31.2621,-17.9025,0.8283,21.6973,37.0702,50.3700,63.7293,77.6550,91.3871,104.7579,116.7401,126.4705,132.6040,
-26.4066,-33.6869,-31.2185,-18.5521,-1.2813,17.6996,31.7600,44.0819,56.6800,70.1429,83.8942,97.9942,111.7012,124.5571,135.8863,
-26.1239,-33.2718,-30.9729,-19.1145,-3.5690,13.0988,25.4445,36.3688,47.7025,60.0660,73.0554,86.9003,101.1184,115.5899,130.2078,
-25.2994,-32.2473,-30.1672,-19.4302,-6.3143,7.0047,16.7363,25.3856,34.4630,44.5438,55.4000,67.3571,80.1803,94.0096,109.1652,
-23.1389,-29.7137,-27.8421,-18.5450,-8.5849,0.3629,6.5735,12.0214,17.7381,24.1364,31.1277,38.9909,47.6602,57.3442,68.4476,
-20.6707,-26.8356,-25.0088,-16.6476,-8.7088,-2.4377,1.6328,5.1122,8.7195,12.7361,17.1240,22.0773,27.5763,33.7795,40.9847,
-17.5229,-23.1278,-21.2595,-13.7650,-7.5523,-3.3377,-0.8365,1.2201,3.3074,5.6021,8.0915,10.8938,14.0054,17.5248,21.6319,
-12.8530,-17.5183,-15.5737,-9.3020,-5.0212,-2.6598,-1.4284,-0.4745,0.4609,1.4670,2.5435,3.7458,5.0757,6.5781,8.3332,
-4.8904,-7.4055,-5.8617,-2.6854,-1.2592,-0.6938,-0.4467,-0.2693,-0.1022,0.0734,0.2590,0.4650,0.6927,0.9502,1.2520,
1.5808,3.5152,1.9484,0.5658,0.2309,0.1257,0.0816,0.0496,0.0189,-0.0140,-0.0495,-0.0897,-0.1347,-0.1863,-0.2473],

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
  "InternalMsn" => "CAT94007",
  "Make" => "CAT",
  "Model" => "994H",
  "ModelDetail" => "994H",
  "Linkage" => "Extended High Lift",
  "LinkageConfigurationNumber" => 1256
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0001,
}
