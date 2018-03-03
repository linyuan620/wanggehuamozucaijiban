#include "max31865.h"
#include "spi.h"

uint32_t TIMEOUT;                  //define SPI communication timeout 
uint8_t  Data_Buffer[8];           //define data storage
uint8_t MAX31865_Config;           //the value is MAX31865 configuration register
uint8_t MAX31855_Fault_Status;     //the value is Fault Status register 
uint8_t Operation_Fault;          //define SPI status, if =1 SPI error.
float AD_Value;                   //store the value of RTD MSB and RTD LSB register
uint8_t RTD_H,RTD_L;
float RTD_Resistor;            //RTD resistor value based on RTD_MSB and RTD_LSB register
float RTD_Temperature;         // Temperature value based on direct read out data
float Corrected_Temperature;   //Temperature after correction
//please define MAX31865 operation mode:
//Manual_Mode:  1-shot=1, inital conversion by wirte configuration register
//Auto_Mode:    MAX31865 converts automatically
//Fault_Manual_Detect: check MAX31865 Fault status manually
//Fault_Auto_Detect:   check MAX31865 Fault status automatically

//#define Manual_Mode ;     //

#define Auto_Mode ;     //目前代码只支持auto
#define Fault_Auto_Detect ;

void Inital_MCU(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOD, ENABLE );//PORTD时钟使能 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //CS3-->PD.12 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	 //根据参数初始化GPIOD.12
	GPIO_SetBits(GPIOD,GPIO_Pin_12);//输出1，关闭片选
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //DRDY3-->PD.13 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		 //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);	 //根据参数初始化GPIOD.13
		
	CS3_HIGH; //Set MAX31865_3 CS high.
	SPI2_Init();
	SPI2_SetSpeed(SPI_BaudRatePrescaler_2);//设置为18M时钟,高速模式
}

//Used to Read and Write MAX31865
//Register_Address: MAX31865 Register address, buff: stored the write data or read back data, nBytes: read or write Byte Number.
uint8_t SPI_Operation(uint8_t Register_Address,uint8_t *buff,uint8_t nBytes)
{  
	uint8_t  Address,i;
	Address=Register_Address;
	//Enable SPI
	CS3_LOW;  //Pull CS Low
	SPI_I2S_ReceiveData(SPI2);   
	TIMEOUT=Long_TIME_OUT;
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)  == RESET)
	{
		if((TIMEOUT--) == 0) return SPI_FAIL;   //over time: Fail
	}
	SPI_I2S_SendData(SPI2, Address); //send register address

	if((Address&0x80)==0x80)           //SPI Write operation
	{ 
		for(i=0;i<nBytes;i++)     
		{ 
			TIMEOUT=Long_TIME_OUT;
			while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)  == RESET)  //waiting for finish sending data
			{
				if((TIMEOUT--) == 0) return SPI_FAIL;
			}
			SPI_I2S_SendData(SPI2, buff[i]);// send data to MAX31865
			while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)  == RESET);
			SPI_I2S_ReceiveData(SPI2);   
		}
			
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)  == RESET)  //waiting for finish sending data
		{
			if((TIMEOUT--) == 0) return SPI_FAIL;
		}							
	}
	else
	{
		TIMEOUT=Long_TIME_OUT;
		while( SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)  == RESET)
		{
			if((TIMEOUT--) == 0) return SPI_FAIL;
		}
		while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)  == RESET);		 
		SPI_I2S_ReceiveData(SPI2); //read back data, this data is invalid
		for(i=0;i<nBytes;i++)
		{
			SPI_I2S_SendData(SPI2, 0xff); //Send this data only used to generate SPI CLK
			TIMEOUT=Long_TIME_OUT;
			while( SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)  == RESET)
			{
				if((TIMEOUT--) == 0) return SPI_FAIL;
			}						
			while( SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)  == RESET); //waiting for receive
				   
			buff[i]=SPI_I2S_ReceiveData(SPI2);                //readback data and stored in buff
		}		
	}	
	CS3_HIGH;                          //pull cs high
	return SPI_OK;				      //return status
}


