//
// Created by 陈瑜 on 24-11-1.
//

#include "filter.h"

#include <stdio.h>


// 初始化滤波器
void initializeFilter(LowPassFilter* filter, float alpha) {
    filter->alpha = alpha;
    filter->previous_output_1 = 0.0;
    filter->previous_output_2 = 0.0;
    filter->previous_output_3 = 0.0;
    filter->previous_output_4 = 0.0;
}

// 一阶低通滤波函数
float filterValue(LowPassFilter* filter, float input) {
    // 计算输出
    float output = (1.0 - filter->alpha) * ((filter->previous_output_1+filter->previous_output_2+filter->previous_output_3+filter->previous_output_4)/4.0) + filter->alpha * input;

    // 更新上一次的输出
    filter->previous_output_1 = output;
    filter->previous_output_2 = filter->previous_output_1;
    filter->previous_output_3 = filter->previous_output_2;
    filter->previous_output_4 = filter->previous_output_3;


    return output;
}


