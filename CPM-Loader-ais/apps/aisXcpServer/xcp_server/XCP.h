/*******************************************************************************
** COPYRIGHT (C) 2007,2013 CATERPILLAR INC. ALL RIGHTS RESERVED.
** This work contains Caterpillar's proprietary information, which
** may constitute a trade secret and/or be confidential. Copyright
** notice is precautionary only and does not imply publication.
--------------------------------------------------------------------------------
FILE NAME:  XCP.h
DESCRIPTION:
*******************************************************************************/
#ifndef XCP_H_
#define XCP_H_

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdint.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/

//---------------------------------------------------------
// XCP protocol layer specification definitions
#define XCP_MAX_SEED_LENGTH 255
#define XCP_MAX_KEY_LENGTH  255

#define XCP_MAX_CTO 0xFF
#define XCP_MAX_DTO 0xFFFF

typedef enum XCP_BYTEORDER_T {
    /* BYTE_ORDER */
    XCP_BYTEORDER_MSBLAST = 0,
    XCP_BYTEORDER_MSBFIRST= 1,
} XCP_BYTEORDER_T;

typedef enum XCP_ADDRGRAN_T {
    /* ADDRESS_GRANULARITY */
    XCP_ADDRGRAN_1 = 1,
    XCP_ADDRGRAN_2 = 2,
    XCP_ADDRGRAN_4 = 4,
} XCP_ADDRGRAN_T;

typedef enum XCP_DAQCONFIG_TYPE_T {
    XCP_DAQCONFIG_STATIC  = 0,
    XCP_DAQCONFIG_DYNAMIC = 1,
} XCP_DAQCONFIG_TYPE_T;

typedef enum XCP_OPTTYPE_T {
    /* OPTIMISATION_TYPE */
    XCP_OPTTYPE_DEF           = 0,
    XCP_OPTTYPE_ODTTYPE16     = 1,
    XCP_OPTTYPE_ODTTYPE32     = 2,
    XCP_OPTTYPE_ODTTYPE64     = 3,
    XCP_OPTTYPE_ODTTYPEALIGN  = 4,
    XCP_OPTTYPE_MAXENTRYSIZE  = 5,
} XCP_OPT_TYPE_T;

typedef enum XCP_ADDREXT_T {
    /* ADDRESS_EXTENSION */
    XCP_ADDREXT_FREE  = 0,
    XCP_ADDREXT_ODT   = 1,
    XCP_ADDREXT_DAQ   = 3,
} XCP_ADDREXT_T;

typedef enum XCP_IDTYPE_T {
    /* IDENTIFICATION_FIELD */
    XCP_IDTYPE_ABS        = 0,
    XCP_IDTYPE_RELBYTE    = 1,
    XCP_IDTYPE_RELWORD    = 2,
    XCP_IDTYPE_RELWORDALIGNED = 3,
} XCP_IDTYPE_T;

typedef enum XCP_GRANDAQ_T {
    /* GRANULARITY_ODT_ENTRY_SIZE_DAQ */
    XCP_GRANDAQ_1 = 1,   // byte
    XCP_GRANDAQ_2 = 2,   // word/16 bits
    XCP_GRANDAQ_4 = 4,   // dword/32 bits
    XCP_GRANDAQ_8 = 8,   // dlong/64 bits
} XCP_GRANODTENTRY_T;

typedef enum XCP_OVRLOADIND_T {
    /* OVERLOAD_INDICATION */
    XCP_OVRLOADIND_NONE = 0,
    XCP_OVRLOADIND_PID = 1,
    XCP_OVRLOADIND_EVENT = 2,
} XCP_OVRLOADIND_T;

typedef enum XCP_GRANSTIM_T {
    /* GRANULARITY_ODT_ENTRY_SIZE_STIM */
    XCP_GRANSTIM_1     = 1,
    XCP_GRANSTIM_2     = 2,
    XCP_GRANSTIM_4     = 4,
    XCP_GRANSTIM_8     = 8,
} XCP_GRANSTIM_T;

