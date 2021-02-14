
/**
  ******************************************************************************

  ADC Code For STM32F407VG
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
  ADC_config();
  ADC_Enable();
  GPIO_config();
  while (1)
  {
    ADC_start(16);
    temp_VAL = get_val();
    volatge = temp_VAL*3.3 /4095;
    Temp_deg = (volatge - 0.76)/0.0025  ;

  }
  return 0 ; 
}