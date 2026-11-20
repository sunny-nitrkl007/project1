##
## CAT 963 - Standard
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
"outLiftAngle" => [-38.3794, 43.2946],

# Lift angle axis of the lift cylinder length table and the lift gain table, in
# degrees.
"inLiftAngle" => [-38.3794, -28.5496, -23.2999, -18.8934, -14.9154, -11.2173, -7.71224, -4.36155, -1.12478, 2.01333, 5.06863, 8.05794, 10.9893, 13.8606, 16.6908, 19.4786, 22.2339, 24.9553, 27.6414, 30.3031, 32.9394, 35.5634, 38.1599, 40.7429, 43.2946],

# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [1344.00, 1469.60, 1535.90, 1590.70, 1639.30, 1683.60, 1724.70, 1763.10, 1799.30, 1833.50, 1865.90, 1896.70, 1926.00, 1953.80, 1980.30, 2005.50, 2029.50, 2052.30, 2073.90, 2094.40, 2113.80, 2132.20, 2149.50, 2165.80, 2181.00],

# Lift linkage gain axis of the lift gain table, in degrees per mm.
"outLiftAngleGain" => [0.0782095, 0.0786814, 0.0797753, 0.0811129, 0.0826481, 0.0843614, 0.0862514, 0.0883152, 0.0905648, 0.0930060, 0.0956516, 0.0985221, 0.101637, 0.105008, 0.108677, 0.112670, 0.117033, 0.121805, 0.127032, 0.132792, 0.139158, 0.146255, 0.154156, 0.163043, 0.173027],

# deg/s^2
"outLiftAngleAccel" => [-0.0373109, 0.0856976, 0.145561, 0.196990, 0.246398, 0.296454, 0.349013, 0.405348, 0.466939, 0.535046, 0.611172, 0.697196, 0.795190, 0.907299, 1.03708, 1.18810, 1.36551, 1.57521, 1.82458, 2.12455, 2.48830, 2.93587, 3.48914, 4.18463, 5.06380],

# mm/s
"liftRefVel" => 83.7000,

# Distance between the A-pin and B-pin on the lift arms, in mm.
"LiftArmAbLength" => 2945.00,

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-38.3794, 43.2946],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [1344.00, 2181.00],

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
"outTiltCylLen" => [1148.20, 1756.80],

# Tilt cylinder length axis of the tilt angle table, in mm.
"xTiltCylLen" => [1148.20, 1173.20, 1198.20, 1223.20, 1248.20, 1273.20, 1298.20, 1323.20, 1348.20, 1373.20, 1402.20, 1448.20, 1497.20, 1546.20, 1597.20, 1654.20, 1700.20, 1728.20, 1745.20, 1756.80],

# Lift cylinder length axis of the tilt angle table, in mm.
"yLiftCylLen" => [1344.00, 1419.00, 1503.00, 1582.00, 1662.00, 1742.00, 1817.00, 1886.00, 1948.00, 2000.00, 2045.00, 2085.00, 2121.00, 2153.00, 2181.00],

