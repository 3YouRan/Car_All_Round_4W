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

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void data_fusion(void *argument);
void robo_mov(void *argument);
void set_target(void *argument);

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
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of DataFusionTask */
  DataFusionTaskHandle = osThreadNew(data_fusion, NULL, &DataFusionTask_attributes);

  /* creation of ROBOMOVTASK */
  ROBOMOVTASKHandle = osThreadNew(robo_mov, NULL, &ROBOMOVTASK_attributes);

  /* creation of SETTARGETTASK */
  SETTARGETTASKHandle = osThreadNew(set_target, NULL, &SETTARGETTASK_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  xTaskCreate(pid_task, "PID_Task", 64, NULL, osPriorityNormal+1, &g_PID_taskhandle);
  xTaskCreate(uart_tx_task, "Uart_Tx_Task", 64, NULL, osPriorityNormal, &g_Uart_Tx_taskhandle);

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

    data_fusion();

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

    RunPoint_straight();

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
    osDelay(1);
  }
  /* USER CODE END set_target */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

