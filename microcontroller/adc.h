#pragma once
#ifndef _ADC
#define _ADC

// Global Vars

// Used to indicate if ADC has been initialized yet.
char ADC_SET_FLAG;


// Function Headers
int readADC(void);
void initADC(void);
void terminateADC(void);
int sampleADC(void);

void initVref(void);
void terminateVref(void);


#endif
