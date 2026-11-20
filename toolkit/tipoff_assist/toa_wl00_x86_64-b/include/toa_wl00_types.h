/******************************************************************************
 ** COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
 ** The information hereon is the property of Caterpillar Inc.
 ** and/or its subsidiaries.  Without written permission, any copying,
 ** transmittal to others, and any use except that for which it is loaned is
 ** prohibited.
 **-----------------------------------------------------------------------------
 ** File: toa_wl00_types.h
 **
 ** Real-Time Workshop code generated for Simulink model toa_wl00.
 **
 ** Model version                        : 1.44
 ** Real-Time Workshop file version      : 8.13 (R2017b) 24-Jul-2017
 ** TLC version                          : 8.13 (Jul 25 2017)
 ** CATutils_MatLab version              : CATUTILS_MATLAB_4.6.1
 **
 ******************************************************************************/

/******************************************************************************
 ** -- #Includes --
 ******************************************************************************/
#ifndef RTW_HEADER_toa_wl00_types_h_
#define RTW_HEADER_toa_wl00_types_h_
#include "std_t.h"

/******************************************************************************
 ** -- Defines, Structs, Typedefs, Enums --
 ******************************************************************************/
enum {
  TipAssistCpmTipOffMode_t_TIP_OFF_MODE_TRUCK = 1,
  TipAssistCpmTipOffMode_t_TIP_OFF_MODE_PILE = 2
};

typedef uint_least8_t TipAssistCpmTipOffMode_t;
enum {
  TipAssistSecPfwStatus_t_INVALID = 0,
  TipAssistSecPfwStatus_t_VALID_MEASURING = 1,
  TipAssistSecPfwStatus_t_PENDING = 2,
  TipAssistSecPfwStatus_t_FAULT = 3,
  TipAssistSecPfwStatus_t_VALID_NOT_MEASURING = 4
};

typedef uint_least8_t TipAssistSecPfwStatus_t;
enum {
  TipAssistLiveWeighStatus_t_VALID = 0,
  TipAssistLiveWeighStatus_t_FAULT = 1
};

typedef uint_least8_t TipAssistLiveWeighStatus_t;
enum {
  TipAssistUnsecPfwStatus_t_INVALID = 0,
  TipAssistUnsecPfwStatus_t_VALID = 1,
  TipAssistUnsecPfwStatus_t_PENDING = 2,
  TipAssistUnsecPfwStatus_t_FAULT = 3
};

typedef uint_least8_t TipAssistUnsecPfwStatus_t;
enum {
  TipAssistAdvEcmError_t_NO_ERROR = 0,
  TipAssistAdvEcmError_t_TIP_OFF_MODE_NOT_PILE = 1,
  TipAssistAdvEcmError_t_TRUCK_TARGET_NOT_SET = 2,
  TipAssistAdvEcmError_t_PAYLOAD_NOT_ACHIEVABLE = 3,
  TipAssistAdvEcmError_t_FAULT = 4
};

typedef uint_least8_t TipAssistAdvEcmError_t;
enum {
  TipAssistPayloadType_t_LIVE = 0,
  TipAssistPayloadType_t_PSEUDO_FRICTIONLESS = 1
};

typedef uint_least16_t TipAssistPayloadType_t;
enum {
  TipAssistSendCpmStatus_t_INVALID = 0,
  TipAssistSendCpmStatus_t_LIVE = 1,
  TipAssistSendCpmStatus_t_PSEUDO_FRICTIONLESS = 2
};

typedef uint_least8_t TipAssistSendCpmStatus_t;

/* Forward declaration for rtModel */
typedef struct tag_RTM_toa_wl00 RT_MODEL_toa_wl00;

/******************************************************************************
 ** -- Function Prototypes --
 ******************************************************************************/
/******************************************************************************
 ** -- Data Declarations --
 ******************************************************************************/

/******************************************************************************
 ** -- Functions --
 ******************************************************************************/
#endif                                 /* RTW_HEADER_toa_wl00_types_h_ */
