#include <msp430.h>
#include "adc.h"
#include "spi.h"
#include "timer_a.h"
#include "datalogger.h"
#include "bluetooth.h"
#include <stdio.h>

void formatCmd(char* data, char cmd, char a0, char a1, char a2, char a3, char crc);
int sendCmd(char* data);



int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	volatile int i = 0;

	 //P6DIR |= BIT1;

	 //P6REN = BIT1;
	 //P6OUT &= ~BIT1;

	//printf("test\n");


	InitDataLogger();

	InitTimer();

	//LogData(&a);



	 /*
	 initSPI();

	 volatile char data[6];

	 for(i = 0; i < 6; i++){
	     data[i] = 0;
	 }

	 // Init command for micro sd card.
	 formatCmd(data, 0x40, 0x00, 0x00, 0x00, 0x00, 0x95);


	 CSHI();


	 for(i = 0; i < 20; i++){
	     sendSPI(0xFF);
	 }

	 CSLO();

	 sendSPI(0xFF);

	 sendCmd(data);


	 volatile char response[20];

	 while(1){
	     sendSPI(0xFF);
	 }

	 CSHI();


	 //volatile int x = InitBT();

    */

	 //volatile int b = 0;




	 // Start timer A0
	 //InitTimer();



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














// Fill in given char array with values to make a full command packet.
void formatCmd(char* data, char cmd, char a0, char a1, char a2, char a3, char crc){
    data[0] = cmd | 0x40;
    data[1] = a0;
    data[2] = a1;
    data[3] = a2;
    data[4] = a3;
    data[5] = crc;
}


// Send a given command packet to the Micro SD card.
int sendCmd(char* data){

    int i;

    for(i = 0; i < 6; i++){


        sendSPI(data[i]);


    }

    return 1;


}