void Inital_MAX31865(void)
{
	#ifdef Auto_Mode
	MAX31865_Config=0xD1;   //Auto Mode, 3-Wire, 50Hz
	Data_Buffer[0]=MAX31865_Config;
	if(SPI_Operation(0x80,Data_Buffer,1)==SPI_FAIL)
	{
		Operation_Fault=1;
		return;
	}

	#endif
	#ifdef Manual_Mode
	MAX31865_Config=0x91;   //Manual Mode, 3-Wire, 50Hz
	Data_Buffer[0]=MAX31865_Config;
	if(SPI_Operation(0x80,Data_Buffer,1)==SPI_FAIL)
	{
		Operation_Fault=1;
		return;
	}
	#endif
	Data_Buffer[0]=0xFF;
	Data_Buffer[1]=0xFF;    //High Fault Threshold ,this value can be changed as needed
	Data_Buffer[2]=0x00;
	Data_Buffer[3]=0x00;    //Low Fault Threshold , this value can be changed as needed
	if(SPI_Operation(0x83,Data_Buffer,4)==SPI_FAIL)
	{
		Operation_Fault=1;
		return;
	}	 	
}

void Fault_Detect(void)
{
	#ifdef Fault_Auto_Detect
	Data_Buffer[0]=0x84 ;         
	if(SPI_Operation(0x80,Data_Buffer,1)==SPI_FAIL)    // write 0x86 to configuration register
	{
		Operation_Fault=1;
		return;
	}
	//delay_ms(1);   //delay 1ms
  	while((Data_Buffer[0]&0x0C)!=0x00)              //wait for  to finish fault detection
	{
		if(SPI_Operation(0x00,Data_Buffer,1)==SPI_FAIL)
		{
			Operation_Fault=1;
			return;
		}
	}
	if(SPI_Operation(0x07,Data_Buffer,1)==SPI_FAIL)    //read back Fault Status register
	{
		Operation_Fault=1;
		return;
	}
	MAX31855_Fault_Status=Data_Buffer[0];	
	Data_Buffer[0]=MAX31865_Config|0x02;
	if(SPI_Operation(0x80,Data_Buffer,1)==SPI_FAIL)     //write back configuration register
	{
		Operation_Fault=1;
		return;
	}			
	#endif
	#ifdef Fault_Manual_Detect
	Data_Buffer[0]=0x88;
	if(SPI_Operation(0x00,Data_Buffer,1)==SPI_FAIL)    //write 0x88 to configuration register
	{
		Operation_Fault=1;
		return;
	}
	delay_ms(1);                                     //wait for 1ms
	Data_Buffer[0]=0x8c;
	if(SPI_Operation(0x00,Data_Buffer,1)==SPI_FAIL)   //write 0x8C to configuration register
	{
		Operation_Fault=1;
		return;
	}
	while((Data_Buffer[0]&0x0C)!=0x00)                 //wait for to finish Fault detection
	{
		if(SPI_Operation(0x00,Data_Buffer,1)==SPI_FAIL)
		{
			Operation_Fault=1;
			return;
		}
	}	
	if(SPI_Operation(0x07,Data_Buffer,1)==SPI_FAIL)      //read back Fault status
	{
		Operation_Fault=1;
		return;
	}
	MAX31855_Fault_Status=Data_Buffer[0];	
	Data_Buffer[0]=MAX31865_Config|0x02;                      //write back configuration register
	if(SPI_Operation(0x80,Data_Buffer,1)==SPI_FAIL)
	{
		Operation_Fault=1;
		return;
	}							 			
	#endif
}


//Get MAX31865_3 /DRDY status
uint8_t DRDY3_Status(void)
{  
	return GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13);
}









