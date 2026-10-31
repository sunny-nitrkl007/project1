% MWL TOA-Advanced Signals

%***********************************************************************************
%                                    INPUTS
%***********************************************************************************

% Signal - Invalidate_Outputs
Invalidate_Outputs                                                         = CatP.Signal;
Invalidate_Outputs.Description			                                 = 'invalidate outputs';
Invalidate_Outputs.PCEType		                                         = 'Input';
Invalidate_Outputs.SignalScope                                             = 'External';
Invalidate_Outputs.ExternalReference.ReferenceMethod                       = 'Direct';
Invalidate_Outputs.ExternalReference.Data.HeaderFile                       = 'toa_wl00_model_if.h';
Invalidate_Outputs.ExternalReference.Data.GlobalVariable                   = 'TOA_invalidate_outputs';
Invalidate_Outputs.DataType                                                = 'boolean';

% Signal - Lift_Valve_Command
Lift_Valve_Command                                                   = CatP.Signal;
Lift_Valve_Command.Description                                       = 'lift valve cmd';
Lift_Valve_Command.PCEType		                                     = 'Input';
Lift_Valve_Command.SignalScope                                       = 'External';
Lift_Valve_Command.ExternalReference.ReferenceMethod                 = 'Direct';
Lift_Valve_Command.ExternalReference.Data.HeaderFile                 = 'toa_wl00_model_if.h';
Lift_Valve_Command.ExternalReference.Data.GlobalVariable             = 'TOA_lift_valve_cmd';
Lift_Valve_Command.DataType                                          = 'single';

% Signal - Tilt_Valve_Command
Tilt_Valve_Command                                                        = CatP.Signal;
Tilt_Valve_Command.Description			                                 = 'tilt valve cmd';
Tilt_Valve_Command.PCEType		                                         = 'Input';
Tilt_Valve_Command.SignalScope                                            = 'External';
Tilt_Valve_Command.ExternalReference.ReferenceMethod                      = 'Direct';
Tilt_Valve_Command.ExternalReference.Data.HeaderFile                      = 'toa_wl00_model_if.h';
Tilt_Valve_Command.ExternalReference.Data.GlobalVariable                  = 'TOA_tilt_valve_cmd';
Tilt_Valve_Command.DataType                                               = 'single';

% Signal - Tilt_Extension
Tilt_Extension                                                 = CatP.Signal;
Tilt_Extension.Description			                         = 'tilt extension';
Tilt_Extension.PCEType		                                 = 'Input';
Tilt_Extension.SignalScope                                     = 'External';
Tilt_Extension.ExternalReference.ReferenceMethod               = 'Direct';
Tilt_Extension.ExternalReference.Data.HeaderFile               = 'toa_wl00_model_if.h';
Tilt_Extension.ExternalReference.Data.GlobalVariable           = 'TOA_tilt_extension';
Tilt_Extension.DataType                                        = 'single';

% Signal - Lift_Angle
Lift_Angle                                                    = CatP.Signal;
Lift_Angle.Description			                             = 'lift angle';
Lift_Angle.PCEType		                                     = 'Input';
Lift_Angle.SignalScope                                        = 'External';
Lift_Angle.ExternalReference.ReferenceMethod                  = 'Direct';
Lift_Angle.ExternalReference.Data.HeaderFile                  = 'toa_wl00_model_if.h';
Lift_Angle.ExternalReference.Data.GlobalVariable              = 'TOA_lift_angle';
Lift_Angle.DataType                                           = 'single';

% Signal - Lift_HE_Pressure
Lift_HE_Pressure                                             = CatP.Signal;
Lift_HE_Pressure.Description			                     = 'lift he pressure';
Lift_HE_Pressure.PCEType		                             = 'Input';
Lift_HE_Pressure.SignalScope                                 = 'External';
Lift_HE_Pressure.ExternalReference.ReferenceMethod           = 'Direct';
Lift_HE_Pressure.ExternalReference.Data.HeaderFile           = 'toa_wl00_model_if.h';
Lift_HE_Pressure.ExternalReference.Data.GlobalVariable       = 'TOA_lift_he_pressure';
Lift_HE_Pressure.DataType                                    = 'single';

