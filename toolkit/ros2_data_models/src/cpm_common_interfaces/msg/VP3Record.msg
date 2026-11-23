################################################################################
# VP3RecordStorage — UID list and R-block data contain binary bytes, not text.
################################################################################

uint16 LOAD=1
uint16 PAYLOAD=2
uint16 CYCLE=3
uint16 SEGMENT=4
uint16 STATUS=5
uint16 GPS=6

uint16 record_type
uint8[] uid_list
uint8[] r_block_data
uint16 number_of_uids
uint16 size_of_record

bool datum_attributes_valid
int64 origination_time_secs
int64 origination_time_usecs
int64 transmission_time_secs
int64 transmission_time_usecs
uint32 transmission_sequence_number
uint32 logger_sequence_number
int64 logged_time_secs
int64 logged_time_usecs
