#include "stm32f10x.h"
void pwm_init(void);
void gpio_init(void);
void delay(int count);
int main(void)
{
	pwm_init();
	while(1)
	{
		
		
		
			TIM2->CCR1 = 100;
		
		delay(1000);
			
			TIM2->CCR1 = 200;
		delay(1000);
		
			TIM2->CCR1 = 800;
		delay(1000);
	}
}
void gpio_init(void)
{
RCC->APB2ENR |=((1<<2));
GPIOA->CRL |=((1<<3) | (1<<1));
GPIOA->CRL &=~((1<<2) | (1<<0));
}
void pwm_init(void)
{
	TIM2->CR1 &=~((1<<0));
	TIM2->SR &=~((1<<0));
	gpio_init();
	RCC->APB1ENR |=((1<<0));
	TIM2->CCMR1 |=((1<<3));
	TIM2->CR1 |=((1<<7));
	TIM2->CCMR1 &=~((1<<1) | (1<<0));
	TIM2->CCER |=((1<<0));
	TIM2->CR1 |=((1<<1));
	TIM2->PSC = 72;
	TIM2->ARR = 1000;
	//TIM2->CCR1 = 40;
	TIM2->CR1 &=~((1<<1));
	TIM2->EGR |=((1<<0));
	TIM2->SR &=~(TIM_SR_UIF);
	TIM2->CCMR1 |=((1<<6) | (1<<5));
	TIM2->CCMR1 &=~((1<<4));
	TIM2->CCER &=~((1<<1));
	TIM2->CR1 |=((1<<0));
	
}
void delay(int count)
{
	int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<count;j++);
}