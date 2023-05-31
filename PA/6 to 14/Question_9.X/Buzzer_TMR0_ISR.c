/*
 * File:   Buzzer_TMR0_ISR.c
 * Author: mokshadvaidya
 *
 * Created on May 20, 2022, 10:45 PM
 */

//
//#include <xc.h>
//#include <pic18f4550.h>
////#define led LATAbits.LATA5
//#define led LATBbits.LATB0
//
//int c = 0;
//
//void __interrupt() Timer_ISR(void){
//    if(TMR0IF==1){
//        TMR0IF = 0;
//        c++;
//        if(c==100){
//            led = ~led;
//            c = 0;
//        }
//        
//    }
//}
//
//void main(void) {
//    
////    TRISAbits.TRISA5 = 0;
////    LATAbits.LATA5 = 0;
//    
//    TRISB = 0;
//    PORTB = 1;
//    
//    T0CON = 8;
//    GIE = 1;
//    PEIE = 1;
//    TMR0IE = 1;
//    TMR0 = 0;
//    TMR0IF = 0;
//    TMR0ON = 1;
//    while(1);
//    return;
//}

#include <xc.h>
#include <pic18f4550.h>
#define buzzer LATAbits.LATA5

int c = 0;

void __interrupt() Timer_ISR(void){
    if(TMR0IF==1){
        TMR0IF = 0;
        c++;
        if(c==100){
            buzzer = ~buzzer;
            c = 0;
        }
        
    }
}

void main(void) {
    
    TRISAbits.TRISA5 = 0;
    LATAbits.LATA5 = 0;
    
    T0CON = 8;
    
    GIE = 1;
    PEIE = 1;
    TMR0IE = 1;
    
    TMR0 = 0;
    TMR0IF = 0;
    TMR0ON = 1;
    
    while(1);
    return;
}

