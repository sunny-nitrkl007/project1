#ifndef SL_OELRTOS_ERROR_DEFS_H_
#define SL_OELRTOS_ERROR_DEFS_H_


/*************************************************************************
 **          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 **         This work contains proprietary information, which may
 **         constitute a trade secret and/or be confidential.
 * -----------------------------------------------------------------------
 * DESCRIPTION:
 * This file contains definitions  needed for the OEL RTOS error reporting
 * from simulink generated code
 *
 * FILE NAME : sl_oelrtos_error_defs.h
 *
 *************************************************************************/

/*************************************************************************
 ** -- Includes --
 *************************************************************************/
#include <oel_rtos.h>

/*************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 *************************************************************************/


#define SL_ERROR_CATAGORY_MASK                             0xF0000000
#define SL_ERROR_LAYER_MASK                                0x0F000000
#define SL_ERROR_COMPONENT_SHIFT                           16
#define SL_ERROR_COMPONENT_MASK                            0x00FF0000
#define SL_ERROR_FUNCTION_SHIFT                            8
#define SL_ERROR_FUNCTION_MASK                             0x0000FF00
#define SL_ERROR_LINE_NUM_MASK                             0x000000FF


#define SL_ERROR_WARNING(component, function)       \
        oel_rtos_err_report((__LINE__ % 255)        \
        | ((function) << SL_ERROR_FUNCTION_SHIFT)   \
        | ((component) << SL_ERROR_COMPONENT_SHIFT) \
        | OEL_RTOS_ERR_LAYER_SIMULINK               \
        | OEL_RTOS_ERR_CATEGORY_WARNING)
        
#define SL_ERROR_SYS_FATAL(component, function)     \
        oel_rtos_err_report((__LINE__ % 255)        \
        | ((function) << SL_ERROR_FUNCTION_SHIFT)   \
        | ((component) << SL_ERROR_COMPONENT_SHIFT) \
        | OEL_RTOS_ERR_LAYER_SIMULINK               \
        | OEL_RTOS_ERR_CATEGORY_SYS_FATAL)
        
        
