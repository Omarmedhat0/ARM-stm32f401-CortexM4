/*
 ============================================================================
 Name        : LCD_Cfg.h
 Author      : Omar Medhat Mohamed
 Description : Header Config File for the LCD Driver
 Date        : 17/2/2024
 ============================================================================
 */
#ifndef LCD_CFG_H_
#define LCD_CFG_H_
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
/* Configure The LCDs Name in this Enum */
typedef enum 
{
	D0,
	D1,
	D2,
	D3,
	D4,
	D5,
	D6,
	D7,
	RS,
	RW,
	EN,
	/*Indicate number of LCDd don't use it */
    _LCD_Num 
}LCDS_t;

#endif


