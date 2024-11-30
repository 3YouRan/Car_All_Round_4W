//
// Created by ��� on 24-11-30.
//

#ifndef RC_ALL_ROUND_BEIZER_H
#define RC_ALL_ROUND_BEIZER_H


typedef struct {
    double x, y;
} Point;

// �������Բ�ֵ
Point lerp(Point p1, Point p2, double t);
// �ݹ���㱴���������ϵĵ�
Point deCasteljau(Point points[], int n, double t);

#endif //RC_ALL_ROUND_BEIZER_H
