/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    usart.h
 * @brief   This file contains all the function prototypes for
 *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#define USART_RX_MAX_LEN 4096
#define USART_TX_MAX_LEN 4096
#define USART_RX_TIMESPAN 10 // ms

  extern uint8_t uart_rx_buffer[USART_RX_MAX_LEN];
  extern uint8_t uart_tx_buffer[USART_TX_MAX_LEN];

  extern uint8_t rx_tmp;
  extern uint8_t tx_tmp;

  extern uint16_t uart_rx_cnt;
  extern uint16_t uart_tx_cnt;

  /* USER CODE END Includes */

  extern UART_HandleTypeDef huart1;

  extern UART_HandleTypeDef huart2;

  /* USER CODE BEGIN Private defines */
  extern DMA_HandleTypeDef hdma_usart2_rx;
  /* USER CODE END Private defines */

  void MX_USART1_UART_Init(void);
  void MX_USART2_UART_Init(void);

  /* USER CODE BEGIN Prototypes */
  void Usrt_Process(void);
  void Uart_task(void);
  /* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
