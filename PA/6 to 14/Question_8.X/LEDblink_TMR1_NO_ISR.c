/*
 * File:   LEDblink_TMR1_NO_ISR.c
 * Author: mokshadvaidya
 *
 * Created on May 20, 2022, 6:16 PM
 */


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 4000000

void delaybytmr1(){
    T1CONbits.TMR1ON = 1;
    while(TMR1IF == 0);
    T1CONbits.TMR1ON = 0;
    PIR1bits.TMR1IF = 0;
    
}

void main(void) {
    TRISB = 0;
    T1CON = 48;
    TMR1IF = 0;
    LATB = 0;
    while(1){
        TMR1 = 0;
        delaybytmr1();
        LATB = 170;
        TMR1 = 0;
        delaybytmr1();
        LATB = 85;
    }
    
    return;
}