% Signal - Lift_RE_Pressure
Lift_RE_Pressure                                             = CatP.Signal;
Lift_RE_Pressure.Description			                     = 'lift re pressure';
Lift_RE_Pressure.PCEType		                             = 'Input';
Lift_RE_Pressure.SignalScope                                 = 'External';
Lift_RE_Pressure.ExternalReference.ReferenceMethod           = 'Direct';
Lift_RE_Pressure.ExternalReference.Data.HeaderFile           = 'toa_wl00_model_if.h';
Lift_RE_Pressure.ExternalReference.Data.GlobalVariable       = 'TOA_lift_re_pressure';
Lift_RE_Pressure.DataType                                    = 'single';

% Signal - Tilt_HE_Pressure
Tilt_HE_Pressure                                             = CatP.Signal;
Tilt_HE_Pressure.Description			                     = 'tilt he pressure';
Tilt_HE_Pressure.PCEType		                             = 'Input';
Tilt_HE_Pressure.SignalScope                                 = 'External';
Tilt_HE_Pressure.ExternalReference.ReferenceMethod           = 'Direct';
Tilt_HE_Pressure.ExternalReference.Data.HeaderFile           = 'toa_wl00_model_if.h';
Tilt_HE_Pressure.ExternalReference.Data.GlobalVariable       = 'TOA_tilt_he_pressure';
Tilt_HE_Pressure.DataType                                    = 'single';

% Signal - Tilt_RE_Pressure
Tilt_RE_Pressure                                             = CatP.Signal;
Tilt_RE_Pressure.Description			                     = 'tilt re pressure';
Tilt_RE_Pressure.PCEType		                             = 'Input';
Tilt_RE_Pressure.SignalScope                                 = 'External';
Tilt_RE_Pressure.ExternalReference.ReferenceMethod           = 'Direct';
Tilt_RE_Pressure.ExternalReference.Data.HeaderFile           = 'toa_wl00_model_if.h';
Tilt_RE_Pressure.ExternalReference.Data.GlobalVariable       = 'TOA_tilt_re_pressure';
Tilt_RE_Pressure.DataType                                    = 'single';

% Signal - EEF_IMU_AccelX
EEF_IMU_AccelX                                                 = CatP.Signal;
EEF_IMU_AccelX.Description			                         = 'EEF IMU Acceleration X';
EEF_IMU_AccelX.PCEType		                                 = 'Input';
EEF_IMU_AccelX.SignalScope                                     = 'External';
EEF_IMU_AccelX.ExternalReference.ReferenceMethod               = 'Direct';
EEF_IMU_AccelX.ExternalReference.Data.HeaderFile               = 'toa_wl00_model_if.h';
EEF_IMU_AccelX.ExternalReference.Data.GlobalVariable           = 'TOA_eef_imu_accelX';
EEF_IMU_AccelX.DataType                                        = 'single';

% Signal - EEF_IMU_AccelY
EEF_IMU_AccelY                                                 = CatP.Signal;
EEF_IMU_AccelY.Description			                         = 'EEF IMU Acceleration Y';
EEF_IMU_AccelY.PCEType		                                 = 'Input';
EEF_IMU_AccelY.SignalScope                                     = 'External';
EEF_IMU_AccelY.ExternalReference.ReferenceMethod               = 'Direct';
EEF_IMU_AccelY.ExternalReference.Data.HeaderFile               = 'toa_wl00_model_if.h';
EEF_IMU_AccelY.ExternalReference.Data.GlobalVariable           = 'TOA_eef_imu_accelY';
EEF_IMU_AccelY.DataType                                        = 'single';

% Signal - EEF_IMU_AccelZ
EEF_IMU_AccelZ                                                 = CatP.Signal;
EEF_IMU_AccelZ.Description			                         = 'EEF IMU Acceleration Z';
EEF_IMU_AccelZ.PCEType		                                 = 'Input';
EEF_IMU_AccelZ.SignalScope                                     = 'External';
EEF_IMU_AccelZ.ExternalReference.ReferenceMethod               = 'Direct';
EEF_IMU_AccelZ.ExternalReference.Data.HeaderFile               = 'toa_wl00_model_if.h';
EEF_IMU_AccelZ.ExternalReference.Data.GlobalVariable           = 'TOA_eef_imu_accelZ';
EEF_IMU_AccelZ.DataType                                        = 'single';

