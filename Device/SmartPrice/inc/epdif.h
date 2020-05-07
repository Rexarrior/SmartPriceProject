

#ifndef EPDIF_H
#define EPDIF_H
#include "stdlib.h"
#include "stm32l1xx.h"

#include "delay.h"
#include "PinMap.h"


// Pin definition
#define RST_PIN         EINC_Pin_RES
#define DC_PIN          EINC_Pin_DC
#define CS_PIN          EINC_Pin_CS
#define BUSY_PIN        EINC_Pin_BUSY

// Pin level definition
#define LOW             0
#define HIGH            1


void DigitalWrite(GPIO_TypeDef * base, uint16_t pin, BitAction value);
uint8_t DigitalRead(GPIO_TypeDef * base, uint16_t pin);
void DelayMs(uint32_t delaytime);
void SpiTransfer(SPI_TypeDef *SPIx, uint16_t data);

#endif
