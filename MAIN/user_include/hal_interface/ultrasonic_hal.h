#ifndef ULTRASONIC_HAL_H_
#define ULTRASONIC_HAL_H_	1

#include "hal_common_includes.h"
#include "uart.h"

typedef enum {
	ultrasonic_right,
	ultrasonic_front,
	ultrasonic_left,
} ultrasonic;

void ultrasonic_init(ultrasonic);
int ultrasonic_distance(ultrasonic);

int timerValue1;
int timerValue2;
int timerValue3;

static volatile int readflag0=0;
static volatile int readflag1=0;
static volatile int readflag2=0;

#endif