/*
 * GLCD.c
 *
 * Created: 10-Dec-23 01:56:22 PM
 * Author: Mohamed Hassan Ali Hassan
 */

#include "../../LIB/Std_Types.h"
#include "../../MCAL/DIO/DIO.h"
#include "GLCD.h"
#include "GLCD_Config.h"
#include "GLCD_CharPatterns.h"

#define	F_CPU 16000000UL 
#include <util/delay.h>

u8_t Current_X_Address = 0;
u8_t Current_Y_Address = 0;
u8_t CurrentPage = 0;

void GLCD_Init(void) 
{
	
	/* Initialize Port Directions */
	DIO_SetPinDirection(GLCD_CTRL_PORT, GLCD_ENABLE_PIN, OUTPUT);
	DIO_SetPinDirection(GLCD_CTRL_PORT, GLCD_RS_PIN, OUTPUT);
	DIO_SetPinDirection(GLCD_CTRL_PORT, GLCD_RW_PIN, OUTPUT);
	DIO_SetPinDirection(GLCD_CTRL_PORT, GLCD_RESET_PIN, OUTPUT);
	DIO_SetPinDirection(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_1, OUTPUT);
	DIO_SetPinDirection(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_2, OUTPUT);

	DIO_SetPortDirection(GLCD_DATA_PORT, OUTPUT);
	/* Keep reset pin inactive (high) */
	DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_RESET_PIN, HIGH);
	/* Initialization of GLCD Sequence */
	GLCD_SelectPage(GLCD_BOTH_PAGES);
	GLCD_SendCommand(GLCD_DISPLAY_OFF);
	GLCD_SendCommand(GLCD_SET_X_ADDRESS_PREFIX + 0);  /* line=0 */
	Current_X_Address = 0;
	GLCD_SendCommand(GLCD_SET_Y_ADDRESS_PREFIX + 0);  /* column=0 */
	Current_Y_Address = 0;
	GLCD_SendCommand(GLCD_SET_Z_ADDRESS_PREFIX + 0);  /* start_line=0 */
	GLCD_SendCommand(GLCD_DISPLAY_ON);
	GLCD_SelectPage(GLCD_PAGE_0);
	CurrentPage = 0;
}

void GLCD_SelectPage(GLCD_PageSelectType Page) 
{
	switch (Page) 
	{
		case GLCD_NO_PAGES:
			DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_1, LOW);
			DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_2, LOW);
			break;
		case GLCD_PAGE_0:
			DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_1, HIGH);
			DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_2, LOW);
			break;
		case GLCD_PAGE_1:
			DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_1, LOW);
			DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_2, HIGH);
			break;
		case GLCD_BOTH_PAGES:
			DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_1, HIGH);
			DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_PAGE_SELECT_PIN_2, HIGH);
			break;
		default: /* Do Nothing */
		break;
	}
}

void GLCD_SendCommand(GLCD_CommandType Instruction) 
{
	/* Select Instruction Register */
	DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_RS_PIN, GLCD_INSTRUCTION_REG);
	/* Select Write Operation */
	DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_RW_PIN, GLCD_WRITE_MODE);
	/* Send Command on Data Pins */
	DIO_SetPortValue(GLCD_DATA_PORT, Instruction);
	/* Enable Pulse of min. width 1us */
	DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_ENABLE_PIN, HIGH);
	_delay_us(5);
	DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_ENABLE_PIN, LOW);
}

void GLCD_SendData(u8_t Data) 
{
	/* Select Data Register */
	DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_RS_PIN, GLCD_DATA_REG);
	/* Select Write Operation */
	DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_RW_PIN, GLCD_WRITE_MODE);
	/* Send Command on Data Pins */
	DIO_SetPortValue(GLCD_DATA_PORT, Data);
	/* Enable Pulse of min. width 1us */
	DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_ENABLE_PIN, HIGH);
	_delay_us(5);
	DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_ENABLE_PIN, LOW);
}

void GLCD_Reset(void) 
{
	DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_RESET_PIN, LOW);
	_delay_us(10);
	DIO_SetPinValue(GLCD_CTRL_PORT, GLCD_RESET_PIN, HIGH);
}

void GLCD_DisplayPattern(u64_t Pattern) 
{
	for(u8_t i = 0; i < 5; i++) 
	{
		GLCD_SendCommand(GLCD_SET_X_ADDRESS_PREFIX + Current_X_Address);
		GLCD_SendCommand(GLCD_SET_Y_ADDRESS_PREFIX + Current_Y_Address);
		GLCD_SendData((Pattern>>(i*8U)) & 0x00000000FFUL);
		Current_Y_Address++;
		if (Current_Y_Address >= GLCD_MAX_PAGE_PIXEL_WIDTH && CurrentPage == 0) 
		{
			GLCD_SelectPage(GLCD_PAGE_1);
			CurrentPage = 0;
		}
	}
}