typedef enum XCP_TIMESTSIZE_T {
    /* Timestamp size */
    XCP_TIMESTSIZE_NONE = 0,
    XCP_TIMESTSIZE_U8   = 1,
    XCP_TIMESTSIZE_U16  = 2,
    XCP_TIMESTSIZE_U32  = 4,
} XCP_TIMESTSIZE_T;

typedef enum XCP_TIMESTRES_T {
    /*  Timestamp resolution */
    XCP_TIMESTRES_1NS     = 0,
    XCP_TIMESTRES_10NS    = 1,
    XCP_TIMESTRES_100NS   = 2,
    XCP_TIMESTRES_1US     = 3,
    XCP_TIMESTRES_10US    = 4,
    XCP_TIMESTRES_100US   = 5,
    XCP_TIMESTRES_1MS     = 6,
    XCP_TIMESTRES_10MS    = 7,
    XCP_TIMESTRES_100MS   = 8,
    XCP_TIMESTRES_1S      = 9,
} XCP_TIMESTRES_T;

typedef enum XCP_DAQLISTTYPE_T {
    XCP_DAQLISTTYPE_DAQ = 1,
    XCP_DAQLISTTYPE_STIM = 2,
    XCP_DAQLISTTYPE_DAQSTIM = 3,
} XCP_DAQLISTTYPE_T;

//---------------------------------------------------------
// XCP implementation specific definitions

typedef enum XCP_TRANSPORT_LAYER_T {
    XCP_XPORT_UDP     = 0,
    XCP_XPORT_TCP     = 1,
    XCP_XPORT_CAN     = 2,
    XCP_XPORT_FLEXRAY = 3,
} XCP_TRANSPORT_LAYER_T;

typedef struct XCP_STD_INFO_T {
    // Non transport layer specific setup information.
    uint8_t Filler;
} XCP_STD_INFO_T;

typedef struct XCP_UDP_INFO_T {
    // UDP/IP specific setup information.
    uint32_t IPAddr;
    uint16_t Port;
} XCP_UDP_INFO_T;

typedef struct XCP_TCP_INFO_T {
    // TCP/IP specific setup information.
    uint32_t IPAddr;
    uint16_t Port;
} XCP_TCP_INFO_T;

typedef struct XCP_CAN_INFO_T {
    // CAN specific setup information.
    uint32_t CTOHeader;
    uint32_t DTOHeader;
} XCP_CAN_INFO_T;

typedef struct XCP_FLEXRAY_INFO_T {
    // Flexray specific setup information
    uint8_t Placeholder;
} XCP_FLEXRAY_INFO_T;


// Packet codes for slave responses
#define XCP_SLAVE_CMD_RESP_PACKET           0xFF
#define XCP_SLAVE_ERROR_PACKET          0xFE
#define XCP_SLAVE_EVENT_PACKET          0xFD
#define XCP_SLAVE_SERV_PACKET               0xFC

//Note: Commands are in the range 0xC0 to 0xFF
// mandatory commands
#define XCP_CMD_CONNECT                   0xFF
#define XCP_CMD_DISCONNECT                0xFE
#define XCP_CMD_GET_STATUS                0xFD
#define XCP_CMD_SYNCH                     0xFC

