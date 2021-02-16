#include <math.h>
#include "spi.h"

#define PI            3.14159
#define MAX_DEGREE    360


unsigned int uiSinArrayValues[MAX_DEGREE];
unsigned int uiSinArgumentDegree;

//funkcja delay z argumentem (w milisekundach)
void Delay(unsigned int uiTime_ms)
{
	unsigned int uiLoopCounter;
	for(uiLoopCounter = 0; uiLoopCounter < uiTime_ms * 5500; uiLoopCounter++){;}
}

int main(void){
	//inicjalizacja tablicy watosciami sinusa
	for(uiSinArgumentDegree = 0; uiSinArgumentDegree < MAX_DEGREE; uiSinArgumentDegree++){
		uiSinArrayValues[uiSinArgumentDegree] = (1 + sin(uiSinArgumentDegree * 2 * PI/MAX_DEGREE)) * 1000;
	}
	
	while(1){

		uiSinArgumentDegree = (uiSinArgumentDegree + 4) % 360;
		DAC_MCP4921_Set_mV(uiSinArrayValues[uiSinArgumentDegree]);
		Delay(1);
	}
}
