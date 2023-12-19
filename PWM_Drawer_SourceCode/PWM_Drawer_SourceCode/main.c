/*
 * PWM_Drawer_SourceCode.c
 *
 * Created: 05-Dec-23 03:40:34 PM
 * Author : Mohamed Hassan Ali Hassan
 */ 

#include "LIB/Std_Types.h"
#include "Application/Application.h"
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	APP_Init();
	SignalAttributesType Signal_Data = {0, 0, 0, 0, 0};
	f32_t Scale_ms = 0.25;
	
    while (1) 
    {
		APP_MeasureSignal(&Signal_Data);
		Scale_ms = (Signal_Data.Period_Time_ms) / 5;
		APP_DrawSignal(&Signal_Data, Scale_ms);
		_delay_ms(100);
    }
}

