/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    usart.c
 * @brief   This file provides code for the configuration
 *          of the USART instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
uint8_t uart_rx_buffer[USART_RX_MAX_LEN];
uint8_t uart_tx_buffer[USART_TX_MAX_LEN];

uint8_t rx_tmp = 0;
uint8_t tx_tmp = 0;

uint8_t rx_time_cnt = 0; // 数据断帧计数值
uint8_t rx_ok_flag = 0;  // 接受完成一帧的标志

uint16_t uart_rx_cnt = 0;
uint16_t uart_tx_cnt = 0;

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */
}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */
}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if (uartHandle->Instance == USART1)
  {
    /* USER CODE BEGIN USART1_MspInit 0 */

    /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    /* USER CODE BEGIN USART1_MspInit 1 */

    /* USER CODE END USART1_MspInit 1 */
  }
  else if (uartHandle->Instance == USART2)
  {
    /* USER CODE BEGIN USART2_MspInit 0 */

    /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 DMA Init */
    /* USART2_RX Init */
    hdma_usart2_rx.Instance = DMA1_Channel6;
    hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_rx.Init.Mode = DMA_NORMAL;
    hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle, hdmarx, hdma_usart2_rx);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    /* USER CODE BEGIN USART2_MspInit 1 */

    /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle)
{

  if (uartHandle->Instance == USART1)
  {
    /* USER CODE BEGIN USART1_MspDeInit 0 */

    /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
    /* USER CODE BEGIN USART1_MspDeInit 1 */

    /* USER CODE END USART1_MspDeInit 1 */
  }
  else if (uartHandle->Instance == USART2)
  {
    /* USER CODE BEGIN USART2_MspDeInit 0 */

    /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);

    /* USART2 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
    /* USER CODE BEGIN USART2_MspDeInit 1 */

    /* USER CODE END USART2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
// wpr
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    uart_rx_buffer[uart_rx_cnt] = rx_tmp;
    uart_rx_cnt++;
    uart_rx_cnt %= USART_RX_MAX_LEN;
    rx_time_cnt = USART_RX_TIMESPAN;
    HAL_UART_Receive_IT(huart, &rx_tmp, 1);
  }
}

/**
 *  @brief 串口断帧任务函数，定时调用（1ms）
 */
void Uart_task(void)
{
  if (rx_time_cnt > 1)
  {
    rx_time_cnt--;
  }
  if (rx_time_cnt == 1)
  {
    rx_time_cnt = 0;
    uart_rx_buffer[uart_rx_cnt] = '\0';
    uart_rx_cnt++;
    uart_rx_cnt %= USART_RX_MAX_LEN;
    rx_ok_flag = 1;
  }
}
/**
 *  @brief 串口数据处理任务函数，定时调用（1ms）
 */
// GPT生成能够分割字符串的函数
void splitString(char *str)
{

  if (strstr(str, "$GNRMC") != NULL) // 检测GNRMC并从此重新开始字符串
  {
    float value1, value2;
    int date, time;
    sscanf(str, "$GNRMC,%*[^,],%*[^,],%f,%*[^,],%f", &value1, &value2);
    sscanf(str, "$GNRMC,%d,%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,]", &time);
    sscanf(str, "$GNRMC,%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%d", &date);
    printf("纬度: %f\n", value1);
    printf("经度: %f\n", value2);
    printf("%d年%d月%d日\n", date % 100, date / 100 - (date / 10000) * 100, date / 10000);
    printf("时间: %d时%d分%d秒\n", (time / 10000 + 8) % 24, time / 100 - (time / 10000) * 100, time % 100);
  }
}

void Usrt_Process(void)
{

  // //////////////////

  if (rx_ok_flag == 1)
  {
    char *token = strtok((char *)uart_rx_buffer, "\n");
    while (token != NULL)
    {
      splitString(token);
      token = strtok(NULL, "\n");
    }
    // printf((const char *)uart_rx_buffer);
    rx_ok_flag = 0;
    uart_rx_cnt = 0;
  }
}

int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}
//////////////////////
// void  splitString(char *str)
//  if (strstr(str, "$GNRMC") != NULL) // 检测GNRMC并从此重新开始字符串
//  {                                  // 检测是否包含 RMC 字符串
//    char *start = strchr(str, ',');  // 跳过第一个逗号
//    char *end = strchr(start, ',');  // 找到下一个逗号的位置
//    char floatStr[20];
//    strncpy(floatStr, start, end - start); // 复制浮点数的字符串部分
//    float value1 = atof(floatStr);         // 将字符串转换为浮点数

//   printf("浮点数1: %f\n", value1);

//   // 提取第二个浮点数
//   start = end + 1;                       // 移动到下一个逗号后面的位置
//   end = strchr(start, ',');              // 找到下一个逗号的位置
//   strncpy(floatStr, start, end - start); // 复制浮点数的字符串部分
//   float value2 = atof(floatStr);         // 将字符串转换为浮点数

//   printf("浮点数2: %f\n", value2);

//////////////////////
// char *end = strchr(start + 1, '*'); // 搜索星号的位置
// if (start != NULL && end != NULL)
// {
//   int length = end - (start + 1);     // 计算子字符串长度
//   char result[length + 1];            // 定义子字符串数组
//   strncpy(result, start + 1, length); // 复制子字符串到数组中
//   result[length] = '\0';              // 添加字符串结束符

//   // 逐个字符替换逗号为空格
//   for (int i = 0; i < length; i++)
//   {
//     if (result[i] == ',')
//     {
//       result[i] = ' ';
//     }
//   }
//   printf("%s\n", result);
// }
// if (strstr(str, "$GNRMC") != NULL) // 检测GNRMC并从此重新开始字符串
// {                                  // 检测是否包含 RMC 字符串
//   char *start = strchr(str, ',');  // 跳过第一个逗号
//   char *end = strchr(start, ',');  // 找到下一个逗号的位置
//   char floatStr[20];
//   for (int i = 0; i < 10; i++)
//   {
//     strncpy(floatStr, start, end - start); // 复制浮点数的字符串部分
//     float value1 = atof(floatStr);         // 将字符串转换为浮点数
//     if (value1 != 0.0)
//       printf(" %f\n", value1);
//     start = end + 1;
//     end = strchr(start, ',');
//   }
// }
/* USER CODE END 1 */
