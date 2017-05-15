# Real-Time-Embedded-System-Maze-Solver
This repository contains files written in C for the development of a maze solver car robot at New York University Tandon School of Engineering

Task Accomplished:

- [x] Drivers for PWM for commanding the motors (Completed by **Manuel Serrano**)
- [x] Drivers for reading the ultrasonic sensor (Completed by **Naman Patel**)
- [x] Drivers for reading the encoders (Completed by **Siddharth Arora**)
- [x] Integration of all drivers (Completed by **Naman Patel**)
- [x] Wall Following Algorithm with bang bang controller(Completed by **Manuel Serrano, Naman Patel and Siddharth Arora**)


# Code structure:
The code, as suggested by the TAs, has been divided in accordingly divided in Hardware Abstraction Layer Interface and Hardware Abstraction Layer Source code. Furthermore, the algorithm is placed in the "main" file called MAIN.c.

- **Leds**: located in board_led.c and board_led.h, used as a visual user interface with the robot.
- **Button**: located in button_hal.c and button_hal.h, used to get the car running after pressing reset. This way, we can easily test our robot and stop it when neccesary without needing to take the batteries out.
- **PWM**: located in pwm_hal.c and pwm_hal.h, used to continously regulate the power given to the motors, i.e. speed.
- **Ultrasonic sensors**: located in ultrasonic_hal.c and ultrasonic_hal.h, used to capture the distance from the sensors to the wall. Nota that the interrupts are not handled in these files, but in an interrupt handler file called interrupt_handlers.c and interrupt_handlers.h. This file also manages the interrupt used for the button.

# Algorithm:
Located in MAIN.c, the algorithm in pseodocode does the following:

1. Infinite loop
...Get distances for sensors
...IF front sensor distance >= front low threshold THEN
  
