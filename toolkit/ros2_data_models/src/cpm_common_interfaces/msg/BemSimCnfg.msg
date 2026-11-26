################################################################################
# BEMSimCnfgStorage (public members)
# Legacy source: prod/infrastructure/aisJhm/aisJhm2/AisJhm2RequestProcessor/BEMSim/BEMSimCnfgStorage.h
################################################################################

# Private save-scheduler members (savePeriodTime_, savePeriodCount_, savePeriodSubCycles_) are not transported.

bool charge_mode
float32 start_charge
# std::chrono::system_clock::time_point, nanoseconds since epoch (TimePoint::min() = INT64_MIN)
int64 charge_mode_start_time_ns
float64 start_fuel_used
float32 last_discharge_rate
bool bem_sim_enabled
float32 charger_capacity
bool engine_derate_enabled
bool new_machine
