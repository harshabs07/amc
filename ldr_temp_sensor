/* p7_1.c: A to D conversion */

/* This program converts the analog input from AIN0 (J3.9 of LaunchPad) using sample sequencer 3 and software trigger continuously.
Notice from Table 7-7, AIN0 channel is on PE3 pin. */
#include "inc\tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdint.h>
void shift_out1(unsigned char str);
void delayMs(int n);
volatile int num1,num2,num3,num4;
unsigned int temp;
int main(void)
{
    volatile int result;
	unsigned char a[16] = {0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xF6,0xEE,0x3E,0x9C,0x7A,0x9E,0x8E};
  // unsigned int i;
    /* enable clocks */
    SYSCTL_RCGCGPIO_R |= 0x08;   /* enable clock to GPIOE (AIN0 is on PE3) */
    SYSCTL_RCGCADC_R |= 1;       /* enable clock to ADC0 */
    SYSCTL_RCGCGPIO_R |= 0x10;
    GPIO_PORTE_DIR_R |= 0x1F;
    GPIO_PORTE_DEN_R |= 0x1F;
    /* initialize PE3 for AIN0 input  */
    GPIO_PORTD_AFSEL_R |= 1;       /* enable alternate function */
    GPIO_PORTD_DEN_R &= ~1;        /* disable digital function */
    GPIO_PORTD_AMSEL_R |= 1;       /* enable analog function */
    /* initialize ADC0 */
   ADC0_ACTSS_R &= ~1;        /* disable SS3 during configuration */
   ADC0_EMUX_R &= ~0x000F;    /* software trigger conversion */
   ADC0_SSMUX0_R &= ~0xFFFFFFFF;  
 	ADC0_SSMUX0_R |= 0x07;         /* get input from channel 0 */
    ADC0_SSCTL0_R |= 0x06;        /* take one sample at a time, set flag at 1st sample */
   ADC0_ACTSS_R |= 0x01;           /* enable ADC0 sequencer 3 */    
    while(1)
    {
        ADC0_PSSI_R |= 1;        /* start a conversion sequence 3 */
        while((ADC0_RIS_R & 1) == 0) ;   /* wait for conversion complete */
        result = ADC0_SSFIFO0_R; /* read conversion result */
        ADC0_ISC_R = 1;          /* clear completion flag */
        temp= (1475 - (((2475 * result)) / 4096))/10;
			  temp= ((temp * 9) + 160) / 5;
				result=temp;
num1 = result%10;//copies data from the specified location
		result = result/10;
	num2 = result%10;
       result = result/10;
	num3 = result%10;
		result = result/10;
num4 = result%10;
			shift_out1(a[num1]);
			shift_out1(a[num2]);
			shift_out1(a[num3]);
			shift_out1(a[num4]);
			shift_out1(0x00);	
		  delayMs(200);
}
	}
void shift_out1(unsigned char str)
{
unsigned char j=0,check;
 unsigned int i;
	for(j=0;j<=7;j++)
	{
		GPIO_PORTE_DATA_R = 0x00;	//PE3 pin(sclk) is low (0000 0000)
		check = (str &(1<<j));
		if(check)
			GPIO_PORTE_DATA_R =  0x04;	//PE2 pin(sdat) is high (0000 0100)
else
				           GPIO_PORTE_DATA_R |=  0x00;
                   GPIO_PORTE_DATA_R |=  0x08;	//PE3 pin(sclk) is high (0000 1000)
		               GPIO_PORTE_DATA_R |=  0x10;
	}
}
void delayMs(int n)
{
	int i,j;
	for(i=0;i<n;i++)
	   for(j=0;j<4180;j++)
	{}
}
