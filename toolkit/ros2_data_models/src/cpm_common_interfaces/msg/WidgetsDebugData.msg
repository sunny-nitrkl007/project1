################################################################################
# WidgetsDebugDataStorage
# Legacy source: prod/common/interfaces/WidgetsDebugData/WidgetsDebugData.h
################################################################################

# pcs_dig_state_t (mach_prod_pcs-interface/include/pcs_public.h)
uint8 PCS_DIG_UNKNOWN=0
uint8 PCS_NOT_DIGGING=0
uint8 PCS_TENTATIVE_DIGGING=1
uint8 PCS_DIGGING=2

WidgetsTireRevDistances distance
WidgetsTireRevRotations rotation
# 0.01 s/bit
uint16 dig_time_current
uint16 traveling_loaded_revs
uint8 dig_state
# GROUNDSPEED_INFO
float32 ground_speed_info_speed
uint16 ground_speed_info_data_status
# GEAR_INFO
uint16 gear_info_gear
uint16 gear_info_gear_status
