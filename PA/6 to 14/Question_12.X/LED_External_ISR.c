/*
 * File:   LED_External_ISR.c
 * Author: mokshadvaidya
 *
 * Created on May 21, 2022, 2:12 PM
 */


#include <xc.h>
#define relay LATAbits.LATA4
#define _XTAL_FREQ 4000000
int c = 0;
void __interrupt() isr(){
    if(INT1IF){
        INT1IF = 0;
        if(c==0 && relay==0){
            relay = 1;
        }
        else if(relay==1 && c==0){
            c++;
        }
        else if(relay==1 && c==1){
            c = 0;
            relay = 0;
        }
   
    }
    
}

void main(void) {
    TRISAbits.TRISA4 = 0;
    TRISBbits.RB1 = 1;
    relay = 0;
    INT1IE = 1;
    INTEDG1 = 0;
    GIE = 1;
    INT1IF = 0;
     while(1);
    return;
}

