/*
 ============================================================================
 Name        : Switch.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the Switch Driver
 Date        : 17/2/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "HAL/Switch.h"
#include "MCAL/GPIO.h"
/*******************************************************************************
 *                             Definitions                                      *
 *******************************************************************************/
#define Get_CURRENT_CONNECTION_SHIFT_MASK 3

/*******************************************************************************
 *                              Variables                                       *
 *******************************************************************************/

extern const Switch_Config_t SwitchS[_Switch_Num];
/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*
 * @brief    : Initializes a Switch pin based on the provided configuration.
 * @param[in]: Void.
 * @return   : Error_enumStatus_t - Error status indicating success or failure of the initialization.
 * @details  : This function initializes a Switch pin according to the provided configuration.
 */
Error_enumStatus_t Switch_Init(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    /*Creat an object from  GPIO_Config_t sturct to configure the GPIO
      Peripheral according to user configuration for privided Switchs*/
    GPIO_Config_t Loc_Switch_GPIO_Handler;
    /*Initiate a local index to loop with it */
    uint8_t Loc_idx = 0;
    /*Loop for each Switch to configure it's port and pin in GPIO*/
    for (Loc_idx = 0; Loc_idx < _Switch_Num; Loc_idx++)
    {
        /*Send the Pin of Switch number Loc_idx to configuartion structure in gpio*/
        Loc_Switch_GPIO_Handler.Pin = SwitchS[Loc_idx].Pin;
        /*Send the Port of Switch number Loc_idx to configuartion structure in gpio*/
        Loc_Switch_GPIO_Handler.Port = SwitchS[Loc_idx].Port;
        /*Send the Mood of Switch number Loc_idx to configuartion structure in gpio*/
        Loc_Switch_GPIO_Handler.Mood = SwitchS[Loc_idx].Connection;
        /*Init GPIO pins with the required configuration */
        Loc_enumReturnStatus = GPIO_InitPin(&Loc_Switch_GPIO_Handler);
    }
    /*Return the error status*/
    return Loc_enumReturnStatus;
}

/*
 * @brief    : Sets the value of a Switch pin to a specified state.
 * @param[in]: Copy_SwitchName - Switch Name or ID.
 * @param[in]: Copy_SwitchStatus - The state that desired to be set if it was Switch_ON or Switch_OFF .
 * @return   : Error_enumStatus_t - Error status indicating success or failure of setting the pin value.
 * @details  : This function sets the value of a Switch pin to the specified state (high or low).
 */
Error_enumStatus_t Switch_Get_Status(uint32_t Copy_SwitchName, uint8_t *Ptr_Status)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    /*Local variable to store the status*/
    uint8_t Loc_Status = 0;
    /*Check if the switch name is valid or not */
    if (Copy_SwitchName >= _Switch_Num)
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    else
    {
        /*Set the required pin the the required status whether it was on of off */
        GPIO_Get_GetPinValue(SwitchS[Copy_SwitchName].Port, SwitchS[Copy_SwitchName].Pin, &Loc_Status);
        /*Return the error status*/
        *Ptr_Status = Loc_Status ^ (((SwitchS[Copy_SwitchName].Connection) >> Get_CURRENT_CONNECTION_SHIFT_MASK) & 0x1);
    }
    return Loc_enumReturnStatus;
}
