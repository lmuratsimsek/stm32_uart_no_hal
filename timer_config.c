#include "stm32f4xx.h"                  // Device header
#include "stdint.h"
#include "timer_config.h"


void TIM2_Config (void) {
  /*
  * @brief
	*	1. Enable TIMER CLOCK
	*	2. Set the prescalar and the ARR (Auto Reload)
	*	3. Enable the TIMER2 and wait for the update flag to set.
	*/
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Timer ENABLED.
	// APB1 P.C                       = 42 mHz * 2 = 84 mHz. ** TIM2 connected APB1 PC.
	TIM2->PSC = 42-1; //Timer Clock = APB1 / PS = 42 / 2 = 21mHz. ??
	// Since it is 1 mhz. each count should take 1us. max count is ARR value. (Avoid overflow.)
	TIM2->ARR = 0xFFFF - 1 ;// Reset Value : 0xFFFF
	TIM2->CR1 |= (1<<0); // Enable Timer.
	while (!(TIM2->SR & (1<<0))); //SR -> Wait to set.
}
void Delay_us (volatile uint16_t us){
	TIM2->CNT = 0; // Reset Counter
	while (TIM2->CNT < us); // Wait for the reaching entered value
}

void Delay_ms (volatile uint16_t ms){
	for (uint16_t i=0; i<ms ; i++){
		Delay_us (1000); // Delay for 1ms.
	}
}

	
	