# Tilt angle axis of the tilt angle table, in degrees.
"outTiltAngle" => [
    49.7012, 52.4151, 52.5930, 50.1059, 44.8141, 36.4061, 25.4820, 13.4246, 3.09783, -5.51915, -13.5436, -21.1376, -28.3417, -34.9581, -40.8292,
    58.7980, 61.0642, 61.0488, 58.6280, 53.6102, 45.6033, 34.9169, 22.2841, 9.81073, 0.505668, -7.83843, -15.7282, -23.1884, -30.0499, -36.1770,
    66.9713, 68.8750, 68.7271, 66.4097, 61.7075, 54.2054, 44.0525, 31.5803, 18.0691, 6.73701, -1.95862, -10.1529, -17.9034, -25.0515, -31.4726,
    74.3218, 75.9375, 75.7025, 73.5051, 69.1240, 62.1517, 52.6555, 40.7423, 27.1350, 14.2779, 4.10058, -4.40667, -12.4707, -19.9307, -26.6646,
    80.9609, 82.3497, 82.0602, 79.9875, 75.9138, 69.4550, 60.6420, 49.4665, 36.3169, 23.0032, 10.8736, 1.52332, -6.87166, -14.6571, -21.7083,
    86.9933, 88.2040, 87.8835, 85.9331, 82.1441, 76.1625, 68.0081, 57.6218, 45.2041, 32.1268, 19.1385, 7.75585, -1.08310, -9.20492, -16.5770,
    92.5123, 93.5838, 93.2488, 91.4143, 87.8836, 82.3345, 74.7899, 65.1754, 53.5932, 41.1269, 28.1143, 15.4155, 4.92517, -3.55643, -11.2669,
    97.5987, 98.5616, 98.2238, 96.4971, 93.1976, 88.0346, 81.0408, 72.1464, 61.4075, 49.7190, 37.1708, 24.1329, 11.8242, 2.30563, -5.77136,
    102.322, 103.200, 102.868, 101.240, 98.1458, 93.3237, 86.8197, 78.5789, 68.6408, 57.7748, 45.9324, 33.1789, 20.1420, 8.59809, -0.0622518,
    106.740, 107.555, 107.234, 105.696, 102.782, 98.2582, 92.1851, 84.5270, 75.3233, 65.2582, 54.2111, 42.0759, 29.0884, 16.3768, 5.91432,
    111.552, 112.313, 112.011, 110.565, 107.832, 103.605, 97.9632, 90.8941, 82.4480, 73.2414, 63.1179, 51.8744, 39.4906, 26.5556, 14.3424,
    118.654, 119.366, 119.102, 117.779, 115.275, 111.423, 106.328, 100.017, 92.5655, 84.5224, 75.7244, 65.9275, 54.9517, 42.9619, 30.4554,
    125.733, 126.435, 126.218, 124.998, 122.667, 119.097, 114.423, 108.711, 102.065, 94.9921, 87.3440, 78.8913, 69.4270, 58.9638, 47.6611,
    132.566, 133.298, 133.138, 131.988, 129.762, 126.361, 121.956, 116.653, 110.587, 104.236, 97.4706, 90.0879, 81.9000, 72.8828, 63.0837,
    139.712, 140.530, 140.442, 139.330, 137.126, 133.770, 129.484, 124.419, 118.742, 112.914, 106.816, 100.272, 93.1196, 85.3351, 76.9343,
    148.260, 149.285, 149.313, 148.176, 145.840, 142.314, 137.915, 132.864, 127.364, 121.868, 116.253, 110.357, 104.041, 97.2889, 90.1124,
    156.343, 157.743, 157.938, 156.660, 153.949, 149.951, 145.145, 139.829, 134.234, 128.801, 123.383, 117.811, 111.954, 105.800, 99.3587,
    162.489, 164.409, 164.816, 163.270, 159.977, 155.326, 149.988, 144.309, 138.509, 133.006, 127.616, 122.155, 116.490, 110.608, 104.516,
    167.232, 169.864, 170.565, 168.571, 164.483, 159.087, 153.215, 147.188, 141.184, 135.587, 130.175, 124.749, 119.169, 113.419, 107.506,
    171.164, 174.281, 175.125, 173.038, 168.273, 162.005, 155.598, 149.249, 143.060, 137.371, 131.925, 126.507, 120.971, 115.298, 109.492
],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [5.34300, 170.994],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [-88.5449, 77.1061],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [5.34300, 170.994],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1148.20, 1756.80],

##
## Lift Cylinders
##

# Number of lift cylinders.
"NoOfLiftCyls" => 2,

# Lift cylinder bore diameter, in mm.
"LiftCylBoreDia" => 127.000,

# Lift cylinder rod diameter, in mm.
"LiftCylRodDia" => 76.2000,

##
## Tilt Cylinders
##

# Number of tilt cylinders.
"NoOfTiltCyls" => 1,

# Tilt cylinder bore diameter, in mm.
"TiltCylBoreDia" => 150.000,

# Tilt cylinder rod diameter, in mm.
"TiltCylRodDia" => 95.0000,

##
## Tool
##

# Tool's length between B and C pins, in mm.
"ToolBcLen" => 516.188,

# Tool's angle between line BC and tool's X-axis, in deg.
"ToolBcAngle" => 93.8879,

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
"LoaderBktPayldTrgtWt" => 5.06944,

