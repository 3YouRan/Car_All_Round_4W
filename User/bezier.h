//
// Created by dyy on 24-11-28.
//

#ifndef BEZIER_H
#define BEZIER_H
typedef struct {
    float x;
    float y;
} Point;
void BezierCurve(Point *controlPoints, uint32_t numPoints, float t, Point *result);
Point lerp(Point p1, Point p2, double t);
Point deCasteljau(Point points[], int n, double t);


#endif //BEZIER_H
