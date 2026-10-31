disp('*** toa_wl00_init.m is initializing ***')
% disp('....')
% run('toa_wl00_signals.m')
disp('....')

% Builds the S-Functions for payload and others
build_sfunc_mass_and_dist
disp('*** toa_wl00_init.m is done with build_sfunc_mass_and_dist ***')
build_sfunc_tilt_sens_to_bucket_ang
disp('*** toa_wl00_init.m is done with build_sfunc_tilt_sens_to_bucket_ang ***')

% Constants
timestep = 0.02;
g = 9.80665;


% The payload target to remain in the bucket after tipping (tonnes)
toa_payload_target_ov_val = Cat.Data;
toa_payload_target_ov_val.Value = 0.0;

% The minimum bucket payload target considered achievable (% rated payload)
toa_payloadTargetMin = Cat.Data;
toa_payloadTargetMin.Value = 5.0;

% Live payload low-pass filter cutoff (Hz)
toa_liveLpfCutoffHz = Cat.Data;
toa_liveLpfCutoffHz.Value = 0.6;

% Spill rate low-pass filter cutoff (Hz)
toa_liveSpillRateLpfCutoffHz = Cat.Data;
toa_liveSpillRateLpfCutoffHz.Value = 0.5;

% Send to CPM live payload low-pass filter cutoff (Hz)
toa_sendCpmLiveLpfCutoffHz = Cat.Data;
toa_sendCpmLiveLpfCutoffHz.Value = 0.955;

% IMU low pass filter cutoff frequency, Hz
toa_imu_lpf_cutoff_hz = Cat.Data;
toa_imu_lpf_cutoff_hz.Value = 0.5;
% Overrides the IMU-determined gravity vector when not zero (m/s^2)
toa_grav_x_ov_val = Cat.Data;
toa_grav_x_ov_val.Value = 0;
toa_grav_y_ov_val = Cat.Data;
toa_grav_y_ov_val.Value = 0;

% Pseudo-Frictionless Weigh
% Don't allow measurement when we could be touching the ground
% Ground condition 1 - These are AND'ed
toa_mcGroundCombLiftNormAng = Cat.Data;
toa_mcGroundCombLiftNormAng.Value = 0.12;	% Decimal percent
toa_mcGroundCombBucketAng = Cat.Data;
toa_mcGroundCombBucketAng.Value = 0.0;      % Degrees
% Ground condition 2 - This acts alone
toa_mcGroundLiftNormAng = Cat.Data;
toa_mcGroundLiftNormAng.Value = 0.07;       % Decimal percent
% Time limit to latch to avoid pressure decay effects (sec)
toa_pfw_time_limit = Cat.Data;
toa_pfw_time_limit.Value = 4.5;
% Cutoff frequency for live payload that's used as initial value when
% starting PFW measurement
toa_pfwResetLpfCutoffHz = Cat.Data;
toa_pfwResetLpfCutoffHz.Value = 0.6;
toa_pfwResetStatsBound = Cat.Data;
toa_pfwResetStatsBound.Value = 0.3;
toa_pfwResetStatsConf = Cat.Data;
toa_pfwResetStatsConf.Value = 0.997;
% Statistics estimation
% Low-pass filter cutoff (Hz)
toa_pfwLpfCutoffHz = Cat.Data;
toa_pfwLpfCutoffHz.Value = 0.6;
% Minimum duration of acceptable conditions before having confidence
toa_pfw_min_meas_duration = Cat.Data;
toa_pfw_min_meas_duration.Value = 1.0;
% Normalized angle and length considered too close for measurement
toa_pfwTravelExtentUpper = Cat.Data;
toa_pfwTravelExtentUpper.Value = 0.97;
toa_pfwTravelExtentLower = Cat.Data;
toa_pfwTravelExtentLower.Value = 0.03;
% Assume payload is secure when tilt norm ang or len are above this
toa_pfwTiltNormRackThresh = Cat.Data;
toa_pfwTiltNormRackThresh.Value = 0.97;

% Noise amplitude we expect in the bucket angle signal (degrees)
toa_expectedBucketAngNoise = Cat.Data;
toa_expectedBucketAngNoise.Value = 1.0; % Degrees

