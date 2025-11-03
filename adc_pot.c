#include <stdint.h>
#include "inc\tm4c123gh6pm.h"
int x,y,z;
void delayMs(int n);
int main(void)
{
    /* enable clock to GPIOF/B/C at clock gating control register */
      SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;//PF
	  
    /* enable the GPIO pins for the PF2/PF3/PB3/PC4 as output */
    GPIO_PORTF_DIR_R = 0x0F;//PF2/3
	
    /* enable the GPIO pins for digital function */
    GPIO_PORTF_DEN_R = 0x0F;
    
  while(1)
    {
        GPIO_PORTF_DATA_R = 0x02; 
        delayMs(500);
				GPIO_PORTF_DATA_R = 0x04; 
        delayMs(500);
				x=4,y=3;
				z= x+y;
        GPIO_PORTF_DATA_R = z; 
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


