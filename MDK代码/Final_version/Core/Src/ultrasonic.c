#include "tim.h"
#include "delay.h"
#include "stm32f4xx.h"
#include "ultrasonic.h"

extern uint8_t TIM1CH2_CAP_STA;
extern uint16_t TIM1CH2_CAP_VAL;


void Ultrasonic_Init(void)
{
	HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_2);	//一定要开启TIM1通道2的捕获中断
	__HAL_TIM_ENABLE_IT(&htim1,TIM_IT_UPDATE);	//一定要开启TIM1的更新中断
}

uint32_t Measure_distance(void)
{
	int i;
	uint32_t distance = 0;
	long long temp = 0;
	
	HAL_GPIO_WritePin(trig_GPIO_Port,trig_Pin,GPIO_PIN_SET);
	delay_us(20);
	HAL_GPIO_WritePin(trig_GPIO_Port,trig_Pin,GPIO_PIN_RESET);
	if(TIM1CH2_CAP_STA & 0X80){		//完成一次高电平捕获
		temp = TIM1CH2_CAP_STA & 0X3F;
		temp *= 65536;				//溢出总时间
		temp += TIM1CH2_CAP_VAL;	//总的高电平时间
		distance = (temp*0.34)/2;		//单位：cm
		TIM1CH2_CAP_STA = 0;		//准备下一次捕获
		return distance;
	}
	return 1000;
}