/* Component codes ----------------------------------------------------- */
#define SL_ERR_COMPONENT_J1939_RX_SPN_BLOCK                0x01
#define SL_ERR_COMPONENT_J1939_RX_PGN_BLOCK                0x02
#define SL_ERR_COMPONENT_J1939_HEALTH_PEER_BLOCK           0x03
#define SL_ERR_COMPONENT_RX_PPGNA_BLOCK                    0x04
#define SL_ERR_COMPONENT_HALCANRX_BLOCK                    0x05
#define SL_ERR_COMPONENT_J1939_EXTPARAMHEALTH_BLOCK        0x06
#define SL_ERR_COMPONENT_J1939_HEALTH_LOCAL_ECM_BLOCK      0x07
#define SL_ERR_COMPONENT_J1939_PGB_BLOCK                   0x08
#define SL_ERR_COMPONENT_J1939_HEALTH_LINK_BLOCK           0x09
#define SL_ERR_COMPONENT_SCLDLINFO_BLOCK                   0x0A
#define SL_ERR_COMPONENT_J1939_ADT_BLOCK                   0x0B
#define SL_ERR_COMPONENT_RAILCANTX_BLOCK                   0x0C
#define SL_ERR_COMPONENT_RAILCANRX_BLOCK                   0x0D
#define SL_ERR_COMPONENT_BDTSETUP_BLOCK                    0x0E
#define SL_ERR_COMPONENT_AR_INDEX_BLOCK_1                  0x0F
#define SL_ERR_COMPONENT_FPS_BLOCK                         0x14
#define SL_ERR_COMPONENT_SCL_QR_BLOCK                      0x10
#define SL_ERR_COMPONENT_HALCAN_SETUP_BLOCK                0x15
#define SL_ERR_COMPONENT_HALCAN_SEND_BLOCK                 0x16
#define SL_ERR_COMPONENT_HALCANRX_FIFO_BLOCK               0x17
#define SL_ERR_COMPONENT_SL_CAL_RS_STATE_ENUM              0x18
#define SL_ERR_COMPONENT_STACK_OVERFLOW                    0x19
#define SL_ERR_COMPONENT_SCL_INFO_QUERY_BLOCK              0x1A
#define SL_ERR_COMPONENT_MODBUS_BLOCK                      0x1B
#define SL_ERR_COMPONENT_SCL_OVERRIDE_BLOCK                0x1C
#define SL_ERR_COMPONENT_SCL_PASSWORD_BLOCK                0x1D
#define SL_ERR_COMPONENT_PMS_GETEVENT_BLOCK                0x1E
#define SL_ERR_COMPONENT_PMS_SETUP_BLOCK                   0x1F
#define SL_ERR_COMPONENT_QUALIFIED_READ_BLOCK              0x20
#define SL_ERR_COMPONENT_SNAPSHOT_BLOCK                    0x21
#define SL_ERR_COMPONENT_HAL_SERIAL_BLOCK                  0x22
#define SL_ERR_COMPONENT_SCL_CCP_BLOCK                     0x23
#define SL_ERR_COMPONENT_DM13_STOP_BCAST_BLOCK             0x24
#define SL_ERR_COMPONENT_J1939_MAP_CLIENT_BLOCK            0x25
#define SL_ERR_COMPONENT_J1939_TRANSMIT_BLOCK              0x26
#define SL_ERR_COMPONENT_J1939_SETUP_BLOCK                 0x27
#define SL_ERR_COMPONENT_QUERY_FAULT_COUNT_BLOCK           0x28
#define SL_ERR_COMPONENT_DM13_BLOCK                        0x29
#define SL_ERR_COMPONENT_COSM_TRIGGER_BLOCK                0x2A
#define SL_ERR_COMPONENT_CDL_TRANSMIT_BLOCK                0x2B
#define SL_ERR_COMPONENT_PMS_ACTION_SETUP_OV_BLOCK         0x2D
#define SL_ERR_COMPONENT_SL_CLOCK_SETUP_BLOCK              0x2E
#define SL_ERR_COMPONENT_CAL_SERVICE_PROTOCOL_GET_BLOCK    0x2F
#define SL_ERR_COMPONENT_HAL_ETHERNET_SETUP_BLOCK          0x30
#define SL_ERR_COMPONENT_PID_PARAMETER                     0x31
#define SL_ERR_COMPONENT_BDT_WRAPPER_SETUP_BLOCK           0x32
#define SL_ERR_COMPONENT_COSM_FAULT_RPT_BLOCK              0x33
#define SL_ERR_COMPONENT_COSM_STATUS_CHECK_BLOCK           0x34
#define SL_ERR_COMPONENT_COSM_WARNING_CLEAR_BLOCK          0x35
#define SL_ERR_COMPONENT_CAT_DATALINK_BLOCK                0x36
#define SL_ERR_COMPONENT_CDL_RECEIVE_BLOCK                 0x37
#define SL_ERR_COMPONENT_CDL_SETUP_BLOCK                   0x38
#define SL_ERR_COMPONENT_RW_HANDLER_BLOCK                  0x39
#define SL_ERR_COMPONENT_REAL_TIME_CLOCK_BLOCK             0x3A
#define SL_ERR_COMPONENT_SCL_QR_SETUP_BLOCK                0x3B
#define SL_ERR_COMPONENT_SCL_CUMULATIVE_BLOCK              0x3C
#define SL_ERR_COMPONENT_SCL_FLEX_J1939_BLOCK              0x3D
#define SL_ERR_COMPONENT_SCL_HISTOGRAM_BLOCK               0x3E
#define SL_ERR_COMPONENT_SCL_INFO_SETUP_BLOCK              0x3F
#define SL_ERR_COMPONENT_SCL_ANNUNC_BLOCK                  0x40
#define SL_ERR_COMPONENT_SCL_CLEAR_DTC_BLOCK               0x41
#define SL_ERR_COMPONENT_SCL_DIAG_CLIENT_BLOCK             0x42
#define SL_ERR_COMPONENT_SCL_DIAG_MANAGER_BLOCK            0x43
#define SL_ERR_COMPONENT_DIAG_MANAGER_CLEAR_BLOCK          0x44
#define SL_ERR_COMPONENT_SCL_INFO_DTC_BLOCK                0x45
#define SL_ERR_COMPONENT_SCL_INFO_BLOCK                    0x46


/* Function codes ------------------------------------------------------ */

/* Function codes for J1939 RX SPN Block */
#define SL_J1939_RX_SPN_BLOCK_INIT                         0x01
#define SL_J1939_RX_SPN_BLOCK_UPDATE                       0x02

/* Function codes for J1939 RX PGN Block */
#define SL_J1939_RX_PGN_BLOCK_INIT                         0x03
#define SL_J1939_RX_PGN_BLOCK_UPDATE                       0x04

