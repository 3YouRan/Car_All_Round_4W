//
// Created by ��� on 24-11-30.
//

#include "bezier.h"
#include "all.h"
// �������Բ�ֵ
Point lerp(Point p1, Point p2, double t) {
    Point result;
    result.x = (1 - t) * p1.x + t * p2.x;
    result.y = (1 - t) * p1.y + t * p2.y;
    return result;
}

// ʹ�� De Casteljau �㷨���㱴���������ϵĵ�
Point bezier(Point controlPoints[], int n, double t) {
    // ����һ����ʱ����洢�����е��м��
    Point temp[n];

    // ��ʼ�� temp ����Ϊ���Ƶ�
    for (int i = 0; i <= n; i++) {
        temp[i] = controlPoints[i];
    }

    // De Casteljau �㷨�����������Բ�ֵ
    for (int k = 1; k <= n; k++) {
        for (int i = 0; i <= n - k; i++) {
            temp[i] = lerp(temp[i], temp[i + 1], t);
        }
    }

    // ���� temp[0] �����˱��������ߵĵ�
    return temp[0];
}


