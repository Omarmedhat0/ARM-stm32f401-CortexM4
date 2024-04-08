/*
 ============================================================================
 Name        : LED.h
 Author      : Omar Medhat Mohamed
 Description : Header File for the LED Driver
 Date        : 17/2/2024
 ============================================================================
 */
#ifndef LED_H_
#define LED_H_
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include  	"LIB/std_types.h"
#include 	"LIB/Mask32.h"
#include 	"LIB/Error.h"
#include   	"CFG/LED_Cfg.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LED_ON 					0x00000001
#define LED_OFF 				0x00010000
#define LED_REV 				0x00010001
#define LED_FWD 				0x00000000

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*Struct for new LED  configuration */
typedef struct
{
	uint32_t  Pin;
	void* 	  Port;
	uint32_t  Connection;
	uint32_t  Init_Status;

}LED_Config_t;

/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
/**
 * @brief    : Initializes a LED pin based on the provided configuration.
 * @param[in]: Void.
 * @return   : Error_enumStatus_t - Error status indicating success or failure of the initialization.
 * @details  : This function initializes a LED pin according to the provided configuration.
 */
Error_enumStatus_t LED_Init (void);
/**
 * @brief    : Sets the value of a LED pin to a specified state.
 * @param[in]: Copy_LEDName - LED Name or ID.
 * @param[in]: Copy_LEDStatus - The state that desired to be set if it was LED_ON or LED_OFF .
 * @return   : Error_enumStatus_t - Error status indicating success or failure of setting the pin value.
 * @details  : This function sets the value of a LED pin to the specified state (high or low).
 */
Error_enumStatus_t LED_Set_Status(uint32_t Copy_LEDName , uint32_t Copy_LEDStatus);




#endif /* LED_H_ */
