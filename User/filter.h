//
// Created by 陈瑜 on 24-11-1.
//

#ifndef RC_ALL_ROUND_FILTER_H
#define RC_ALL_ROUND_FILTER_H
typedef struct {
    float alpha;           // 时间常数
    float previous_output_1; // 上一时刻的输出


} LowPassFilter;

// 卡尔曼滤波器的状态结构体
typedef struct {
    float state;       // 当前状态
    float err_Cov;  // 误差协方差 P_k
    float processNoiseCov; // 过程噪声协方差 Q
    float measurementNoiseCov; // 测量噪声协方差 R
    float kalmanGain;  // 卡尔曼增益
} KalmanFilter;


void initializeFilter(LowPassFilter* filter, float alpha);
float filterValue(LowPassFilter* filter, float input);
void Kalman_Init(KalmanFilter* kf, float initState, float init_err_Covariance, float processNoiseCov, float measurementNoiseCov);
float Kalman_Filter_Update(KalmanFilter *kf, float new_measurement);
#endif //RC_ALL_ROUND_FILTER_H
