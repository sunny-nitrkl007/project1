#ifndef AC_MAP_PROTO_H_
#define AC_MAP_PROTO_H_
/******************************************************************************
**          COPYRIGHT (C) CATERPILLAR INC. ALL RIGHTS RESERVED
**         This work contains proprietary information, which may
**         constitute a trade secret and/or be confidential.
-------------------------------------------------------------------------------
DESCRIPTION:
This file contains prototypes for the ac_map routines.  The core functions are
intended for use by the real-time embedded application and the Simulink
simulation s-functions.

FILE NAME : ac_map_proto.h

******************************************************************************/

/******************************************************************************
** -- Includes --
******************************************************************************/
#include <std_t.h>

/******************************************************************************
** -- Defines, Structs, Typedefs, Enums --
******************************************************************************/

/******************************************************************************
** -- Function Prototypes --
******************************************************************************/
uint32_t ac_map_ratio_multiply_32(uint32_t in0,
                                     int32_t      in1);

uint32_t ac_map_ratio_divide_u32(uint32_t numerator,
                                    uint32_t denominator,
                                    uint32_t radix);

uint8_t
ac_map_lookup_sequential_u8(uint8_t  val,
                            uint8_t  *axis,
                            uint8_t  num_points,
                            uint8_t  *past_index);

uint8_t
ac_map_lookup_sequential_s8(int8_t       val,
                            int8_t       *axis,
                            uint8_t  num_points,
                            uint8_t  *past_index);

uint16_t
ac_map_lookup_sequential_u16(uint16_t  val,
                             uint16_t  *axis,
                             uint16_t  num_points,
                             uint16_t  *past_index);

uint16_t
ac_map_lookup_sequential_s16(int16_t       val,
                             int16_t       *axis,
                             uint16_t  num_points,
                             uint16_t  *past_index);

uint32_t
ac_map_lookup_sequential_u32(uint32_t  val,
                             uint32_t  *axis,
                             uint32_t  num_points,
                             uint32_t  *past_index);

uint32_t
ac_map_lookup_sequential_s32(int32_t       val,
                             int32_t       *axis,
                             uint32_t  num_points,
                             uint32_t  *past_index);

#if ! defined (__CSMC__)
uint32_t
ac_map_lookup_sequential_r32(float      val,
                             float      *axis,
                             uint32_t  num_points,
                             uint32_t  *past_index);

uint32_t
ac_map_lookup_sequential_r64(double      val,
                             double      *axis,
                             uint32_t  num_points,
                             uint32_t  *past_index);

uint32_t
ac_map_lookup_bisection_r32(float      val,
                            float      *axis,
                            uint32_t  num_points);

uint32_t
ac_map_lookup_bisection_r64(double      val,
                            double      *axis,
                            uint32_t  num_points);

uint32_t
ac_map_lookup_interp_sequential_r32(float      val,
                                    float      *axis,
                                    uint32_t  num_points,
                                    uint32_t  *past_index,
                                    float      *ratio);

uint32_t
ac_map_lookup_interp_sequential_r64(double      val,
                                    double      *axis,
                                    uint32_t  num_points,
                                    uint32_t  *past_index,
                                    double      *ratio);

uint32_t
ac_map_lookup_interp_bisection_r32(float      val,
                                   float      *axis,
                                   uint32_t  num_points,
                                   float      *ratio);

uint32_t
ac_map_lookup_interp_bisection_r64(double      val,
                                   double      *axis,
                                   uint32_t  num_points,
                                   double      *ratio);

float
ac_map_interp_linear_2D_r32(float     *dep_axis,
                            uint32_t  index,
                            float      ratio);

double
ac_map_interp_linear_2D_r64(double     *dep_axis,
                            uint32_t  index,
                            double      ratio);

float
ac_map_interp_linear_3D_r32(float      *axis,
                            uint32_t  x_index,
                            uint32_t  y_index,
                            float      x_ratio,
                            float      y_ratio,
                            uint32_t  x_size);

double
ac_map_interp_linear_3D_r64(double      *axis,
                            uint32_t  x_index,
                            uint32_t  y_index,
                            double      x_ratio,
                            double      y_ratio,
                            uint32_t  x_size);
float
ac_map_interp_linear_4D_r32(float    *axis,
						  uint32_t  index1,
						  uint32_t  index2,
						  uint32_t  index3,
						  float      ratio1,
						  float      ratio2,
						  float      ratio3,
						  uint32_t  size1,
                          uint32_t  size2);

double
ac_map_interp_linear_4D_r64(double    *axis,
						  uint32_t  index1,
						  uint32_t  index2,
						  uint32_t  index3,
						  double      ratio1,
						  double      ratio2,
						  double      ratio3,
						  uint32_t  size1,
                          uint32_t  size2);

float
ac_map_interp_linear_ND_r32(float     *dep_array,
                            uint8_t  num_inputs,
                            uint32_t *start_offset,
                            uint32_t *index,
                            float     *ratio);

