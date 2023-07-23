#include "stm32f10x.h"
void timer_init(void);
void delay( int count);
void gpio_init(void);
int main(void)
{
	gpio_init();
	timer_init();
	while(1)
	{
		GPIOC->ODR |=((1<<14));
		delay(2000);
		GPIOC->ODR &=~((1<<14));
		delay(2000);
	}

}
void timer_init(void)
{
	RCC->APB1ENR |=((1<<0));
	TIM2->ARR = 1000;
	TIM2->PSC = 72-1;
	TIM2->CR1 |=((1<<0));
	while(!(TIM2->SR & (1<<0)));

}
void gpio_init(void)
{
		RCC->APB2ENR |=((1<<4));
	  GPIOC->CRH |=((1<<25));
	   GPIOC->CRH &=~((1<<24) | (1<<26) | (1<<27));
	
}
void delay( int count)
{
	int i;
	for(i=0;i<count;i++)
	{
		TIM2->CNT =0;
		while(TIM2->CNT < 1000);
	}
	
}