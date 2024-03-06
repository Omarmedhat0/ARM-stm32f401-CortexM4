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
#include "MCAL/GPIO.h"
#include "HAL/Switch_Cfg.h"
#include "HAL/Switch.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/********************Macros for the SWITCH Ports********************/
#define SWITCH_PORTA  	(void *)(0x40020000)
#define SWITCH_PORTB	(void *)(0x40020400)
#define SWITCH_PORTC  	(void *)(0x40020800)
#define SWITCH_PORTD 	(void *)(0x40020C00)
#define SWITCH_PORTE 	(void *)(0x40021000)
#define SWITCH_PORTH	(void *)(0x40021C00)

/********************Macros for the SWITCH Pins********************/
#define SWITCH_PIN0 	0x00000000
#define SWITCH_PIN1 	0x00000001
#define SWITCH_PIN2 	0x00000002
#define SWITCH_PIN3 	0x00000003
#define SWITCH_PIN4 	0x00000004
#define SWITCH_PIN5 	0x00000005
#define SWITCH_PIN6 	0x00000006
#define SWITCH_PIN7 	0x00000007
#define SWITCH_PIN8 	0x00000008
#define SWITCH_PIN9		0x00000009
#define SWITCH_PIN10 	0x0000000A
#define SWITCH_PIN11 	0x0000000B
#define SWITCH_PIN12 	0x0000000C
#define SWITCH_PIN13 	0x0000000D
#define SWITCH_PIN14 	0x0000000E
#define SWITCH_PIN15 	0x0000000F
/********************Macros for the SWITCH type of connection********************/
#define SWITCH_INPUT_FL					0x00000000
#define SWITCH_INPUT_PL					0x00000008
#define SWITCH_INPUT_PD					0x00000010
/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*Global array to set Switchs configuration
 I make an extra extern here beacuse of linker issue when declare and constant global array 
 It implicitly make it static fri this file so the other files can't see it */
 const  Switch_Config_t SwitchS[_Switch_Num] = {
   /*Ex : Set Switch1 Configuration*/
    [Switch1] = {
        .Pin = SWITCH_PIN4,
        .Port = SWITCH_PORTB,
        .Connection = SWITCH_INPUT_FL
    },
   [Switch2] = {
        .Pin = SWITCH_PIN5,
        .Port = SWITCH_PORTB,
        .Connection = SWITCH_INPUT_FL
    }

};
