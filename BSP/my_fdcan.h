//
// Created by 陈瑜 on 24-10-6.
//

#ifndef FD_CAN_LEARN_MY_FDCAN_H
#define FD_CAN_LEARN_MY_FDCAN_H
//
// Created by 陈瑜 on 24-10-6.
//

#include "my_fdcan.h"
#include "all.h"
#include "fdcan.h"

//滤波器编号
#define FDCAN_FILTER(x) ((x)<<3)
//接收队列
#define FDCAN_FIFO_0 (1<<1)
#define FDCAN_FIFO_1 (2<<1)
//标准帧或扩展帧
#define FDCAN_STDID (0<<0)
#define FDCAN_EXTID (1<<0)
//滤波器模式 0-范围过滤 1-列表过滤 2-掩码过滤 3-范围过滤 without EDI掩码
#define Filter_Mode(x) ((x)<<5)




void FDCAN_Init(FDCAN_HandleTypeDef *hfdcan);
void FDCAN_Transmit_Data_NotBRS(FDCAN_HandleTypeDef *hfdcan, uint32_t stdid, uint32_t extid, uint8_t *data, uint8_t len);
void FDCAN_Filter_Config_Simple(FDCAN_HandleTypeDef *hfdcan, uint16_t STDID1, uint16_t STDID2, uint32_t EXTID1, uint32_t EXTID2);
void FDCAN_Filter_Config(FDCAN_HandleTypeDef *hfdcan, uint32_t ID1, uint32_t ID2,uint16_t Object_Param);
#endif //FD_CAN_LEARN_MY_FDCAN_H
