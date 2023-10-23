#include "stm32f10x.h"
void gpio_init(void);
void uart_init(void);
void delay(int count);
int i,j;
char chat  = 'A';
char chat1 = 'B';
int main(void)
{
	gpio_init();
	uart_init();
	while(1)
	{
		while((USART2->SR & (0x80)) == 0x00);
		USART2->DR = chat;
		delay(500);
	while((USART2->SR & (0x80)) == 0x00);
		USART2->DR = chat1;
		delay(500);
	}
}
void gpio_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN  |  RCC_APB2ENR_IOPAEN;  //   Enabling  of Alternate Function

	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;  //  Enabling  of uart2
	
	GPIOA->CRL  |=   ((1<<11) | (1<<9) | (1<<8)  | (1<<15));
	
	GPIOA->CRL  &=  ~((1<<10));
	
	GPIOA->CRL &=  ~((1<<13) | (1<<12) | (1<<14));
	
	//GPIOA->ODR |= ((1<<3));
	
}
void uart_init(void)
{
	USART2->BRR = 0xEA6;  //  Setting Baud rate
	
	USART2->CR1 |=  ((1<<13));   // Enabling  of  UART
	
	USART2->CR1 |=  ((1<<3));  //  Enabling  of Transmitter  
	
	USART2->CR1 |=  ((1<<2)); // Enabling   of Reciever	
}
void delay(int count)
{
	for(i=0;i<count;i++)
	for(j=0;j<count;j++);
}