#include "pluse_encode.h"
 

ENCODE_T g_tEncode[ENCODE_COUNT];

void TIM3_Mode_Config(void)
{
	//u16 CCR1_Val = 2500;
	//u16 CCR2_Val = 1000;
//	int i=0;
//	for(i=0;i<ENCODE_COUNT;i++){
//		//g_tEncode[i].encoderDir=0;
//		g_tEncode[i].encoderNum=32768;
//	}
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	//TIM_OCInitTypeDef  TIM_OCInitStructure;
/*----------------------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_StructInit(&GPIO_InitStructure);
	/* Configure PA.06,07 as encoder input */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
/*----------------------------------------------------------------*/	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //使能ＴＩＭ３
	TIM_DeInit(TIM3);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Period =0xffff;       //
	TIM_TimeBaseStructure.TIM_Prescaler =0;	    //设置预分频：
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*初始化TIM3定时器 */
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	/*-----------------------------------------------------------------*/
	//编码配置                        编码模式
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising上升沿捕获
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;         //比较滤波器
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	//TIM_ARRPreloadConfig(TIM3, ENABLE);
	// Clear all pending interrupts
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);   //使能中断
	//Reset counter
	TIM3->CNT =32768;
	TIM_Cmd(TIM3, ENABLE);   //使能定时器3
	
}

//void TIM4_Mode_Config(void)
//{
//	//u16 CCR1_Val = 2500;
//	//u16 CCR2_Val = 1000;
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_ICInitTypeDef TIM_ICInitStructure;
//	//TIM_OCInitTypeDef  TIM_OCInitStructure;
///*----------------------------------------------------------------*/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//	GPIO_StructInit(&GPIO_InitStructure);
//	/* Configure PB.06,07 as encoder input */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
///*----------------------------------------------------------------*/	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //使能ＴＩＭ4
//	TIM_DeInit(TIM4);
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

//	TIM_TimeBaseStructure.TIM_Period =0xffff;       //
//	TIM_TimeBaseStructure.TIM_Prescaler =0;	    //设置预分频：
//	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
//  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
//	/*初始化TIM4定时器 */
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
//	/*-----------------------------------------------------------------*/
//	//编码配置                        编码模式
//	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, 
//                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising上升沿捕获
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	TIM_ICInitStructure.TIM_ICFilter = 6;         //比较滤波器
//	TIM_ICInit(TIM4, &TIM_ICInitStructure);
//	//TIM_ARRPreloadConfig(TIM4, ENABLE);
//	// Clear all pending interrupts
//	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
//	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);   //使能中断
//	//Reset counter
//	TIM4->CNT =32768;
//	TIM_Cmd(TIM4, ENABLE);   //使能定时器4
//}

//void TIM5_Mode_Config(void)
//{
//	//u16 CCR1_Val = 2500;
//	//u16 CCR2_Val = 1000;
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_ICInitTypeDef TIM_ICInitStructure;
//	//TIM_OCInitTypeDef  TIM_OCInitStructure;
///*----------------------------------------------------------------*/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	GPIO_StructInit(&GPIO_InitStructure);
//	/* Configure PA.00,01 as encoder input */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
///*----------------------------------------------------------------*/	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //使能ＴＩＭ5
//	TIM_DeInit(TIM5);
//	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

//	TIM_TimeBaseStructure.TIM_Period =0xffff;       //
//	TIM_TimeBaseStructure.TIM_Prescaler =0;	    //设置预分频：
//	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
//  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
//	/*初始化TIM5定时器 */
//	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
//	/*-----------------------------------------------------------------*/
//	//编码配置                        编码模式
//	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, 
//                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising上升沿捕获
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	TIM_ICInitStructure.TIM_ICFilter = 6;         //比较滤波器
//	TIM_ICInit(TIM5, &TIM_ICInitStructure);
//	//TIM_ARRPreloadConfig(TIM5, ENABLE);
//	// Clear all pending interrupts
//	TIM_ClearFlag(TIM5, TIM_FLAG_Update);
//	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);   //使能中断
//	//Reset counter
//	TIM5->CNT =32768;
//	TIM_Cmd(TIM5, ENABLE);   //使能定时器5
//}

//void TIM8_Mode_Config(void)
//{
//	//u16 CCR1_Val = 2500;
//	//u16 CCR2_Val = 1000;
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	TIM_ICInitTypeDef TIM_ICInitStructure;
//	//TIM_OCInitTypeDef  TIM_OCInitStructure;
///*----------------------------------------------------------------*/
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
//	GPIO_StructInit(&GPIO_InitStructure);
//	/* Configure PC.06,07 as encoder input */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
///*----------------------------------------------------------------*/	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); //使能ＴＩＭ8
//	TIM_DeInit(TIM8);
//	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

