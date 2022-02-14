#include <msp430.h>
#include "adc.h"



/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	



	int i = 0;

	for(i = 0; i < 3; i++){

	    int x = readADC();

	    float v = ((((float)x) / 1023.0) * 3.3);



	    // For some reason these print statements have to be here so that I can view the values of my float variable.
	    // The print statements don't even print anything
	    printf("hi");

	    printf("%d %f\n", x, v);

    }



	return 0;
}





