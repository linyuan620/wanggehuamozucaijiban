#include "exti.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"

//外部中断12服务程序

unsigned int beta_cnt =0;

//void EXTIX_Init(void)
//{

// 	EXTI_InitTypeDef EXTI_InitStructure;
// 	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	//初始化PB12  上拉输入
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTB时钟

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//PB12
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB12
//	
//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

//   //GPIOB.12 中断线以及中断初始化配置   下降沿触发
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);

//  	EXTI_InitStructure.EXTI_Line=EXTI_Line12;	
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

//    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);
//	
//}

//void EXTIX_Init(void)
//{

// 	EXTI_InitTypeDef EXTI_InitStructure;
// 	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	//初始化PE2  上拉输入
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//PE2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
// 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE2
//	
//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

//   //GPIOE.2 中断线以及中断初始化配置   下降沿触发
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

//  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

//      NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY2所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级2
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);
//	
//}

 //外部中断2服务程序
//void EXTI15_10_IRQHandler(void)
//{
//	if(One_second == 1)
//	{
//		One_second = 0;	
//	}
//	beta_cnt ++;
//	EXTI_ClearITPendingBit(EXTI_Line12);  //清除LINE12上的中断标志位  
//}

