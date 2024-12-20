//
// Created by 陈瑜 on 24-9-18.
//
#include "all.h"
#include "set_target.h"
LowPassFilter filter_x;
LowPassFilter filter_y;
LowPassFilter filter_angle;
void my_Init() {


    RetargetInit(&huart3);//初始化串口
    HAL_UART_Receive_IT(&huart3, (uint8_t *)RxBuffer, 1);//开启串口接收中断
    //FDCAN初始化
    FDCAN_Init(&hfdcan1);
    FDCAN_Filter_Config_Simple(&hfdcan1, 0x000, 0x7FF, 0x00000000, 0x00000000);

    //set_runpoint_target(20,0,0);
    set_runpoint_target(0,0,0);
    set_runpoint_target(0,0,0);
    // HAL_Delay(200);

    PID_Init(&pid_speed,&pid_speed_3,&pid_position,&PID_POINT,&PID_Angle_POS,&PID_Angle_SPD,&PID_POINT_x,&PID_POINT_y);//PID参数初始化


    HAL_TIM_Base_Start_IT(&htim3);//定时器3初始化

    Set_Target_UartInit();

    initializeFilter(&filter_x, 0.085);
    initializeFilter(&filter_y, 0.085);
    initializeFilter(&filter_angle, 0.085);

}