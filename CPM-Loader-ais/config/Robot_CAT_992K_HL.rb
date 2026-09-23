##

## CAT 992K - High Lift
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Depending how the Rotation Sensor is mounter for LIFT & TILT, the DC may need to be inverted
#    0 = don't invert	//dc = sensorDc
#    1 = invert  		//dc = (100-sensorDc)
"invertLiftDc" => 0,
"invertTiltDc" => 0,

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.000000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-33.18, 53.02],

# Lift angle axis of the lift cylinder length table, in degrees.
"inLiftAngle" => [-33.18, -25.59, -18, -10.41, -2.82, 1.84, 6.5, 11.16, 15.82, 20.47, 25.12, 29.77, 34.42, 39.07, 43.72, 48.37, 53.02],


# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [2184, 2307.7, 2432.1, 2554.9, 2674.3, 2745.4, 2814.2, 2880.6, 2944.3, 3005, 3062.5, 3116.7, 3167.4, 3214.4, 3257.6, 3296.8, 3332],

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-33.18, 53.02],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [2184.00, 3332.00],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 

"inTiltDc" => [0.0000, 3.09, 6.30, 9.64, 13.18, 16.97, 21.13, 25.81, 31.28, 37.97, 46.52, 56.79, 68.18, 84.39, 90.93, 95.84, 100.0000],


# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger 
# angles are rack.

"outTiltAngle" => [-30.28, -19.77, -10.46, -1.89, 6.33, 14.41, 22.64, 31.29, 40.78, 51.7, 64.86, 79.9, 95.99, 118.72, 128.21, 135.7, 142.57],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [-30.28, -19.77, -10.46, -1.89, 6.33, 14.41, 22.64, 31.29, 40.78, 51.7, 64.86, 79.9, 95.99, 118.72, 128.21, 135.7, 142.57],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-33.18, -25.59, -18.00, -10.41, -2.82,	1.84, 6.50, 11.16, 15.82, 20.47, 25.12, 29.77, 34.42, 39.07, 43.72, 48.37, 53.02],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [5889.7, 5830.1, 5759.1, 5677.5, 5586.5, 5526.3, 5463.4, 5397.8, 5330.1, 5260.8, 5190.0, 5118.2, 5045.9, 4973.5, 4901.5, 4830.4, 4760.6,
5831.6, 5770.7, 5698.5, 5616.0, 5524.0, 5463.4, 5399.9, 5334.0, 5266.0, 5196.4, 5125.4, 5053.5, 4981.2, 4908.8, 4836.9, 4765.9, 4696.5,
5768.6, 5706.5, 5633.2, 5549.5, 5456.7, 5395.5, 5331.7, 5265.4, 5197.0, 5127.2, 5056.0, 4984.0, 4911.6, 4839.3, 4767.5, 4696.8, 4627.7,
5700.1, 5636.7, 5562.2, 5477.6, 5383.8, 5322.2, 5257.9, 5191.2, 5122.6, 5052.4, 4981.1, 4909.0, 4836.6, 4764.3, 4692.7, 4622.2, 4553.4,
5624.4, 5559.7, 5484.1, 5398.4, 5303.6, 5241.5, 5176.8, 5109.8, 5040.8, 4970.5, 4899.0, 4826.8, 4754.4, 4682.2, 4610.7, 4540.5, 4472.0,
5539.9, 5473.9, 5397.0, 5310.2, 5214.6, 5152.0, 5086.8, 5019.4, 4950.1, 4879.6, 4807.9, 4735.7, 4663.2, 4591.1, 4519.8, 4449.9, 4381.8,
5443.1, 5375.7, 5297.5, 5209.6, 5113.0, 5049.9, 4984.3, 4916.6, 4847.0, 4776.2, 4704.4, 4632.1, 4559.7, 4487.7, 4416.6, 4346.9, 4279.2,
5329.3, 5260.5, 5181.0, 5092.0, 4994.4, 4930.8, 4864.7, 4796.6, 4726.7, 4655.7, 4583.8, 4511.4, 4439.0, 4367.1, 4296.3, 4227.0, 4159.7,
5190.3, 5119.9, 5039.1, 4948.8, 4850.2, 4786.0, 4719.5, 4651.0, 4580.8, 4509.6, 4437.5, 4365.1, 4292.8, 4221.1, 4150.5, 4081.5, 4014.8,
5012.4, 4940.4, 4858.1, 4766.5, 4666.8, 4602.0, 4535.0, 4466.1, 4395.7, 4324.2, 4252.0, 4179.6, 4107.4, 4035.9, 3965.6, 3897.1, 3830.9,
4774.6, 4700.8, 4617.0, 4524.1, 4423.3, 4358.0, 4290.6, 4221.3, 4150.5, 4078.9, 4006.6, 3934.2, 3862.1, 3790.8, 3720.9, 3652.8, 3587.3,
4476.3, 4401.1, 4316.1, 4222.3, 4120.8, 4055.1, 3987.4, 3917.8, 3846.9, 3775.1, 3702.8, 3630.4, 3558.4, 3487.3, 3417.6, 3349.9, 3284.8,
4137.3, 4061.6, 3976.4, 3882.4, 3780.8, 3715.1, 3647.4, 3577.9, 3507.0, 3435.2, 3362.9, 3290.5, 3218.5, 3147.3, 3077.6, 3009.9, 2944.8,
3659.2, 3585.4, 3502.1, 3410.1, 3310.4, 3245.8, 3179.0, 3110.3, 3040.0, 2968.7, 2896.6, 2824.2, 2751.9, 2680.2, 2609.7, 2541.0, 2474.6,
3475.8, 3403.8, 3322.3, 3232.1, 3134.0, 3070.3, 3004.3, 2936.3, 2866.6, 2795.8, 2724.0, 2651.6, 2579.2, 2507.2, 2436.2, 2366.7, 2299.3,
3344.5, 3274.4, 3194.8, 3106.4, 3009.9, 2947.2, 2882.0, 2814.8, 2745.7, 2675.3, 2603.9, 2531.7, 2459.3, 2387.1, 2315.6, 2245.3, 2177.0,
3239.2, 3171.1, 3093.4, 3006.8, 2912.1, 2850.4, 2786.1, 2719.7, 2651.3, 2581.5, 2510.4, 2438.5, 2366.1, 2293.7, 2221.9, 2151.1, 2081.9],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [-30.28, 142.57],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-98.07, 74.78],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [-30.28, 142.57],

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
"KgPerLiftKpaAtMidExtension" => 1.950,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 3155.7,

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
"LiftCylExtPctAxis" => [0.00, 20.03, 42.25, 58.36, 69.25, 76.66, 81.88, 85.80, 88.85, 91.46, 93.64, 95.38, 97.13, 98.43, 100.00],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.