% Bucket angle threshold above which we are sure material won't slide
% out against the bucket floor.  Note bucket floor angle and gravity
% affect this.
toa_noSlidingAngle = Cat.Data;
toa_noSlidingAngle.Value = 7.0;         % Degrees

% Angle above the observed minimum bucket angle for a load that makes us
% sure the load won't significantly fall out due to repose breakdown
toa_reposeMarginAng = Cat.Data;
toa_reposeMarginAng.Value = 6.0;        % Degrees

% Send to CPM
% The minimum 3 sigma precision considered good enough to send PFW weight to CPM
toa_sendToCpmMinPrecision = Cat.Data;
toa_sendToCpmMinPrecision.Value = 0.02; % Decimal percent of rated load

% Tool properties
toa_toolBcLength = Cat.Parameter;   % Length between the B and C pins, mm
toa_toolBcAngle = Cat.Parameter;    % Angle between ground and BC when tool is flat on ground
toa_tiltNumCyl = Cat.Parameter;
toa_tiltBoreDia = Cat.Parameter;
toa_tiltRodDia = Cat.Parameter;
toa_liftBoreDia = Cat.Parameter;
toa_liftRodDia = Cat.Parameter;
toa_ratedPayload = Cat.Parameter;
toa_appNumber = Cat.Parameter;

% Rotation from nominal IMU placement coord sys to nominal EEF coord sys
% EEF X = IMU -Z, Y = X, Z = -Y when IMU axis orientation is in "Z-Up" mode
% and IMU is mounted in AU2020 position on left outer pant leg with
% connector facing down.
toa_imuBasicOrient = Cat.Data;
toa_imuBasicOrient.Value = [0,0,-1;1,0,0;0,-1,0];

% Allow overriding the pitch calibration value for development
% 360 = override disabled
% Any other value = override enabled
toa_imuCalPitchAngOv = Cat.Data;
toa_imuCalPitchAngOv.Value = 360;

% Machine-Specific Properties
% When built into Analysis ECM, these values are populated by other means
if ~exist('propertySet','var')
    propertySet = 'MK800100';
