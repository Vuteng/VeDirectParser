#ifndef UART_HANDLER_H
#define UART_HANDLER_H

#define BUFFER_SIZE 512  // Large enough to accommodate more frames

#include <stdint.h>  // Add this line
#include <stm32g0xx_it.h>

typedef enum {
    VEDIRECT_RX_State_IDLE,        // Idle state, no data is being processed
    VEDIRECT_RX_State_RECEIVING,   // Data is currently being received
    VEDIRECT_RX_State_DATA_READY,  // Data reception is complete and ready for processing
} VEDIRECT_RX_State;

typedef struct {
    volatile uint8_t *p_rx_buff_user;      // Pointer to the buffer for processing
    volatile uint8_t *p_rx_buff_reception; // Pointer to the buffer for receiving data via DMA
    volatile uint16_t new_data_sz;         // Size of the newly received data
} ProtocolRxBuff;

extern ProtocolRxBuff protocol_rx_buff;

extern VEDIRECT_RX_State rx_state;

void transmit_data_dma(uint8_t transmit_bufer,uint8_t size);

void vedirect_rx_set_state(VEDIRECT_RX_State new_state);
void vedirect_rx_upd_rx_timestamp(void);
VEDIRECT_RX_State vedirect_rx_get_state(void);

#endif // UART_HANDLER_H
