/*
 ============================================================================
 Name        : LED_CGF.c
 Author      : Omar Medhat Mohamed
 Description : Source Configuration file for the LED driver
 Date        : 17/2/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "MCAL/GPIO.h"
#include "CFG/LED_Cfg.h"
#include "HAL/LED.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/********************Macros for the LED Ports********************/
#define LED_PORTA  	(void *)(0x40020000)
#define LED_PORTB	(void *)(0x40020400)
#define LED_PORTC  	(void *)(0x40020800)
#define LED_PORTD 	(void *)(0x40020C00)
#define LED_PORTE 	(void *)(0x40021000)
#define LED_PORTH	(void *)(0x40021C00)

/********************Macros for the LED Pins********************/
#define LED_PIN0 	0x00000000
#define LED_PIN1 	0x00000001
#define LED_PIN2 	0x00000002
#define LED_PIN3 	0x00000003
#define LED_PIN4 	0x00000004
#define LED_PIN5 	0x00000005
#define LED_PIN6 	0x00000006
#define LED_PIN7 	0x00000007
#define LED_PIN8 	0x00000008
#define LED_PIN9	0x00000009
#define LED_PIN10 	0x0000000A
#define LED_PIN11 	0x0000000B
#define LED_PIN12 	0x0000000C
#define LED_PIN13 	0x0000000D
#define LED_PIN14 	0x0000000E
#define LED_PIN15 	0x0000000F

/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*Global array to set LEDs configuration
 I make an extra extern here beacuse of linker issue when declare and constant global array 
 It implicitly make it static fri this file so the other files can't see it */
const  LED_Config_t LEDS[_Led_Num] = {
   /*Ex : Set Led1 Configuration*/
    [Green_Light] = {.Pin = LED_PIN0,.Port = LED_PORTA,.Connection = LED_FWD,.Init_Status = LED_OFF},
    [Yellow_Light] = {.Pin = LED_PIN1,.Port = LED_PORTA,.Connection = LED_FWD,.Init_Status = LED_OFF},
    [Red_Light] = {.Pin = LED_PIN2,.Port = LED_PORTA,.Connection = LED_FWD,.Init_Status = LED_OFF}
};
