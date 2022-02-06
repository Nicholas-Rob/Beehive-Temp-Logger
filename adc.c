#include <msp430.h>
#include "adc.h"


   //*     ADC     *//

int readADC(void){
    initADC();

    int x = sampleADC();

    terminateADC();

    return x;
}

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
    ADCCTL0 |= ADCSHT_2;


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

}


void terminateADC(void){

    ADCCTL0 &= ~ADCENC;

    ADCCTL0 &= ~ADCON;

    ADC_SET_FLAG = 0;
}

int sampleADC(void){

    // Initialize internal Vref
    initVref();

    // Enable ADC conversion and start conversion
        ADCCTL0 |= ADCENC | ADCSC;


    while ((ADCCTL1 & ADCBUSY) != 1);







    // Read results.
    int x = ADCMEM0;

    // Disable conversion
    ADCCTL0 = ADCCTL0 & ~ADCENC;

    // Disable internal Vref
    terminateVref();

    return x;
}


void initVref(void){


    PMMCTL0_H = PMMPW_H;
    PMMCTL2 |= INTREFEN;

    int i = 0;
    for(i = 0; i < 10; i++);
}

void terminateVref(void){

    PMMCTL2 &= ~INTREFEN;
    PMMCTL0_H &= ~PMMPW_H;
}

    ////////////////////////////

