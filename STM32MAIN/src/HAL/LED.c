/*
 ============================================================================
 Name        : LED.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the LED Driver
 Date        : 17/2/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "HAL/LED.h"
#include "MCAL/GPIO.h"

/*******************************************************************************
 *                              Variables                                       *
 *******************************************************************************/

 extern  const LED_Config_t  LEDS[_Led_Num];
/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*
 * @brief    : Initializes a LED pin based on the provided configuration.
 * @param[in]: Void.
 * @return   : Error_enumStatus_t - Error status indicating success or failure of the initialization.
 * @details  : This function initializes a LED pin according to the provided configuration.
 */
Error_enumStatus_t LED_Init (void)
{
    /* Local Variable to store error status */
	Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk ;
    /*Creat an object from  GPIO_Config_t sturct to configure the GPIO
      Peripheral according to user configuration for privided leds*/
    GPIO_Config_t Loc_Led_GPIO_Handler ; 
    /*Configure all LEDs speed as GPIO_HIGH_SPEED */    
    Loc_Led_GPIO_Handler.Speed = GPIO_HIGH_SPEED ;
    /*Configure all LEDs Moode as Push PUll */ 
    Loc_Led_GPIO_Handler.Mood = GPIO_OUTPUT_PP ;
    /*Initiate a local index to loop with it */
    uint8_t Loc_idx = 0 ;
    /*Loop for each led to configure it's port and pin in GPIO*/
    for (Loc_idx = 0 ; Loc_idx < _Led_Num ; Loc_idx ++)
    {
        /*Send the Pin of led number Loc_idx to configuartion structure in gpio*/
        Loc_Led_GPIO_Handler.Pin = LEDS[Loc_idx].Pin ;
        /*Send the Port of led number Loc_idx to configuartion structure in gpio*/
        Loc_Led_GPIO_Handler.Port = LEDS[Loc_idx].Port ; 
        /*Init GPIO pins with the required configuration */
        Loc_enumReturnStatus=  GPIO_InitPin(&Loc_Led_GPIO_Handler);
        /*Set the init status for the required LED */
        Loc_enumReturnStatus=  GPIO_Set_PinValue(LEDS[Loc_idx].Port , LEDS[Loc_idx].Pin ,(LEDS[Loc_idx].Connection)^(LEDS[Loc_idx].Init_Status )) ;
    }
    /*Return the error status*/
    return Loc_enumReturnStatus ;
}

/*
 * @brief    : Sets the value of a LED pin to a specified state.
 * @param[in]: Copy_LEDName - LED Name or ID.
 * @param[in]: Copy_LEDStatus - The state that desired to be set if it was LED_ON or LED_OFF .
 * @return   : Error_enumStatus_t - Error status indicating success or failure of setting the pin value.
 * @details  : This function sets the value of a LED pin to the specified state (high or low).
 */
Error_enumStatus_t LED_Set_Status(uint32_t Copy_LEDName , uint32_t Copy_LEDStatus)
{
    /* Local Variable to store error status */
	Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk ; 
    /*Set the required pin the the required status whether it was on of off */
	Loc_enumReturnStatus=  GPIO_Set_PinValue(LEDS[Copy_LEDName].Port , LEDS[Copy_LEDName].Pin ,(LEDS[Copy_LEDName].Connection)^Copy_LEDStatus ) ;
    /*Return the error status*/
    return Loc_enumReturnStatus ;
}
