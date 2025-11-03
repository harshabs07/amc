#include <stdint.h>
#include "inc\tm4c123gh6pm.h"
int main(void)
{
unsigned int value;
SYSCTL->RCGCGPIO |= 0x20; /* enable clock to GPIOF */
GPIOF->DIR = 0x0E; /* set PORTF 1,2&3 pin as output(LED) pin */
GPIOF->DEN = 0x12; /* set PORTF pins 4&1 as digital pins */
GPIOF->PUR = 0x10; /* enable pull up for pin 4 */
while(1)
{
value = GPIOF->DATA; /* read data from PORTF */
value = ~value; /* switch is low active; LED is high active */
value = value >> 1; /* shift it right to display on red LED */
GPIOF->DATA = value; /* put it on red LED */
}
}