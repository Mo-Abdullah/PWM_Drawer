/*
 * ICU.c
 *
 * Created: 10-Dec-23 01:56:22 PM
 * Author: Mohamed Hassan Ali Hassan
 */ 

/* ICU is Timer 1 Component */
/* Must Have access To Timer 1 Registers */
#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Macros.h"
#include "../DIO/DIO.h"
#include "../Timers/Timers.h"
#include "../Timers/Timers_Registers.h"
#include "ICU.h"
#include "ICU_Config.h"

/* Private Functions Prototypes */
static void ICU_InitTimer1(const ICU_ConfigurationType* ConfigPointer);
static void ICU_GetDutyCycle_Timer1(u16_t PrescaleValue, ICU_DutyCycleType* DutyPointer);

/* Functions Implementations */
void ICU_Init(const ICU_ConfigurationType* ConfigPointer) 
{
	switch (ConfigPointer->TimerChannel) 
	{
		case ICU_TIMER_1: ICU_InitTimer1(ConfigPointer); break;
		default: /* Do Nothing */
		break;
	}
}

void ICU_SetTriggerEdge(ICU_TimerChannelType TimerChannel, ICU_TriggerEdgeType Edge)
{
	CLEAR_BIT(*TIMER1_CTRL_REG_B, ICU_TIMER1_EDGE_SELECT_BIT);
	switch (TimerChannel) 
	{
		case ICU_TIMER_1: *TIMER1_CTRL_REG_B |= (Edge<<ICU_TIMER1_EDGE_SELECT_BIT); break;
		default: /* Do Nothing */
		break;
	}
}

void ICU_ClearTimerValue(ICU_TimerChannelType TimerChannel) 
{
	switch (TimerChannel) 
	{
		case ICU_TIMER_1: *(u16_t*)TIMER1_CNTR_REG_L = 0x0000U; break;
		default: /* Do Nothing */
		break;
	}
}

u16_t ICU_GetInputCaptureValue(ICU_TimerChannelType TimerChannel)
{
	u16_t InputCaptureValue = 0U;
	switch (TimerChannel) 
	{
		case ICU_TIMER_1: InputCaptureValue = (*(u16_t*)TIMER1_INP_CAPT_REG_L);
		default:  /* Do Nothing */
		break;
	}
	return InputCaptureValue;
}

ICU_StatusType ICU_GetStatus(ICU_TimerChannelType TimerChannel) 
{
	switch (TimerChannel) 
	{
		case ICU_TIMER_1:
		if (GET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_INT_BIT) == 1) 
		{
			/* Clear Flag */
			SET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_INT_BIT);  
			return ICU_EVENT_CATURED;
			} 
			else 
			{
			return ICU_RUNNING;
			}
		default: /* Do Nothing */
		break;
	}
	return ICU_RUNNING;
}

void ICU_GetDutyCycle(ICU_TimerChannelType TimerChannel, u16_t Prescale_Value, ICU_DutyCycleType* DutyPointer) 
{
	switch (TimerChannel) 
	{
		case ICU_TIMER_1:
		ICU_GetDutyCycle_Timer1(Prescale_Value, DutyPointer); break;
		default: /* Do Nothing */
		break;
	}
}

void ICU_InitTimer1(const ICU_ConfigurationType* ConfigPointer) 
{
	/* Set ICP1 Pin (on PD6) as Input to trigger the ICU */
	DIO_SetPinDirection(PORTD, PIN6, INPUT);
	//CLEAR_BIT(*PORTD_DIR_REG, 6U);
	/* Clear Configurations on TCCR1A and TCCR1B */
	*TIMER1_CTRL_REG_A = 0x00U;
	*TIMER1_CTRL_REG_B = 0x00U;
	/* Timer 1 mode is set to normal */
	/* Set Prescaler */
	*TIMER1_CTRL_REG_B |= (ConfigPointer->ClkPrescale);
	/* Set Trigger Edge (Falling or Rising) */
	*TIMER1_CTRL_REG_B |= ((ConfigPointer->TriggerEdge)<<ICU_TIMER1_EDGE_SELECT_BIT);
	/* Set Interrupt State */
	*TIMERS_INT_MASK_REG |= ((ConfigPointer->InterruptState)<<ICU_TIMER1_INT_BIT);
	/* Clear Timer 1 and ICR Values */
	*(u16_t*)TIMER1_CNTR_REG_L = 0x0000U;
	*(u16_t*)TIMER1_INP_CAPT_REG_L = 0x0000U;
}

void ICU_GetDutyCycle_Timer1(u16_t PrescaleValue, ICU_DutyCycleType* DutyPointer) 
{
	/* Clear Input Capture Flag for safety */
	SET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_INT_BIT);
	ICU_SetTriggerEdge(ICU_TIMER_1, ICU_TRIGGER_RISING_EDGE);
	/* Wait for the start of the period at rising edge */
	while (ICU_GetStatus(ICU_TIMER_1) == ICU_RUNNING);
	{	
		// Do Nothing
	}

	u32_t ON_Counts = 0U;
	ICU_SetTriggerEdge(ICU_TIMER_1, ICU_TRIGGER_FALLING_EDGE);
	ICU_ClearTimerValue(ICU_TIMER_1);
	/* Clear Input Capture Flag for safety */
	SET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_INT_BIT);
	/* Wait for the end of the high time at falling edge */
	while (ICU_GetStatus(ICU_TIMER_1) == ICU_RUNNING)
	{
		if (GET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_OVF_FLAG_BIT) == 1) 
		{
			SET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_OVF_FLAG_BIT);
			ON_Counts += ICU_TIMER1_RESOLUTION;
		}
	}
	ON_Counts += ICU_GetInputCaptureValue(ICU_TIMER_1);

	u32_t OFF_Counts = 0U;
	ICU_SetTriggerEdge(ICU_TIMER_1, ICU_TRIGGER_RISING_EDGE);
	ICU_ClearTimerValue(ICU_TIMER_1);
	/* Clear Input Capture Flag for safety */
	SET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_INT_BIT);
	/* Wait for the end of the period at rising edge */
	while (ICU_GetStatus(ICU_TIMER_1) == ICU_RUNNING)
	 {
		if (GET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_OVF_FLAG_BIT) == 1)
		{
			SET_BIT(*TIMERS_INT_FLAG_REG, ICU_TIMER1_OVF_FLAG_BIT);
			OFF_Counts += ICU_TIMER1_RESOLUTION;
		}
	}
	OFF_Counts = ICU_GetInputCaptureValue(ICU_TIMER_1);
	/* Set counts */
	/* Convert these into milliseconds */
	DutyPointer->High_Time = (f32_t)(ON_Counts * PrescaleValue * 1000.0 / F_CPU);
	DutyPointer->Period_Time = (f32_t)((ON_Counts + OFF_Counts) * PrescaleValue * 1000.0 / F_CPU);
}
