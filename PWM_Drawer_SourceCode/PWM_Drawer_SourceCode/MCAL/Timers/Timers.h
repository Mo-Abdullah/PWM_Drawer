/*
 * Timers.h
 *
 * Created: 08-Dec-23 03:56:40 PM
 * Author: Mohamed Hassan Ali Hassan
 */ 

#ifndef TIMERS_H_
#define TIMERS_H_

#define F_CPU								(16000000UL)
#define NUM_TIMERS_OPERATING				(1U)
#define PWM_TIMER_0_RESOLUTION				(255U)

/* Input the number of operating Timers for PWM */
#define NUM_OPERATING_PWM_CHANNELS			(1U)
/* Bits For PWM Mode */
#define PWM_TIMER_0_FAST_BIT				(3U)
#define PWM_TIMER_0_INVERTING_BIT			(4U)

typedef enum
{
	TIMERS_TIMER_0,
	TIMERS_TIMER_1,
	TIMERS_TIMER_2
}TIMERS_TimerType;

typedef enum
{
	TIMERS_NORMAL_MODE,
	TIMERS_CTC_MODE
}TIMERS_OperationType;

typedef enum
{
	TIMERS_TIMER_STOP,
	TIMERS_PRESCALE_1,
	TIMERS_PRESCALE_8,
	TIMERS_PRESCALE_32,
	TIMERS_PRESCALE_64,
	TIMERS_PRESCALE_128,
	TIMERS_PRESCALE_256,
	TIMERS_PRESCALE_1024,
	TIMERS_EXT_CLK_FALLING_EDGE,
	TIMERS_EXT_CLK_RISING_EDGE
}TIMERS_ClockType;

typedef enum
{
	TIMERS_INTERRUPT_DISABLED,
	TIMERS_INTERRUPT_ENABLED
}TIMERS_InterruptState;

typedef struct
{
	TIMERS_TimerType TimerChannel;
	TIMERS_OperationType OperationMode;
	TIMERS_ClockType ClkPrescale;
	TIMERS_InterruptState IntterruptState;
}TIMERS_ConfigurationType;

typedef enum
{
	TIMERS_TIMER_RUNNING,
	TIMERS_TIMER_FINISHED,
}TIMERS_StatusType;

typedef enum 
{
	PWM_TIMER_0_CHANNEL
}PWM_ChannelType;

typedef enum 
{
	PWM_PHASE_CORRECT,
	PWM_FAST
}PWM_ModeType;

typedef enum 
{
	PWM_NO_CLK_SRC,
	PWM_PRESCALE_1,
	PWM_PRESCALE_8,
	PWM_PRESCALE_32,
	PWM_PRESCALE_64,
	PWM_PRESCALE_128,
	PWM_PRESCALE_256,
	PWM_PRESCALE_1024,
	PWM_EXT_CLK_FALLING_EDGE,
	PWM_EXT_CLK_RISING_EDGE
}PWM_ClockPrescaleType;

typedef enum 
{
	PWM_NON_INVERTED,
	PWM_INVERTED
}PWM_OutputStateType;

typedef struct 
{
	PWM_ChannelType TimerChannel;
	PWM_ModeType Mode;
	PWM_ClockPrescaleType ClkPrescale;
	PWM_OutputStateType State;
	u16_t PrescaleValue;
	u16_t Period_ms;
	u8_t DutyPercent;
}PWM_ConfigurationType;

/* Functions Prototypes */
void Timers_Init(const TIMERS_ConfigurationType* ConfigArrPtr);
void Timers_Delay_us(const TIMERS_ConfigurationType* ConfigPointer, u16_t Delay_Time_us);
void Timers_Delay_ms(const TIMERS_ConfigurationType* ConfigPointer, u16_t Delay_Time_ms);
TIMERS_StatusType Timers_GetTimerStatus(const TIMERS_ConfigurationType* ConfigPointer);
void PWM_Init(const PWM_ConfigurationType* ConfigPointer);
void PWM_SetDuty(PWM_ChannelType TimerChannel, PWM_OutputStateType State, u16_t Duty_Percent);

/* Extern Variables to use outside of this file scope */
extern const  TIMERS_ConfigurationType Timers_Config[NUM_TIMERS_OPERATING];
extern const PWM_ConfigurationType PWM_Config[NUM_OPERATING_PWM_CHANNELS];

#endif /* TIMERS_H_ */