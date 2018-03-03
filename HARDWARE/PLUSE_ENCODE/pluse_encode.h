#ifndef __PLUSE_ENCODE_H
#define __PLUSE_ENCODE_H
#include "sys.h"

#define ENCODE_COUNT 2

typedef struct{
	u16 encoderNum;
	//uint8_t encoderDir;
}ENCODE_T;

extern ENCODE_T g_tEncode[ENCODE_COUNT];

void PLUSE_Encode_init(void);

void UpdatePluseEncode(void);
 
#endif
