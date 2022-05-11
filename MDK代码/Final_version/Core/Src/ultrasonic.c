#include "tim.h"
#include "delay.h"
#include "stm32f4xx.h"
#include "ultrasonic.h"

extern uint8_t TIM1CH2_CAP_STA;
extern uint16_t TIM1CH2_CAP_VAL;


void Ultrasonic_Init(void)
{
	HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_2);	//һ��Ҫ����TIM1ͨ��2�Ĳ����ж�
	__HAL_TIM_ENABLE_IT(&htim1,TIM_IT_UPDATE);	//һ��Ҫ����TIM1�ĸ����ж�
}

uint32_t Measure_distance(void)
{
	int i;
	uint32_t distance = 0;
	long long temp = 0;
	
	HAL_GPIO_WritePin(trig_GPIO_Port,trig_Pin,GPIO_PIN_SET);
	delay_us(20);
	HAL_GPIO_WritePin(trig_GPIO_Port,trig_Pin,GPIO_PIN_RESET);
	if(TIM1CH2_CAP_STA & 0X80){		//���һ�θߵ�ƽ����
		temp = TIM1CH2_CAP_STA & 0X3F;
		temp *= 65536;				//�����ʱ��
		temp += TIM1CH2_CAP_VAL;	//�ܵĸߵ�ƽʱ��
		distance = (temp*0.34)/2;		//��λ��cm
		TIM1CH2_CAP_STA = 0;		//׼����һ�β���
		return distance;
	}
	return 1000;
}









