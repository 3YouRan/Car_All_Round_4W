//
// Created by ��� on 24-11-1.
//

#include "filter.h"

#include <stdio.h>


// ��ʼ���˲���
void initializeFilter(LowPassFilter* filter, float alpha) {
    filter->alpha = alpha;
    filter->previous_output_1 = 0.0;

}

// һ�׵�ͨ�˲�����
float filterValue(LowPassFilter* filter, float input) {
    // �������
    float output = (1.0 - filter->alpha) * (filter->previous_output_1) + filter->alpha * input;

    // ������һ�ε����
    filter->previous_output_1 = output;



    return output;
}


// �������˲�����ʼ��
void Kalman_Init(KalmanFilter* kf, float initState, float init_err_Covariance, float processNoiseCov, float measurementNoiseCov) {
    kf->state = initState;
    kf->err_Cov = init_err_Covariance;
    kf->processNoiseCov = processNoiseCov;
    kf->measurementNoiseCov = measurementNoiseCov;
    kf->kalmanGain = 0.0f;
}
// �������˲�������
float Kalman_Filter_Update(KalmanFilter *kf, float new_measurement){
    // step1 Ԥ��״̬
    float predicted_state = kf->state;//��ʱԤ�����A=1,�޿�������
    // step2 ����������Э����
    float predicted_err_Cov = kf->err_Cov + kf->processNoiseCov;
    // step3 ���㿨�������� ��ʱ��������H=1
    kf->kalmanGain = predicted_err_Cov / (predicted_err_Cov + kf->measurementNoiseCov);
    // step4 ����״̬����ֵ
    kf->state = predicted_state + kf->kalmanGain * (new_measurement - predicted_state);
    // step5 �������Э����
    kf->err_Cov=(1-kf->kalmanGain)*predicted_err_Cov;
    // ��������״̬����ֵ
    return kf->state;
}

