//
// Created by ��� on 24-11-1.
//

#include "filter.h"

#include <stdio.h>


// ��ʼ���˲���
void initializeFilter(LowPassFilter* filter, float alpha) {
    filter->alpha = alpha;
    filter->previous_output_1 = 0.0;
    filter->previous_output_2 = 0.0;
    filter->previous_output_3 = 0.0;
    filter->previous_output_4 = 0.0;
}

// һ�׵�ͨ�˲�����
float filterValue(LowPassFilter* filter, float input) {
    // �������
    float output = (1.0 - filter->alpha) * ((filter->previous_output_1+filter->previous_output_2+filter->previous_output_3+filter->previous_output_4)/4.0) + filter->alpha * input;

    // ������һ�ε����
    filter->previous_output_1 = output;
    filter->previous_output_2 = filter->previous_output_1;
    filter->previous_output_3 = filter->previous_output_2;
    filter->previous_output_4 = filter->previous_output_3;


    return output;
}


