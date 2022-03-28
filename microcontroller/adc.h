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
void sampleADC(int* samples);
void GetVoltage(float* volts);
void GetTemperature(float* temps);

void initVref(void);
void terminateVref(void);


#endif
