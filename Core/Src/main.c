
/**
  ******************************************************************************

  STM32F407VG Code to do the flow diagram in the photo "Flow diagram.PNG"
  Author:   Mouadh Dahech
  Updated:  1/16/2021

  ******************************************************************************
  Copyright (C) 

  ******************************************************************************
*/



#include "main.h"

uint16_t temp_VAL = 0 ; 
double volatge    = 0.0;
double Temp_deg   = 0.0;

int main(void)
{
  SystemClock();
  UART_config();
  ADC_config();
  ADC_Enable();
  GPIO_config();
  while (1)
  {
    ADC_start(16);
    temp_VAL = get_val();
    volatge = temp_VAL*3.3 /4095;
    Temp_deg = (volatge - 0.76)/0.0025  ;

    if(Temp_deg > 30)
       GPIOD->ODR = 0xF000;
    else
       GPIOD->ODR = 0x0000;

    if(GPIOA->IDR & 0x0001)
      Send_Char('P');
  }
  return 0 ; 
}

 void Send_Char(uint8_t ch)
{
  		/*********** STEPS FOLLOWED *************
	
	1. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
		 for each data to be transmitted in case of single buffer.
	2. After writing the last data into the USART_DR register, wait until TC=1. This indicates
		 that the transmission of the last frame is complete. This is required for instance when
		 the USART is disabled or enters the Halt mode to avoid corrupting the last transmission.
	
	****************************************/
  
  USART3->DR = ch;
  while(!(USART3->SR & (1<<6)));   // while(0) if TC = 1 , while(1) if TC = 0 
}