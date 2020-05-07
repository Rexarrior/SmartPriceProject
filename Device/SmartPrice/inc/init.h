#ifndef APP_INIT_FILE
#define APP_INIT_FILE
#include "stdlib.h"
#include "stm32l1xx.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_spi.h"
#include "PinMap.h"
#include "delay.h"


#define Init_GPIO_Speed GPIO_Speed_2MHz
#define Init_DefaultSPI SPI3
void Init_All(void);
#endif
