##
## CAT 973 - Standard
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Depending on sensor mounting, sensor duty cycle increases or decreases with
# raise. 0 = not inverted (default), 1 = inverted
"invertLiftDc" => 1,

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.00000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-38.2818, 41.7211],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-38.2818, -29.4065, -22.7822, -18.1159, -14.0768, -10.3940, -6.94612, -3.67635, -0.541518, 2.48741, 5.42428, 8.29210, 11.0979, 13.8397, 16.5337, 19.1881, 21.8016, 24.3827, 26.9305, 29.4545, 31.9540, 34.4279, 36.8748, 39.3060, 41.7211],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1526.40, 1650.90, 1743.60, 1808.10, 1863.10, 1912.40, 1957.70, 1999.80, 2039.30, 2076.60, 2111.90, 2145.50, 2177.50, 2207.90, 2236.90, 2264.60, 2291.00, 2316.20, 2340.20, 2363.10, 2384.90, 2405.60, 2425.20, 2443.80, 2461.40],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0717038, 0.0711796, 0.0718833, 0.0728758, 0.0740555, 0.0753921, 0.0768757, 0.0785000, 0.0802675, 0.0821846, 0.0842551, 0.0864955, 0.0889157, 0.0915204, 0.0943345, 0.0973813, 0.100678, 0.104257, 0.108144, 0.112389, 0.117031, 0.122117, 0.127702, 0.133883, 0.140749],

# deg/s^2
"outLiftAngleAccel" => [-0.105435, 0.0251889, 0.106659, 0.162670, 0.212926, 0.261855, 0.311726, 0.363926, 0.419733, 0.480358, 0.546897, 0.620884, 0.703770, 0.796971, 0.902848, 1.02407, 1.16346, 1.32510, 1.51349, 1.73520, 1.99777, 2.31076, 2.68635, 3.14295, 3.70327],

# mm/s
"liftRefVel" => 93.5000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 3220.00,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-38.2818, 41.7211],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1526.40, 2461.40],

##
## Tilt Kinematics
##

# Tilt sensor type, 0 is rotary (default), 1 is position sensing cylinder.
"tiltSensorType" => 1,

# Depending on sensor mounting, sensor duty cycle increases or decreases with
# rack. 0 = not inverted (default), 1 = inverted
"invertTiltDc" => 0,

# Normalized, calibrated, tilt sensor axis of the tilt cylinder length table, in
# % 
"inTiltDc" => [0.00000, 100.000],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [1310.30, 1943.20],

# Tilt cylinder length axis of the tilt angle table, in mm.
"xTiltCylLen" => [1310.30, 1334.30, 1358.30, 1382.30, 1406.30, 1431.30, 1456.30, 1481.30, 1506.30, 1531.30, 1558.30, 1599.30, 1650.30, 1701.30, 1753.30, 1810.30, 1869.30, 1907.30, 1931.30, 1943.20],

# Lift cylinder length axis of the tilt angle table, in mm.
"yLiftCylLen" => [1526.40, 1612.40, 1705.40, 1793.40, 1885.40, 1975.40, 2059.40, 2136.40, 2203.40, 2259.40, 2308.40, 2352.40, 2392.40, 2428.40, 2461.40],

