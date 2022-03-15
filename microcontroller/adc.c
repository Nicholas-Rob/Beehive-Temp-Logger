#include <msp430.h>
#include "adc.h"


// Do a full single read from the ADC. [Initialize ADC, Sample ADC, Shutdown ADC]
int readADC(void){
    //initADC();

    int x = sampleADC();

    //terminateADC();

    return x;
}


// Initialize ADC0
void initADC(void){

    // Disable conversion first
    ADCCTL0 &= ~ADCENC;


    // Enable ADC0 pin
    SYSCFG2 |= 0x1;


    // Set ADCON to 1
    ADCCTL0 |= ADCON;

    // Set sampling timer to MODOSC
    ADCCTL1 |= ADCSHP;

    // Set input channel to 0
    ADCMCTL0 &= ~0xF;

    // Set voltage references
    ADCMCTL0 |= ADCSREF_0;


    // Set sample and hold time
    //ADCCTL0 |= ADCSHT_2;


    // Set conversion sequence mode to "single channel, single conversion"
    ADCCTL1 &= ~0x6;


    ADCCTL1 &= ~(0x0C00);

    // Set clk to SMCLK
    ADCCTL1 |= ADCSSEL_0;


    // Set 10 bit resolution
    ADCCTL2 |= ADCRES_1;


    // Enable interrupt
    ADCIE = ADCIE0;

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
int sampleADC(void){



    // Enable ADC conversion and start conversion
    ADCCTL0 |= ADCENC | ADCSC;


    // Wait for ADC to finish taking a sample.
    while ((ADCCTL1 & ADCBUSY) != 1);



    // Read results.
    int x = ADCMEM0;

    // Disable conversion
    ADCCTL0 &= ~ADCENC;



    return x;
}


float GetVoltage(void){

    int adcValue = sampleADC();

    return ((((float)adcValue) / 1023.0) * 3.3);

}


float GetTemperature(void){

    return 0.0f;

    //float t =
}


// Initialize voltage reference registers.
void initVref(void){


    PMMCTL0_H = PMMPW_H;
    PMMCTL2 |= INTREFEN;

    int i = 0;
    for(i = 0; i < 10; i++);
}


// Shutdown use of voltage reference.
void terminateVref(void){

    PMMCTL2 &= ~INTREFEN;
    PMMCTL0_H &= ~PMMPW_H;
}

    ////////////////////////////

