/*RS  = A8
    E= A10
		
		DB4-DB7 = A4-A7
		*/
#include "stm32f10x.h"

void lcd_init(void);
void lcd_data(unsigned char dat);
void lcd_cmd(unsigned char cmd);
void lcd_str(char *a1);
void delay(unsigned int count);
void gpio_init(void);

int main(void)
{
	gpio_init();
	lcd_init();
	while(1)
	{
		lcd_cmd(0x81);
		lcd_str("WELCOME");
		delay(2000);
		lcd_cmd(0x01);
	  lcd_str("EMBEDDED");
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
	RCC->APB2ENR |= ((1<<2));
  GPIOA->CRH |= ((1<<1) | (1<<9));
	GPIOA->CRH &= ~((1<<0) | (1<<2) | (1<<3) | (1<<8) | (1<<10) | (1<<11));
	GPIOA->CRL |= ((1<<17) | (1<<21) | (1<<25) | (1<<29));
	GPIOA->CRL &= ~((1<<16) | (1<<18) | (1<<19) | (1<<20) | (1<<22) | (1<<23) | (1<<24) | (1<<26) | (1<<27) | (1<<28) | (1<<30) | (1<<31) );
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