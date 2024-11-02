//
// Created by 陈瑜 on 24-11-1.
//

#ifndef RC_ALL_ROUND_FILTER_H
#define RC_ALL_ROUND_FILTER_H
typedef struct {
    float alpha;           // 时间常数
    float previous_output_1; // 上一时刻的输出
    float previous_output_2; // 上一时刻的输出
    float previous_output_3; // 上一时刻的输出
    float previous_output_4; // 上一时刻的输出

} LowPassFilter;

void initializeFilter(LowPassFilter* filter, float alpha);
float filterValue(LowPassFilter* filter, float input);

#endif //RC_ALL_ROUND_FILTER_H
