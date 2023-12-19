/*
 * GLCD.h
 *
 * Created: 10-Dec-23 01:56:22 PM
 * Author: Mohamed Hassan Ali Hassan
 */ 


#ifndef GLCD_H_
#define GLCD_H_

#include "GLCD_Config.h"
/* Data Types for Graphical LCD Module */

typedef enum 
{
	GLCD_DISPLAY_OFF				= (0x3EU),
	GLCD_DISPLAY_ON					= (0x3FU),
	GLCD_SET_Y_ADDRESS_PREFIX		= (0x40U),
	GLCD_SET_X_ADDRESS_PREFIX		= (0xB8U),
	GLCD_SET_Z_ADDRESS_PREFIX		= (0xC0U)
}GLCD_CommandType;

typedef enum 
{
	GLCD_INSTRUCTION_REG,
	GLCD_DATA_REG
}GLCD_RegisterSelectType;

typedef enum 
{
	GLCD_NO_PAGES,
	GLCD_PAGE_0,
	GLCD_PAGE_1,
	GLCD_BOTH_PAGES
}GLCD_PageSelectType;

typedef enum 
{
	GLCD_WRITE_MODE,
	GLCD_READ_MODE
}GLCD_ReadWriteType;


/* Function Prototypes for Graphical LCD Module */
void GLCD_Init(void);
void GLCD_SelectPage(GLCD_PageSelectType Page);
void GLCD_SendCommand(GLCD_CommandType Instruction);
void GLCD_SendData(u8_t Data);
void GLCD_Reset(void);
void GLCD_DisplayCharacter(char Data);
void GLCD_DisplayString(char* Data_Ptr);
void GLCD_DisplayInteger(s32_t Data);
void GLCD_DisplayFloatingNumber(f32_t Data);
void GLCD_ClearDisplay(void);
void GLCD_GoToLine(u8_t Line);
void GLCD_DisplayPattern(u64_t Pattern);

#endif /* GLCD_H_ */