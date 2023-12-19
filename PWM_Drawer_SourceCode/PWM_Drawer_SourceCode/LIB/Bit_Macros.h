/*
 * Bit_Macros.h
 *
 * Created: 07-Oct-23 06:35:22 PM
 * Author: Mohamed Hassan Ali Abdullah
 */ 


#ifndef BIT_MACROS_H_
#define BIT_MACROS_H_

#define SET_BIT(REG, BIT)    (REG |= (1<<BIT))
#define GET_BIT(REG, BIT)    ((REG>>BIT)&0x01)
#define CLEAR_BIT(REG, BIT)  (REG &= ~(1<<BIT))
#define TOGGLE_BIT(REG, BIT) (REG ^= (1<<BIT))

#define ALL_INPUT    0x00
#define ALL_OUTPUT   0xFF
#define ALL_PORT_ON  0xFF
#define ALL_PORT_OFF 0x00

#endif /* BIT_MACROS_H_ */