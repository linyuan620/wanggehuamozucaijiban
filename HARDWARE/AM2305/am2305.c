#include "am2305.h"
#include "delay.h"

unsigned char Sensor_Data[5]={0x00,0x00,0x00,0x00,0x00};
unsigned char Sensor_Check;		  //�����

unsigned char Sensor_AnswerFlag;  //�յ���ʼ��־λ
unsigned char Sensor_ErrorFlag;   //��ȡ�����������־
unsigned int  Sys_CNT;
unsigned int  Tmp;

unsigned int  OutdoorHumidity;
unsigned int  OutdoorTemperature; 
 	 
void AM2305_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PE�˿�ʱ��
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //PE13�˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				 //��ʼ��IO��
 	GPIO_SetBits(GPIOE,GPIO_Pin_13);						 //PE13 �����
} 


 
void Clear_Data (void)
{
	int i;
	for(i=0;i<5;i++)
	{
		Sensor_Data[i] = 0x00;
	}//������������
}


/********************************************\
|* ���ܣ���ȡ���������͵ĵ������� *|
\********************************************/
unsigned char Read_SensorData(void)
{
	unsigned char i,cnt;
	unsigned char buffer,tmp;
	buffer = 0;
	for(i=0;i<8;i++)
	{
		cnt=0;
		DHT11_IO_IN();
		//while(!Sensor_SDA)	//����ϴε͵�ƽ�Ƿ����
		while(!DHT11_DQ_IN)
		{
		  if(++cnt >= 250)
		   {
			  break;
		   }
		}
		//��ʱMin=26uS Max50uS �������ݡ�0���ĸߵ�ƽ
		//Delay_N10us(2);	 //��ʱ30uS
		delay_us(30);
			
		//�жϴ�������������λ
		tmp =0;
		//if(Sensor_SDA)	
		if(DHT11_DQ_IN)
		{
		  tmp = 1;
		}  
		cnt =0;
		//while(Sensor_SDA)		//�ȵ��ߵ�ƽ ����
		while(DHT11_DQ_IN)
		{
			if(++cnt >= 200)
			{
			  break;
			}
		}
		buffer <<=1;
		buffer |= tmp;	
	}
	return buffer;
}

/********************************************\
|* ���ܣ���������           	        *|
\********************************************/
unsigned char Read_Sensor(void)
{
	unsigned char i;
	//��������(Min=800US Max=20Ms) 
	//Sensor_SDA = 0;
	DHT11_IO_OUT();
	DHT11_DQ_OUT=0;
	//Delay_N1ms(2);  //��ʱ2Ms
	delay_ms(2);
	
	//�ͷ����� ��ʱ(Min=30us Max=50us)
	//Sensor_SDA = 1; 	
	DHT11_DQ_OUT =1;
	//Delay_N10us(1);//��ʱ30us
	delay_us(30);
	//������Ϊ���� �жϴ�������Ӧ�ź�
	//Sensor_SDA = 1; 
	DHT11_DQ_OUT =1;  
	Sensor_AnswerFlag = 0;  // ��������Ӧ��־
	DHT11_IO_IN();
	//�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������  
	//if(Sensor_SDA ==0)
	if(DHT11_DQ_IN ==0)
	{
		Sensor_AnswerFlag = 1;//������Ӧ�ź�
		Sys_CNT = 0;
		//�жϴӻ��Ƿ񷢳�80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����
		//while((!Sensor_SDA))
		while(!DHT11_DQ_IN)
		{
			if(++Sys_CNT>300) //��ֹ������ѭ��
			{
				Sensor_ErrorFlag = 1;
				return 0;
			} 
		}
		Sys_CNT = 0;
		//�жϴӻ��Ƿ񷢳�80us�ĸߵ�ƽ���緢����������ݽ���״̬
		//while((Sensor_SDA))
		while(DHT11_DQ_IN)
		{
		   if(++Sys_CNT>300) //��ֹ������ѭ��
		   {
				Sensor_ErrorFlag = 1;
				return 0;
		   } 
		} 		 
		// ���ݽ��� ������������40λ����
		// ��5���ֽ� ��λ���� 5���ֽڷֱ�λʪ�ȸ�λ ʪ�ȵ�λ �¶ȸ�λ �¶ȵ�λ У���
		// У���Ϊ��ʪ�ȸ�λ+ʪ�ȵ�λ+�¶ȸ�λ+�¶ȵ�λ
		for(i=0;i<5;i++)
		{
			Sensor_Data[i] = Read_SensorData();
		}
	}
	else
	{
		Sensor_AnswerFlag = 0;	  // δ�յ���������Ӧ
	}
	return 1;
}    