# Tilt angle axis of the tilt angle table, in degrees.
"outTiltAngle" => [
    36.3976, 39.3261, 39.5062, 36.9809, 31.4726, 23.1024, 12.8224, 2.63769, -5.46238, -12.8533, -19.8611, -26.5836, -33.0117, -38.9827, -44.5336,
    45.5460, 48.0504, 48.0390, 45.5398, 40.2102, 32.0154, 21.5049, 9.91992, 0.192507, -7.43808, -14.6645, -21.5833, -28.1917, -34.3428, -40.0937,
    53.9061, 56.0450, 55.8962, 53.4739, 48.4070, 40.5809, 30.3038, 18.2762, 6.68554, -1.89911, -9.34604, -16.4732, -23.2863, -29.6467, -35.6261,
    61.5104, 63.3461, 63.1027, 60.7842, 56.0133, 48.6400, 38.8356, 26.9688, 14.5860, 4.01604, -3.90240, -11.2491, -18.2852, -24.8757, -31.1032,
    68.4296, 70.0182, 69.7129, 67.5100, 63.0396, 56.1419, 46.9139, 35.5336, 23.1098, 11.3999, 1.68973, -5.90411, -13.1757, -20.0107, -26.4992,
    74.9959, 76.3774, 76.0329, 73.9536, 69.7844, 63.3702, 54.7705, 44.0560, 32.0463, 20.0459, 8.79170, -0.198881, -7.72204, -14.8220, -21.5945,
    80.9956, 82.2122, 81.8474, 79.8886, 75.9998, 70.0384, 62.0493, 52.0512, 40.6847, 28.9508, 17.1564, 6.29674, -2.11346, -9.48618, -16.5612,
    86.5098, 87.5956, 87.2238, 85.3793, 81.7464, 76.1987, 68.7793, 59.4866, 48.8497, 37.6709, 25.9895, 14.3035, 3.89737, -3.97613, -11.3691,
    91.6102, 92.5926, 92.2233, 90.4851, 87.0828, 81.9069, 75.0063, 66.3765, 56.4767, 45.9771, 34.7659, 23.0148, 11.4483, 1.75345, -5.94086,
    96.3590, 97.2606, 96.9006, 95.2600, 92.0634, 87.2181, 80.7824, 72.7587, 63.5617, 53.7714, 43.1972, 31.8208, 19.9715, 8.76782, -0.287100,
    101.156, 101.990, 101.646, 100.101, 97.0997, 92.5676, 86.5746, 79.1363, 70.6366, 61.5882, 51.7621, 41.0315, 29.4731, 17.7243, 6.69026,
    107.908, 108.674, 108.360, 106.941, 104.188, 100.052, 94.6216, 87.9367, 80.3551, 72.3218, 63.5972, 53.9917, 43.4068, 32.0826, 20.1969,
    115.646, 116.373, 116.104, 114.811, 112.295, 108.531, 103.635, 97.6790, 91.0056, 84.0082, 76.4639, 68.1781, 58.9951, 48.9688, 37.9236,
    122.924, 123.653, 123.437, 122.239, 119.883, 116.372, 111.850, 106.421, 100.424, 94.2191, 87.6066, 80.4109, 72.4802, 63.8158, 54.1613,
    130.156, 130.933, 130.779, 129.644, 127.373, 124.000, 119.705, 114.627, 109.110, 103.493, 97.5935, 91.2568, 84.3505, 76.8671, 68.5570,
    138.259, 139.164, 139.096, 137.982, 135.692, 132.305, 128.063, 123.156, 117.942, 112.742, 107.383, 101.725, 95.6560, 89.1720, 82.0547,
    147.568, 148.771, 148.842, 147.655, 145.119, 141.421, 136.930, 131.906, 126.737, 121.725, 116.681, 111.471, 105.993, 100.246, 94.0403,
    154.844, 156.494, 156.739, 155.358, 152.347, 148.090, 143.126, 137.778, 132.446, 127.401, 122.426, 117.373, 112.140, 106.725, 100.951,
    160.667, 162.965, 163.450, 161.713, 157.974, 152.980, 147.449, 141.719, 136.167, 131.021, 126.024, 121.015, 115.883, 110.624, 105.065,
    164.302, 166.740, 167.313, 165.470, 161.365, 155.739, 149.779, 143.777, 138.068, 132.842, 127.813, 122.807, 117.710, 112.512, 107.045
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [0.634900, 164.740],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-89.3651, 74.7404],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [0.634900, 164.740],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1310.30, 1943.20],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 160.000,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 85.0000,

##
## Tilt Cylinders
##

# Number of tilt cylinders.
"NoOfTiltCyls" => 2,

# Tilt cylinder bore diameter, in mm.
"TiltCylBoreDia" => 130.000,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 80.0000,

##
## Tool
##

# Tool's length between B and C pins, in mm.
"ToolBcLen" => 585.000,

