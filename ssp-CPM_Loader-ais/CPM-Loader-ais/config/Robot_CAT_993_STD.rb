##

## CAT 993 - Std Lift
##
MachineSpecificConfig = {

##
## Lift Kinematics
##

# Normalized, calibrated, lift sensor axis of the lift angle table, in %.
"inLiftDc" => [0.000000, 100.000],

# Lift angle axis of the lift angle table, in degrees.
"outLiftAngle" => [-40.79, 40.32],

# Lift angle axis of the lift cylinder length table, in degrees.
"inLiftAngle" => [-40.79,-32.05,-25.33,-19.39,-13.90,-8.70,-3.73,1.10,5.79,10.37,14.84,19.25,23.59,27.86,32.06,36.24,40.32],


# Lift cylinder length axis of the lift cylinder length table, in mm.
"outLiftCylLen" => [2527.0,2762.0,2938.0,3089.0,3224.0,3347.0,3460.0,3565.0,3662.0,3752.0,3835.0,3912.0,3983.0,4048.0,4107.0,4161.0,4209.0],

# Lift angle limits, in degrees.
"KnmaticsLiftAngleMinMax" => [-40.79, 40.32],

# Lift cylinder length limits, in mm.
"KnmaticsLiftCylLenMinMax" => [2527.0,4209.0],

##
## Tilt Kinematics
##

# Normalized, calibrated, tilt sensor axis of the tilt angle table, in % 

"inTiltDc" => [0.00,3.44,6.60,9.71,13.16,18.35,26.57,32.01,37.52,43.54,50.49,59.03,72.02,87.44,93.71,97.59,100.00],


# Tilt angle axis of the tilt angle table, in degrees. Angle ABC where larger 
# angles are rack.

"outTiltAngle" => [6.61,8.79,12.53,18.04,26.11,40.69,64.47,78.42,90.7,102.23,113.57,125.47,141.16,159.38,168.21,175.12,180.84],

# Tilt angle axis of the tilt cylinder length table, in degrees.
"xTiltAngle" => [6.61,8.04,11.04,16.84,28.44,54.29,72.29,86.59,98.79,109.69,119.99,130.64,146.64,157.99,166.34,173.74,180.84],

# Lift angle axis of the tilt cylinder length table, in degrees.
"yLiftAngle" => [-40.79,-36.54,-32.39,-28.29,-24.24,-20.19,-16.14,-12.04,-7.84,-3.49,1.06,5.86,10.96,16.56,22.86,30.31,40.31],

# Tilt cylinder length axis of the tilt cylinder length table, in mm.
"outTiltCylLen" => [1625.6, 1602.6, 1585.9, 1575.1, 1570.3, 1571.3, 1578.1, 1590.8, 1609.7, 1635.2, 1667.8, 1708.3, 1757.4, 1817.4, 1891.2, 1984.9, 2117.7,
1639.3, 1617.5, 1601.9, 1592.2, 1588.5, 1590.6, 1598.5, 1612.2, 1632.1, 1658.5, 1692.1, 1733.4, 1783.2, 1843.8, 1918.2, 2012.4, 2145.5,
1658.3, 1637.7, 1623.4, 1615.1, 1612.7, 1616.0, 1625.1, 1640.0, 1661.0, 1688.5, 1723.0, 1765.2, 1815.9, 1877.3, 1952.3, 2047.0, 2180.5,
1684.3, 1665.3, 1652.5, 1645.7, 1644.7, 1649.5, 1660.0, 1676.2, 1698.4, 1727.0, 1762.6, 1805.9, 1857.4, 1919.6, 1995.3, 2090.6, 2224.5,
1725.4, 1708.4, 1697.5, 1692.6, 1693.5, 1700.0, 1712.2, 1730.0, 1753.7, 1783.8, 1820.7, 1865.1, 1917.7, 1980.8, 2057.3, 2153.3, 2287.6,
1813.6, 1799.6, 1791.8, 1789.8, 1793.5, 1802.8, 1817.4, 1837.6, 1863.5, 1895.6, 1934.3, 1980.4, 2034.5, 2098.9, 2176.5, 2273.3, 2408.1,
1888.1, 1876.1, 1870.1, 1869.9, 1875.2, 1886.0, 1902.1, 1923.6, 1950.7, 1983.9, 2023.7, 2070.6, 2125.5, 2190.6, 2268.7, 2365.9, 2501.0,
1962.7, 1952.1, 1947.5, 1948.6, 1955.2, 1967.1, 1984.2, 2006.7, 2034.6, 2068.6, 2109.0, 2156.6, 2211.9, 2277.5, 2356.0, 2453.4, 2588.7,
2042.2, 2032.8, 2029.3, 2031.4, 2038.9, 2051.7, 2069.6, 2092.7, 2121.3, 2155.8, 2196.8, 2244.8, 2300.4, 2366.3, 2445.0, 2542.6, 2677.9,
2129.2, 2120.8, 2118.2, 2121.1, 2129.4, 2142.8, 2161.3, 2185.0, 2214.0, 2248.9, 2290.1, 2338.4, 2394.2, 2460.2, 2539.1, 2636.8, 2772.1,
2228.0, 2220.4, 2218.5, 2222.0, 2230.8, 2244.7, 2263.6, 2287.5, 2316.8, 2351.9, 2393.3, 2441.6, 2497.6, 2563.6, 2642.4, 2740.1, 2875.5,
2347.7, 2340.6, 2339.1, 2343.1, 2352.2, 2366.3, 2385.3, 2409.4, 2438.7, 2473.8, 2515.1, 2563.4, 2619.2, 2685.0, 2763.7, 2861.3, 2996.6,
2550.7, 2543.7, 2542.4, 2546.2, 2555.2, 2569.1, 2587.8, 2611.4, 2640.3, 2674.8, 2715.6, 2763.3, 2818.5, 2883.8, 2961.9, 3059.0, 3194.0,
2692.2, 2684.9, 2683.1, 2686.5, 2695.0, 2708.3, 2726.4, 2749.4, 2777.7, 2811.5, 2851.6, 2898.6, 2953.1, 3017.8, 3095.3, 3192.0, 3326.6,
2781.9, 2774.3, 2772.1, 2775.1, 2783.0, 2795.9, 2813.5, 2836.0, 2863.6, 2896.9, 2936.5, 2982.9, 3036.9, 3101.1, 3178.2, 3274.4, 3408.8,
2845.4, 2837.4, 2834.9, 2837.5, 2845.0, 2857.4, 2874.6, 2896.7, 2923.9, 2956.8, 2995.9, 3041.9, 3095.5, 3159.2, 3235.9, 3331.8, 3466.0,
2889.7, 2881.4, 2878.5, 2880.8, 2888.1, 2900.2, 2917.0, 2938.7, 2965.6, 2998.2, 3036.9, 3082.6, 3135.9, 3199.3, 3275.8, 3371.4, 3505.5],

# Tilt angle axis of the bucket angle table, in degrees.
"inTiltAngle" => [6.61, 180.84],

# Bucket angle axis of the bucket angle table, in degrees.
"outBktAngle" => [ -90.63, 83.60],

# Tilt angle ABC limits, in degrees.
"KnmaticsTiltAngleMinMax" => [6.61, 180.84],

# Tilt cylinder length limits, in mm.
"KnmaticsTiltCylLenMinMax" => [1845.0,2885.0 ],

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
"KgPerLiftKpaAtMidExtension" => 2.9052,

# The lift he pressure necessary to hold the linkage stationary at full rack,
# and at 50% lift cylinder extension, assuming the bucket was massless, rod-end
# is at atmospheric pressure, and there is no friction. Used to estimate the
# empty bucket weight.
"LiftKpaNoBucketMidExtension" => 3210.8,

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
"LiftCylExtPctAxis" => [0.0,15.041617,31.926278,50.356718,62.663496,70.035672,75.862069,80.618312,84.661118,88.109394,91.141498,93.757432,96.076100,98.156956,100.0],

# Tilt cylinder extension axis for the tilt compensation gain table, in %.
"TiltCylExtPctAxis" => [0,5.769231,10.865385,15.480769,19.807692,23.846154,27.596154,31.25,34.711538,37.980769,41.153846,44.134615,47.211538,50.769231,55.673077,64.134615,71.923077,79.903846,89.423077,100],

# Tilt compensation gain table. Lift cylinder pressure delta per tonne of
# payload (kPa / tonne)
"TiltCompGainData" => [-24.604492, -39.349006, -15.181500, 42.766099, 72.340076, 58.552864, 21.008310, -24.501928, -73.630737, -127.661856, -192.282975, -273.837390, -394.204761, -649.704355, -857.851820,
-38.015743,	-45.399688,	-21.489279,	39.179188, 91.217070, 105.667860, 85.789815, 41.402105,	-12.581517,	-68.025522,	-126.624148, -190.550344, -266.822536, -367.519984,	-520.925052,
-42.551026,	-48.176123,	-26.866214,	29.939201, 89.714701, 125.569189, 134.165800, 109.387869, 58.938974, -1.534407,	-64.240568,	-126.796809, -193.678789, -270.681559, -364.727186,
-43.693115,	-49.435478,	-31.059447,	19.993889, 78.898152, 124.628137, 155.579972, 159.069208, 129.409566, 74.305887, 7.121154,	-60.680744,	-128.778412, -200.548144, -279.555080,
-43.422190,	-49.885301,	-34.239477,	10.922534, 65.142188, 112.751260, 155.675154, 182.536052, 181.777069, 148.285361, 88.128865, 16.737150,	-57.193071,	-131.823415, -208.196205,
-42.523164,	-49.836569,	-36.528541,	3.340199, 51.714285, 96.908902,	143.502317,	183.846007,	207.354578,	202.579068,	164.698838,	101.474062,	24.991601, -55.584051, -135.813982,
-41.364583,	-49.474359,	-38.093161,	-2.712392, 39.945676, 80.997658, 126.453930, 172.025646, 210.440689, 230.177052, 220.946714, 179.545853, 112.134863, 29.944041, -55.916746,
-40.053268,	-48.880507,	-39.137875,	-7.650015, 29.661638, 65.974915, 107.871117, 153.500329, 198.899138, 235.238276, 252.184590, 239.788990, 195.167211, 123.311207, 36.784024,
-38.704405,	-48.130959,	-39.729768,	-11.482977, 21.181196, 52.938594, 90.393740, 133.202133, 179.812031, 224.437292, 259.314088, 273.114336, 257.560885, 208.994125, 133.636062,
-37.365471,	-47.276221,	-39.966278,	-14.400535,	14.323188, 41.997863, 74.970632, 113.745342, 158.289090, 205.249832, 249.802199, 282.171857, 293.128861, 273.757093, 221.574341,
-36.021240,	-46.323331,	-39.923253,	-16.635847,	8.692442, 32.735041, 61.451150,	95.791474, 136.605135, 182.264693, 230.390717, 273.691572, 304.529855, 312.892068, 290.327999,
-34.725963,	-45.325687,	-39.658830,	-18.250159,	4.258271, 25.229750, 50.205457,	80.332036, 116.897244, 159.356321, 207.011229, 254.863155, 297.606992, 326.686142, 331.735089,
-33.359585,	-44.197312,	-39.176035,	-19.470960,	0.473923, 18.627837, 40.090338,	66.068074, 98.034746, 136.133228, 180.793522, 228.941593, 277.592957, 320.714890, 348.807778,
-31.743898,	-42.772305,	-38.371694,	-20.376563,	-3.001761, 12.319995, 30.198470, 51.806717,	78.627013, 111.216296, 150.705194, 195.581357, 244.902643, 295.492244, 340.466831,
-29.450525,	-40.599622,	-36.862577,	-20.844385,	-6.420772, 5.667238, 19.423618,	35.893599, 56.392369, 81.652050, 113.091529, 150.394208, 194.193482, 244.022023, 296.619779,
-25.273706,	-36.259667,	-33.245814,	-19.879500,	-9.318070, -1.347706, 7.197889,	17.107579, 29.294303, 44.363485, 63.454707,	86.868359, 115.823271, 151.438597, 193.655232,
-21.089387,	-31.501441,	-28.803252,	-17.377347,	-9.456154, -4.113219, 1.221954,	7.143101, 14.251876, 22.951710,	33.971440, 47.600693, 64.745542, 86.416515,	113.150953,
-16.289156,	-25.609046,	-23.021998,	-13.490946,	-7.804464, -4.431602, -1.344350, 1.890158, 5.641726, 10.147673,	15.807701, 22.800808, 31.640207, 42.930556, 57.092362,
-9.445686, -16.377287,	-13.955361,	-7.373070,	-4.260496, -2.710298, -1.449505, -0.231324, 1.113067, 2.683401,	4.628230, 7.017560,	10.037298, 13.909810, 18.804949,
0.644891, 1.709047,	1.129316, 0.423627,	0.225640, 0.147976,	0.092155, 0.041986,	-0.011374, -0.072752, -0.148480, -0.241686,	-0.360015, -0.512662, -0.706962],

##
## Dig Detection Configuration
##

# The fixed reference for calculating payload ratio for the purposes of dig
# detection and segment identification, in tonnes.
"DigTargetWt" => 27.2,

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
  "InternalMsn" => "CAT93200",
  "Make" => "CAT",
  "Model" => "993",
  "ModelDetail" => "993",
  "Linkage" => "Standard",
  "LinkageConfigurationNumber" => 52
}

DeviceID_J1939 = {
  "MID" => 0x0196,
  "ST_app_num" => 0x01B0,
  "ST_chg_lvl" => 0x0001,
}
