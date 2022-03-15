

#ifndef TIMER_A_H_
#define TIMER_A_H_

extern char TimerIntFlag;

extern volatile int t_milliseconds;
extern volatile unsigned char t_seconds;
extern volatile unsigned char t_minutes;
extern volatile unsigned char t_hours;
extern volatile int t_days;

extern unsigned char* time;

void InitTimer(void);


#endif /* TIMER_A_H_ */
