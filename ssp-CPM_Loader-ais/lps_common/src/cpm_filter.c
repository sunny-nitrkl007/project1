/*******************************************************************************
** COPYRIGHT (C) 2015 CATERPILLAR INC. ALL RIGHTS RESERVED.
--------------------------------------------------------------------------------
FILE NAME: prod_core_low_pass.c
DESCRIPTION: low pass filter function(s) implementation.
Dev Name: Subba Gundala
Date: Sep/24/2015 
*******************************************************************************/
/*******************************************************************************
** -- #Include's --
*******************************************************************************/
#include <cpm_filter.h>

/*******************************************************************************
** -- #Define, Struct's, Typedef's, Enum's --
*******************************************************************************/


/*******************************************************************************
** -- Function Prototypes --
*******************************************************************************/

/*******************************************************************************
** -- Data Declarations --
*******************************************************************************/

/******************************************************************************
FUNCTION NAME: cpm_filter_low_pass_filter_init
DESCRIPTION: Initializes the low pass filter.
PARAMETER DESCRIPTION:
    LPFILT* pw - pointer to the workspace structure
    float cf - the corner frequency in rad/s
    float ts - the sample period
RETURN VALUE: void
*******************************************************************************/
void cpm_filter_low_pass_filter_init(LPFILT* pw, float cf, float ts)
{
    pw->cf = cf;
    pw->ts = ts;
    pw->init = false;
}

/******************************************************************************
FUNCTION NAME: prod_core_low_pass_filter
DESCRIPTION:
PARAMETER DESCRIPTION: 
LPFILT *px 
float input
RETURN VALUE: void
*******************************************************************************/
//*********************************************************
//  gain_a  gain_b
// |1-2AT   -A^2T|  |    ylast   |  |  A^2T |
// |   T       1 |  | yprimelast |  |    0  |
//
// Backward approximation provides y' and y
//*********************************************************
void cpm_filter_low_pass_filter(LPFILT *px, float input)
{
    float nyprime,ny;

    // Have we been initialized yet?
    if (px->init == false)
    {
        px->gain_a = (float) 1.0 - ((float) 2.0 * px->cf * px->ts);
        px->gain_b = SQUARE(px->cf) * px->ts;
        px->ystate = input;
        px->yprimestate = (float) 0.0;
        px->init = true;
    }

    // Calculate the new variables based on the old
    nyprime = px->gain_a * px->yprimestate + px->gain_b * (input - px->ystate);
    ny = px->ystate + px->ts * px->yprimestate;

    // Transfer the new values back into the structure
    px->yprimestate = nyprime;
    px->ystate = ny;
}


/******************************************************************************
FUNCTION NAME: cpm_filter_low_pass_filter_reset
DESCRIPTION:
PARAMETER DESCRIPTION: 
LPFILT *px 
float input
RETURN VALUE: void
*******************************************************************************/
void cpm_filter_low_pass_filter_reset(LPFILT* px, float input)
{
    px->yprimestate = 0.0;
    px->ystate = input;
}

/******************************************************************************
FUNCTION NAME: cpm_filter_band_stop_filter_init
DESCRIPTION: Initializes the notch/band-stop filter.
PARAMETER DESCRIPTION:
    BSFILT* pw - pointer to the workspace structure
    float cf - the center frequency
    float damping - the damping coefficient
    float ts - the sample period
RETURN VALUE: void
*******************************************************************************/
void cpm_filter_band_stop_filter_init(BSFILT* pw, float cf, float damping, float ts)
{
    pw->cf = cf;
    pw->damping = damping;
    pw->ts = ts;
    pw->init = false;
}

/******************************************************************************
FUNCTION NAME: cpm_filter_band_stop_filter_reset
DESCRIPTION: Resets the notch/band-stop filter.
PARAMETER DESCRIPTION:
    BSFILT* pw - pointer to the workspace structure
RETURN VALUE: void
*******************************************************************************/
void cpm_filter_band_stop_filter_reset(BSFILT* pw)
{
    pw->init = false;
}

