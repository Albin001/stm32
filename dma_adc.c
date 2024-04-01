/*RS  = A8
    E= A10
		
		DB4-DB7 = A4-A7
		*/
#include "stm32f10x.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define NO_CHANNEL 2
void lcd_init(void);
void lcd_data(unsigned char dat);
void lcd_cmd(unsigned char cmd);
void lcd_str(char *a1);
void running(char a1[]);
void delay(unsigned int count);
void gpio_init(void);
void adc_init(void);
uint32_t val;

uint16_t adc_raw[NO_CHANNEL] = {0,0};
char buffer[35];
char buffer1[35];

int d1,i;
int main(void)
{
	gpio_init();
	lcd_init();
	adc_init();
	while(1)
	{
		lcd_cmd(0x81);
		//lcd_str("WELCOME");
		//delay(2000);
	  //lcd_cmd(0x01);
	  //lcd_str("EMBEDDED");
		//delay(2000);
	  //lcd_cmd(0x01);
		sprintf(buffer,"%d",adc_raw[0]);
			running(buffer);
		lcd_cmd(0xC0);
		sprintf(buffer1,"%d",adc_raw[1]);
			running(buffer1);
		delay(2000);
		lcd_cmd(0x01);
	}
	
}
void delay(unsigned int count)
{
	unsigned int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<count;j++);
	
}
void gpio_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN  | RCC_APB2ENR_AFIOEN;
	RCC->AHBENR |= RCC_AHBENR_DMA1EN; // To Enable the DMA 1
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	
  GPIOA->CRH |= ((1<<1) | (1<<9));
	GPIOA->CRH &= ~((1<<0) | (1<<2) | (1<<3) | (1<<8) | (1<<10) | (1<<11));
	GPIOA->CRL |= ((1<<17) | (1<<21) | (1<<25) | (1<<29));
	GPIOA->CRL &= ~((1<<16) | (1<<18) | (1<<19) | (1<<20) | (1<<22) | (1<<23) | (1<<24) | (1<<26) | (1<<27) | (1<<28) | (1<<30) | (1<<31) );

  GPIOA->CRL |= GPIO_CRL_CNF1_1;
	GPIOA->CRL &= ~(GPIO_CRL_CNF1_0);
	
	GPIOA->CRL |= GPIO_CRL_CNF0_1;
	GPIOA->CRL &= ~(GPIO_CRL_CNF0_0);
	
}
void lcd_cmd(unsigned char cmd)
{
	GPIOA->ODR &= ~((1<<8));  // rs=0
	delay(100);
  GPIOA->ODR |= ((1<<10)); // e=1
	delay(50);
	GPIOA->ODR &= 0xff0f;
	GPIOA->ODR |= (cmd & 0x00f0);
	delay(50);
	GPIOA->ODR &= ~((1<<10)); // e=0
	
	delay(150);
	
	GPIOA->ODR |= ((1<<10)); // e=1
	delay(50);
	GPIOA->ODR &= 0xff0f;
	GPIOA->ODR |= ((cmd<<4) & 0x00f0);
	delay(50);
	GPIOA->ODR &= ~((1<<10)); // e=0
}
void lcd_data(unsigned char dat)
{
	GPIOA->ODR |= ((1<<8));  // rs=1
	delay(100);
	GPIOA->ODR |= ((1<<10)); // e=1
	delay(50);
	GPIOA->ODR &= 0xff0f;
	GPIOA->ODR |= (dat & 0x00f0);
	delay(50);
	GPIOA->ODR &= ~((1<<10)); // e=0
	
	delay(150);
	
	GPIOA->ODR |= ((1<<10)); // e=1
	delay(50);
	GPIOA->ODR &= 0xff0f;
	GPIOA->ODR |= ((dat<<4) & 0x00f0);
	delay(50);
	GPIOA->ODR &= ~((1<<10)); // e=0
	
}
void lcd_init(void)
{
	delay(20);		/* LCD Power ON Initialization time >15ms */
	lcd_cmd(0x02);	/* 4bit mode */
	lcd_cmd(0x28);	/* Initialization of 16X2 LCD in 4bit mode */
	lcd_cmd(0x0C);	/* Display ON Cursor OFF */
	lcd_cmd(0x06);	/* Auto Increment cursor */
	lcd_cmd(0x01);	/* clear display */
	lcd_cmd(0x80);	/* cursor at home position */
}
void lcd_str(char *a1)
{
	while(*a1)
	{
		lcd_data(*a1);
		a1++;
	}
}
void adc_init(void)
{
	//ADC1->CR1 |= ADC_CR1_EOCIE;
	//NVIC_EnableIRQ(ADC1_2_IRQn);
	ADC1->SMPR2 |= ADC_SMPR2_SMP0_0 | ADC_SMPR2_SMP0_1 | ADC_SMPR2_SMP0_2; //  Configuration of Channel 0
	
	ADC1->SMPR2 |= ADC_SMPR2_SMP1_0 | ADC_SMPR2_SMP1_1 | ADC_SMPR2_SMP1_2;  // Configuration of Channel 1
	
	ADC1->SQR1 |= (ADC_SQR1_L_0); // Setting of Sequence Length
	
	ADC1->SQR1 &= ~(ADC_SQR1_L_1 | ADC_SQR1_L_2 | ADC_SQR1_L_3); // Setting of Sequence Length
	
	ADC1->SQR3 &= ~(ADC_SQR3_SQ1_0 | ADC_SQR3_SQ1_1 | ADC_SQR3_SQ1_2 | ADC_SQR3_SQ1_3 | ADC_SQR3_SQ1_4 );  // Setting of ADC Channel 0
	
	ADC1->SQR3 |= (ADC_SQR3_SQ2_0);  // Configuration of  ADC Channel 1
	
	ADC1->SQR3 &= ~(ADC_SQR3_SQ2_1 | ADC_SQR3_SQ2_2 | ADC_SQR3_SQ2_3 | ADC_SQR3_SQ2_4); // Configuration of ADC Channel 1
	
	ADC1->CR1 |= ADC_CR1_SCAN; // Enabling of Scan Mode
	
	ADC1->CR2 |= ADC_CR2_DMA ; // Enabling of Continuos Mode and DMA Mode
	
	/* ...............DMA CONFIGURATION ..................................*/
	
	DMA1_Channel1->CPAR = (uint32_t)(&(ADC1->DR)); // Passing Adress OF ADC Peripheral to Peripheral of dma register
	
	DMA1_Channel1->CMAR = (uint32_t)adc_raw;
	
	DMA1_Channel1->CNDTR = 2;
	
	DMA1_Channel1->CCR |= DMA_CCR1_MINC | DMA_CCR1_MINC | DMA_CCR1_MSIZE_0 | DMA_CCR1_PSIZE_0 | DMA_CCR1_CIRC;
	
	DMA1_Channel1->CCR |= DMA_CCR1_EN;

	ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_CONT;
	delay(5);
	ADC1->CR2 |= ADC_CR2_ADON;
	delay(5);
	ADC1->CR2 |= ADC_CR2_CAL;
	delay(6);
}
void running(char a1[])
{
	d1 = strlen(a1);
	for(i=0;i<d1;i++)
	{
		lcd_data(a1[i]);
	}
}