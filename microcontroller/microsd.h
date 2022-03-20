
#ifndef MICROSD_H_
#define MICROSD_H_

void AppendMicroSD(char* time, float temperature);
void formatCmd(char* data, char cmd, char a0, char a1, char a2, char a3, char crc);
char transferSD(char* data, char expResp, char tries);
int recvSD(char expResp, char mask);
int sendCmd(char* data);
void sendReset(void);
char getVer(void);
void sendInit(void);
void sendCMD55(void);
void writeBlock(void);



#endif /* MICROSD_H_ */
