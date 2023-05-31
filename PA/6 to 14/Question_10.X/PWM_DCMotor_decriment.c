/*
 * File:   PWM_DCMotor_decriment.c
 * Author: mokshadvaidya
 *
 * Created on May 21, 2022, 2:20 PM
 */


#include <xc.h>

void main(void) {
    TRISCbits.TRISC2 = 0;
    CCP1CON = 0b00001100;
    T2CON = 0b00000010;
    PR2 = 61;
    CCPR1L = 61;
    while(1){
        TMR2IF = 0;
        TMR2 = 0;
        TMR2ON = 1;
        while(TMR2IF==0);
    }
    return;
}
