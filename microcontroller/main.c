#include <msp430.h>
#include "adc.h"
#include "spi.h"

void formatCmd(char* data, char cmd, char a0, char a1, char a2, char a3, char crc);
int sendCmd(char* data);

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// Initialize SPI.
	initSPI();


	volatile int i = 0;
	volatile int t = 0;


	// Setup initialization command to be sent to MicroSD card reader.
	int cmd = 0x40;
	int crc = 0x95;

	// Setup command packet.
	char data[6] = {cmd, 0, 0, 0, 0, crc};


	// Send command packet to Micro SD Card.
	t = sendCmd(data);

	// Format a command packet with the given data, insert it into "data" packet.
	formatCmd(data, 8, 0,0,1,0xAA,0x87);


	// Send packet.
	t = sendCmd(data);


	// TODO: Configure timing to match Micro SD card.



	// USED FOR TESTING:
	// Sample voltage at ADC a few times.
	for(i = 0; i < 3; i++){

	    // Sample ADC.
	    volatile int x = readADC();

	    // Convert ADC value into proper voltage value.
	    volatile float v = ((((float)x) / 1023.0) * 3.3);


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

    // Hold the select-enable down to send packet through SPI.
    P2OUT &= ~BIT7;

    transferSPI(0xFF);

    for(i = 0; i < 6; i++){


        transferSPI(data[i]);


    }

    // TODO: Correct the timing for the SPI communication to the Micro SD card.
    int t = transferSPI(0xFF);

    // Set the select-enable back to HIGH.
    P2OUT |= BIT7;


    return t;
}


