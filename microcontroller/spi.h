#ifndef SPI_H_
#define SPI_H_

// Global Vars

// Used to indicate if SPI has been enabled yet.
int SPI_ENABLED;


// Function Headers
void initSPI(void);
int transferSPI(int data);
void sendSPI(int data);
int recvSPI(void);


#endif
