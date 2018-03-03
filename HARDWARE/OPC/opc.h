#ifndef __OPC_H
#define __OPC_H			    
#include "sys.h" 
 
#define	SPI_Opc_CS PBout(12)  //Ñ¡ÖÐFLASH	
				 
////////////////////////////////////////////////////////////////////////////


void SPI_Opc_Init(void);

u8 SPI_Opc_ReadSR(void);
u8 SPI_Opc_CloseFan(void);
u8 SPI_Opc_OpenFan(void);

void SPI_Opc_ReadPM(void);
void SPI_Opc_ReadInfo(void);

#endif
















