// dac.c
// This software configures DAC output
// Lab 6 requires a minimum of 4 bits for the DAC, but you could have 5 or 6 bits
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 11/15/2021 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data

// **************DAC_Init*********************
// Initialize 6-bit DAC, called once 
// Input: none
// Output: none
void DAC_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x02;
	__nop();
	__nop();
	__nop();
	__nop();
	
	
	GPIO_PORTB_AMSEL_R &= ~0x3F;// disable analog on PB3-0
  GPIO_PORTB_PCTL_R &= ~0x00FFFFFF; // configure PB3-0 as GPIO
  GPIO_PORTB_DIR_R |= 0x3F;   // make PB3-0 out
  GPIO_PORTB_AFSEL_R &= 0x3F; // disable alt funct on PB3-0
  GPIO_PORTB_DEN_R |= 0x3F;   // enable digital I/O on PB3-0
  GPIO_PORTB_DR8R_R |= 0x3F;  // enable 8 mA drive on PB3-0
	
	//GPIO_PORTB_DR8R_R |= 0x3F; //drive more current
	//GPIO_PORTB_DEN_R |= 0x3F;
	//GPIO_PORTB_DIR_R |= 0x3F;
}

// **************DAC_Out*********************
// output to DAC
// Input: 6-bit data, 0 to 63 
// Input=n is converted to n*3.3V/63
// Output: none
void DAC_Out(uint32_t data){
	GPIO_PORTB_DATA_R=data;
}
