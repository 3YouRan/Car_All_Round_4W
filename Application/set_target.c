#include "set_target.h"
#include "all.h"

pointStruct Target_point;

void set_runpoint_target(float x,float y,float angle)
{
    Target_point.x = x;
    Target_point.y = y;
    Target_point.angle = angle;

}
