#ifndef _WS2812_H
#define _WS2812_H
#include "sys.h"
#include "delay.h"

#define 	RGB_LED 	     GPIO_PIN_0
#define		RGB_LED_HIGH	( GPIO_SetBits(GPIOB,GPIO_Pin_0))
#define 	RGB_LED_LOW		( GPIO_ResetBits(GPIOB,GPIO_Pin_0))
 
void RGB_LED_Init(void);
void RGB_LED_Write0(void);
void RGB_LED_Write1(void);
void RGB_LED_Reset(void);
void RGB_LED_Write_Byte(uint8_t byte);
void RGB_LED_Write_24Bits(uint8_t green,uint8_t red,uint8_t blue);
void RGB_LED_Red(void);
void RGB_LED_Green(void);
void RGB_LED_Blue	(void);
void RGB_LED_Update(void);
void RGB_LED_ColorSet(uint8_t LED_Name,uint8_t green,uint8_t red,uint8_t blue);
#endif
