#ifndef __AWA5636_H
#define __AWA5636_H
#include "sys.h"
extern u16 noise;
void uart4_init(u32 bound);
void uart5_init(u32 bound);
u16 Read_Noise(void);
 
 
#endif
