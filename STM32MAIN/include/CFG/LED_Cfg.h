/*
 ============================================================================
 Name        : LED_Cfg.h
 Author      : Omar Medhat Mohamed
 Description : Header Config File for the LED Driver
 Date        : 17/2/2024
 ============================================================================
 */
#ifndef LED_CFG_H_
#define LED_CFG_H_
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
/* Configure The Leds Namein this Enum */
typedef enum 
{
	/* EX : Led */
	Green_Light,
	Yellow_Light,
	Red_Light,
	/*Indicate number of Ledd don't use it */
    _Led_Num 
}LEDS_t;

#endif


