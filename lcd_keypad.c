 /* ************************************************
 *Project name :Interfacing of analog hex keypad and Output displaying in LCD 16x2 using TIVA C launchpad
 *Date : 12/04/2018
 ***************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "inc\tm4c123gh6pm.h"
#include "driverlib/sysctl.h"

#define LCD_clear()   LCD_command(0x1)        /* Clear display LCD */
#define LCD_origin()  LCD_command(0x2)        /* Set to origin LCD */
#define LCD_row1()    LCD_command(0x80)        /* Begin at Line 1 */
#define LCD_row2()    LCD_command(0xC0)  /* Begin at Line 2 */
void shift_out1(unsigned char str);
void LCD_enable(void);
void LCD_command(unsigned char command);
void LCD_putc(unsigned char ascii);
void LCD_puts(unsigned char *lcd_string);
void LCD_init(void);
unsigned char key_scan(unsigned int volatile rec_val);//stores key pressed
int main(void)
{
	uint32_t ui32ADC0Value;
	unsigned char Dig_val;//values for LCD
	volatile uint32_t ui32TempAvg,Temp_val;
	
	
	
	SYSCTL_RCGCGPIO_R |= 0x039;   /* enable clock to GPIOD/E/A/F */
  SYSCTL_RCGCADC_R |= 1;       /* enable clock to ADC0 */
    
    /* initialize PE3 for AIN4 input  */
    GPIO_PORTD_AFSEL_R |= 8;       /* enable alternate function */
    GPIO_PORTD_DEN_R &= ~8;        /* disable digital function */
    GPIO_PORTD_AMSEL_R |= 8;       /* enable analog function */
	GPIO_PORTE_DIR_R |= 0x0C;			/*   */
	GPIO_PORTE_DEN_R |= 0x0C;
	GPIO_PORTA_DIR_R |= 0x20;
	GPIO_PORTA_DEN_R |= 0x20;
	GPIO_PORTF_DIR_R |= 0x01;
	GPIO_PORTF_DEN_R |= 0x01;
    /* initialize ADC0 */
   ADC0_ACTSS_R &= ~1;        /* disable SS0 during configuration */
   ADC0_EMUX_R &= ~0x000F;    /* software trigger conversion */ 
   ADC0_SSMUX0_R |= 0x05;         /* get input from channel 4 */
   ADC0_SSCTL0_R |= 0x06;        /* take one sample at a time, set flag at 1st sample */
   ADC0_ACTSS_R |= 0x01;           /* enable ADC0 sequencer 0 */
    
    
	  LCD_init();	//LCD 16x2 initializing
	  LCD_row1();	//Cursor position at 1st line
	  LCD_puts("Interfacing");
    LCD_row2();	//Cursor position at 2nd line
    LCD_puts("Analog KEYPAD");
    SysCtlDelay(5000000);
    LCD_clear();
		while(1)
    {
    ADC0_PSSI_R |= 1;        /* start a conversion sequence 0 */
    while((ADC0_RIS_R & 1) == 0) ;   /* wait for conversion complete */
    ui32ADC0Value = ADC0_SSFIFO0_R; /* read conversion result */
    ADC0_ISC_R = 1;          /* clear completion flag */
    Temp_val = ui32ADC0Value/10;
		Dig_val = key_scan(Temp_val);//compare the key pressed
		SysCtlDelay(50000);
		LCD_row1();
		LCD_puts("Press any Key");
		LCD_row2();
		if(Dig_val <= 'F')//if the ascii is less or equal to F put the value in LCD
			LCD_putc(Dig_val);
	}
}


unsigned char key_scan(unsigned int volatile rec_val)
{
	
	     if( rec_val == 373)  return '0';	    // 0 key pressed
	else if( rec_val == 376)  return '1'; 	  // 1st key pressed
	else if( rec_val == 379)  return '2';	    // 2nd key pressed
	else if( rec_val == 381)  return '3'; 	  // 3rd key pressed
	else if( rec_val == 358)  return '4';    	// 4th key pressed
	else if( rec_val == 363)  return '5';    	// 5th key pressed
	else if( rec_val == 368)  return '6';     // 6th key pressed
	else if( rec_val == 372)  return '7';   	// 7th key pressed
	else if( rec_val == 318)  return '8';    	// 8th key pressed
	else if( rec_val == 334)  return '9';   	// 9th key pressed
	else if( rec_val == 346)  return 'A';   	// A  key pressed
	else if( rec_val == 354)  return 'B';   	// B key pressed
	else if( rec_val == 0)    return 'C';   	// C key pressed
	else if( rec_val == 204)  return 'D';    	// D key pressed
	else if( rec_val == 273)  return 'E';			// E key pressed
	else if( rec_val == 307)  return 'F';   	// F key pressed
	else 
	return 'G';

}