/* Function codes for J1939 Peer Health Block */
#define SL_J1939_HEALTH_PEER_BLOCK_INIT                    0x05
#define SL_J1939_HEALTH_PEER_BLOCK_UPDATE                  0x06

/* Function codes for J1939 PPGN  Block */
#define SL_RX_PPGNA_BLOCK_INIT                             0x07
#define SL_RX_PPGNA_BLOCK_UPDATE                           0x08

/* Function codes for HAL CAN  Block */
#define SL_HALCANRX_BLOCK_INIT                             0x09
#define SL_HALCANRX_BLOCK_UPDATE                           0x0A

/* Function codes for J1939 External Parameter Health Block */
#define SL_J1939_EXTPARAMHEALTH_BLOCK_INIT                 0x0B
#define SL_J1939_EXTPARAMHEALTH_BLOCK_UPDATE               0x0C

/* Function codes for LOCAL ECM HEALTH Block */
#define SL_J1939_HEALTH_LOCAL_ECM_BLOCK_INIT               0x0D
#define SL_J1939_HEALTH_LOCAL_ECM_BLOCK_UPDATE             0x0E

/* Function codes for PGB Block */
#define SL_J1939_PGB_BLOCK_INIT                            0x0F
#define SL_J1939_PGB_BLOCK_UPDATE                          0x10

/* Function codes for HEALTH LINK Block */
#define SL_J1939_HEALTH_LINK_BLOCK_INIT                    0x11
#define SL_J1939_HEALTH_LINK_BLOCK_UPDATE                  0x12

#define SL_SCLDLINFO_BLOCK_INIT                            0x13

/* Function codes for ADT Block */
#define SL_J1939_ADT_BLOCK_INIT                            0x14
#define SL_J1939_ADT_BLOCK_UPDATE                          0x15
#define SL_J1939_ADT_REMOVE_GROUP                          0x3D

/* Function codes for RAILCAN Block */
#define SL_RAILCAN_INIT                                    0x16

/* Function codes for BDT Setup Block */
#define SL_BDT_INIT                                        0x17
#define SL_BDT_CDL_INIT                                    0x18
#define SL_BDT_j1939_INIT                                  0x19
#define SL_BDT_CALLBACK_BLOCK_COUNT                        0x1A
#define SL_BDT_DATATYPE_COUNT                              0x1B
#define SL_BDT_DATATTYPE_INIT                              0xA5

/* Function codes for AUTOSAR Index 1 Block */
#define SL_AR_INDEX_BLOCK_1_BAD_INDEX                      0x1C
#define SL_AR_INDEX_BLOCK_1_NULL_PTR                       0x1D

/* Function codes for FPS Block */
#define SL_FPS_BLOCK_INIT                                  0x1E

/* Function codes for QR Block */
#define SL_QR_INIT                                         0x3E
#define SL_QR_ADD_ENTRY                                    0x1F
#define SL_QR_REMOVE_ENTRY                                 0x20
#define SL_QR_INVALID_QR_TYPE                              0x21

/* Function codes for HALCAN Setup and Fifo Block*/
#define SL_PORT_ATTACH_CLIENT2                             0x22
#define SL_PORT_ATTACH_CLIENT                              0x23

/* Function codes for HALCAN Setup Block*/
#define SL_PORT_SET_BTRT                                   0x24
#define SL_PORT_OPEN                                       0x25

/* Function code for HALCAN Send Block*/
#define SL_PORT_SUBMIT_PACKET                              0x26

/* Function code for CAL Block*/
#define SL_CAL_INIT                                        0x27
#define SL_CAL_MUTABLE_SELECT                              0x28
#define SL_CAL_SELECT                                      0x29
#define SL_CAL_IS_SELECTED                                 0x2A

/* Function codes for Stack Overflow Task */
#define SL_STACK_OVERFLOW_TASKID                           0x2B

/* Function codes for Cosm Trigger Block  */
#define SL_COSM_TRIGGER_ADD_STATUS_SERVICE                 0x2C
#define SL_COSM_TRIGGER_ADD_STATUS_CALIBRATION             0x2D

/* Function code for CDL Transmit Block*/
#define SL_J1939_SERVER_INIT                               0x2E
#define SL_J1939_SET_CHECK_PEROID                          0x2F

/* Function code for Map Client Block*/
#define SL_J1939_MAP_CLIENT_INIT                           0x30

/* Function code for PMS Action Setup OV Block*/
#define SL_PMS_ACTION_SETUP_OV_MODIFIER                    0x31

