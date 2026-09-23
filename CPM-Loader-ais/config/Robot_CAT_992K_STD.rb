##

## CAT 992K - Standard
##
MachineSpecificConfig = {

# Depending how the Rotation Sensor is mounter for LIFT & TILT, the DC may need to be inverted
#    0 = don't invert	//dc = sensorDc
#    1 = invert  		//dc = (100-sensorDc)
"invertLiftDc" => 0,
"invertTiltDc" => 0,

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.000000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-36.45, 47.46],

# Lift angle axis of the lift cylinder length table, in degrees.
"inLiftAngle" => [-36.45, -29.06, -21.67, -14.27, -6.88, -2.35, 2.18, 6.71, 11.23, 15.76, 20.29, 24.82, 29.35, 33.88, 38.40, 42.93, 47.46],

# Lift cylinder length axis of the lift cylinder length table, in mm.

"outLiftCylLen" => [2184.00, 2304.30, 2425.40, 2545.90, 2663.50, 2733.70, 2802.00, 2868.20, 2931.80, 2993.00, 3051.30, 3106.60, 3158.70, 3207.40, 3252.50, 3294.00, 3332.00],
# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-36.45, 47.46],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [2184.00, 3332.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 
"inTiltDc" => [0.0000, 4.6016, 9.2032, 13.8048, 18.4064, 23.0080, 27.6096, 39.2732, 50.9471, 62.6107, 67.9535, 73.2963, 78.6391, 83.9716, 89.3144, 94.6572, 100.0000],


# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger 
# angles are rack.
"outTiltAngle" => [-29.70, -17.11, -5.94, 4.22, 13.61, 22.42, 30.76, 50.42, 68.65, 86.07, 93.91, 101.73, 109.59, 117.58, 125.85, 134.71, 145.22],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [-29.70, -17.11, -5.94, 4.22, 13.61, 22.42, 30.76, 50.42, 68.65, 86.07, 93.91, 101.73, 109.59, 117.58, 125.85, 134.71, 145.22],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-36.45, -29.06, -21.67, -14.27, -6.88, -2.35, 2.18, 6.71, 11.23, 15.76, 20.29, 24.82, 29.35, 33.88, 38.4, 42.93, 47.46],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [5944.8, 5893.3, 5830.5, 5757.2, 5674.3, 5619.1, 5561.0, 5500.1, 5436.9, 5371.4, 5304.2, 5235.5, 5165.8, 5095.5, 5025.0, 4954.7, 4885.0,
5865.2, 5811.5, 5746.8, 5671.6, 5587.1, 5531.0, 5472.0, 5410.4, 5346.6, 5280.6, 5212.9, 5143.9, 5074.0, 5003.5, 4933.1, 4862.9, 4793.5,
5778.6, 5722.9, 5656.3, 5579.4, 5493.3, 5436.4, 5376.7, 5314.3, 5249.9, 5183.4, 5115.3, 5046.0, 4975.9, 4905.4, 4835.0, 4765.0, 4695.9,
5685.4, 5627.7, 5559.3, 5480.8, 5393.2, 5335.5, 5275.1, 5212.1, 5147.1, 5080.2, 5011.7, 4942.2, 4871.9, 4801.3, 4731.1, 4661.3, 4592.5,
5585.7, 5526.2, 5456.1, 5376.0, 5287.1, 5228.7, 5167.5, 5104.0, 5038.5, 4971.1, 4902.3, 4832.6, 4762.2, 4691.6, 4621.5, 4551.9, 4483.5,
5480.0, 5418.7, 5346.9, 5265.4, 5175.2, 5116.1, 5054.3, 4990.2, 4924.3, 4856.5, 4787.5, 4717.5, 4647.1, 4576.5, 4506.5, 4437.2, 4369.1,
5368.3, 5305.4, 5232.2, 5149.3, 5057.9, 4998.1, 4935.8, 4871.2, 4804.8, 4736.8, 4667.5, 4597.4, 4526.9, 4456.4, 4386.5, 4317.4, 4249.7,
5061.6, 4994.9, 4918.4, 4832.5, 4738.5, 4677.4, 4613.9, 4548.3, 4481.1, 4412.3, 4342.6, 4272.2, 4201.7, 4131.3, 4061.9, 3993.4, 3926.7,
4725.8, 4656.3, 4577.2, 4489.2, 4393.4, 4331.3, 4266.9, 4200.6, 4132.9, 4063.7, 3993.7, 3923.2, 3852.7, 3782.6, 3713.5, 3645.6, 3579.6,
4369.1, 4297.8, 4217.2, 4127.9, 4031.1, 3968.5, 3903.7, 3837.0, 3769.0, 3699.7, 3629.5, 3559.0, 3488.5, 3418.5, 3349.6, 3282.1, 3216.6,
4201.4, 4129.8, 4048.9, 3959.4, 3862.4, 3799.7, 3734.9, 3668.2, 3600.2, 3530.8, 3460.7, 3390.2, 3319.7, 3249.7, 3180.8, 3113.3, 3047.8,
4032.6, 3961.0, 3880.1, 3790.6, 3693.8, 3631.2, 3566.4, 3499.8, 3431.8, 3362.5, 3292.4, 3221.9, 3151.4, 3081.4, 3012.4, 2944.9, 2879.3,
3864.1, 3792.7, 3712.1, 3623.0, 3526.6, 3464.2, 3399.6, 3333.2, 3265.4, 3196.2, 3126.2, 3055.7, 2985.1, 2915.0, 2846.0, 2778.2, 2712.4,
3697.5, 3626.6, 3546.7, 3458.3, 3362.6, 3300.6, 3236.4, 3170.3, 3102.7, 3033.8, 2963.9, 2893.4, 2822.9, 2752.6, 2683.4, 2615.3, 2549.1,
3533.9, 3464.3, 3385.6, 3298.3, 3203.6, 3142.3, 3078.6, 3013.0, 2945.9, 2877.2, 2807.6, 2737.2, 2666.7, 2596.3, 2526.8, 2458.2, 2391.5,
3375.8, 3307.9, 3230.8, 3145.2, 3052.0, 2991.5, 2928.7, 2863.8, 2797.3, 2729.1, 2659.8, 2589.7, 2519.1, 2448.6, 2378.8, 2309.7, 2242.2,
3224.8, 3159.6, 3084.8, 3001.3, 2910.2, 2850.8, 2789.1, 2725.2, 2659.5, 2592.0, 2523.3, 2453.5, 2383.1, 2312.6, 2242.4, 2172.8, 2104.4],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [-29.70, 145.22],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-97.49, 77.43],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [-29.70, 145.22],

# Tilt cylinder length limits, in mm.
#"KnmaticsTiltCylLenMinMax" => [3065.00, 5120.00],
# Reversed for 6 bar linkages
"KnmaticsTiltCylLenMinMax" => [5120.00, 3065.00],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 279.0,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 178.0,

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
"LoaderBktPayldTrgtWt" => 21.7,

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
"KgPerLiftKpaAtMidExtension" => 2.119,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 2883.8,

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
"LiftCylExtPctAxis" => [0.00, 9.15, 19.60, 31.79, 47.91, 60.10, 69.25, 76.66, 82.32, 87.11, 90.59, 93.64, 96.25, 98.43, 100.00],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.

