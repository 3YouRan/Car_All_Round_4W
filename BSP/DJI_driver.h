//
// Created by 陈瑜 on 24-10-2.
//

#ifndef DS_2024_E_DJI_DRIVER_H
#define DS_2024_E_DJI_DRIVER_H
#include "main.h"
#define GM_ID(x) 1<<(x-1)
//DJI_motor结构体
typedef struct DJI_motor{
    uint16_t can_id;//电机ID
    int16_t  set_voltage;//设定的电压值
    int16_t  rotor_angle;//机械角度
    int16_t  rotor_speed;//转速
    int16_t  torque_current;//扭矩电流
    uint8_t  temp;//温度
}DJI_motor;

void GM6020_Voltage_Set(FDCAN_HandleTypeDef *hcan, int16_t volt,uint8_t motor_ID);
void GM3508_Current_Set(FDCAN_HandleTypeDef *hcan, int16_t Current,uint16_t id,uint8_t motor_ID);
void GM2006_Current_Set(FDCAN_HandleTypeDef *hcan, int16_t Current1,int16_t Current2,int16_t Current3,int16_t Current4,uint16_t id,uint8_t motor_ID);


#endif //DS_2024_E_DJI_DRIVER_H
