//
// Created by 陈瑜 on 24-11-30.
//

#include "bezier.h"
#include "all.h"
// 计算线性插值
Point lerp(Point p1, Point p2, double t) {
    Point result;
    result.x = (1 - t) * p1.x + t * p2.x;
    result.y = (1 - t) * p1.y + t * p2.y;
    return result;
}

// 使用 De Casteljau 算法计算贝塞尔曲线上的点
Point bezier(Point controlPoints[], int n, double t) {
    // 创建一个临时数组存储计算中的中间点
    Point temp[n];

    // 初始化 temp 数组为控制点
    for (int i = 0; i <= n; i++) {
        temp[i] = controlPoints[i];
    }

    // De Casteljau 算法：逐层计算线性插值
    for (int k = 1; k <= n; k++) {
        for (int i = 0; i <= n - k; i++) {
            temp[i] = lerp(temp[i], temp[i + 1], t);
        }
    }

    // 最终 temp[0] 保存了贝塞尔曲线的点
    return temp[0];
}


