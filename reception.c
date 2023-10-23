#include "stm32f10x.h"
void gpio_init(void);
void uart_init(void);
void delay(int count);
int i,j;
char chat  = 'A';
char recive;
int main(void)
{
	gpio_init();
	uart_init();
	while(1)
	{
		
		while((USART2->SR	  & 0x20) == 0x00);
		recive = USART2->DR;
		delay(100);
		//while((USART2->SR & (0x80)) == 0x00);

	//while((USART2->SR & (0x80)) == 0x00);
		USART2->DR = recive;
		while((USART2->SR & (0x80)) == 0x00);
		delay(500);
		USART2->DR = 'B';
		while((USART2->SR & (0x80)) == 0x00);
		delay(500);
		USART2->DR = 'C';
		while((USART2->SR & (0x80)) == 0x00);
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
}
void uart_init(void)
{
	USART2->BRR = 0xEA6;  //  Setting Baud rate
	USART2->CR1 |=  (USART_CR1_UE | USART_CR1_TE  | USART_CR1_RE); //  Enabling  the  UART , Transmisson , Receptiion
}
void delay(int count)
{
	for(i=0;i<count;i++)
	for(j=0;j<count;j++);
}