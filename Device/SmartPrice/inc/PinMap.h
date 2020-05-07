#ifndef APP_PIN_MAP
#define APP_PIN_MAP
#include "stm32l1xx_gpio.h"

#define EINC_Base_SDI GPIOC
#define EINC_Pin_SDI GPIO_Pin_12
#define EINC_PinSource_SDI GPIO_PinSource12

#define EINC_Base_SCK GPIOB
#define EINC_Pin_SCK GPIO_Pin_3
#define EINC_PinSource_SCK GPIO_PinSource3

#define EINC_Base_CS GPIOA
#define EINC_Pin_CS GPIO_Pin_4
#define EINC_PinSource_CS GPIO_PinSource4

#define EINC_Base_DC GPIOB
#define EINC_Pin_DC GPIO_Pin_11
#define EINC_PinSource_DC GPIO_PinSource11

#define EINC_Base_RES GPIOB
#define EINC_Pin_RES GPIO_Pin_4
#define EINC_PinSource_RES GPIO_PinSource4

#define EINC_Base_BUSY GPIOB
#define EINC_Pin_BUSY GPIO_Pin_5
#define EINC_PinSource_BUSY GPIO_PinSource5

#endif
