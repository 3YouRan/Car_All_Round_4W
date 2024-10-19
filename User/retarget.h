#ifndef _RETARGET_H__
#define _RETARGET_H__
#include <sys/stat.h>
#include <stdio.h>
#include "main.h"
#include "stm32g4xx_hal.h"


void RetargetInit(UART_HandleTypeDef *huart);
int _isatty(int fd);
int _write(int fd, char *ptr, int len);
int _close(int fd);
int _lseek(int fd, int ptr, int dir);
int _read(int fd, char *ptr, int len);
int _fstat(int fd, struct stat *st);
#endif