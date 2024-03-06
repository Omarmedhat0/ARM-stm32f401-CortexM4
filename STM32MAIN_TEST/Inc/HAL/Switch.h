/*
 ============================================================================
 Name        : Switch.h
 Author      : Omar Medhat Mohamed
 Description : Header File for the Switch Driver
 Date        : 17/2/2024
 ============================================================================
 */
#ifndef Switch_H_
#define Switch_H_
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include  	"LIB/std_types.h"
#include 	"LIB/Mask32.h"
#include 	"LIB/Error.h"
#include   	"HAL/Switch_Cfg.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define Switch_PRESSED 				0x00000001
#define Switch_RELEASED 			0x00000000
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*Struct for new Switch  configuration */
typedef struct
{
	u32_t  Pin;
	void* 	  Port;
	u32_t  Connection;
}Switch_Config_t;

/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
/*
 * @brief    : Initializes a Switch pin based on the provided configuration.
 * @param[in]: Void.
 * @return   : Error_enumStatus_t - Error status indicating success or failure of the initialization.
 * @details  : This function initializes a Switch pin according to the provided configuration.
 */
Error_enumStatus_t Switch_Init (void);
/*
 * @brief    : Sets the value of a Switch pin to a specified state.
 * @param[in]: Copy_SwitchName - Switch Name or ID.
 * @param[in]: Copy_SwitchStatus - The state that desired to be set if it was Switch_PRESSED or Switch_RELEASED .
 * @return   : Error_enumStatus_t - Error status indicating success or failure of setting the pin value.
 * @details  : This function sets the value of a Switch pin to the specified state (high or low).
 */
Error_enumStatus_t Switch_Get_Status(u32_t Copy_SwitchName , u8_t* Ptr_Status );




#endif /* Switch_H_ */
