#include "ultrasonic_hal.h"

void timer3ch_start(ultrasonic num)
{
	//__HAL_RCC_TIM3_CLK_ENABLE();
	
	switch(num)
	{
		case ultrasonic_right:
			tim3ch1_init.Instance = TIM3;
			tim3ch1_init.Channel = HAL_TIM_ACTIVE_CHANNEL_1;
			tim3ch1_init.Init.CounterMode = TIM_COUNTERMODE_UP;
			tim3ch1_init.Init.ClockDivision = 0U;
			tim3ch1_init.Init.Prescaler = 71;
			tim3ch1_init.Init.Period = 65535; //23200 max
			tim3ch1_init.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

			HAL_TIM_Base_Init(&tim3ch1_init);
			__HAL_TIM_SET_COUNTER(&tim3ch1_init,0);
			HAL_TIM_Base_Start(&tim3ch1_init);
			break;

		case ultrasonic_front:
			tim3ch2_init.Instance = TIM3;
			tim3ch2_init.Channel = HAL_TIM_ACTIVE_CHANNEL_2;
			tim3ch2_init.Init.CounterMode = TIM_COUNTERMODE_UP;
			tim3ch2_init.Init.ClockDivision = 0U;
			tim3ch2_init.Init.Prescaler = 71;
			tim3ch2_init.Init.Period = 65535; //23200 max
			tim3ch2_init.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

			HAL_TIM_Base_Init(&tim3ch2_init);
			__HAL_TIM_SET_COUNTER(&tim3ch2_init,0);
			HAL_TIM_Base_Start(&tim3ch2_init);
			break;

		case ultrasonic_left:
			tim3ch3_init.Instance = TIM3;
			tim3ch3_init.Channel = HAL_TIM_ACTIVE_CHANNEL_3;
			tim3ch3_init.Init.CounterMode = TIM_COUNTERMODE_UP;
			tim3ch3_init.Init.ClockDivision = 0U;
			tim3ch3_init.Init.Prescaler = 71;
			tim3ch3_init.Init.Period = 65535; //23200 max
			tim3ch3_init.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

			HAL_TIM_Base_Init(&tim3ch3_init);
			__HAL_TIM_SET_COUNTER(&tim3ch3_init,0);
			HAL_TIM_Base_Start(&tim3ch3_init);
			break;
	}
}

void timer3ch_stop(ultrasonic num)
{
	switch(num)
	{
		case ultrasonic_right:
			HAL_TIM_Base_DeInit(&tim3ch1_init);
			break;

		case ultrasonic_front:
			HAL_TIM_Base_DeInit(&tim3ch2_init);
			break;

		case ultrasonic_left:
			HAL_TIM_Base_DeInit(&tim3ch3_init);
			break;
	}
}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* TIMx Peripheral clock enable */
  __HAL_RCC_TIM3_CLK_ENABLE();
  __HAL_RCC_TIM4_CLK_ENABLE();
  
  /*##-2- Configure the NVIC for TIMx ########################################*/
  /* Set Interrupt Group Priority */ 
  /* Set Interrupt Group Priority */
  /* 
  if(htim->Instance==TIM4)
  {
  	HAL_NVIC_SetPriority(TIM4_IRQn, 6, 0);
  	//Enable the TIMx global Interrupt
  	HAL_NVIC_EnableIRQ(TIM4_IRQn);
  }*/
}

void timer_echostart()
{
	//__HAL_RCC_TIM4_CLK_ENABLE();

	tim4handle.Instance = TIM4;

	tim4handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim4handle.Init.ClockDivision = 0U;
	tim4handle.Init.Prescaler = 71U;
	tim4handle.Init.Period = 30U; //23200 max
	tim4handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	HAL_TIM_Base_Init(&tim4handle);
	//HAL_TIM_Base_Start_IT(&tim3ch4_init); 

	__HAL_TIM_SET_COUNTER(&tim4handle,0);

  	
	HAL_TIM_Base_Start(&tim4handle);

}

void timer_echostop()
{
	HAL_TIM_Base_DeInit(&tim4handle);
}


int gettimervalue(ultrasonic num)
{
		if(num==ultrasonic_right)
			return __HAL_TIM_GET_COUNTER(&tim3ch1_init);
			
		if(num==ultrasonic_front)
			return __HAL_TIM_GET_COUNTER(&tim3ch2_init);

		if(num==ultrasonic_left)
			return __HAL_TIM_GET_COUNTER(&tim3ch3_init);
	return 0;
	
}


