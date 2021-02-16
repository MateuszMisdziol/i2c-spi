#include "i2c.h"
#include "led.h"

//funkcja delay z argumentem (w milisekundach)
void Delay(unsigned int uiTime_ms)
{
	unsigned int uiLoopCounter;
	for(uiLoopCounter = 0; uiLoopCounter < uiTime_ms * 5500; uiLoopCounter++){;}
}

int main(void){
	
	unsigned char ucBinaryCounter = 0;
	
	LedInit();
	I2C_Init();
	
	while(1){
		
		PCF8574_Write(ucBinaryCounter);
		ucBinaryCounter = (ucBinaryCounter + 1) % 256;
		Delay(200);
	}
}
