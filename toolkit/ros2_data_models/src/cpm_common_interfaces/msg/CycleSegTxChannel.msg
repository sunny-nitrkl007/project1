################################################################################
# CycleSegTxInterfaceStorage
# Legacy source: prod/common/interfaces/CycleSeg/TxInterface.hpp
################################################################################

uint8 active_segment_id
uint8 dig_state
uint8 segment_last_completed_id
float32 segment_seconds_since_last_end
uint8 segment_sequence_number
CycleSegInputs cycle_seg_in
CycleSegOutputs cycle_seg_out
