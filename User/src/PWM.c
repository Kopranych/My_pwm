

#include "PWM.h"

uint8_t PWM_count = 0;
uint8_t PWM_duty_cycle = 20, PWM_period = 20;
uint8_t PWM_count_DC_UP = 0,PWM_count_DC_DOWN = 0;
uint8_t increase = 0, period_delay = 10;


void SysTick_PWM(void)
{
	if(PWM_count>= PWM_period)
	{
		GPIO_ResetBits(PWM_bus, PWM_pin);		
		PWM_count = 0;
	}
	else if(PWM_count == PWM_duty_cycle)
	{
		GPIO_SetBits(PWM_bus, PWM_pin);
		PWM_count++;
	}
	else 
		PWM_count++;
}


void PWM_increase(void)
{
	if(increase)
	{
		if(PWM_count_DC_UP >= 60)
		{
			PWM_count_DC_UP = 0;
			if(PWM_duty_cycle < PWM_period)
				PWM_duty_cycle++;
			else 
				if(period_delay)//���� �������� ������������ � ����������� �������
				{
					PWM_duty_cycle = PWM_period;
					period_delay--;
				}
			  else
				{
				 increase = 0;
				 period_delay = 30;				
				}
		}
		else 
		{
			PWM_count_DC_UP++;
		}
	}
	else
		{
		if(PWM_count_DC_DOWN >= 60)
		{
			PWM_count_DC_DOWN = 0;
			if(PWM_duty_cycle > 0)
			{
				PWM_duty_cycle--;

			}
			else 
				if(period_delay)//���� �������� ������������ � ����������� �������
				{
					PWM_duty_cycle = 0;
					period_delay--;
				}
			  else
				{
				 increase = 1;
					period_delay = 30;				
				}
		}
		else 
		{
			PWM_count_DC_DOWN++;
		}
	}
}
//-----------------------------------------------------------------

void PWM_hard(void)
{
	TIM_TimeBaseInitTypeDef timer_pwm;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);// clock tim4
	
	
	timer_pwm.TIM_Prescaler = 0;
	timer_pwm.TIM_CounterMode = TIM_CounterMode_Up;
	timer_pwm.TIM_Period = 1000;
	timer_pwm.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM4, &timer_pwm);// �������������� ������
	
	GPIO_InitTypeDef GPIO_D;// ��������� ��������� ��� ������������� ������
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//�������� ������������ ���� AHB1 �� ��� ����� D � A
	//������������� ������ ������ ����� D
	GPIO_D.GPIO_Pin = GPIO_Pin_12;
	GPIO_D.GPIO_Mode = GPIO_Mode_AF;//output analog
	GPIO_D.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_D.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_D.GPIO_OType = GPIO_OType_PP;
	
	GPIO_Init(GPIOD, &GPIO_D);// �������������� ���� �����
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12,GPIO_AF_TIM4);
	
	TIM_OCInitTypeDef PWM_hard_init;// ��������� ������������� ��������� ��������� �������
	PWM_hard_init.TIM_OCMode = TIM_OCMode_PWM1;//����� ������ �������
	PWM_hard_init.TIM_OutputState = TIM_OutputState_Enable; //���������/���������� ������ ���� ������
	PWM_hard_init.TIM_Pulse = 500; // ������������� �������� �� 0 �� timer_pwm.TIM_Period ����� ���� ������������
	PWM_hard_init.TIM_OCPolarity = TIM_OCPolarity_High;//���������� ��� ������ ��� ���������
	
	TIM_OC1Init(TIM4, &PWM_hard_init);// �������������� ��� ������ OC1Init �� ��������� LD4 ����� �� ����� PD12 ������� �� 1 ������ ������� 4
	
	TIM_Cmd(TIM4, ENABLE);//�������� ������
	
}

