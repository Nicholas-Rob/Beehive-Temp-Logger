#include <msp430.h>
#include <math.h>
#include "adc.h"



// Do a full single read from the ADC. [Initialize ADC, Sample ADC, Shutdown ADC]
int readADC(void){
    //initADC();

    int x[3];
    sampleADC(x);

    //terminateADC();

    return 0;
}


// Initialize ADC0
void initADC(void){

    P1SEL0 |= BIT2 | BIT1 | BIT0;
    P1SEL1 |= BIT2 | BIT1 | BIT0;

    PM5CTL0 &= ~LOCKLPM5;

    // Disable conversion first
    ADCCTL0 &= ~ADCENC;


    // Enable ADC0 pin
    //SYSCFG2 |= 0x1;


    // Turn ADC on.
    ADCCTL0 |= ADCON;

    // Used for multiple successive conversions over multiple channels.
    //ADCCTL0 |= ADCMSC;

    // Set sampling timer to MODOSC
    ADCCTL1 |= ADCSHP;

    // Set input channel to be A0 to A2 in sequence mode.
    ADCMCTL0 |= ADCINCH_2;

    // Set voltage references
    ADCMCTL0 |= ADCSREF_0;


    // Set sample and hold time
    //ADCCTL0 |= ADCSHT_2;

    // Divide clock
    ADCCTL1 |= ADCDIV_7;

    // Set conversion sequence mode to "sequence-of-channels"
    ADCCTL1 |= ADCCONSEQ_1;

    //ADCCTL1 |= 0x2;//&= ~0x6;

    //ADCCTL1 &= ~(0x0C00);

    // Set clk to SMCLK
    ADCCTL1 |= ADCSSEL_0;


    // Set 10 bit resolution
    ADCCTL2 |= ADCRES_1;


    // Enable interrupt
    ADCIE |= ADCIE0;

    // Set status flag of ADC
    ADC_SET_FLAG = 1;

    // Initialize internal Vref
    initVref();

}


// Shutdown ADC0.
void terminateADC(void){

    // Disable internal Vref
    terminateVref();

    ADCCTL0 &= ~ADCENC;

    ADCCTL0 &= ~ADCON;

    ADC_SET_FLAG = 0;
}



// Sample ADC0.
void sampleADC(int* samples){


    while ((ADCCTL1 & ADCBUSY) == ADCBUSY);

    // Enable ADC conversion and start conversion
    ADCCTL0 |= ADCENC;// | ADCSC;



    int i;
    for(i = 0; i < 3; i++){

        ADCCTL0 |= ADCSC;

    // Wait for ADC to finish taking a sample.
      while ((ADCIFG & ADCIFG0) != ADCIFG0);



    // Read results.
        samples[i] = ADCMEM0;

        __delay_cycles(4000);

    }



    // Disable conversion
    ADCCTL0 &= ~ADCENC;



}


float GetVoltage(void){

    int adcValues[3];

    sampleADC(adcValues);

    float x0 = ((((float)adcValues[2]) / 1023.0) * 3.3);
    float x1 = ((((float)adcValues[1]) / 1023.0) * 3.3);
    float x2 = ((((float)adcValues[0]) / 1023.0) * 3.3);



    return 0.0f;

}


float GetTemperature(void){

    int adcValues[3];

    sampleADC(adcValues);

    volatile float x0 = ((((float)adcValues[2]) / 1023.0f) * 3.3f);
    volatile float x1 = ((((float)adcValues[1]) / 1023.0f) * 3.3f);
    volatile float x2 = ((((float)adcValues[0]) / 1023.0f) * 3.3f);

    volatile float vin = x0 - x2;
    volatile float vout = x1 - x2;

    volatile float v = vout/vin;


    volatile float r_t = 10000.0f * (v/(1.0f-v));

    return (1.0f/((log(r_t/10000.0f))/3380.0f)) - 298.2f;
}


// Initialize voltage reference registers.
void initVref(void){


    PMMCTL0_H = PMMPW_H;
    PMMCTL2 |= INTREFEN; // enable internal reference
    PMMCTL2 |= REFVSEL_2; // set it to 2.5V.

    int i = 0;
    for(i = 0; i < 10; i++);
}


// Shutdown use of voltage reference.
void terminateVref(void){

    PMMCTL2 &= ~INTREFEN;
    PMMCTL0_H &= ~PMMPW_H;
}

    ////////////////////////////

