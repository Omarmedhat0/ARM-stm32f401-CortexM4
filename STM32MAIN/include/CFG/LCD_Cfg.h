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
/* Configure The LCDs Namein this Enum */
typedef enum 
{
	/* EX : LCD */
	Green_Light,
	Yellow_Light,
	Red_Light,
	/*Indicate number of LCDd don't use it */
    _LCD_Num 
}LCDS_t;

#endif


