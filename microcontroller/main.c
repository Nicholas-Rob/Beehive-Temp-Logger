#include <msp430.h>
#include "adc.h"
#include "spi.h"
#include "timer_a.h"
#include "datalogger.h"
#include "microsd.h"
#include "bluetooth.h"
#include <stdio.h>



int main(void){
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	CSCTL5 |= DIVS_2; // Divide smclk by 4 // (1MHz / 4)
	volatile int i = 0;








	 /*// SD card comm.
	 initSPI();






	 sendReset();

	 __delay_cycles(100);

	 volatile char ver = getVer();


	 sendInit();

	 sendCMD55();

	 writeBlock();

	 */


/*
	initADC();

	int adcValues[3];

	volatile int temp = GetTemperature();

	terminateADC();

	 volatile char bb = 0; // Debug stop */








	 // Log Temperature when timer interrupt flag is set.

	InitDataLogger();

    InitTimer();



     // Enable all interrupts
    _BIS_SR(GIE);

	 while(1){



	     if(TimerIntFlag == 1){



	         TimerIntFlag = 0;


	         LogData(time);


	     }


	 }




	return 0;
}








