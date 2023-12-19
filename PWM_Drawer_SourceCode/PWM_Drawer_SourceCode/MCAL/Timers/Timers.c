/*
 * Timers.c
 *
 * Created: 08-Dec-23 03:56:27 PM
 * Author: Mohamed Hassan Ali Hassan 
 */ 


#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Macros.h"
#include "../DIO/DIO.h"
#include "Timers.h"
#include "Timers_Registers.h"
#include "Timers_Config.h"

u16_t PWM_TimerTopValue = 0;

/* Private Functions (Only Visible To This File) */
static void Timers_InitTimer0(const TIMERS_ConfigurationType* ConfigPointer);
static void Timers_InitTimer1(const TIMERS_ConfigurationType* ConfigPointer);
static void Timers_InitTimer2(const TIMERS_ConfigurationType* ConfigPointer);
static void PWM_InitTimer0(const PWM_ConfigurationType* ConfigPointer);

/* Functions Implementation (APP APIs) */
void Timers_Init(const TIMERS_ConfigurationType* ConfigArrPtr) 
{
	for (u8_t i = 0; i < NUM_TIMERS_OPERATING; i++, ConfigArrPtr++) 
	{
		switch (ConfigArrPtr->TimerChannel) 
		{
			case TIMERS_TIMER_0: Timers_InitTimer0(ConfigArrPtr); break;
			case TIMERS_TIMER_1: Timers_InitTimer1(ConfigArrPtr); break;
			case TIMERS_TIMER_2: Timers_InitTimer2(ConfigArrPtr); break;
			default: /*Do Nothing */
			break;
		}
	}
}

static void Timers_InitTimer0(const TIMERS_ConfigurationType* ConfigPointer)
{
	/* Clear TCCR0 Register */
	*TIMER0_CTRL_REG = 0x00;
	/* Set Mode (Normal or CTC) */
	*TIMER0_CTRL_REG |= (ConfigPointer->OperationMode);
	/* Select Clock Source and Prescaler */
	switch (ConfigPointer->ClkPrescale) 
	{
		case TIMERS_TIMER_STOP:
		case TIMERS_PRESCALE_1:
		case TIMERS_PRESCALE_8:
		*TIMER0_CTRL_REG |= (ConfigPointer->ClkPrescale); break;
		case TIMERS_PRESCALE_64:
		*TIMER0_CTRL_REG |= ((ConfigPointer->ClkPrescale) - 1U); break;
		case TIMERS_PRESCALE_256:
		case TIMERS_PRESCALE_1024:
		case TIMERS_EXT_CLK_FALLING_EDGE:
		case TIMERS_EXT_CLK_RISING_EDGE:
		*TIMER0_CTRL_REG |= ((ConfigPointer->ClkPrescale) - 2U); break;
		default: /* Do Nothing */
		break;
	}
	/* Set Interrupt State */
	*TIMERS_INT_MASK_REG &= 0xFC;
	switch (ConfigPointer->OperationMode)
	{
		case TIMERS_NORMAL_MODE: *TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState) << TIMER0_OVF_INT_BIT);
		case TIMERS_CTC_MODE: *TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState) << TIMER0_CMP_INT_BIT);
		default: /* Do Nothing */
		break;
	}
}

static void Timers_InitTimer1(const TIMERS_ConfigurationType* ConfigPointer)
{
	/* Clear TCCR1A and TCCR1B Register */
	*TIMER1_CTRL_REG_A = 0x00U;
	*TIMER1_CTRL_REG_B = 0x00U;
	/* Set Mode (Normal or CTC) */
	*TIMER1_CTRL_REG_B |= (ConfigPointer->OperationMode);
	/* Select Clock Source and Prescaler */
	switch (ConfigPointer->ClkPrescale) 
	{
		case TIMERS_TIMER_STOP:
		case TIMERS_PRESCALE_1:
		case TIMERS_PRESCALE_8:
		*TIMER1_CTRL_REG_B |= (ConfigPointer->ClkPrescale); break;
		case TIMERS_PRESCALE_64:
		*TIMER1_CTRL_REG_B |= ((ConfigPointer->ClkPrescale) - 1U); break;
		case TIMERS_PRESCALE_256:
		case TIMERS_PRESCALE_1024:
		case TIMERS_EXT_CLK_FALLING_EDGE:
		case TIMERS_EXT_CLK_RISING_EDGE:
		*TIMER1_CTRL_REG_B |= ((ConfigPointer->ClkPrescale) - 2U); break;
		default: /* Do Nothing */
		break;
	}
	/* Set Interrupt State */
	*TIMERS_INT_MASK_REG &= (0xE3U);
	switch (ConfigPointer->OperationMode) 
	{
		case TIMERS_NORMAL_MODE: *TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState) << TIMER1_OVF_INT_BIT);
		case TIMERS_CTC_MODE: *TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState) << TIMER1_CMP_A_INT_BIT);
		default: /* Do Nothing */
		break;
	}
}

