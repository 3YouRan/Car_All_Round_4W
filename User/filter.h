//
// Created by ��� on 24-11-1.
//

#ifndef RC_ALL_ROUND_FILTER_H
#define RC_ALL_ROUND_FILTER_H
typedef struct {
    float alpha;           // ʱ�䳣��
    float previous_output_1; // ��һʱ�̵����


} LowPassFilter;

// �������˲�����״̬�ṹ��
typedef struct {
    float state;       // ��ǰ״̬
    float err_Cov;  // ���Э���� P_k
    float processNoiseCov; // ��������Э���� Q
    float measurementNoiseCov; // ��������Э���� R
    float kalmanGain;  // ����������
} KalmanFilter;


void initializeFilter(LowPassFilter* filter, float alpha);
float filterValue(LowPassFilter* filter, float input);
void Kalman_Init(KalmanFilter* kf, float initState, float init_err_Covariance, float processNoiseCov, float measurementNoiseCov);
float Kalman_Filter_Update(KalmanFilter *kf, float new_measurement);
#endif //RC_ALL_ROUND_FILTER_H
