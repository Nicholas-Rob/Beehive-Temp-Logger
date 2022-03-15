#include <msp430.h>
#include "bluetooth.h"
#include "spi.h"

#define BUFSIZE 128 // Incoming data buffer size

int InitBT(void){

    int k = 0;
    for(k = 0; k < 10; k++){
        transferRAW(0xFF);
    }





    CSLO();

    // Delay for 100us. 16 cycles @ 16Mhz for 1us delay.
    __delay_cycles(1600);


    //                msg type   cmd id     payload len         payload
    char initcmd[6] = {0x10,    0x00,0x0A,      0x02,            'a','t'};


    char ret[128];

    int jj = 0;
    for(jj = 0; jj < 128; jj++){
        ret[jj] = 0;
    }


        volatile int ii = 0;
        int i = 0;
        for(i = 0; i < 6; i++){

            volatile char rt = transferSPI(initcmd[i]);
            volatile char ff = 0;
            if(rt != 0){
                ff = 1;
            }

        }
    //volatile char x2[128] = transferSPIf(initcmd, 6);

    volatile int g = 5;

    //char r[2] = {0x00,0x00};

    CSHI();



    while((P6IN & BIT1)){

        CSLO();


        char r = transferRAW(0x00);

        if(r != 0x00){
            ret[ii] = r;
            ii++;
        }

        volatile char nn = 0;
    }

    volatile char n = 0;

    CSHI();

    //free(x2);

    return 0;

}


