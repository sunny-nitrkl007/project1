################################################################################
# AppRegStorage — protocol fields only; producer set and timeout are local state.
################################################################################

uint8 STATE_ACTIVE=0
uint8 STATE_INACTIVE=1
uint8 REQ=0
uint8 RESP=1
uint8 NAME_NOT_SET=0
uint8 DEST_NAME_MISMATCH=1
uint8 NAME_EMPTY=2
uint8 REGISTERED=3
uint8 ALREADY_REGISTERED=4
uint8 UNREGISTERED=5
uint8 UNKNOWN=6

uint8 msg_type
string app_name
uint8 app_state 1
string dest_app_name
uint8 reg_status 6
