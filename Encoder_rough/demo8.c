/*
	This is the main user software application
	In this case, we have below the code necessary to toggle a set of LEDs on a	STM32 F3 Discovery PCB 
  in response to an EXTI (External Interrupt) occurring when a GPIO changes state due to the USER (Blue) 
  button being pressed/released.

	(c) Abhimanyu Ghosh, 2017
 */

#include "cpu.h"
#include "board_led.h"
#include "button_hal.h"

#include "foo.h"
extern int count;

int main()
{
   
  /*
    Initialize the PLL, clock tree to all peripherals, flash and Systick 1 ms time reference:
   */
  cpu_init();
  /*
    Initialize the GPIO (General-Purpose I/O) subsystem pins that are connected to the LEDs on the board:
   */
  board_led_init();

  int i = 0;

  /*
    Set up the USER button on the Discovery board (PA0) as an EXTI line, sensitive to both RISING
    and FALLING edges.
   */
  button_init();

  /*
    wait for the USER button to be pressed before starting the main infinite loop...
   */
  // while(!button_pressed(button_user))
  // {
  //   count = count +1;
  // }

  /*
    In an infinite loop, keep toggling the LEDs in an alternating pattern:
   */
  while(1)
  {
    /*
      Carry out a simple unit test of foo() declared in foo.h:
     */
    if(TEST_FOO(i, i+1) < 0)
    {
      /*
        If the above fails there is either a hardware, code or other undefined error.
        Now we're in an undefined state regarding processor core behavior...
       */
      while(1); // We probably have had a radiation hit or a major malfunction on the ALU of the processor...
    }
    else
    {

        //  if(button_pressed(button_user) == 1)
        // {
        //    count = count +1;
        //    cpu_sw_delay(50U);  
        // }



          if(button_pressed(button_user) > 50)
        {
          board_led_on(LED1);
          board_led_off(LED2);

          cpu_sw_delay(50U);  // Invoke a simple software busy-wait routine to delay approximately 50 milliseconds

          board_led_off(LED1);
          board_led_on(LED2);

          cpu_sw_delay(50U);

            // Increment i for the next test iteration...
        }
        ++i;
    } 
  }


  return 0;
}
