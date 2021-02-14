
/**
  ******************************************************************************

  CLOCK Setup For STM32F407VG
  Author:   Mouadh Dahech
  Updated:  1/16/2021

  ******************************************************************************
  Copyright (C) 

  ******************************************************************************
*/

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = HSI
  *            SYSCLK(Hz)                     = 16 MHZ
  *            HCLK(Hz)                       = 16 MHZ
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16
  *            PLL_M                          = *
  *            PLL_N                          = *
  *            PLL_P                          = *
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
//   * @param  None
//   * @retval None
//   */

#include "RCC_Config.h"

void SystemClock(void)
{

//1. ENABLE HSI and wait for the HSI to become Ready	
RCC->CR |= RCC_CR_HSION;
while(!(RCC->CR &= RCC_CR_HSIRDY));	

//2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
RCC->APB1ENR |= RCC_APB1ENR_PWREN;
PWR->CR |= PWR_CR_VOS;	
	
//3. Configure the FLASH PREFETCH and the LATENCY Related Settings	
FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN |FLASH_ACR_PRFTEN |FLASH_ACR_LATENCY_0WS;	
	
//4. Configure the PRESCALARS HCLK, PCLK1, PCLK2	
RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;
RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

//5. Select the Clock Source and wait for it to be set	
RCC->CFGR |= RCC_CFGR_SWS_HSI;
while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);	
}

	
