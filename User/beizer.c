//
// Created by ��� on 24-11-30.
//


#include "all.h"


// �������Բ�ֵ
Point lerp(Point p1, Point p2, double t) {
    Point result;
    result.x = (1 - t) * p1.x + t * p2.x;
    result.y = (1 - t) * p1.y + t * p2.y;
    return result;
}

// �ݹ���㱴���������ϵĵ�
Point deCasteljau(Point points[], int n, double t) {
    if (n == 1) {
        return points[0]; // ֻʣ��һ���㣬����
    }

    // ����һ���µ�����洢��ֵ���
    Point newPoints[n];
    for (int i = 0; i < n - 1; i++) {
        newPoints[i] = lerp(points[i], points[i + 1], t);
    }

    // �ݹ����
    return deCasteljau(newPoints, n - 1, t);
}

