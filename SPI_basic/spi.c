#include <LPC21xx.H>
#include "spi.h"

#define P04_SCK_SPI0_PIN  		(1<<8)
#define P05_MISO_SPI0_PIN 		(1<<10)
#define P06_MOSI_SPI0_PIN 		(1<<12)
#define P07_SSEL_SPI0_PIN 		(1<<14)

#define CS_bm 		        		(1<<10)

#define SPI_CPHA_bm           (1<<3)
#define SPI_CPOL_bm           (1<<4)
#define SPI_MSTR_bm        		(1<<5)
#define SPI_LSBF_bm						(1<<6)
#define SPI_SPIF_bm           (1<<7)
#define SPI_CLK_DIVIDER_bm       8

#define DAC_GA_bm							(1<<5)
#define DAC_SHDN_bm						(1<<4)
#define DAC_BUFF_bm           (1<<3)
#define DAC_AB_bm             (1<<2)

#define MAX_12BIT_NUMBER 		   4095
#define MAX_VOLTAGE						 3300


void DAC_MCP4921_Set(unsigned int uiVoltage){
	
	PINSEL0 |= (P04_SCK_SPI0_PIN | P05_MISO_SPI0_PIN | P06_MOSI_SPI0_PIN | P07_SSEL_SPI0_PIN);
	IO0DIR |= CS_bm;	
	S0SPCR |= SPI_MSTR_bm;
	S0SPCR &= (~(SPI_CPHA_bm | SPI_CPOL_bm | SPI_LSBF_bm));
	S0SPCCR = SPI_CLK_DIVIDER_bm;
	
	IO0CLR = CS_bm;
	S0SPDR = (~(DAC_AB_bm & DAC_BUFF_bm)) & (DAC_GA_bm | DAC_SHDN_bm | (uiVoltage >> 8));
	while((S0SPSR & SPI_SPIF_bm) == 0){}
	S0SPDR = uiVoltage;
	while((S0SPSR & SPI_SPIF_bm) == 0){}
	IO0SET = CS_bm;
}

void DAC_MCP4921_Set_mV(unsigned int uiVoltage){
	
	DAC_MCP4921_Set((uiVoltage * MAX_12BIT_NUMBER)/MAX_VOLTAGE);
}
