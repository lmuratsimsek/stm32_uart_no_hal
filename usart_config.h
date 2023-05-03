#include "stdint.h"
#include "stm32f4xx.h"                  // Device header

void usart2Config(void);
static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate);
static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t BaudRate);

