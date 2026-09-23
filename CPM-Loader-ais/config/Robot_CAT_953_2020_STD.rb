##
## CAT 953 - Standard
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
"outLiftAngle" => [-40.1954, 45.8238],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-40.1954, -31.0664, -25.6764, -21.0474, -16.8380, -12.8998, -9.15840, -5.57786, -2.10934, 1.25488, 4.53392, 7.74849, 10.8963, 13.9871, 17.0315, 20.0417, 23.0165, 25.9540, 28.8682, 31.7584, 34.6233, 37.4609, 40.2683, 43.0643, 45.8238],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1221.00, 1319.70, 1377.10, 1425.50, 1468.60, 1508.00, 1544.50, 1578.50, 1610.50, 1640.60, 1669.00, 1695.90, 1721.30, 1745.30, 1768.00, 1789.50, 1809.80, 1828.90, 1846.90, 1863.80, 1879.60, 1894.30, 1907.90, 1920.50, 1932.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0921621, 0.0931815, 0.0947427, 0.0966275, 0.0987846, 0.101202, 0.103880, 0.106818, 0.110047, 0.113576, 0.117436, 0.121670, 0.126304, 0.131389, 0.136989, 0.143191, 0.150075, 0.157733, 0.166327, 0.176014, 0.186994, 0.199509, 0.213868, 0.230605, 0.250144],

# deg/s^2
"outLiftAngleAccel" => [-0.00422736, 0.106390, 0.169018, 0.225550, 0.281612, 0.340143, 0.403200, 0.472446, 0.550155, 0.638187, 0.739119, 0.856338, 0.993259, 1.15472, 1.34714, 1.57921, 1.86150, 2.20788, 2.63948, 3.18376, 3.87910, 4.78014, 5.96594, 7.56844, 9.76311],

# mm/s
"liftRefVel" => 71.1000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 2585.00,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-40.1954, 45.8238],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1221.00, 1932.00],

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
"outTiltCylLen" => [1041.50, 1519.50],

# Tilt cylinder length axis of the tilt angle table, in mm.
"xTiltCylLen" => [1041.50, 1061.50, 1081.50, 1101.50, 1121.50, 1141.50, 1161.50, 1181.50, 1201.50, 1221.50, 1241.50, 1267.50, 1305.50, 1343.50, 1382.50, 1425.50, 1468.50, 1494.50, 1509.50, 1519.50],

# Lift cylinder length axis of the tilt angle table, in mm.
"yLiftCylLen" => [1221.00, 1289.00, 1361.00, 1426.00, 1500.00, 1568.00, 1631.00, 1688.00, 1739.00, 1783.00, 1821.00, 1854.00, 1883.00, 1909.00, 1932.00],

