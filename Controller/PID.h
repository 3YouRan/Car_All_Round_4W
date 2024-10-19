//
// Created by 陈瑜 on 2023-12-22.
//


#ifndef _PID_H_
#define _PID_H_

#include "stm32g4xx.h"
//#include "encoder.h"
#include <stdio.h>
//#include "control.h"

//PID三个参数的值
#define KP_speed 5.25
#define KI_speed 0
#define KD_speed 25
#define KP_position 0
#define KI_position 0
#define KD_position 0

typedef struct _PID//PID参数结构体
{
    float kp,ki,kd;
    float err,lastErr;
    float integral,maxIntegral; //积分值
    float output,maxOutput;
    float deadZone; //死区
}PID;

void PID_Init(PID *pid_speed,PID *pid_position);//PID参数初始化
float Inc_PID_Realize(PID* pid, float target, float feedback);//一次PID计算
float FW_PID_Realize(PID* pid, float target, float feedback);
double transfer(double x, double in_min, double in_max, double out_min, double out_max);//映射函数，将编码器的值（0~8191）转换为弧度制的角度值（-pi~pi）

#endif
