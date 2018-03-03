#include "awa5636.h"
#include "delay.h"
#include "usart.h"	 
#include <string.h>
#include <stdlib.h>

u16 noise=0;
u16 res_cut=0;
u8 AWA_TX_BUF[8]={'A','W','A','0'}; 

u8 AWA_RX_BUF[200]={0}; 

char des1[20];
char des2[5];//awaa
char des3[6];// 24.6



u16 Read_Noise(void)
{
	u8 t;
	
	for(t=0;t<15;t++)		//ѭ����������
	{		   
		AWA_RX_BUF[t] = 0;
	}	 
  res_cut = 0;
  for(t=0;t<4;t++)		//ѭ����������
	{		   
		while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);	  
		USART_SendData(UART4,AWA_TX_BUF[t]);
	}	 
 
	while(USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);	
	
	delay_ms(100);
	if(res_cut>10)
	{
		memcpy(des1,AWA_RX_BUF,12);
		des1[12] = '\0';
	}
	strncpy(des2,des1,4);
	strncpy(des3,des1+5,5);
	noise=10*atof(des3);
	return noise;
}



//��ʼ��IO ����4
//bound:������
//noise 
void uart4_init(u32 bound){
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//ʹ��UART4ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//ʹ��GPIOCʱ��

	USART_DeInit(UART4);  //��λ����4
	
	//UART4_TX   PC.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��PC10

	//UART4_RX	  PC.11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOC, &GPIO_InitStructure);  //��ʼ��PC11

	//Uart4 NVIC ����

	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//UART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(UART4, &USART_InitStructure); //��ʼ������
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ��� 
}


//��ʼ��IO ����5 
//bound:������
//nvr
void uart5_init(u32 bound){
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//ʹ��UART5ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	//ʹ��GPIOCʱ��

	USART_DeInit(UART5);  //��λ����4
	
	//UART5_TX   PC.12
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PC12
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��PC12

	//UART5_RX	  PD.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ��PD2

	//Uart5 NVIC ����

	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

	//UART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(UART5, &USART_InitStructure); //��ʼ������
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�����ж�
	USART_Cmd(UART5, ENABLE);                    //ʹ�ܴ��� 
}

void UART4_IRQHandler(void)
{

 	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET) //���յ�����
	{	 
	 	AWA_RX_BUF[res_cut] =USART_ReceiveData(UART4); 	//��ȡ���յ�������
		res_cut++;
	}  											 
} 

void UART5_IRQHandler(void)
{
	u8 res = 0  ;
 	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET) //���յ�����
	{	 
		res = res;
	 	res = USART_ReceiveData(UART5); 	//��ȡ���յ�������
	}  											 
} 