# Tool's angle between line BC and tool's X-axis, in deg.
"ToolBcAngle" => 90.0000,

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
"LoaderBktPayldTrgtWt" => 6.76400,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 9.50000,

# The CAT datalink configuration file.
"BMI_CDL_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiCdl_TTL_SA.json",

# The BMI J1939 configuration file.
"BMI_J1939_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/BmiJ1939_TTL_SA.json",

# This will define which UI features are supported or not.
"UI_SHOW_FEATURE_CONFIG_JSON_FILE_PATH" => ENV["CAT_CONFIG_DIR"] + "/UI_SHOW_FEATURE_CONFIG_TTL.json",

# Determines whether or not hydraulic oil temperature is optional for this
# machine configuration.
"HydOilTempOptional" => true,

# Determines whether or not acceleration compensation is supported for this
# machine configuration
"AccelCompSupported" => true,

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
"KgPerLiftKpaAtMidExtension" => 0.934320,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1702.36,

##
## Temperature Compensation
##

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylHeLineLoss2ndOrdrCoeff" => 5.91777E-06,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3.
"LiftCylHeLineLoss1stOrdrCoeff" => 6.64300,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow squared. delta_p = K2 * rho * Q^2, in m^-4.
"LiftCylReLineLoss2ndOrdrCoeff" => 4.14134E-06,

# Used to estimate the pressure drop from the sensor to the cylinder as
# proportional to flow. delta_p = K1 * mu * Q, in m^-3
"LiftCylReLineLoss1stOrdrCoeff" => 7.24829,

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
"StageOneCf" => 6.91000,

# Band stop filter stage 2 center frequency in rad/sec.
"StageTwoCf" => 15.0100,

# Band stop filter stage 3 center frequency in rad/sec.
"StageThreeCf" => 29.5300,

# Band stop filter dampening ratio.
"DampingRate" => 0.900000,

# Determines whether or not an additional low-pass filter is applied to weight.
# Optional
"WtLpsOptional" => true,

# Corner Frequency in Hz.
"WtLpsOptionalCf" => 5.00000,

