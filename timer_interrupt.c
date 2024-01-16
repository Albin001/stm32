#include "stm32f10x.h"
void gpio_init(void);
void tim_init(void);
int main(void)
{
	gpio_init();
	tim_init();
	while(1)
	{
		GPIOC->ODR |= GPIO_ODR_ODR14;
	}
}
void gpio_init(void)
{
	
	   RCC->APB2ENR |= RCC_APB2ENR_IOPCEN ;  //  Enabling the GPIO port C
	
	   RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;  //  Enabling of Timer2 Module
	
		GPIOC->CRH |= GPIO_CRH_MODE13_1; //  Configuration of Port C13
	   
	  GPIOC->CRH &= ~(GPIO_CRH_MODE13_0 | GPIO_CRH_CNF13_1 | GPIO_CRH_CNF13_0); // Configuration of Port c
	 
	  GPIOC->CRH |= GPIO_CRH_MODE14_1; //  Configuration of Port C13
	   
	  GPIOC->CRH &= ~(GPIO_CRH_MODE14_0 | GPIO_CRH_CNF14_1 | GPIO_CRH_CNF14_0); // Configuration of Port c
}
void tim_init(void)
{
	__disable_irq();
	
	 TIM2->PSC = 65536-1; // Assigning of Prescaler value
	
	 TIM2->ARR= 60000;  //  Maximum Count Value
	
	 TIM2->DIER |= TIM_DIER_UIE; //Enabling of Update Interrupt
	
	 TIM2->CR1 |= TIM_CR1_CEN; //  Enabling of  Counter
	
	  NVIC_EnableIRQ(TIM2_IRQn); //  Enabling   of TIM2 interrupt to NVIC
	
	__enable_irq(); // Enabing Of Global Interrupt
	
} 
void TIM2_IRQHandler(void)
{
	TIM2->SR  = 0;
	
	GPIOC->ODR^= GPIO_ODR_ODR13;
	
	GPIOC->ODR &= ~(GPIO_ODR_ODR14);
}