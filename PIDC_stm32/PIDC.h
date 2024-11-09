/*
 * File: PIDC.h
 *
 * Code generated for Simulink model :PIDC.
 *
 * Model version      : 1.0
 * Simulink Coder version    : 9.3 (R2020a) 18-Nov-2019
 * TLC version       : 9.3 (Jan 23 2020)
 * C/C++ source code generated on  : Fri Nov  8 11:00:29 2024
 *
 * Target selection: stm32.tlc
 * Embedded hardware selection: STM32CortexM
 * Code generation objectives: Unspecified
 * Validation result: Not run
 *
 *
 *
 * ******************************************************************************
 * * attention
 * *
 * * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * *
 * ******************************************************************************
 */

#ifndef RTW_HEADER_PIDC_h_
#define RTW_HEADER_PIDC_h_
#include <math.h>
#include "STM32_Config.h"
#include "PIDC_External_Functions.h"
#ifndef PIDC_COMMON_INCLUDES_
# define PIDC_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* PIDC_COMMON_INCLUDES_ */

#include "PIDC_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T UD_DSTATE;                    /* '<S1>/UD' */
  real_T FilterDifferentiatorTF_states;/* '<S30>/Filter Differentiator TF' */
  real_T Integrator_DSTATE;            /* '<S37>/Integrator' */
  real_T FilterDifferentiatorTF_states_b;/* '<S80>/Filter Differentiator TF' */
  real_T Integrator_DSTATE_k;          /* '<S87>/Integrator' */
} DW_PIDC;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T P_TAR;                        /* '<Root>/P_TAR' */
  real_T PKP;                          /* '<Root>/P-KP' */
  real_T P_KI;                         /* '<Root>/P_KI' */
  real_T P_KD;                         /* '<Root>/P_KD' */
  real_T P_N;                          /* '<Root>/P_N' */
  real_T S_P;                          /* '<Root>/S_P' */
  real_T S_I;                          /* '<Root>/S_I ' */
  real_T S_D;                          /* '<Root>/S_D' */
  real_T S_N;                          /* '<Root>/S_N' */
  real_T P_FEED;                       /* '<Root>/P_FEED' */
  real_T S_FEED;                       /* '<Root>/S_FEED' */
  real_T FOR_PID;                      /* '<Root>/FOR_PID' */
} ExtU_PIDC;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Current;                      /* '<Root>/Current' */
} ExtY_PIDC;

/* Real-time Model Data Structure */
struct tag_RTM_PIDC {
  const char_T *errorStatus;
};

/* Block states (default storage) */
extern DW_PIDC PIDC_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_PIDC PIDC_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_PIDC PIDC_Y;

/* Model entry point functions */
extern void PIDC_initialize(void);
extern void PIDC_step(void);

