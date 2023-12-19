/*
 * Timers_Config.h
 *
 * Created: 08-Dec-23 03:57:05 PM
 * Author: Mohamed Hassan Ali Hassan
 */ 


#ifndef TIMERS_CONFIG_H_
#define TIMERS_CONFIG_H_

const TIMERS_ConfigurationType Timers_Config[NUM_TIMERS_OPERATING] =
{
	{
		TIMERS_TIMER_2,
		TIMERS_CTC_MODE,
		TIMERS_PRESCALE_8,
		TIMERS_INTERRUPT_DISABLED
	}
};

const PWM_ConfigurationType PWM_Config[NUM_OPERATING_PWM_CHANNELS] =
{
	{
		PWM_TIMER_0_CHANNEL,
		PWM_FAST,
		PWM_PRESCALE_8,
		PWM_INVERTED,
		256U,
		4U,
		90U
	}
};


#endif /* TIMERS_CONFIG_H_ */