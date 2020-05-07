#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32l1xx.h"
#include "system_stm32l1xx.h"

void DelayInit(void);
void DelayUs(uint32_t us);
void _DelayMs(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif
