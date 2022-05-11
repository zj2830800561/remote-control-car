#ifndef __SMG_H
#define __SMG_H

#include "stm32f4xx_hal.h"

////74HC138操作线
#define LED_A0 PCout(10) //A0地址线
#define LED_A1 PCout(11) //A1地址线
#define LED_A2 PCout(12) //A2地址线

////74HC595操作线
#define LED_DS		PBout(3) //数据线
#define LED_LCLK	PBout(4) //锁存时钟线
#define LED_SCK		PBout(5) //时钟线



void SMG_Init(void);
void LED_Wei(uint8_t num);
void LED_Write_Data(uint8_t duan,uint8_t wei);
void LED_Refresh(void);
void LED_Display(uint32_t distance);








#endif // __SMG_H
