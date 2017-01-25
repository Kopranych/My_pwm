#ifndef INTERRUPT_H_
#define INTERRUPT_H_


#include "stm32f4xx.h"                  // Device header



void init_delay(void);
void delay_ms(uint16_t delay_temp); // ������� �������� ������������� ����������� ���������� SysTick
void SysTick_Handler(void);// ������ ����������


#endif /*INTERRUPT_H_*/
