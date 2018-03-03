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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ�ܣԣɣͣ�
	TIM_DeInit(TIM3);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Period =0xffff;       //
	TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ԥ��Ƶ��
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
	/*��ʼ��TIM3��ʱ�� */
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	/*-----------------------------------------------------------------*/
	//��������                        ����ģʽ
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	//TIM_ARRPreloadConfig(TIM3, ENABLE);
	// Clear all pending interrupts
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);   //ʹ���ж�
	//Reset counter
	TIM3->CNT =32768;
	TIM_Cmd(TIM3, ENABLE);   //ʹ�ܶ�ʱ��3
	
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
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʹ�ܣԣɣ�4
//	TIM_DeInit(TIM4);
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

//	TIM_TimeBaseStructure.TIM_Period =0xffff;       //
//	TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ԥ��Ƶ��
//	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
//  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
//	/*��ʼ��TIM4��ʱ�� */
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
//	/*-----------------------------------------------------------------*/
//	//��������                        ����ģʽ
//	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, 
//                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
//	TIM_ICInit(TIM4, &TIM_ICInitStructure);
//	//TIM_ARRPreloadConfig(TIM4, ENABLE);
//	// Clear all pending interrupts
//	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
//	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);   //ʹ���ж�
//	//Reset counter
//	TIM4->CNT =32768;
//	TIM_Cmd(TIM4, ENABLE);   //ʹ�ܶ�ʱ��4
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
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʹ�ܣԣɣ�5
//	TIM_DeInit(TIM5);
//	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

//	TIM_TimeBaseStructure.TIM_Period =0xffff;       //
//	TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ԥ��Ƶ��
//	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
//  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
//	/*��ʼ��TIM5��ʱ�� */
//	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
//	/*-----------------------------------------------------------------*/
//	//��������                        ����ģʽ
//	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, 
//                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
//	TIM_ICInit(TIM5, &TIM_ICInitStructure);
//	//TIM_ARRPreloadConfig(TIM5, ENABLE);
//	// Clear all pending interrupts
//	TIM_ClearFlag(TIM5, TIM_FLAG_Update);
//	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);   //ʹ���ж�
//	//Reset counter
//	TIM5->CNT =32768;
//	TIM_Cmd(TIM5, ENABLE);   //ʹ�ܶ�ʱ��5
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
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); //ʹ�ܣԣɣ�8
//	TIM_DeInit(TIM8);
//	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

//	TIM_TimeBaseStructure.TIM_Period =0xffff;       //
//	TIM_TimeBaseStructure.TIM_Prescaler =0;	    //����Ԥ��Ƶ��
//	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
//  //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1; 
//	/*��ʼ��TIM8��ʱ�� */
//	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
//	/*-----------------------------------------------------------------*/
//	//��������                        ����ģʽ
//	TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, 
//                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);  //TIM_ICPolarity_Rising�����ز���
//	TIM_ICStructInit(&TIM_ICInitStructure);
//	TIM_ICInitStructure.TIM_ICFilter = 6;         //�Ƚ��˲���
//	TIM_ICInit(TIM8, &TIM_ICInitStructure);
//	//TIM_ARRPreloadConfig(TIM8, ENABLE);
//	// Clear all pending interrupts
//	TIM_ClearFlag(TIM8, TIM_FLAG_Update);
//	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE);   //ʹ���ж�
//	//Reset counter
//	TIM8->CNT =32768;
//	TIM_Cmd(TIM8, ENABLE);   //ʹ�ܶ�ʱ��8
//}


void PLUSE_Encode_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//GPIO_InitTypeDef GPIO_InitStructure;

	TIM3_Mode_Config();//ENC1
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�0�� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;			//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); 

	//TIM4_Mode_Config();//ENC2
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�0�� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//�����ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); 

//	TIM5_Mode_Config();//ENC3
//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�0�� 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;			//�����ȼ�2
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure); 

//	TIM8_Mode_Config();//ENC4
//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�0�� 
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;			//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure); 
//	//ENC5 ��ͨio��ģ�������
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

//	  /*������5���*/
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
 /*������1-4���*/
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
 

//��ʱ��3�жϷ������
//void TIM3_IRQHandler(void)   //TIM3�ж�
//{
//	
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
//		{
//			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
//		}
//		
//}

//��ʱ��4�жϷ������
//void TIM4_IRQHandler(void)   //TIM4�ж�
//{
//	
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
//		{
//			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
//		}
//		
//}

//��ʱ��5�жϷ������
//void TIM5_IRQHandler(void)   //TIM5�ж�
//{
//	
//	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
//		{
//			TIM_ClearITPendingBit(TIM5, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
//		}
//		
//}

//��ʱ��8�жϷ������
//void TIM8_IRQHandler(void)   //TIM8�ж�
//{
//	
//	if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
//		{
//			TIM_ClearITPendingBit(TIM8, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
//		}
//		
//}

