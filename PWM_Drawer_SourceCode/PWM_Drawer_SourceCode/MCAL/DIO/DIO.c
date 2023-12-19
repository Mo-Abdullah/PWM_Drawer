/*
 * DIO.c
 *
 * Created: 07-Oct-23 06:56:47 PM
 * Author: Mohamed Hassan Ali Hassan
 */ 

#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Macros.h"
#include "DIO.h"
#include "DIO_Registers.h"

void DIO_SetPinDirection(u8_t Port, u8_t PinNumber, u8_t Direction)
{
	if(Direction == OUTPUT || Direction == INPUT)/* Guard Section */
	{
		if(Direction == OUTPUT)
		{
			switch(Port)
			{
				case PORTA: SET_BIT(DDRA_REG, PinNumber); break ;
				case PORTB: SET_BIT(DDRB_REG, PinNumber); break ;
				case PORTC: SET_BIT(DDRC_REG, PinNumber); break ;
				case PORTD: SET_BIT(DDRD_REG, PinNumber); break ;
			}
		}
		else if(Direction == INPUT)
		{
			switch(Port)
			{
				case PORTA: CLEAR_BIT(DDRA_REG, PinNumber); break ;
				case PORTB: CLEAR_BIT(DDRB_REG, PinNumber); break ;
				case PORTC: CLEAR_BIT(DDRC_REG, PinNumber); break ;
				case PORTD: CLEAR_BIT(DDRD_REG, PinNumber); break ;
			}
		}
	}
}

void DIO_SetPinValue(u8_t Port, u8_t PinNumber, u8_t Value)
{
	if(Value == HIGH || Value == LOW)
	{
		if(Value == HIGH)
		{	
			switch(Port)
			{
				case PORTA: SET_BIT(PORTA_REG, PinNumber); break;
				case PORTB: SET_BIT(PORTB_REG, PinNumber); break;
				case PORTC: SET_BIT(PORTC_REG, PinNumber); break;
				case PORTD: SET_BIT(PORTD_REG, PinNumber); break;
			}
		}
		else if(Value == LOW)
		{
			switch(Port)
			{
				
				case PORTA: CLEAR_BIT(PORTA_REG, PinNumber); break;
				case PORTB: CLEAR_BIT(PORTB_REG, PinNumber); break;
				case PORTC: CLEAR_BIT(PORTC_REG, PinNumber); break;
				case PORTD: CLEAR_BIT(PORTD_REG, PinNumber); break;
			}
		}
	}
}

void DIO_TogglePinValue(u8_t Port, u8_t PinNumber)
{		
	switch(Port)
	{	
		case PORTA:  TOGGLE_BIT(PORTA_REG, PinNumber); break;
		case PORTB:  TOGGLE_BIT(PORTB_REG, PinNumber); break;
		case PORTC:  TOGGLE_BIT(PORTC_REG, PinNumber); break;
		case PORTD:  TOGGLE_BIT(PORTD_REG, PinNumber); break;
	}
}

u8_t DIO_GetPinValue(u8_t Port, u8_t PinNumber)
{
	u8_t PinValue = 0;
	
	switch(Port)
	{	
		case PORTA: PinValue= GET_BIT(PINA_REG, PinNumber); break;
		case PORTB: PinValue= GET_BIT(PINB_REG, PinNumber); break;
		case PORTC: PinValue= GET_BIT(PINC_REG, PinNumber); break;
		case PORTD: PinValue= GET_BIT(PIND_REG, PinNumber); break;
	}
	return PinValue ;
}

void DIO_SetPortDirection(u8_t Port, u8_t Direction)
{
	switch(Port)
	{	
		case PORTA: DDRA_REG = Direction; break;
		case PORTB: DDRB_REG = Direction; break;
		case PORTC: DDRC_REG = Direction; break;
		case PORTD: DDRD_REG = Direction; break;
	}
}

void DIO_SetPortValue(u8_t Port, u8_t Value)
{	
	switch(Port)
	{
		case PORTA: PORTA_REG = Value; break;
		case PORTB: PORTB_REG = Value; break;
		case PORTC: PORTC_REG = Value; break;
		case PORTD: PORTD_REG = Value; break;
	}
}