#include "interrupt_handlers.h"

volatile int button_pressed_flag;

int timerValue1;
int timerValue2;
int timerValue3;

volatile int readflag0;
volatile int readflag1;
volatile int readflag2;

//volatile int trigger_flag;  // Holds whether or not a RISING edge has been detected

TIM_HandleTypeDef tim3ch1_init;
TIM_HandleTypeDef tim3ch2_init;
TIM_HandleTypeDef tim3ch3_init;
TIM_HandleTypeDef tim4handle;

void EXTI15_10_IRQHandler(void) {

    /* Make sure that interrupt flag is set */

    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11); 	// This function will first clear the IRQ on EXTI11
											// It will then call the HAL_GPIO_EXTI_Callback below
}


void EXTI9_5_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6); 	// This function will first clear the IRQ on EXTI6
											// It will then call the HAL_GPIO_EXTI_Callback below
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9); 	// This function will first clear the IRQ on EXTI6
											// It will then call the HAL_GPIO_EXTI_Callback below
}

/*
void TIM4_IRQHandler(void)
{
 // printf("EXTIDetected\r\n");
  HAL_TIM_IRQHandler(&tim4handle);
}*/

void EXTI0_IRQHandler(void)
{
	//printf("Detected\r\n");
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0); 	// This function will first clear the IRQ on EXTI0
											// It will then call the HAL_GPIO_EXTI_Callback below
}

/*
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
 //printf("EXTICallbackDetected\r\n");
  trigger_flag=1;
}*/
/*
	User code section of the EXTI IRQ, called from HAL_GPIO_EXTI_IRQHandler
	after interrupt flags are cleared:
 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_6) // This means we're sure we've gotten an EXTI event on pin 0
	{
		if(HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_6) == GPIO_PIN_SET) // If the pin is high now, it must've been a
																// RISING edge we captured
		{
			//start timer
			timer3ch_start(ultrasonic_front);
		}
		else
		{
			//end timer
			timerValue2 = gettimervalue(ultrasonic_front);
			timer3ch_stop(ultrasonic_front);
			readflag1=1;
		}
	}

	if(GPIO_Pin == GPIO_PIN_11) // This means we're sure we've gotten an EXTI event on pin 0
	{
		if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11) == GPIO_PIN_SET) // If the pin is high now, it must've been a
																// RISING edge we captured
		{
			//start timer
			timer3ch_start(ultrasonic_right);	
		}
		else
		{
			//end timer
			timerValue1 = gettimervalue(ultrasonic_right);
			timer3ch_stop(ultrasonic_right);
			readflag0=1;
		}
	}

	if(GPIO_Pin == GPIO_PIN_9) // This means we're sure we've gotten an EXTI event on pin 0
	{
		if(HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_9) == GPIO_PIN_SET) // If the pin is high now, it must've been a
																// RISING edge we captured
		{
			//start timer
			timer3ch_start(ultrasonic_left);
		}
		else
		{
			//end timer
			timerValue3 = gettimervalue(ultrasonic_left);
			timer3ch_stop(ultrasonic_left);
			readflag2=1;
		}
	}
	
	if(GPIO_Pin == GPIO_PIN_0) // This means we're sure we've gotten an EXTI event on pin 0
	{
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) // If the pin is high now, it must've been a
																// RISING edge we captured
																// I.e. the button was PRESSED
		{
			button_pressed_flag = 1; // Set the flag since we've detected a button press event
		}
	}
	
}