#include <msp430.h>
#include "spi.h"

//#define LOOPBACK UCLISTEN
#define LOOPBACK UCLISTEN

// Initialize SPI
void initSPI(void){



    // Set UCB1STE port to be an output
    P2OUT |= BIT7;
    P2DIR |= BIT7;

    /*
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
    P3SEL0 = BIT2;
    P3SEL0 = BIT5;
    P3SEL0 = BIT6;



    // take eUSCI out of reset condition.
    UCB1CTL1 &= ~UCSWRST;

    */


    // put eUSCI onto the reset condition in order to configure ports.
        UCA0CTL1 = UCSWRST;

        // Loopback mode
        UCA0STATW |= LOOPBACK;

        // MSB is sent and received first & set to master & synchronous communication & using SMCLK.
        UCA0CTLW0 |= UCMSB | UCMST | UCSYNC | UCSSEL_3 ;// | UCCKPL;

        // Enable interrupt flags for tx and rx buffers.
        //UCA0IE |= UCTXIE | UCRXIE;

        // Divide clk by 8. == 1 MHz / 2
        UCA0BRW |= 8;

        // Configure SPI ports
        P5SEL0 = BIT0;
        P5SEL0 = BIT1;
        P5SEL0 = BIT2;



        // take eUSCI out of reset condition.
        UCA0CTL1 &= ~UCSWRST;

    PM5CTL0 &= ~LOCKLPM5;

    SPI_ENABLED = 1;
}


// Transfer data using SPI
char transferSPI(char data){

    sendSPI(data);

    volatile char x = recvSPI();

    return x;
}


char* transferSPIf(char* buf, int len){

    char* ret = (char*)malloc(sizeof(char)*128);


    volatile int ii = 0;
    int i = 0;
    for(i = 0; i < len; i++){

        sendSPI(buf[i]);

        volatile char resp = recvSPI();

        ret[i] = resp;

        /*

        if(resp != 0x00){
            ret[ii] = resp;
            ii++;
        }

        volatile int g = 5;
        */

    }

    return ret;


}


char transferRAW(char data){

    while((UCB1IFG & UCTXIFG) != UCTXIFG);

    UCB1TXBUF = data;



    while((UCB1IFG & UCRXIFG) != UCRXIFG);


    volatile int res = UCB1RXBUF;

    volatile int tets = data;

    while(UCB1STAT & UCBUSY);

    volatile char dummy = UCB1RXBUF;

    return res;

}

// Fill the tx buffer with data to be sent.
/*
void sendSPI(int data){



    volatile int t = UCB1TXBUF;




    while((UCB1IFG & UCTXIFG) != UCTXIFG);



    UCB1TXBUF = data;

    if ((UCB1IFG & UCTXIFG) == UCTXIFG){

    }

    while((UCB1IFG & UCRXIFG) != UCRXIFG || (UCB1STATW & UCOE == UCOE)){

    }

   // while((UCB1IFG & UCTXIFG) != UCTXIFG);
    //while(UCB1STATW & UCBUSY);
}


// Read from the rx buffer.
char recvSPI(void){





    while((UCB1IFG & UCRXIFG) != UCRXIFG);
    while(UCB1STATW & UCBUSY);

    int data = UCB1RXBUF;

    return data;

}
*/

void sendSPI(int data){




    while((UCA0IFG & UCTXIFG) != UCTXIFG);



    UCA0TXBUF = data;

    if ((UCA0IFG & UCTXIFG) == UCTXIFG){

    }

    while((UCA0IFG & UCRXIFG) != UCRXIFG || (UCA0STATW & UCOE == UCOE)){

    }

   // while((UCB1IFG & UCTXIFG) != UCTXIFG);
    //while(UCB1STAT & UCBUSY);
}


// Read from the rx buffer.
char recvSPI(void){





    while((UCA0IFG & UCRXIFG) != UCRXIFG);
    while(UCA0STATW & UCBUSY);

    int data = UCA0RXBUF;

    return data;

}

void CSLO(void){
    P2OUT &= ~BIT7;
}

void CSHI(void){
    P2OUT |= BIT7;
}

/*
#pragma vector=EUSCI_A0_VECTOR
__interrupt void SPI_int(void){

    if(UCA0IV != 0x0002){
        return;
    }

    RXBUFF = UCA0RXBUF;

    CSHI();

    volatile int b = 0;


}
*/
