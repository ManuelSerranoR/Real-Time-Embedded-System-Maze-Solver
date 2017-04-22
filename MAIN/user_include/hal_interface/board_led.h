#ifndef BOARD_LED_H
#define BOARD_LED_H		1

#include "hal_common_includes.h"

typedef enum {
	LED3,
	LED4,
	LED5,
	LED6,
	LED7,
	LED8,
	LED9,
	LED10
} led;

void board_led_init(void);
void board_led_on(led led_id);
void board_led_off(led led_id);
void board_led_all_on();
//void board_led_toggle(led led_id);

#endif