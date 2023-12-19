/*
 * DIO.h
 *
 * Created: 07-Oct-23 06:57:00 PM
 * Author: Mohamed Hassan Ali Hassan
 */ 

#ifndef DIO_H_
#define DIO_H_

/* Pins Direction */
#define  OUTPUT   1
#define  INPUT    0

/* Pins Values */
#define  HIGH     1
#define  LOW      0

/* Ports Names */
#define  PORTA    0
#define  PORTB    1
#define  PORTC    2
#define  PORTD    3

/* Pins Names */
#define  PIN0     0
#define  PIN1     1
#define  PIN2     2
#define  PIN3     3
#define  PIN4     4
#define  PIN5     5
#define  PIN6     6
#define  PIN7     7


/************************************************************************/
/*						Functions Prototypes							*/
/************************************************************************/

/*****************************************************************************
* Function Name: DIO_SetPinDirection
* Purpose      : Set Pin Direction -> Output or Input
* Parameters   : u8_t Port, u8_t PinNumber, u8_t Direction
* Return value : void
*****************************************************************************/
void DIO_SetPinDirection(u8_t Port, u8_t PinNumber, u8_t Direction);

/*****************************************************************************
* Function Name: DIO_SetPinValue
* Purpose      : Set Pin Value-> High or Low
* Parameters   : u8_t Port, u8_t PinNumber, u8_t Value
* Return value : void
*****************************************************************************/
void DIO_SetPinValue(u8_t Port, u8_t PinNumber, u8_t Value);

/*****************************************************************************
* Function Name: DIO_TogglePinValue
* Purpose      : Toggle Pin Value-> High to Low or vice versa
* Parameters   : u8_t Port, u8_t PinNumber
* Return value : void
*****************************************************************************/
void DIO_TogglePinValue(u8_t Port, u8_t PinNumber);

/*****************************************************************************
* Function Name: DIO_GetPinValue
* Purpose      : Get/Read Pin Value-> High
* Parameters   : u8_t Port, u8_t PinNumber
* Return value : unsigned integer 8 bits
*****************************************************************************/
u8_t DIO_GetPinValue(u8_t Port, u8_t PinNumber);

/*****************************************************************************
* Function Name: DIO_SetPortDirection
* Purpose      : Set the whole Port Direction -> Output or Input
* Parameters   : u8_t Port, u8_t Direction
* Return value : void
*****************************************************************************/
void DIO_SetPortDirection(u8_t Port, u8_t Direction);

/*****************************************************************************
* Function Name: DIO_SetPortValue
* Purpose      : Set the whole Port Value -> High or Low
* Parameters   : u8_t Port, u8_t Value
* Return value : void
*****************************************************************************/
void DIO_SetPortValue(u8_t Portt, u8_t Value);

#endif /* DIO_H_ */