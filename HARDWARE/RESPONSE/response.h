#ifndef __RESPONSE_H
#define __RESPONSE_H
#include "sys.h"
  
#define START 0XEF
#define STOP 0XEF
#define ESC 0XEC
#define FPGA_RESET 0XE9
#define ACK 0XE8
#define ENDFRAME 0XE7
#define ADCCTRLS 0XDF
#define ADCCTRLM 0XDE
#define ADCCTRLC 0XDD
#define DACCTRLS 0XDC
#define DACCTRLM 0XDB
#define DACCTRLC 0XDA
#define ADDACTRL 0XD9
#define TTLCTRLI 0XD8
#define TTLCTRLO 0XD7
#define SPICTRLI 0XD6
#define SPICTRLO 0XD5
#define ADBUFFCTRL 0XD3
#define ADBUFFREAD 0XD2
#define ADBUFFRLS  0XD1
#define USERBUFF   0XD0
#define USERWRITE  0XCF
#define USERREAD   0XCE
#define USEINTEST  0XCD
#define ADDASELFTEST  0XCC
#define ADRANGESEL  0XCB
#define ROTARY  0XC8
#define MOCTRL  0XC9
#define BUSSEL  0XC4
#define CNT  0XC3

#define COUNT_START 0x53
#define COUNT_END   0x45
#define COUNT_READ   0xc2

#define ERR_OK 0X00
#define ERR1	0X01
#define ERR2	0X02
#define ERR3	0X03
#define ERR4	0X04
#define ERR5	0X05
#define ERR6	0X06
#define ERR7	0X07
#define ERR8	0X08
#define ERR9	0X09
#define ERR10	0X0A
#define ERR11	0X0B
#define ERR12	0X0C
#define ERR13	0X10


#define USB_STYLE	1
#define UART_STYLE	2

#define DIR_RIGHT	0X00
#define DIR_LEFT	0X80


extern unsigned char controlStep  ;
unsigned char CheackDat( unsigned char *dat);
unsigned char CheackDat2( unsigned char *dat);
void ACKpro(unsigned char  errorcode);
void PMS_IO_Init(void);

#endif
