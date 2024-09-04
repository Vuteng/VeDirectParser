#include "string.h"
#include <uart_handler.h>
#include <stm32g0xx_it.h>
#include "stm32g0xx_ll_usart.h"  // Low Layer USART header for STM32G0 series
#include <stdio.h>

#define BUFFER_SIZE 512  // Large enough to accommodate more frames

extern UART_HandleTypeDef huart3;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart == &huart3)
    {
    	 // Swap the buffers so the main loop can access the received data
        volatile uint8_t *p_tmp = protocol_rx_buff.p_rx_buff_user;
        protocol_rx_buff.p_rx_buff_user = protocol_rx_buff.p_rx_buff_reception;
        protocol_rx_buff.p_rx_buff_reception = p_tmp;

        protocol_rx_buff.new_data_sz = Size;

        printf("%s\n", (char *)protocol_rx_buff.p_rx_buff_reception);
        
        vedirect_rx_upd_rx_timestamp();
        vedirect_rx_set_state(VEDIRECT_RX_State_DATA_READY);
    }
}

// DMA Transfer Complete callback
void
HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart3)
    {
        // This can be used to handle data if full buffer is filled
        // For example, reset DMA here if necessary

        // Reset the DMA for next reception
        __HAL_DMA_DISABLE(huart->hdmarx); // Disable the DMA stream
        //memset(&protocol_rx_buff.p_rx_buff_user, 0, BUFFER_SIZE);
        //memset(&protocol_rx_buff.p_rx_buff_reception, 0, BUFFER_SIZE);
        HAL_UARTEx_ReceiveToIdle_DMA(huart, protocol_rx_buff.p_rx_buff_reception, BUFFER_SIZE);
    }
}

void transmit_data_dma(uint8_t transmit_buffer,uint8_t size){
     if (HAL_UART_Transmit_DMA(&huart3, transmit_buffer, sizeof(size)) != HAL_OK)
    {
        // Transmission error handling
        Error_Handler();
    }
}

// Function to set the state
void vedirect_rx_set_state(VEDIRECT_RX_State new_state)
{
    rx_state = new_state;
}

// Function to get the current state
VEDIRECT_RX_State vedirect_rx_get_state(void)
{
    return rx_state;
}

// Function to update the timestamp (dummy function for example)
void vedirect_rx_upd_rx_timestamp(void)
{
    // Implement timestamp update logic if needed
    // For now, it's just a placeholder function
}
