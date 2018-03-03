#ifndef __AM2305_H
#define __AM2305_H
#include "sys.h"

//IO�������� PG11
//#define DHT11_IO_IN()  {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=8<<12;}
//#define DHT11_IO_OUT() {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=3<<12;}
#define DHT11_IO_IN()  {GPIOE->CRH&=0XFF0FFFFF;GPIOE->CRH|=8<<20;}
#define DHT11_IO_OUT() {GPIOE->CRH&=0XFF0FFFFF;GPIOE->CRH|=3<<20;}

////IO��������											   
#define	DHT11_DQ_OUT PEout(13) //���ݶ˿�	
#define	DHT11_DQ_IN  PEin(13)  //���ݶ˿�	


extern unsigned char Sensor_Data[5] ;
extern unsigned char Sensor_Check;		  //�����

extern unsigned char Sensor_AnswerFlag;  //�յ���ʼ��־λ
extern unsigned char Sensor_ErrorFlag;   //��ȡ�����������־
extern unsigned int  Sys_CNT;

extern unsigned int  OutdoorHumidity;
extern unsigned int  OutdoorTemperature; 

void AM2305_Init(void);
void Clear_Data (void);
unsigned char Read_SensorData(void);
unsigned char Read_Sensor(void);

 
#endif
