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

#endif //BEZIER_H
