#ifndef _KEYPAD_H
#define _KEYPAD_H

#include "types.h"

void Keypad_Init(void);
u32 ColScan(void);
u32 RowCheck(void);
u32 ColCheck(void);
u32 KeyDetect(void);
s32 ReadNum(void);
s32 PSReadNum(void);

#endif
