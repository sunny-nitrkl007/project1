#ifndef MTP_BMI_CDL_PID_H_
#define MTP_BMI_CDL_PID_H_

#define BMI_CDL_DATA_STATUS_OK 0
constexpr uint32_t BMI_CDL_PID_ACTUAL_ENGINE_RPM                              = 0x40;
constexpr uint32_t BMI_CDL_PID_HYD_OIL_TEMP		                              = 0x45;
constexpr uint32_t BMI_CDL_PID_TOTAL_FUEL_USED                                = 0xC8;
constexpr uint32_t BMI_CDL_PID_TRANSMISSION_GEAR                              = 0xF002;
constexpr uint32_t BMI_CDL_PID_OP_REQUESTED_GEAR                              = 0xF5D7;
constexpr uint32_t BMI_CDL_PID_IGNITION_KEY_SWITCH_POSITION                   = 0xF08F;
constexpr uint32_t BMI_CDL_PID_STORE_SWITCH                  				  = 0xF1AA;
constexpr uint32_t BMI_CDL_PID_TILT_RIGHT_SOLENOID_CURRENT_PERCENTAGE         = 0xF146;
constexpr uint32_t BMI_CDL_PID_TILT_LEFT_SOLENOID_CURRENT_PERCENTAGE          = 0xF147;
constexpr uint32_t BMI_CDL_PID_RIPPER_SHANK_RAISE_SOLENOID_CURRENT_PERCENTAGE = 0xF27C;
constexpr uint32_t BMI_CDL_PID_RIPPER_SHANK_LOWER_SOLENOID_CURRENT_PERCENTAGE = 0xF27D;
constexpr uint32_t BMI_CDL_PID_TORQUE_CONVERTER_SPEED                         = 0xF478;
constexpr uint32_t BMI_CDL_PID_TILT_LEVER_POSITION	                          = 0xF49C;
constexpr uint32_t BMI_CDL_PID_FUEL_CONSUMPTION_RATE                          = 0xF525;
constexpr uint32_t BMI_CDL_PID_MACHINE_PITCH                                  = 0xF58B;
constexpr uint32_t BMI_CDL_PID_TRACK_SPEED_DIRECTION                          = 0xF5B2;
constexpr uint32_t BMI_CDL_PID_BLADE_LOWER_SOLENOID_CURRENT_PERCENTAGE        = 0xF5BE;
constexpr uint32_t BMI_CDL_PID_BLADE_RAISE_SOLENOID_CURRENT_PERCENTAGE        = 0xF5BF;
constexpr uint32_t BMI_CDL_PID_ACTUAL_GEAR                                    = 0xF5D9;
constexpr uint32_t BMI_CDL_PID_TILT_ANGLE                                     = 0xF47A;
constexpr uint32_t BMI_CDL_PID_LIFT_ANGLE                                     = 0xF479;
constexpr uint32_t BMI_CDL_PID_GROUND_SPEED                                   = 0xF4FD;
constexpr uint32_t BMI_CDL_PID_TOTAL_FUEL                                     = 0xFE5D;
constexpr uint32_t BMI_CDL_PID_UNITS_STATUS                                   = 0xF25B;
constexpr uint32_t BMI_CDL_PID_PRODUCT_ID  	                                  = 0xF82D;
constexpr uint32_t BMI_CDL_PID_EXT_FORCE						              = 0xD01E8C;
constexpr uint32_t BMI_CDL_PID_MACHINE_IDLE_STATUS				              = 0xD10AB5;
constexpr uint32_t BMI_CDL_PID_TILT_RIGHT_SOLENOID_CURRENT_STATUS             = 0xD00191;
constexpr uint32_t BMI_CDL_PID_TILT_RIGHT_SOLENOID_MAXIMUM_CURRENT            = 0xD00192;
constexpr uint32_t BMI_CDL_PID_TILT_LEFT_SOLENOID_CURRENT_STATUS              = 0xD00194;
constexpr uint32_t BMI_CDL_PID_TILT_LEFT_SOLENOID_MAXIMUM_CURRENT             = 0xD00195;
constexpr uint32_t BMI_CDL_PID_LEFT_STEERING_SOLENOID_CURRENT_STATUS          = 0xD00897;
constexpr uint32_t BMI_CDL_PID_RIGHT_STEERING_SOLENOID_CURRENT_STATUS         = 0xD00898;
constexpr uint32_t BMI_CDL_PID_MACHINE_ROLL                                   = 0xD00A64;
constexpr uint32_t BMI_CDL_PID_RIPPER_SHANK_RAISE_SOLENOID_MAXIMUM_CURRENT    = 0xD00CC1;
constexpr uint32_t BMI_CDL_PID_RIPPER_SHANK_LOWER_SOLENOID_MAXIMUM_CURRENT    = 0xD00CC2;
constexpr uint32_t BMI_CDL_PID_BLADE_RAISE_SOLENOID_MAXIMUM_CURRENT           = 0xD00F93;
constexpr uint32_t BMI_CDL_PID_BLADE_LOWER_SOLENOID_MAXIMUM_CURRENT           = 0xD00F94;
constexpr uint32_t BMI_CDL_PID_BLADE_RAISE_SOLENOID_CURRENT_STATUS            = 0xD014B0;
constexpr uint32_t BMI_CDL_PID_BLADE_LOWER_SOLENOID_CURRENT_STATUS            = 0xD014B1;
constexpr uint32_t BMI_CDL_PID_RIPPER_SHANK_RAISE_SOLENOID_CURRENT_STATUS     = 0xD016AC;
constexpr uint32_t BMI_CDL_PID_RIPPER_SHANK_LOWER_SOLENOID_CURRENT_STATUS     = 0xD016AD;
constexpr uint32_t BMI_CDL_PID_TRANSMISSION_OUTPUT_TORQUE                     = 0xD01C79;
constexpr uint32_t BMI_CDL_PID_IMPLEMENT_OPERATION_STATUS                     = 0xD106D9;
constexpr uint32_t BMI_CDL_PID_PRODUCT_LINK_MODULE_GPS_POSITION_STATUS        = 0xF84D;
constexpr uint32_t BMI_CDL_PID_TIME_ZONE_INFORMATION                          = 0xFA27;

#endif  // MTP_BMI_CDL_PID_H_
