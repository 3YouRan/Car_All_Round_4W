//
// Created by 陈瑜 on 24-11-30.
//

#ifndef RC_ALL_ROUND_BEZIER_H
#define RC_ALL_ROUND_BEZIER_H
// 定义点结构
typedef struct {
    double x, y;
} Point;
Point lerp(Point p1, Point p2, double t);
// 使用 De Casteljau 算法计算贝塞尔曲线上的点
Point bezier(Point controlPoints[], int n, double t);
#endif //RC_ALL_ROUND_BEZIER_H
