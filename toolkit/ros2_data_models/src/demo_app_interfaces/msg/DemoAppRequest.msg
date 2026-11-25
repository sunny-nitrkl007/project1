################################################################################
# DemoAppReqstCommand / DemoAppReqst
################################################################################

uint8 WRITE_LIFT_POSITION=0
uint8 WRITE_LIFT_POSITION_RATE=1
uint8 WRITE_TILT_POSITION=2
uint8 WRITE_TILT_POSITION_RATE=3
uint8 WRITE_PAYLOAD=4
uint8 WRITE_PAYLOAD_RATE=5
uint8 DIG=6
uint8 WRW=7
uint8 DUMP=8
uint8 LLW=9
uint8 PDUMP=10
uint8 CARRY=11
uint8 NONE=12

uint8 command 12
# Legacy position/rate/payload/weight accessors alias this same argument.
float32 arg 0.0
bool arg1 false
