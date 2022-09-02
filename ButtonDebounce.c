/*
 * File:   ButtonDebounce.c
 * Author: Anokhramesh
 *https://www.allaboutcircuits.com/technical-articles/switch-bounce-how-to-deal-with-it/
 * Created on September 2, 2022, 11:23 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
__CONFIG(FOSC_INTOSCIO & WDTE_OFF & PWRTE_OFF & MCLRE_ON & BOREN_ON & LVP_ON & CPD_OFF & CP_OFF);//PIC COnfiguration Bit setting
#define _XTAL_FREQ 4000000// CRYSTAL FREQUENCY 4 MhZ
#define LEDGreen PORTBbits.RB3//Connect LEDGreen to PORTB Pin RB3
#define Relay PORTBbits.RB2//Connect Relay to PORTB Pin RB2
#define BTN  PORTBbits.RB0//Connect Push Button to PORTB Pin RB0 pull down to GND via 10K resister

// VARIABLES
char BTN_pressed = 0;
char BTN_press = 0;
char BTN_release = 0;
char Bouncevalue = 200;
// MAIN PROGRAM
int main(int argc, char** argv) {
    // Comparators off
    CMCON = 0x07;
    // Port directions
    TRISB = 0b00000001;// set PORTB pin RB0 as an INPUT
    // Port state, all low
    PORTB = 0b00000000;//set initial value of entire PORTB as LOW
    // Starting with LEDGreen HIGH and Relay is LOW
    LEDGreen = 1;
    Relay = 0;
    while (1)
    {
        // If BTN is pressed 
        if (BTN == 1)// if button value is HIGH
        {
            // Bouncing has started so increment BTN_press with 1
            BTN_press++;
            // "reset" BTN_release
            BTN_release = 0;
            // If it bounces so much that BTN_press is greater than Bouncevalue
            // Then button must be pressed
            if (BTN_press > Bouncevalue)
            {
                // This is initial value of BTN_pressed
                if (BTN_pressed == 0)
                {
                    // Toggle the LEDs
                    LEDGreen ^= 1;// switch the current status of LEDGReen to Back
                    Relay ^= 1;// switch the current status of Relay to Back
                    BTN_pressed = 1;//set the value of variable BTN_pressed is equal to 1.
                }
                BTN_press = 0;//set the value of variable BTN_press is equal to 0.
            }
        }
        else
        {
            // Increment the "low" in the bouncing
            BTN_release++;
            BTN_press = 0;
            // If BTN_release is greater than bouncevalue, we do not have a
            // pressed button
            if (BTN_release > Bouncevalue)
            {
                BTN_pressed = 0;//set the value of variable BTN_pressed is equal to 0.
                BTN_release = 0;//set the value of variable BTN_release is equal to 0.
            }
        }
        
    }
    return (EXIT_SUCCESS);
}
