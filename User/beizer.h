//
// Created by 陈瑜 on 24-11-30.
//

#ifndef RC_ALL_ROUND_BEIZER_H
#define RC_ALL_ROUND_BEIZER_H


typedef struct {
    double x, y;
} Point;

// 计算线性插值
Point lerp(Point p1, Point p2, double t);
// 递归计算贝塞尔曲线上的点
Point deCasteljau(Point points[], int n, double t);

#endif //RC_ALL_ROUND_BEIZER_H
