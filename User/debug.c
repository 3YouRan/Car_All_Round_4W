#include "debug.h"
#include "usart.h"
#include "pid.h"
#include "string.h"
#include "all.h"
#include "semphr.h"
#define TX_BUF_SIZE 512
uint8_t send_buf[TX_BUF_SIZE];
#include "locater.h"

#include"stdint.h"
#include <stdarg.h>
#include <stdio.h>
#include "stdlib.h"
#define TX_BUF_SIZE 512
uint8_t send_buf[TX_BUF_SIZE];


extern int cnt_mood;
extern SemaphoreHandle_t g_CAN_TASK_Semphr;

uint8_t debugRvAll[LOCATER_DATA_SIZE]={0};//存放串口1直接接收数据
//原来写的u_int8_t,怪不得串口你接收不到数据呢

char *pEnd;
//
// void usart_printf(const char* format, ...)
// {
//     va_list args;
//     uint32_t length;
//     va_start(args, format);
//
//     length = vsnprintf((char*)send_buf, TX_BUF_SIZE, (const char*)format, args);
//
//     va_end(args);
//
//     HAL_UART_Transmit_DMA(&huart2, (uint8_t*)send_buf, length);
// }


//串口接收
void Set_Target_UartInit()
{
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);//使能串口一的空闲中断,用于串口接收
    HAL_UART_Receive_DMA(&huart2, (uint8_t*)&debugRvAll, DEBUG_RV_MXSIZE);//开启串口的DMA接收，debugRvAll存储串口接受的第一手数据
}

void Set_Target_UartIdleCallback(UART_HandleTypeDef *huart);
void Set_Target_UartIrqHandler(UART_HandleTypeDef *huart)
{
    if(huart->Instance == huart2.Instance)//判断是否是串口1
    {
        if(RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))//判断是否是空闲中断
        {


            __HAL_UART_CLEAR_IDLEFLAG(huart);//清楚空闲中断标志，防止会一直不断进入中断
            Set_Target_UartIdleCallback(huart);//调用中断处理函数
        }
    }
}

uint8_t data_length  =0;
void Set_Target_UartIdleCallback(UART_HandleTypeDef *huart)//注意一个问题，调用的时候再写&huart1，否则在这个函数里就写&huart1打印会出问题
{
//    printf("%c,%c,%c,%c,%c,%c\n\r",debugRvAll[0],debugRvAll[1],debugRvAll[2],debugRvAll[3],debugRvAll[4],debugRvAll[5]);
    HAL_UART_DMAStop(huart);//停止本次DMA传输

    //计算接收到的数据长度，接收到的数据长度等于数组的最大存储长度减去DMA空闲的数据区长度
    uint8_t data_length  = DEBUG_RV_MXSIZE - __HAL_DMA_GET_COUNTER(huart->hdmarx);
    printf("%d\n\r",data_length);
    locater_data_rec((uint8_t *)&debugRvAll,&locater);   //解包

    printf("%f\n\r",locater.continuousAngle);
    if(data_length==14){
        memset(debugRvAll,0,data_length); //清零接收缓冲区
        data_length = 0;
    }
    HAL_UART_Receive_DMA(huart, (uint8_t*)&debugRvAll, DEBUG_RV_MXSIZE);//循环中开启串口的DMA接收


}


