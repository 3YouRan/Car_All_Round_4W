
//created by dyy on 24-10-23

#include "radar.h"
#include "all.h"
#include "math.h"

RaDar_Info_t radar_data;
void RaDar_Data_Cal(uint8_t *data,RaDar_Info_t *loc_data)
{
    static uint8_t Fresh_Flag=0;
    static int cnt=0;
    static float base_x=0 , base_y=0, base_angle=0;
    if(data[0]=='A' )
    {

        loc_data->angle_last = loc_data->angle;
        //雷达坐标
        loc_data->pos_x = -(float)(data[1] | data[2] << 8 | data[3] << 16 | data[4] << 24) / 10.0f ;
        loc_data->pos_y = -(float)(data[5] | data[6] << 8 | data[7] << 16 | data[8] << 24) / 10.0f  ;
        loc_data->angle = (float)(data[9] | data[10] << 8 | data[11] << 16 | data[12] << 24) * 180.0f / pi / 1000.0f  ;//角度转为度


        if((loc_data->angle - loc_data->angle_last) < -180.0f)
        {
            loc_data->circleNum++;
        }
        else if((loc_data->angle - loc_data->angle_last) > 180.0f)
        {
            loc_data->circleNum--;
        }
        loc_data->total_angle = (float)loc_data->circleNum * 360.0f + loc_data->angle;

    }

}