double
ac_map_interp_linear_ND_r64(double     *dep_array,
                            uint8_t  num_inputs,
                            uint32_t *start_offset,
                            uint32_t *index,
                            double     *ratio);

#endif

/*****************************************************************************/

uint8_t
ac_map_lookup_bisection_u8(uint8_t  val,
                           uint8_t  *axis,
                           uint8_t  num_points);

uint8_t
ac_map_lookup_bisection_s8(int8_t       val,
                           int8_t       *axis,
                           uint8_t  num_points);

uint16_t
ac_map_lookup_bisection_u16(uint16_t  val,
                            uint16_t  *axis,
                            uint16_t  num_points);

uint16_t
ac_map_lookup_bisection_s16(int16_t       val,
                            int16_t       *axis,
                            uint16_t  num_points);

uint32_t
ac_map_lookup_bisection_u32(uint32_t  val,
                            uint32_t  *axis,
                            uint32_t  num_points);

uint32_t
ac_map_lookup_bisection_s32(int32_t       val,
                            int32_t       *axis,
                            uint32_t  num_points);


/*****************************************************************************/
/*****************************************************************************/

uint8_t
ac_map_lookup_interp_sequential_u8(uint8_t  val,
                                   uint8_t  *axis,
                                   uint8_t  num_points,
                                   uint8_t  *past_index,
                                   uint8_t  *ratio);

uint8_t
ac_map_lookup_interp_sequential_s8(int8_t       val,
                                   int8_t       *axis,
                                   uint8_t  num_points,
                                   uint8_t  *past_index,
                                   uint8_t  *ratio);

uint16_t
ac_map_lookup_interp_sequential_u16(uint16_t  val,
                                    uint16_t  *axis,
                                    uint16_t  num_points,
                                    uint16_t  *past_index,
                                    uint16_t  *ratio);

uint16_t
ac_map_lookup_interp_sequential_s16(int16_t       val,
                                    int16_t       *axis,
                                    uint16_t  num_points,
                                    uint16_t  *past_index,
                                    uint16_t  *ratio);

uint32_t
ac_map_lookup_interp_sequential_u32(uint32_t  val,
                                    uint32_t  *axis,
                                    uint32_t  num_points,
                                    uint32_t  *past_index,
                                    uint32_t  *ratio);

uint32_t
ac_map_lookup_interp_sequential_s32(int32_t       val,
                                    int32_t       *axis,
                                    uint32_t  num_points,
                                    uint32_t  *past_index,
                                    uint32_t  *ratio);


/*****************************************************************************/

uint8_t
ac_map_lookup_interp_bisection_u8(uint8_t  val,
                                  uint8_t  *axis,
                                  uint8_t  num_points,
                                  uint8_t  *ratio);

uint8_t
ac_map_lookup_interp_bisection_s8(int8_t       val,
                                  int8_t       *axis,
                                  uint8_t  num_points,
                                  uint8_t  *ratio);

uint16_t
ac_map_lookup_interp_bisection_u16(uint16_t  val,
                                   uint16_t  *axis,
                                   uint16_t  num_points,
                                   uint16_t  *ratio);

uint16_t
ac_map_lookup_interp_bisection_s16(int16_t       val,
                                   int16_t       *axis,
                                   uint16_t  num_points,
                                   uint16_t  *ratio);

uint32_t
ac_map_lookup_interp_bisection_u32(uint32_t  val,
                                   uint32_t  *axis,
                                   uint32_t  num_points,
                                   uint32_t  *ratio);

uint32_t
ac_map_lookup_interp_bisection_s32(int32_t       val,
                                   int32_t       *axis,
                                   uint32_t  num_points,
                                   uint32_t  *ratio);


/*****************************************************************************/
/*****************************************************************************/

uint8_t
ac_map_interp_linear_2D_u8(uint8_t  *dep_axis,
                           uint8_t   index,
                           uint8_t   ratio);

int8_t
ac_map_interp_linear_2D_s8(int8_t        *dep_axis,
                           uint8_t   index,
                           uint8_t   ratio);

uint16_t
ac_map_interp_linear_2D_u16(uint16_t *dep_axis,
                            uint16_t  index,
                            uint16_t  ratio);

int16_t
ac_map_interp_linear_2D_s16(int16_t      *dep_axis,
                            uint16_t  index,
                            uint16_t  ratio);

uint32_t
ac_map_interp_linear_2D_u32(uint32_t *dep_axis,
                            uint32_t  index,
                            uint32_t  ratio);

int32_t
ac_map_interp_linear_2D_s32(int32_t      *dep_axis,
                            uint32_t  index,
                            uint32_t  ratio);


/*****************************************************************************/
/*****************************************************************************/
uint8_t
ac_map_interp_linear_3D_u8(uint8_t  *axis,
                           uint8_t  x_index,
                           uint8_t  y_index,
                           uint8_t  x_ratio,
                           uint8_t  y_ratio,
                           uint8_t  x_size);

