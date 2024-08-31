#include "string.h"
#include <uart_handler.h>
#include <stm32g0xx_it.h>
#include "stm32g0xx_ll_usart.h"  // Low Layer USART header for STM32G0 series

#define BUFFER_SIZE 512  // Large enough to accommodate more frames

volatile char uart_buffer[BUFFER_SIZE];  // Buffer to store received data
volatile uint8_t uart_index = 0;            // Index for next character
volatile uint8_t frame_ready = 0;            // Flag indicating frame completion
volatile uint8_t frame_number = 0;          // Frame counter
volatile uint8_t checksum_calculated = 0;
volatile uint8_t checksum_received = 0;      
volatile uint8_t checksum_index = 0;
volatile char g_uart_buffer[BUFFER_SIZE];
volatile uint8_t is_checksum_received = 0;

void UART_IRQ_HANDLER(void)
{
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


      // Optional: Check for errors like Overrun (ORE) and clear them if needed
    if (LL_USART_IsActiveFlag_ORE(USART3))
    {
        LL_USART_ClearFlag_ORE(USART3);  // Clear overrun error flag
    }

}
