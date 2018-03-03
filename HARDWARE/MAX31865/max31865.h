#ifndef __MAX31865_H
#define __MAX31865_H
#include "sys.h"

//define interface of MAX31865_3
#define CS3_HIGH   (GPIO_SetBits(GPIOD,GPIO_Pin_12))       //define PD.12 as CS3 
#define CS3_LOW    (GPIO_ResetBits(GPIOD,GPIO_Pin_12))

#define Long_TIME_OUT  (uint32_t)0xFFFFFF;
#define SPI_FAIL       1
#define SPI_OK         0
#define Rref           400         //if using PT1000, change this from 400 to 4000

extern uint8_t  Data_Buffer[8];           //define data storage
extern uint8_t Operation_Fault;          //define SPI status, if =1 SPI error.
extern uint8_t RTD_H,RTD_L;
extern float AD_Value;                   //store the value of RTD MSB and RTD LSB register
extern float RTD_Resistor;            //RTD resistor value based on RTD_MSB and RTD_LSB register
extern float RTD_Temperature;         // Temperature value based on direct read out data
extern float Corrected_Temperature;   //Temperature after correction

void Inital_MCU(void);
uint8_t SPI_Operation(uint8_t Register_Address,uint8_t *buff,uint8_t nBytes);
void Inital_MAX31865(void);
void Fault_Detect(void);
uint8_t DRDY3_Status(void);
 
#endif

