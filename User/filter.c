//
// Created by ��� on 24-11-1.
//

#include "filter.h"

#include <stdio.h>


// ��ʼ���˲���
void initializeFilter(LowPassFilter* filter, float alpha) {
    filter->alpha = alpha;
    filter->previous_output = 0.0;
}

// һ�׵�ͨ�˲�����
float filterValue(LowPassFilter* filter, float input) {
    // �������
    float output = (1.0 - filter->alpha) * filter->previous_output + filter->alpha * input;

    // ������һ�ε����
    filter->previous_output = output;

    return output;
}


