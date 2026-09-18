#include <xc.h>

#define _XTAL_FREQ 4000000UL

#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define LR_GREEN   0x02  // RC1
#define LR_YELLOW  0x04  // RC2
#define LR_RED     0x08  // RC3

#define UD_GREEN   0x10  // RC4
#define UD_YELLOW  0x20  // RC5
#define UD_RED     0x40  // RC6

#define GREEN_TIME_MS   3000
#define YELLOW_TIME_MS  1000

void main(void)
{
    TRISC = 0x81;  // RC1-RC6 output, RC0 and RC7 input
    PORTC = 0x00;

    while (1)
    {
        PORTC = LR_GREEN | UD_RED;
        __delay_ms(GREEN_TIME_MS);

        PORTC = LR_YELLOW | UD_RED;
        __delay_ms(YELLOW_TIME_MS);

        PORTC = LR_RED | UD_GREEN;
        __delay_ms(GREEN_TIME_MS);

        PORTC = LR_RED | UD_YELLOW;
        __delay_ms(YELLOW_TIME_MS);
    }
}