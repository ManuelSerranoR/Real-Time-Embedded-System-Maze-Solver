/*
  This is the main user software application
  In this case, we have below the code necessary to use PWM with LEDs on an STM32 F3 Discovery PCB.

  (c) Abhimanyu Ghosh, 2017
 */

// C standard include(s):
#include <math.h>
#include <stdio.h>
// Custom user APIs needed for hardware access specific to this board:
#include "cpu.h"
#include "board_led.h"
#include "movement_directions.h"
#include "interrupt_handlers.h"
#include "uart.h"
//#include "ultrasonic_hal.h"
//#include "pwm_hal.h"
//#include "button_hal.h"
//#include "button_hal.h"
// #include "board_led.h"
// Custom user APIs needed for generic algorithmic libraries that are hardware-independent:
#include "foo.h"

#define front_threshold 17
#define left_threshold  15
#define right_threshold 15
#define DUTY 0.5f

int main()
{

  //Initialize the PLL, clock tree to all peripherals, flash and Systick 1 ms time reference
  cpu_init();

  uart_debug_init();

  button_init();
  setvbuf(stdin,NULL,_IONBF,0);   // Sets stdin in unbuffered mode (normal for usart com)
  setvbuf(stdout,NULL,_IONBF,0);  // Sets stdin in unbuffered mode (normal for usart com)

  board_led_init();

  int distance_right,distance_front,distance_left;

  printf("Hello World!!\r\n");

  board_led_all_on();
  while(!button_pressed(button_user));
  board_led_all_off();

  init_pwm();
  ultrasonic_all_init();

  /*
  Left wall following

  0 means too close
  1 means too far
  USL USR USF   Output
  0   0   0     Deadend. Take right
  0   0   1     Go straight
  0   1   0     Take a right
  0   1   1     Go straight (While moving right)
  1   0   0     Take a left
  1   0   1     Go Straight
  1   1   0     Take a left
  1   1   1     Go straight

  */
  while(1)
  {
    distance_right=ultrasonic_distance(ultrasonic_right);
    distance_front=ultrasonic_distance(ultrasonic_front);
    distance_left=ultrasonic_distance(ultrasonic_left);

    if(distance_front>=front_threshold)
    {
      if(distance_left<left_threshold && distance_right>=right_threshold)
      {
        move(STRAIGHT_RIGHT, DUTY);
      }
      else
        move(STRAIGHT,DUTY);
    }
    else
    {
      if(distance_left>=left_threshold)
      {
        move(LEFT,DUTY);
      }
      else
      {
        move(RIGHT,DUTY);
      }
    }
  }
  /*
  while(1)
  {
    distance_right=ultrasonic_distance(ultrasonic_right);
    printf("Distance Right: %d\r\n",distance_right);

    distance_front=ultrasonic_distance(ultrasonic_front);
    printf("Distance Front: %d\r\n",distance_front);

    distance_left=ultrasonic_distance(ultrasonic_left);
    printf("Distance Left: %d\r\n",distance_left);  
   
  }*/
  /*
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
  move(STRAIGHT,0.3f);
  while(!button_pressed(button_user));
  move(LEFT.0.3f);
  while(!button_pressed(button_user));
  move(RIGHT.0.3f);
  while(!button_pressed(button_user));
  move(STOP.0.3f);
  while(!button_pressed(button_user));
  //board_led_on(LED6);
  //board_led_on(LED7);
  */

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
