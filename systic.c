#include "stm32f10x.h"
void systick_init(void);
void gpio_init(void);
void delay(int n);
int i;
int main(void)
{
	gpio_init();
	systick_init();
	while(1)
	{
		GPIOC->ODR |= GPIO_ODR_ODR13;
		delay(5000);
		GPIOC->ODR  &= ~(GPIO_ODR_ODR13);
		delay(5000);
	}
}
void systick_init(void)
{
	//SysTick->LOAD = 72000 -1;
	
	SysTick->VAL  = 0; // To Clear the Current value;

	SysTick->LOAD = 72000 -1;

	
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE  | SysTick_CTRL_ENABLE;
	
}
void delay(int n)
{
	for(i=0;i<n;i++)
	{
		while((SysTick->CTRL & (1<<16))== 0);
		 SysTick->CTRL &= ~((1<<16));
		 SysTick->LOAD = 72000 -1;
		
	}
}
void gpio_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	GPIOC->CRH |= GPIO_CRH_MODE13_1 ;
	
	GPIOC->CRH &= ~(GPIO_CRH_CNF13_0  |  GPIO_CRH_CNF13_1 | GPIO_CRH_MODE13_0);
}