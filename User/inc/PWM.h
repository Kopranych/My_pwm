#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f4xx.h"                  // Device header

#define PWM_bus GPIOD
#define PWM_pin GPIO_Pin_14



void SysTick_PWM(void);//PWM software
void PWM_increase(void);//PWM плавное включение и выключение светодиода
void PWM_hard(void);//PWM hardware

#endif /*MAIN_H_*/
