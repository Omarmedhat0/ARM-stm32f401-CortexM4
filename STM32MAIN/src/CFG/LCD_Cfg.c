/*
 ============================================================================
 Name        : LCD_CGF.c
 Author      : Omar Medhat Mohamed
 Description : Source Configuration file for the LCD driver
 Date        : 17/2/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "MCAL/GPIO.h"
#include "CFG/LCD_Cfg.h"
#include "HAL/LCD.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/********************Macros for the LCD Ports********************/
#define LCD_PORTA  	(void *)(0x40020000)
#define LCD_PORTB	(void *)(0x40020400)
#define LCD_PORTC  	(void *)(0x40020800)
#define LCD_PORTD 	(void *)(0x40020C00)
#define LCD_PORTE 	(void *)(0x40021000)
#define LCD_PORTH	(void *)(0x40021C00)

/********************Macros for the LCD Pins********************/
#define LCD_PIN0 	0x00000000
#define LCD_PIN1 	0x00000001
#define LCD_PIN2 	0x00000002
#define LCD_PIN3 	0x00000003
#define LCD_PIN4 	0x00000004
#define LCD_PIN5 	0x00000005
#define LCD_PIN6 	0x00000006
#define LCD_PIN7 	0x00000007
#define LCD_PIN8 	0x00000008
#define LCD_PIN9	0x00000009
#define LCD_PIN10 	0x0000000A
#define LCD_PIN11 	0x0000000B
#define LCD_PIN12 	0x0000000C
#define LCD_PIN13 	0x0000000D
#define LCD_PIN14 	0x0000000E
#define LCD_PIN15 	0x0000000F

/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*Global array to set LCDs configurationt */
const  LCD_Config_t LCDS[_LCD_Num] = {
   /*Ex : Set LCD1 Configuration*/
    [D0] = {.Port=LCD_PORTA , .Pin= LCD_PIN0 },
    [D1] = {.Port=LCD_PORTA , .Pin= LCD_PIN1 },
    [D2] = {.Port=LCD_PORTA , .Pin= LCD_PIN2 },
    [D3] = {.Port=LCD_PORTA , .Pin= LCD_PIN3 },
    [D4] = {.Port=LCD_PORTA , .Pin= LCD_PIN4 },
    [D5] = {.Port=LCD_PORTA , .Pin= LCD_PIN5 },
    [D6] = {.Port=LCD_PORTA , .Pin= LCD_PIN6 },
    [D7] = {.Port=LCD_PORTA , .Pin= LCD_PIN7 },
    [RS] = {.Port=LCD_PORTA , .Pin= LCD_PIN8 },
    [RW] = {.Port=LCD_PORTA , .Pin= LCD_PIN9 },
    [EN] = {.Port=LCD_PORTA , .Pin= LCD_PIN10 },
};
