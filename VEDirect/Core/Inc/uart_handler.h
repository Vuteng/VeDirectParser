#ifndef UART_HANDLER_H
#define UART_HANDLER_H

#define BUFFER_SIZE 512  // Large enough to accommodate more frames

#include <stdint.h>  // Add this line
#include <stm32g0xx_it.h>

extern volatile char uart_buffer[BUFFER_SIZE];  // Buffer to store received data
extern volatile uint8_t uart_index;            // Index for next character
extern volatile uint8_t frame_ready;            // Flag indicating frame completion
extern volatile uint8_t frame_number;          // Frame counter
extern volatile uint8_t checksum_calculated;
extern volatile uint8_t checksum_received;
extern volatile uint8_t checksum_index;
extern volatile char g_uart_buffer[BUFFER_SIZE];
extern volatile uint8_t is_checksum_received;

#endif // UART_HANDLER_H
