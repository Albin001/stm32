#include "stm32f10x.h"
void systick_init(void);
void gpio_init(void);

int i;
int main(void)
{
	__disable_irq();
	gpio_init();
	systick_init();
	__enable_irq();
	while(1)
	{
	
	}
}
void systick_init(void)
{
	//SysTick->LOAD = 72000 -1;
	
	SysTick->VAL  = 0; // To Clear the Current value;

	SysTick->LOAD = 16000000 -1;

	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE  | SysTick_CTRL_ENABLE;
	
	SysTick->CTRL |= SysTick_CTRL_TICKINT;
	
}

void gpio_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	
	GPIOC->CRH |= GPIO_CRH_MODE13_1 ;
	
	GPIOC->CRH &= ~(GPIO_CRH_CNF13_0  |  GPIO_CRH_CNF13_1 | GPIO_CRH_MODE13_0);
}
void SysTick_Handler(void)
{
		GPIOC->ODR ^= GPIO_ODR_ODR13;
}