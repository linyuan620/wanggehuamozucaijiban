#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
 
// ��ʱ������

//T2 1s ��ʱ�������� ������
//T4 0.15ms ��ʱ�� FPGA ֡����ʱ
extern volatile  unsigned char One_second ;	 

void TIM2_Int_Init(u16 arr,u16 psc);

void TIM4_Int_Init(u16 arr,u16 psc); 
#endif
