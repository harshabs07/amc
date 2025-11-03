#include <stdint.h>
#include "inc\tm4c123gh6pm.h"

void delayMs(int n);

int main(void)
{
    uint32_t duty;
    const uint32_t load_val = 64000;  // PWM period
    
    // Enable clocks to PWM1 and Port F
    SYSCTL_RCGCPWM_R |= 0x02;         // PWM1 clock enable
    SYSCTL_RCGCGPIO_R |= 0x20;        // Port F clock enable
    
    // Configure PWM clock divider to 64
    SYSCTL_RCC_R = (SYSCTL_RCC_R & ~0x000E0000) | 0x000E0000;  // PWM divider 64
    
    // Configure PF3 for PWM output (M1PWM7)
    GPIO_PORTF_AFSEL_R |= 0x08;        // Enable alternate function on PF3
    GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R & 0xFFFF0FFF) | 0x00005000;  // M1PWM7 on PF3
    GPIO_PORTF_DEN_R |= 0x08;          // Digital enable PF3
    
    // Configure PWM generator 3, generator B (M1PWM7)
    PWM1_3_CTL_R = 0;                  // Disable generator 3 during setup
    PWM1_3_GENB_R = 0x0000008C;        // Set PWM output behavior: output set on reload, clear on comparator match
    
    PWM1_3_LOAD_R = load_val;           // Set PWM period
    PWM1_3_CMPA_R = 0;                  // Start with 0% duty cycle
    PWM1_3_CTL_R = 1;                   // Enable generator 3
    
    PWM1_ENABLE_R |= 0x80;              // Enable PWM output on M1PWM7 (PF3)
    
    while(1)
    {
        // Fade LED from low to high brightness
        for (duty = 0; duty < load_val; duty += 256) {
            PWM1_3_CMPA_R = duty;
            delayMs(30);
        }
        
        // Fade LED from high to low brightness
        for (duty = load_val; duty > 0; duty -= 256) {
            PWM1_3_CMPA_R = duty;
            delayMs(30);
        }
    }
}

void delayMs(int n)
{
    volatile int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 3180; j++) {}  // Approximate 1 ms delay at 16 MHz
}
