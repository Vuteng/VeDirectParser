/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32g0xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "main.h"
#include "stm32g0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BUFFER_SIZE 512  // Large enough to accommodate more frames
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
volatile char uart_buffer[BUFFER_SIZE];  // Buffer to store received data
volatile uint16_t uart_index = 0;            // Index for next character
volatile uint8_t frame_ready = 0;            // Flag indicating frame completion
volatile uint8_t frame_number = 0;          // Frame counter
volatile uint8_t checksum_calculated = 0;
volatile uint8_t checksum_received = 0;      
volatile uint8_t checksum_index = 0;
volatile char g_uart_buffer[BUFFER_SIZE];
uint8_t is_checksum_received = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */
extern volatile uint8_t received_data; 
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32G0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32g0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles USART3, USART4 and LPUART1 interrupts / LPUART1 wake-up interrupt through EXTI line 28.
  */
void USART3_4_LPUART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_4_LPUART1_IRQn 0 */
	if (LL_USART_IsActiveFlag_RXNE(USART3))
  {
    char received_char = LL_USART_ReceiveData8(USART3);


    if (uart_index < BUFFER_SIZE - 1)
    {
      uart_buffer[uart_index++] = received_char;

      checksum_calculated = (checksum_calculated + (uint8_t)received_char);


      if (!is_checksum_received)
      {
        // Calculate checksum by adding the received character
        //checksum_calculated = (checksum_calculated + (uint8_t)received_char) & 256;

        // Check for the "Checksum\t" field in the buffer
        if (strstr(uart_buffer, "Checksum\t") != NULL)
        {
          // Indicate that the checksum string has been detected, so the next character is the checksum
          is_checksum_received = 1;

        }
      }
      else
      {
        // Once the checksum string has been detected, the next character is the actual checksum
        checksum_received = (uint8_t)received_char;

        // Calculate checksum by adding the received character
        checksum_calculated = (checksum_calculated + (uint8_t)received_char) %256;


        // Mark the frame as ready for processing in the main loop
        frame_ready = 1;

        //put local buffer into global buffer for main function to transmit
        memcpy(g_uart_buffer, uart_buffer, BUFFER_SIZE);

        //set local buffer to 0 for new frame
        memset(uart_buffer, 0, BUFFER_SIZE);

        //reset checksum received flag
        is_checksum_received = 0;
      }
    }
  }
  /* USER CODE END USART3_4_LPUART1_IRQn 0 */

  /* USER CODE BEGIN USART3_4_LPUART1_IRQn 1 */
    // Optional: Check for errors like Overrun (ORE) and clear them if needed
    if (LL_USART_IsActiveFlag_ORE(USART3))
    {
        LL_USART_ClearFlag_ORE(USART3);  // Clear overrun error flag
    }
    if (LL_USART_IsActiveFlag_ORE(USART4))
    {
        LL_USART_ClearFlag_ORE(USART4);  // Clear overrun error flag
    }
  /* USER CODE END USART3_4_LPUART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
