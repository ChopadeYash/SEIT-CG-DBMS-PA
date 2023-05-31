#include <xc.h>
#include<stdio.h>
#include <pic18f4550.h>
#define _XTAL_FREQ 4000000

void putch(unsigned char c){
    while(PIR1bits.TXIF ==0);
    TXREG = c;
}

//void init_uart(void){
//    TXSTA1bits.TXEN = 1;
//    RCSTA1bits.SPEN = 1;
//}

void main (void){
    //init_uart();
    int a = 0;
    TRISC=0;
    TXSTA=0x20;
    RCSTA=0b10010000;
    SPBRG=6;
    TRISCbits.TRISC7=1;
    while(1){
        printf("\n PICT");
        a = RCREG;
        if(a>=1 && a<=9){
            printf("\nEntered: %d", a);
            break;
        }
    }
    while(1);
    return;
}