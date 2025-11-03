/*  p2_3b.c: Toggling LEDs using special function registers by their names defined in the TivaWare header file */

#include <stdint.h>
#include "inc\tm4c123gh6pm.h"

void delayMs(int n);

int main(void)
{
    /* enable clock to GPIOF/B/C at clock gating control register */
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
	  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
	  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
    /* enable the GPIO pins for the PF2/PF3/PB3/PC4 as output */
    GPIO_PORTF_DIR_R = 0x0E;
	  GPIO_PORTB_DIR_R = 0x08;
	  GPIO_PORTC_DIR_R = 0x10;
    /* enable the GPIO pins for digital function */
    GPIO_PORTF_DEN_R = 0x0E;
    GPIO_PORTB_DEN_R = 0x08;
	  GPIO_PORTC_DEN_R = 0x10;
  while(1)
    {
        GPIO_PORTF_DATA_R = 0x04;   
        delayMs(500);

        GPIO_PORTF_DATA_R = 0;      
        delayMs(500); 
    
       GPIO_PORTF_DATA_R = 0x08;   
        delayMs(500);

        GPIO_PORTF_DATA_R = 0;     
        delayMs(500);
			
			  GPIO_PORTB_DATA_R = 0x08;   
        delayMs(500);

        GPIO_PORTB_DATA_R = 0;      
        delayMs(500); 
    
       GPIO_PORTC_DATA_R = 0x10;  
        delayMs(500);

        GPIO_PORTC_DATA_R = 0;     
        delayMs(500);
}
		
}

/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n)
{
    int i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 4180; j++)
        {}  /* do nothing for 1 ms */
}

/* This function is called by the startup assembly code to perform system specific initialization tasks. */

t