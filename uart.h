#ifndef __UART_H
#define __UART_H
#include "stm32f10x.h"
void UART_Config(void);
void UART_SendChar(USART_TypeDef *USARTx, char data);
void UART_SendString(USART_TypeDef *USARTx, char *str);
void UART_Transmit(char *string);
#endif