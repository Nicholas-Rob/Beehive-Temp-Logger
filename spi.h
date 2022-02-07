#ifndef SPI_H_
#define SPI_H_

int SPI_ENABLED;

void initSPI(void);
int transferSPI(int data);
void sendSPI(int data);
int recvSPI(void);


#endif
