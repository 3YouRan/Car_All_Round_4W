//
// Created by 陈瑜 on 2023-12-22.
//

#include "all.h"

PID pid_position;
PID pid_speed;
PID pid_current;
/**********************************
 * 功能：PID结构体参数初始化
 * 输入：无
 * 返回：无
 * *******************************/
void PID_Init(PID *pid_speed,PID *pid_position)//PID参数初始化
{
    pid_speed->err = 0;
    pid_speed->integral = 0;
    pid_speed->maxIntegral = 10000;
    pid_speed->maxOutput=16000;
    pid_speed->lastErr = 0;
    pid_speed->output = 0;
    pid_speed->kp = 76.72;
    pid_speed->ki = 0.0;
    pid_speed->kd = 10;
    pid_speed->deadZone = 0.05;

    pid_position->err = 0;
    pid_position->integral = 0;
    pid_position->maxIntegral = 600;
    pid_position->maxOutput = 600;
    pid_position->lastErr = 0;
    pid_position->output = 0;
    pid_position->kp = 50.763;
    pid_position->ki = 0;
    pid_position->kd = 5;
    pid_position->deadZone = 0.001;

}

/****************************************
 * 作用：增量式PID计算
 * 参数：PID参数结构体地址；目标值；反馈值
 * 返回值：无
 * ****************************************/
float Inc_PID_Realize(PID* pid, float target, float feedback)//一次PID计算
{
    pid->err = target - feedback;
   if(pid->err < pid->deadZone && pid->err > -pid->deadZone) pid->err = 0;//pid死区
    pid->integral += pid->err;

    if(pid->ki * pid->integral < -pid->maxIntegral) pid->integral = -pid->maxIntegral / pid->ki;//积分限幅
    else if(pid->ki * pid->integral > pid->maxIntegral) pid->integral = pid->maxIntegral / pid->ki;

    if(target == 0) pid->integral = 0; // 刹车时清空i


    pid->output += (pid->kp * pid->err) + (pid->ki * pid->integral)
            + (pid->kd * (pid->err - pid->lastErr));//增量式PID

    //输出限幅
    if(target >= 0)//正转时
    {
        if(pid->output < 0) pid->output = 0;
        else if(pid->output > pid->maxOutput) pid->output = pid->maxOutput;
    }
    else if(target < 0)//反转时
    {
        if(pid->output < -pid->maxOutput) pid->output = -pid->maxOutput;
        else if(pid->output > 0) pid->output = 0;
    }

    pid->lastErr = pid->err;
    if(target == 0) pid->output = 0; // 刹车时直接输出0
    return pid->output;
}
/****************************************
 * 作用：全量式PID计算
 * 参数：PID参数结构体地址；目标值；反馈值
 * 返回值：无
 * ****************************************/
float FW_PID_Realize(PID* pid, float target, float feedback)//一次PID计算
{

    if(pid->err < pid->deadZone && pid->err > -pid->deadZone) pid->err = 0;//pid死区
    pid->err = target - feedback;
    pid->integral += pid->err;

    if(pid->ki * pid->integral < -pid->maxIntegral) pid->integral = -pid->maxIntegral / pid->ki;//积分限幅
    else if(pid->ki * pid->integral > pid->maxIntegral) pid->integral = pid->maxIntegral / pid->ki;

    pid->output = (pid->kp * pid->err) + (pid->ki * pid->integral) + (pid->kd * (pid->err - pid->lastErr));//全量式PID

    //输出限幅
    if(pid->output > pid->maxOutput) pid->output = pid->maxOutput;
    if(pid->output < -pid->maxOutput) pid->output = -pid->maxOutput;

    pid->lastErr = pid->err;

    return pid->output;
}
/*
 * 功能：映射函数，将x从in_min~in_max映射到out_min~out_max
 * 输入：x：输入值；in_min：输入最小值；in_max：输入最大值；out_min：输出最小值；out_max：输出最大值
 * 返回：映射后的值
 */
double transfer(double x, double in_min, double in_max, double out_min, double out_max)//映射函数，将编码器的值（0~8191）转换为弧度制的角度值（-pi~pi）
{
    return (x-in_min)*(out_max-out_min)/(in_max-in_min)+out_min;
}

