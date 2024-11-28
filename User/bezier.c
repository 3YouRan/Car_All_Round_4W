//
// Created by dyy on 24-11-28.
//

#include <stdio.h>
#include <string.h>
#include "bezier.h"


// �ǵݹ鷽ʽ���㱴���������ϵĵ�
void BezierCurve(Point *controlPoints, uint32_t numPoints, float t, Point *result) {
    Point tempPoints[10];
    memcpy(tempPoints, controlPoints, sizeof(Point) * numPoints);

    for (uint32_t k = 1; k < numPoints; k++) {
        for (uint32_t i = 0; i < numPoints - k; i++) {
            tempPoints[i].x = (1 - t) * tempPoints[i].x + t * tempPoints[i + 1].x;
            tempPoints[i].y = (1 - t) * tempPoints[i].y + t * tempPoints[i + 1].y;
        }
    }
    result->x = tempPoints[0].x;
    result->y = tempPoints[0].y;
}

