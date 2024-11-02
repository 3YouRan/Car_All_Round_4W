////
//// Created by 陈瑜 on 24-9-18.
////

#include "all.h"
#include "debug.h"
#include "radar.h"
/*
 * @brief UART接收数据回调函数
 *
 * @param huart UART句柄
 * @return None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    if(huart==&huart3)
    {

        RxLine++;                      //姣忔帴鏀跺埌涓?涓暟鎹紝杩涘叆鍥炶皟鏁版嵁闀垮害鍔?1
        DataBuff[RxLine-1]=RxBuffer[0];  //鎶婃瘡娆℃帴鏀跺埌鐨勬暟鎹繚瀛樺埌缂撳瓨鏁扮粍
        if(RxBuffer[0]=='!')           //鎺ユ敹缁撴潫鏍囧織浣?
        {
            printf("RXLen=%d\r\n",RxLine);
            for(int i=0;i<RxLine;i++)
                printf("UART DataBuff[%d] = %c\r\n",i,DataBuff[i]);
//            xEventGroupSetBitsFromISR(g_xEventGroup_Uart_Rx,(1<<0),NULL);
//            xSemaphoreGiveFromISR(g_SemaphoreHandle_For_Uart_RX, NULL);//使用信号量唤醒UART_Rx任务

            USART_PID_Adjust(1);//鏁版嵁瑙ｆ瀽鍜屽弬鏁拌祴鍊煎嚱鏁?


            memset(DataBuff,0,sizeof(DataBuff));  //娓呯┖缂撳瓨鏁扮粍
            RxLine=0;  //娓呯┖鎺ユ敹闀垮害


        }
        RxBuffer[0]=0;
        HAL_UART_Receive_IT(&huart3, (uint8_t *)RxBuffer, 1);//姣忔帴鏀朵竴涓暟鎹紝灏辨墦寮?涓?娆′覆鍙ｄ腑鏂帴鏀?
        __HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);
    }
}


/**
  * @brief 非阻塞模式下的 Period elapsed 回调
  * @note 当 TIM4 中断发生时，在
  * HAL_TIM_IRQHandler（） 的它直接调用 HAL_IncTick（） 以递增
  * 用作应用程序时基的全局变量 “uwTick”。
  * @param htim ： TIM 句柄
  * @retval 无
  */
uint8_t time1=0;
float angle_now_1=0,angle_last_1=0,angle_total_1=0;//电机位置统计
float angle_now_2=0,angle_last_2=0,angle_total_2=0;
float angle_now_3=0,angle_last_3=0,angle_total_3=0;//电机位置统计
float angle_now_4=0,angle_last_4=0,angle_total_4=0;

bool Pos_flag=1;//是否开启位置控制

int time2=0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    /* USER CODE BEGIN Callback 0 */

    /* USER CODE END Callback 0 */
    if (htim->Instance == TIM4) {
        HAL_IncTick();
    }
    /* USER CODE BEGIN Callback 1 */
    if(htim->Instance==TIM3){
        time1++;
        time2++;
        if(time1==5){
            // printf("1321313\r\n");
            // xSemaphoreGiveFromISR(g_SemaphoreHandle_For_PID, NULL);//使用信号量唤醒PID任务

            time1=0;
//            速度爬坡
//            电机1速度爬坡
             if((Target_Speed_1 - Target_Speed_actual_1) > MIN_Spe_Increment){
                 Target_Speed_actual_1+=MIN_Spe_Increment;
             } else if((Target_Speed_1 - Target_Speed_actual_1) < -MIN_Spe_Increment){
                 Target_Speed_actual_1-=MIN_Spe_Increment;
             }
             //电机2速度爬坡
             if((Target_Speed_2 - Target_Speed_actual_2) > MIN_Spe_Increment){
                 Target_Speed_actual_2+=MIN_Spe_Increment;
             } else if((Target_Speed_2 - Target_Speed_actual_2) < -MIN_Spe_Increment){
                 Target_Speed_actual_2-=MIN_Spe_Increment;
             }
             //电机3速度爬坡
             if((Target_Speed_3 - Target_Speed_actual_3) > MIN_Spe_Increment){
                 Target_Speed_actual_3+=MIN_Spe_Increment;
             } else if((Target_Speed_3 - Target_Speed_actual_3) < -MIN_Spe_Increment){
                 Target_Speed_actual_3-=MIN_Spe_Increment;
             }
             //电机4速度爬坡
             if((Target_Speed_4 - Target_Speed_actual_4) > MIN_Spe_Increment){
                 Target_Speed_actual_4+=MIN_Spe_Increment;
             } else if((Target_Speed_4 - Target_Speed_actual_4) < -MIN_Spe_Increment){
                 Target_Speed_actual_4-=MIN_Spe_Increment;
             }
//            xEventGroupSetBitsFromISR(g_EventGroupHandle,(1<<0),NULL);
        }
        if(time2==16000){
            radar_mender_flag=true;
        }
        if(time2==10000){

            pid_spe_flag=true;
        }
    }
    /* USER CODE END Callback 1 */
}