static void Timers_InitTimer2(const TIMERS_ConfigurationType* ConfigPointer)
{
	/* Clear TCCR2 Register Configurations */
	*TIMER2_CTRL_REG = 0x00U;
	/* Set Mode (Normal or CTC) */
	*TIMER2_CTRL_REG |= (ConfigPointer->OperationMode);
	/* Select Clock Source and Prescaler */
	if ((ConfigPointer->ClkPrescale) != TIMERS_EXT_CLK_FALLING_EDGE && (ConfigPointer->ClkPrescale) != TIMERS_EXT_CLK_RISING_EDGE) {
		*TIMER2_CTRL_REG |= (ConfigPointer->ClkPrescale);
	}
	/* Set Interrupt State */
	*TIMERS_INT_MASK_REG &= (0x3FU);
	switch (ConfigPointer->OperationMode) {
		case TIMERS_NORMAL_MODE: *TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER2_OVF_INT_BIT);
		case TIMERS_CTC_MODE: *TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER2_CMP_INT_BIT);
		default: /* Do Nothing */
		break;
	}
}

void Timers_Delay_us(const TIMERS_ConfigurationType* ConfigPointer, u16_t Delay_Time_us)
{
	// Delay_Time_us = 10^6 * Prescale * Num_Counts / F_CPU
	u16_t Tmr_Counts = 0U;
	switch (ConfigPointer->ClkPrescale) 
	{
		case TIMERS_PRESCALE_1:	   Tmr_Counts = (u16_t)(Delay_Time_us * F_CPU / (1.0 * 1000000UL)); break;
		case TIMERS_PRESCALE_8:	   Tmr_Counts = (u16_t)(Delay_Time_us * F_CPU / (8.0 * 1000000UL)); break;
		case TIMERS_PRESCALE_32:   Tmr_Counts = (u16_t)(Delay_Time_us * F_CPU / (32.0 * 1000000UL)); break;
		case TIMERS_PRESCALE_64:   Tmr_Counts = (u16_t)(Delay_Time_us * F_CPU / (64.0 * 1000000UL)); break;
		case TIMERS_PRESCALE_128:  Tmr_Counts = (u16_t)(Delay_Time_us * F_CPU / (128.0 * 1000000UL)); break;
		case TIMERS_PRESCALE_256:  Tmr_Counts = (u16_t)(Delay_Time_us * F_CPU / (256.0 * 1000000UL)); break;
		case TIMERS_PRESCALE_1024: Tmr_Counts = (u16_t)(Delay_Time_us * F_CPU / (1024.0 * 1000000UL)); break;
		default: /* Do Nothing */
		break;
	}
	switch (ConfigPointer->TimerChannel) 
	{
		case TIMERS_TIMER_0:
		/* Disable Interrupts for Waiting Delay */
		*TIMERS_INT_MASK_REG &= (0xFCU);
		switch (ConfigPointer->OperationMode)
		 {
			case TIMERS_CTC_MODE:
			*TIMER0_CMP_REG = (u8_t)Tmr_Counts;
			*TIMER0_CNTR_REG = 0x00U;
			while (GET_BIT(*TIMERS_INT_FLAG_REG, TIMER0_CMP_INT_BIT) == 0);
			SET_BIT(*TIMERS_INT_FLAG_REG, TIMER0_CMP_INT_BIT);
			/* Re-set interrupt state */
			*TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER0_CMP_INT_BIT);
			return;
			case TIMERS_NORMAL_MODE:
			*TIMER0_CNTR_REG = 256 - (u8_t)(Tmr_Counts);
			while (GET_BIT(*TIMERS_INT_FLAG_REG, TIMER0_OVF_INT_BIT) == 0) ;
			SET_BIT(*TIMERS_INT_FLAG_REG, TIMER0_OVF_INT_BIT);
			/* Re-set interrupt state */
			*TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER0_OVF_INT_BIT);
			return;
			default:/* Do Nothing */
			break;
		 }
		break;
		case TIMERS_TIMER_1:
		/* Disable Interrupts for Waiting Delay */
		*TIMERS_INT_MASK_REG &= (0xC3U);
		switch (ConfigPointer->OperationMode) 
		{
			case TIMERS_CTC_MODE:
			*TIMER1_CMP_A_REG_L = (u8_t)(Tmr_Counts & 0x00FFU);
			*TIMER1_CMP_A_REG_H = (u8_t)((Tmr_Counts & 0xFF00U)>>8);
			*TIMER1_CNTR_REG_L = 0x00U;
			*TIMER1_CNTR_REG_H = 0x00U;
			while(GET_BIT(*TIMERS_INT_FLAG_REG, TIMER1_CMP_A_INT_BIT) == 0) ;
			SET_BIT(*TIMERS_INT_FLAG_REG, TIMER1_CMP_A_INT_BIT);
			/* Re-set interrupt state */
			*TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER1_CMP_A_INT_BIT);
			return;
			case TIMERS_NORMAL_MODE:
			*TIMER1_CNTR_REG_L = (u8_t)((65535 - Tmr_Counts) & 0x00FFU);
			*TIMER1_CNTR_REG_H = (u8_t)((65535 - Tmr_Counts) >> 8);
			while (GET_BIT(*TIMERS_INT_FLAG_REG, TIMER1_OVF_INT_BIT) == 0) ;
			SET_BIT(*TIMERS_INT_FLAG_REG, TIMER1_OVF_INT_BIT);
			/* Re-set interrupt state */
			*TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER1_OVF_INT_BIT);
			return;
			default: /* Do Nothing */
			break;
		}
		break;
		case TIMERS_TIMER_2:
		/* Disable Interrupts for Waiting Delay */
		*TIMERS_INT_MASK_REG &= (0x3FU);
		switch (ConfigPointer->OperationMode) 
		{
			case TIMERS_CTC_MODE:
			*TIMER2_CMP_REG = (u8_t)Tmr_Counts;
			*TIMER2_CNTR_REG = 0x00U;
			while(GET_BIT(*TIMERS_INT_FLAG_REG, TIMER2_CMP_INT_BIT) == 0) ;
			SET_BIT(*TIMERS_INT_FLAG_REG, TIMER2_CMP_INT_BIT);
			/* Re-set interrupt state */
			*TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER2_CMP_INT_BIT);
			return;
			case TIMERS_NORMAL_MODE:
			*TIMER2_CNTR_REG = 256 - (u8_t)(Tmr_Counts);
			while(GET_BIT(*TIMERS_INT_FLAG_REG, TIMER2_OVF_INT_BIT) == 0) ;
			SET_BIT(*TIMERS_INT_FLAG_REG, TIMER2_OVF_INT_BIT);
			/* Re-set interrupt state */
			*TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER2_OVF_INT_BIT);
			return;
			default: /* Do Nothing */
			break;
		}
		break;
		default: 
		break;
	}
}

