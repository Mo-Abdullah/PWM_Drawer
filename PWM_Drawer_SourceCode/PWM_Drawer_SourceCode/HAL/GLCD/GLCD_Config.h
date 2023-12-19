/*
 * GLCD_Config.h
 *
 * Created: 10-Dec-23 02:56:22 PM
 * Author: Mohamed Hassan Ali Hassan
 */

#ifndef GLCD_CONFIG_H_
#define GLCD_CONFIG_H_

/* Graphical LCD Characteristics */
#define GLCD_MAX_LINES							(8U)
#define GLCD_MAX_LINE_PIXEL_WIDTH				(128U)
#define GLCD_MAX_PAGE_PIXEL_WIDTH				(64U)

/* Graphical LCD Connections */
#define GLCD_CTRL_PORT							(PORTB)
#define GLCD_ENABLE_PIN							(PIN0)
#define GLCD_RW_PIN								(PIN1)
#define GLCD_RS_PIN								(PIN2)
#define GLCD_PAGE_SELECT_PIN_1					(PIN4)
#define GLCD_PAGE_SELECT_PIN_2					(PIN5)
#define GLCD_RESET_PIN							(PIN6)
#define GLCD_DATA_PORT							(PORTA)
#define GLCD_DATA_D0_PIN						(PIN0)
#define GLCD_DATA_D1_PIN						(PIN1)
#define GLCD_DATA_D2_PIN						(PIN2)
#define GLCD_DATA_D3_PIN						(PIN3)
#define GLCD_DATA_D4_PIN						(PIN4)
#define GLCD_DATA_D5_PIN						(PIN5)
#define GLCD_DATA_D6_PIN						(PIN6)
#define GLCD_DATA_D7_PIN						(PIN7)

#endif /* GLCD_CONFIG_H_ */