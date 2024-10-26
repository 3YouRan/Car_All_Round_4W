//
// Created by 陈瑜 on 24-10-23.
//

#include "all.h"
float current_1;
float current_2;
float current_3;
float current_4;
#define R_Car 0.142
#define R_Wheel 0.041
void Kinematic_solution(float v_x,float v_y,float w){
    Target_Speed_1=(w*R_Car+(v_x*sin(pi/2.0)+v_y*sin(0.0)))/(2*pi/60.0)/R_Wheel;
    Target_Speed_2=(w*R_Car+(v_x*sin(0.0)+v_y*sin(pi/2.0)))/(2*pi/60.0)/R_Wheel;
    Target_Speed_3=(w*R_Car+(v_x*sin(-pi/2.0)+v_y*sin(0.0)))/(2*pi/60.0)/R_Wheel;
    Target_Speed_4=(w*R_Car+(v_x*sin(0.0)+v_y*sin(-pi/2.0)))/(2*pi/60.0)/R_Wheel;
}

// void pid_task(void *arg){
//
//     while(1){
//         xSemaphoreTake(g_SemaphoreHandle_For_PID, portMAX_DELAY);
//         Kinematic_solution(0.1,0.1,0.0);
//
//
//         //速度环
//         current_1=FW_PID_Realize(&pid_speed, Target_Speed_actual_1, gm2006_1.rotor_speed / 36.0);
//         current_2=FW_PID_Realize(&pid_speed, Target_Speed_actual_2, gm2006_2.rotor_speed / 36.0);
//         current_3=FW_PID_Realize(&pid_speed, Target_Speed_actual_3, gm2006_3.rotor_speed / 36.0);
//         current_4=FW_PID_Realize(&pid_speed, Target_Speed_actual_4, gm2006_4.rotor_speed / 36.0);
//         //角度环
//
//         //发送电机can控制信号
//         GM2006_Current_Set(&hfdcan1, current_1, current_2, current_3, current_4, 0x200, GM_ID(1) | GM_ID(2)| GM_ID(3)|GM_ID(4));
//
//     }
// }