% Signal - Steering_Angle
Steering_Angle                                                       = CatP.Signal;
Steering_Angle.Description			                                 = 'Steering Angle';
Steering_Angle.PCEType		                                         = 'Input';
Steering_Angle.SignalScope                                           = 'External';
Steering_Angle.ExternalReference.ReferenceMethod                     = 'Direct';
Steering_Angle.ExternalReference.Data.HeaderFile                     = 'toa_wl00_model_if.h';
Steering_Angle.ExternalReference.Data.GlobalVariable                 = 'TOA_steering_angle';
Steering_Angle.DataType                                              = 'single';

% Signal - Tool_Mass
Tool_Mass                                                       = CatP.Signal;
Tool_Mass.Description			                                 = 'tool mass';
Tool_Mass.PCEType		                                         = 'Input';
Tool_Mass.SignalScope                                           = 'External';
Tool_Mass.ExternalReference.ReferenceMethod                     = 'Direct';
Tool_Mass.ExternalReference.Data.HeaderFile                     = 'toa_wl00_model_if.h';
Tool_Mass.ExternalReference.Data.GlobalVariable                 = 'TOA_tool_mass';
Tool_Mass.DataType                                              = 'single';

% Signal - PCS_Truck_Target
PCS_Truck_Target                                                           = CatP.Signal;
PCS_Truck_Target.Description			                                     = 'pcs truck target';
PCS_Truck_Target.PCEType		                                             = 'Input';
PCS_Truck_Target.SignalScope                                               = 'External';
PCS_Truck_Target.ExternalReference.ReferenceMethod                         = 'Direct';
PCS_Truck_Target.ExternalReference.Data.HeaderFile                         = 'toa_wl00_model_if.h';
PCS_Truck_Target.ExternalReference.Data.GlobalVariable                     = 'TOA_truck_target_wt';
PCS_Truck_Target.DataType                                                  = 'single';

% Signal - PCS_Truck_Start_Weight
PCS_Truck_Start_Weight                                                          = CatP.Signal;
PCS_Truck_Start_Weight.Description			                                  = 'pcs truck start weight';
PCS_Truck_Start_Weight.PCEType		                                          = 'Input';
PCS_Truck_Start_Weight.SignalScope                                              = 'External';
PCS_Truck_Start_Weight.ExternalReference.ReferenceMethod                        = 'Direct';
PCS_Truck_Start_Weight.ExternalReference.Data.HeaderFile                        = 'toa_wl00_model_if.h';
PCS_Truck_Start_Weight.ExternalReference.Data.GlobalVariable                    = 'TOA_truck_start_weight';
PCS_Truck_Start_Weight.DataType                                                 = 'single';

% Signal - PCS_Bucket_Current_Weight_Accuracy
PCS_Bucket_Current_Weight_Accuracy                                                         = CatP.Signal;
PCS_Bucket_Current_Weight_Accuracy.Description			                                 = 'pcs bucket current weight accuracy';
PCS_Bucket_Current_Weight_Accuracy.PCEType		                                         = 'Input';
PCS_Bucket_Current_Weight_Accuracy.SignalScope                                             = 'External';
PCS_Bucket_Current_Weight_Accuracy.ExternalReference.ReferenceMethod                       = 'Direct';
PCS_Bucket_Current_Weight_Accuracy.ExternalReference.Data.HeaderFile                       = 'toa_wl00_model_if.h';
PCS_Bucket_Current_Weight_Accuracy.ExternalReference.Data.GlobalVariable                   = 'TOA_bucket_current_weight_accuracy';
PCS_Bucket_Current_Weight_Accuracy.DataType                                                = 'uint8_t'; %TipAssistPcsAccuracy_t;

% Signal - PCS_Bucket_Current_Weight
PCS_Bucket_Current_Weight                                                       = CatP.Signal;
PCS_Bucket_Current_Weight.Description			                                 = 'pcs bucket current weight';
PCS_Bucket_Current_Weight.PCEType		                                         = 'Input';
PCS_Bucket_Current_Weight.SignalScope                                           = 'External';
PCS_Bucket_Current_Weight.ExternalReference.ReferenceMethod                     = 'Direct';
PCS_Bucket_Current_Weight.ExternalReference.Data.HeaderFile                     = 'toa_wl00_model_if.h';
PCS_Bucket_Current_Weight.ExternalReference.Data.GlobalVariable                 = 'TOA_bucket_current_weight';
PCS_Bucket_Current_Weight.DataType                                              = 'single';

