/*
 ============================================================================
 Name        : CLK_CONTROL.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the CLK_CONTROL Module
 Date        : 5/3/2024
 ============================================================================
 */

/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "HAL\CLK_Control.h"
#include "MCAL\RCC.h"
/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*
 * @brief    : Set Clock ON For Certain GPIO Port.
 * @param[in]: Copy_PortName Port Name.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of setting the clock on.
 * @details  : This function turns on the specified clock source for specific GPIO portt. 
 */
Error_enumStatus_t Set_PORT_Clock_ON (uint32_t Copy_PortName)
{
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk ;
    if (Copy_PortName > GPIOH)
    {
        Loc_enumReturnStatus = Status_enumWrongInput ;
    }
    else
    {
        RCC_Enable_AHB1_Peripheral(Copy_PortName);
    }
    return Loc_enumReturnStatus ;
}
