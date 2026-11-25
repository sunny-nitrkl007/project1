################################################################################
# DemoApp executive cycle; legacy DataLinkData reconstruction belongs to bridge.
################################################################################

# Unique per process start; sequence begins at one and increases per model step.
string session_id
uint64 sequence

# Raw SetLastValue arguments, not engineering values. Bridge owns fixed PID,
# SID, parameter type, scaling and per-publication legacy metadata bookkeeping.
uint32 hydraulic_oil_temperature
uint32 sea_level_installation
uint32 production_measurement
uint8[8] engine_speed_pgn
uint32 service_mode
uint32 total_fuel_used

# DataLink values are captured before requests; Tx follows the same model step.
weigh_app_interfaces/DemoAppTxChannel tx