% Signal - PCS_Tipoff_Mode
PCS_Tipoff_Mode                                                    = CatP.Signal;
PCS_Tipoff_Mode.Description			                             = 'tipoff mode';
PCS_Tipoff_Mode.PCEType		                                     = 'Input';
PCS_Tipoff_Mode.SignalScope                                        = 'External';
PCS_Tipoff_Mode.ExternalReference.ReferenceMethod                  = 'Direct';
PCS_Tipoff_Mode.ExternalReference.Data.HeaderFile                  = 'toa_wl00_model_if.h';
PCS_Tipoff_Mode.ExternalReference.Data.GlobalVariable              = 'TOA_tipoff_mode';
PCS_Tipoff_Mode.DataType                                           = 'uint8';

% Signal - Zero_Offset
Zero_Offset                                                       = CatP.Signal;
Zero_Offset.Description			                                 = 'zero offset weight';
Zero_Offset.PCEType		                                         = 'Input';
Zero_Offset.SignalScope                                           = 'External';
Zero_Offset.ExternalReference.ReferenceMethod                     = 'Direct';
Zero_Offset.ExternalReference.Data.HeaderFile                     = 'toa_wl00_model_if.h';
Zero_Offset.ExternalReference.Data.GlobalVariable                 = 'TOA_zero_offset';
Zero_Offset.DataType                                              = 'single';

% Signal - Simple_Cal_Factor
Simple_Cal_Factor                                                       = CatP.Signal;
Simple_Cal_Factor.Description			                                 = 'simple cal adjust factor';
Simple_Cal_Factor.PCEType		                                         = 'Input';
Simple_Cal_Factor.SignalScope                                           = 'External';
Simple_Cal_Factor.ExternalReference.ReferenceMethod                     = 'Direct';
Simple_Cal_Factor.ExternalReference.Data.HeaderFile                     = 'toa_wl00_model_if.h';
Simple_Cal_Factor.ExternalReference.Data.GlobalVariable                 = 'TOA_simple_cal_factor';
Simple_Cal_Factor.DataType                                              = 'single';

% Signal - IMU_Pitch_Cal
IMU_Pitch_Cal                                                       = CatP.Signal;
IMU_Pitch_Cal.Description			                                = 'IMU placement error correction angle';
IMU_Pitch_Cal.PCEType		                                        = 'Input';
IMU_Pitch_Cal.SignalScope                                           = 'External';
IMU_Pitch_Cal.ExternalReference.ReferenceMethod                     = 'Direct';
IMU_Pitch_Cal.ExternalReference.Data.HeaderFile                     = 'toa_wl00_model_if.h';
IMU_Pitch_Cal.ExternalReference.Data.GlobalVariable                 = 'TOA_imu_pitch_cal';
IMU_Pitch_Cal.DataType                                              = 'single';

% Signal - Bucket_Angle
Bucket_Angle                                                = CatP.Signal;
Bucket_Angle.Description			                        = 'Bucket_Angle';
Bucket_Angle.PCEType		                                = 'Input';
Bucket_Angle.SignalScope                                    = 'External';
Bucket_Angle.ExternalReference.ReferenceMethod              = 'Direct';
Bucket_Angle.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Bucket_Angle.ExternalReference.Data.GlobalVariable          = 'TOA_bucket_angle';
Bucket_Angle.DataType                                       = 'single';

% Signal - Unlatch_Trigger
Unlatch_Trigger                                                = CatP.Signal;
Unlatch_Trigger.Description                                    = 'Unlatch_Trigger';
Unlatch_Trigger.PCEType                                        = 'Input';
Unlatch_Trigger.SignalScope                                    = 'External';
Unlatch_Trigger.ExternalReference.ReferenceMethod              = 'Direct';
Unlatch_Trigger.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Unlatch_Trigger.ExternalReference.Data.GlobalVariable          = 'TOA_unlatch_trigger';
Unlatch_Trigger.DataType                                       = 'boolean';

% Signal - Anchor_Zero_Offset
Anchor_Zero_Offset                                                = CatP.Signal;
Anchor_Zero_Offset.Description                                    = 'Anchor Zero Offset';
Anchor_Zero_Offset.PCEType                                        = 'Input';
Anchor_Zero_Offset.SignalScope                                    = 'External';
Anchor_Zero_Offset.ExternalReference.ReferenceMethod              = 'Direct';
Anchor_Zero_Offset.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Anchor_Zero_Offset.ExternalReference.Data.GlobalVariable          = 'TOA_anchor_zero_offset';
Anchor_Zero_Offset.DataType                                       = 'single';