void Timers_Delay_ms(const TIMERS_ConfigurationType* ConfigPointer, u16_t Delay_Time_ms)
{
	// Delay_Time_us = 10^6 * Prescale * Num_Counts / F_CPU
	u16_t Tmr_Counts = 0U;
	switch (ConfigPointer->ClkPrescale)
	{
		case TIMERS_PRESCALE_1:	   Tmr_Counts = (u16_t)(Delay_Time_ms * F_CPU / (1.0 * 1000UL)); break;
		case TIMERS_PRESCALE_8:	   Tmr_Counts = (u16_t)(Delay_Time_ms * F_CPU / (8.0 * 1000UL)); break;
		case TIMERS_PRESCALE_32:   Tmr_Counts = (u16_t)(Delay_Time_ms * F_CPU / (32.0 * 1000UL)); break;
		case TIMERS_PRESCALE_64:   Tmr_Counts = (u16_t)(Delay_Time_ms * F_CPU / (64.0 * 1000UL)); break;
		case TIMERS_PRESCALE_128:  Tmr_Counts = (u16_t)(Delay_Time_ms * F_CPU / (128.0 * 1000UL)); break;
		case TIMERS_PRESCALE_256:  Tmr_Counts = (u16_t)(Delay_Time_ms * F_CPU / (256.0 * 1000UL)); break;
		case TIMERS_PRESCALE_1024: Tmr_Counts = (u16_t)(Delay_Time_ms * F_CPU / (1024.0 * 1000UL)); break;
		default: /* Do Nothing */
		break;
	}
	switch (ConfigPointer->TimerChannel)
	{
		case TIMERS_TIMER_0:
		/* Disable Interrupts for Waiting Delay */
		*TIMERS_INT_MASK_REG &= (0xFCU);
		switch (ConfigPointer->OperationMode)
		{
			case TIMERS_CTC_MODE:
			*TIMER0_CMP_REG = (u8_t)Tmr_Counts;
			*TIMER0_CNTR_REG = 0x00U;
			while (GET_BIT(*TIMERS_INT_FLAG_REG, TIMER0_CMP_INT_BIT) == 0);
			SET_BIT(*TIMERS_INT_FLAG_REG, TIMER0_CMP_INT_BIT);
			/* Re-set interrupt state */
			*TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER0_CMP_INT_BIT);
			return;
			case TIMERS_NORMAL_MODE:
			*TIMER0_CNTR_REG = 256 - (u8_t)(Tmr_Counts);
			while (GET_BIT(*TIMERS_INT_FLAG_REG, TIMER0_OVF_INT_BIT) == 0) ;
			SET_BIT(*TIMERS_INT_FLAG_REG, TIMER0_OVF_INT_BIT);
			/* Re-set interrupt state */
			*TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER0_OVF_INT_BIT);
			return;
			default:/* Do Nothing */
			break;
		}
		break;
		case TIMERS_TIMER_1:
		/* Disable Interrupts for Waiting Delay */
		*TIMERS_INT_MASK_REG &= (0xC3U);
		switch (ConfigPointer->OperationMode)
		{
			case TIMERS_CTC_MODE:
			*TIMER1_CMP_A_REG_L = (u8_t)(Tmr_Counts & 0x00FFU);
			*TIMER1_CMP_A_REG_H = (u8_t)((Tmr_Counts & 0xFF00U)>>8);
			*TIMER1_CNTR_REG_L = 0x00U;
			*TIMER1_CNTR_REG_H = 0x00U;
			while(GET_BIT(*TIMERS_INT_FLAG_REG, TIMER1_CMP_A_INT_BIT) == 0) ;
			SET_BIT(*TIMERS_INT_FLAG_REG, TIMER1_CMP_A_INT_BIT);
			/* Re-set interrupt state */
			*TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER1_CMP_A_INT_BIT);
			return;
			case TIMERS_NORMAL_MODE:
			*TIMER1_CNTR_REG_L = (u8_t)((65535 - Tmr_Counts) & 0x00FFU);
			*TIMER1_CNTR_REG_H = (u8_t)((65535 - Tmr_Counts) >> 8);
			while (GET_BIT(*TIMERS_INT_FLAG_REG, TIMER1_OVF_INT_BIT) == 0) ;
			SET_BIT(*TIMERS_INT_FLAG_REG, TIMER1_OVF_INT_BIT);
			/* Re-set interrupt state */
			*TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER1_OVF_INT_BIT);
			return;
			default: /* Do Nothing */
			break;
		}
		break;
		case TIMERS_TIMER_2:
		/* Disable Interrupts for Waiting Delay */
		*TIMERS_INT_MASK_REG &= (0x3FU);
		switch (ConfigPointer->OperationMode)
		{
			case TIMERS_CTC_MODE:
			*TIMER2_CMP_REG = (u8_t)Tmr_Counts;
			*TIMER2_CNTR_REG = 0x00U;
			while(GET_BIT(*TIMERS_INT_FLAG_REG, TIMER2_CMP_INT_BIT) == 0) ;
			SET_BIT(*TIMERS_INT_FLAG_REG, TIMER2_CMP_INT_BIT);
			/* Re-set interrupt state */
			*TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER2_CMP_INT_BIT);
			return;
			case TIMERS_NORMAL_MODE:
			*TIMER2_CNTR_REG = 256 - (u8_t)(Tmr_Counts);
			while(GET_BIT(*TIMERS_INT_FLAG_REG, TIMER2_OVF_INT_BIT) == 0) ;
			SET_BIT(*TIMERS_INT_FLAG_REG, TIMER2_OVF_INT_BIT);
			/* Re-set interrupt state */
			*TIMERS_INT_MASK_REG |= ((ConfigPointer->IntterruptState)<<TIMER2_OVF_INT_BIT);
			return;
			default: /* Do Nothing */
			break;
		}
		break;
		default: /* Do Nothing */
		break;
	}
}

