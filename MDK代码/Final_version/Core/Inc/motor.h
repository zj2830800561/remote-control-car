#ifndef __MOTOR_CTRL_H_
#define __MOTOR_CTRL_H_


#include "stm32f4xx_hal.h"
#include "tim.h"

#define	HIGH_SPEED		1000
#define	MIDDLE_SPEED	900
#define	LOW_SPEED		800
#define	NONE_SPEED		0
#define	Turn_to_left	0x10
#define	Turn_to_right	0x20

void LEFT_WHEEL_CTRL(uint16_t X,uint16_t Y);
void RIGHT_WHEEL_CTRL(uint16_t X,uint16_t Y);

void CAR_STOP(void);
void HIGH_SPEED_RUN(void);
void MIDDLE_SPEED_RUN(void);
void LOW_SPEED_RUN(void);

void Bend_adjustment(uint8_t direction);

#endif // __MOTOR_CTRL_H_

