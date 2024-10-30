#ifndef __ROBO_H
#define __ROBO_H
#include "main.h"

typedef struct
{
    float x;
    float y;
    float angle;
    float xy_dead_bone;
    float angle_dead_bone;
    uint8_t job_flag;
}pointStruct;


typedef struct
{
    float pos_x;
    float pos_y;

    float pos_x_first;
    float pos_y_first;


    float angle_last;
    float angle;

    int circleNum;
    float total_angle;
    float total_angle_first;


}RaDar_Info_t;


typedef struct
{
    float angle_last;
    float angle;
    int circleNum;
    float total_angle;

}Robot_Imu_Info_t;

void RunPoint_straight(pointStruct targetPoint);
















#endif
