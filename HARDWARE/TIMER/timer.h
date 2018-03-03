#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
 
// 定时器配置

//T2 1s 定时器心跳包 计数用
//T4 0.15ms 定时器 FPGA 帧包计时
extern volatile  unsigned char One_second ;	 

void TIM2_Int_Init(u16 arr,u16 psc);

void TIM4_Int_Init(u16 arr,u16 psc); 
#endif
