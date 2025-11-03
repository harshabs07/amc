#include <stdint.h>
#include "inc\tm4c123gh6pm.h"
void UART0Tx(char c);
void delayMs(int n);
int main(void) 
{
    SYSCTL_RCGCUART_R = 1;  /* provide clock to UART0 */
    SYSCTL_RCGCGPIO_R = 1;  /* enable clock to PORTB */ 
    /* UART0 initialization */
    UART0_CTL_R = 0;         /* disable UART0 */
    UART0_IBRD_R = 104;      /* 16MHz/16=1MHz, 1MHz/104=9600 baud rate */
    UART0_FBRD_R = 11;       /* fraction part*/
    UART0_CC_R = 0;          /* use system clock */
    UART0_LCRH_R = 0x60;     /* 8-bit, no parity, 1-stop bit, no FIFO */
    UART0_CTL_R = 0x301;     /* enable UART0, TXE, RXE */
                            /* UART0 TX0 and RX0 use PB0 and PB1. Set them up. */
    GPIO_PORTA_DEN_R = 0x03;      /* Make PB0 and PB1 as digital */
    GPIO_PORTA_AFSEL_R = 0x03;    /* Use PB0,PB1 alternate function */
    GPIO_PORTA_PCTL_R = 0x11;     /* configure PB0 and PB1 for UART */    
    delayMs(1);             /* wait for output line to stabilize */  
    UART0Tx('E');
    UART0Tx('N');
    UART0Tx('T');
    UART0Tx('E');    
	  UART0Tx('R');  
	  UART0Tx(' ');  
	  UART0Tx('T');  
	  UART0Tx('E');  
	  UART0Tx('X');  
	  UART0Tx('T');  
	  UART0Tx(':');	
}
/* UART0 Transmit */
/* This function waits until the transmit buffer is available then */
/* writes the character in the transmit buffer. It does not wait */
void UART0Tx(char c)  
{
    while((UART0_FR_R & 0x20) != 0); /* wait until Tx buffer not full */
    UART0_DR_R = c;                  /* before giving it another byte */
}
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 5000; j++)
            {}  /* do nothing for 1 ms */
}