void GLCD_DisplayCharacter(char Data) 
{
	if ((CurrentPage == 0) | (Current_Y_Address < GLCD_MAX_PAGE_PIXEL_WIDTH - 7U)) 
	{
		/* Enough space to write character */
		switch (Data) 
		{
			case 'A': case 'a': GLCD_DisplayPattern(GLCD_CHAR_A); break;
			case 'F': case 'f': GLCD_DisplayPattern(GLCD_CHAR_F); break;
			case 'R': case 'r': GLCD_DisplayPattern(GLCD_CHAR_R); break;
			case 'E': case 'e': GLCD_DisplayPattern(GLCD_CHAR_E); break;
			case 'Q': case 'q': GLCD_DisplayPattern(GLCD_CHAR_Q); break;
			case 'U': case 'u': GLCD_DisplayPattern(GLCD_CHAR_U); break;
			case 'N': case 'n': GLCD_DisplayPattern(GLCD_CHAR_N); break;
			case 'C': case 'c': GLCD_DisplayPattern(GLCD_CHAR_C); break;
			case 'Y': case 'y': GLCD_DisplayPattern(GLCD_CHAR_Y); break;
			case 'D': case 'd': GLCD_DisplayPattern(GLCD_CHAR_D); break;
			case 'T': case 't': GLCD_DisplayPattern(GLCD_CHAR_T); break;
			case 'K': case 'k': GLCD_DisplayPattern(GLCD_CHAR_K); break;
			case 'H': case 'h': GLCD_DisplayPattern(GLCD_CHAR_H); break;
			case 'Z': case 'z': GLCD_DisplayPattern(GLCD_CHAR_Z); break;
			case 'M': case 'm': GLCD_DisplayPattern(GLCD_CHAR_M); break;
			case 'S': case 's': GLCD_DisplayPattern(GLCD_CHAR_S); break;
			case 'I': case 'i': GLCD_DisplayPattern(GLCD_CHAR_I); break;
			case '%': GLCD_DisplayPattern(GLCD_CHAR_PERCENT); break;
			case '=': GLCD_DisplayPattern(GLCD_CHAR_EQUAL); break;
			case '.': GLCD_DisplayPattern(GLCD_CHAR_POINT); break;
			case ' ': GLCD_DisplayPattern(GLCD_CHAR_SPACE); break;
			case '-': GLCD_DisplayPattern(GLCD_CHAR_NEGATIVE); break;
			case '0': GLCD_DisplayPattern(GLCD_CHAR_0); break;
			case '1': GLCD_DisplayPattern(GLCD_CHAR_1); break;
			case '2': GLCD_DisplayPattern(GLCD_CHAR_2); break;
			case '3': GLCD_DisplayPattern(GLCD_CHAR_3); break;
			case '4': GLCD_DisplayPattern(GLCD_CHAR_4); break;
			case '5': GLCD_DisplayPattern(GLCD_CHAR_5); break;
			case '6': GLCD_DisplayPattern(GLCD_CHAR_6); break;
			case '7': GLCD_DisplayPattern(GLCD_CHAR_7); break;
			case '8': GLCD_DisplayPattern(GLCD_CHAR_8); break;
			case '9': GLCD_DisplayPattern(GLCD_CHAR_9); break;
			default: /* Do Nothing */ 
			break;
		}
		GLCD_SendCommand(GLCD_SET_X_ADDRESS_PREFIX + Current_X_Address);
		GLCD_SendCommand(GLCD_SET_Y_ADDRESS_PREFIX + Current_Y_Address);
		GLCD_SendData(0);
		Current_Y_Address++;
		if (Current_Y_Address >= GLCD_MAX_PAGE_PIXEL_WIDTH && CurrentPage == 0) 
		{
			GLCD_SelectPage(GLCD_PAGE_1);
			Current_Y_Address = 0;
		}
	}
}

void GLCD_DisplayString(char* DataPtr) 
{
	while (*DataPtr != '\0') 
	{	
		GLCD_DisplayCharacter(*DataPtr);
		DataPtr++;
	}
}

void GLCD_DisplayInteger(s32_t Data) 
{
	if (Data < 0) 
	{
		GLCD_DisplayCharacter('-');
		Data = -1 * Data;
	}
	u8_t u8Local_Digit = 0U;
	char str_reversed[5] = "";
	char* str_ptr = str_reversed;
	
	do 
	{
		u8Local_Digit = Data%10;
		*str_ptr = (char)(48 + u8Local_Digit); /* 48 is the ASCII code of '0' */
		Data = Data/10;
		str_ptr++;
	} while (Data > 0);
	
	do 
	{
		str_ptr--;
		GLCD_DisplayCharacter(*str_ptr);
	} while (str_ptr != str_reversed);
}

void GLCD_DisplayFloatingNumber(f32_t Data) 
{
	/* Will display only 3 Decimal Places */
	u16_t IntegerPart = (u16_t)Data;
	GLCD_DisplayInteger(IntegerPart);
	GLCD_DisplayCharacter('.');
	f32_t DecimalPart = (Data - IntegerPart);
	u8_t Digit = 0;
	for (u8_t i = 0; i < 3; i++) 
	{
		Digit = (u8_t)(DecimalPart * 10.0);
		GLCD_DisplayCharacter((char)(48+Digit));
		DecimalPart = ((DecimalPart*10.0) - Digit);
	}
}

void GLCD_GoToLine(u8_t Line) 
{
	if (Line < GLCD_MAX_LINES) 
	{
		GLCD_SelectPage(GLCD_PAGE_0);
		Current_X_Address = Line;
		GLCD_SendCommand(GLCD_SET_X_ADDRESS_PREFIX + Current_X_Address);
		Current_Y_Address = 0;
		GLCD_SendCommand(GLCD_SET_Y_ADDRESS_PREFIX + Current_Y_Address);
	}
}

void GLCD_ClearDisplay(void) 
{
	for (u8_t Line = 0; Line < GLCD_MAX_LINES; Line++) 
	{
		GLCD_GoToLine(Line);
		GLCD_SelectPage(GLCD_BOTH_PAGES);
		for (u8_t i = 0; i < GLCD_MAX_PAGE_PIXEL_WIDTH; i++) 
		{
			GLCD_SendCommand(GLCD_SET_Y_ADDRESS_PREFIX + i);
			GLCD_SendData(0);
		}
	}
	GLCD_Reset();
	GLCD_SelectPage(GLCD_PAGE_0);
	CurrentPage = 0;
	GLCD_GoToLine(0);
}
