//
// Created by 陈瑜 on 24-11-30.
//


#include "all.h"


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

