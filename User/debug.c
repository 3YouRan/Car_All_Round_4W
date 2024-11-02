
//created by dyy on 24-10-26

//串口二接收码盘
//串口三打印
//串口四给码盘发复位
//串口五接收视觉

#include "debug.h"
#include "usart.h"
#include "pid.h"
#include "string.h"
#include "all.h"
#include "semphr.h"
#define TX_BUF_SIZE 512
uint8_t send_buf[TX_BUF_SIZE];
#include "locater.h"
#include "radar.h"
#include"stdint.h"
#include <stdarg.h>
#include <stdio.h>
#include "stdlib.h"
#define TX_BUF_SIZE 512
uint8_t send_buf[TX_BUF_SIZE];

int cnt_radar;//
extern int cnt_mood;
extern SemaphoreHandle_t g_CAN_TASK_Semphr;

uint8_t debugRvAll[LOCATER_DATA_SIZE]={0};//存放串口2直接接收数据
//原来写的u_int8_t,怪不得串口你接收不到数据呢
uint8_t debugRvAll_radar[RADAR_DATA_SIZE]={0};//存放串口1直接接收数据

char debugRvData_radar_x[DEBUG_RV_MXSIZE]={0};//
char debugRvData_radar_y[DEBUG_RV_MXSIZE]={0};//
char debugRvData_radar_angle[DEBUG_RV_MXSIZE]={0};//

char *pEnd;

//c串口重定向

 void usart_printf(const char* format, ...)
 {
     va_list args;
     uint32_t length;
     va_start(args, format);

     length = vsnprintf((char*)send_buf, TX_BUF_SIZE, (const char*)format, args);

     va_end(args);

     HAL_UART_Transmit_DMA(&huart4, (uint8_t*)send_buf, length);
 }


//串口接收
void Set_Target_UartInit()
{
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);//使能串口2的空闲中断,用于串口接收
    HAL_UART_Receive_DMA(&huart2, (uint8_t*)&debugRvAll, DEBUG_RV_MXSIZE);//开启串口的DMA接收，debugRvAll存储串口接受的第一手数据

    __HAL_UART_ENABLE_IT(&huart5, UART_IT_IDLE);//使能串口1的空闲中断,用于串口接收
    HAL_UART_Receive_DMA(&huart5, (uint8_t*)&debugRvAll_radar, DEBUG_RV_MXSIZE);//开启串口的DMA接收，debugRvAll_radar存储串口接受的第一手数据

}

void Set_Target_UartIdleCallback(UART_HandleTypeDef *huart);
void Set_Target_UartIrqHandler(UART_HandleTypeDef *huart)
{
    if(huart->Instance == huart2.Instance)//判断是否是串口2
    {
        if(RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))//判断是否是空闲中断
        {
            __HAL_UART_CLEAR_IDLEFLAG(huart);//清楚空闲中断标志，防止会一直不断进入中断
            Set_Target_UartIdleCallback(huart);//调用中断处理函数
        }
    }

    if(huart->Instance == huart5.Instance)//判断是否是串口1
    {
        if(RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))//判断是否是空闲中断
        {
            __HAL_UART_CLEAR_IDLEFLAG(huart);//清楚空闲中断标志，防止会一直不断进入中断
            Set_Target_UartIdleCallback_radar(huart);//调用中断处理函数
        }
    }
}

uint8_t data_length  =0;
void Set_Target_UartIdleCallback(UART_HandleTypeDef *huart)//注意一个问题，调用的时候再写&huart5，否则在这个函数里就写&huart5打印会出问题
{
//    printf("%c,%c,%c,%c,%c,%c\n\r",debugRvAll[0],debugRvAll[1],debugRvAll[2],debugRvAll[3],debugRvAll[4],debugRvAll[5]);
    HAL_UART_DMAStop(huart);//停止本次DMA传输

    //计算接收到的数据长度，接收到的数据长度等于数组的最大存储长度减去DMA空闲的数据区长度
    uint8_t data_length  = DEBUG_RV_MXSIZE - __HAL_DMA_GET_COUNTER(huart->hdmarx);
    //printf("%d\n\r",data_length);

    //if(data_length==14){

        locater_data_rec((uint8_t *)&debugRvAll,&locater);   //解包
        // printf("%f\n\r",locater.continuousAngle);

   // printf("%.2f,%.2f,%.2f\n\r",locater.pos_x,locater.pos_y,locater.continuousAngle);

        data_length = 0;
        memset(debugRvAll,0,data_length); //清零接收缓冲区

    //}
    HAL_UART_Receive_DMA(huart, (uint8_t*)&debugRvAll, DEBUG_RV_MXSIZE);//循环中开启串口的DMA接收


}