//optional commands
#define XCP_CMD_GET_COMM_MODE_INFO        0xFB
#define XCP_CMD_GET_ID                    0xFA
#define XCP_CMD_SET_REQUEST               0xF9
#define XCP_CMD_GET_SEED                  0xF8
#define XCP_CMD_UNLOCK                    0xF7
#define XCP_CMD_SET_MTA                   0xF6
#define XCP_CMD_UPLOAD                    0xF5
#define XCP_CMD_SHORT_UPLOAD              0xF4
#define XCP_CMD_BUILD_CHECKSUM            0xF3
#define XCP_CMD_TRANSPORT_LAYER_CMD       0xF2
#define XCP_CMD_USER_CMD                  0xF1
#define XCP_CMD_DOWNLOAD                  0xF0
#define XCP_CMD_DOWNLOAD_NEXT             0xEF
#define XCP_CMD_DOWNLOAD_MAX              0xEE
#define XCP_CMD_SHORT_DOWNLOAD            0xED
#define XCP_CMD_MODIFY_BITS               0xEC
#define XCP_CMD_SET_CAL_PAGE              0xEB
#define XCP_CMD_GET_CAL_PAGE              0xEA
#define XCP_CMD_GET_PAG_PROCESSOR_INFO    0xE9
#define XCP_CMD_GET_SEGMENT_INFO          0xE8
#define XCP_CMD_GET_PAGE_INFO             0xE7
#define XCP_CMD_SET_SEGMENT_MODE          0xE6
#define XCP_CMD_GET_SEGMENT_MODE          0xE5
#define XCP_CMD_COPY_CAL_PAGE             0xE4
#define XCP_CMD_CLEAR_DAQ_LIST            0xE3
#define XCP_CMD_SET_DAQ_PTR               0xE2
#define XCP_CMD_WRITE_DAQ                 0xE1
#define XCP_CMD_SET_DAQ_LIST_MODE         0xE0
#define XCP_CMD_GET_DAQ_LIST_MODE         0xDF
#define XCP_CMD_START_STOP_DAQ_LIST       0xDE
#define XCP_CMD_START_STOP_SYNCH          0xDD
#define XCP_CMD_GET_DAQ_CLOCK             0xDC
#define XCP_CMD_READ_DAQ                  0xDB
#define XCP_CMD_GET_DAQ_PROCESSOR_INFO    0xDA
#define XCP_CMD_GET_DAQ_RESOLUTION_INFO   0xD9
#define XCP_CMD_GET_DAQ_LIST_INFO         0xD8
#define XCP_CMD_GET_DAQ_EVENT_INFO        0xD7
#define XCP_CMD_FREE_DAQ                  0xD6
#define XCP_CMD_ALLOC_DAQ                 0xD5
#define XCP_CMD_ALLOC_ODT                 0xD4
#define XCP_CMD_ALLOC_ODT_ENTRY           0xD3
#define XCP_CMD_PROGRAM_START             0xD2
#define XCP_CMD_PROGRAM_CLEAR             0xD1
#define XCP_CMD_PROGRAM                   0xD0
#define XCP_CMD_PROGRAM_RESET             0xCF
#define XCP_CMD_GET_PGM_PROCESSOR_INFO    0xCE
#define XCP_CMD_GET_SECTOR_INFO           0xCD
#define XCP_CMD_PROGRAM_PREPARE           0xCC
#define XCP_CMD_PROGRAM_FORMAT            0xCB
#define XCP_CMD_PROGRAM_NEXT              0xCA
#define XCP_CMD_PROGRAM_MAX               0xC9
#define XCP_CMD_PROGRAM_VERIFY            0xC8
#define XCP_CMD_WRITE_DAQ_MULTIPLE        0xC7

#define XCP_CMD_MINVALUE                0xC0 // Commands starte here.. 0xC0-0xFF.
// CAN specific transport layer commands.
#define XCP_CANTPL_CMD_GET_SLAVE_ID     0xFF
#define XCP_CANTPL_CMD_GET_DAQ_ID           0xFE
#define XCP_CANTPL_CMD_SET_DAQ_ID           0xFD

