#include "microsd.h"
#include "spi.h"

void AppendMicroSD(char* time, float temperature){

    /*
    Write(time[0]); // Minute
    Write(time[1]); // Hour
    Write(time[2]); // Day
    Write(time[3]); // Month
    Write(time[4]); // Year

    Write(temperature);
    */

}


char transferSD(char* data, char expResp, char tries){
    char i = 0;



             CSHI();

             for(i = 0; i < 1; i++){
                 transferSPI(0xFF);
             }


             char x;

             CSLO();

             if(tries == 0){
                 x = 1;
             }else{
                 x = 0;
             }

             while(x != tries){


             transferSPI(0xFF);

             sendCmd(data);


             //transferSPI(0xFF);

             int resp = recvSD(expResp, 0xFF);

             if((resp & 0x100) == 0x100){
                 x++;

                 continue;
             }


             CSHI();

             return resp & 0xFF;


             }


             return 0x55;

}


int recvSD(char expResp, char mask){
    volatile char resp = transferSPI(0xFF);

    int timeout = 0;
    int MAX_TO = 400;
    //while((resp == 0xFF  || resp == 0x00) && timeout < 10){

    /*
    while(resp == 0x00){
        resp = transferSPI(0xFF);
    }*/

    volatile char r[400];

    if(expResp == 0xFF){
     while(resp == 0xFF && timeout < MAX_TO){

         resp = transferSPI(0xFF);
         r[timeout] = resp;
         timeout++;
     }
    }
    else{
     while((resp & mask) != expResp && timeout < MAX_TO){

         resp = transferSPI(0xFF);
         r[timeout] = resp;
         timeout++;
     }
    }



    if(timeout == MAX_TO){

        return 0x100;
    }

    volatile char cc = 5;

    return resp;

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


        transferSPI(data[i]);


    }


    volatile char b = 5;
    return 1;


}



void sendReset(void){

    char i = 0;

    volatile char data[6];

     for(i = 0; i < 6; i++){
         data[i] = 0;
     }



    // Init command for micro sd card.
     formatCmd(data, 0x40, 0x00, 0x00, 0x00, 0x00, 0x95);

     volatile char ccc = transferSD(data, 0x01, 0);

     volatile char gg = 5;


}



char getVer(void){
    char i = 0;

        volatile char data[6];

             for(i = 0; i < 6; i++){
                 data[i] = 0;
             }


        // Init command for micro sd card.
             formatCmd(data, 0x48, 0x00, 0x00, 0x01, 0xAA, 0x87);

             return transferSD(data, 0x01, 0);

             /*
             CSHI();

             for(i = 0; i < 20; i++){
                 transferSPI(0xFF);
             }




             CSLO();

             while(1){


             transferSPI(0xFF);

             sendCmd(data);


             //transferSPI(0xFF);



             volatile char resp = transferSPI(0xFF);

             int timeout = 0;
             //while((resp == 0xFF  || resp == 0x00) && timeout < 10){
             while(resp != 0x01 && timeout < 10){
                 timeout++;
                 resp = transferSPI(0xFF);
             }

             if(timeout == 10){
                 continue;
             }

             CSHI();

             return resp;


             for(i = 0; i < 2; i++){
                 response[i] = transferSPI(0xFF);
             }



             if(response[0] == 0x01 || response[0] == 0x05){
                 CSHI();
                 return response[0];
             }

             if(response[1] == 0x01 || response[1] == 0x05){
                 CSHI();
                 return response[1];
             }




             }

    */



}




void sendInit(void){
    char i = 0;

        volatile char data[6];

        for(i = 0; i < 6; i++){
            data[i] = 0;
        }


        // Init command for micro sd card.
        formatCmd(data, 0x08, 0x00, 0x00, 0x01, 0xAA, 0x87);


        transferSD(data, 0x00, 0);

             /*
             CSHI();

             for(i = 0; i < 20; i++){
                 transferSPI(0xFF);
             }




             CSLO();

             while(1){


             transferSPI(0xFF);

             sendCmd(data);


             transferSPI(0xFF);






             for(i = 0; i < 2; i++){
                 response[i] = transferSPI(0xFF);
             }



             if(response[0] == 0x01 || response[1] == 0x01){
                 continue;
             }

             if(response[0] == 0x00 || response[1] == 0x00){
                 CSHI();
                 return;
             }






       }
       */




}





void sendCMD55(void){
    char i = 0;

        volatile char data[6];
        char data2[6];

             for(i = 0; i < 6; i++){
                 data[i] = 0;
                 data2[i] = 0;
             }





        // Init command for micro sd card.
             formatCmd(data, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00);
             formatCmd(data2, 0x29, 0x40, 0x00, 0x00, 0x00, 0x00);

             char resp = 0xFF;

             while(resp != 0x00){
             resp = transferSD(data, 0x00, 1);
             resp = transferSD(data2, 0x00, 1);

             }
             /*
             CSHI();

             for(i = 0; i < 20; i++){
                 transferSPI(0xFF);
             }




             CSLO();

             while(1){


             transferSPI(0xFF);

             sendCmd(data);


             transferSPI(0xFF);

             CSHI();
             __delay_cycles(100);

             transferSPI(0xFF);
             CSLO();

             transferSPI(0xFF);

             sendCmd(data2);

             transferSPI(0xFF);






             for(i = 0; i < 2; i++){
                 response[i] = transferSPI(0xFF);
             }

             if(response[0] == 0xFF || response[1] == 0xFF){
                 volatile char ccc = 5;
             }

             if(response[0] == 0x01 || response[1] == 0x01){
                 continue;
             }

             if(response[0] == 0x00 || response[1] == 0x00){
                 CSHI();
                 break;
             }






       }

*/

}




void writeBlock(void){


    char i = 0;

    volatile char data[6];

    for(i = 0; i < 6; i++){
        data[i] = 0;
    }





    // Init command for micro sd card.
    formatCmd(data, 24, 0x00, 0x00, 0x00, 0x01, 0xFF);


    char resp = 0xFF;

    while(resp != 0x00){
        resp = transferSD(data, 0xFF, 1);

    }

    //0xFE

    sendSPI(0xFE);
    sendSPI(0x55);

    sendSPI(0xFF);
    sendSPI(0xFF);


    resp = recvSD(0x05, 0x1F);


    volatile int aa = resp;


}



