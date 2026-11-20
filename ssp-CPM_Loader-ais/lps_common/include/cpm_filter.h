/*******************************************************************************
 ** COPYRIGHT (C) 2015 CATERPILLAR INC. ALL RIGHTS RESERVED.
 --------------------------------------------------------------------------------
 FILE NAME: cpm_filter.h 
 DESCRIPTION: low pass and abnd_stop filter header file for declarations.
 Dev Name: Subba Gundala
 Date: Sep/24/2015 
 *******************************************************************************/
#ifndef __CPM_FILTER_H__
#define __CPM_FILTER_H__
/*******************************************************************************
 ** -- #Include's --
 *******************************************************************************/
#include <stdbool.h>
//#include <std_types.h>

/*******************************************************************************
 ** -- #Define, Struct's, Typedef's, Enum's --
 *******************************************************************************/
#define SQUARE(a)  ((a) * (a))
#define CUBE(a) ((a) * (a) * (a))
#define PI  (float) 3.14159265358979323846264338327
#define LP_FLT_CF_TO_KFF(CF,T)    ((float) ( 2.0 * PI * CF * T))

typedef struct LPFILT
{
	float cf;
	float ts;
	bool  init;
	float gain_a;
	float gain_b;
	float ystate;
	float yprimestate;
} LPFILT;

typedef struct
{
	bool init;
	float kff;
	float y;
} LPFILT2;

typedef struct  {
    float   cf;
    float   damping;
    float   ts;
    bool    init;
    float   alpha;
    float   beta;
    float   gamma;
    float   input[3];  
    float   output[3];
} BSFILT;

typedef struct
{
    bool init;
    float kff;
    float ts;
    float y[3];
    float d;
} DERFILT;

/*******************************************************************************
 ** -- Function Prototypes --
 *******************************************************************************/

#if defined (__cplusplus)
extern "C"
{
#endif

extern void cpm_filter_low_pass_filter_init(LPFILT* pw, float cf, float ts);
extern void cpm_filter_low_pass_filter_reset(LPFILT* px, float input);
extern void cpm_filter_low_pass_filter(LPFILT *px, float input);

extern void cpm_filter_band_stop_filter_init(BSFILT* pw, float cf, float damping, float ts);
extern void cpm_filter_band_stop_filter_reset(BSFILT* pw);
extern float cpm_filter_band_stop_filter(BSFILT *px, float input);

extern void cpm_filter_low_pass_filter2_init(LPFILT2* pw, float kff);
extern void cpm_filter_low_pass_filter2_reset(LPFILT2* pw);
extern float cpm_filter_low_pass_filter2(LPFILT2* pw, float input);

extern void cpm_filter_derivative_filter_init(DERFILT* pw, float kff, float ts);
extern void cpm_filter_derivative_filter_reset(DERFILT* pw);
extern float cpm_filter_derivative_filter(DERFILT* pw, float input);

#if defined (__cplusplus)
}
#endif


/*******************************************************************************
 ** -- Data Declarations --
 *******************************************************************************/

#endif /* #ifndef __CPM_FILTER_H__ */
