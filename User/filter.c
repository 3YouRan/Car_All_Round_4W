//
// Created by 陈瑜 on 24-11-1.
//

#include "filter.h"

#include <stdio.h>


// 初始化滤波器
void initializeFilter(LowPassFilter* filter, float alpha) {
    filter->alpha = alpha;
    filter->previous_output_1 = 0.0;

}

// 一阶低通滤波函数
float filterValue(LowPassFilter* filter, float input) {
    // 计算输出
    float output = (1.0 - filter->alpha) * (filter->previous_output_1) + filter->alpha * input;

    // 更新上一次的输出
    filter->previous_output_1 = output;



    return output;
}


// 卡尔曼滤波器初始化
void Kalman_Init(KalmanFilter* kf, float initState, float init_err_Covariance, float processNoiseCov, float measurementNoiseCov) {
    kf->state = initState;
    kf->err_Cov = init_err_Covariance;
    kf->processNoiseCov = processNoiseCov;
    kf->measurementNoiseCov = measurementNoiseCov;
    kf->kalmanGain = 0.0f;
}
// 卡尔曼滤波器更新
float Kalman_Filter_Update(KalmanFilter *kf, float new_measurement){
    // step1 预测状态
    float predicted_state = kf->state;//此时预测矩阵A=1,无控制输入
    // step2 计算估计误差协方差
    float predicted_err_Cov = kf->err_Cov + kf->processNoiseCov;
    // step3 计算卡尔曼增益 此时测量矩阵H=1
    kf->kalmanGain = predicted_err_Cov / (predicted_err_Cov + kf->measurementNoiseCov);
    // step4 更新状态估计值
    kf->state = predicted_state + kf->kalmanGain * (new_measurement - predicted_state);
    // step5 更新误差协方差
    kf->err_Cov=(1-kf->kalmanGain)*predicted_err_Cov;
    // 返回最优状态估计值
    return kf->state;
}

