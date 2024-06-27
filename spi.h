#ifndef __SPI_H
#define __SPI_H
#include "stm32f10x.h"

#define MFRC522_CS_LOW					GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define MFRC522_CS_HIGH					GPIO_SetBits(GPIOB, GPIO_Pin_12)

void SPI_Config(void);
uint8_t SPI_Send(uint8_t data);
//uint8_t SPI_Receive1Byte(void);
#endif