# Lift Angular Velocity low pass filter corner frequency in rad/sec.
"LiftAngVelFilterCf" => 31.4159,

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
"LiftCylExtPctAxis" => [0.00000, 13.1551, 28.1283, 47.8075, 60.0000, 67.7005, 73.7968, 78.8235, 83.1016, 86.8449, 90.1604, 93.0481, 95.6150, 97.9679, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 6.00411, 11.0602, 15.4843, 19.5924, 23.3844, 27.0185, 30.3365, 33.4966, 36.4987, 39.3427, 42.1868, 45.1888, 48.6649, 53.2470, 61.9371, 70.7853, 79.3174, 89.4296, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -4.12864, -77.6606, -50.8133, 77.0426, 112.420, 47.0204, -76.3964, -220.602, -375.443, -549.704, -762.573, -1052.52, -1596.31, -2073.85, -2492.58,
    -66.5280, -110.518, -71.1849, 83.7953, 186.434, 195.958, 118.661, -22.4883, -187.140, -356.637, -533.946, -727.068, -959.632, -1291.51, -1891.30,
    -96.5470, -128.292, -87.8427, 69.0679, 201.996, 269.311, 265.684, 177.881, 22.1561, -162.922, -350.302, -533.458, -725.136, -947.631, -1213.92,
    -111.703, -138.499, -100.750, 48.4257, 189.135, 286.880, 339.645, 323.642, 224.441, 53.5403, -150.087, -349.843, -543.369, -745.020, -955.741,
    -119.579, -144.608, -110.814, 27.1797, 164.363, 274.089, 360.285, 401.969, 375.652, 264.860, 79.5323, -135.571, -349.582, -560.219, -761.640,
    -123.189, -147.989, -118.300, 8.02833, 136.502, 247.028, 348.341, 425.466, 457.490, 420.112, 296.243, 101.906, -125.635, -359.046, -573.744,
    -124.303, -149.586, -123.844, -8.79305, 108.841, 214.174, 319.123, 414.427, 484.846, 508.914, 461.147, 329.394, 125.877, -119.636, -357.551,
    -123.843, -149.879, -127.567, -22.3673, 84.5778, 182.225, 284.179, 385.423, 475.948, 539.811, 553.705, 494.785, 352.085, 131.888, -115.555,
    -122.411, -149.282, -129.996, -33.5365, 63.2567, 152.299, 247.922, 348.116, 447.025, 534.030, 591.061, 594.793, 525.121, 366.753, 144.476,
    -120.346, -148.028, -131.363, -42.5254, 45.0318, 125.518, 213.371, 308.588, 408.310, 506.184, 589.429, 638.103, 632.194, 548.443, 384.958,
    -117.883, -146.297, -131.873, -49.6148, 29.7489, 102.228, 182.005, 270.350, 366.445, 467.054, 563.769, 640.817, 681.721, 664.333, 571.960,
    -115.013, -144.093, -131.675, -55.3779, 16.4238, 81.2558, 152.820, 233.196, 322.953, 421.109, 522.730, 616.048, 688.938, 724.007, 699.408,
    -111.614, -141.302, -130.752, -60.1078, 4.43026, 61.7449, 124.892, 196.436, 277.864, 369.781, 469.942, 570.152, 662.515, 735.380, 767.283,
    -107.278, -137.526, -128.834, -63.9772, -6.94188, 42.4871, 96.5386, 158.021, 228.977, 311.077, 404.114, 503.041, 603.796, 700.422, 774.818,
    -101.006, -131.731, -125.026, -66.6957, -18.1681, 22.2464, 65.6796, 114.949, 172.312, 239.994, 319.189, 407.551, 504.256, 608.401, 707.082,
    -87.6211, -118.362, -114.167, -65.4997, -29.5321, -2.31697, 25.4243, 56.1354, 91.7607, 134.326, 185.526, 245.197, 314.733, 396.755, 485.453,
    -72.0755, -101.485, -98.4600, -57.2848, -30.7435, -12.9456, 3.84230, 21.5914, 41.7173, 65.6037, 94.4868, 128.658, 169.459, 219.298, 275.792,
    -54.8947, -81.3550, -78.4503, -43.8782, -24.8058, -13.6546, -4.09132, 5.41093, 15.8082, 27.9320, 42.5071, 59.7913, 80.6023, 106.380, 136.164,
    -30.2434, -49.4472, -46.0341, -22.0985, -12.0035, -7.18464, -3.57834, -0.300673, 3.10756, 6.98201, 11.5937, 17.0579, 23.6674, 31.9233, 41.5713,
    5.22068, 12.5154, 9.16262, 2.26973, 0.974409, 0.534202, 0.243149, -0.0150580, -0.289038, -0.610609, -1.00525, -1.48493, -2.07727, -2.83022, -3.72350
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 6.76400,

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

# Used to determine if the bucket is fully racked back for LFT payload. LFT
# Fully Racked = Cyl% > This Value
"TiltCylExtThresholdStrict" => 97.5938,

# Used to determine if the bucket is near the end of tilt cylinder extension.
# Used to determine fully racked and partial dump status. Fully Racked = ((Cyl%
# > This Value) OR (ABC% > Y)) AND (Bucket Angle > Z). Partial Dump = (Cyl% <=
# This Value) AND (ABC% <= Y) AND (Bucket Angle <= Z)
"TiltCylExtThreshold" => 85.0000,

# Used to determine if the tilt angle is near the rack stops. Used to determine
# fully racked and partial dump status. Fully Racked = ((Cyl% > X) OR (ABC% >
# This Value)) AND (Bucket Angle > Z). Partial Dump = (Cyl% <= X) AND (ABC% <=
# This Value) AND (Bucket Angle <= Z)
"TiltAngleABCThreshold" => 90.0000,

}

MachineType = {
  "InternalMsn" => "CAT73700",
  "Make" => "CAT",
  "Model" => "973",
  "ModelDetail" => "973",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x00BC,
  "ST_chg_lvl" => 0x0001,
}
