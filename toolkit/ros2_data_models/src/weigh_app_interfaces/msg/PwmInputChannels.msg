################################################################################
# PwmInputChannelsStorage::PwmData
################################################################################

int32[] period
int32[] width
uint8[] switch_status
uint8[] timeout

# Timing fields of PwmData (serialized over SCS, read by aisXcpServer XCP group 7, offsets 0-3).
# Appended 2026-11-23; no other subscriber of this message existed.
int64 actual_time_us   # long ActualTimeUs: actual time in micro-seconds, wraps around every 99,999
int32 exec_time        # int ExecTime: execution time in ms to create record
int32 diff_time        # int DiffTime: difference from previous ActualTimeUs, in micro-seconds
uint32 exp             # unsigned int Exp: number of times the timer expired since last read()
