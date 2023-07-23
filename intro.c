#include "stm32f10x.h"
void delay(int count);
int main(void)
{
	RCC->APB2ENR |=((1<<4)  | (1<<2));  //  Configured  the  Clock  Enable  For  PORT A  and PORT C
	GPIOC->CRH &= ~((1<<23) | (1<<22) | (1<<20) |  (1<<24) | (1<<26) |  (1<<27));
	GPIOC->CRH |=((1<<21) | (1<<25));
	GPIOA->CRH &= ~((1<<5) | (1<<4) | (1<<6));
	GPIOA->CRH |= ((1<<7));
	GPIOA->ODR |=((1<<9));
	
	while(1)
	{
		
		if(!(GPIOA->IDR &(1<<9)))
		{

		GPIOC->ODR |=((1<<13) | (1<<14));
		}
		else
		{
		GPIOC->ODR &=((0<<13) | (0<<14));
		}
	
}
	}
void delay(  int count)
{
	int i,j;
	for(i=0;i < count;i++)
	for(j=0;j<count;j++);
}
