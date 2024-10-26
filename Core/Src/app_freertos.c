/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "all.h"
#include "data_fusion_task.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
TaskHandle_t g_Uart_Tx_taskhandle;
TaskHandle_t g_PID_taskhandle;

SemaphoreHandle_t g_SemaphoreHandle_For_PID;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for DataFusionTask */
osThreadId_t DataFusionTaskHandle;
const osThreadAttr_t DataFusionTask_attributes = {
  .name = "DataFusionTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for ROBOMOVTASK */
osThreadId_t ROBOMOVTASKHandle;
const osThreadAttr_t ROBOMOVTASK_attributes = {
  .name = "ROBOMOVTASK",
  .priority = (osPriority_t) osPriorityHigh,
  .stack_size = 128 * 4
};
/* Definitions for SETTARGETTASK */
osThreadId_t SETTARGETTASKHandle;
const osThreadAttr_t SETTARGETTASK_attributes = {
  .name = "SETTARGETTASK",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for PID_Task */
osThreadId_t PID_TaskHandle;
const osThreadAttr_t PID_Task_attributes = {
  .name = "PID_Task",
  .priority = (osPriority_t) osPriorityHigh3,
  .stack_size = 128 * 8
};
/* Definitions for Uart_Tx */
osThreadId_t Uart_TxHandle;
const osThreadAttr_t Uart_Tx_attributes = {
  .name = "Uart_Tx",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void data_fusion(void *argument);
void robo_mov(void *argument);
void set_target(void *argument);
void pid_task(void *argument);
void uart_tx_task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
    g_SemaphoreHandle_For_PID = xSemaphoreCreateBinary();
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  // defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of DataFusionTask */
  DataFusionTaskHandle = osThreadNew(data_fusion, NULL, &DataFusionTask_attributes);

  /* creation of ROBOMOVTASK */
  ROBOMOVTASKHandle = osThreadNew(robo_mov, NULL, &ROBOMOVTASK_attributes);

  /* creation of SETTARGETTASK */
  SETTARGETTASKHandle = osThreadNew(set_target, NULL, &SETTARGETTASK_attributes);

  /* creation of PID_Task */
  PID_TaskHandle = osThreadNew(pid_task, NULL, &PID_Task_attributes);

  /* creation of Uart_Tx */
  Uart_TxHandle = osThreadNew(uart_tx_task, NULL, &Uart_Tx_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  // xTaskCreate(pid_task, "PID_Task", 64, NULL, osPriorityNormal+1, &g_PID_taskhandle);
  // xTaskCreate(uart_tx_task, "Uart_Tx_Task", 64, NULL, osPriorityNormal+1, &g_Uart_Tx_taskhandle);

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */

  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_data_fusion */
/**
* @brief Function implementing the DataFusionTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_data_fusion */
void data_fusion(void *argument)
{
  /* USER CODE BEGIN data_fusion */
  portTickType CurrentTime1;

  /* Infinite loop */

  for(;;)
  {
    CurrentTime1=xTaskGetTickCount();

    //usart_printf("%.2f\n\r",locater.continuousAngle);

    data_fusion_radar();

    vTaskDelayUntil(&CurrentTime1,5);

  }
  /* USER CODE END data_fusion */
}

/* USER CODE BEGIN Header_robo_mov */
/**
* @brief Function implementing the ROBOMOVTASK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_robo_mov */
void robo_mov(void *argument)
{
  /* USER CODE BEGIN robo_mov */
  portTickType CurrentTime2;

  /* Infinite loop */
  for(;;)
  {
    CurrentTime2=xTaskGetTickCount();

    RunPoint_straight(Target_point);

    vTaskDelayUntil(&CurrentTime2,5);

  }
  /* USER CODE END robo_mov */
}

/* USER CODE BEGIN Header_set_target */
/**
* @brief Function implementing the SETTARGETTASK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_set_target */
void set_target(void *argument)
{
  /* USER CODE BEGIN set_target */
  /* Infinite loop */
  for(;;)
  {
      vTaskDelay(100); // 1s delay
  }
  /* USER CODE END set_target */
}

/* USER CODE BEGIN Header_pid_task */
/**
* @brief Function implementing the PID_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_pid_task */
void pid_task(void *argument)
{
  /* USER CODE BEGIN pid_task */
  portTickType CurrentTime_PID;

   /* Infinite loop */
   for(;;)
   {
     // xSemaphoreTake(g_SemaphoreHandle_For_PID, portMAX_DELAY);

     CurrentTime_PID=xTaskGetTickCount();

     //速度�?
     current_1=FW_PID_Realize(&pid_speed, Target_Speed_1, gm2006_1.rotor_speed / 36.0);
     current_2=FW_PID_Realize(&pid_speed, Target_Speed_2, gm2006_2.rotor_speed / 36.0);
     current_3=FW_PID_Realize(&pid_speed, Target_Speed_3, gm2006_3.rotor_speed / 36.0);
     current_4=FW_PID_Realize(&pid_speed, Target_Speed_4, gm2006_4.rotor_speed / 36.0);
     //角度�?

     //发�?�电机can控制信号
     GM2006_Current_Set(&hfdcan1, current_1, current_2, current_3, current_4, 0x200, GM_ID(1) | GM_ID(2)| GM_ID(3)|GM_ID(4));
     vTaskDelayUntil(&CurrentTime_PID,5);

   }
  /* USER CODE END pid_task */
}

/* USER CODE BEGIN Header_uart_tx_task */
// // /**
// // * @brief Function implementing the Uart_Tx thread.
// // * @param argument: Not used
// // * @retval None
// // */
/* USER CODE END Header_uart_tx_task */
void uart_tx_task(void *argument)
{
  /* USER CODE BEGIN uart_tx_task */
  portTickType CurrentTime3;

   /* Infinite loop */
   for(;;)
   {
     CurrentTime3=xTaskGetTickCount();

    //printf("%.1f,%.1f,%.2f,%.2f,%.2f,%.2f\n\r",radar_data.pos_x,radar_data.pos_y,radar_data.total_angle,locater.pos_x,locater.pos_y,locater.continuousAngle);
    printf("%.2f,%.2f,%d\n\r",dis,PID_POINT.kp,0);
     vTaskDelayUntil(&CurrentTime3,5);


     //printf("%.2f,%.2f,%.2f\n\r",locater.pos_x,locater.pos_y,locater.continuousAngle);
   }
  /* USER CODE END uart_tx_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

