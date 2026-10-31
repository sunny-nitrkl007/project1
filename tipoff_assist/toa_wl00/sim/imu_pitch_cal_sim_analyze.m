% This must be copied and pasted into the command line at a debug prompt
% inside the imu cal simulation during the getPitchOffset step.

f1 = figure('Name', 'Lift Pressure (kPa)');
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs), raiseBufLiftPress(raiseLaSlopePointsIdxs),lowerBufLiftAngle(lowerLaSlopePointsIdxs), lowerBufLiftPress(lowerLaSlopePointsIdxs))
f2 = figure('Name', 'Tilt Head-End Pressure (kPa)');
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs), raiseBufTiltHePress(raiseLaSlopePointsIdxs),lowerBufLiftAngle(lowerLaSlopePointsIdxs), lowerBufTiltHePress(lowerLaSlopePointsIdxs))
f3 = figure('Name', 'Tilt Rod-End Pressure (kPa)');
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs), raiseBufTiltRePress(raiseLaSlopePointsIdxs),lowerBufLiftAngle(lowerLaSlopePointsIdxs), lowerBufTiltRePress(lowerLaSlopePointsIdxs))
f4 = figure('Name', 'Tilt Extension');
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs), raiseBufTiltExt(raiseLaSlopePointsIdxs),lowerBufLiftAngle(lowerLaSlopePointsIdxs), lowerBufTiltExt(lowerLaSlopePointsIdxs))

plot(slopePointsLiftAngles, slopePointWeightsFilt)
hold
plot(bufLiftAngle(1:endDataIdx), weights(1:endDataIdx))

figure('Name', sprintf('Lift Angle vs TOA Stuff Weight, Cal=%0.2f', searchPitchOffset))
hold
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs),searchRaiseWeight(raiseLaSlopePointsIdxs))
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs),searchLowerWeight(fliplr(lowerLaSlopePointsIdxs)))
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs),(searchRaiseWeight(raiseLaSlopePointsIdxs) + searchLowerWeight(fliplr(lowerLaSlopePointsIdxs)))/2)
% plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs),(searchRaiseWeight(raiseLaSlopePointsIdxs) + searchLowerWeight(lowerLaSlopePointsIdxs))/2)
hold off

% Basic input data plots
figure('Name', 'Lift Angle vs Lift Press')
hold on
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs), raiseBufLiftPress(raiseLaSlopePointsIdxs))
plot(lowerBufLiftAngle(lowerLaSlopePointsIdxs), lowerBufLiftPress(lowerLaSlopePointsIdxs))
hold off

figure('Name', 'Lift Angle vs Tilt HE Press')
hold on
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs), raiseBufTiltHePress(raiseLaSlopePointsIdxs))
plot(lowerBufLiftAngle(lowerLaSlopePointsIdxs), lowerBufTiltHePress(lowerLaSlopePointsIdxs))
hold off

figure('Name', 'Lift Angle vs Tilt RE Press')
hold on
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs), raiseBufTiltRePress(raiseLaSlopePointsIdxs))
plot(lowerBufLiftAngle(lowerLaSlopePointsIdxs), lowerBufTiltRePress(lowerLaSlopePointsIdxs))
hold off

figure('Name', 'Lift Angle vs. Tilt Ext')
hold on
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs), raiseBufTiltExt(raiseLaSlopePointsIdxs))
plot(lowerBufLiftAngle(lowerLaSlopePointsIdxs), lowerBufTiltExt(lowerLaSlopePointsIdxs))
hold off

figure('Name', 'Lift Angle vs. Steering Angle')
hold on
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs), raiseBufSteerAngle(raiseLaSlopePointsIdxs))
plot(lowerBufLiftAngle(lowerLaSlopePointsIdxs), lowerBufSteerAngle(lowerLaSlopePointsIdxs))
hold off

figure('Name', 'Lift Angle vs. IMU')
hold on
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs), raiseBufImuX(raiseLaSlopePointsIdxs))
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs), raiseBufImuY(raiseLaSlopePointsIdxs))
plot(raiseBufLiftAngle(raiseLaSlopePointsIdxs), raiseBufImuZ(raiseLaSlopePointsIdxs))
hold off