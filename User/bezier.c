//
// Created by dyy on 24-11-28.
//

#include <stdio.h>
#include <string.h>
#include "bezier.h"

#include "debug.h"
#include "stdlib.h"
int flag_bezier;
// 非递归方式计算贝塞尔曲线上的点
void BezierCurve(Point *controlPoints, uint32_t numPoints, float t, Point *result) {

    Point *tempPoints = (Point *)malloc(sizeof(Point) * numPoints);
    memcpy(tempPoints, controlPoints, sizeof(Point) * numPoints);

    for (uint32_t k = 1; k < numPoints; k++) {
        for (uint32_t i = 0; i < numPoints - k; i++) {
            tempPoints[i].x = (1 - t) * tempPoints[i].x + t * tempPoints[i + 1].x;
            tempPoints[i].y = (1 - t) * tempPoints[i].y + t * tempPoints[i + 1].y;
        }
    }
    result->x = tempPoints[0].x;
    result->y = tempPoints[0].y;
    free(tempPoints);
}
// 计算线性插值
Point lerp(Point p1, Point p2, double t) {
    Point result;
    result.x = (1 - t) * p1.x + t * p2.x;
    result.y = (1 - t) * p1.y + t * p2.y;
    return result;
}

// 递归计算贝塞尔曲线上的点
Point deCasteljau(Point points[], int n, double t) {
    if (n == 1) {
        return points[0]; // 只剩下一个点，返回
    }

    // 创建一个新的数组存储插值结果
    Point newPoints[n];
    for (int i = 0; i < n - 1; i++) {
        newPoints[i] = lerp(points[i], points[i + 1], t);
    }

    // 递归调用
    return deCasteljau(newPoints, n - 1, t);
}
