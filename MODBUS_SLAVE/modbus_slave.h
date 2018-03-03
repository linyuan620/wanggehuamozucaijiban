#ifndef _MODBUS_SLAVE_H
#define _MODBUS_SLAVE_H

#include "sys.h"	
void Timer7_Init(void);
void Modbus_03_Solve(void);
void Modbus_04_Solve(void);
void Modbus_06_Solve(void);
void Modbus_16_Solve(void);

void RS485_Initt(u32 bound);

void RS485_Service(void);

#endif
