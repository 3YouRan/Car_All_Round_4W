//
// Created by ��� on 24-9-18.
//
#include "all.h"
#include "set_target.h"
void my_Init() {


    RetargetInit(&huart3);//��ʼ������
    HAL_UART_Receive_IT(&huart3, (uint8_t *)RxBuffer, 1);//�������ڽ����ж�
    //FDCAN��ʼ��
    FDCAN_Init(&hfdcan1);
    FDCAN_Filter_Config_Simple(&hfdcan1, 0x000, 0x7FF, 0x00000000, 0x00000000);

    set_runpoint_target(0,0,0);

    PID_Init(&pid_speed,&pid_position,&PID_POINT,&PID_Angle_POS,&PID_Angle_SPD);//PID��ʼ��


    HAL_TIM_Base_Start_IT(&htim3);//��ʱ��3��ʼ��

    Set_Target_UartInit();
}