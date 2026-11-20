propertySet = 'WLJ00161';
scenario = 'full2';  % May be empty string if there is only one scenario
toa_wl00_init
switch propertySet
    case 'MK800100'
        load('data\imu_pitch_cal_sim_data.mat');
        time = TIME;
        time2 = TIME;
        tiltHePress = WeighDebug_TOAtilt_he_pressure;
        tiltRePress = WeighDebug_TOAtilt_re_pressure;
        liftCylPress = WeighDebug_LiftCylPres;
        imuX = WeighDebug_TOAeef_imu_accelX;
        imuY = WeighDebug_TOAeef_imu_accelY;
        imuZ = WeighDebug_TOAeef_imu_accelZ;
        liftAngle = WeighDebug_TOAlift_angle;
        tiltExt = WeighDebug_TOAtilt_extension;
        steerAng = WeighDebug_TOAsteering_angle;
        liftCylLength = WeighDebug_LiftCylLenghtNorm_Val;
        % Simulation times
        start_time = 467;
        stop_time = 640;
        % Trigger times in the data s=raise/lower "set", c=func call time
        s1c1 = 472;
        s1c2 = 505;
        s1c3 = 548;
        s2c1 = 548;
        s2c2 = 580;
        s2c3 = 636;
    case 'A8P00101'
        load('data\imu_pitch_cal_sim_data_A8P00101.mat');
        time = t;
        time2 = t2;
        tiltHePress = toa_tiltHePress;
        tiltRePress = toa_tiltRePress;
        liftCylPress = toa_inPcsDiffPress;
        imuX = toa_inImuAcclX;
        imuY = toa_inImuAcclY;
        imuZ = toa_inImuAcclZ;
        liftAngle = toa_inRawLiftAng;
        tiltExt = toa_inRawTiltCylExt;
        steerAng = toa_steer_ang_t2;
        liftCylLength = toa_inLiftNormLength_t2 * 100;
        % Simulation times
        start_time = 135;
        stop_time = 282;
        % Trigger times in the data
        %   s=set number, where a set is a consecutive loaded raise & lower
        %   c=point number, where:
        %     1=before slow full raise
        %     2=after slow full raise / before slow full lower
        %     3=after slow full lower / also triggers IMU cal return
        s1c1 = 140;
        s1c2 = 180;
        s1c3 = 210;
        s2c1 = 220;
        s2c2 = 247;
        s2c3 = 280;
    case 'MK900100'
        if strcmp(scenario, 'full')
            load('data\imu_pitch_cal_sim_data_MK900100_20201109_full.mat');
            time = t78;
            time2 = t78;
            tiltHePress = WeighDebug_TOAtilt_he_pressure_t78;
            tiltRePress = WeighDebug_TOAtilt_re_pressure_t78;
            liftCylPress = WeighDebug_LiftCylPres_t78;
            imuX = WeighDebug_TOAeef_imu_accelX_t78;
            imuY = WeighDebug_TOAeef_imu_accelY_t78;
            imuZ = WeighDebug_TOAeef_imu_accelZ_t78;
            liftAngle = WeighDebug_TOAlift_angle_t78;
            tiltExt = WeighDebug_TOAtilt_extension_t78;
            steerAng = WeighDebug_TOAsteering_angle_t78;
            liftCylLength = WeighDebug_LiftCylLenghtNorm_Val_t78;
            % Simulation times
            start_time = 670;
            stop_time = 822;
            % Trigger times in the data
            %   s=set number, where a set is a consecutive loaded raise & lower
            %   c=point number, where:
            %     1=before slow full raise
            %     2=after slow full raise / before slow full lower
            %     3=after slow full lower / also triggers IMU cal return
            s1c1 = 678;
            s1c2 = 715;
            s1c3 = 748;
            s2c1 = 751;
            s2c2 = 789;
            s2c3 = 821;
        elseif strcmp(scenario, 'empty')
            load('data\imu_pitch_cal_sim_data_MK900100_20201109_empty.mat');
            time = t78;
            time2 = t78;
            tiltHePress = WeighDebug_TOAtilt_he_pressure_t78;
            tiltRePress = WeighDebug_TOAtilt_re_pressure_t78;
            liftCylPress = WeighDebug_LiftCylPres_t78;
            imuX = WeighDebug_TOAeef_imu_accelX_t78;
            imuY = WeighDebug_TOAeef_imu_accelY_t78;
            imuZ = WeighDebug_TOAeef_imu_accelZ_t78;
            liftAngle = WeighDebug_TOAlift_angle_t78;
            tiltExt = WeighDebug_TOAtilt_extension_t78;
            steerAng = WeighDebug_TOAsteering_angle_t78;
            liftCylLength = WeighDebug_LiftCylLenghtNorm_Val_t78;
            % Simulation times
            start_time = 195;
            stop_time = 360;
            % Trigger times in the data
            %   s=set number, where a set is a consecutive loaded raise & lower
            %   c=point number, where:
            %     1=before slow full raise
            %     2=after slow full raise / before slow full lower
            %     3=after slow full lower / also triggers IMU cal return
            s1c1 = 196;
            s1c2 = 232;
            s1c3 = 275;
            s2c1 = 276;
            s2c2 = 310;
            s2c3 = 354;
        elseif strcmp(scenario, 'full2')
            load('data\temp.mat');
            time = t194;
            time2 = t194;
            tiltHePress = WeighDebug_TOAtilt_he_pressure_t194;
            tiltRePress = WeighDebug_TOAtilt_re_pressure_t194;
            liftCylPress = WeighDebug_LiftCylPres_t194;
            imuX = WeighDebug_TOAeef_imu_accelX_t194;
            imuY = WeighDebug_TOAeef_imu_accelY_t194;
            imuZ = WeighDebug_TOAeef_imu_accelZ_t194;
            liftAngle = WeighDebug_TOAlift_angle_t194;
            tiltExt = WeighDebug_TOAtilt_extension_t194;
            steerAng = WeighDebug_TOAsteering_angle_t194;
            liftCylLength = WeighDebug_LiftCylLenghtNorm_Val_t194;
            % Simulation times
            start_time = 699;
            stop_time = 828;
            % Trigger times in the data
            %   s=set number, where a set is a consecutive loaded raise & lower
            %   c=point number, where:
            %     1=before slow full raise
            %     2=after slow full raise / before slow full lower
            %     3=after slow full lower / also triggers IMU cal return
            s1c1 = 700;
            s1c2 = 730;
            s1c3 = 760;
            s2c1 = 761;
            s2c2 = 795;
            s2c3 = 827;
        end
    case 'WLJ00161'
        load('data\WLJ00161_bad_imu_cal_orig.mat');
        time = t194;
        time2 = t194;
        tiltHePress = WeighDebug_TOAtilt_he_pressure_t194;
        tiltRePress = WeighDebug_TOAtilt_re_pressure_t194;
        liftCylPress = WeighDebug_LiftCylPres_t194;
        imuX = WeighDebug_TOAeef_imu_accelX_t194;
        imuY = WeighDebug_TOAeef_imu_accelY_t194;
        imuZ = WeighDebug_TOAeef_imu_accelZ_t194;
        liftAngle = WeighDebug_TOAlift_angle_t194;
        tiltExt = WeighDebug_TOAtilt_extension_t194;
        steerAng = WeighDebug_TOAsteering_angle_t194;
        liftCylLength = WeighDebug_LiftCylLenghtNorm_Val_t194;
        % Simulation times
        start_time = 504;
        stop_time = 646;
        % Trigger times in the data
        %   s=set number, where a set is a consecutive loaded raise & lower
        %   c=point number, where:
        %     1=before slow full raise
        %     2=after slow full raise / before slow full lower
        %     3=after slow full lower / also triggers IMU cal return
        s1c1 = 515;
        s1c2 = 548;
        s1c3 = 579;
        s2c1 = s1c3 + 1;
        s2c2 = 616;
        s2c3 = 646;       
end