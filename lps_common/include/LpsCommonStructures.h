/*******************************************************************************
** COPYRIGHT (C) 2016 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: LPSCommonStructures.h
DESCRIPTION:
*******************************************************************************/
#ifndef __LPS_COMMON_STRUCTURES_H__
#define __LPS_COMMON_STRUCTURES_H__

/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <stdint.h>

#define CAL_EMPTY_BKT_CURVE_MASK     0x0004
#define CAL_FULL_BKT_CURVE_MASK      0x0008
#define CAL_BKT_WT_MASK              0x0010
#define CAL_LIFT_LINKAGE_MASK        0x0040
#define CAL_TILT_LINKAGE_MASK        0x0080
#define CAL_VELCAL                   0x0020

/* CDA UID64 Defs */
#define UID64_DIG_STATE              (int64_t)0x00A181FD15000005
#define UID64_DUMP_STATE             (int64_t)0x00A181FD15010005
#define UID64_CAL_STATE              (int64_t)0x00A181FD15020005
#define UID64_BEST_BUCKET_WEIGHT     (int64_t)0x00A181FD15030005
#define UID64_CAL_METHOD             (int64_t)0x00A181FD15040005
#define UID64_ZERO_NOTIFY_STATE      (int64_t)0x00A181FD15050005
#define UID64_LIFT_CYL_EXT_VEL       (int64_t)0x00A181FD150F0005

#define UID64_TRUCK_WEIGHT           (int64_t)0x00A181FD15070005
#define UID64_PASS_COUNT             (int64_t)0x00A181FD15080005
#define UID64_TARGET_WEIGHT          (int64_t)0x00A181FD15090005
#define UID64_MAT_ID                 (int64_t)0x00A181FD150A0005
#define UID64_MATERIAL_NAME          (int64_t)0x00A181FD150B0005
#define UID64_TIP_OFF_STATE          (int64_t)0x00A181FD150C0005
#define UID64_OPERATION_MODE         (int64_t)0x00A181FD150D0005

/* CDA Command Response UIDs */
#define UID64_WEIGH_APP_CMD        (int64_t)0x00A181FD15060009
#define UID64_WEIGH_APP_RESP       (int64_t)0x00A181FD1506000A
#define UID64_JOB_MGR_APP_CMD      (int64_t)0x00A181FD150E0009
#define UID64_JOB_MGR_APP_RESP     (int64_t)0x00A181FD150E000A

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/
typedef enum {
    LPS_STATUS_OK = 0,
	LPS_STATUS_BAD
} LpsStat_t;

typedef enum {
    LPS_HYD_OIL_TEMP_STATUS_OK = 0,
    LPS_HYD_OIL_TEMP_STATUS_BAD,
    LPS_HYD_OIL_TEMP_STATUS_DISABLED
} LpsHydOilTempSensorStat_t;

typedef enum {
    LPS_WEIGHT_BKT_DUMP_STATE_UNKNOWN = 0,
    LPS_WEIGHT_BKT_FULLY_RACKED,
    LPS_WEIGHT_BKT_NOT_RACKED_AND_NOT_DUMPED,
    LPS_WEIGHT_BKT_PARTIALLY_DUMPED,
    LPS_WEIGHT_BKT_FULLY_DUMPED
} LpsWeighBktDumpStat_t;

typedef enum {
    LPS_WEIGHT_BKT_DIG_STATE_UNKNOWN = 0,
    LPS_WEIGHT_BKT_NOT_DIGGING,
    LPS_WEIGHT_BKT_TENTATIVE_DIGGING,
    LPS_WEIGHT_BKT_DIGGING
} LpsWeighBktDigStat_t;

// This is not an enumeration because accuracy is compared >, <, >=, <=
typedef uint8_t LpsWeighBktWtAccuracy_t;
#define LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_NONE (0)
#define LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_LOW (1)
#define LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_MED (2)
#define LPS_WEIGH_BUCKET_WEIGHT_ACCURACY_HIGH (3)

typedef enum{
    LPS_TIPOFF_WEIGHT_INVALID = 0,
    LPS_TIPOFF_WEIGHT_LIVE = 1,
    LPS_TIPOFF_WEIGHT_PFW = 2,
} LpsTipoffWeightStat_t;

typedef struct {
    LpsTipoffWeightStat_t Stat;
    float Val;
} LpsTipoffWeight_t;

typedef struct {
    LpsStat_t Stat;
    float Val;
} LpsFloatIO_t;

typedef struct {
    LpsHydOilTempSensorStat_t Stat;
    float Val;
} LpsHydOilTemp_t;

typedef struct {
    LpsStat_t Stat;
    uint16_t Val;
} LpsEngineSpeedRPM_t;

typedef struct {
    LpsStat_t Stat;
	uint16_t Val;
} LpsRequestedGear_t;

typedef struct
{
    float LinAcc[3]; // Linear Acceleration Vector (m/s^2): x - FORWARD, y - RIGHT, z - DOWN
    float AngVel[3]; // Angular Velocity Vector (rad/s): x - FORWARD, y - RIGHT, z - DOWN
    float Pitch;
    float Roll;
    LpsStat_t Stat;
} LpsIMUData_t;

#endif /* #ifndef __LPS_COMMON_STRUCTURES_H__ */