// XCP Error Codes
#define XCP_ERR_CMD_SYNCH         0x00
#define XCP_ERR_CMD_BUSY          0x10
#define XCP_ERR_DAQ_ACTIVE        0x11
#define XCP_ERR_PGM_ACTIVE        0x12
#define XCP_ERR_CMD_UNKNOWN       0x20
#define XCP_ERR_CMD_SYNTAX        0x21
#define XCP_ERR_OUT_OF_RANGE      0x22
#define XCP_ERR_WRITE_PROTECTED   0x23
#define XCP_ERR_ACCESS_DENIED     0x24
#define XCP_ERR_ACCESS_LOCKED     0x25
#define XCP_ERR_PAGE_NOT_VALID    0x26
#define XCP_ERR_MODE_NOT_VALID    0x27
#define XCP_ERR_SEGMENT_NOT_VALID 0x28
#define XCP_ERR_SEQUENCE          0x29
#define XCP_ERR_DAQ_CONFIG        0x2A

#define XCP_ERR_MEMORY_OVERFLOW   0x30
#define XCP_ERR_GENERIC           0x31
#define XCP_ERR_VERIFY            0x32
#define XCP_ERR_TEMPNOACCESS        0x33

#define XCP_EV_RESUME_MODE      0x00 //Slave starting in RESUME mode S0
#define XCP_EV_CLEAR_DAQ            0x01 //The DAQ configuration in non-volatile memory has been cleared. S0
#define XCP_EV_STORE_DAQ            0x02 //The DAQ configuration has been stored into non-volatile memory. S0
#define XCP_EV_STORE_CAL            0x03 //The calibration data has been stored into non-volatile memory. S0
#define XCP_EV_CMD_PENDING      0x05 //Slave requesting to restart time-out S1
#define XCP_EV_DAQ_OVERLOAD     0x06 //DAQ processor overload. S1
#define XCP_EV_SESSION_TERMINATED   0x07 //Session terminated by slave device. S3
#define XCP_EV_TIME_SYNC            0x08 //Transfer of externally triggered timestamp S0
#define XCP_EV_STIM_TIMEOUT     0x09 //Indication of a STIM timeout S0-S3
#define XCP_EV_SLEEP                0x0A //Slave entering SLEEP mode S1
#define XCP_EV_WAKE_UP          0x0B //Slave leaving SLEEP mode S1
#define XCP_EV_USER             0xFE //User-defined event S0
#define XCP_EV_TRANSPORT            0xFF //Transport layer specific event Ref. Part3

#define XCP_SERV_RESET  0x00 //Slave requesting to be reset
#define XCP_SERV_TEXT       0x01 //Slave transferring a byte stream of plain ASCII text. The line separator is LF or CR/LF. The text can be transferred in consecutive packets. The end of the overall text is indicated by the last packet containing a Null terminated string.

#define XCP_MAX_DAQ_LISTS       252 // XCP Protocol Max is 252 (0 to 251), as this is communicated in an 8 bit field, and has to be less than the command responses
#define XCP_MAX_DAQ_ODTS        252 // XCP Protocol Max is 252 (0 to 251), as this is communicated in an 8 bit field, and has to be less than the command responses
                                    // Although technically, on CAN, may be able to go above this if PID_OFF is used...
#define XCP_MAX_ODT_ENTRIES 255 // XCP Protocol Max is 255, as this is communicated in an 8 bit field.


// bit masks for RESOURCE
#define XCP_RESOURCE_PGM        0x10
#define XCP_RESOURCE_STIM       0x08
#define XCP_RESOURCE_DAQ        0x04
#define XCP_RESOURCE_CALPAG 0x01

// Bit masks for COMM_MODE_BASIC
#define XCP_COMMMODEBASIC_OPTIONAL      0x80
#define XCP_COMMMODEBASIC_SLAVEBLOCKMODE    0x40
#define XCP_COMMMODEBASIC_AG            0x06    // 00 = byte, 01 = word, 10 = double word, 11 = reserved
#define XCP_COMMMODEBASIC_AG1           0x04
#define XCP_COMMMODEBASIC_AG0           0x02    //
#define XCP_COMMMODEBASIC_BYTEORDER         0x01    // 1 = MSB first, 0 = LSB first

// Bit masks for DAQ_PROPERTIES in GET_DAQ_PROCESSOR_INFO response