int8_t
ac_map_interp_linear_3D_s8(int8_t       *axis,
                           uint8_t  x_index,
                           uint8_t  y_index,
                           uint8_t  x_ratio,
                           uint8_t  y_ratio,
                           uint8_t  x_size);

uint16_t
ac_map_interp_linear_3D_u16(uint16_t  *axis,
                            uint16_t  x_index,
                            uint16_t  y_index,
                            uint16_t  x_ratio,
                            uint16_t  y_ratio,
                            uint16_t  x_size);

int16_t
ac_map_interp_linear_3D_s16(int16_t       *axis,
                            uint16_t  x_index,
                            uint16_t  y_index,
                            uint16_t  x_ratio,
                            uint16_t  y_ratio,
                            uint16_t  x_size);

uint32_t
ac_map_interp_linear_3D_u32(uint32_t  *axis,
                            uint32_t  x_index,
                            uint32_t  y_index,
                            uint32_t  x_ratio,
                            uint32_t  y_ratio,
                            uint32_t  x_size);

int32_t
ac_map_interp_linear_3D_s32(int32_t       *axis,
                            uint32_t  x_index,
                            uint32_t  y_index,
                            uint32_t  x_ratio,
                            uint32_t  y_ratio,
                            uint32_t  x_size);



/*****************************************************************************/
/*****************************************************************************/
uint8_t
ac_map_interp_linear_4D_u8(uint8_t  *axis,
                           uint8_t  index1,
                           uint8_t  index2,
                           uint8_t  index3,
                           uint8_t  ratio1,
                           uint8_t  ratio2,
                           uint8_t  ratio3,
                           uint8_t  size1,
                           uint16_t size2);

int8_t
ac_map_interp_linear_4D_s8(int8_t       *axis,
                           uint8_t  index1,
                           uint8_t  index2,
                           uint8_t  index3,
                           uint8_t  ratio1,
                           uint8_t  ratio2,
                           uint8_t  ratio3,
                           uint8_t  size1,
                           uint16_t size2);

uint16_t
ac_map_interp_linear_4D_u16(uint16_t *axis,
                           uint16_t  index1,
                           uint16_t  index2,
                           uint16_t  index3,
                           uint16_t  ratio1,
                           uint16_t  ratio2,
                           uint16_t  ratio3,
                           uint16_t  size1,
                           uint32_t  size2);

int16_t
ac_map_interp_linear_4D_s16(int16_t *axis,
                           uint16_t  index1,
                           uint16_t  index2,
                           uint16_t  index3,
                           uint16_t  ratio1,
                           uint16_t  ratio2,
                           uint16_t  ratio3,
                           uint16_t  size1,
                           uint32_t  size2);

uint32_t
ac_map_interp_linear_4D_u32(uint32_t *axis,
                           uint32_t  index1,
                           uint32_t  index2,
                           uint32_t  index3,
                           uint32_t  ratio1,
                           uint32_t  ratio2,
                           uint32_t  ratio3,
                           uint32_t  size1,
                           uint32_t  size2);

int32_t
ac_map_interp_linear_4D_s32(int32_t      *axis,
                           uint32_t  index1,
                           uint32_t  index2,
                           uint32_t  index3,
                           uint32_t  ratio1,
                           uint32_t  ratio2,
                           uint32_t  ratio3,
                           uint32_t  size1,
                           uint32_t  size2);



/*****************************************************************************/
/*****************************************************************************/

int8_t
ac_map_interp_linear_ND_s8(int8_t       *dep_array,
                           uint8_t  num_inputs,
                           uint16_t *start_offset,
                           uint8_t  *index,
                           uint8_t  *ratio);

uint8_t
ac_map_interp_linear_ND_u8(uint8_t  *dep_array,
                           uint8_t  num_inputs,
                           uint16_t *start_offset,
                           uint8_t  *index,
                           uint8_t  *ratio);

int16_t
ac_map_interp_linear_ND_s16(int16_t      *dep_array,
                            uint8_t  num_inputs,
                            uint32_t *start_offset,
                            uint16_t *index,
                            uint16_t *ratio);

uint16_t
ac_map_interp_linear_ND_u16(uint16_t *dep_array,
                            uint8_t  num_inputs,
                            uint32_t *start_offset,
                            uint16_t *index,
                            uint16_t *ratio);

int32_t
ac_map_interp_linear_ND_s32(int32_t      *dep_array,
                            uint8_t  num_inputs,
                            uint32_t *start_offset,
                            uint32_t *index,
                            uint32_t *ratio);

uint32_t
ac_map_interp_linear_ND_u32(uint32_t *dep_array,
                            uint8_t  num_inputs,
                            uint32_t *start_offset,
                            uint32_t *index,
                            uint32_t *ratio);


/******************************************************************************
** -- Data Declarations --
******************************************************************************/

#endif /* AC_MAP_PROTO_H_ */
