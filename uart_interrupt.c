#include "stm32f10x.h"
void gpio_init(void);
void uart_init(void);
void delay(int count);
int i,j;
char chat  = 'A';
char recive;
int8_t flag =0;
int8_t flag1 = 0;
int main(void)
{
	gpio_init();
	uart_init();
	while(1)
	{
		

		if(flag == 1)
		{
			
		GPIOC->ODR |= ((1<<13));
		delay(1000);
		GPIOC->ODR &= ~((1<<13));
		delay(1000);
		USART2->DR = '1';
		while((USART2->SR & (0x80)) == 0x00);
		delay(500);
		}
		if(flag == 0)
		{
		GPIOC->ODR &= ~((1<<13));
			USART2->DR = '0';
		while((USART2->SR & (0x80)) == 0x00);
		delay(500);
		}
	}
		
}
void gpio_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN  |  RCC_APB2ENR_IOPAEN |  RCC_APB2ENR_IOPCEN;  //   Enabling  of Alternate Function
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;  //  Enabling  of uart2
	GPIOA->CRL  |=   ((1<<11) | (1<<9) | (1<<8)  | (1<<15));
	GPIOA->CRL  &=  ~((1<<10));
	GPIOA->CRL &=  ~((1<<13) | (1<<12) | (1<<14));
	
	/*......Configuration of pin C13 as output  .....................*/
	
	GPIOC->CRH &=  ~((1<<23) | (1<<22)  | (1<<20));
	GPIOC->CRH |= ((1<<21));
}
void uart_init(void)
{
	//__disable_irq();
	USART2->BRR = 0xEA6;  //  Setting Baud rate
	USART2->CR1 |=  (USART_CR1_UE | USART_CR1_TE  | USART_CR1_RE); //  Enabling  the  UART , Transmisson , Receptiion
	
	USART2->CR1 |= USART_CR1_RXNEIE ;  // Enabling  Of    Interrupt during Receiving and  Transmission
	
	NVIC_EnableIRQ(USART2_IRQn);//  Enabling  of Interrupt
	__enable_irq();
}
void delay(int count)
{
	for(i=0;i<count;i++)
	for(j=0;j<count;j++);
}
void USART2_IRQHandler(void)
{
	if(USART2->SR & USART_SR_RXNE)
	{
		recive = USART2->DR;
		if(recive == 'a')
		{
			flag = 1;
		}
		if(recive == 'b')
		{
			flag = 0;
		}
	}
}