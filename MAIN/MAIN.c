/*
  This is the main user software application
  In this case, we have below the code necessary to use PWM with LEDs on an STM32 F3 Discovery PCB.

  (c) Abhimanyu Ghosh, 2017
 */

// C standard include(s):
#include <math.h>

// Custom user APIs needed for hardware access specific to this board:
#include "cpu.h"
#include "board_led.h"
#include "pwm_hal.h"
#include "button_hal.h"
#include "movement_directions.h"
// Custom user APIs needed for generic algorithmic libraries that are hardware-independent:
#include "foo.h"


int main()
{

  //Initialize the PLL, clock tree to all peripherals, flash and Systick 1 ms time reference
  cpu_init();

  //Initialize all LEDs (from LED3 to LED10)
  board_led_init();

  //Initialize user button
  button_init();

  //Initialize the PWM outputs for PD3, PD4, PD6, PD7:
  init_pwm();

  board_led_all_on();
  while(!button_pressed(button_user));
  board_led_all_off();

  //THIS IS JUST TO CHECK THAT IT IS WORKING. In real application there is no need of pushing buttons
  move(STRAIGHT);
  while(!button_pressed(button_user));
  move(LEFT);
  while(!button_pressed(button_user));
  move(RIGHT);
  while(!button_pressed(button_user));
  move(STOP);
  while(!button_pressed(button_user));
  //board_led_on(LED6);
  //board_led_on(LED7);


  int i = 0;

  while(1)
  {
    //If this fails, some hardware or serious problem is going on
    if(TEST_FOO(i, i+1) < 0)
    {
      while(1);
    }
    
    else
    {
    
    }
  }

  return 0;
}
