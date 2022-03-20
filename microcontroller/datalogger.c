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

    P2OUT &= ~BIT4;

    P6DIR |= BIT2;
    P4DIR |= BIT1;
    P3DIR |= BIT1;

    P2DIR |= BIT4;

    PM5CTL0 &= ~LOCKLPM5;
}

void LogData(unsigned char* time){


    P2OUT |= BIT4;

    initADC();

    char sensor = 0;
    for(sensor = 0; sensor < NUM_SENSORS; sensor++){

        P6OUT &= ~BIT2;
        P4OUT &= ~BIT1;
        P3OUT &= ~BIT1;

        if((sensor & 0x1) == 0x1){
            P6OUT |= BIT2;
        }

        if((sensor & 0x2) == 0x2){
            P4OUT |= BIT1;
        }

        if((sensor & 0x4) == 0x4){
            P3OUT |= BIT1;
        }

        /*
        P6OUT |= ((sensor & 0x1) << 2);
        P4OUT |= (sensor & 0x2);
        P3OUT |= (sensor & 0x4) >> 1;
        */



        __delay_cycles(100);

        // Disable internal Vref


        sensor_data[sensor] = GetTemperature();

        //printf("%d: %f\n", sensor, sensor_data[sensor]);

    }



    terminateADC();

    P2OUT &= ~BIT4;


    //float temperature = GetTemperature();


    //AppendMicroSD(time, temperature);




}


