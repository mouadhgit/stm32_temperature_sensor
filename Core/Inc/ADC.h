/**
  ******************************************************************************

  ADC Code For STM32F407VG
  Author:   Mouadh Dahech
  Updated:  1/16/2021

  ******************************************************************************
  Copyright (C) 

  ******************************************************************************
*/
#ifndef __ADC_H__
#define __ADC_H__

#include "stm32f407xx.h"
#include "stm32f4xx.h"

void ADC_config();
void GPIO_config();
void ADC_Enable();
void ADC_start(int channel);
uint16_t get_val (void);
void ADC_Disable();
#endif 