#ifndef SPI_H_
#define SPI_H_

// Global Vars

// Used to indicate if SPI has been enabled yet.
int SPI_ENABLED;

char RXBUFF;

// Function Headers
void initSPI(void);
char transferSPI(char data);
char* transferSPIf(char* buf, int len);
char transferRAW(char data);
void sendSPI(int data);
char recvSPI(void);
void CSLO(void);
void CSHI(void);

#endif
