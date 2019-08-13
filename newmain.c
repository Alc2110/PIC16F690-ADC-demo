/*
 * File:   newmain.c
 * Author: Alex
 * PIC16F690 ADC voltage input 0-5 V demo
 * Created on 13 August 2019, 12:50 AM
 */

#include <xc.h>

#pragma config FOSC=INTRCIO, WDTE=OFF, PWRTE=OFF, MCLRE=ON, CP=OFF, \
                CPD=OFF, BOREN=OFF, IESO=OFF, FCMEN=OFF

#define _XTAL_FREQ 4000000

#define LED1 PORTBbits.RB4
#define LED2 PORTBbits.RB5
#define LED3 PORTBbits.RB6
#define LED4 PORTBbits.RB7

int result;

void main(void)
{
    // AN2/RA2 is analog
    ANSEL = 0b00000100;
    ANSELH = 0;
    
    // making sure all unused pins are outputs
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    // explicitly setting the LED output pins
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB7 = 0;
    
    // ADC channel selection - select AN2/RA2 pin as input
    ADCON0bits.CHS = 0b0010;
    
    // Set Vref to VDD
    ADCON0bits.VCFG = 0;
    
    // conversion clock
    ADCON1bits.ADCS = 0b001;
    
    // result formatting - right justified
    ADCON0bits.ADFM = 1;
    
    // enable ADC
    ADCON0bits.ADON = 1;
    
    // start with all LEDs off
    LED1 = 0;   LED2 = 0;   LED3 = 0;   LED4 = 0;
    
    // main loop
    while(1)
    {
        // wait the acquisition time
        __delay_us(5);
        
        // start ADC cycle, and wait until it is done
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO) {};
        
        result = (ADRESH<<8) + ADRESL;
        
        if ((result >= 0)&&(result < 205))
        {
            // 0-1 V
            LED1 = 0;   LED2 = 0;   LED3 = 0;   LED4 = 0;
        }
        else if ((result >= 205)&&(result < 409))
        {
            // 1-2 V
            LED1 = 1;   LED2 = 0;   LED3 = 0;   LED4 = 0;
        }
        else if ((result >= 409)&&(result < 614))
        {
            // 2-3 V
            LED1 = 1;   LED2 = 1;   LED3 = 0;   LED4 = 0;
        }
        else if ((result >= 614)&&(result < 818))
        {
            // 3-4 V
            LED1 = 1;   LED2 = 1;   LED3 = 1;   LED4 = 0;
        }
        else if ((result >= 818)&&(result <= 1023))
        {
            // 4-5 V
            LED1 = 1;   LED2 = 1;   LED3 = 1;   LED4 = 1;
        }
        else
        {
            LED1 = 0;   LED2 = 0;   LED3 = 0;   LED4 = 0;
        }
    }
    
    return;
}
