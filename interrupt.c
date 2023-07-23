#include "stm32f10x.h"
/* .................. Setting  Pin A0  as Interrupt .......................*/
void gpio_init(void);
void delay(int count);
int main(void)
{
	gpio_init();
__disable_irq();
	AFIO->EXTICR[4] = 0000;
	EXTI->IMR |= ((1<<4));
	EXTI->FTSR |= ((1<<4));
	NVIC_EnableIRQ(EXTI4_IRQn);
	__enable_irq();
	while(1)
	{
	GPIOC->ODR  |= ((1<<14));
	delay(1000);
	GPIOC->ODR &= ~((1<<14));
	delay(1000);
	}
}
void gpio_init(void)
{
	RCC->APB2ENR |= ((1<<0) | (1<<2) | (1<<4));
	GPIOC->CRH |= ((1<<25));
	GPIOC->CRH &= ~((1<<24) | (1<<26) | (1<<27));
	GPIOA->CRL &= ~((1<<16) | (1<<18) | (1<<19));
	GPIOA->CRL |= ((1<<17));
	GPIOA->ODR |= ((1<<4));
	GPIOC->CRH |= ((1<<21));
	GPIOC->CRH &= ~((1<<20));
	GPIOC->CRH &= ~((1<<22) | (1<<23));

}
void delay(int count)
{
	int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<count;j++);
}
void EXTI4_IRQHandler( )
{
	EXTI->PR |= ((1<<0));
	//GPIOC->ODR &= ~((1<<14));
	GPIOC->ODR |= ((1<<13));
	delay(5000);
	GPIOC->ODR &= ~((1<<13));
}