#define XCP_DAQPROCINFO_OVERLOADEVENT           0x80    // overload indication method
#define XCP_DAQPROCINFO_OVERLOADMSB         0x40    // overload indication method
#define XCP_DAQPROCINFO_OVERLOADINDMETHOD       0xC0    // mask for the above two bits
#define XCP_DAQPROCINFO_PIDOFFSUPPORTED     0x20    // 0 = not supported, 1 = supported
#define XCP_DAQPROCINFO_TIMESTAMPSUPPORTED  0x10    // 0 = not supported, 1 = supported
#define XCP_DAQPROCINFO_BITSTIMSUPPORTED        0x08    // 0 = not supported, 1 = supported
#define XCP_DAQPROCINFO_RESUMESUPPORTED     0x04    // 0 = not supported, 1 = supported
#define XCP_DAQPROCINFO_PRESCALERSUPPORTED  0x02    // 0 = not supported, 1 = supported
#define XCP_DAQPROCINFO_DAQCONFIGTYPE           0x01    // List configuration.  0 = static, 1 = dynamic

#define XCP_DAQPROCINFO_DAQCONFIGTYPE_STATIC 0x00
#define XCP_DAQPROCINFO_DAQCONFIGTYPE_DYNAMIC 0x01

// Bit Masks for TIMESTAMP_MODE in GET_DAQ_RESOLUTION_INFO
#define XCP_DAQRESINFO_TSMODE_UNITMASK  0xF0        // Unit, 4 bits
#define XCP_DAQRESINFO_TSMODE_TSFIXED     0x08      // 1 = fixed, always sent
#define XCP_DAQRESINFO_TSMODE_SIZE        0x07      // 0 = no TS, 1 = 1, 2 = 2, 4 = 4, others not allowed.


// XCP_DAQPROCINFO_OVERLOADEVENT and XCP_DAQPROCINFO_OVERLOADMSB incidate overload indication method
#define XCP_OVERLOADMETHOD_NOINDICATION   0x0
#define XCP_OVERLOADMETHOD_MSBOFPID     0x1     // When this is used, Max ODT number is 0x7B
#define XCP_OVERLOADMETHOD_EVENTPACKET      0x2
#define XCP_OVERLOADMETHOD_NOTALLOWED       0x3

#define XCP_DAQKEYBYTE_IDFIELDMASK      0xC0
#define XCP_DAQKEYBYTE_ADDRESSEXTMASK       0x30
#define XCP_DAQKEYBYTE_OPTIMIZATIONMASK     0x0F

// values for XCP_DAQKEYBYTE_IDFIELDMASK
// This defines the header format of the DTO messages containing DAQ broadcasts.
// Note, this could also be followed by a timestamp field.
#define XCP_IDFIELD_ABSOLUTEODTNUM          0x0 // header is {U8 AbsODT}
#define XCP_IDFIELD_RELODTABSDAQBYTE        0x1 // header is {U8 RelODT, U8 AbsDAQ}
#define XCP_IDFIELD_RELODTABSDAQWORD        0x2 // header is {U8 RelODT, U16 AbsDAQ}
#define XCP_IDFIELD_RELODTABSDAQWORDALIGNED     0x3 // header is {U8 RelODT, U8 Fill, U16 AbsDAQ}
// values for XCP_DAQKEYBYTE_ADDRESSEXTMASK
#define XCP_ADDEXT_DIFFERENTINODT   0x0
#define XCP_ADDEXT_SAMEINODT        0x1
#define XCP_ADDEXT_NOTALLOWED       0x2
#define XCP_ADDEXT_SAMEINDAQ        0x3
// values for XCP_DAQKEYBYTE_OPTIMIZATIONMASK
// These indicate the type of optimisation method the master preferably should use.
#define XCP_OPTIMIZATION_DEFAULT        0x0
#define XCP_OPTIMIZATION_ODTTYPE16  0x1
#define XCP_OPTIMIZATION_ODTTYPE32  0x2
#define XCP_OPTIMIZATION_ODTTYPE64  0x3
#define XCP_OPTIMIZATION_ODTTYPEALIGN 0x4
#define XCP_OPTIMIZATION_MAXENTRYSIZE 0x5

