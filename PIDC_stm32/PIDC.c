/*
 * File: PIDC.c
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

#include "PIDC.h"
#include "PIDC_private.h"

/* Block states (default storage) */
DW_PIDC PIDC_DW;

/* External inputs (root inport signals with default storage) */
ExtU_PIDC PIDC_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_PIDC PIDC_Y;

/* Real-time model */
RT_MODEL_PIDC PIDC_M_;
RT_MODEL_PIDC *const PIDC_M = &PIDC_M_;

/* Model step function */
void PIDC_step(void)
{
  real_T denAccum;
  real_T denAccum_0;
  real_T rtb_SignPreIntegrator;
  real_T rtb_NProdOut;
  real_T rtb_IProdOut;
  real_T rtb_TSamp;
  real_T rtb_ZeroGain;
  boolean_T rtb_NotEqual;
  real_T rtb_ZeroGain_j;
  real_T Integrator;
  real_T tmp;
  rtb_TSamp = PIDC_U.FOR_PID * PIDC_U.P_TAR * 200.0;
  rtb_SignPreIntegrator = PIDC_U.P_TAR - PIDC_U.P_FEED;
  rtb_NProdOut = rtb_SignPreIntegrator * PIDC_U.PKP;
  PIDC_Y.Current = PIDC_U.P_N * 0.0025;
  rtb_IProdOut = 1.0 / (PIDC_Y.Current + 1.0);
  denAccum = rtb_SignPreIntegrator * PIDC_U.P_KD - (PIDC_Y.Current - 1.0) *
    rtb_IProdOut * PIDC_DW.FilterDifferentiatorTF_states;
  rtb_IProdOut = (denAccum + -PIDC_DW.FilterDifferentiatorTF_states) *
    rtb_IProdOut * PIDC_U.P_N;
  PIDC_Y.Current = (rtb_NProdOut + PIDC_DW.Integrator_DSTATE) + rtb_IProdOut;
  rtb_ZeroGain = 0.0 * PIDC_Y.Current;
  if (PIDC_Y.Current > 350.0) {
    PIDC_Y.Current -= 350.0;
  } else if (PIDC_Y.Current >= -350.0) {
    PIDC_Y.Current = 0.0;
  } else {
    PIDC_Y.Current -= -350.0;
  }

  rtb_NotEqual = (rtb_ZeroGain != PIDC_Y.Current);
  if (PIDC_Y.Current < 0.0) {
    PIDC_Y.Current = -1.0;
  } else if (PIDC_Y.Current > 0.0) {
    PIDC_Y.Current = 1.0;
  } else if (PIDC_Y.Current == 0.0) {
    PIDC_Y.Current = 0.0;
  } else {
    PIDC_Y.Current = (rtNaN);
  }

  rtb_SignPreIntegrator *= PIDC_U.P_KI;
  if (rtIsNaN(PIDC_Y.Current)) {
    rtb_ZeroGain_j = 0.0;
  } else {
    rtb_ZeroGain_j = fmod(PIDC_Y.Current, 256.0);
  }

  if (rtb_SignPreIntegrator < 0.0) {
    tmp = -1.0;
  } else if (rtb_SignPreIntegrator > 0.0) {
    tmp = 1.0;
  } else if (rtb_SignPreIntegrator == 0.0) {
    tmp = 0.0;
  } else {
    tmp = (rtNaN);
  }

  if (rtIsNaN(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  if (rtb_NotEqual && ((rtb_ZeroGain_j < 0.0 ? (int32_T)(int8_T)-(int8_T)
                        (uint8_T)-rtb_ZeroGain_j : (int32_T)(int8_T)(uint8_T)
                        rtb_ZeroGain_j) == (tmp < 0.0 ? (int32_T)(int8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp))) {
    rtb_ZeroGain = 0.0;
  } else {
    rtb_ZeroGain = rtb_SignPreIntegrator;
  }

  Integrator = 0.0025 * rtb_ZeroGain + PIDC_DW.Integrator_DSTATE;
  rtb_NProdOut = (rtb_NProdOut + Integrator) + rtb_IProdOut;
  if (rtb_NProdOut > 350.0) {
    rtb_NProdOut = 350.0;
  } else {
    if (rtb_NProdOut < -350.0) {
      rtb_NProdOut = -350.0;
    }
  }

  rtb_IProdOut = (rtb_TSamp - PIDC_DW.UD_DSTATE) + (rtb_NProdOut - PIDC_U.S_FEED);
  PIDC_Y.Current = rtb_IProdOut * PIDC_U.S_P;
  rtb_NProdOut = PIDC_U.S_N * 0.0025;
  rtb_SignPreIntegrator = 1.0 / (rtb_NProdOut + 1.0);
  denAccum_0 = rtb_IProdOut * PIDC_U.S_D - (rtb_NProdOut - 1.0) *
    rtb_SignPreIntegrator * PIDC_DW.FilterDifferentiatorTF_states_b;
  rtb_NProdOut = (denAccum_0 + -PIDC_DW.FilterDifferentiatorTF_states_b) *
    rtb_SignPreIntegrator * PIDC_U.S_N;
  rtb_SignPreIntegrator = (PIDC_Y.Current + PIDC_DW.Integrator_DSTATE_k) +
    rtb_NProdOut;
  rtb_ZeroGain_j = 0.0 * rtb_SignPreIntegrator;
  if (rtb_SignPreIntegrator > 20.0) {
    rtb_SignPreIntegrator -= 20.0;
  } else if (rtb_SignPreIntegrator >= -20.0) {
    rtb_SignPreIntegrator = 0.0;
  } else {
    rtb_SignPreIntegrator -= -20.0;
  }

  rtb_NotEqual = (rtb_ZeroGain_j != rtb_SignPreIntegrator);
  if (rtb_SignPreIntegrator < 0.0) {
    rtb_SignPreIntegrator = -1.0;
  } else if (rtb_SignPreIntegrator > 0.0) {
    rtb_SignPreIntegrator = 1.0;
  } else if (rtb_SignPreIntegrator == 0.0) {
    rtb_SignPreIntegrator = 0.0;
  } else {
    rtb_SignPreIntegrator = (rtNaN);
  }

  rtb_IProdOut *= PIDC_U.S_I;
  if (rtIsNaN(rtb_SignPreIntegrator)) {
    rtb_ZeroGain_j = 0.0;
  } else {
    rtb_ZeroGain_j = fmod(rtb_SignPreIntegrator, 256.0);
  }

  if (rtb_IProdOut < 0.0) {
    tmp = -1.0;
  } else if (rtb_IProdOut > 0.0) {
    tmp = 1.0;
  } else if (rtb_IProdOut == 0.0) {
    tmp = 0.0;
  } else {
    tmp = (rtNaN);
  }

  if (rtIsNaN(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  if (rtb_NotEqual && ((rtb_ZeroGain_j < 0.0 ? (int32_T)(int8_T)-(int8_T)
                        (uint8_T)-rtb_ZeroGain_j : (int32_T)(int8_T)(uint8_T)
                        rtb_ZeroGain_j) == (tmp < 0.0 ? (int32_T)(int8_T)
        -(int8_T)(uint8_T)-tmp : (int32_T)(int8_T)(uint8_T)tmp))) {
    rtb_IProdOut = 0.0;
  }

  rtb_SignPreIntegrator = 0.0025 * rtb_IProdOut + PIDC_DW.Integrator_DSTATE_k;
  PIDC_Y.Current = (PIDC_Y.Current + rtb_SignPreIntegrator) + rtb_NProdOut;
  if (PIDC_Y.Current > 20.0) {
    PIDC_Y.Current = 20.0;
  } else {
    if (PIDC_Y.Current < -20.0) {
      PIDC_Y.Current = -20.0;
    }
  }

  PIDC_DW.UD_DSTATE = rtb_TSamp;
  PIDC_DW.FilterDifferentiatorTF_states = denAccum;
  PIDC_DW.Integrator_DSTATE = 0.0025 * rtb_ZeroGain + Integrator;
  PIDC_DW.FilterDifferentiatorTF_states_b = denAccum_0;
  PIDC_DW.Integrator_DSTATE_k = 0.0025 * rtb_IProdOut + rtb_SignPreIntegrator;
}

/* Model initialize function */
void PIDC_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
}

/* File trailer for Real-Time Workshop generated code.
 *
 * [EOF] PIDC.c
 */
