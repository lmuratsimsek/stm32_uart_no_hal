#include "stm32f4xx.h"                  // Device header
#include "stdint.h"
#include "clock_config.h"
#include "timer_config.h"
#include "usart_config.h"


void uart2_write(int ch);


void uart2_write(int ch){
	while(!(USART2->SR & (1U<<7))); //TXE
	USART2->DR = (ch & 0XFF);
}


int main(void){
  systemClockConfig(); // System Clock Call
	usart2Config(); // USART Config Call
	TIM2_Config(); // TIMER Config Call
	while(1){
		uart2_write('M');
		Delay_ms(1000);
	}
}
