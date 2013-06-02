/*
 * File:   blink.c
 * Author: viitanenm
 *
 * Created on April 5, 2013, 11:45 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24FJ64GB002.h>

#define DELAY 4000

// control the DS
#define DS_low()  LATB &=~0x8000
#define DS_high()  LATB |=0x8000

// control the ST_CP
#define ST_CP_low() LATB &=~0x4000
#define ST_CP_high() LATB |=0x4000

// control the SH_CP
#define SH_CP_low() LATB &=~0x2000
#define SH_CP_high() LATB |=0x2000

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

void doStep(unsigned int pattern);
void setLEDs(unsigned int pattern);

int main(int argc, char** argv) {

    TRISB = 0x0000;
    T1CON = 0x8030;

    // reset everything
    LATB = 0x0000;
    doStep(0x00);
    while (1) {
        doStep(0x2000);
        doStep(0x8000);
        doStep(0x0080);
    } // main loop
    return (EXIT_SUCCESS);
}

void doStep(unsigned int pattern) {
    TMR1 = 0;
    setLEDs(pattern);
    while (TMR1 < DELAY) {
    }
}

void setLEDs(unsigned int pattern) {
    ST_CP_low();
    SH_CP_low();
    int i;
    for (i = 0; i < 8; i++) {
        if (CHECK_BIT(pattern, i))
            DS_high();
        else
            DS_low();

        SH_CP_high();
        SH_CP_low();
    }
    ST_CP_high();
}