# Tilt angle axis of the tilt angle table, in degrees.
"outTiltAngle" => [
    45.0149, 47.5802, 47.2736, 44.3632, 37.7390, 28.0894, 15.8913, 3.39486, -8.07392, -19.0430, -29.3904, -39.0029, -47.8287, -55.9403, -63.1924,
    55.3366, 57.4146, 56.9386, 54.1385, 47.9052, 38.7610, 26.7623, 12.9720, 0.184036, -11.2504, -22.0189, -32.0099, -41.2017, -49.6883, -57.3236,
    64.5145, 66.2091, 65.6292, 62.9744, 57.1774, 48.6723, 37.3301, 23.6084, 9.00097, -3.22573, -14.4276, -24.8343, -34.4382, -43.3472, -51.4093,
    72.6972, 74.0948, 73.4564, 70.9578, 65.5919, 57.7442, 47.2142, 34.1720, 19.2528, 5.06351, -6.60475, -17.4550, -27.5087, -36.8791, -45.4038,
    80.0358, 81.2045, 80.5380, 78.1939, 73.2309, 66.0072, 56.3062, 44.1671, 29.8090, 14.6935, 1.46902, -9.84579, -20.3802, -30.2447, -39.2622,
    86.6662, 87.6587, 86.9843, 84.7863, 80.1887, 73.5340, 64.6163, 53.4223, 39.9770, 25.1396, 10.3044, -1.97733, -13.0155, -23.4043, -32.9420,
    92.7052, 93.5620, 92.8928, 90.8294, 86.5575, 80.4103, 72.2047, 61.9144, 49.4812, 35.4528, 20.4766, 6.27445, -5.36907, -16.3180, -26.4073,
    98.2513, 99.0037, 98.3481, 96.4067, 92.4218, 86.7209, 79.1487, 69.6853, 58.2454, 45.2131, 30.8621, 15.9600, 2.59379, -8.94098, -19.6300,
    103.387, 104.060, 103.423, 101.591, 97.8567, 92.5448, 85.5283, 76.8031, 66.2848, 54.2713, 40.8521, 26.3103, 11.5493, -1.22118, -12.5789,
    108.183, 108.796, 108.181, 106.445, 102.928, 97.9529, 91.4195, 83.3433, 73.6545, 62.6062, 50.2001, 36.4825, 21.7145, 7.03748, -5.18451,
    112.699, 113.267, 112.675, 111.025, 107.695, 103.008, 96.8916, 89.3802, 80.4243, 70.2553, 58.8366, 46.1025, 32.0049, 16.7682, 2.66908,
    118.236, 118.765, 118.204, 116.648, 113.520, 109.144, 103.480, 96.5882, 88.4472, 79.2769, 69.0280, 57.5793, 44.7176, 30.1516, 14.5758,
    125.839, 126.344, 125.827, 124.375, 121.465, 117.430, 112.268, 106.078, 98.8772, 90.8833, 82.0572, 72.2715, 61.2646, 48.5525, 34.0228,
    133.109, 133.624, 133.149, 131.763, 128.985, 125.163, 120.339, 114.643, 108.128, 101.016, 93.2838, 84.8245, 75.3991, 64.5399, 51.9692,
    140.517, 141.081, 140.645, 139.284, 136.543, 132.808, 128.167, 122.786, 116.750, 110.285, 103.384, 95.9577, 87.8047, 78.5203, 67.8341,
    149.083, 149.768, 149.369, 147.959, 145.103, 141.270, 136.614, 131.354, 125.602, 119.591, 113.317, 106.705, 99.5861, 91.6219, 82.5940,
    158.976, 159.946, 159.573, 157.938, 154.633, 150.342, 145.336, 139.895, 134.151, 128.330, 122.415, 116.332, 109.924, 102.903, 95.0993,
    166.629, 168.037, 167.657, 165.598, 161.557, 156.583, 151.053, 145.273, 139.357, 133.506, 127.680, 121.788, 115.675, 109.070, 101.824,
    172.536, 174.612, 174.179, 171.430, 166.421, 160.692, 154.643, 148.535, 142.432, 136.503, 130.679, 124.853, 118.866, 112.454, 105.476,
    177.967, 180.553, 180.140, 176.768, 170.348, 163.772, 157.216, 150.807, 144.532, 138.520, 132.674, 126.874, 120.954, 114.650, 107.830
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [3.54300, 176.496],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-94.5871, 78.3659],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [3.54300, 176.496],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1041.50, 1519.50],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 115.000,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 65.0000,

##
## Tilt Cylinders
##

# Number of tilt cylinders.
"NoOfTiltCyls" => 1,

# Tilt cylinder bore diameter, in mm.
"TiltCylBoreDia" => 140.000,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 85.0000,

##
## Tool
##

# Tool's length between B and C pins, in mm.
"ToolBcLen" => 410.122,

