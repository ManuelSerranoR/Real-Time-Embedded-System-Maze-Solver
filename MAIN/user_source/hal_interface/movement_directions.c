#include "movement_directions.h"

void move(movement_type mov){
	switch(mov)
	{
		case STRAIGHT:
			//BOTH MOTORS RUN CLOCKWISE
			board_led_all_off();
			board_led_on(LED10);
			set_pwm(PD3, 0.0f);
  			set_pwm(PD4, 0.3f);
  			set_pwm(PD6, 0.0f);
  			set_pwm(PD7, 0.3f);
			break;

		case LEFT:
			board_led_all_off();
			board_led_on(LED7);
			set_pwm(PD3, 0.3f);
  			set_pwm(PD4, 0.0f);
  			set_pwm(PD6, 0.0f);
  			set_pwm(PD7, 0.3f);
			break;

		case RIGHT:
			board_led_all_off();
			board_led_on(LED6);
			set_pwm(PD3, 0.0f);
  			set_pwm(PD4, 0.3f);
  			set_pwm(PD6, 0.3f);
  			set_pwm(PD7, 0.0f);
			break;

		case STOP:
			board_led_all_off();
			board_led_on(LED3);
			set_pwm(PD3, 0.0f);
  			set_pwm(PD4, 0.0f);
  			set_pwm(PD6, 0.0f);
  			set_pwm(PD7, 0.0f);
			break;

	}		
}