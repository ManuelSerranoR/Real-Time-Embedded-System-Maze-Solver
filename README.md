# Real-Time-Embedded-System-Maze-Solver
This repository contains files written in C for the development of a maze solver car robot at New York University Tandon School of Engineering, using the interface board Release-0.1.

Group Members: **Manuel Serrano (msr542)**, **Michael Shamouilian (mis294)**, **Naman Patel (nkp269)**, **Siddhartha Arora (sa4186)**, **Anusha Sharma (as10553)**

Task Accomplished:

- [x] Drivers for PWM for commanding the motors (Completed by **Manuel Serrano**)
- [x] Drivers for reading the ultrasonic sensor (Completed by **Naman Patel**)
- [x] Drivers for reading the encoders (Completed by **Siddhartha Arora, Anusha Sharma**)
- [x] Integration of all drivers (Completed by **Naman Patel**)
- [x] Wall Following Algorithm with bang bang controller(Completed by **Manuel Serrano, Naman Patel and Siddhartha Arora**)


# Code structure:
The code, as suggested by the TAs, has been divided in accordingly divided in Hardware Abstraction Layer Interface and Hardware Abstraction Layer Source code. Furthermore, the algorithm is placed in the "main" file called MAIN.c.

- **LEDs**: located in board_led.c and board_led.h, used as a visual user interface with the robot.
- **Button**: located in button_hal.c and button_hal.h, used to get the car running after pressing reset. This way, we can easily test our robot and stop it when neccesary without needing to take the batteries out.
- **PWM**: located in pwm_hal.c and pwm_hal.h, used to continously regulate the power given to the motors, i.e. speed.
- **Ultrasonic sensors**: located in ultrasonic_hal.c and ultrasonic_hal.h, used to capture the distance from the sensors to the wall. Nota that the interrupts are not handled in these files, but in an interrupt handler file called interrupt_handlers.c and interrupt_handlers.h. This file also manages the interrupt used for the button.
- **Types of movement:** located in movement_directions.c and movement_directions.h, used to define the duty cycles of every type of movement. These are:
1. STRAIGHT.
2. LEFT.
3. RIGHT.
4. STRAIGHT_LEFT.
5. STRAIGHT_RIGHT.

# Algorithm:
Located in MAIN.c, the algorithm in pseodocode does the following:

1. Infinite loop

----Get distances for sensors

----IF front sensor distance >= front low threshold THEN

--------IF left sensor distance < left low threshold AND right sensor distance > right high threshold THEN
  
------------move straight_right

--------ELSE IF left sensor distance < left high threshold THEN

------------move straight_left

--------ELSE

------------move straight

----ELSE IF front sensor distance < front low threshold THEN

------------move right

----END IF

**Observations:** In the algorithm, we have several mechanisms that help the car drive smooth and turn the appropriate degrees when necessary. First, we are filtering captured values from the sensors to make the reception more accurate. Also, when turning right, we are setting a mechanism that allows us to not stop turning until the desired degrees have been turned.

**YouTube videos:** The following are the links showcasing the trial runs:
1. https://youtu.be/GP3gEITnyiU
2. https://youtu.be/I_ei28f7XuQ

**References:** Part of this project contains pieces of code from https://github.com/Aghosh993/EL6483_EmbeddedSystems. Specially, the HAL of the PWM, button and LEDs.

