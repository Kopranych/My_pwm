#include "stm32f4xx.h"                  // Device header
#include "main.h"
#include "interrupt.h"
#include "PWM.h"

int main()
{
	uint32_t period =0;
	uint8_t flag = 1;
	init_perif();
	init_delay();
	PWM_hard();
	GPIO_SetBits(GPIOD, GPIO_Pin_14);
	while(1)
	{
		TIM_SetCompare1(TIM4, period);//������ SetCompare1 �� ��������� LD4 ����� �� ����� PD12 ������� �� 1 ������ ������� 4
		if(flag)
		{
			if(period < 1000)
				period++;
			else 
				flag = 0;
		}
		else
		{	
			if(period > 0)
				period --;
			else
				flag = 1;
		}
		delay_ms(1);
				
	}
}