uint8_t data_length_radar  =0;
bool radar_mender_flag = false;
void Set_Target_UartIdleCallback_radar(UART_HandleTypeDef *huart)//注意一个问题，调用的时候再写&huart5，否则在这个函数里就写&huart5打印会出问题
{
    HAL_UART_DMAStop(huart);//停止本次DMA传输

    RaDar_Data_Cal((uint8_t *)&debugRvAll_radar,&radar_data);
//    if(cnt_radar <= 300&&radar_mender_flag==true)
    if(cnt_radar <= 300)
    {
        radar_data.pos_x_first += radar_data.pos_x;


        radar_data.pos_y_first += radar_data.pos_y;
//        radar_data.total_angle_first  = radar_data.total_angle;
        cnt_radar++;
    }
    radar_data.pos_x_average = radar_data.pos_x_first/300.0f;
    radar_data.pos_y_average = radar_data.pos_y_first/300.0f;
    if(cnt_radar ==301)
    {
        radar_data.pos_x =  0.5*(radar_data.pos_x - radar_data.pos_x_average)*sqrtf(2.0);
        radar_data.pos_y =  0.5*(radar_data.pos_y - radar_data.pos_y_average)*sqrtf(2.0);
        radar_data.pos_x= filterValue(&filter_x,radar_data.pos_x);
        radar_data.pos_y= filterValue(&filter_y,radar_data.pos_y);
    }


    /*
    if(debugRvAll_radar[0] == 'A' && debugRvAll_radar[5] == 'B' && debugRvAll_radar[10])
    {
          memcpy(debugRvData_radar_x ,&debugRvAll_radar[2],4);//
          memcpy(debugRvData_radar_y ,&debugRvAll_radar[6],4);//
          memcpy(debugRvData_radar_angle ,&debugRvAll_radar[10],4);//
    }


    radar_data.pos_x= -atof(debugRvData_radar_x)/10;
    radar_data.pos_y= -strtof(debugRvData_radar_y,&pEnd)/10;
    radar_data.angle = (strtof(debugRvData_radar_angle,&pEnd))* 180.0f / pi / 1000.0f;


    if((radar_data.angle - radar_data.angle_last) < -180.0f)
    {
        radar_data.circleNum++;
    }
    else if((radar_data.angle - radar_data.angle_last) > 180.0f)
    {
        radar_data.circleNum--;
    }
    radar_data.total_angle = (float)radar_data.circleNum * 360.0f + radar_data.angle;

*/

    //计算接收到的数据长度，接收到的数据长度等于数组的最大存储长度减去DMA空闲的数据区长度
    uint8_t data_length_radar  = DEBUG_RV_MXSIZE - __HAL_DMA_GET_COUNTER(huart->hdmarx);
    //printf("%d\n\r",data_length);

    //if(data_length==14){

    //RaDar_Data_Cal((uint8_t *)&debugRvAll_radar,&radar_data);   //解包

    //printf("%f\n\r",locater.continuousAngle);
     //printf("%.1f,%.1f,%.2f\n\r",radar_data.pos_x,radar_data.pos_y,radar_data.total_angle);

    data_length_radar = 0;
    memset(debugRvAll_radar,0,data_length_radar); //清零接收缓冲区

    //}
    HAL_UART_Receive_DMA(huart, (uint8_t*)&debugRvAll_radar, DEBUG_RV_MXSIZE);//循环中开启串口的DMA接收


}

