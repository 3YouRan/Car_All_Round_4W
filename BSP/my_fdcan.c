//
// Created by 陈瑜 on 24-10-6.
//

#include "my_fdcan.h"
#include "all.h"
#include "fdcan.h"



void FDCAN_Init(FDCAN_HandleTypeDef *hfdcan){
    HAL_FDCAN_Start(hfdcan);
    __HAL_FDCAN_ENABLE_IT(hfdcan,FDCAN_IT_GROUP_RX_FIFO0);//使能接收FIFO0中断组
    __HAL_FDCAN_ENABLE_IT(hfdcan,FDCAN_IT_GROUP_RX_FIFO1);//使能接收FIFO1中断组
    HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE,0);
    HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO1_NEW_MESSAGE,0);
}
/*
 * @brief 简单地配置FDCAN滤波器，直接配置两个滤波器，一个标准帧滤波器，一个扩展帧滤波器
 *
 * @param hfdcan FDCAN句柄
 * @param STDID1 标准帧滤波器ID1
 * @param STDID2 标准帧滤波器ID2
 * @param EXTID1 扩展帧滤波器ID1
 * @param EXTID2 扩展帧滤波器ID2
 *
 * @return 无
 */
void FDCAN_Filter_Config_Simple(FDCAN_HandleTypeDef *hfdcan, uint16_t STDID1, uint16_t STDID2, uint32_t EXTID1, uint32_t EXTID2){
    FDCAN_FilterTypeDef Filter_Config;
    //扩展帧滤波器
    Filter_Config.IdType=FDCAN_EXTENDED_ID;
    Filter_Config.FilterIndex=1;
    Filter_Config.FilterType=FDCAN_FILTER_RANGE;//滤波器类型为范围滤波器,接收指定ID1~ID2范围内的数据
    Filter_Config.FilterConfig=FDCAN_FILTER_TO_RXFIFO1;//(Object_Param>>1)&0x03;//配置接收到的数据放入指定的FIFO中
    Filter_Config.FilterID1=EXTID1;//滤波器ID1
    Filter_Config.FilterID2=EXTID2;//滤波器ID2
    HAL_FDCAN_ConfigFilter(hfdcan, &Filter_Config);
    //标准帧滤波器
    Filter_Config.IdType = FDCAN_STANDARD_ID;
    Filter_Config.FilterIndex = 0;
    Filter_Config.FilterType = FDCAN_FILTER_RANGE;//滤波器类型为范围滤波器,接收指定ID1~ID2范围内的数据
    Filter_Config.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;//配置接收到的数据放入指定的FIFO中
    Filter_Config.FilterID1 = STDID1;//滤波器ID1
    Filter_Config.FilterID2 = STDID2;//滤波器ID2
    HAL_FDCAN_ConfigFilter(hfdcan, &Filter_Config);
}

/*
 * @brief 较详细地配置FDCAN滤波器，可指定滤波器编号、滤波器帧类型、接收FIFO、滤波器模式等参数
 *
 * @param hfdcan FDCAN句柄
 * @param ID1 标准帧滤波器ID1
 * @param ID2 标准帧滤波器ID2
 * @param Object_Param 配置参数 使用示例：FDCAN_STDID|FDCAN_FIFO_0|FDCAN_FILTER(0)|Filter_Mode(x)
 *
 * @return 无
 */
void FDCAN_Filter_Config(FDCAN_HandleTypeDef *hfdcan, uint32_t ID1, uint32_t ID2,uint16_t Object_Param){
    FDCAN_FilterTypeDef Filter_Config;
    if(Object_Param&0x01) {
        //扩展帧滤波器
        Filter_Config.IdType = FDCAN_EXTENDED_ID;
        Filter_Config.FilterIndex = (Object_Param>>3)&0x03;
        Filter_Config.FilterType = (Object_Param>>5)&0x03;//滤波器类型为范围滤波器,接收指定ID1~ID2范围内的数据
        Filter_Config.FilterConfig = (Object_Param>>1)&0x03;//配置接收到的数据放入指定的FIFO中
        Filter_Config.FilterID1 = ID1;//滤波器ID1
        Filter_Config.FilterID2 = ID2;//滤波器ID2
    }else {
        //标准帧滤波器
        Filter_Config.IdType = FDCAN_STANDARD_ID;
        Filter_Config.FilterIndex = Object_Param>>3;
        Filter_Config.FilterType =(Object_Param>>5)&0x03;//滤波器类型为范围滤波器,接收指定ID1~ID2范围内的数据
        Filter_Config.FilterConfig = (Object_Param>>3)&0x03;//配置接收到的数据放入指定的FIFO中
        Filter_Config.FilterID1 = ID1;//滤波器ID1
        Filter_Config.FilterID2 = ID2;//滤波器ID2
    }
    HAL_FDCAN_ConfigFilter(hfdcan, &Filter_Config);
}

/*
 * @brief FDCAN发送数据（关闭比特率切换）
 *
 * @param hfdcan FDCAN句柄
 * @param stdid 标准帧ID (如果为0则不使用标准帧)
 * @param extid 扩展帧ID (如果为0则不使用扩展帧)
 * @param data 发送数据的指针
 * @param len 发送数据长度
 */
void FDCAN_Transmit_Data_NotBRS(FDCAN_HandleTypeDef *hfdcan, uint32_t stdid, uint32_t extid, uint8_t *data, uint8_t len){
    FDCAN_TxHeaderTypeDef TxHeader1;

    if(extid==0){
        TxHeader1.Identifier=stdid;
        TxHeader1.IdType=FDCAN_STANDARD_ID;
    }else if(stdid==0){
        TxHeader1.Identifier=extid;
        TxHeader1.IdType=FDCAN_EXTENDED_ID;
    }
    TxHeader1.TxFrameType=FDCAN_DATA_FRAME;//为数据帧
    TxHeader1.DataLength=len;
    TxHeader1.ErrorStateIndicator=FDCAN_ESI_ACTIVE;//激活错误状态指示位
    TxHeader1.BitRateSwitch=FDCAN_BRS_OFF;//关闭比特率切换
    TxHeader1.FDFormat=FDCAN_CLASSIC_CAN;//CAN帧格式为经典CAN
    TxHeader1.TxEventFifoControl=FDCAN_NO_TX_EVENTS;//不使用事件FIFO
    TxHeader1.MessageMarker=0;//消息标记位（不知道有什么用）

    HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &TxHeader1, data);//将数据帧添加到发送FIFO队列中
}