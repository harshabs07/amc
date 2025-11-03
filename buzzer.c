#include <stdint.h>
#include "inc\tm4c123gh6pm.h"
void delayMs(int n);
int value;
int main(void)
{
/* enable clock to GPIO F/D at clock gating control register *//* GPIO PORT D PIN 7 is
connected to Buzzer */
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;//PD
SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;//PF
/* enable the GPIO pins for the PF2/PF3/PB3/PC4 as output */
GPIO_PORTD_LOCK_R = 0x4C4F434B; // unlock GPIO Port D
GPIO_PORTD_CR_R = 0x80; // allow changes to PD7-1 for GPIO
GPIO_PORTD_DIR_R = 0xf0;//PD7
GPIO_PORTD_DEN_R = 0xf0; /* enable the GPIO pins for digital function */
GPIO_PORTF_DIR_R = 0x08; /* set PORTF3 pin as output (LED) pin */
/* and PORTF4 as input, SW1 is on PORTF4 */
GPIO_PORTF_DEN_R = 0x18; /* set PORTF pins 4-3 as digital pins */
GPIO_PORTF_PUR_R = 0x10; /* enable pull up for pin 4 */
while (1)
{
value = GPIO_PORTF_DATA_R; /* read data from PORTF */
value = ~value; /* switch is low active; LED is high active */
value = value >> 1; /* shift it right to display on green LED */
GPIO_PORTF_DATA_R = value; /* put it on the green LED */
value = value << 5;
GPIO_PORTD_DATA_R = value;
}
}
/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(int n)
{
int i, j;
for(i = 0 ; i < n; i++)
for(j = 0; j < 4180; j++)
{} /* do nothing for 1 ms */
}