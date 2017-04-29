#ifndef BUTTON_HAL_H_
#define BUTTON_HAL_H_	1

#include "hal_common_includes.h"

typedef enum {
	button_user
} button;

void button_init(void);
int button_pressed(button b);

extern volatile int button_pressed_flag; 	// Holds whether or not a RISING edge has been detected
											// @wWarning: Access shared between EXTI0 ISR and user code!!


#endif