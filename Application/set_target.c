#include "set_target.h"
#include "all.h"
#include "bezier.h"
pointStruct Target_point;
pointStruct Target_point_actual;


Point controlPoints[4];

Point result;
float t;
void set_bezier_target(float angle)
{
    float t;
    for (t = 0.0f;t <= 1.0f;t += 0.01f)
    {
        BezierCurve(controlPoints, 4, t, &result);
    }
    Target_point.x = result.x;
    Target_point.y = result.y;
    Target_point.angle = angle;

}





void set_runpoint_target(float x,float y,float angle)
{

    Target_point.x = x;
    Target_point.y = y;
    Target_point.angle = angle;

}