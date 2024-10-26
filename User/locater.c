
//created by dyy on 24-10-23

#include "locater.h"
locater_def locater = {.pos_x_base=0.0f,.pos_y_base=0.0f};  // 上电在坐标系中初始位置
uint8_t locater_data[LOCATER_DATA_SIE] = {0}; //定位仪数据

void locater_data_rec(uint8_t *data, locater_def *loc)
{
    loc_receive_union union_loc;
    static int cnt =0 ;
    if(data[0] == 'P' && data[1] == 'G')
    {
        cnt ++;
        loc->lastAngle = loc->angle;
        for(int i = 0; i < 12; i++)
        {
            union_loc.data_8[i] = data[i+2];//去掉数据包头
        }
        //
        loc->pos_x = 1.0054746843f*union_loc.data_f[0] + loc->pos_x_base;
        loc->pos_y = 1.0054746843f*union_loc.data_f[1] + loc->pos_y_base;
        loc->angle = union_loc.data_f[2];

        loc->angular_speed = 500.0f*(loc->angle - loc->lastAngle); // 500.0f为参数,配合pid

        //角度连续化
        if((loc->angle - loc->lastAngle) < -180.0f)//上溢
        {
            loc->circleNum++;
        }
        else if((loc->angle - loc->lastAngle) > 180.0f)//下溢
        {
            loc->circleNum--;
        }
        loc->continuousAngle = (float)loc->circleNum * 360.0f + loc->angle;

    }
}

