#include "stm32f4xx.h"                  // Device header
#include "stdint.h"
#include "clock_config.h"

void systemClockConfig(void){
	/*
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL HSE
	*            HSE Frequency(Hz)              = 8000000
  *            SYSCLK(Hz)                     = 16800000
  *            HCLK(Hz)                       = 8000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            PLL_M                          = 4
  *            PLL_N                          = 168
  *            PLL_P                          = 0
  *            PLL_Q                          = 7
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5 CYC
	*						 APB1 P.C                       = 42 MHZ
	*            APB2 P.C                       = 84 MHZ
*/
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS; 
	RCC->PLLCFGR = (4<<0) | (168<<6) | (0<<16) | (7<<25)| RCC_PLLCFGR_PLLSRC_HSE;
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));
	FLASH->ACR |= FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_PPRE2_DIV2;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
	SystemCoreClockUpdate();
}
