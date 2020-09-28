/* Includes ---------------------------------------------------*/
#include "stm32f4xx.h"
#include <stm32f4xx_spi.h>
/* Private function prototypes --------------------------------*/
void SPI_Config(void);
/* Private functions ------------------------------------------*/
/**
* @brief Main program
* @param None
* @retval None
*/

/**
* @brief Configures the SPI1 Peripheral.
* @param None
* @retval None
*/
void SPI_Config(void)
{
GPIO_InitTypeDef GPIO_InitStruct;
SPI_InitTypeDef SPI_InitStruct;

	
/* Enable the GPIOA clock */
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
GPIO_Init(GPIOA, &GPIO_InitStruct);
	
/* Connect PA5 to SPI1_SCK */
GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
/* Connect PA6 to SPI1_MISO */
GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
/* Connect PA7 to SPI1_MOSI */
GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

/* Configure SPI1 pins as alternate function (No need to

configure PA4 since NSS will be managed by software) */

//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;
GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOA, &GPIO_InitStruct);

/* SPI configuration *****************************************/

/* Enable the SPI clock */
SPI_DeInit(SPI1);

RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
SPI_InitStruct.SPI_Direction =
SPI_Direction_2Lines_FullDuplex;
SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
SPI_InitStruct.SPI_BaudRatePrescaler =
SPI_BaudRatePrescaler_32;
SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_LSB;
//SPI_InitStruct.SPI_CRCPolynomial = 0;

SPI_Init(SPI1, &SPI_InitStruct);
SPI_Cmd(SPI1, ENABLE);
}
