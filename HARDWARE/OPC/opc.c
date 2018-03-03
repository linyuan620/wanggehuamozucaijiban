#include "opc.h" 

#include "delay.h"   
#include "spi.h"


u8 temArr[16] = {0};
u8 temInfo[60] = {0};

float* PM1 = (float*)&temArr[0];
float* PM25 = (float*)&temArr[4];
float* PM10 = (float*)&temArr[8];

float Opc_Pm1=0;
float Opc_Pm25=0;
float Opc_Pm10=0;
	
//初始化SPI OPC的IO口
void SPI_Opc_Init(void)
{	
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTB时钟使能 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  // PB12 推挽 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_ResetBits(GPIOB,GPIO_Pin_12);

	SPI2_Init();		   	//初始化SPI
	SPI2_SetSpeed(SPI_BaudRatePrescaler_64);//设置为18M时钟,高速模式
	 
}  

////读取SPI_Opc的状态寄存器
 
u8 SPI_Opc_ReadSR(void)   
{  
	u8 byte=0;   
	SPI_Opc_CS=0;                            //使能器件   
	byte = SPI2_ReadWriteByte(0x03);                  //发送读取状态寄存器命令    
	 
	SPI_Opc_CS=1;                            //取消片选     
	return byte;   
} 

u8 SPI_Opc_CloseFan(void)   
{  
	u8 byte=0;   
	SPI_Opc_CS=0;                            //使能器件   
	byte = SPI2_ReadWriteByte(0x01);                  //发送读取状态寄存器命令    
	 
	SPI_Opc_CS=1;                            //取消片选     
	return byte;   
} 

u8 SPI_Opc_OpenFan(void)   
{  
	u8 byte=0;   
	SPI_Opc_CS=0;                            //使能器件   
	byte = SPI2_ReadWriteByte(0x00);                  //发送读取状态寄存器命令    
	 
	SPI_Opc_CS=1;                            //取消片选     
	return byte;   
} 



void SPI_Opc_ReadPM(void)
{
	u8 i = 0;
	
	SPI_Opc_CS=0;	
	i = SPI2_ReadWriteByte(0x32);

	delay_ms(10);	
  for(i=0;i<12;i++)
	{
		temArr[i] = SPI2_ReadWriteByte(0xff);//发送读取PM数据命令	    
		delay_us(6);	
	}
	
  Opc_Pm1 = *PM1;
	Opc_Pm25 = *PM25;
	Opc_Pm10 = *PM10;
	
	SPI_Opc_CS=1;				    

}

void SPI_Opc_ReadInfo(void)
{
	
	u8 i = 0;
	
	SPI_Opc_CS=0;	
	SPI2_ReadWriteByte(0x3F);

	delay_ms(10);	
  for(i=0;i<60;i++)
	{
		temInfo[i] = SPI2_ReadWriteByte(0xff);//发送读取PM数据命令	    
		delay_us(6);	
	}
  
	SPI_Opc_CS=1;				    
 
}
