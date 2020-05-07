

#include "epdif.h"



void DigitalWrite(GPIO_TypeDef * base, uint16_t pin, BitAction value) {
    GPIO_WriteBit(base, pin, value);
}

uint8_t DigitalRead(GPIO_TypeDef * base, uint16_t pin) {
    return GPIO_ReadInputDataBit(base, pin);
}

void DelayMs(uint32_t delaytime) {
	_DelayMs(delaytime);
}

void SpiTransfer(SPI_TypeDef *SPIx, uint16_t data) {
	GPIO_WriteBit(EINC_Base_CS, EINC_Pin_CS, Bit_SET);
	GPIO_WriteBit(EINC_Base_CS, EINC_Pin_CS, Bit_RESET);
	DelayMs(10);
	SPI_I2S_SendData(SPIx, data);
	DelayMs(10);
	GPIO_WriteBit(EINC_Base_CS, EINC_Pin_CS, Bit_SET);
	while(SPIx->SR & SPI_SR_BSY);
}


