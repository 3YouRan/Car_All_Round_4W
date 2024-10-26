
//created by dyy on 24-10-23

#include "robo.h"
#include "PID.h"
#include "all.h"
#include "math.h"
#include <main.h>
#include "locater.h"

RaDar_Info_t RaDar_Loc;

Robot_Imu_Info_t Robot_Angle;



void RunPoint_straight(pointStruct targetPoint)
{
    float xSpeed;
    float ySpeed;
    float dis = 0.0f;   //当前与目标点的距离
    float v = 0.0f, omega = 0.0f; //速度、角速度
    float err_x = (targetPoint.x - RaDar_Loc.pos_x);  //x差值
    float err_y = (targetPoint.y - RaDar_Loc.pos_y);  //y差值
    //先计算向量长度
    dis = sqrt(err_x * err_x + err_y * err_y);

    //计算速度pid输
    v = FW_PID_Realize(&PID_POINT,0, -dis );

    FW_PID_Realize(&PID_Angle_POS, targetPoint.angle,Robot_Angle.total_angle);

    omega = FW_PID_Realize(&PID_Angle_SPD,PID_Angle_POS.output,locater.angular_speed);

    //线速度分解为x和y的分量
    xSpeed = v * cos(atan2f(err_y, err_x));
    ySpeed = v * sin(atan2f(err_y, err_x));

    Kinematic_solution(xSpeed,ySpeed,omega);



}
