/*
 ============================================================================
 Name        : CLK_CONTROL.h
 Author      : Omar Medhat Mohamed
 Description : Header File for the CLK_CONTROL Module
 Date        : 5/3/2024
 ============================================================================
 */
#ifndef CLK_CONTROL_H_
#define CLK_CONTROL_H_
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include  	"LIB/std_types.h"
#include 	"LIB/Mask32.h"
#include 	"LIB/Error.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/************GPIO Set Clcok Values************/
/************AHB1_BUS_Peripheral_Masks ************/
#define GPIOA 	0x00000001
#define GPIOB 	0x00000002
#define GPIOC 	0x00000004
#define GPIOD 	0x00000008
#define GPIOE 	0x00000010
#define GPIOH 	0x00000080
/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
/*
 * @brief    : Set Clock ON For Certain GPIO Port.
 * @param[in]: Copy_PortName Port Name.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of setting the clock on.
 * @details  : This function turns on the specified clock source for specific GPIO portt. 
 */
Error_enumStatus_t Set_PORT_Clock_ON (uint32_t Copy_PortName);


#endif