/*
 * @brief FDCAN接收数据回调函数 标准帧进入接收FIFO0，扩展帧进入接收FIFO1
 *
 * @param hfdcan FDCAN句柄
 * @param RxFifo0ITs/RxFifo1ITs 接收FIFO0/FIFO1中断次数
 *
 * @return None
 */
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs){
    if(hfdcan->Instance == FDCAN1){
        FDCAN_RxHeaderTypeDef rx_header;
        uint8_t rx_data[8];
        HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rx_header, rx_data); //receive can data
        // printf("FDCAN_FIFO0_get:id=%x,data=%x\r\n",rx_header.Identifier,rx_data[0]);
        switch(rx_header.Identifier){
            case 0x201:{
                gm2006_1.rotor_angle    = ((rx_data[0] << 8) | rx_data[1]);
                gm2006_1.rotor_speed    = ((rx_data[2] << 8) | rx_data[3]);
                gm2006_1.torque_current = ((rx_data[4] << 8) | rx_data[5]);
                break;
            }
            case 0x202:{
                gm2006_2.rotor_angle    = ((rx_data[0] << 8) | rx_data[1]);
                gm2006_2.rotor_speed    = ((rx_data[2] << 8) | rx_data[3]);
                gm2006_2.torque_current = ((rx_data[4] << 8) | rx_data[5]);
                break;
            }
            case 0x203:{
                gm2006_3.rotor_angle    = ((rx_data[0] << 8) | rx_data[1]);
                gm2006_3.rotor_speed    = ((rx_data[2] << 8) | rx_data[3]);
                gm2006_3.torque_current = ((rx_data[4] << 8) | rx_data[5]);
                break;
            }
            case 0x204:{
                gm2006_4.rotor_angle    = ((rx_data[0] << 8) | rx_data[1]);
                gm2006_4.rotor_speed    = ((rx_data[2] << 8) | rx_data[3]);
                gm2006_4.torque_current = ((rx_data[4] << 8) | rx_data[5]);
                break;
            }
        }
    }
}
/*
 * @brief FDCAN接收数据回调函数 标准帧进入接收FIFO0，扩展帧进入接收FIFO1
 *
 * @param hfdcan FDCAN句柄
 * @param RxFifo0ITs/RxFifo1ITs 接收FIFO0/FIFO1中断次数
 *
 * @return None
 */
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs){
    if(hfdcan->Instance == FDCAN1){
        FDCAN_RxHeaderTypeDef rx_header;
        uint8_t rx_data[8];
        HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &rx_header, rx_data); //receive can data
        // printf("FDCAN_FIFO1_get:id=%x,data=%x\r\n",rx_header.Identifier,rx_data[0]);
        switch(rx_header.Identifier){

        }
    }
}
