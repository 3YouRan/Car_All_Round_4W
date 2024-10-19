//
// Created by 陈瑜 on 24-9-18.
//
#include "all.h"

void my_Init() {
    RetargetInit(&huart3);//初始化串口
    HAL_UART_Receive_IT(&huart3, (uint8_t *)RxBuffer, 1);//开启串口接收中断
    //FDCAN初始化
    FDCAN_Init(&hfdcan1);
    FDCAN_Filter_Config_Simple(&hfdcan1, 0x000, 0x7FF, 0x00000000, 0x00000000);

//    FDCAN_Filter_Config(&hfdcan1, 0x111,0x122,  FDCAN_STDID|FDCAN_FIFO_0| FDCAN_FILTER(4)| Filter_Mode(1));
//    FDCAN_Filter_Config(&hfdcan1, 0,0x1FFFFFFF,  FDCAN_EXTID|FDCAN_FIFO_0| FDCAN_FILTER(1));

//    //CAN1滤波器初始化
//    CAN_Filter_Mask_Config_32bit(&hcan1,CAN_FILTER(0) | CAN_FIFO_0 | CAN_STDID | CAN_DATA_TYPE,0x201,0);
//    //CAN2滤波器初始化
//    CAN_Filter_Mask_Config_32bit(&hcan2,CAN_FILTER(15) | CAN_FIFO_0 | CAN_STDID | CAN_DATA_TYPE,0x201,0);
//    //CAN初始化
//    CAN_Init(&hcan1);
//    CAN_Init(&hcan2);
//
//    PID_Init(&pid_speed,&pid_position);//PID初始化
//    HAL_TIM_Base_Start_IT(&htim3);//定时器3初始化

}