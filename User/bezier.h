//
// Created by ��� on 24-11-30.
//

#ifndef RC_ALL_ROUND_BEZIER_H
#define RC_ALL_ROUND_BEZIER_H
// �����ṹ
typedef struct {
    double x, y;
} Point;
Point lerp(Point p1, Point p2, double t);
// ʹ�� De Casteljau �㷨���㱴���������ϵĵ�
Point bezier(Point controlPoints[], int n, double t);
#endif //RC_ALL_ROUND_BEZIER_H
