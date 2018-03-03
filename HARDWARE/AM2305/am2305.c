#include "am2305.h"
#include "delay.h"

unsigned char Sensor_Data[5]={0x00,0x00,0x00,0x00,0x00};
unsigned char Sensor_Check;		  //检验和

unsigned char Sensor_AnswerFlag;  //收到起始标志位
unsigned char Sensor_ErrorFlag;   //读取传感器错误标志
unsigned int  Sys_CNT;
unsigned int  Tmp;

unsigned int  OutdoorHumidity;
unsigned int  OutdoorTemperature; 
 	 
void AM2305_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //使能PE端口时钟
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //PE13端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);				 //初始化IO口
 	GPIO_SetBits(GPIOE,GPIO_Pin_13);						 //PE13 输出高
} 


 
void Clear_Data (void)
{
	int i;
	for(i=0;i<5;i++)
	{
		Sensor_Data[i] = 0x00;
	}//接收数据清零
}


/********************************************\
|* 功能：读取传感器发送的单个数据 *|
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
		//while(!Sensor_SDA)	//检测上次低电平是否结束
		while(!DHT11_DQ_IN)
		{
		  if(++cnt >= 250)
		   {
			  break;
		   }
		}
		//延时Min=26uS Max50uS 跳过数据“0”的高电平
		//Delay_N10us(2);	 //延时30uS
		delay_us(30);
			
		//判断传感器发送数据位
		tmp =0;
		//if(Sensor_SDA)	
		if(DHT11_DQ_IN)
		{
		  tmp = 1;
		}  
		cnt =0;
		//while(Sensor_SDA)		//等到高电平 结束
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
|* 功能：读传感器           	        *|
\********************************************/
unsigned char Read_Sensor(void)
{
	unsigned char i;
	//主机拉低(Min=800US Max=20Ms) 
	//Sensor_SDA = 0;
	DHT11_IO_OUT();
	DHT11_DQ_OUT=0;
	//Delay_N1ms(2);  //延时2Ms
	delay_ms(2);
	
	//释放总线 延时(Min=30us Max=50us)
	//Sensor_SDA = 1; 	
	DHT11_DQ_OUT =1;
	//Delay_N10us(1);//延时30us
	delay_us(30);
	//主机设为输入 判断传感器响应信号
	//Sensor_SDA = 1; 
	DHT11_DQ_OUT =1;  
	Sensor_AnswerFlag = 0;  // 传感器响应标志
	DHT11_IO_IN();
	//判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行  
	//if(Sensor_SDA ==0)
	if(DHT11_DQ_IN ==0)
	{
		Sensor_AnswerFlag = 1;//收起响应信号
		Sys_CNT = 0;
		//判断从机是否发出80us 的低电平响应信号是否结束
		//while((!Sensor_SDA))
		while(!DHT11_DQ_IN)
		{
			if(++Sys_CNT>300) //防止进入死循环
			{
				Sensor_ErrorFlag = 1;
				return 0;
			} 
		}
		Sys_CNT = 0;
		//判断从机是否发出80us的高点平，如发出则进入数据接收状态
		//while((Sensor_SDA))
		while(DHT11_DQ_IN)
		{
		   if(++Sys_CNT>300) //防止进入死循环
		   {
				Sensor_ErrorFlag = 1;
				return 0;
		   } 
		} 		 
		// 数据接收 传感器共发送40位数据
		// 即5个字节 高位先送 5个字节分别位湿度高位 湿度低位 温度高位 温度低位 校验和
		// 校验和为：湿度高位+湿度低位+温度高位+温度低位
		for(i=0;i<5;i++)
		{
			Sensor_Data[i] = Read_SensorData();
		}
	}
	else
	{
		Sensor_AnswerFlag = 0;	  // 未收到传感器响应
	}
	return 1;
}    












