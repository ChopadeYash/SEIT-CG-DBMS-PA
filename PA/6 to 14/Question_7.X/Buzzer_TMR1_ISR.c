/*
 * File:   Buzzer_TMR1_ISR.c
 * Author: mokshadvaidya
 *
 * Created on May 20, 2022, 10:22 PM
 */


//#include <xc.h>
//#include <pic18f4550.h>
////#define led LATAbits.LATA5
//#define led LATBbits.LATB0

//int c = 0;
//
//void __interrupt() Timer_ISR(void){
//    if(TMR1IF==1){
//        TMR1IF = 0;
//        c++;
//        if(c==1000){
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
//    T1CON = 0;
//    GIE = 1;
//    PEIE = 1;
//    TMR1IE = 1;
//    TMR1 = 0;
//    TMR1IF = 0;
//    TMR1ON = 1;
//    while(1);
//    return;
//}

#include <xc.h>
#include <pic18f4550.h>
#define led LATAbits.LATA5


int c = 0;

void __interrupt() Timer_ISR(void){
    if(TMR1IF==1){
        TMR1IF = 0;
        c++;
        if(c==100){
            led = ~led;
            c = 0;
        }
        
    }
}

void main(void) {
    
    TRISAbits.TRISA5 = 0;
    LATAbits.LATA5 = 0;
    
    T1CON = 0;
    
    GIE = 1;
    PEIE = 1;
    TMR1IE = 1;
    
    TMR1 = 0;
    TMR1IF = 0;
    TMR1ON = 1;
    
    while(1);
    return;
}

