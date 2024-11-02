////
//// Created by ��� on 24-9-18.
////

#include "all.h"
#include "debug.h"
#include "radar.h"
/*
 * @brief UART�������ݻص�����
 *
 * @param huart UART���
 * @return None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    if(huart==&huart3)
    {

        RxLine++;                      //每接收到�?个数据，进入回调数据长度�?1
        DataBuff[RxLine-1]=RxBuffer[0];  //把每次接收到的数据保存到缓存数组
        if(RxBuffer[0]=='!')           //接收结束标志�?
        {
            printf("RXLen=%d\r\n",RxLine);
            for(int i=0;i<RxLine;i++)
                printf("UART DataBuff[%d] = %c\r\n",i,DataBuff[i]);
//            xEventGroupSetBitsFromISR(g_xEventGroup_Uart_Rx,(1<<0),NULL);
//            xSemaphoreGiveFromISR(g_SemaphoreHandle_For_Uart_RX, NULL);//ʹ���ź�������UART_Rx����

            USART_PID_Adjust(1);//数据解析和参数赋值函�?


            memset(DataBuff,0,sizeof(DataBuff));  //清空缓存数组
            RxLine=0;  //清空接收长度


        }
        RxBuffer[0]=0;
        HAL_UART_Receive_IT(&huart3, (uint8_t *)RxBuffer, 1);//每接收一个数据，就打�?�?次串口中断接�?
        __HAL_UART_ENABLE_IT(&huart3,UART_IT_RXNE);
    }
}


/**
  * @brief ������ģʽ�µ� Period elapsed �ص�
  * @note �� TIM4 �жϷ���ʱ����
  * HAL_TIM_IRQHandler���� ����ֱ�ӵ��� HAL_IncTick���� �Ե���
  * ����Ӧ�ó���ʱ����ȫ�ֱ��� ��uwTick����
  * @param htim �� TIM ���
  * @retval ��
  */
uint8_t time1=0;
float angle_now_1=0,angle_last_1=0,angle_total_1=0;//���λ��ͳ��
float angle_now_2=0,angle_last_2=0,angle_total_2=0;
float angle_now_3=0,angle_last_3=0,angle_total_3=0;//���λ��ͳ��
float angle_now_4=0,angle_last_4=0,angle_total_4=0;

bool Pos_flag=1;//�Ƿ���λ�ÿ���

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
            // xSemaphoreGiveFromISR(g_SemaphoreHandle_For_PID, NULL);//ʹ���ź�������PID����

            time1=0;
//            �ٶ�����
//            ���1�ٶ�����
             if((Target_Speed_1 - Target_Speed_actual_1) > MIN_Spe_Increment){
                 Target_Speed_actual_1+=MIN_Spe_Increment;
             } else if((Target_Speed_1 - Target_Speed_actual_1) < -MIN_Spe_Increment){
                 Target_Speed_actual_1-=MIN_Spe_Increment;
             }
             //���2�ٶ�����
             if((Target_Speed_2 - Target_Speed_actual_2) > MIN_Spe_Increment){
                 Target_Speed_actual_2+=MIN_Spe_Increment;
             } else if((Target_Speed_2 - Target_Speed_actual_2) < -MIN_Spe_Increment){
                 Target_Speed_actual_2-=MIN_Spe_Increment;
             }
             //���3�ٶ�����
             if((Target_Speed_3 - Target_Speed_actual_3) > MIN_Spe_Increment){
                 Target_Speed_actual_3+=MIN_Spe_Increment;
             } else if((Target_Speed_3 - Target_Speed_actual_3) < -MIN_Spe_Increment){
                 Target_Speed_actual_3-=MIN_Spe_Increment;
             }
             //���4�ٶ�����
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
 * @brief FDCAN�������ݻص����� ��׼֡�������FIFO0����չ֡�������FIFO1
 *
 * @param hfdcan FDCAN���
 * @param RxFifo0ITs/RxFifo1ITs ����FIFO0/FIFO1�жϴ���
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
 * @brief FDCAN�������ݻص����� ��׼֡�������FIFO0����չ֡�������FIFO1
 *
 * @param hfdcan FDCAN���
 * @param RxFifo0ITs/RxFifo1ITs ����FIFO0/FIFO1�жϴ���
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