#define XCP_SETDAQLISTMODE_MODE_ALTERNATING 0x01    // bit value of 0 to disable, 1 to enable
#define XCP_SETDAQLISTMODE_MODE_DIRECTION       0x02    // bit value of 0 for DAQ, 1 for STIM
#define XCP_SETDAQLISTMODE_MODE_TIMESTAMP       0x10    // 0 to disable, 1 to enable
#define XCP_SETDAQLISTMODE_MODE_PID_OFF     0x20    // 1 to turn PID off.


#define XCP_SESSIONSTATUS_DAQRUNNING 0x40
// Event Time Cycle defs

#define XCP_EVENT_TU_1NS        0x0
#define XCP_EVENT_TU_10NS       0x1
#define XCP_EVENT_TU_100NS  0x2
#define XCP_EVENT_TU_1US        0x3
#define XCP_EVENT_TU_10US       0x4
#define XCP_EVENT_TU_100US  0x5
#define XCP_EVENT_TU_1MS        0x6
#define XCP_EVENT_TU_10MS       0x7
#define XCP_EVENT_TU_100MS  0x8
#define XCP_EVENT_TU_1S     0x9
#define XCP_EVENT_TU_1PS        0xA
#define XCP_EVENT_TU_10PS       0xB
#define XCP_EVENT_TU_100PS  0xC

#define XCP_EVENTPROP_CONSISTENCY_EVENT     0x80
#define XCP_EVENTPROP_CONSISTENCY_DAQ   0x40
#define XCP_EVENTPROP_STIM              0x08
#define XCP_EVENTPROP_DAQ               0x04

//----------------------------------------
#define XCP_DAQLISTINFO_DAQLISTPROP_STIM         0x08
#define XCP_DAQLISTINFO_DAQLISTPROP_DAQ          0x04
#define XCP_DAQLISTINFO_DAQLISTPROP_EVENTFIXED 0x02
#define XCP_DAQLISTINFO_DAQLISTPROP_PREDEFINED 0x01

#define XCP_STARTSTOPDAQLIST_MODE_STOP      0x00
#define XCP_STARTSTOPDAQLIST_MODE_START     0x01
#define XCP_STARTSTOPDAQLIST_MODE_SELECT        0x02

#define XCP_STARTSTOPSYNCH_STOPALL      0x00
#define XCP_STARTSTOPSYNCH_STARTSEL     0x01
#define XCP_STARTSTOPSYNCH_STOPSEL      0x02

typedef struct XCP_EVENT_T {
    // Properties.
    uint16_t ChannelNumber;      // Event Channel ID
    uint8_t Properties;          // 0x80 CONSISTENCY_EVENT
                            // 0x40 CONSISTENCY_DAQ
                            // 0x08 STIM
                            // 0x04 DAQ

    uint8_t MaxDAQList;          // Number of DAQ lists that can be assigned this event.
                            // 0xFF = no limit
    uint8_t TimeCycle;           // 0 = not cyclic
    uint8_t TimeUnit;            // don't care, if time cycle == 0
    uint8_t Priority;            //
    // ------------------
    // uint8_t NumDAQsAssignedTo;    // For assignment tracking purposes.
                            // Does client need to keep track of this?  Channels should explicitly
                            // define which event to use, so if event used too many times, should be
                            // caught in configuration validation, or at run time during setup.
                            // If checking at run time setup, or during packing, either way would have
                            // to error out.
} XCP_EVENT_T;

typedef struct XCP_ODT_T {
    // uint8_t BitOffset;        // Not using
    uint8_t Size;
    uint8_t AddressExtension;
    uint32_t Address;
} XCP_ODT_T;
/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/
/*******************************************************************************
** -- Data Declarations
*******************************************************************************/
#endif /* XCP_H_ */