TIMERS_StatusType Timers_GetTimerStatus(const TIMERS_ConfigurationType* ConfigPointer) {
	switch (ConfigPointer->TimerChannel) 
	{
		case TIMERS_TIMER_0:
		switch (ConfigPointer->OperationMode)
		{
			case TIMERS_NORMAL_MODE:
			return GET_BIT(*TIMERS_INT_FLAG_REG, TIMER0_OVF_INT_BIT);
			case TIMERS_CTC_MODE:
			return GET_BIT(*TIMERS_INT_FLAG_REG, TIMER0_CMP_INT_BIT);
			default:
			break;
		}
		
		case TIMERS_TIMER_1:
		switch (ConfigPointer->OperationMode)
		{
			case TIMERS_NORMAL_MODE:
			return GET_BIT(*TIMERS_INT_FLAG_REG, TIMER1_OVF_INT_BIT);
			case TIMERS_CTC_MODE:
			return GET_BIT(*TIMERS_INT_FLAG_REG, TIMER1_CMP_A_INT_BIT);
			default: 
			break;
		}	
		
		case TIMERS_TIMER_2:
		switch (ConfigPointer->OperationMode)
		{
			case TIMERS_NORMAL_MODE:
			return GET_BIT(*TIMERS_INT_FLAG_REG, TIMER2_OVF_INT_BIT);
			case TIMERS_CTC_MODE:
			return GET_BIT(*TIMERS_INT_FLAG_REG, TIMER2_CMP_INT_BIT);
			default:
			break;
		}
		default:
		break;
	}
	return TIMERS_TIMER_FINISHED;
}

