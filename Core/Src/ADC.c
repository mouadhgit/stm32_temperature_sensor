/**
  ******************************************************************************

  ADC Temperature sensor Code For STM32F407VG
  Author:   Mouadh Dahech
  Updated:  1/16/2021

  ******************************************************************************
  Copyright (C) 

  ******************************************************************************/




//#define CR1 *((int*)0xffffffff)

#include "ADC.h"

void GPIO_config()
{
  RCC->AHB1ENR |= (1 << 0);
  RCC->AHB1ENR |= (1 << 3);
  GPIOD->MODER = 0x55000000;  // PD12--PD15 output 
  
}

void ADC_config()
{
    // Enable the clock of Temp semsor connected to ADC1 ch16
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
   
    // disable vbat also F = F/2 , ADCPRE bit = 0 ==> F divide per 2 
    ADC->CCR &= ~0x00400000;
     
    // Select channel 16 for ADC1
    ADC1->SQR3 = 16;
   
    // Set SMPR1 to 84 cycle      f = 8 MHZ , 10us min sampling time so n_cycle >= 10*8 ==> C = 84
    ADC1->SMPR1 |= (1 << 20);

}

void ADC_Enable()
{
  ADC->CCR |= 0x00800000; // Enable Temperature sensor 

  // 1. Enable ADC 
  ADC1->CR2 |= (1 << 0);
 
 // Wait some Times the ADC to stablise 
  uint16_t i = 10000;
  while(i--);
}

void ADC_start(int channel)
{
	/************** STEPS TO FOLLOW *****************
	1. Set the channel Sequence in the SQR Register
	2. Clear the Status register
	3. Start the Conversion by Setting the SWSTART bit in CR2
	************************************************/
  
  ADC1->SQR3 = 0;
  ADC1->SQR3 |= (channel<<0);
  
  ADC1->SR  = 0;
  ADC1->CR2 |= (1<<30);  


}

uint16_t get_val (void)
{ 
  // Wait while conversion complete 
  while(!(ADC1->SR & (1<<1)));

  // return the conversion data 
  return ADC1->DR;
}
// 
void ADC_Disable()
{
  ADC1->CR2 &= ~(1<<0);
} 