#ifndef ULTRASONIC_HAL_H_
#define ULTRASONIC_HAL_H_	1

#include "hal_common_includes.h"
//#include "uart.h"

typedef enum {
	ultrasonic_right,
	ultrasonic_front,
	ultrasonic_left,
} ultrasonic;

void ultrasonic_init(ultrasonic);
void ultrasonic_all_init();
int ultrasonic_distance(ultrasonic);

void timer3ch_start(ultrasonic num);
void timer3ch_stop(ultrasonic num);

extern int gettimervalue(ultrasonic num);

extern int timerValue1;
extern int timerValue2;
extern int timerValue3;

extern volatile int readflag0;
extern volatile int readflag1;
extern volatile int readflag2;

extern volatile int trigger_flag;  // Holds whether or not a RISING edge has been detected

extern TIM_HandleTypeDef tim3ch1_init;
extern TIM_HandleTypeDef tim3ch2_init;
extern TIM_HandleTypeDef tim3ch3_init;
extern TIM_HandleTypeDef tim4handle;

#endif