//	TIM_TimeBaseStructure.TIM_Period =0xffff;       //
//	TIM_TimeBaseStructure.TIM_Prescaler =0;	    //设置预分频：
//	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
//  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
//	/*初始化TIM8定时器 */
//	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
//	/*-----------------------------------------------------------------*/
//	//编码配置                        编码模式
//	TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, 
//                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising上升沿捕获
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	TIM_ICInitStructure.TIM_ICFilter = 6;         //比较滤波器
//	TIM_ICInit(TIM8, &TIM_ICInitStructure);
//	//TIM_ARRPreloadConfig(TIM8, ENABLE);
//	// Clear all pending interrupts
//	TIM_ClearFlag(TIM8, TIM_FLAG_Update);
//	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);   //使能中断
//	//Reset counter
//	TIM8->CNT =32768;
//	TIM_Cmd(TIM8, ENABLE);   //使能定时器8
//}


void PLUSE_Encode_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//GPIO_InitTypeDef GPIO_InitStructure;

	TIM3_Mode_Config();//ENC1
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级0， 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;			//子优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); 

	//TIM4_Mode_Config();//ENC2
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级0， 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); 

//	TIM5_Mode_Config();//ENC3
//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级0， 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			//子优先级2
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//使能外部中断通道
//	NVIC_Init(&NVIC_InitStructure); 

//	TIM8_Mode_Config();//ENC4
//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级0， 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;			//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//使能外部中断通道
//	NVIC_Init(&NVIC_InitStructure); 
//	//ENC5 普通io口模拟编码器
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

//	GPIO_InitStructure.GPIO_Pin  =GPIO_Pin_2|GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
//	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void UpdatePluseEncode(void)
{
//	static uint8_t 	TmpValueA;
//	static uint8_t 	TmpValueB;
//	static uint8_t  pre_sts_PinA = 0;
//	static uint8_t  pre_sts_PinB = 0;
//	static uint8_t  rotate_cnt_out = 0x20;
//	static uint8_t  rotate_sts = 0;
//	//TmpPin = inpw((uint32_t)&GPIOA->PIN);
//	TmpValueA=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);
//	TmpValueB=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);

//	  /*编码器5检测*/
//	if ((pre_sts_PinA == 1) && (pre_sts_PinB == 1))
//	{
//		rotate_sts = 1;
//	}

//	if (rotate_sts == 1)
//	{
//		if ((TmpValueA == 0) && TmpValueB)
//		{
//			if (rotate_cnt_out == 0x40)
//			{
//				rotate_cnt_out = 0x00;
//			}
//			else
//			{
//				rotate_cnt_out++;
//			}
//			rotate_sts = 0;
//		}
//		else if (TmpValueA && (TmpValueB == 0))
//		{
//			if (rotate_cnt_out == 0x00)
//			{
//				rotate_cnt_out = 0x40;
//			}
//			else
//			{
//				rotate_cnt_out--;
//			}
//			rotate_sts = 0;
//		}
//	}
//	
//	pre_sts_PinA = TmpValueA;
//	pre_sts_PinB = TmpValueB;
//	pDesArr[28]=0;
//	pDesArr[29]=rotate_cnt_out;
 /*编码器1-4检测*/
	g_tEncode[0].encoderNum=TIM_GetCounter(TIM4);
//	g_tEncode[1].encoderNum=TIM_GetCounter(TIM5);
	g_tEncode[1].encoderNum=TIM_GetCounter(TIM3);
//	g_tEncode[3].encoderNum=TIM_GetCounter(TIM8);

//	pDesArr[20]=*((unsigned char*)(&g_tEncode[0].encoderNum)+1);
//	pDesArr[21]=g_tEncode[0].encoderNum;
//	pDesArr[22]=*((unsigned char*)(&g_tEncode[1].encoderNum)+1);
//	pDesArr[23]=g_tEncode[1].encoderNum;
//	pDesArr[24]=*((unsigned char*)(&g_tEncode[2].encoderNum)+1);
//	pDesArr[25]=g_tEncode[2].encoderNum;
//	pDesArr[26]=*((unsigned char*)(&g_tEncode[3].encoderNum)+1);
//	pDesArr[27]=g_tEncode[3].encoderNum;
	//g_tEncode[3].encoderDir=(TIM8->CR1>>4)&0x0F;
	
}
 

//定时器3中断服务程序
//void TIM3_IRQHandler(void)   //TIM3中断
//{
//	
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
//		{
//			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
//		}
//		
//}

//定时器4中断服务程序
//void TIM4_IRQHandler(void)   //TIM4中断
//{
//	
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
//		{
//			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
//		}
//		
//}

//定时器5中断服务程序
//void TIM5_IRQHandler(void)   //TIM5中断
//{
//	
//	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
//		{
//			TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
//		}
//		
//}

//定时器8中断服务程序
//void TIM8_IRQHandler(void)   //TIM8中断
//{
//	
//	if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
//		{
//			TIM_ClearITPendingBit(TIM8, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
//		}
//		
//}

