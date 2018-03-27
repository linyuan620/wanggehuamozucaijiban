#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "led.h"
#include "math.h"
#include "adc.h"
#include "response.h"
#include "modbus_slave.h"
#include "mbcrc.h"

//#define TVOC_K 19.048
//#define TVOC_B -571

#define TVOC_K 1
#define TVOC_B 0

u16 adcx;
float adc_value;

u32 TVOCPpm; 

int main(void)
{		
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LED_Init();			     //LED端口初始化
	uart2_init(9600);	 	//串口2初始化为9600  pms5000 
	TIM2_Int_Init(49,7199);//10Khz的计数频率，计数到50为5ms  //5ms modbus 服务处理 led
	TIM4_Int_Init(49,7199);//10Khz的计数频率，计数到50为 5ms    //5ms计时 pms500
	PMS_IO_Init();
	RS485_Initt(9600);
	Adc_Init(); 
 
	while(1)
	{	
			adcx=Get_Adc_Average(0,10);//每次是延时5ms 这就是 50ms的延迟
			adc_value = (float)4.0*adcx*(3.3/4096)/11.0;
			TVOCPpm = 1000*TVOC_K*adc_value+TVOC_B; //放大1000保留三位小数
	}
}



//模组板
//usart1 modbus从机 3 0 
//time3 5ms modbus 帧截取定时器 3 1
//time2 5s 中断 led modbus服务处理 3 2


//工控机背板
//主优先级 从优先级
//uart4 3 0     //modbus从机
//time7 3 1     // 帧截取定时器
//time2 3 2     // 50ms led 与 modbus服务处理
//usart3 3 3   //modbus主机