/******************************************************************************
FUNCTION NAME: cpm_filter_band_stop_filter
DESCRIPTION:
PARAMETER DESCRIPTION: 
LPFILT *px 
float input
RETURN VALUE: void
*******************************************************************************/
//*********************************************************
//  gain_a  gain_b
// |1-2AT   -A^2T|  |    ylast   |  |  A^2T |
// |   T       1 |  | yprimelast |  |    0  |
//
// Backward approximation provides y' and y
//*********************************************************
float cpm_filter_band_stop_filter(BSFILT *px, float newinput)
{
    float q,r,p,s,t;
    char x;

    // Determine the operating Coefficients (Efficiency Enhancer)
    if(px->init == false)
    {
        // Temporary Computations
        q = SQUARE(px->cf * px->ts / (float)2.0);
        r = px->cf * px->damping * px->ts;
        p = (1+q);
        s = (float) 2.0 * (q - 1);
        t = p+r;

        px->alpha = p / t;
        px->beta =  s / t;
        px->gamma = r / t;

        px->input[0] = px->input[1] = px->input[2] = newinput;
        px->output[0] = px->output[1]  = px->output[2] = newinput;

        px->init = true;
    }

    // Shift the last values in time
    for(x = 2; x > 0; x--)
    {
        unsigned char ux = (unsigned char)x;
        px->input[ux] = px->input[ux-1];
        px->output[ux] = px->output[ux-1];
    }

    px->input[0] = newinput;

    px->output[0] = (px->alpha * (px->input[0] + px->input[2] - px->output[2]));
    px->output[0] += (px->beta * (px->input[1] - px->output[1]));
    px->output[0] += (px->gamma * px->output[2]);
    return px->output[0];
}

/******************************************************************************
FUNCTION NAME: cpm_filter_low_pass_filter2_init
DESCRIPTION: Initialize the low pass filter
PARAMETER DESCRIPTION:
    LPFILT2* pw - pointer to the workspace structure
    float kff - the filter factor
RETURN VALUE: void
*******************************************************************************/
void cpm_filter_low_pass_filter2_init(LPFILT2* pw, float kff)
{
    pw->kff = kff;
    cpm_filter_low_pass_filter2_reset(pw);
}

/******************************************************************************
FUNCTION NAME: cpm_filter_low_pass_filter2_reset
DESCRIPTION: Resets the low pass filter
PARAMETER DESCRIPTION:
    LPFILT2* pw - pointer to the workspace structure
RETURN VALUE: void
*******************************************************************************/
void cpm_filter_low_pass_filter2_reset(LPFILT2* pw)
{
    pw->init = false;
    pw->y = 0.f;
}

/******************************************************************************
FUNCTION NAME: cpm_filter_low_pass_filter2
DESCRIPTION: Updated the low pass filter
PARAMETER DESCRIPTION:
    LPFILT2* pw - pointer to the workspace structure
    float input - the new input sample
RETURN VALUE: float - the filtered value
*******************************************************************************/
float cpm_filter_low_pass_filter2(LPFILT2* pw, float input)
{
    float y_prev = pw->y;

    // Have we been initialized yet?
    if (pw->init == false) {
        y_prev = input;
        pw->init = true;
    }

    float y = pw->kff * input + (1-pw->kff) * y_prev;

    pw->y = y;

    return y;
}

/******************************************************************************
FUNCTION NAME: cpm_filter_derivative_filter_init
DESCRIPTION: Initializes the filtered derivative.
PARAMETER DESCRIPTION:
    DERFILT* pw - pointer to the workspace structure
    float kff - the filter factor
    float ts - the sample period
RETURN VALUE: void
*******************************************************************************/
void cpm_filter_derivative_filter_init(DERFILT* pw, float kff, float ts)
{
    pw->kff = kff;
    pw->ts = ts;
    cpm_filter_derivative_filter_reset(pw);
}

/******************************************************************************
FUNCTION NAME: cpm_filter_derivative_filter_reset
DESCRIPTION: Resets the filtered derivative.
PARAMETER DESCRIPTION:
    DERFILT* pw - pointer to the workspace structure
RETURN VALUE: void
*******************************************************************************/
void cpm_filter_derivative_filter_reset(DERFILT* pw)
{
    pw->init = false;
    pw->y[0] = 0.f;
    pw->y[1] = 0.f;
    pw->y[2] = 0.f;
    pw->d = 0.f;
}

/******************************************************************************
FUNCTION NAME: cpm_filter_derivative_filter
DESCRIPTION: Updates the filtered derivative.
PARAMETER DESCRIPTION:
    DERFILT* pw - pointer to the workspace structure
    float input - the new input sample
RETURN VALUE: float - the filtered derivative
*******************************************************************************/
float cpm_filter_derivative_filter(DERFILT* pw, float input)
{
    // Have we been initialized yet?
    if (pw->init == false) {
        pw->y[0] = input;
        pw->y[1] = input;
        pw->y[2] = input;
        pw->init = true;
    }

    // Get the previous output
    float y_prev = pw->y[0];

    // Update the filter
    float y = y_prev + pw->kff * (input - y_prev);

    // Shift in the new values
    pw->y[2] = pw->y[1];
    pw->y[1] = pw->y[0];
    pw->y[0] = y;

    float d = (y - pw->y[2]) / (2 * pw->ts);

    pw->d = d;

    return d;
}
