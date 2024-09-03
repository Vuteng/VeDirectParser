/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <uart_handler.h>
#include <parser.h>
#include <stdio.h>
#include "SEGGER_RTT.h"
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

/* USER CODE BEGIN PV */
uint8_t rx_buffer_1[BUFFER_SIZE];
uint8_t rx_buffer_2[BUFFER_SIZE];

ProtocolRxBuff protocol_rx_buff = {
    .p_rx_buff_user = rx_buffer_1,
    .p_rx_buff_reception = rx_buffer_2,
    .new_data_sz = 0
};

VEDIRECT_RX_State rx_state = VEDIRECT_RX_State_IDLE;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint8_t UART_Receive(void);
void process_frame(void);
void reset_frame_data(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern UART_HandleTypeDef huart3;

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{

  SEGGER_RTT_printf(0, "%c", ch);


  return ch;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);

  /* USER CODE BEGIN 1 */
	int counter = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

 
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART3_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  __HAL_UART_CLEAR_FLAG(&huart3, UART_FLAG_IDLE);
  HAL_StatusTypeDef status = HAL_UARTEx_ReceiveToIdle_DMA(&huart3, protocol_rx_buff.p_rx_buff_reception, BUFFER_SIZE);
 // __HAL_DMA_DISABLE_IT(huart3.hdmarx, DMA_IT_HT);
  SEGGER_RTT_ConfigUpBuffer  (0,  NULL  ,  NULL  , 0,  SEGGER_RTT_MODE_NO_BLOCK_SKIP  );
  SEGGER_RTT_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(vedirect_rx_get_state() == VEDIRECT_RX_State_DATA_READY){

		  //calculate checksum of the whole frame
		  calculate_checksum(protocol_rx_buff.p_rx_buff_user, protocol_rx_buff.new_data_sz);


		  HAL_StatusTypeDef check = HAL_UARTEx_ReceiveToIdle_DMA(&huart3, protocol_rx_buff.p_rx_buff_reception, BUFFER_SIZE);
		  if (check != HAL_OK) Error_Handler();
		  __HAL_UART_CLEAR_FLAG(&huart3, UART_FLAG_IDLE);
		  vedirect_rx_set_state(VEDIRECT_RX_State_RECEIVING);
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void process_frame(void)
{
	  if (frame_ready)
	  {
		// Process the received data
		for (uint16_t i = 0; i < frame_size; i++)
		{
			char received_char = uart_buffer[i];

			checksum_calculated = (checksum_calculated + (uint8_t)received_char);

			if (!is_checksum_received)
			{
				// Check for the "Checksum\t" field in the buffer
				if (strstr((char*)uart_buffer, "Checksum\t") != NULL)
				{
					is_checksum_received = 1;  // Found the checksum marker
				}
			}
			else
			{
				// The next character is the actual checksum
				checksum_received = (uint8_t)received_char;

				checksum_received = uart_buffer[frame_size];

				// Verify the checksum
				checksum_calculated = (checksum_calculated + (uint8_t)received_char) % 256;

				// Mark the frame as ready for processing
				frame_ready = 1;

				// Copy the local buffer to the global buffer for further processing
				memcpy(g_uart_buffer, uart_buffer, uart_index);

				// Reset the local buffer and variables for the next frame
				uart_index = 0;
				memset(uart_buffer, 0, BUFFER_SIZE);
				is_checksum_received = 0;
			}
		}
	  }


    if (frame_ready)
    {
        // Check if the calculated checksum matches the received checksum
        if ((checksum_calculated % 256) == checksum_received)
        {
        	//parse_frame(g_uart_buffer);

            HAL_UART_Transmit(&huart2, g_uart_buffer, uart_index, 1000);
        }
        else
        {
            // Invalid checksum
            HAL_UART_Transmit(&huart2, (uint8_t *)"Checksum Error\n", 15, 1000);
        }

        // Clear buffers and reset flags
        reset_frame_data();
    }
}

void reset_frame_data(void)
{
    // Clear the UART buffer
    memset(g_uart_buffer, 0, BUFFER_SIZE);

    // Reset flags
    frame_ready = 0;
    checksum_calculated = 0;
    uart_index = 0;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
