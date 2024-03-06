//Where is the led connected
//Port:	A
//Pin : 5
//xác định địa chỉ cơ sở(base của ngoại vi )
#define PERIPH_BASE 			(0x40000000UL)// unsigned long
#define AHB1PERIPH_OFFSET 		(0x00020000UL)//0x4002 0000 - 0x4000 0000

#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET			(0x0000UL)
#define GPIOA_BASE				(AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)
#define AHB1EN_R_OFFSET			(0x30UL)
#define RCC_AHB1EN_R			(*(volatile unsigned int *)(AHB1EN_R_OFFSET + RCC_BASE))

#define MODE_R_OFFSET			(0x00UL)
#define GPIOA_MODE_R			(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))
#define OD_R_OFFSET				(0x14UL)
#define GPIOA_OD_R				(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define GPIOA_EN				(1U<<0)//Shift left 0
#define PIN5					(1U<<5)
#define LED_PIN					PIN5
/*
 * (1U<<10)//điều này có nghĩa là chúng ta đang set bit số 10 lên 1
 * &=~(1U<<11)//ta sẽ đảo lại để thực hiện việc dịch bit 0 đến vị trí 11*/

int main(void)
{
	/*1. Enable clock access to GPIOA*/
	/*"|" ex: rcc_ahb1en_r = 0b1001 0000 1111 0101 0000 0000 0000
	 * 		   GPIOA_EN		=0b0000 0000 0000 0000 0000 0000 0001
	 * 		   Nếu ko xài or thì có rcc sẽ bị mất dữ liệu của các bit còn lại thành 0									*/
	 RCC_AHB1EN_R |= GPIOA_EN;
	 /* 2. Set PA5 as output pin*/
	 GPIOA_MODE_R |= (1U<<10);//Set bit 10 to 1
	 GPIOA_MODE_R &= ~(1U<<11);// Set bit 11 to 0
	while(1)
	{
		/*3. Set PA5 high */
		//GPIOA_OD_R |= LED_PIN;//Set PA5 high
		/*Toggle PA5*/
		GPIOA_OD_R^=LED_PIN;//Toggle
		for(int i=0;i<100000;i++)
		{};
	}


}
