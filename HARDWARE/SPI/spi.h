#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
 
//CS1�ӿڶ���
#define CS1 PBout(12)	// CS1�ӿ�		

void SPI2_Init(void);			 //��ʼ��SPI��
void SPI2_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPI2_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
		 
#endif

