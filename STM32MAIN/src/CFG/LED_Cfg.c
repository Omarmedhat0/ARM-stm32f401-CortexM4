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
 *                             Implementation   				                *
 *******************************************************************************/
/*Global array to set LEDs configuration
 I make an extra extern here beacuse of linker issue when declare and constant global array 
 It implicitly make it static fri this file so the other files can't see it */
const  LED_Config_t LEDS[_Led_Num] = {
   /*Ex : Set Led1 Configuration*/
    [Led1] = {
        .Pin = GPIO_PIN0,
        .Port = GPIO_PORTA,
        .Connection = LED_FWD,
        .Init_Status = LED_OFF
    },
    [Led2] = {
        .Pin = GPIO_PIN1,
        .Port = GPIO_PORTA,
        .Connection = LED_FWD,
        .Init_Status = LED_OFF
    }

};