% Signal - Anchor_Factor
Anchor_Factor                                                = CatP.Signal;
Anchor_Factor.Description                                    = 'Anchor Factor';
Anchor_Factor.PCEType                                        = 'Input';
Anchor_Factor.SignalScope                                    = 'External';
Anchor_Factor.ExternalReference.ReferenceMethod              = 'Direct';
Anchor_Factor.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Anchor_Factor.ExternalReference.Data.GlobalVariable          = 'TOA_anchor_factor';
Anchor_Factor.DataType                                       = 'single';

% Signal - CPM_Pass_Count
CPM_Pass_Count                                                = CatP.Signal;
CPM_Pass_Count.Description                                    = 'CPM Pass Count';
CPM_Pass_Count.PCEType                                        = 'Input';
CPM_Pass_Count.SignalScope                                    = 'External';
CPM_Pass_Count.ExternalReference.ReferenceMethod              = 'Direct';
CPM_Pass_Count.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
CPM_Pass_Count.ExternalReference.Data.GlobalVariable          = 'TOA_Pass_Count';
CPM_Pass_Count.DataType                                       = 'uint16';

% Signal - Lift_Norm_Angle
Lift_Norm_Angle                                                = CatP.Signal;
Lift_Norm_Angle.Description                                    = 'Lift_Norm_Angle';
Lift_Norm_Angle.PCEType                                        = 'Input';
Lift_Norm_Angle.SignalScope                                    = 'External';
Lift_Norm_Angle.ExternalReference.ReferenceMethod              = 'Direct';
Lift_Norm_Angle.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Lift_Norm_Angle.ExternalReference.Data.GlobalVariable          = 'TOA_Lift_Norm_Angle';
Lift_Norm_Angle.DataType                                       = 'single';

% Signal - Lift_Norm_Length
Lift_Norm_Length                                                = CatP.Signal;
Lift_Norm_Length.Description                                    = 'Lift_Norm_Length';
Lift_Norm_Length.PCEType                                        = 'Input';
Lift_Norm_Length.SignalScope                                    = 'External';
Lift_Norm_Length.ExternalReference.ReferenceMethod              = 'Direct';
Lift_Norm_Length.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Lift_Norm_Length.ExternalReference.Data.GlobalVariable          = 'TOA_Lift_Norm_Length';
Lift_Norm_Length.DataType                                       = 'single';

% Signal - Tilt_Norm_Angle
Tilt_Norm_Angle                                                = CatP.Signal;
Tilt_Norm_Angle.Description                                    = 'Tilt_Norm_Angle';
Tilt_Norm_Angle.PCEType                                        = 'Input';
Tilt_Norm_Angle.SignalScope                                    = 'External';
Tilt_Norm_Angle.ExternalReference.ReferenceMethod              = 'Direct';
Tilt_Norm_Angle.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Tilt_Norm_Angle.ExternalReference.Data.GlobalVariable          = 'TOA_Tilt_Norm_Angle';
Tilt_Norm_Angle.DataType                                       = 'single';

% Signal - Tilt_Norm_Length
Tilt_Norm_Length                                                = CatP.Signal;
Tilt_Norm_Length.Description                                    = 'Tilt_Norm_Length';
Tilt_Norm_Length.PCEType                                        = 'Input';
Tilt_Norm_Length.SignalScope                                    = 'External';
Tilt_Norm_Length.ExternalReference.ReferenceMethod              = 'Direct';
Tilt_Norm_Length.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Tilt_Norm_Length.ExternalReference.Data.GlobalVariable          = 'TOA_Tilt_Norm_Length';
Tilt_Norm_Length.DataType                                       = 'single';

% Signal - Friction_Mu
Friction_Mu                                                = CatP.Signal;
Friction_Mu.Description                                    = 'Friction_Mu';
Friction_Mu.PCEType                                        = 'Input';
Friction_Mu.SignalScope                                    = 'External';
Friction_Mu.ExternalReference.ReferenceMethod              = 'Direct';
Friction_Mu.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Friction_Mu.ExternalReference.Data.GlobalVariable          = 'TOA_Friction_Mu';
Friction_Mu.DataType                                       = 'single';

