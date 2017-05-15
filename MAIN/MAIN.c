/*
  This is the main user software application
  In this case, we have below the code necessary to do wall-following using Ultrasonic sensor

  (c) Naman Patel and Manuel Serrano, 2017
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


#define front_low_threshold 12
#define left_low_threshold  9
#define right_low_threshold 9

#define front_high_threshold 35
#define left_high_threshold  11.5
#define right_high_threshold 11.5

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

  int distance_right, distance_front, distance_left;

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
  1   0   1     Go straight (While moving left)
  1   1   0     Take a left
  1   1   1     Go straight
  */
  int flag_turn = 0;
  int flag_begin = 1;
  int flag_filter=0;

  while(1)
  {
    distance_right=ultrasonic_distance(ultrasonic_right);
    distance_front=ultrasonic_distance(ultrasonic_front);
    distance_left=ultrasonic_distance(ultrasonic_left);

    if(distance_front>=front_low_threshold && flag_turn == 0)
      {
        flag_filter=0;
        
        if(distance_left<left_low_threshold && distance_right>right_high_threshold)
          move(STRAIGHT_RIGHT, DUTY);
        else if(distance_left>left_high_threshold)
          move(STRAIGHT_LEFT,DUTY);
        else
          move(STRAIGHT,DUTY);
      }

    else if((distance_front<front_low_threshold || flag_turn == 1) && flag_filter==1)
      {
        flag_filter=0;    
        flag_turn = 1;
        move(RIGHT, DUTY);
        if(distance_front >= front_high_threshold)    
          flag_turn = 0;
      }

    else if((distance_front<front_low_threshold || flag_turn == 1) && flag_filter==0)
    {
      flag_filter=1;
    }
  }

  return 0;
}
