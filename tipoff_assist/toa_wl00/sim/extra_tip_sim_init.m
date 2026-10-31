% How to run:
% Go to top level toa_wl00 as current directory.
% Set sim, pkg, sys, c_src at least as on the matlab path.
% Run the model
propertySet = 'MK800100';
toa_wl00_init
switch propertySet
    case 'MK800100'
        load('data\extra_tip_example\extra_tip_example_MK800100_20200317.mat');
        time = t27;
        time2 = t27;
        time3 = t28;
        tiltHePress = WeighDebug_TOAtilt_he_pressure_t27;
        tiltRePress = WeighDebug_TOAtilt_re_pressure_t27;
        liftCylPress = WeighDebug_LiftCylPres_t27;
        imuX = WeighDebug_TOAeef_imu_accelX_t27;
        imuY = WeighDebug_TOAeef_imu_accelY_t27;
        imuZ = WeighDebug_TOAeef_imu_accelZ_t27;
        liftAngle = WeighDebug_TOAlift_angle_t27;
        tiltExt = WeighDebug_TOAtilt_extension_t27;
        steerAng = WeighDebug_TOAsteering_angle_t27;
        liftCylLength = WeighDebug_LiftCylNormLen_t27;
        unlatchTrigger = WeighDebug_TOAunlatch_trigger_t27;
        liftCmd = WeighDebug_TOAlift_valve_cmd_t27;
        tiltCmd = WeighDebug_TOAtilt_valve_cmd_t27;
        bucketAngle = WeighDebug_TOAbucket_angle_t27;
        payloadTarget = TOAtestPts_toa_payload_target_final_t27;
        toolMass = WeighDebug_TOAtool_mass_t28;
        % Simulation times
        start_time = 139;
        stop_time = 2664;
end