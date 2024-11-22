
//created by dyy on 24-10-23

#include "robo.h"
#include "PID.h"
#include "all.h"
#include "math.h"
#include <main.h>
#include "locater.h"


Robot_Imu_Info_t Robot_Angle;


float dis = 0.0f;   //当前与目标点的距离
float v = 0.0f;

bool pid_spe_flag = false;
void RunPoint_straight(pointStruct targetPoint)
{


    float xSpeed;
    float ySpeed;
    float v_x = 0.0f;
    float v_y = 0.0f;

    float omega = 0.0f; //速度、角速度
    float err_x = (targetPoint.x - radar_data.pos_x);  //x差值
    float err_y = (targetPoint.y - radar_data.pos_y);  //y差值

    //先计算向量长度
    dis = sqrt(err_x * err_x + err_y * err_y);
    //计算速度pid输
    if(pid_spe_flag ==true) {
//         omega = 3;
        omega = FW_PID_Realize_without_brake(&PID_Angle_POS,Target_point_actual.angle,radar_data.total_angle);//位置环
         v_x = FW_PID_Realize_without_brake(&PID_POINT_x,Target_point_actual.x, radar_data.pos_x);
         v_y = FW_PID_Realize_without_brake(&PID_POINT_y,Target_point_actual.y,radar_data.pos_y);
    }
// v_x = 0;
//    v_y = 0;

    // v = FW_PID_Realize_without_brake(&PID_POINT,0, -dis );

    //FW_PID_Realize(&PID_Angle_POS, targetPoint.angle,Robot_Angle.total_angle);//雷达数据

    // omega = FW_PID_Realize_without_brake(&PID_Angle_POS,targetPoint.angle,radar_data.total_angle);//位置环

    // omega = FW_PID_Realize(&PID_Angle_SPD,PID_Angle_POS.output,locater.angular_speed);//数据调整

    // printf("%.2f\n\r",omega);
    //线速度分解为x和y的分量
    xSpeed = v * cos(atan2f(err_y, err_x));
    ySpeed = v * sin(atan2f(err_y, err_x));


    Kinematic_solution(v_x,v_y,omega);
     // Kinematic_solution(xSpeed,ySpeed,omega);
}