/* Function code for clock setup Block*/
#define SL_CLOCK_SETUP_INIT                                0x32
#define SL_RTC_INIT_NO_CDL                                 0x33
#define SL_CLOCK_MODULE_INIT                               0x34
#define SL_CLOCK_SET_NVM_CACHE                             0x35
#define SL_CLOCK_NVM_SAVE                                  0x36
#define SL_CLOCK_J1939_SYNCLK_INIT                         0x37
#define SL_CLOCK_SYNCLK_KSW_REGISTER                       0x38
#define SL_CLOCK_SYNCLK_MARGINAL_UPDATE                    0x39
#define SL_CLOCK_SYNCLK_MANUAL_ADJ                         0x3A
#define SL_CLOCK_CDL_SYNCLK_INIT                           0x3B
#define SL_CLOCK_MODULE_UPDATE                             0x3C

/* Function code for Calibration and Service Protocol Set Block*/
#define SL_CAL_SERVICE_PROTOCOL_MESSAGE_EMPTY              0x3F
#define SL_CAL_SERVICE_PROTOCOL_MESSAGE_LENGTH             0x40

/* Function code for HAL Ethernet setup Block*/
#define SL_HAL_ETHERNET_SETUP_INIT                         0x41

/* Function code for HAL Serial block*/
#define SL_HAL_SERIAL_INIT                                 0x42

/* Function code for SCL CCP block*/
#define SL_SCL_CCP_UPDATE                                  0x43

/* Function code for Calibration Service Cosm Block*/
#define SL_COSM_FAULT_RPT_ERR_WARN_UPD                     0x44
#define SL_COSM_WARNING_CLEAR                              0x45

/* Function code for Read Software part No Block*/
#define SL_COSM_STATUS_CHECK_OUTPUT                        0x46

/* Function code for CDL Block*/
#define SL_CDL_SETUP_TRANSMIT_INIT                         0x48
#define SL_CDL_TRANSMIT_PIT                                0x49
#define SL_CDL_WRITE_PIT                                   0x4A
#define SL_CDL_RECEIVE_PIT                                 0x4B
#define SL_CDL_REMOVE_TRANSMIT_PIT                         0x4C
#define SL_CDL_REMOVE_WRITE_PIT                            0x4D
#define SL_CDL_REMOVE_RECEIVE_PIT                          0x4E
#define SL_CDL_POLLING_UPDATE                              0x4F
#define SL_J1939_TRANSMIT_PIT                              0x50
#define SL_CDL_PID_MEMORY_UPDATE                           0x51
#define SL_CDL_DATALINK_INIT                               0xA0

/* Function code for Real Time Clock Block*/
#define SL_REAL_TIME_CLOCK_UPDATE                          0x52

/* Function code for SCL Cumulative Block*/
#define SL_SCL_CUMS_PRIMARY_INIT                           0x53
#define SL_SCL_CUMS_PRIMARY_ROLLING_INIT                   0x54
#define SL_SCL_CUMS_PRI_SAMPLING_COUNTS                    0x55
#define SL_SCL_CUMULATIVE_DATA_UPDATE                      0x56
#define SL_SCL_CUMS_SET_ROLLING_DATA                       0x57
#define SL_SCL_CUMS_GET_ROLLING_DATA                       0x58
#define SL_SCL_CUMULATIVE_DATA_SET                         0x59
#define SL_SCL_CUMULATIVE_DATA_GET                         0x5A
#define SL_SCL_CUMULATIVE_ID_UPDATE                        0x5B
#define SL_SCL_CUMS_PRIMARY_INIT_SUBSYS                    0x5C

/* Function code for SCL Flex J1939 Block*/
#define SL_SCL_FLEX_J1939_MAP_PID                          0x5D
#define SL_SCL_FLEX_INIT                                   0x5E
#define SL_SCL_FLEX_J1939_PID_ADD_VALUE                    0x5F
#define SL_SCL_FLEX_WR_PID_RANGE                           0x60
#define SL_SCL_FLEX_WR_PID_VALUE                           0x61

/* Function code for SCL Override block*/
#define SL_SCL_OVERRIDE_INIT                               0x62

/* Function code for HISTOGRAM*/
#define SL_HISTOGRAM_INIT                                  0x63
#define SL_HISTOGRAM_ADD_TABLE                             0x64
#define SL_HISTOGRAM_TABLE_INC_OCCUR                       0x65
#define SL_HISTOGRAM_TABLE_CLEAR                           0x66
#define SL_HISTOGRAM_PEROIDIC_UPDATE                       0xA2