end
switch propertySet
    case 'A8P00101'
        % A8P00101 - 972M Std w/ non-heavy-lift cylinders
        % IMU cal pitch ang value determined to be -2.5
        toa_tiltNumCyl.Value = 1;
        toa_tiltBoreDia.Value = 190;
        toa_tiltRodDia.Value = 100;
        toa_liftBoreDia.Value = 158.8;
        toa_liftRodDia.Value = 88.9;
        toa_toolBcLength.Value = 434;
        % Rated load (tonnes)
        % Reference: https://arlgitgisp01.ecorp.cat.com/mwl/mwl_matlab_lib/blob/1969485c73ccad786be5cf5e317795289ce85df5/ZBarLib/GeneratePayloadConfig.m#L237
        toa_ratedPayload.Value = 8.366;
        toa_appNumber.Value = uint32(9972999);
    case 'EJB00165'
        % EJB00165 - 962M Std - 347-5538 tilt cylinder, 347-5536 lift cylinder
        % IMU cal pitch ang value determined to be -7.7
        toa_tiltNumCyl.Value = 1;
        toa_tiltBoreDia.Value = 170;
        toa_tiltRodDia.Value = 85;
        toa_liftBoreDia.Value = 150;
        toa_liftRodDia.Value = 85;
        toa_toolBcLength.Value = 434.0;
        toa_imuBasicOrient.Value = [0 0 1; 1 0 0; 0 1 0];
        % 3.3 m3 rated bucket volume from mwl_matlab_lib/ZVarLib * 1780 kg/m3 standard density / 1000 kg/t
        toa_ratedPayload.Value = 3.3 * 1780 / 1000;
    case 'MK800100'
        % MK800100 - 982M Std - ***-**** tilt cylinder, ***-**** lift cylinder
        % IMU cal pitch ang value determined to be -2
        toa_tiltNumCyl.Value = uint8(2);
        toa_tiltBoreDia.Value = 130;
        toa_tiltRodDia.Value = 95;
        toa_liftBoreDia.Value = 190;
        toa_liftRodDia.Value = 100;
        toa_toolBcLength.Value = 510;
        % 7.0 m3 rated bucket volume from mwl_matlab_lib/ZVarLib * 1780 kg/m3 standard density / 1000 kg/t
        % Ref: https://arlgitgisp01.ecorp.cat.com/mwl/mwl_matlab_lib/blob/21266f8e5325939f8f6acd280a2f873585829556/ZBarLib/GeneratePayloadConfig.m#L237
        % Ref: https://arlgitgisp01.ecorp.cat.com/mwl/mwl_matlab_lib/blob/21266f8e5325939f8f6acd280a2f873585829556/ZBarLib/data_982M_STD.m#L42
        toa_ratedPayload.Value = 6.1 * 1780 / 1000;
        toa_appNumber.Value = uint32(82700);
    case 'MK900100'
        % MK900100 - 980 PS HMU LRC AU2020
        % Machine was built from MGD00201, which has a 371-9390 arrangement with a std lift arm assembly 416-6484
        % Cylinder information from: https://arlgitgisp01.ecorp.cat.com/mwl/mwl_matlab_lib/blob/21266f8e5325939f8f6acd280a2f873585829556/ZBarLib/data_980M_STD.m#L50
        toa_tiltNumCyl.Value = 2;
        toa_tiltBoreDia.Value = 130;
        toa_tiltRodDia.Value = 95;
        toa_liftBoreDia.Value = 180;
        toa_liftRodDia.Value = 90;
        toa_toolBcLength.Value = 472.9693;
        % Rated load (tonnes)
        % 5.6 m3 rated bucket volume from mwl_matlab_lib/ZVarLib * 1780 kg/m3 standard density / 1000 kg/t
        % Reference: https://arlgitgisp01.ecorp.cat.com/mwl/mwl_matlab_lib/blob/21266f8e5325939f8f6acd280a2f873585829556/ZBarLib/GeneratePayloadConfig.m#L237
        % Reference: https://arlgitgisp01.ecorp.cat.com/mwl/mwl_matlab_lib/blob/21266f8e5325939f8f6acd280a2f873585829556/ZBarLib/data_980M_STD.m#L50
        toa_ratedPayload.Value = 5.6 * 1780 / 1000;
        toa_appNumber.Value = 80700;
    case 'WL900100'
        % WL900100 - AU2020 testbed w/ 962M Std linkage
        % 962 PZ linkage with standard cylinders. The rear half of the machine and the linkage is from EJB00901. The front frame is from EJB00170.
        toa_tiltNumCyl.Value = 1;
        toa_tiltBoreDia.Value = 170;
        toa_tiltRodDia.Value = 85;
        toa_liftBoreDia.Value = 150;
        toa_liftRodDia.Value = 85;
        toa_toolBcLength.Value = 434.0;
        % 3.3 m3 rated bucket volume from mwl_matlab_lib/ZVarLib * 1780 kg/m3 standard density / 1000 kg/t
        toa_ratedPayload.Value = 3.3 * 1780 / 1000;
    case 'WLJ00161'
        % WLJ00161 - AU2020 pilot 962M PZ STD
        toa_appNumber.Value = 62700;
        toa_tiltNumCyl.Value = 1;
        toa_tiltBoreDia.Value = 170;
        toa_tiltRodDia.Value = 85;
        toa_liftBoreDia.Value = 150;
        toa_liftRodDia.Value = 85;
        toa_toolBcLength.Value = 434.015;
        % 3.3 m3 rated bucket volume from mwl_matlab_lib/ZVarLib * 1780 kg/m3 standard density / 1000 kg/t
        toa_ratedPayload.Value = 3.3 * 1780 / 1000;
    otherwise
        disp('No matching propertySet (serial number) was specified!')
        return
end

% Define enumerated types
TipAssistPayloadTypeTypeDef
TipAssistSendCpmStatusTypeDef
TipAssistSecPfwStatusTypeDef
TipAssistUnsecPfwStatusTypeDef
TipAssistLiveWeighStatusTypeDef
TipAssistCpmTipOffModeTypeDef
TipAssistAdvEcmErrorTypeDef

disp('** toa_wl00_init.m done initializing **')
