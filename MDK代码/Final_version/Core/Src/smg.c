#include "smg.h"
#include "main.h"
#include "delay.h"
#include "stm32f4xx.h"


//共阴数字数组
//0,1,2,3,4,5,6,7,8,9,A,B,C,D,E,F, .,全灭
uint8_t smg_num[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e,0x01,0x00};
uint8_t point_smg_num[]={0xfd,0x61,0xdb,0xf3,0x67,0xb7,0xbf,0xe1,0xff,0xf7,0xef,0x3f,0x9d,0x7b,0x9f,0x8f};

void SMG_Init(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,GPIO_PIN_RESET);
}

//74HC138驱动
//数码管位选
//num:要显示的数码管编号 0-7(共8个数码管)
void LED_Wei(uint8_t num)
{
    LED_A0=num&0x01;
	LED_A1=(num&0x02)>>1;
	LED_A2=(num&0x04)>>2;
}
//74HC595驱动
//数码管显示
//duan:显示的段码
//wei:要显示的数码管编号 0-7(共8个数码管)
void LED_Write_Data(uint8_t duan,uint8_t wei)
{
	uint8_t i;
	for( i=0;i<8;i++)//先送段
	{
		LED_DS=(duan>>i)&0x01;
		LED_SCK=0;
		delay_us(5);
		LED_SCK=1;
	}
    LED_Wei(wei);//后选中位
}
//74HC595驱动
//数码管刷新显示
void LED_Refresh(void)
{
	LED_LCLK=1;
	delay_us(5);
	LED_LCLK=0;
}
// 使用数码管显示指定变量
void LED_Display(uint32_t distance)
{
	int8_t i;
	uint32_t display_number = distance;
	for(i=7;i >= 0;i--)
	{
		HAL_Delay(1);
		// 增加小数点
		if(i == 6) 
			LED_Write_Data(point_smg_num[display_number % 10],i);
		else
			LED_Write_Data(smg_num[display_number % 10],i);
		display_number /= 10;
		LED_Refresh();
		if(display_number == 0 && i < 7) break;
	}
	//LED_Refresh();
}









