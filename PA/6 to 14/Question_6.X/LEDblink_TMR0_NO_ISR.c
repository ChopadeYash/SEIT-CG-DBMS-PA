/*
 * File:   LEDblink_TMR0_NO_ISR.c
 * Author: mokshadvaidya
 *
 * Created on May 20, 2022, 3:15 PM
 */


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 4000000

//void delaybytmr0(){
//    T0CONbits.TMR0ON = 1;
//    while(INTCONbits.TMR0IF == 0);
//    T0CONbits.TMR0ON = 0;
//    INTCONbits.TMR0IF = 0;
//    
//}
//
//void ledBlink(){
//    for(int i=0;i<8;i++)
//    {
//         TMR0 = 48828;
//         delaybytmr0();
//        //__delay_ms(5);
//        LATB=LATB*4+1;
//    }
//}
//
//void main(void) {
//    TRISB = 0;
//    T0CON = 7;
//    INTCONbits.TMR0IF = 0;
//    LATB = 0;
//    while(1){
//        ledBlink();
//        LATB = 0;
//    }
//    
//    return;
//}

void delaybytmr0(){
    T0CONbits.TMR0ON = 1;
    while(INTCONbits.TMR0IF == 0);
    T0CONbits.TMR0ON = 0;
    INTCONbits.TMR0IF = 0;
    
}

void main(void) {
    TRISB = 0;
    T0CON = 7;
    INTCONbits.TMR0IF = 0;
    LATB = 0;
    while(1){
        TMR0 = 46004;
        delaybytmr0();
        LATB = 170;
        TMR0 = 46004;
        delaybytmr0();
        LATB = 85;
    }
    
    return;
}