# The capacity of the scale used for Legal for Trade Max, in tonnes.
"ScaleWeightCapacity" => 7.00000,

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
"KgPerLiftKpaAtMidExtension" => 0.559910,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 1860.37,

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
"LiftCylExtPctAxis" => [0.00000, 15.4122, 31.6607, 51.4934, 62.8435, 69.8925, 75.6272, 80.4062, 84.4683, 87.9331, 91.0394, 93.6679, 96.0573, 98.2079, 100.000],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0.00000, 5.91522, 11.0089, 15.6096, 19.8817, 23.8252, 27.6043, 31.0549, 34.3411, 37.4630, 40.5849, 43.5426, 46.6645, 50.2793, 55.2087, 64.2458, 72.7900, 81.3342, 91.5215, 100.000],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [
    -88.6868, -178.009, -68.1227, 213.491, 290.227, 178.299, -47.4601, -312.966, -590.676, -886.243, -1237.84, -1669.69, -2348.16, -4211.07, -5619.15,
    -157.343, -213.760, -99.7704, 215.503, 409.889, 433.399, 296.686, 36.9225, -266.725, -568.591, -883.920, -1211.78, -1604.62, -2124.13, -2879.76,
    -187.624, -233.562, -127.575, 180.946, 426.306, 552.702, 551.541, 390.685, 102.914, -229.177, -568.744, -890.309, -1232.79, -1619.59, -2053.11,
    -201.085, -245.052, -150.130, 136.578, 392.131, 572.459, 677.327, 652.667, 469.204, 161.491, -208.437, -562.134, -914.081, -1275.20, -1637.37,
    -206.124, -251.504, -167.741, 92.8522, 337.837, 536.943, 702.939, 788.338, 742.570, 542.203, 204.430, -175.973, -565.846, -946.673, -1300.31,
    -206.557, -254.549, -180.807, 54.4809, 280.204, 477.536, 669.038, 821.099, 887.430, 822.088, 594.975, 250.487, -162.421, -583.276, -961.919,
    -204.350, -255.292, -190.441, 21.4136, 224.833, 409.888, 604.964, 789.502, 929.394, 979.549, 893.921, 659.245, 289.424, -151.098, -568.163,
    -200.723, -254.386, -196.874, -4.89535, 177.359, 346.360, 532.992, 726.159, 903.382, 1028.60, 1060.50, 957.529, 697.234, 301.554, -129.026,
    -196.199, -252.302, -201.035, -26.3141, 136.358, 288.257, 460.749, 649.238, 840.477, 1008.48, 1123.29, 1136.45, 1011.39, 725.604, 339.800,
    -191.149, -249.346, -203.339, -43.4137, 101.800, 237.216, 393.483, 570.177, 760.638, 947.437, 1112.04, 1209.41, 1205.42, 1055.94, 772.545,
    -185.511, -245.533, -204.157, -57.4906, 71.6818, 191.213, 330.319, 491.221, 671.846, 861.553, 1051.43, 1203.79, 1294.00, 1275.20, 1125.02,
    -179.721, -241.198, -203.662, -68.2141, 47.1727, 152.636, 275.669, 419.964, 586.288, 768.729, 965.196, 1145.63, 1295.58, 1374.94, 1346.51,
    -173.205, -235.918, -201.898, -76.9841, 25.3387, 117.218, 224.161, 350.657, 499.273, 667.538, 858.207, 1048.55, 1233.35, 1382.80, 1456.25,
    -165.206, -228.954, -198.376, -84.1563, 4.85013, 82.7242, 172.660, 279.437, 406.643, 554.266, 728.217, 912.600, 1109.81, 1301.36, 1450.34,
    -153.591, -218.062, -191.213, -89.3514, -15.6984, 45.9775, 115.906, 198.670, 298.157, 415.941, 559.359, 718.993, 902.603, 1102.82, 1291.86,
    -130.277, -193.955, -171.561, -87.3968, -35.2164, 4.20463, 46.5588, 95.4728, 154.065, 224.301, 312.175, 414.212, 538.966, 687.605, 846.450,
    -105.538, -165.682, -145.393, -74.6082, -37.3907, -12.4804, 12.4172, 40.0111, 72.4408, 111.145, 159.859, 217.249, 289.028, 377.386, 475.932,
    -77.1911, -130.146, -110.824, -53.4508, -28.6840, -14.3229, -1.21131, 12.5415, 28.2450, 46.7580, 70.0077, 97.5198, 132.259, 175.649, 224.968,
    -35.4450, -70.1050, -53.6407, -20.4512, -10.5113, -5.85283, -2.08326, 1.61435, 5.70938, 10.4878, 16.4884, 23.6256, 32.7110, 44.1790, 57.3760,
    9.04847, 36.1009, 14.8480, 2.72149, 1.16548, 0.552849, 0.0431480, -0.497793, -1.14190, -1.93430, -2.96696, -4.22749, -5.86289, -7.95860, -10.4002
],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 5.06944,

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
"TiltCylExtThresholdStrict" => 97.0940,

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
  "InternalMsn" => "CAT63700",
  "Make" => "CAT",
  "Model" => "963",
  "ModelDetail" => "963",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x00BC,
  "ST_chg_lvl" => 0x0001,
}