# Tool's angle between line BC and tool's X-axis, in deg.
"ToolBcAngle" => 98.1301,

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
"LoaderBktPayldTrgtWt" => 3.76648,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 5.00000,

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
"KgPerLiftKpaAtMidExtension" => 0.442544,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1778.24,

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
"LiftCylExtPctAxis" => [0.00000, 17.7215, 39.9437, 59.0717, 68.2138, 74.8242, 79.8875, 84.1069, 87.4824, 90.4360, 92.9677, 95.0774, 96.9058, 98.5935, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 6.90377, 12.5523, 17.3640, 21.7573, 25.7322, 29.2887, 32.6360, 35.7741, 38.7029, 41.6318, 44.3515, 47.0711, 50.2092, 54.1841, 61.2971, 71.3389, 80.3347, 90.5858, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    40.1969, -143.659, 76.1194, 300.009, 130.760, -215.922, -597.143, -1044.33, -1590.13, -2444.57, -4707.45, -6531.01, -8117.28, -9579.84, -10798.2,
    -100.004, -213.535, 39.8809, 444.775, 534.303, 324.806, -95.8826, -559.140, -1001.08, -1506.16, -2138.98, -3030.65, -4881.79, -6497.85, -7871.02,
    -161.927, -252.994, -9.76050, 438.215, 686.255, 732.400, 497.643, 8.69354, -508.477, -1009.24, -1519.80, -2078.80, -2777.59, -3871.34, -6095.01,
    -192.301, -276.865, -53.8662, 380.751, 688.296, 891.842, 901.719, 625.763, 111.081, -486.629, -1040.22, -1556.97, -2106.60, -2791.60, -3644.11,
    -208.466, -292.266, -90.7959, 310.433, 626.826, 903.661, 1075.03, 1055.04, 763.626, 196.945, -459.196, -1047.00, -1596.59, -2194.19, -2833.43,
    -216.542, -301.774, -119.750, 243.767, 545.108, 843.012, 1095.21, 1245.13, 1199.06, 870.307, 265.412, -416.075, -1054.74, -1681.63, -2279.16,
    -219.934, -307.216, -141.568, 186.779, 464.538, 757.013, 1039.34, 1279.75, 1398.31, 1317.24, 945.934, 326.582, -393.413, -1120.81, -1763.38,
    -220.602, -310.023, -158.508, 137.680, 389.231, 663.881, 948.990, 1230.94, 1446.74, 1544.97, 1428.28, 1037.78, 393.856, -410.362, -1153.75,
    -219.466, -310.841, -171.312, 96.5600, 322.561, 574.361, 847.405, 1140.18, 1404.59, 1612.22, 1684.05, 1542.02, 1128.30, 413.462, -393.983,
    -217.145, -310.177, -180.707, 62.7588, 265.391, 493.453, 747.530, 1033.65, 1315.48, 1581.43, 1772.01, 1817.28, 1650.25, 1175.91, 459.225,
    -213.800, -308.255, -187.782, 33.3850, 213.858, 417.699, 648.862, 918.017, 1198.28, 1490.19, 1751.38, 1925.35, 1959.48, 1763.00, 1290.83,
    -209.905, -305.431, -192.408, 9.94826, 171.283, 353.227, 561.696, 809.712, 1077.24, 1372.36, 1665.58, 1912.51, 2076.59, 2093.61, 1883.55,
    -205.341, -301.672, -195.285, -9.98116, 133.758, 294.974, 480.741, 705.083, 953.210, 1237.89, 1539.55, 1824.30, 2069.28, 2236.95, 2245.23,
    -199.330, -296.241, -196.580, -28.9093, 96.4921, 235.660, 396.324, 592.537, 813.965, 1076.08, 1367.60, 1664.37, 1955.44, 2226.91, 2406.68,
    -190.680, -287.767, -195.343, -47.1783, 57.9138, 172.322, 303.955, 465.882, 651.595, 877.191, 1138.06, 1419.03, 1718.80, 2042.33, 2332.99,
    -172.565, -268.330, -185.895, -66.1307, 9.82813, 88.5794, 177.490, 286.787, 413.687, 571.564, 760.996, 975.823, 1221.78, 1516.10, 1825.23,
    -141.294, -231.248, -158.450, -69.1136, -22.2924, 21.7416, 69.0533, 125.996, 191.865, 274.505, 375.532, 493.365, 633.476, 810.030, 1008.47,
    -106.511, -186.132, -120.459, -54.3666, -26.1295, -2.40936, 21.5020, 49.3449, 81.0742, 120.708, 169.283, 226.374, 295.068, 383.084, 484.157,
    -54.6285, -110.863, -59.9088, -24.5068, -13.3210, -5.23829, 2.24802, 10.5919, 19.9073, 31.4493, 45.5756, 62.2240, 82.3654, 108.379, 138.558,
    6.11749, 45.9427, 10.1403, 3.17883, 1.71925, 0.742089, -0.152952, -1.15906, -2.29613, -3.72114, -5.48271, -7.57638, -10.1281, -13.4472, -17.3245
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 3.76648,

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
"TiltCylExtThresholdStrict" => 97.3264,

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
  "InternalMsn" => "CAT53700",
  "Make" => "CAT",
  "Model" => "953",
  "ModelDetail" => "953",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x00BC,
  "ST_chg_lvl" => 0x0001,
}
