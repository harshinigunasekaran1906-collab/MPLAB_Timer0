#include <xc.h>

// CONFIG BITS
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 8000000

// LED PIN
#define LED RC0

// GLOBALS
volatile unsigned char tmr_count = 0;
volatile unsigned char led_state = 0;

// TIMER0 INTERRUPT
void __interrupt() ISR(void)
{
    if (TMR0IF)
    {
        TMR0 = 0;
        TMR0IF = 0;

        tmr_count++;

        if (tmr_count >= 31)   // ? 2 seconds
        {
            tmr_count = 0;
            led_state = !led_state;   // toggle LED state
            LED = led_state;
        }
    }
}

void main(void)
{
    OSCCON = 0x70;   // 8 MHz
    ANSEL = 0;
    ANSELH = 0;
    TRISC = 0x00;

    LED = 0;         // LED OFF initially

    // TIMER0 SETUP
    OPTION_REG = 0b00000111; // Prescaler 1:256
    TMR0 = 0;
    TMR0IF = 0;
    TMR0IE = 1;
    GIE = 1;

    while (1)
    {
        // Nothing here
        // LED controlled only by TIMER
    }
}