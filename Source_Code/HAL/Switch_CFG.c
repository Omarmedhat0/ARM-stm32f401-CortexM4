/*
 ============================================================================
 Name        : Switch_CGF.c
 Author      : Omar Medhat Mohamed
 Description : Source Configuration file for the Switch driver
 Date        : 17/2/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "GPIO.h"
#include "Switch_CFG.h"
#include "Switch.h"


/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*Global array to set Switchs configuration
 I make an extra extern here beacuse of linker issue when declare and constant global array 
 It implicitly make it static fri this file so the other files can't see it */
extern const  Switch_Config_t SwitchS[_Switch_Num] = {
   /*Ex : Set Switch1 Configuration*/
    [Switch1] = {
        .Pin = GPIO_PIN4,
        .Port = GPIO_PORTB,
        .Connection = GPIO_INPUT_PL
    },
   [Switch2] = {
        .Pin = GPIO_PIN5,
        .Port = GPIO_PORTB,
        .Connection = GPIO_INPUT_PL
    }

};