/* Only Use Timer 0 For Internal PWM Generation
 * Further Timers Could be Added to These Functions */

void PWM_Init(const PWM_ConfigurationType* ConfigPointer) 
{
	switch (ConfigPointer->TimerChannel) 
	{
		case PWM_TIMER_0_CHANNEL: PWM_InitTimer0(ConfigPointer); break;
		default:
		break;
	}
}

void PWM_SetDuty(PWM_ChannelType TimerChannel, PWM_OutputStateType State, u16_t Duty_Percent) 
{
	switch (TimerChannel) 
	{
		case PWM_TIMER_0_CHANNEL:
		switch (State) 
		{
			case PWM_NON_INVERTED: *TIMER0_CMP_REG = (u8_t)(Duty_Percent * PWM_TIMER_0_RESOLUTION / 100.0); break;
			case PWM_INVERTED: *TIMER0_CMP_REG = (u8_t)((100.0 - Duty_Percent) * PWM_TIMER_0_RESOLUTION / 100.0); break;
			default: /* Do Nothing */
			break;
		}
		break;
	}
}

void PWM_InitTimer0(const PWM_ConfigurationType* ConfigPointer) 
{
	/* Make PB3=OC0 as output */
	DIO_SetPinDirection(PORTB, PIN3, OUTPUT);
	//SET_BIT(*PORTB_DIR_REG, 3U);
	/* Clear TCCR0 Register Configurations */
	*TIMER0_CTRL_REG = 0x00;
	/* Set PWM Mode */
	*TIMER0_CTRL_REG |= (1U<<6U) | ((ConfigPointer->Mode)<<PWM_TIMER_0_FAST_BIT);
	/* Set PWM Output State (inverting or not) */
	*TIMER0_CTRL_REG |= (1U<<5U) | ((ConfigPointer->State)<<PWM_TIMER_0_INVERTING_BIT);
	/* Select Clock Source and Prescaler */
	switch (ConfigPointer->ClkPrescale) 
	{
		case PWM_NO_CLK_SRC:
		case PWM_PRESCALE_1:
		case PWM_PRESCALE_8:
			*TIMER0_CTRL_REG |= (ConfigPointer->ClkPrescale); break;
		case PWM_PRESCALE_64:
			*TIMER0_CTRL_REG |= ((ConfigPointer->ClkPrescale) - 1U); break;
		case PWM_PRESCALE_256:
		case PWM_PRESCALE_1024:
		case PWM_EXT_CLK_FALLING_EDGE:
		case PWM_EXT_CLK_RISING_EDGE:
			*TIMER0_CTRL_REG |= ((ConfigPointer->ClkPrescale) - 2U); break;
		default: /* Do Nothing */
		break;
	}
	/* Set Duty Value in OCR0 Register */
	*TIMER0_CMP_REG = 0x00U;
	switch (ConfigPointer->State) 
	{
		case PWM_NON_INVERTED: *TIMER0_CMP_REG = (u8_t)((ConfigPointer->DutyPercent) * PWM_TIMER_0_RESOLUTION / 100.0); break;
		case PWM_INVERTED: *TIMER0_CMP_REG = (u8_t)((100.0 - ConfigPointer->DutyPercent) * PWM_TIMER_0_RESOLUTION / 100.0); break;
		default: break;
	}
	/* Clear TCNT0 Register Configurations */
	*TIMER0_CNTR_REG = 0x00U;
}
