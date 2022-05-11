#include "motor.h"


/*	用于控制左轮
	*参数X：定时器二通道一Pulse(占空比)
	*参数Y：定时器二通道二Pulse(占空比)
*/
void LEFT_WHEEL_CTRL(uint16_t X,uint16_t Y)
{
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,X);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,Y);
}

void RIGHT_WHEEL_CTRL(uint16_t X,uint16_t Y)
{
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,X);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_4,Y);
}



/*	车辆初始运行速度	*/
void CAR_STOP(void){
	LEFT_WHEEL_CTRL(NONE_SPEED,NONE_SPEED);
	RIGHT_WHEEL_CTRL(NONE_SPEED,NONE_SPEED);
}
void HIGH_SPEED_RUN(void)
{
	LEFT_WHEEL_CTRL(HIGH_SPEED,NONE_SPEED);
	RIGHT_WHEEL_CTRL(HIGH_SPEED,NONE_SPEED);
}
void MIDDLE_SPEED_RUN(void)
{
	LEFT_WHEEL_CTRL(MIDDLE_SPEED,NONE_SPEED);
	RIGHT_WHEEL_CTRL(MIDDLE_SPEED,NONE_SPEED);
}
void LOW_SPEED_RUN(void)
{
	LEFT_WHEEL_CTRL(LOW_SPEED,NONE_SPEED);
	RIGHT_WHEEL_CTRL(LOW_SPEED,NONE_SPEED);
}

/*	弯道调整	*/
void Bend_adjustment(uint8_t direction)
{
	//	向左转
	if(direction == Turn_to_left){
		LEFT_WHEEL_CTRL(NONE_SPEED,NONE_SPEED);
		RIGHT_WHEEL_CTRL(MIDDLE_SPEED,NONE_SPEED);
	}
	if(direction == Turn_to_right){
		LEFT_WHEEL_CTRL(MIDDLE_SPEED,NONE_SPEED);
		RIGHT_WHEEL_CTRL(NONE_SPEED,NONE_SPEED);
	}
}



