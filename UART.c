// UART1.c
// Runs on LM4F120/TM4C123
// Use UART1 to implement bidirectional data transfer to and from 
// another microcontroller in Lab 9.  
// Daniel Valvano
// November 11, 2021

// U1Rx (VCP receive) connected to PC4
// U1Tx (VCP transmit) connected to PC5
#include <stdint.h>
#include "UART.h"
#include "../inc/tm4c123gh6pm.h"
#define LF  0x0A

// Initialize UART1 on PC4 PC5
// Baud rate is 1000 bits/sec
// Receive interrupts and FIFOs are used on PC4
// Transmit busy-wait is used on PC5.
void UART_Init(void){
  // write this
	/*
	Fifo_Init();
	SYSCTL_RCGCUART_R |= 0x02;            // activate UART1
  SYSCTL_RCGCGPIO_R |= 0x04;            // activate port C
  while((SYSCTL_PRGPIO_R&0x01) == 0){};
  UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART1_IBRD_R = 5000;                    // IBRD = int(80,000,000 / (16 * 1000)) = int(5000)
  UART1_FBRD_R = 0;                     // FBRD = int(0 * 64 + 0.5) = 1?
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART1_CTL_R |= 0x301;                 // enable UART
  GPIO_PORTC_AFSEL_R |= 0x30;           // enable alt funct on PA1-0
  GPIO_PORTC_DEN_R |= 0x30;             // enable digital I/O on PA1-0
                                        // configure PA1-0 as UART
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;
  GPIO_PORTC_AMSEL_R &= ~0x30;          // disable analog functionality on PA
		
	UART1_IFLS_R = ((UART1_IFLS_R & (~(0x38))) | 0x10);
	NVIC_EN0_R |= 0x40; //enabling interrupt 6?
	NVIC_PRI1_R &= (~(0x00E00000)); //setting priority to 0?
		
	GPIO_PORTC_DIR_R |= 0x20;
	GPIO_PORTC_DIR_R &= ~(0x10);
	*/
	
	SYSCTL_RCGCUART_R |= 0x00000002;  // activate UART1
  SYSCTL_RCGCGPIO_R |= 0x00000004;  // activate port C
	while((SYSCTL_PRGPIO_R&0x04) == 0){};
  UART1_CTL_R &= ~0x00000001;    // disable UART
  UART1_IBRD_R = 5000;     // IBRD = int(80,000,000/(16*115,200)) = int(43.40278)
  UART1_FBRD_R = 0;     // FBRD = round(0.40278 * 64) = 26
  UART1_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs
  UART1_CTL_R |= 0x00000301;     // enable UART
  GPIO_PORTC_AFSEL_R |= 0x30;    // enable alt funct on PC5-4
  GPIO_PORTC_DEN_R |= 0x30;      // configure PC5-4 as UART1
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;
  GPIO_PORTC_AMSEL_R &= ~(0x30);   // disable analog on PC5-4
	
	//should interrupt at 2/16 items in FIFO
	//UART1_IFLS_R = ((UART1_IFLS_R & (~(0x38))) | 0x00);
	
	UART1_IM_R = 0x10;
		
	//NVIC_EN0_R |= 0x40; //enabling interrupt 6?
	//NVIC_PRI1_R &= (~(0x00E00000)); //setting priority to 0?
	
	
}

//------------UART_InChar------------
// Receive new input, interrupt driven
// Input: none
// Output: return read ASCII code from UART, 
// Reads from software FIFO (not hardware)
// Either return 0 if no data or wait for data (your choice)
int32_t UART_InChar(void){
	
	//essentially useless function
	if((UART1_FR_R&UART_FR_RXFE) != 0){
		return(-1);
	}
  return((UART1_DR_R));
}
//------------UART1_InMessage------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until LR is received
//    or until max length of the string is reached.
// Reads from software FIFO (not hardware)
// Input: pointer to empty buffer of 8 characters
// Output: Null terminated string
void UART1_InMessage(char *bufPt){
// optional implement this here or in Lab 9 main
}
//------------UART1_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
// busy-wait; if TXFF is 1, then wait
// Transmit busy-wait is used on PC5.
void UART_OutChar(int32_t data){
  // write this
	
	while((UART1_FR_R&UART_FR_TXFF) != 0){};
  UART1_DR_R = data;
	
	
	/*
	while((UART1_FR_R&0x0020) != 0);      // wait until TXFF is 0
  UART1_DR_R = data;
	*/
}
#define PF2       (*((volatile uint32_t *)0x40025010))
// hardware RX FIFO goes from 7 to 8 or more items
// Receive interrupts and FIFOs are used on PC4

char output2;
void UART1_Handler(void){
}

//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART_OutString(char *pt){
  // if needed
  
}



