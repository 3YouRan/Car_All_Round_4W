//
// Created by ��� on 24-11-1.
//

#ifndef RC_ALL_ROUND_FILTER_H
#define RC_ALL_ROUND_FILTER_H
typedef struct {
    float alpha;           // ʱ�䳣��
    float previous_output; // ��һʱ�̵����
} LowPassFilter;

void initializeFilter(LowPassFilter* filter, float alpha);
float filterValue(LowPassFilter* filter, float input);

#endif //RC_ALL_ROUND_FILTER_H
