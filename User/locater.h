#ifndef __LOCATER_H
#define __LOCATER_H

#include "main.h"
#include "stm32g4xx.h"
#include "pid.h"
#include "usart.h"

#define LOCATER_DATA_SIE 15

typedef struct
{
    float pos_x;
    float pos_y;

    float pos_x_last;
    float pos_y_last;
    float angle;

    float continuousAngle;
    float lastAngle;
    int circleNum;

    float angular_speed;

    float pos_x_base;
    float pos_y_base;

}locater_def;

typedef union
{
    uint8_t data_8[12];
    int32_t data_32[3];
    float data_f[3];
}loc_receive_union;


extern locater_def locater;
extern uint8_t locater_data[LOCATER_DATA_SIE]; //定位仪数据

void locater_data_rec(uint8_t *data, locater_def *loc);

#endif

