#include "led.h"
#include "delay.h"
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "oled.h"
#include "ws2812.h"
#include "semphr.h"

/************************************************
 ALIENTEK Mini STM32F103开发板 FreeRTOS实验2-1
 FreeRTOS移植实验-库函数版本
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


#define START_TASK_PRIO    1
#define START_STACK_SIZE   128
TaskHandle_t StartTask_Handle;
void start_task(void);

#define RGB_TASK_PRIO    2
#define RGB_STACK_SIZE   128
TaskHandle_t RgbTask_Handle;
void rgb_task(void);

#define OLED_TASK_PRIO    2
#define OLED_STACK_SIZE   128
TaskHandle_t OledTask_Handle;
void oled_task(void);

SemaphoreHandle_t BinarySemaphore;

int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4	 
	RGB_LED_Init();
	OLED_Init();
	OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	OLED_ShowString(5,18,(u8 *)"LED2:",12,1);
    OLED_ShowString(5,34,(u8 *)"LED3:",12,1);
	OLED_ShowString(5,50,(u8 *)"LED4:",12,1);
	OLED_ShowString(5,2,(u8 *)"LED1:",12,1);

	uart_init(115200);
    xTaskCreate((TaskFunction_t )start_task,
                (const char *)"start_task",
                (uint16_t )START_STACK_SIZE,
                (void * )NULL,
                (UBaseType_t )START_TASK_PRIO,
                (TaskHandle_t *)StartTask_Handle);
	vTaskStartScheduler();          //开启任务调度
}

void start_task(void)
{
    taskENTER_CRITICAL();

    xTaskCreate((TaskFunction_t )rgb_task,
            (const char *)"rgb_task",
            (uint16_t )RGB_STACK_SIZE,
            (void * )NULL,
            (UBaseType_t )RGB_TASK_PRIO,
            (TaskHandle_t *)RgbTask_Handle);
	xTaskCreate((TaskFunction_t )oled_task,
		(const char *)"oled_task",
		(uint16_t )OLED_STACK_SIZE,
		(void * )NULL,
		(UBaseType_t )OLED_TASK_PRIO,
		(TaskHandle_t *)OledTask_Handle); 
    vTaskDelete(StartTask_Handle);
    taskEXIT_CRITICAL();
}
char oled_buff[16];
void rgb_task(void)
{
	uint32_t colour=0;
    for(;;)
    {
		if(colour<120)
			colour+=10;
		else
			colour=0;
		delay_ms(500);
		RGB_LED_ColorSet(1,colour,colour,colour);
		RGB_LED_ColorSet(2,colour,colour,colour);
		RGB_LED_ColorSet(3,colour,colour,colour);
		RGB_LED_ColorSet(4,colour,colour,colour);
	    printf("RGB TASK : %d\r\n",colour);
		sprintf(oled_buff,"%d",colour);
		
//		taskENTER_CRITICAL();
		RGB_LED_Update();
//		taskEXIT_CRITICAL();


    }
}

void oled_task(void)
{

	for(;;)
    {
		Partial_OLED_Clear(60,80,2,16);
		
		OLED_ShowString(60,2,(u8 *)oled_buff,12,1);
		OLED_Refresh();
		memset(oled_buff,16,0);
//		OLED_ShowChinese(0,0,0,16,1);//中
//		OLED_ShowChinese(18,0,1,16,1);//景
//		OLED_ShowChinese(36,0,2,16,1);//园
//		OLED_ShowChinese(54,0,3,16,1);//电
//		OLED_ShowChinese(72,0,4,16,1);//子
//		OLED_ShowChinese(90,0,5,16,1);//技
//		OLED_ShowChinese(108,0,6,16,1);//术
		printf("OLED TASK : \r\n");
//		OLED_ShowString(5,2,"LED1:",12,1);
//		OLED_ShowString(45,2,oled_buff,12,1);
//		OLED_ShowString(5,18,"LED2:",12,1);
//		OLED_ShowString(5,34,"LED3:",12,1);
//		OLED_ShowString(5,50,"LED4:",12,1);
//		OLED_Refresh();
		delay_ms(500);
	}
}

