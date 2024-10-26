
//created by dyy on 24-10-23

#include "data_fusion_task.h"
#include "all.h"
#include "math.h"

void data_fusion_radar(void)
{
    float err_angel= 0;
    int cnt1=0;
    Robot_Angle.angle_last = Robot_Angle.angle;
    if(fabs(locater.continuousAngle - RaDar_Loc.total_angle)<=3.0f)
    {
        if(fabs(RaDar_Loc.total_angle-Target_point.angle )<2 && fabs(locater.continuousAngle - Target_point.angle )<=3)
        {
            cnt1++;
            if(cnt1 == 100)
            {
                cnt1=0;
                err_angel = locater.angle - RaDar_Loc.angle;//雷达接收的帧率慢,locater接收的帧率快
                //但雷达数据准，这里用雷达的数据修正
            }
        }

        Robot_Angle.angle = locater.angle-err_angel;

        if((Robot_Angle.angle - Robot_Angle.angle_last) < -180.0f)
        {
            Robot_Angle.circleNum++;
        }
        else if((Robot_Angle.angle - Robot_Angle.angle_last) > 180.0f)
        {
            Robot_Angle.circleNum--;
        }
        Robot_Angle.total_angle = (float)Robot_Angle.circleNum * 360.0f +Robot_Angle.angle;

    }
}