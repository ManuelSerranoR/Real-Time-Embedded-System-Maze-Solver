#include "hal_common_includes.h"
#include "board_led.h"
#include "pwm_hal.h"

typedef enum {
	STRAIGHT,
	LEFT,
	RIGHT,
	STOP,
	STRAIGHT_RIGHT,
	STRAIGHT_LEFT,
	STRAIGHT_STRAIGHT_LEFT,
	STRAIGHT_STRAIGHT_RIGHT
} movement_type;

void move(movement_type mov, float duty);