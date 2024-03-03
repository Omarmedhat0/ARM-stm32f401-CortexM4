/*
 ============================================================================
 Name        : NVIC.h
 Author      : Omar Medhat Mohamed
 Description : Header File for the NVIC Driver
 Date        : 3/3/2024
 ============================================================================
 */
#ifndef NVIC_H_
#define NVIC_H_
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include  	"LIB/std_types.h"
#include 	"LIB/Mask32.h"
#include 	"LIB/Error.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
/*
 * @brief    : 
 * @param[in]: 
 * @return   : 
 * @details  : 
 */
Error_enumStatus_t Set_Interrupt_Priority ();

Error_enumStatus_t Set_Interrupt_Enable ();

Error_enumStatus_t Set_Interrupt_Disable ();

Error_enumStatus_t Set_Pending ();

Error_enumStatus_t Clear_Pending ();

Error_enumStatus_t Get_Interrupt_Status();

#endif /* NVIC_H_ */
