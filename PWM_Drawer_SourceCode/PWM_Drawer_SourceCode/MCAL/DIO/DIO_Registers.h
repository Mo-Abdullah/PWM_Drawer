/*
 * DIO_Registers.h
 *
 * Created: 07-Oct-23 06:57:18 PM
 * Author: Mohamed Hassan Ali Hassan
 */ 

#ifndef DIO_REGISTERS_H_
#define DIO_REGISTERS_H_

/* PORT_A Control Registers */
#define PORTA_REG   *((volatile u8_t*)0x3B)
#define DDRA_REG    *((volatile u8_t*)0x3A)
#define PINA_REG    *((volatile u8_t*)0x39)

/* PORT_B Control Registers */
#define PORTB_REG   *((volatile u8_t*)0x38)
#define DDRB_REG    *((volatile u8_t*)0x37)
#define PINB_REG    *((volatile u8_t*)0x36)

/* PORT_C Control Registers */
#define PORTC_REG   *((volatile u8_t*)0x35)
#define DDRC_REG    *((volatile u8_t*)0x34)
#define PINC_REG    *((volatile u8_t*)0x33)
								  
/* PORT_D Control Registers */					  
#define PORTD_REG   *((volatile u8_t*)0x32)
#define DDRD_REG    *((volatile u8_t*)0x31)
#define PIND_REG    *((volatile u8_t*)0x30)

#endif /* DIO_REGISTERS_H_ */