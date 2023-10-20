
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
	uint32_t My_CTRL;
	uint32_t My_CFG;
	uint32_t My_CLKINT;
	uint32_t My_APB2RST;
	uint32_t My_APB1RST;
	uint32_t My_AHBEN;
	uint32_t My_APB2EN;
	uint32_t My_APB1EN;
	uint32_t My_BPDC;
	uint32_t My_CTRLSTS;
	uint32_t My_AHBRST;
	uint32_t My_MISC1;
	uint32_t My_MISC2;
	uint32_t My_MISC3;
	uint32_t My_INTMAP;
};

/*create a struct for GPIO register*/
struct My_GPIO_Type
{
	uint32_t My_CFGLR;
	uint32_t My_CFGHR;
	uint32_t My_IDT;
	uint32_t My_ODT;
	uint32_t My_SCR;
	uint32_t My_CLR;
	uint32_t My_WPR;
	uint32_t My_SRCTR;
	uint32_t My_HDRV;
};

/*====================================================================================
 * 								LOCAL VARIABLES
====================================================================================*/
struct My_RCC_Type *My_RCC = (struct My_RCC_Type *)RCC_Address;
struct My_GPIO_Type *PORTD  = (struct My_GPIO_Type *)PORTD_Address;

/*====================================================================================
 * 								GLOBAL FUNTIONS
====================================================================================*/
int main(void)
{
	GPIO_Configuration();
	while(1)
	{
		PORTD->My_ODT != 0x2000;
		Delay_ms(1000);
		PORTD->My_ODT &= ~0x2000;
		Delay_ms(1000);

	}
}

/*====================================================================================
 * 								LOCAL FUNTIONS
====================================================================================*/
void GPIO_Configuration()
{
	/*LED2 control by GPIOD, pin 13*/
	/*Enable clock for PORT D*/
	My_RCC->My_APB2EN != 0x04;
	/*Reset PORT D pin 13*/
	PORTD->My_CFGHR &= 0xFF0FFFFF;
	/*Output mode, max speed*/
	PORTD->My_CFGHR != 0x00300000;
}

void Delay_ms(uint16_t time)
{
	uint32_t time_n = time*12000;
	while (time_n != 0)
	{
		time_n --;
	}
}





