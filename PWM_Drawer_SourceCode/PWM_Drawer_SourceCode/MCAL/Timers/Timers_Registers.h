/*
 * Timers_Registers.h
 *
 * Created: 08-Dec-23 03:57:27 PM
 * Author: Mohamed Hassan Ali Hassan
 */ 


#ifndef TIMERS_REGISTERS_H_
#define TIMERS_REGISTERS_H_

/* Global Interrupts Enable Register */
#define SREG					((volatile u8_t*)0x5F)
/* Timers SFR Registers */				   
#define TIMERS_INT_MASK_REG		((volatile u8_t*)0x59)
#define TIMERS_INT_FLAG_REG		((volatile u8_t*)0x58)
/*	Timer 0 SFR Registers */			   
#define TIMER0_CTRL_REG			((volatile u8_t*)0x53)
#define TIMER0_CNTR_REG			((volatile u8_t*)0x52)
#define TIMER0_CMP_REG			((volatile u8_t*)0x5C)
/* Timer 1 SFR Registers */				   
#define TIMER1_CTRL_REG_A		((volatile u8_t*)0x4F)
#define TIMER1_CTRL_REG_B		((volatile u8_t*)0x4E)
#define TIMER1_CNTR_REG_H		((volatile u8_t*)0x4D)
#define TIMER1_CNTR_REG_L		((volatile u8_t*)0x4C)
#define TIMER1_CMP_A_REG_H		((volatile u8_t*)0x4B)
#define TIMER1_CMP_A_REG_L		((volatile u8_t*)0x4A)
#define TIMER1_CMP_B_REG_H		((volatile u8_t*)0x49)
#define TIMER1_CMP_B_REG_L		((volatile u8_t*)0x48)
#define TIMER1_INP_CAPT_REG_H	((volatile u8_t*)0x47)
#define TIMER1_INP_CAPT_REG_L	((volatile u8_t*)0x46)
/* Timer 2 SFR Addresses */				   
#define TIMER2_CTRL_REG			((volatile u8_t*)0x45)
#define TIMER2_CNTR_REG			((volatile u8_t*)0x44)
#define TIMER2_CMP_REG			((volatile u8_t*)0x43)

/* Bit Definitions in Timers Registers */
/* TCCR1 */
#define TIMER0_CTC_CTRL_BIT		3  
#define TIMER0_OVF_INT_BIT		0
#define TIMER0_CMP_INT_BIT		1
/* TCCR1B */
#define TIMER1_CTC_CTRL_BIT		3 
#define TIMER1_OVF_INT_BIT		2
#define TIMER1_CMP_B_INT_BIT	3
#define TIMER1_CMP_A_INT_BIT	4
/* TCCR2 */
#define TIMER2_CTC_CTRL_BIT		3 
#define TIMER2_OVF_INT_BIT		6
#define TIMER2_CMP_INT_BIT		7

#endif /* TIMERS_REGISTERS_H_ */