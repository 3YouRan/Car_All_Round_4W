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

#include "FreeRTOS.h"

#include "task.h"

#include "uart_task.h"

#include "DJI_driver.h"

#include <stdbool.h>

#include "semphr.h"

#include "pid_task.h"

#include "tim.h"

#include "event_groups.h"

#include "math.h"

#include "locater.h"

#include "robo.h"

#include "debug.h"
#include "bezier.h"
#include "NRF24L01.h"
#include "filter.h"
//电机1位置和速度
extern float Target_Speed_1;
extern float Target_Speed_actual_1;
extern float Target_Position_1;
extern float Target_Position_last_1;
//电机2位置和速度
extern float Target_Speed_2;
extern float Target_Speed_actual_2;
extern float Target_Position_last_2;
extern float Target_Position_2;
//电机3位置和速度
extern float Target_Speed_3;
extern float Target_Speed_actual_3;
extern float Target_Position_last_3;
extern float Target_Position_3;
//电机4位置和速度
extern float Target_Speed_4;
extern float Target_Speed_actual_4;
extern float Target_Position_last_4;
extern float Target_Position_4;
extern float MIN_Spe_Increment;


extern PID pid_position;//位置PID
extern PID pid_speed;//速度PID


extern uint8_t RxBuffer[1];//接收缓冲区
extern uint16_t RxLine;//接收行数
extern uint8_t DataBuff[200];//数据缓存区

extern TaskHandle_t g_Uart_Tx_taskhandle;
extern TaskHandle_t g_Uart_Rx_taskhandle;
extern TaskHandle_t g_PID_taskhandle;
extern SemaphoreHandle_t g_SemaphoreHandle_For_Uart_RX;
extern SemaphoreHandle_t g_SemaphoreHandle_For_PID;
extern EventGroupHandle_t g_EventGroupHandle;

extern void my_Init();//初始化函数
extern float Kinematics_Solution(int16_t x, int16_t y);//运动学解算函数

extern DJI_motor gm2006_1;
extern DJI_motor gm2006_2;
extern DJI_motor gm2006_3;
extern DJI_motor gm2006_4;
#define pi 3.1415926
#define r 1234//待定
#define LOCATER_DATA_SIZE 14
#define RADAR_DATA_SIZE 14
#define DEBUG_RV_MXSIZE 255


extern float current_1;
extern float current_2;
extern float current_3;
extern float current_4;

//宏定义跑直线需要的三个pid
extern PID PID_POINT;
extern PID PID_POINT_x;
extern PID PID_POINT_y;
extern PID PID_Angle_POS;
extern PID PID_Angle_SPD;
extern PID pid_speed_3;
extern float dis;
extern float v;
extern locater_def locater;

extern Robot_Imu_Info_t Robot_Angle;


extern float angle_target ;
void Kinematic_solution(float v_x,float v_y,float w);

extern pointStruct Target_point;
extern pointStruct Target_point_actual;


extern uint8_t debugRvAll[LOCATER_DATA_SIZE];

extern RaDar_Info_t radar_data;
extern int cnt_radar;

extern LowPassFilter filter_x;
extern LowPassFilter filter_y;
extern LowPassFilter filter_angle;


extern float theta;

extern bool pid_spe_flag ;

extern bool radar_mender_flag ;

extern Control_Struct control_data;
extern uint8_t Speed_PS_Rece_Buf[32]; // 声明全局数组
extern Point result;
extern Point controlPoints[4];


#endif //RC_WORK1_ALL_H