/* Function code for SCL block*/
#define SL_SCL_INFO_GET_ACTIVE_ANNUCIATION                 0x67
#define SL_SCL_INFO_CLEAR_FAULT                            0x68
#define SL_SCL_INFO_ADD_SERVICE                            0x69
#define SL_SCL_INFO_PEER_REQUEST_AI                        0x6A
#define SL_SCL_INFO_PEER_REQUEST_DM                        0x6B
#define SL_SCL_INFO_PEER_EDDT_TABLE_REQ                    0x6C
#define SL_SCL_INFO_ADD_J1939_LINK                         0x6D
#define SL_SCL_INFO_ADD_PEER                               0x6E
#define SL_SCL_AI_REQUEST                                  0x70
#define SL_SCL_DIAGNOSTIC_TEST_NOTIFY                      0x72
#define SL_SCL_OBD_ES_REGISTER                             0x73
#define SL_SCL_OBD_CRICTICAL_REGISTER                      0x74
#define SL_SCL_OBD_ES_ANNUCIATION                          0x75
#define SL_SCL_J1939_DIAG_REGISTER                         0x76
#define SL_SCL_J1939_FAULT_REGISTER                        0x77
#define SL_SCL_CDL_FAULT_REGISTER                          0xA3
#define SL_SCL_RAILCAN_DIAG_REGISTER                       0x79
#define SL_SCL_SPN_TEST_HANDLE                             0x7A
#define SL_SCL_GET_ADDL_ERR_INFO                           0x7B
#define SL_SCL_GET_FALUT_INFO                              0x7C
#define SL_SCL_GET_FALUT_REPORT                            0x7D
#define SL_SCL_REMOVE_GARBAGE_DTC                          0x7E
#define SL_SCL_DRIVER_COMPLETE                             0x7F
#define SL_SCL_DRIVER_WARMUP_COMPLETE                      0x80
#define SL_SCL_INFO_COMPONENT_UPDATE                       0x81
#define SL_SCL_INFO_J1939_INIT                             0x82
#define SL_SCL_INFO_PJ1939_INIT                            0x83
#define SL_SCL_INFO_CDL_INIT                               0x84
#define SL_SCL_INFO_J1939_UPDATE                           0x85
#define SL_SCL_INFO_PJ1939_UPDATE                          0x86
#define SL_SCL_INFO_RAILCAN_UPDATE                         0x87
#define SL_SCL_INFO_CDL_UPDATE                             0x88
#define SL_SCL_INFO_RAILCAN_ADD                            0x89
#define SL_SCL_INFO_HANDLE_GEN                             0x8A
#define SL_SCL_INFO_OBD_INIT                               0x8B

/* Function code for Diagnotics Client block*/
#define SL_J1939_DM13_ADD_CLIENT                           0x8C
#define SL_J1939_DM13_INIT                                 0x8D
#define SL_J1939_DM13_UPDATE                               0x8E
#define SL_J1939_DM_CLEAR_UPDATE                           0x8F

/* Function code for SCL block*/
#define SL_J1939_TX_BLOCK_UPDATE                           0x90

/* Function code for J1939 Setup block*/
#define SL_J1939_PPGN_INIT                                 0x91
#define SL_J1939_CONNECTION_MGMR_INIT                      0x92
#define SL_J1939_ADD_ECM                                   0x93

/* Function code for Mod Bus block*/
#define SL_SCL_MODBUS_INIT                                 0x94
#define SL_SCL_MODBUS_UPDATE                               0x95
#define SL_SCL_MODBUS_MASTER_SLAVE_REG                     0x96

/* Function code for SCL PMS block*/
#define SL_SCL_PMS_UPDATE                                  0x97
#define SL_SCL_PMS_ADD_EVENT                               0x98
#define SL_SCL_PMS_REMOVE_EVENT                            0x99

/* Function code for SCL Snapshot block*/
#define SL_SCL_SNAPSHOT_PJ1939_INIT                        0x9A
#define SL_SCL_SNAPSHOT_CDL_INIT                           0x9B
#define SL_SCL_SNAPSHOT_RTC_INIT                           0x9C
#define SL_SCL_SNAPSHOT_INIT                               0x9D
#define SL_SCL_SNAPSHOT_UPDATE                             0x9E
#define SL_SCL_SNAPSHOT_J1939_INIT                         0x9F

/* Function code for Diagnotics Manager block*/      
#define SL_SCL_FAULT_TABLE_PEER                            0xA1
        
#endif /* SL_OELRTOS_ERROR_DEFS_H_ */