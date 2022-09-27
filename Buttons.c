#include <stdint.h>

#include "../inc/tm4c123gh6pm.h"
#include "SpaceRace.h"
#include "ST7735.h"

//PE0 = move up
//PE1 = shield
//PE2 = move down

void Delay100ms(uint32_t count); // time delay in 0.1 seconds


void Buttons_Init(void){
		SYSCTL_RCGCGPIO_R |= 0x10;
		__nop();
		__nop();
		__nop();
		__nop();
		
		GPIO_PORTE_DEN_R |= 0xF;

		GPIO_PORTE_DIR_R &= !0xF;
}


//PE0 = Spanish
//PE1 = n/a
//PE2 = n/a
//PE3 = English





