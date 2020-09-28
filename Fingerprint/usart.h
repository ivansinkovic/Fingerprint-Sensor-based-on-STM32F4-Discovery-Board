/* usart.h */ 
#ifndef USART_H 
#define USART_H 

#define printf_uart(format,...) \
do {\
		char buffer[30];\
    sprintf(buffer, format, ##__VA_ARGS__ ); \
    USART1_puts(buffer); \
} while(0)
 
#include <stm32f4xx.h>    // common stuff 
#include <stm32f4xx_rcc.h>   // reset anc clocking 
#include <stm32f4xx_gpio.h>   // gpio control 
#include <stm32f4xx_usart.h>   // USART 
 
#define BUFSIZE  8 
#define BAUDRATE 115200 
 
void USART1_Init(void);   // init USART1 peripheral 
void USART1_SendChar(char c);   // blocking send character 
int  USART1_Dequeue(char* c);   // pop character from receive FIFO 
void USART1_puts(char *buffer);
int sprintf(char *str, const char *format, ...);
#endif 
