// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC0
// Last Modified: 11/11/2021 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly
// Labs 8 and 9 specify PD2
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// ADC initialization function 
// Input: none
// Output: none
// measures from PD2, analog channel 5
void ADC_Init(void){ 
  // put Lab 8 solution here

	SYSCTL_RCGCADC_R |= 0x0001;   // 1) activate ADC0
  SYSCTL_RCGCGPIO_R |= 0x1A;    // 2) activate clock for Port E
	__nop();
	__nop();
	__nop();
	__nop();
	
	
	GPIO_PORTD_DEN_R &= ~0x04;
	GPIO_PORTD_DIR_R &= ~(0x04);
	GPIO_PORTE_DEN_R |= 0x03;
	GPIO_PORTE_DIR_R &= ~(0x03);
	GPIO_PORTB_DEN_R |= 0x30;
	GPIO_PORTB_DIR_R |= (0x30);
	
	
	
  while((SYSCTL_PRGPIO_R&0x10) != 0x10){};  // 3 for stabilization
  GPIO_PORTD_AFSEL_R |= 0x04;   // 5) enable alternate function on PE4
  GPIO_PORTD_AMSEL_R |= 0x04;   // 7) enable analog functionality on PE4
// while((SYSCTL_PRADC_R&0x0001) != 0x0001){}; // good code, but not implemented in simulator
  ADC0_PC_R &= ~0xF;
  ADC0_PC_R |= 0x1;             // 8) configure for 125K samples/sec
  ADC0_SSPRI_R = 0x0123;        // 9) Sequencer 3 is highest priority
  ADC0_ACTSS_R &= ~0x0008;      // 10) disable sample sequencer 3
  ADC0_EMUX_R &= ~0xF000;       // 11) seq3 is software trigger
  ADC0_SSMUX3_R &= ~0x000F;
  ADC0_SSMUX3_R += 5;           // 12) set channel
  ADC0_SSCTL3_R = 0x0006;       // 13) no TS0 D0, yes IE0 END0
  ADC0_IM_R &= ~0x0008;         // 14) disable SS3 interrupts
  ADC0_ACTSS_R |= 0x0008;       // 15) enable sample sequencer 3
	//ADC0_SAC_R = 3; //according to slides??
}

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t ADC_In(void){  
  // put Lab 8 solution here
	// 1) initiate SS3
  // 2) wait for conversion done
  // 3) read result
  // 4) acknowledge completion
	ADC0_PSSI_R=0x0008;
	while((ADC0_RIS_R & 0x08)==0){}
	uint32_t data = ADC0_SSFIFO3_R&0xFFF;
	ADC0_ISC_R=0x0008;
  return data;
}


