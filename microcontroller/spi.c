#include <msp430.h>
#include "spi.h"

//#define LOOPBACK UCLISTEN
#define LOOPBACK 0

// Initialize SPI
void initSPI(void){



    // Set UCB1STE port to be an output
    P2OUT |= BIT7;
    P2DIR |= BIT7;


    // put eUSCI onto the reset condition in order to configure ports.
    UCB1CTL1 = UCSWRST;

    // Loopback mode
    UCB1STATW |= LOOPBACK;

    // MSB is sent and received first & set to master & synchronous communication & using SMCLK.
    UCB1CTLW0 |= UCMSB | UCMST | UCSYNC | UCSSEL_2 ;// | UCCKPL;

    // Enable interrupt flags for tx and rx buffers.
    UCB1IE |= UCTXIE | UCRXIE;

    // Divide clk by 8. == 1 MHz / 2
    UCB1BRW |= 8;

    // Configure SPI ports
    P3SEL0 |= BIT2;
    P3SEL0 |= BIT5;
    P3SEL0 |= BIT6;



    // take eUSCI out of reset condition.
    UCB1CTL1 &= ~UCSWRST;




    PM5CTL0 &= ~LOCKLPM5;

    SPI_ENABLED = 1;
}


// Transfer data using SPI
char transferSPI(char data){

    while((UCB1STATW & UCBUSY) == UCBUSY);

    sendSPI(data);

    while((UCB1STATW & UCBUSY) == UCBUSY);
    volatile char x = recvSPI();

    return x;
}







// Fill the tx buffer with data to be sent.

void sendSPI(int data){



    while((UCB1IFG & UCTXIFG) != UCTXIFG);



    UCB1TXBUF = data;

    //if ((UCB1IFG & UCTXIFG) == UCTXIFG){

    //}

    /*
    while((UCB1IFG & UCRXIFG) != UCRXIFG || (UCB1STATW & UCOE == UCOE)){

    } */


}


// Read from the rx buffer.
char recvSPI(void){



    while((UCB1IFG & UCRXIFG) != UCRXIFG);

    //while(UCB1STATW & UCBUSY);

    int data = UCB1RXBUF;

    return data;

}




void CSLO(void){
    P2OUT &= ~BIT7;
}

void CSHI(void){
    P2OUT |= BIT7;
}


