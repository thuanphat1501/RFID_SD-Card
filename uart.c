#include "uart.h"
void UART_Config(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_InitTypeDef USARTInitStruct;
	USARTInitStruct.USART_BaudRate = 9600;
	USARTInitStruct.USART_WordLength = USART_WordLength_8b;
	USARTInitStruct.USART_StopBits = USART_StopBits_1;
	USARTInitStruct.USART_Parity = USART_Parity_No;
	USARTInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USARTInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USARTInitStruct);
	USART_Cmd(USART1,ENABLE);
}

void UART_Transmit(char *string)
{
  while(*string)
  {
    while(!(USART1->SR & USART_SR_TXE)); // Ch? cho d?n khi TXE (Transmit data register empty) tr? thành 1
    USART1->DR = (*string & 0xFF); // G?i m?t ký t?
    string++; // Chuy?n d?n ký t? ti?p theo
  }
}
void UART_SendChar(USART_TypeDef *USARTx, char data){
	USARTx->DR = 0x00;
	USART_SendData(USARTx, data);
	
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)==RESET);
}

void UART_SendString(USART_TypeDef *USARTx, char *str){
	while(*str)
		{
		UART_SendChar(USARTx, *str);
		str++;
		}
}
