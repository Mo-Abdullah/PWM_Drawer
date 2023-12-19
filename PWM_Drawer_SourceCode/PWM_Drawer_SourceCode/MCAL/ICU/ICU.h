/*
 * ICU.h
 *
 * Created: 10-Dec-23 01:56:43 PM
 * Author: Mohamed Hassan Ali Hassan
 */ 


#ifndef ICU_H_
#define ICU_H_

#define ICU_TIMER1_RESOLUTION			(65536U)

#define ICU_TIMER1_EDGE_SELECT_BIT		(6U)
#define ICU_TIMER1_INT_BIT				(5U)
#define ICU_TIMER1_OVF_FLAG_BIT			(2U)

/* ICP1 Pin on PD6 */
typedef enum 
{
	ICU_TIMER_1			
}ICU_TimerChannelType;

typedef enum 
{
	ICU_NO_CLK_SRC,
	ICU_PRESCALE_1,
	ICU_PRESCALE_8,
	ICU_PRESCALE_64,
	ICU_PRESCALE_256,
	ICU_PRESCALE_1024,
	ICU_EXT_CLK_FALLING_EDGE,
	ICU_EXT_CLK_RISING_EDGE
}ICU_ClockPrescaleType;

typedef enum 
{
	ICU_TRIGGER_FALLING_EDGE,
	ICU_TRIGGER_RISING_EDGE
}ICU_TriggerEdgeType;

typedef enum 
{
	ICU_INTERRUPT_DISABLED,
	ICU_INTERRUPT_ENABLED
}ICU_InterruptStateType;

typedef enum 
{
	ICU_RUNNING,
	ICU_EVENT_CATURED
}ICU_StatusType;

typedef struct 
{
	f32_t High_Time;
	f32_t Period_Time;
}ICU_DutyCycleType;

typedef struct 
{
	ICU_TimerChannelType TimerChannel;
	ICU_ClockPrescaleType ClkPrescale;
	ICU_TriggerEdgeType TriggerEdge;
	ICU_InterruptStateType InterruptState;
}ICU_ConfigurationType;

/* Functions Implementations */
void ICU_Init(const ICU_ConfigurationType* ConfigPointer);
void ICU_SetTriggerEdge(ICU_TimerChannelType TimerChannel, ICU_TriggerEdgeType Edge);
void ICU_ClearTimerValue(ICU_TimerChannelType TimerChannel);
u16_t ICU_GetInputCaptureValue(ICU_TimerChannelType TimerChannel);
ICU_StatusType ICU_GetStatus(ICU_TimerChannelType TimerChannel);
void ICU_GetDutyCycle(ICU_TimerChannelType TimerChannel, u16_t Prescale_Value, ICU_DutyCycleType* DutyPointer);

/* Extern Variable to be used outside of this file */
extern const ICU_ConfigurationType ICU_Config;

#endif /* ICU_H_ */