//
// Created by 陈瑜 on 24-9-16.
//

#ifndef RC_WORK1_ALL_H
#define RC_WORK1_ALL_H

#include "retarget.h"

#include "string.h"

#include "main.h"

#include "usart.h"

#include "math.h"

#include "fdcan.h"

#include "my_fdcan.h"

#include "PID.h"

#include "PID_Adjust.h"

extern float Target_Speed_1;//电机1目标速度
extern float Target_Speed_2;//电机2目标速度
extern float Target_Speed_actual_1;//电机1实际目标速度
extern float Target_Speed_actual_2;//电机2实际目标速度
extern float MIN_Spe_Increment;//最小速度增量
extern float Target_Position_1;//电机1目标位置
extern float Target_Position_last_1;//电机1上一次目标位置
extern float Target_Position_2;//电机2目标位置
extern float Target_Position_last_2;//电机2上一次目标位置
extern float Target_Current;
extern PID pid_position;//位置PID
extern PID pid_speed;//速度PID
extern PID pid_current;


extern uint8_t RxBuffer[1];//接收缓冲区
extern uint16_t RxLine;//接收行数
extern uint8_t DataBuff[200];//数据缓存区

extern int16_t x;//机械臂端子x坐标
extern int16_t y;//机械臂端子y坐标
extern float theta;//电机1的目标theta角度
extern float theta_last;
extern int16_t theta_2_last;
extern int16_t theta_2_last_last;

extern void my_Init();//初始化函数
extern float Kinematics_Solution(int16_t x, int16_t y);//运动学解算函数
#define pi 3.1416


#endif //RC_WORK1_ALL_H
