#ifndef __DEBUG_H
#define __DEBUG_H

#include "usart.h"


void Set_Target_UartInit();
void Set_Target_UartIrqHandler(UART_HandleTypeDef *huart);
void Set_Target_UartIdleCallback(UART_HandleTypeDef *huart);


void Set_Target_UartInit_auto();
void Set_Target_UartIrqHandler_auto(UART_HandleTypeDef *huart);
void Set_Target_UartIdleCallback_auto(UART_HandleTypeDef *huart);

void Set_Target_UartIdleCallback_radar(UART_HandleTypeDef *huart);


#define START 0x31//电机启动标志位
#define STOP  0x30//电机截止标志位
#define MAOHAO 0x3A//宏定义冒号

#define PV_Target 0x70//输入为小写的p




void usart_printf(const char* format, ...);








#endif
