#ifndef __AM2305_H
#define __AM2305_H
#include "sys.h"

//IO方向设置 PG11
//#define DHT11_IO_IN()  {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=8<<12;}
//#define DHT11_IO_OUT() {GPIOG->CRH&=0XFFFF0FFF;GPIOG->CRH|=3<<12;}
#define DHT11_IO_IN()  {GPIOE->CRH&=0XFF0FFFFF;GPIOE->CRH|=8<<20;}
#define DHT11_IO_OUT() {GPIOE->CRH&=0XFF0FFFFF;GPIOE->CRH|=3<<20;}

////IO操作函数											   
#define	DHT11_DQ_OUT PEout(13) //数据端口	
#define	DHT11_DQ_IN  PEin(13)  //数据端口	


extern unsigned char Sensor_Data[5] ;
extern unsigned char Sensor_Check;		  //检验和

extern unsigned char Sensor_AnswerFlag;  //收到起始标志位
extern unsigned char Sensor_ErrorFlag;   //读取传感器错误标志
extern unsigned int  Sys_CNT;

extern unsigned int  OutdoorHumidity;
extern unsigned int  OutdoorTemperature; 

void AM2305_Init(void);
void Clear_Data (void);
unsigned char Read_SensorData(void);
unsigned char Read_Sensor(void);

 
#endif
