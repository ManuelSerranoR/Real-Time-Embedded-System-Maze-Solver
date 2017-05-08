#include "pwm_hal.h"

TIM_HandleTypeDef tim_init;
TIM_OC_InitTypeDef tim1_conf;

void init_pwm(void)
{
	tim_init.Instance = TIM2;
	tim_init.Channel = HAL_TIM_ACTIVE_CHANNEL_1 | HAL_TIM_ACTIVE_CHANNEL_2 | HAL_TIM_ACTIVE_CHANNEL_3 | HAL_TIM_ACTIVE_CHANNEL_4;
	
	tim_init.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim_init.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
	tim_init.Init.Prescaler = 500;
	tim_init.Init.Period = TIMER_PERIOD_1KHZ;
	tim_init.Init.AutoReloadPreload = 0;

	TIM_ClockConfigTypeDef tim_clk_init;
	tim_clk_init.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	tim_clk_init.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;

	HAL_TIM_PWM_Init(&tim_init);

	tim1_conf.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	tim1_conf.OCMode = TIM_OCMODE_PWM1; // Timer PWM mode 2, if Counter > Pulse, we set the output pin LOW till end of cycle
	tim1_conf.OCNIdleState = TIM_OCIDLESTATE_RESET;
	tim1_conf.Pulse = 500;

	HAL_TIM_PWM_ConfigChannel(&tim_init, &tim1_conf, TIM_CHANNEL_1 | TIM_CHANNEL_2 | TIM_CHANNEL_3 | TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&tim_init, TIM_CHANNEL_1 | TIM_CHANNEL_2 | TIM_CHANNEL_3 | TIM_CHANNEL_4);

	//Set all to 0 at the beginning
	set_pwm(PD3, 0.0f);
    set_pwm(PD4, 0.0f);
    set_pwm(PD6, 0.0f);
    set_pwm(PD7, 0.0f);
}

void set_pwm(pwm_channel ch, float duty)
{
	switch(ch)
	{
		case PD3:
			tim1_conf.Pulse = (uint32_t)(duty * (float)TIMER_PERIOD_1KHZ);
			HAL_TIM_PWM_ConfigChannel(&tim_init, &tim1_conf, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&tim_init, TIM_CHANNEL_1);
			break;
		case PD4:
			tim1_conf.Pulse = (uint32_t)(duty * (float)TIMER_PERIOD_1KHZ);
			HAL_TIM_PWM_ConfigChannel(&tim_init, &tim1_conf, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&tim_init, TIM_CHANNEL_2);
			break;
		case PD7:
			tim1_conf.Pulse = (uint32_t)(duty * (float)TIMER_PERIOD_1KHZ);
			HAL_TIM_PWM_ConfigChannel(&tim_init, &tim1_conf, TIM_CHANNEL_3);
			HAL_TIM_PWM_Start(&tim_init, TIM_CHANNEL_3);
			break;
		case PD6:
			tim1_conf.Pulse = (uint32_t)(duty * (float)TIMER_PERIOD_1KHZ);
			HAL_TIM_PWM_ConfigChannel(&tim_init, &tim1_conf, TIM_CHANNEL_4);
			HAL_TIM_PWM_Start(&tim_init, TIM_CHANNEL_4);
			break;
	}
}