#include "stm32f4xx.h"                  // Device header
#include "stdint.h"
#include "usart_config.h"


static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t BaudRate){
	USARTx->BRR = compute_uart_div(PeriphClk,BaudRate);
}

static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate){
	return (uint16_t)((PeriphClk + (BaudRate/2U))/BaudRate);
}

void usart2Config(void){
/*
  * @brief  UART Configuration
  *         The UART is configured as follow :
	*            USART2_TX PD5 [11:10](23:22:21:20), USART2_RX PD6 [13:12](27:26:25:24)
  *            USART2_TX            = PD5
	*            USART2_RX            = PD6
  *            USART2_SYSCLK(mHz)   = 42 MHZ
	*            USART2_ClockPORT     = GPIOD - AHB1ENR
  *            USART2_BRR           = 115200
	*            USART2_AFRL          = AF7 (USART1..3) - 0111: AF7
	*            USART2_AFRL          = Pin x(x = 0..7)
	*            OVER8 = Oversampling = 0 
	*                 		  fck					 	42000000
										_____________   =  ____________ =  22.786
										(8x2xUSARTDIV)    (8X2X115.200)
	* 					 16 * (0.786) = 12.576  = 13
	*            (DIV_FRACTION) [0:3] we have 1 so add to the mantissa = 13
  *             22 + 1 = (DIV_Mantissa) [4:15]
*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	GPIOD->MODER &=~(0U<<10)|(0U<<12);
	GPIOD->MODER |= (1<<11) |(1<<13);
	GPIOD->AFR[0]&=~(0U<<23);  // AFR for PD5
	GPIOD->AFR[0]|= (1<<22) |(1<<21) |(1<<20);
	GPIOD->AFR[0]&=~(0U<<27);  // AFR for PD6
	GPIOD->AFR[0]|= (1<<24) |(1<<25) |(1<<26);
	uart_set_baudrate(USART2, 42000000, 115200);
	USART2->CR1  = 0x0U;
	USART2->CR1 |= (1<<3);
	USART2->CR1 |= (1<<2);
	USART2->CR1 |= (1<<13);
	USART2->CR1 &= ~(1U<<12);
}





