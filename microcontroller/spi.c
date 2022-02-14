#include <msp430.h>
#include "spi.h"



void initSPI(void){

    // Set UCB1STE port to be an output
    P2OUT |= BIT7;
    P2DIR |= BIT7;

    P3SEL0 = BIT2;
    P3SEL0 = BIT5;
    P3SEL0 = BIT6;

    // put eUSCI onto the reset condition in order to configure ports.
    UCB1CTL1 = UCSWRST;

    // MSB is sent and received first & set to master & synchronous communication & using SMCLK.
    UCB1CTLW0 |= UCMSB | UCMST | UCSYNC | UCSSEL_2;

    // Enable interrupt flags for tx and rx buffers.
    UCB1IE |= UCTXIE | UCRXIE;

    UCB1BRW = 8;

    // take eUSCI out of reset condition.
    UCB1CTL1 &= ~UCSWRST;

    SPI_ENABLED = 1;
}

int transferSPI(int data){

    P2OUT &= ~BIT7;

    sendSPI(data);
    int x = recvSPI();

    P2OUT |= BIT7;

    return x;
}


void sendSPI(int data){

    if(!SPI_ENABLED){
        return ;
    }

    while((UCB1IFG & UCTXIFG) != UCTXIFG);

    UCB1TXBUF = data;
}

int recvSPI(void){

    if(!SPI_ENABLED){
        return 0;
    }

    while((UCB1IFG & UCRXIFG) != UCRXIFG);

    int data = UCB1RXBUF;

    return data;

}