% Signal - Friction_Offset
Friction_Offset                                                = CatP.Signal;
Friction_Offset.Description                                    = 'Friction_Offset';
Friction_Offset.PCEType                                        = 'Input';
Friction_Offset.SignalScope                                    = 'External';
Friction_Offset.ExternalReference.ReferenceMethod              = 'Direct';
Friction_Offset.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Friction_Offset.ExternalReference.Data.GlobalVariable          = 'TOA_Friction_Offset';
Friction_Offset.DataType                                       = 'single';
%***********************************************************************************
%                                    OUTPUTS
%***********************************************************************************


% Signal - Tilt_Sensitivity
Tilt_Sensitivity                                                = CatP.Signal;
Tilt_Sensitivity.Description			                         = 'tilt sensitivity';
Tilt_Sensitivity.PCEType		                                 = 'Output';
Tilt_Sensitivity.SignalScope                                    = 'External';
Tilt_Sensitivity.ExternalReference.ReferenceMethod              = 'Direct';
Tilt_Sensitivity.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Tilt_Sensitivity.ExternalReference.Data.GlobalVariable          = 'TOA_tilt_sensitivity_out';
Tilt_Sensitivity.DataType                                       = 'single';

% Signal - Tilt_HE_Pressure_Out
Tilt_HE_Pressure_Out                                                    = CatP.Signal;
Tilt_HE_Pressure_Out.Description			                             = 'tilt he pressure out';
Tilt_HE_Pressure_Out.PCEType		                                     = 'Output';
Tilt_HE_Pressure_Out.SignalScope                                        = 'External';
Tilt_HE_Pressure_Out.ExternalReference.ReferenceMethod                  = 'Direct';
Tilt_HE_Pressure_Out.ExternalReference.Data.HeaderFile                  = 'toa_wl00_model_if.h';
Tilt_HE_Pressure_Out.ExternalReference.Data.GlobalVariable              = 'TOA_tilt_pressure_out';
Tilt_HE_Pressure_Out.DataType                                           = 'single';

% Signal - Arbitrated_Payload_Norm_Error
Arbitrated_Payload_Norm_Error                                            = CatP.Signal;
Arbitrated_Payload_Norm_Error.Description			                     = 'Arbitrated_Payload_Norm_Error';
Arbitrated_Payload_Norm_Error.PCEType		                             = 'Output';
Arbitrated_Payload_Norm_Error.SignalScope                                = 'External';
Arbitrated_Payload_Norm_Error.ExternalReference.ReferenceMethod          = 'Direct';
Arbitrated_Payload_Norm_Error.ExternalReference.Data.HeaderFile          = 'toa_wl00_model_if.h';
Arbitrated_Payload_Norm_Error.ExternalReference.Data.GlobalVariable      = 'TOA_arbitrated_payload_norm_error_out';
Arbitrated_Payload_Norm_Error.DataType                                   = 'single';

% Signal - Weigh_Status
Weigh_Status                                                 = CatP.Signal;
Weigh_Status.Description			                         = 'Weigh_Status';
Weigh_Status.PCEType		                                 = 'Output';
Weigh_Status.SignalScope                                     = 'External';
Weigh_Status.ExternalReference.ReferenceMethod               = 'Direct';
Weigh_Status.ExternalReference.Data.HeaderFile               = 'toa_wl00_model_if.h';
Weigh_Status.ExternalReference.Data.GlobalVariable           = 'TOA_weigh_status_out';
Weigh_Status.DataType                                        = 'uint8'; %TipAssistPfwStatus_t;

% Signal - Payload_Norm_Stdev
Payload_Norm_Stdev                                                 = CatP.Signal;
Payload_Norm_Stdev.Description			                         = 'Payload_Norm_Stdev';
Payload_Norm_Stdev.PCEType		                                 = 'Output';
Payload_Norm_Stdev.SignalScope                                     = 'External';
Payload_Norm_Stdev.ExternalReference.ReferenceMethod               = 'Direct';
Payload_Norm_Stdev.ExternalReference.Data.HeaderFile               = 'toa_wl00_model_if.h';
Payload_Norm_Stdev.ExternalReference.Data.GlobalVariable           = 'TOA_payload_norm_stdev_out';
Payload_Norm_Stdev.DataType                                        = 'single';

