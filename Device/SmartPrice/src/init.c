#include "init.h"
void Init_GPIO(void);
void Init_Timing(void);
void Init_SPI(void);

void Init_SPI()
{
	SPI_InitTypeDef spi;
	SPI_StructInit(&spi);
	spi.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spi.SPI_Mode = SPI_Mode_Master;
	spi.SPI_DataSize = SPI_DataSize_8b;
	spi.SPI_CPOL = SPI_CPOL_Low;
	spi.SPI_CPHA = SPI_CPHA_1Edge;
	spi.SPI_NSS =  SPI_NSS_Soft  ;
	spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	spi.SPI_FirstBit = SPI_FirstBit_MSB;
	spi.SPI_CRCPolynomial = 10;

	SPI_Init(Init_DefaultSPI, &spi);


}


void Init_Timing()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
}


void Init_GPIO()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = Init_GPIO_Speed;

	GPIO_InitStructure.GPIO_Pin  = EINC_Pin_SDI  ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;

	GPIO_Init(EINC_Base_SDI, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin  = EINC_Pin_SCK ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;

	GPIO_Init(EINC_Base_SCK, &GPIO_InitStructure);

	GPIO_PinAFConfig(EINC_Base_SDI, EINC_PinSource_SDI,  GPIO_AF_SPI3) ;
	GPIO_PinAFConfig(EINC_Base_SCK, EINC_PinSource_SCK, GPIO_AF_SPI3) ;
	//GPIO_PinAFConfig(EINC_Base_CS, EINC_PinSource_CS, GPIO_AF_SPI2) ;

	GPIO_InitStructure.GPIO_Pin  =  EINC_Pin_DC;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(EINC_Base_DC, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin  = EINC_Pin_RES;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(EINC_Base_RES, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin  = EINC_Pin_CS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(EINC_Base_CS, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin  = EINC_Pin_BUSY;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(EINC_Base_BUSY, &GPIO_InitStructure);


	GPIO_ResetBits(EINC_Base_CS, EINC_Pin_CS);
}




void Init_All()
{

	 __enable_irq();
	 Init_Timing();
	 Init_GPIO();
	 Init_SPI();
	 //DelayInit();
	 SPI_Cmd(Init_DefaultSPI, ENABLE);
	 uint16_t tmp = Init_DefaultSPI->SR;
	if (tmp & 16 )
	 		;
}

