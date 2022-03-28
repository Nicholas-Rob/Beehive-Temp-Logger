#include <msp430.h>
#include "datalogger.h"
#include "adc.h"
#include "microsd.h"
#include <stdio.h>

#define NUM_SENSORS 8

volatile float sensor_data[NUM_SENSORS];

void InitDataLogger(void){

    P6OUT &= ~BIT2;
    P4OUT &= ~BIT1;
    P3OUT &= ~BIT1;

    P2OUT &= ~BIT1;

    P6DIR |= BIT2;
    P4DIR |= BIT1;
    P3DIR |= BIT1;

    P2DIR |= BIT1;

    PM5CTL0 &= ~LOCKLPM5;
}

void LogData(unsigned char* time){


    P2OUT |= BIT1;

    volatile float sensors[12];

    volatile char t[2];
    t[0] = time[0];
    t[1] = time[1];

    initADC();

    char sensor = 0;




        __delay_cycles(100);

        GetTemperature(sensors);




    terminateADC();

    P2OUT &= ~BIT1;


    volatile int aaf = 2;





}