% Signal - PCS_Bucket_Current_Weight_Accuracy_Out
PCS_Bucket_Current_Weight_Accuracy_Out                                          = CatP.Signal;
PCS_Bucket_Current_Weight_Accuracy_Out.Description			                     = 'PCS_Bucket_Current_Weight_Accuracy_Out';
PCS_Bucket_Current_Weight_Accuracy_Out.PCEType		                             = 'Output';
PCS_Bucket_Current_Weight_Accuracy_Out.SignalScope                              = 'External';
PCS_Bucket_Current_Weight_Accuracy_Out.ExternalReference.ReferenceMethod        = 'Direct';
PCS_Bucket_Current_Weight_Accuracy_Out.ExternalReference.Data.HeaderFile        = 'toa_wl00_model_if.h';
PCS_Bucket_Current_Weight_Accuracy_Out.ExternalReference.Data.GlobalVariable    = 'TOA_pcs_weight_accuracy_out';
PCS_Bucket_Current_Weight_Accuracy_Out.DataType                                 = 'uint8_t'; %TipAssistPcsAccuracy_t;

% Signal - PCS_Bucket_Current_Weight_Norm_Error_Out
PCS_Bucket_Current_Weight_Norm_Error_Out                                                = CatP.Signal;
PCS_Bucket_Current_Weight_Norm_Error_Out.Description			                         = 'PCS_Bucket_Current_Weight_Norm_Error_Out';
PCS_Bucket_Current_Weight_Norm_Error_Out.PCEType		                                 = 'Output';
PCS_Bucket_Current_Weight_Norm_Error_Out.SignalScope                                    = 'External';
PCS_Bucket_Current_Weight_Norm_Error_Out.ExternalReference.ReferenceMethod              = 'Direct';
PCS_Bucket_Current_Weight_Norm_Error_Out.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
PCS_Bucket_Current_Weight_Norm_Error_Out.ExternalReference.Data.GlobalVariable          = 'TOA_current_weight_norm_error_out';
PCS_Bucket_Current_Weight_Norm_Error_Out.DataType                                       = 'single';

% Signal - Tipoff_Assist_Adv_Error_Code
Tipoff_Assist_Adv_Error_Code                                                 = CatP.Signal;
Tipoff_Assist_Adv_Error_Code.Description			                         = 'Tipoff_Assist_Adv_Error_Code';
Tipoff_Assist_Adv_Error_Code.PCEType		                                 = 'Output';
Tipoff_Assist_Adv_Error_Code.SignalScope                                     = 'External';
Tipoff_Assist_Adv_Error_Code.ExternalReference.ReferenceMethod               = 'Direct';
Tipoff_Assist_Adv_Error_Code.ExternalReference.Data.HeaderFile               = 'toa_wl00_model_if.h';
Tipoff_Assist_Adv_Error_Code.ExternalReference.Data.GlobalVariable           = 'TOA_error_code_out';
Tipoff_Assist_Adv_Error_Code.DataType                                        = 'uint8'; %TipAssistAdvEcmError_t;

% Signal - Spill_Rate_Norm
Spill_Rate_Norm                                                = CatP.Signal;
Spill_Rate_Norm.Description			                         = 'Spill_Rate_Norm';
Spill_Rate_Norm.PCEType		                                 = 'Output';
Spill_Rate_Norm.SignalScope                                    = 'External';
Spill_Rate_Norm.ExternalReference.ReferenceMethod              = 'Direct';
Spill_Rate_Norm.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Spill_Rate_Norm.ExternalReference.Data.GlobalVariable          = 'TOA_spill_rate_out';
Spill_Rate_Norm.DataType                                       = 'single';

% Signal - Bucket_Payload_Target
Bucket_Payload_Target                                                = CatP.Signal;
Bucket_Payload_Target.Description			                         = 'Bucket Payload Target';
Bucket_Payload_Target.PCEType		                                 = 'Output';
Bucket_Payload_Target.SignalScope                                    = 'External';
Bucket_Payload_Target.ExternalReference.ReferenceMethod              = 'Direct';
Bucket_Payload_Target.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Bucket_Payload_Target.ExternalReference.Data.GlobalVariable          = 'TOA_bucket_payload_target';
Bucket_Payload_Target.DataType                                       = 'single';

% Signal - Payload_Send_To_CPM
Payload_Send_To_CPM                                                = CatP.Signal;
Payload_Send_To_CPM.Description			                         = 'Payload_Send_To_CPM';
Payload_Send_To_CPM.PCEType		                                 = 'Output';
Payload_Send_To_CPM.SignalScope                                    = 'External';
Payload_Send_To_CPM.ExternalReference.ReferenceMethod              = 'Direct';
Payload_Send_To_CPM.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Payload_Send_To_CPM.ExternalReference.Data.GlobalVariable          = 'TOA_payload_send_to_CPM';
Payload_Send_To_CPM.DataType                                       = 'single';

