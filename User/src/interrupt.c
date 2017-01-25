
#include "interrupt.h"
#include "PWM.h"
uint16_t delay_count = 0;

void init_delay(void)
{
	SysTick_Config(SystemCoreClock/1000);//������������� SysTick ������ ���������� ��� � 1/1000 ���.
}


void SysTick_Handler(void)// ������ ����������
{
	if(delay_count>0)
		delay_count--;
	SysTick_PWM();
	PWM_increase();
	
}

void delay_ms(uint16_t delay_temp) // ������� �������� ������������� ����������� ���������� SysTick
{
	delay_count = delay_temp;
	while(delay_count);
}