/* Real-time Model object */
extern RT_MODEL_PIDC *const PIDC_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Data Type Duplicate' : Unused code path elimination
 * Block '<S30>/Passthrough for tuning' : Eliminate redundant data type conversion
 * Block '<S80>/Passthrough for tuning' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PIDC'
 * '<S1>'   : 'PIDC/Discrete Derivative'
 * '<S2>'   : 'PIDC/P_PID'
 * '<S3>'   : 'PIDC/S_PID'
 * '<S4>'   : 'PIDC/P_PID/Anti-windup'
 * '<S5>'   : 'PIDC/P_PID/D Gain'
 * '<S6>'   : 'PIDC/P_PID/Filter'
 * '<S7>'   : 'PIDC/P_PID/Filter ICs'
 * '<S8>'   : 'PIDC/P_PID/I Gain'
 * '<S9>'   : 'PIDC/P_PID/Ideal P Gain'
 * '<S10>'  : 'PIDC/P_PID/Ideal P Gain Fdbk'
 * '<S11>'  : 'PIDC/P_PID/Integrator'
 * '<S12>'  : 'PIDC/P_PID/Integrator ICs'
 * '<S13>'  : 'PIDC/P_PID/N Copy'
 * '<S14>'  : 'PIDC/P_PID/N Gain'
 * '<S15>'  : 'PIDC/P_PID/P Copy'
 * '<S16>'  : 'PIDC/P_PID/Parallel P Gain'
 * '<S17>'  : 'PIDC/P_PID/Reset Signal'
 * '<S18>'  : 'PIDC/P_PID/Saturation'
 * '<S19>'  : 'PIDC/P_PID/Saturation Fdbk'
 * '<S20>'  : 'PIDC/P_PID/Sum'
 * '<S21>'  : 'PIDC/P_PID/Sum Fdbk'
 * '<S22>'  : 'PIDC/P_PID/Tracking Mode'
 * '<S23>'  : 'PIDC/P_PID/Tracking Mode Sum'
 * '<S24>'  : 'PIDC/P_PID/Tsamp - Integral'
 * '<S25>'  : 'PIDC/P_PID/Tsamp - Ngain'
 * '<S26>'  : 'PIDC/P_PID/postSat Signal'
 * '<S27>'  : 'PIDC/P_PID/preSat Signal'
 * '<S28>'  : 'PIDC/P_PID/Anti-windup/Disc. Clamping Parallel'
 * '<S29>'  : 'PIDC/P_PID/D Gain/External Parameters'
 * '<S30>'  : 'PIDC/P_PID/Filter/Disc. Trapezoidal Filter'
 * '<S31>'  : 'PIDC/P_PID/Filter/Disc. Trapezoidal Filter/Tsamp'
 * '<S32>'  : 'PIDC/P_PID/Filter/Disc. Trapezoidal Filter/Tsamp/Internal Ts'
 * '<S33>'  : 'PIDC/P_PID/Filter ICs/Internal IC - Filter'
 * '<S34>'  : 'PIDC/P_PID/I Gain/External Parameters'
 * '<S35>'  : 'PIDC/P_PID/Ideal P Gain/Passthrough'
 * '<S36>'  : 'PIDC/P_PID/Ideal P Gain Fdbk/Passthrough'
 * '<S37>'  : 'PIDC/P_PID/Integrator/Discrete'
 * '<S38>'  : 'PIDC/P_PID/Integrator ICs/Internal IC'
 * '<S39>'  : 'PIDC/P_PID/N Copy/External Parameters'
 * '<S40>'  : 'PIDC/P_PID/N Gain/External Parameters'
 * '<S41>'  : 'PIDC/P_PID/P Copy/Disabled'
 * '<S42>'  : 'PIDC/P_PID/Parallel P Gain/External Parameters'
 * '<S43>'  : 'PIDC/P_PID/Reset Signal/Disabled'
 * '<S44>'  : 'PIDC/P_PID/Saturation/Enabled'
 * '<S45>'  : 'PIDC/P_PID/Saturation Fdbk/Passthrough'
 * '<S46>'  : 'PIDC/P_PID/Sum/Sum_PID'
 * '<S47>'  : 'PIDC/P_PID/Sum Fdbk/Enabled'
 * '<S48>'  : 'PIDC/P_PID/Tracking Mode/Disabled'
 * '<S49>'  : 'PIDC/P_PID/Tracking Mode Sum/Passthrough'
 * '<S50>'  : 'PIDC/P_PID/Tsamp - Integral/Passthrough'
 * '<S51>'  : 'PIDC/P_PID/Tsamp - Ngain/Passthrough'
 * '<S52>'  : 'PIDC/P_PID/postSat Signal/Feedback_Path'
 * '<S53>'  : 'PIDC/P_PID/preSat Signal/Feedback_Path'
 * '<S54>'  : 'PIDC/S_PID/Anti-windup'
 * '<S55>'  : 'PIDC/S_PID/D Gain'
 * '<S56>'  : 'PIDC/S_PID/Filter'
 * '<S57>'  : 'PIDC/S_PID/Filter ICs'
 * '<S58>'  : 'PIDC/S_PID/I Gain'
 * '<S59>'  : 'PIDC/S_PID/Ideal P Gain'
 * '<S60>'  : 'PIDC/S_PID/Ideal P Gain Fdbk'
 * '<S61>'  : 'PIDC/S_PID/Integrator'
 * '<S62>'  : 'PIDC/S_PID/Integrator ICs'
 * '<S63>'  : 'PIDC/S_PID/N Copy'
 * '<S64>'  : 'PIDC/S_PID/N Gain'
 * '<S65>'  : 'PIDC/S_PID/P Copy'
 * '<S66>'  : 'PIDC/S_PID/Parallel P Gain'
 * '<S67>'  : 'PIDC/S_PID/Reset Signal'
 * '<S68>'  : 'PIDC/S_PID/Saturation'
 * '<S69>'  : 'PIDC/S_PID/Saturation Fdbk'
 * '<S70>'  : 'PIDC/S_PID/Sum'
 * '<S71>'  : 'PIDC/S_PID/Sum Fdbk'
 * '<S72>'  : 'PIDC/S_PID/Tracking Mode'
 * '<S73>'  : 'PIDC/S_PID/Tracking Mode Sum'
 * '<S74>'  : 'PIDC/S_PID/Tsamp - Integral'
 * '<S75>'  : 'PIDC/S_PID/Tsamp - Ngain'
 * '<S76>'  : 'PIDC/S_PID/postSat Signal'
 * '<S77>'  : 'PIDC/S_PID/preSat Signal'
 * '<S78>'  : 'PIDC/S_PID/Anti-windup/Disc. Clamping Parallel'
 * '<S79>'  : 'PIDC/S_PID/D Gain/External Parameters'
 * '<S80>'  : 'PIDC/S_PID/Filter/Disc. Trapezoidal Filter'
 * '<S81>'  : 'PIDC/S_PID/Filter/Disc. Trapezoidal Filter/Tsamp'
 * '<S82>'  : 'PIDC/S_PID/Filter/Disc. Trapezoidal Filter/Tsamp/Internal Ts'
 * '<S83>'  : 'PIDC/S_PID/Filter ICs/Internal IC - Filter'
 * '<S84>'  : 'PIDC/S_PID/I Gain/External Parameters'
 * '<S85>'  : 'PIDC/S_PID/Ideal P Gain/Passthrough'
 * '<S86>'  : 'PIDC/S_PID/Ideal P Gain Fdbk/Passthrough'
 * '<S87>'  : 'PIDC/S_PID/Integrator/Discrete'
 * '<S88>'  : 'PIDC/S_PID/Integrator ICs/Internal IC'
 * '<S89>'  : 'PIDC/S_PID/N Copy/External Parameters'
 * '<S90>'  : 'PIDC/S_PID/N Gain/External Parameters'
 * '<S91>'  : 'PIDC/S_PID/P Copy/Disabled'
 * '<S92>'  : 'PIDC/S_PID/Parallel P Gain/External Parameters'
 * '<S93>'  : 'PIDC/S_PID/Reset Signal/Disabled'
 * '<S94>'  : 'PIDC/S_PID/Saturation/Enabled'
 * '<S95>'  : 'PIDC/S_PID/Saturation Fdbk/Passthrough'
 * '<S96>'  : 'PIDC/S_PID/Sum/Sum_PID'
 * '<S97>'  : 'PIDC/S_PID/Sum Fdbk/Enabled'
 * '<S98>'  : 'PIDC/S_PID/Tracking Mode/Disabled'
 * '<S99>'  : 'PIDC/S_PID/Tracking Mode Sum/Passthrough'
 * '<S100>' : 'PIDC/S_PID/Tsamp - Integral/Passthrough'
 * '<S101>' : 'PIDC/S_PID/Tsamp - Ngain/Passthrough'
 * '<S102>' : 'PIDC/S_PID/postSat Signal/Feedback_Path'
 * '<S103>' : 'PIDC/S_PID/preSat Signal/Feedback_Path'
 */
#endif                                 /* RTW_HEADER_PIDC_h_ */

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] PIDC.h
 */
