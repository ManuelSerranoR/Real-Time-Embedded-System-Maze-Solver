#include "board_led.h"

void board_led_init(void)
{
	static GPIO_InitTypeDef  GPIO_InitStruct;

	GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_15 | GPIO_PIN_14 | GPIO_PIN_12 | GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	__HAL_RCC_GPIOE_CLK_ENABLE();

	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}

void board_led_on(led led_id)
{
	switch(led_id)
	{
		case LED3:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
			break;
		case LED4:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
			break;	
		case LED6:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_SET);
			break;
		case LED8:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);
			break;
		case LED9:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_SET);
			break;
		case LED10:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_SET);
			break;
	}
}

void board_led_off(led led_id)
{
	switch(led_id)
	{
		case LED3:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_RESET);
			break;
		case LED4:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
			break;	
		case LED6:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, GPIO_PIN_RESET);
			break;
		case LED8:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_RESET);
			break;
		case LED9:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, GPIO_PIN_RESET);
			break;
		case LED10:
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, GPIO_PIN_RESET);
			break;
	}
}

void board_led_all_on(){
	board_led_on(LED3);
    board_led_on(LED4);
    board_led_on(LED6);
    board_led_on(LED8);
    board_led_on(LED9);
    board_led_on(LED10);
}

void board_led_all_off(){
	board_led_off(LED3);
    board_led_off(LED4);
    board_led_off(LED6);
    board_led_off(LED8);
    board_led_off(LED9);
    board_led_off(LED10);
}

/*
void board_led_toggle(led led_id)
{
	switch(led_id)
	{
		case LED1:
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_8);
			break;
		case LED2:
			HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
			break;
	}
} 
*/
