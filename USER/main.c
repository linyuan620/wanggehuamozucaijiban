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
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();			     //LED�˿ڳ�ʼ��
	uart2_init(9600);	 	//����2��ʼ��Ϊ9600  pms5000 
	TIM2_Int_Init(49,7199);//10Khz�ļ���Ƶ�ʣ�������50Ϊ5ms  //5ms modbus ������ led
	TIM4_Int_Init(49,7199);//10Khz�ļ���Ƶ�ʣ�������50Ϊ 5ms    //5ms��ʱ pms500
	PMS_IO_Init();
	RS485_Initt(9600);
	Adc_Init(); 
 
	while(1)
	{	
			adcx=Get_Adc_Average(0,10);//ÿ������ʱ5ms ����� 50ms���ӳ�
			adc_value = (float)4.0*adcx*(3.3/4096)/11.0;
			TVOCPpm = 1000*TVOC_K*adc_value+TVOC_B; //�Ŵ�1000������λС��
	}
}



//ģ���
//usart1 modbus�ӻ� 3 0 
//time3 5ms modbus ֡��ȡ��ʱ�� 3 1
//time2 5s �ж� led modbus������ 3 2


//���ػ�����
//�����ȼ� �����ȼ�
//uart4 3 0     //modbus�ӻ�
//time7 3 1     // ֡��ȡ��ʱ��
//time2 3 2     // 50ms led �� modbus������
//usart3 3 3   //modbus����



