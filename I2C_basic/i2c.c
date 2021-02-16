#include <LPC21xx.H>
#include "i2c.h"
#include "led.h"

//I2C Pin Select
#define P02_I2C_SCL_PIN 		(1<<4)
#define P03_I2C_SDA_PIN 		(1<<6)

//I2C Control Set Register
#define I2C_AA_bm       		(1<<2)
#define I2C_SI_bm       		(1<<3)
#define I2C_STO_bm      		(1<<4)
#define I2C_STA_bm      	  (1<<5)
#define I2C_I2EN_bm     	  (1<<6)

//I2C Control Clear Register
#define I2C_AAC_bm          (1<<2)
#define I2C_SIC_bm          (1<<3)
#define I2C_STAC_bm         (1<<5)
#define I2C_I2ENC_bm        (1<<6)

//I2C Serial Clock Duty Cycle
#define I2SCLH_bm            0x80
#define I2SCLL_bm            0x80

//I2C Interrupt
#define VIC_I2C_CHANNEL_NR    9
#define IRQ_SLOT_ENABLE_bm  (1<<5)

//I2C Status Codes
#define START_CONDITION            0x08
#define SLAVE_ADDR_W_ACK           0x18
#define DATA_SEND_COMPLETE_ACK     0x28

#define I2C_SLAVE_ADDRESS    0x20

unsigned char ucI2CData = 0;

__irq void I2C_Interrupt(void){
	
	switch(I2STAT){
		case START_CONDITION:
			I2DAT = (I2C_SLAVE_ADDRESS << 1); //dodatkowo bit R/W W = 0 R = 1;  (0100 0000)
			I2CONCLR = I2C_STAC_bm;
			break;
		case SLAVE_ADDR_W_ACK: //slave_addr + w wyslane i otrzymane potwierdzenie od slave AA
			I2DAT = ucI2CData;
			break;
		case DATA_SEND_COMPLETE_ACK: //dane wyslane i otrzymane potwierdzenie AA
			I2CONSET = I2C_STO_bm;
			break;
		default: //ERROR
			LedOn(I2STAT);
			break;
	}
	
	I2CONCLR = I2C_SIC_bm; //kasowanie flagi przerwania
	VICVectAddr = 0x00; //potwierdzenie wykonania przerwania
}

void I2C_Init(void){
	
	//konfigurujemy piny do obslugi i2c
	PINSEL0 |= P02_I2C_SCL_PIN | P03_I2C_SDA_PIN;
	
	//konfigurujemy transmisje i2c
	I2CONCLR = I2C_STAC_bm | I2C_SIC_bm | I2C_AAC_bm;
	I2CONSET = I2C_I2EN_bm;
	I2SCLH = I2SCLH_bm;
	I2SCLL = I2SCLL_bm;
	
	//konfigurujemy obsluge przerwan
	VICIntEnable |= (1 << VIC_I2C_CHANNEL_NR);  // wlaczenie kanalu przerwan i2c
	VICVectCntl0  = IRQ_SLOT_ENABLE_bm | VIC_I2C_CHANNEL_NR; //wlaczenie slotu i przypisanie do niego kanalu przerwan i2c
	VICVectAddr0  = (unsigned long)I2C_Interrupt; //przypisanie adresu procedury obslugi przerwania
}

//funkcja inicjalizuje do wpisania bajt danych do ekspandera PCF8574
void PCF8574_Write(unsigned char ucData){
	
	ucI2CData = ucData;
	I2CONSET = I2C_STA_bm; //podanie na linie danych warunku startu
}
