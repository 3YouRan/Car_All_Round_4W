//
// Created by ��� on 24-9-18.
//
#include "all.h"

void my_Init() {


    RetargetInit(&huart3);//��ʼ������
    HAL_UART_Receive_IT(&huart3, (uint8_t *)RxBuffer, 1);//�������ڽ����ж�
    //FDCAN��ʼ��
    FDCAN_Init(&hfdcan1);
    FDCAN_Filter_Config_Simple(&hfdcan1, 0x000, 0x7FF, 0x00000000, 0x00000000);

    PID_Init(&pid_speed,&pid_position);//PID��ʼ��


    HAL_TIM_Base_Start_IT(&htim3);//��ʱ��3��ʼ��

    float angle_target = 0;

}