"TiltCylExtPctAxis" => [0.00, 5.60, 9.73, 12.41, 14.60,	16.55, 18.49, 20.68, 23.36, 26.52, 30.41, 34.79, 40.15,	46.23, 53.28, 61.56, 70.80, 81.27, 90.75, 100.00],
# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
	-10.15,	-3.80, 14.94, 43.90, 81.64, 126.74, 177.73, 232.21, 216.67, 361.95, 551.14, 768.55, 793.60, 636.86, 687.20,
	-15.89,	-9.79, 6.35, 30.15, 60.35, 95.99, 136.64, 183.49, 238.20, 310.61, 422.87, 768.55, 793.60, 636.86, 687.20,
	-19.56,	-13.62,	0.81, 21.20, 46.32, 75.29, 107.61, 143.98, 184.99, 235.63, 297.37, 371.53, 502.18, 811.86, 687.20,
	-21.68,	-15.83,	-2.40, 16.01, 38.22, 63.40, 91.09, 121.74, 155.69, 196.55, 244.40, 297.87, 375.54, 465.28, 686.21,
	-23.27,	-17.48,	-4.80, 12.11, 32.17, 54.58, 78.91, 105.52, 134.60, 169.07, 208.57, 251.42, 310.60, 372.87, 486.77,
	-24.57,	-18.82,	-6.77, 8.92, 27.20, 47.38, 69.04, 92.49, 117.84, 147.53, 181.06, 216.79, 264.87, 313.58, 396.24,
	-25.77,	-20.05,	-8.59, 5.96, 22.62, 40.76, 60.03, 80.67, 102.76, 128.36, 156.93, 186.94, 226.61, 265.88, 330.04,
	-27.00,	-21.32,	-10.46,	2.91, 17.90, 33.97, 50.83, 68.68, 87.60, 109.28, 133.18, 157.98, 190.27, 221.64, 271.59,
	-28.34,	-22.67,	-12.50,	-0.45, 12.71, 26.54, 40.82, 55.75, 71.37, 89.04, 108.28, 127.99, 153.26, 177.41, 215.06,
	-29.68,	-24.03,	-14.57, -3.91, 7.35, 18.89, 30.58, 42.60, 55.00, 68.84,	83.70, 98.71, 117.67, 135.53, 162.84,
	-30.99,	-25.34,	-16.65, -7.47, 1.79, 10.99, 20.05, 29.18, 38.42, 48.56,	59.26, 69.91, 83.15, 95.41, 113.82,
	-32.04,	-26.34,	-18.40, -10.62,	-3.21, 3.82, 10.54, 17.12, 23.64, 30.63, 37.88,	44.94, 53.57, 61.41, 72.96,
	-32.68,	-26.94,	-19.76, -13.38,	-7.78, -2.79, 1.75, 6.00, 10.07, 14.30, 18.53, 22.55, 27.31, 31.52, 37.53,
	-33.00,	-26.81,	-20.33, -15.21,	-11.17,	-7.89, -5.15, -2.75, -0.60, 1.50, 3.46, 5.22, 7.17, 8.77, 10.89,
	-31.00,	-25.62,	-19.82, -15.82,	-13.09,	-11.19,	-9.83, -8.83, -8.10, -7.52, -7.15, -6.96, -6.90, -7.02, -7.42,
	-29.00,	-22.84,	-17.77, -14.76,	-13.07,	-12.18,	-11.78,	-11.70,	-11.85,	-12.21,	-12.77,	-13.45,	-14.44,	-15.47,	-17.16,
	-23.00,	-17.96,	-13.81, -11.68,	-10.73,	-10.44,	-10.53,	-10.86,	-11.37,	-12.04,	-12.88,	-13.79,	-15.01,	-16.20,	-18.06,
	-14.00,	-10.02,	-7.40, -6.26, -5.85, -5.83, -6.00 -6.31, -6.69, -7.18, -7.75, -8.34, -9.12, -9.85, -10.99,
	-0.14, -0.08, -0.06, -0.05, -0.04, -0.04, -0.05, -0.05 -0.05, -0.05, -0.06, -0.07, -0.08, -0.08, -0.09,
	210.05,	13.76, 8.03, 6.47, 6.08, 6.17, 6.49, 6.93, 7.46, 8.10, 8.80, 9.52, 10.45, 11.30, 12.60],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 19.1000,

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
  "InternalMsn" => "CAT92201",
  "Make" => "CAT",
  "Model" => "992K",
  "ModelDetail" => "992K",
  "Linkage" => "High Lift",
  "LinkageConfigurationNumber" => 137
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0001,
}
