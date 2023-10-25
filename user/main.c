
/*====================================================================================
 * 								INCLUDE FILES
=================================================================================== */
#include <stdio.h>
#include <stdint.h>

/*====================================================================================
 * 								DEFINITIONS
====================================================================================*/
#define RCC_Address				0x40021000
#define PORTA_Address			0x40010800
#define PORTB_Address			0x40010C00
#define PORTC_Address			0x40011000
#define PORTD_Address			0x40011400
#define PORTE_Address			0x40011800
#define PORTF_Address			0x40011C00
#define PORTG_Address			0x40020000

/*====================================================================================
 * 								LOCAL FUNTION PROTOTYPES
====================================================================================*/
void Delay_ms(uint16_t time);
void GPIO_Configuration();

/*====================================================================================
 * 								LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
====================================================================================*/
/*create a struct for RRC register*/
struct My_RCC_Type
{
	uint32_t My_CTRL;		//Clock control register
	uint32_t My_CFG;		//Clock configuration register
	uint32_t My_CLKINT;		//Clock interrupt register
	uint32_t My_APB2RST;	//APB2 peripheral reset register
	uint32_t My_APB1RST;	//APB1 peripheral reset register
	uint32_t My_AHBEN;		//APB peripheral clock enable register
	uint32_t My_APB2EN;		//APB2 peripheral clock enable register
	uint32_t My_APB1EN;		//APB1 peripheral clock enable register
	uint32_t My_BPDC;		//Battery powered domain control register
	uint32_t My_CTRLSTS;	//Control/status register
	uint32_t My_AHBRST;		//AHB peripheral reset register
	uint32_t My_MISC1;		//Additional register1
	uint32_t My_MISC2;		//Additional register2
	uint32_t My_MISC3;		//Additional register3
	uint32_t My_INTMAP;		//Interrupt map register
};

/*create a struct for GPIO register*/
struct My_GPIO_Type
{
	uint32_t My_CFGLR;		//GPIO configuration register low
	uint32_t My_CFGHR;		//GPIO configuration register high
	uint32_t My_IDT;		//GPIO input data register
	uint32_t My_ODT;		//GPIO output data register
	uint32_t My_SCR;		//GPIO set/clear register
	uint32_t My_CLR;		//GPIO clear register
	uint32_t My_WPR;		//GPIO write protection register
	uint32_t My_SRCTR;		//(no mention)
	uint32_t My_HDRV;		//GPIO huge current control register
};

/*====================================================================================
 * 								LOCAL VARIABLES
====================================================================================*/
struct My_RCC_Type *My_RCC = (struct My_RCC_Type *)RCC_Address;
struct My_GPIO_Type *PORTA = (struct My_GPIO_Type *)PORTA_Address;
struct My_GPIO_Type *PORTD = (struct My_GPIO_Type *)PORTD_Address;

/*====================================================================================
 * 								GLOBAL FUNTIONS
====================================================================================*/
int main(void)
{
	GPIO_Configuration();
	while(1)
	{
		/*Check if button is holding -> set(turn on) LED
		 *if button is releasing -> reset(turn off) LED */
		if (PORTA->My_IDT & 1)
		{
			PORTD->My_SCR = 0x60000000;
		}
		else
		{
			PORTD->My_SCR = 0x6000;
		}
	}
}

/*====================================================================================
 * 								LOCAL FUNTIONS
====================================================================================*/
void GPIO_Configuration()
{
	/*LED2 control by GPIOD, port 13
	 *User button control by GPIOA, port0*/
	/*Enable clock for PORT A&D*/
	My_RCC->My_APB2EN |= 0b100; //portA
	My_RCC->My_APB2EN |= 0b100000; //portD
	/*Reset GPIOD port 13*/
	/*Output mode General-purpose output push-pull for PD13, max speed*/
	PORTD->My_CFGHR |= 0x03300000;
}

void Delay_ms(uint16_t time)
{
	uint32_t time_n = time*12000;
	while (time_n != 0)
	{
		time_n --;
	}
}





