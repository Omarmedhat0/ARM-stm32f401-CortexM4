/*
 ============================================================================
 Name        : LCD.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the LCD Driver
 Date        : 17/2/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "HAL/LCD.h"
#include "MCAL/GPIO.h"
/*******************************************************************************
 *                              Variables                                       *
 *******************************************************************************/

 extern  const LCD_Config_t  LCDS[_LCD_Num];
/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*
 * @brief    : Initializes a LCD pin based on the provided configuration.
 * @param[in]: Void.
 * @return   : Error_enumStatus_t - Error status indicating success or failure of the initialization.
 * @details  : This function initializes a LCD pin according to the provided configuration.
 */
Error_enumStatus_t LCD_Init (void)
{
    /* Local Variable to store error status */
	Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk ;
    /*Creat an object from  GPIO_Config_t sturct to configure the GPIO
      Peripheral according to user configuration for privided LCDs*/
    GPIO_Config_t Loc_LCD_GPIO_Handler ; 
    /*Configure all LCDs speed as GPIO_HIGH_SPEED */    
    Loc_LCD_GPIO_Handler.Speed = GPIO_HIGH_SPEED ;
    /*Configure all LCDs Moode as Push PUll */ 
    Loc_LCD_GPIO_Handler.Mood = GPIO_OUTPUT_PP ;
    /*Initiate a local index to loop with it */
    uint8_t Loc_idx = 0 ;
    /*Loop for each LCD to configure it's port and pin in GPIO*/
    for (Loc_idx = 0 ; Loc_idx < _LCD_Num ; Loc_idx ++)
    {
        /*Send the Pin of LCD number Loc_idx to configuartion structure in gpio*/
        Loc_LCD_GPIO_Handler.Pin = LCDS[Loc_idx].Pin ;
        /*Send the Port of LCD number Loc_idx to configuartion structure in gpio*/
        Loc_LCD_GPIO_Handler.Port = LCDS[Loc_idx].Port ; 
        /*Init GPIO pins with the required configuration */
        Loc_enumReturnStatus=  GPIO_InitPin(&Loc_LCD_GPIO_Handler);
        /*Set the init status for the required LCD */
        Loc_enumReturnStatus=  GPIO_Set_PinValue(LCDS[Loc_idx].Port , LCDS[Loc_idx].Pin ,(LCDS[Loc_idx].Connection)^(LCDS[Loc_idx].Init_Status )) ;
    }
    /*Return the error status*/
    return Loc_enumReturnStatus ;
}

