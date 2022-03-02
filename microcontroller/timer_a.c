#include <msp430.h>
#include "timer_a.h"

// Timer A0 Setup
//
// Write 1 to the TACLR bit (TACLR = 1) to clear TAxR, clock divider state, and the counter direction.
// If necessary, write initial counter value to TAxR
// Initialize TAxCCRn.
// Apply desired configuration to TAxIV, TAIDEX and TAxCCTLn.
// Apply desired configuration to TAxCTL including to MC bits




volatile int milliseconds = 0;
volatile unsigned char seconds = 0;
volatile unsigned char minutes = 0;
volatile unsigned char hours = 0;


// Initialize Timer A0
void InitTimer(void){

    // Clear Timer A settings.
    TA0CTL |= TACLR;


    // Store the value that the timer should count up to.
    // Is set to 25000 because the clock (SMCLK = 1 MHz) is divided by 8 later in this function (125 KHz).
    // 125 KHz is easily divided by 25000.
    // 5 full counts = 1 second.
    //
    // For clock divide = 8, 5 counts = 1 second
    // TA0CCR0 = 25000;
    //
    // Clock Divide = 8
    // TA0CTL |= ID_3;



    // Store the value that the timer should count up to.
    // Is set to 1000 because the clock (SMCLK = 1 MHz), 1000 ticks = 1 millisecond.
    // For clock divide = 1, 1 count = 1 millisecond
    TA0CCR0 = 1000;

    // Set capture mode to rising edge.
    TA0CCTL0 |= CM_1;

    // Enable CCR0 interrupts.
    TA0CCTL0 |= CCIE;


    // Set timer to use SMCLK as a source.
    TA0CTL |= TASSEL_2;



    // Set timer to count up to the value in TA0CCR0.
    TA0CTL |= MC_1;




}


// Interrupt for TIMERA0
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void){


    // Do event every millisecond


    milliseconds++;




    if(milliseconds == 1000){
        // Do event every second

        // Used to debug timer. Should blink connected LED every second.
        //P6OUT ^= BIT1;

        seconds++;
        milliseconds = 0;
    }

    if(seconds == 60){
        // Do event every minute
        minutes++;
        seconds = 0;
    }

    if(minutes == 60){
        // Do event every hour

        // Log data.

        hours++;
        minutes = 0;
    }


}

