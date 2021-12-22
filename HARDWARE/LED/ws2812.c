#include "ws2812.h"

#define WS2812_Num 4

uint8_t color_buff[WS2812_Num*3]={0x0f,0x00,0x00,0x00,0x0f,0x00,0x00,0x0f,0x00,0x00,0x0f,0x00};





void RGB_LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 GPIO_ResetBits(GPIOB,GPIO_Pin_0);						 //PB.5 输出高

}
 

/********************************************************/
//
/********************************************************/
void RGB_LED_Write0(void)
{
	RGB_LED_HIGH;
	__nop();__nop();__nop();__nop();__nop();__nop();
	RGB_LED_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}
 
/********************************************************/
//
/********************************************************/
 
void RGB_LED_Write1(void)
{
	RGB_LED_HIGH;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
	RGB_LED_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}
 
void RGB_LED_Reset(void)
{
	uint8_t i;
	RGB_LED_LOW;
	for(i=0;i<4;i++)
    {
			RGB_LED_Write_24Bits(0, 0x00, 0);
    }
	delay_us(80);
}
 
void RGB_LED_Write_Byte(uint8_t byte)
{
	uint8_t i;
 
	for(i=0;i<8;i++)
		{
			if(byte&0x80)
				{
					RGB_LED_Write1();
			}
			else
				{
					RGB_LED_Write0();
			}
		byte <<= 1;
	}
}
 
void RGB_LED_Write_24Bits(uint8_t green,uint8_t red,uint8_t blue)
{
	RGB_LED_Write_Byte(green);
	RGB_LED_Write_Byte(red);
	RGB_LED_Write_Byte(blue);
}
 
void RGB_LED_ColorSet(uint8_t LED_Name,uint8_t green,uint8_t red,uint8_t blue)
{
	if(LED_Name > WS2812_Num)
		return;
	color_buff[(LED_Name-1)*3]=green;
	color_buff[(LED_Name-1)*3+1]=red;
	color_buff[(LED_Name-1)*3+2]=blue;
} 

void RGB_LED_Update(void)
 {
	 uint8_t i;
	 for(i=0;i<WS2812_Num;i++)
	 {
		 RGB_LED_Write_Byte(color_buff[i*3]);
		 RGB_LED_Write_Byte(color_buff[i*3+1]);
		 RGB_LED_Write_Byte(color_buff[i*3+2]);
	 }
 }
 
 
void RGB_LED_Red(void)
{
	 uint8_t i;
	for(i=0;i<1;i++)
		{
			RGB_LED_Write_24Bits(0, 0x0f, 0);
	    }
}
 
void RGB_LED_Green(void)
{
	uint8_t i;
 
	for(i=0;i<1;i++)
		{
			RGB_LED_Write_24Bits(0x0f, 0, 0);
	    }
}
 
void RGB_LED_Blue(void)
{
	uint8_t i;
 
	for(i=0;i<1;i++)
		{
			RGB_LED_Write_24Bits(0, 0, 0x0f);
	    }
}


