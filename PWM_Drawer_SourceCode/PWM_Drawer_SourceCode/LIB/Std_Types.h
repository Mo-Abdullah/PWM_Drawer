/*
 * Std_Types.h
 *
 * Created: 07-Oct-23 06:28:36 PM
 * Author: Mohamed Hassan Ali Abdullah
 */ 

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Standard Types for Unsigned Integers */
typedef unsigned char u8_t;
typedef unsigned short int u16_t;
typedef unsigned int u32_t;
typedef unsigned long long int u64_t;

/* Standard Types for Signed Integers */
typedef signed char s8_t;
typedef signed short int s16_t;
typedef signed int s32_t;
typedef signed long long int s64_t;

/* Char for Chars and Strings */
typedef char ch8_t;

/* Standard Floating Point Numbers */
typedef float f32_t;
typedef double f64_t;
typedef long double f80_t;

/* Enumeration Boolean -> True or False */
typedef enum {False, True} Bool;
	
/* Null Definition */
#define Null       0
#define NullChar   '\0'

/* Null Pointer */
#define NullPointer ((void*)0)

#endif /* STD_TYPES_H_ */