% Signal - Payload_Status_Send_To_CPM
Payload_Status_Send_To_CPM                                                = CatP.Signal;
Payload_Status_Send_To_CPM.Description			                         = 'Payload_Status_Send_To_CPM';
Payload_Status_Send_To_CPM.PCEType		                                 = 'Output';
Payload_Status_Send_To_CPM.SignalScope                                    = 'External';
Payload_Status_Send_To_CPM.ExternalReference.ReferenceMethod              = 'Direct';
Payload_Status_Send_To_CPM.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Payload_Status_Send_To_CPM.ExternalReference.Data.GlobalVariable          = 'TOA_payload_status_send_to_CPM';
Payload_Status_Send_To_CPM.DataType                                       = 'uint8';

% Signal - Unsecured_Payload_Upper_Bound_Norm
Unsecured_Payload_Upper_Bound_Norm                                                = CatP.Signal;
Unsecured_Payload_Upper_Bound_Norm.Description			                         = 'Unsecured_Payload_Upper_Bound_Norm';
Unsecured_Payload_Upper_Bound_Norm.PCEType		                                 = 'Output';
Unsecured_Payload_Upper_Bound_Norm.SignalScope                                    = 'External';
Unsecured_Payload_Upper_Bound_Norm.ExternalReference.ReferenceMethod              = 'Direct';
Unsecured_Payload_Upper_Bound_Norm.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Unsecured_Payload_Upper_Bound_Norm.ExternalReference.Data.GlobalVariable          = 'TOA_unsecured_payload_upper_bound_norm';
Unsecured_Payload_Upper_Bound_Norm.DataType                                       = 'single';

% Signal - Unsecured_Payload_Lower_Bound_Norm 
Unsecured_Payload_Lower_Bound_Norm                                                 = CatP.Signal;
Unsecured_Payload_Lower_Bound_Norm.Description			                         = 'Unsecured_Payload_Lower_Bound_Norm ';
Unsecured_Payload_Lower_Bound_Norm.PCEType		                                 = 'Output';
Unsecured_Payload_Lower_Bound_Norm.SignalScope                                    = 'External';
Unsecured_Payload_Lower_Bound_Norm.ExternalReference.ReferenceMethod              = 'Direct';
Unsecured_Payload_Lower_Bound_Norm.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Unsecured_Payload_Lower_Bound_Norm.ExternalReference.Data.GlobalVariable          = 'TOA_unsecured_payload_lower_bound_norm ';
Unsecured_Payload_Lower_Bound_Norm.DataType                                       = 'single';

% Signal - Unsecured_PFW_Status 
Unsecured_PFW_Status                                                = CatP.Signal;
Unsecured_PFW_Status.Description			                         = 'Unsecured_PFW_Status';
Unsecured_PFW_Status.PCEType		                                 = 'Output';
Unsecured_PFW_Status.SignalScope                                    = 'External';
Unsecured_PFW_Status.ExternalReference.ReferenceMethod              = 'Direct';
Unsecured_PFW_Status.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Unsecured_PFW_Status.ExternalReference.Data.GlobalVariable          = 'TOA_unsecured_PFW_status';
Unsecured_PFW_Status.DataType                                       = 'uint8'; %TipAssistUnsecPfwStatus_t;

% Signal - Min_Secure_Bucket_Angle  
Min_Secure_Bucket_Angle                                                = CatP.Signal;
Min_Secure_Bucket_Angle.Description			                         = 'Min_Secure_Bucket_Angle';
Min_Secure_Bucket_Angle.PCEType		                                 = 'Output';
Min_Secure_Bucket_Angle.SignalScope                                    = 'External';
Min_Secure_Bucket_Angle.ExternalReference.ReferenceMethod              = 'Direct';
Min_Secure_Bucket_Angle.ExternalReference.Data.HeaderFile              = 'toa_wl00_model_if.h';
Min_Secure_Bucket_Angle.ExternalReference.Data.GlobalVariable          = 'TOA_min_secure_bucket_angle';
Min_Secure_Bucket_Angle.DataType                                       = 'single';