/*
				Trigger		Echo 
Ultrasonic 0	PE10		PE11	Right
Ultrasonic 1	PA12		PF6		Front
Ultrasonic 2	PA11		PA13	Left
Ultrasonic 1	PD0		    PF6		Front
Ultrasonic 2	PB0		    PF9	    Left
Trigger 10us TTL pulse
Echo Detect TTL us/58=centimeters
*/
static void ultrasonic_gpio_init(ultrasonic num)
{
	static GPIO_InitTypeDef  GPIO_InitStruct;

	switch(num)
	{
		case ultrasonic_right:
			GPIO_InitStruct.Pin = GPIO_PIN_10;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

			__HAL_RCC_GPIOE_CLK_ENABLE(); // Enable clock to GPIOE

			HAL_GPIO_Init(GPIOE, &GPIO_InitStruct); // Done

			GPIO_InitStruct.Pin = GPIO_PIN_11;
			GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

			HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
			break;
		case ultrasonic_front:
			GPIO_InitStruct.Pin = GPIO_PIN_0;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

			__HAL_RCC_GPIOD_CLK_ENABLE(); // Enable clock to GPIOA

			HAL_GPIO_Init(GPIOD, &GPIO_InitStruct); // Done

			GPIO_InitStruct.Pin = GPIO_PIN_6;
			GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

			__HAL_RCC_GPIOF_CLK_ENABLE(); // Enable clock to GPIOF

			HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
			break;
		case ultrasonic_left:
			GPIO_InitStruct.Pin = GPIO_PIN_0;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

			__HAL_RCC_GPIOB_CLK_ENABLE(); // Enable clock to GPIOA

			HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); // Done

			GPIO_InitStruct.Pin = GPIO_PIN_9;
			GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
			GPIO_InitStruct.Pull = GPIO_PULLDOWN;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

			__HAL_RCC_GPIOF_CLK_ENABLE(); // Enable clock to GPIOA

			HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
			break;
	}
}



void ultrasonic_init(ultrasonic num)
{
	ultrasonic_gpio_init(num);	// set up the PA0 GPIO pin so it can connect to the edge detection subsystem
	switch(num)
	{
	case ultrasonic_front:
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 3, 4); // Set the priority according to the application needs
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn); // Enable (un-mask) the EXTI0 interrupt in the NVIC
	break;

	case ultrasonic_right:
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 4, 4); // Set the priority according to the application needs
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn); // Enable (un-mask) the EXTI0 interrupt in the NVIC
	break;

	case ultrasonic_left:
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 5, 4); // Set the priority according to the application needs
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn); // Enable (un-mask) the EXTI0 interrupt in the NVIC
	break;
	}

}

void ultrasonic_all_init()
{
  ultrasonic_init(ultrasonic_right);
  ultrasonic_init(ultrasonic_front);
  ultrasonic_init(ultrasonic_left);
}

void ultrasonic_trigger(ultrasonic num)
{
	if (num==ultrasonic_front)
	{
	//trigger_flag=0;

	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET);
	timer_echostart();
	while(__HAL_TIM_GET_COUNTER(&tim4handle)<10);
	timer_echostop();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET);
	}

	if(num== ultrasonic_right)
	{
	//trigger_flag=0;
	
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
	timer_echostart();
	while(__HAL_TIM_GET_COUNTER(&tim4handle)<10);
	timer_echostop();
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_RESET);
	}

	if(num== ultrasonic_left)
	{
	//trigger_flag=0;

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	timer_echostart();
	while(__HAL_TIM_GET_COUNTER(&tim4handle)<10);
	timer_echostop();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	}
	
}

int ultrasonic_distance(ultrasonic num)
{
	if(num==ultrasonic_right)
	{
	readflag0=0;
    ultrasonic_trigger(ultrasonic_right);
    while(readflag0==0);
    return timerValue1/58;
	}

	if(num==ultrasonic_front)
	{
	readflag1=0;
    ultrasonic_trigger(ultrasonic_front);
    while(readflag1==0);

    return timerValue2/58;
	}

	if(num==ultrasonic_left)
	{
	readflag2=0;
    ultrasonic_trigger(ultrasonic_left);
    while(readflag2==0);
    return timerValue3/58;
	}
	return 0;
}


/*
	EXTI IRQ Handlers. These call the generic EXTI IRQ handler from the Cube
	HAL, which in turn call the user-defined generic EXTI Callback function 
	defined further below:
 */

/* Handle PE11 interrupt */
/* Handle PE11 interrupt */
/*
void EXTI15_10_IRQHandler(void) {
    //Make sure that interrupt flag is set
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
void TIM4_IRQHandler(void)
{
 // printf("EXTIDetected\r\n");
  HAL_TIM_IRQHandler(&tim4handle);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
 //printf("EXTICallbackDetected\r\n");
  trigger_flag=1;
}
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
	
	
}*/