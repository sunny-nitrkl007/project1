################################################################################
# DemoApp process identity and measured progress; not bridge process health.
################################################################################

# Numeric lifecycle values match legacy task::TaskState.
uint8 INITIALIZING=0
uint8 WAITING_FOR_PRECONDITIONS=1
uint8 EXECUTIVE_RUNNING=2
uint8 SHUTTING_DOWN=3
uint8 UNKNOWN=4

string session_id
uint64 report_sequence
string source
string host
int32 process_id
uint8 state 4
string logger_threshold

float64 intended_cycle_rate_hz
float64 cycle_rate_hz
float64 recent_executive_cycle_rate_hz
float64 longest_executive_cycle_sec
float64 longest_recent_executive_cycle_sec
uint64 total_executive_cycle_count
uint64 total_executive_late_cycle_count
# Measured executor idle time, not assumed equivalent to AIS executive sleep.
float64 executor_idle_time_sec
