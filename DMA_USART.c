#include "stm32f10x.h"
#include "string.h"
void gpio_init(void);
void uart_init(void);
void delay(int count);
void DMA_init(void);
int i,j;
char chat[ ] = "HELLO WORLD\n";
	unsigned int len ;
int main(void)
{
	gpio_init();
	len = strlen(chat);
	 DMA_init();
	uart_init();
	while(1)
	{
	
    DMA1_Channel7->CCR |= DMA_CCR7_EN;  // Enabling of DMA1 
		
    while((DMA1->ISR &	DMA_ISR_TCIF7) == 0);  // Checking Whether Transmission Is Complete or Not
		
    DMA1->IFCR |=  DMA_IFCR_CTCIF7; // Clearing the Flag Bit
		 
	DMA1_Channel7->CCR &= ~DMA_CCR7_EN;
		
	delay(2000);
		
	
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
	
}
void DMA_init(void)
{
	
	RCC->AHBENR |= RCC_AHBENR_DMA1EN; // Enabling of  DMA1
	
	USART2->CR3 |= USART_CR3_DMAT;  // Enabling of DMA Mode For Transmission
	
	DMA1_Channel7->CNDTR = len;
	
	DMA1_Channel7->CCR |=  DMA_CCR7_MINC | DMA_CCR7_DIR |  DMA_CCR7_TCIE  | DMA_CCR7_CIRC;  // DMA Control Settings
	
	DMA1_Channel7->CPAR = (uint32_t)&USART2->DR;  // Pheripheral Adress  of  USART
	
	DMA1_Channel7->CMAR = (uint32_t)chat;  // Memory Adress of Array
	
	
}
void delay(int count)
{
	for(i=0;i<count;i++)
	for(j=0;j<count;j++);
}