"TiltCylExtPctAxis" => [0.00, 2.92, 6.33, 10.71, 16.06,	20.44, 24.82, 29.68, 34.79, 40.63, 46.96, 54.01, 61.56,	69.83, 78.35, 86.13, 91.24, 93.92, 96.59, 100.00],
# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
	-22.47,	-16.62,	-10.87,	-2.85,	12.95,	32.54,	55.67,	84.09,	115.65,	152.20,	185.03,	213.52,	218.17,	125.07,	275.36,
	-25.66,	-19.67,	-13.96,	-6.26,	8.48,	26.48,	47.63,	73.70,	103.16,	138.71,	173.72,	212.47,	250.70,	278.06,	275.36,
	-29.07,	-22.93,	-17.27,	-9.93,	3.62,	19.79,	38.56,	61.60,	87.69,	119.61,	151.96,	189.93,	232.69,	277.65,	315.45,
	-32.97,	-26.64,	-21.03,	-14.14,	-2.00,	11.97,	27.84,	47.07,	68.65,	94.99,	121.79,	153.63,	190.49,	231.34,	268.94,
	-37.00,	-30.46,	-24.90,	-18.47,	-7.88,	3.73,	16.49,	31.57,	48.20,	68.19,	88.32,	112.06,	139.43,	169.77,	197.83,
	-39.72,	-33.01,	-27.47,	-21.37,	-11.86,	-1.92,	8.67,	20.88,	34.09,	49.72,	65.23,	83.32,	103.94,	126.57,	147.34,
	-41.93,	-35.05,	-29.53,	-23.71,	-15.13,	-6.63,	2.11,	11.91,	22.26,	34.28,	46.01,	59.48,	74.63,	91.05,	105.94,
	-43.80,	-36.76,	-31.23,	-25.67,	-17.98,	-10.82,	-3.81,	3.77,	11.55,	20.33,	28.72,	38.17,	48.59,	59.68,	69.59,
	-45.13,	-37.91,	-32.37,	-27.03,	-20.14,	-14.15,	-8.61,	-2.89,	2.73,	8.87,	14.56,	20.80,	27.50,	34.45,	40.54,
	-45.86,	-38.46,	-32.89,	-27.77,	-21.62,	-16.72,	-12.51,	-8.46,	-4.71,	-0.84,	2.57,	6.13,	9.79,	13.40,	16.44,
	-46.00,	-38.13,	-32.56,	-27.64,	-22.14,	-18.16,	-15.07,	-12.36,	-10.08,	-7.96,	-6.28,	-4.69,	-3.26,	-2.04,	-1.16,
	-44.00,	-36.67,	-31.11,	-26.39,	-21.51,	-18.33,	-16.14,	-14.49,	-13.33,	-12.50,	-12.05,	-11.86,	-11.95,	-12.32,	-12.85,
	-42.00,	-33.77,	-28.29,	-23.84,	-19.54,	-17.03,	-15.52,	-14.61,	-14.20,	-14.17,	-14.46,	-15.06,	-15.98,	-17.19,	-18.43,
	-37.00,	-28.87,	-23.66,	-19.62,	-15.98,	-14.07,	-13.09,	-12.67,	-12.67,	-13.04,	-13.65,	-14.54,	-15.72,	-17.15,	-18.53,
	-29.00,	-21.57,	-17.00,	-13.68,	-10.92,	-9.61,	-9.02,	-8.86,	-9.00,	-9.42,	-9.98,	-10.75,	-11.72,	-12.86,	-13.93,
	-17.00,	-11.87,	-8.75,	-6.70,	-5.17,	-4.50,	-4.23,	-4.18,	-4.29,	-4.52,	-4.83,	-5.23,	-5.73,	-6.29,	-6.83,
	-4.00,	-2.39,	-1.60,	-1.16,	-0.86,	-0.74,	-0.69,	-0.69,	-0.71,	-0.75,	-0.81,	-0.87,	-0.95,	-1.05,	-1.14,
	11.00,	5.04,	3.08,	2.13,	1.54,	1.32,	1.24,	1.22,	1.27,	1.34,	1.44,	1.57,	1.72,	1.91,	2.06,
	11.00,	18.35,	8.97,	5.74,	4.02,	3.41,	3.20,	3.17,	3.28,	3.49,	3.75,	4.08,	4.49,	4.96,	5.38,
	11.00,	-15.95,	21.35,	11.00,	7.24,	6.07,	5.67,	5.64,	5.85,	6.25,	6.72,	7.35,	8.09,	8.93,	9.70
	],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 21.7000,

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
  "InternalMsn" => "CAT92200",
  "Make" => "CAT",
  "Model" => "992K",
  "ModelDetail" => "992K",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0001,
}
