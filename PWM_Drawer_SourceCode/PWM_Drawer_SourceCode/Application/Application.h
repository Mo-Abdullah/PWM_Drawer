/*
 * Application.h
 *
 * Created: 10-Dec-23 04:34:04 PM
 * Author: Mohamed Hassan Ali Hassan
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_


#define NUM_SPECIAL_CHARACTERS				(7U)

/* Signal Patterns Characters (Font = 5 x 8) */
#define PWM_DRAWER_GLCD_HIGH_LINE					(0x0202020202UL)
#define PWM_DRAWER_GLCD_LOW_LINE					(0x4040404040UL)
#define PWM_DRAWER_GLCD_RISING_EDGE					(0x02027E4040UL)
#define PWM_DRAWER_GLCD_FALLING_EDGE				(0x40407E0202UL)
#define PWM_DRAWER_GLCD_RIGHT_ARROW_HEAD			(0x003E081C2AUL)
#define PWM_DRAWER_GLCD_LEFT_ARROW_HEAD				(0x2A1C083E00UL)
#define PWM_DRAWER_GLCD_ARROW_MIDDLE_BODY			(0x0808080808UL)

/* Data Types for PWM Drawer Application */
typedef struct 
{
	u8_t Duty_Percent;
	f32_t High_Time_ms;
	f32_t Low_Time_ms;
	f32_t Period_Time_ms;
	f32_t Freq_kHz;
}SignalAttributesType;

void APP_Init(void);

void APP_MeasureSignal(SignalAttributesType* Signal_Data_Ptr); 

void APP_DrawSignal(SignalAttributesType* Signal_Data_Ptr, f32_t Scale_ms);

/* 1 if the same MCU is used to generate PWM signal and display it using GLCD, 0 otherwise */
#define GENERATE_PWM_FROM_SAME_MCU			(1U)
/* If the different MCUs is used to generate PWM signal and display it using LCD */
/* 1 if this is the MCU to display the signal using GLCD only, 0 if this is the MCU generating PWM only */
#if GENERATE_PWM_FROM_SAME_MCU == 0

#define GLCD_MCU						(0U)
		
#endif


#endif /* APPLICATION_H_ */