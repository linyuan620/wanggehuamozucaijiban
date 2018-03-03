#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
 
//CS1接口定义
#define CS1 PBout(12)	// CS1接口		

void SPI2_Init(void);			 //初始化SPI口
void SPI2_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8 SPI2_ReadWriteByte(u8 TxData);//SPI总线读写一个字节
		 
#endif

