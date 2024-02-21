/*
 ============================================================================
 Name        : GPIO.h
 Author      : Omar Medhat Mohamed
 Description : Header File for the GPIO Driver
 Date        : 16/2/2024
 ============================================================================
 */
#ifndef GPIO_H_
#define GPIO_H_
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include  	"LIB/std_types.h"
#include 	"LIB/Mask32.h"
#include 	"LIB/Error.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define GPIO_PORTA  (void *)(0x40020000)
#define GPIO_PORTB	(void *)(0x40020400)
#define GPIO_PORTC  (void *)(0x40020800)
#define GPIO_PORTD 	(void *)(0x40020C00)
#define GPIO_PORTE 	(void *)(0x40021000)
#define GPIO_PORTH	(void *)(0x40021C00)

/********************Macros for the GPIO pins********************/
#define GPIO_PIN0 	0x00000000
#define GPIO_PIN1 	0x00000001
#define GPIO_PIN2 	0x00000002
#define GPIO_PIN3 	0x00000003
#define GPIO_PIN4 	0x00000004
#define GPIO_PIN5 	0x00000005
#define GPIO_PIN6 	0x00000006
#define GPIO_PIN7 	0x00000007
#define GPIO_PIN8 	0x00000008
#define GPIO_PIN9	0x00000009
#define GPIO_PIN10 	0x0000000A
#define GPIO_PIN11 	0x0000000B
#define GPIO_PIN12 	0x0000000C
#define GPIO_PIN13 	0x0000000D
#define GPIO_PIN14 	0x0000000E
#define GPIO_PIN15 	0x0000000F
/********************Macros for the GPIO SPEEDS********************/
#define GPIO_LOW_SPEED			0x00000000
#define GPIO_MEDIUM_SPEED		0x00000001
#define GPIO_HIGH_SPEED			0x00000002
#define GPIO_VERY_HIGH_SPEED	0x00000003
/********************Macros for the GPIO MOODS********************/
#define GPIO_INPUT_FL					0x00000000
#define GPIO_INPUT_PL					0x00000008
#define GPIO_INPUT_PD					0x00000010

#define GPIO_OUTPUT_PP 					0x00000001
#define GPIO_OUTPUT_PP_PL				0x00000009
#define GPIO_OUTPUT_PP_PD				0x00000011
#define GPIO_OUTPUT_OD					0x00000005
#define GPIO_OUTPUT_OD_PL				0x0000000D
#define GPIO_OUTPUT_OD_PD				0x00000015

#define GPIO_ANALOG 					0x00000003

#define GPIO_AF_PP 						0x00000002
#define GPIO_AF_PP_PL					0x0000000A
#define GPIO_AF_PP_PD					0x00000012
#define GPIO_AF_OD						0x00000006
#define GPIO_AF_OD_PL					0x0000000E
#define GPIO_AF_OD_PD					0x00000016

#define GPIO_SET_PIN 					0x00000001
#define GPIO_RESET_PIN 					0x00010000

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*Struct for new GPIO pin configuration */
typedef struct
{
	/**
	 *@brief : Everything Ok, Function had Performed Correctly.
	 */
	uint32_t  Pin;
	void* 	  Port;
	uint32_t  Speed;
	uint32_t  Mood;

}GPIO_Config_t;

/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
/*
 * @brief    : Initializes a GPIO pin based on the provided configuration.
 * @param[in]: Loc_GPIOElement - Pointer to a structure containing the GPIO pin configuration.
 * @return   : Error_enumStatus_t - Error status indicating success or failure of the initialization.
 * @details  : This function initializes a GPIO pin according to the provided configuration.
 */
Error_enumStatus_t GPIO_InitPin (GPIO_Config_t *Loc_GPIOElement);
/*
 * @brief    : Sets the value of a GPIO pin to a specified state.
 * @param[in]: Port - Pointer to the GPIO port (From GPIO_PORTA to GPIO_PORTH).
 * @param[in]: Copy_PinNum - The number of the pin to be set (FROM GPIO_PIN0 TO GPIO_PIN16) .
 * @param[in]: Copy_PinState - The state to set the pin to (GPIO_SET_PIN or GPIO_RESET_PIN).
 * @return   : Error_enumStatus_t - Error status indicating success or failure of setting the pin value.
 * @details  : This function sets the value of a GPIO pin to the specified state (high or low).
 */
Error_enumStatus_t GPIO_Set_PinValue(void *Port , uint32_t Copy_PinNum , uint32_t Copy_PinState );
/*
 * @brief    : Gets the current value of a GPIO pin.
 * @param[in]: Port - Pointer to the GPIO port (From GPIO_PORTA to GPIO_PORTH).
 * @param[in]: Copy_PinNum - The number of the pin to be set (FROM GPIO_PIN0 TO GPIO_PIN16) .
 * @param[out]: PinStatus - Pointer to a variable to store the pin status (1 for high, 0 for low).
 * @return   : Error_enumStatus_t - Error status indicating success or failure of reading the pin value.
 * @details  : This function reads the current value of a GPIO pin and stores it in PinStatus.
 */
Error_enumStatus_t GPIO_Get_GetPinValue(void *Port , uint32_t Copy_PinNum,  uint8_t * PinStatus) ;



#endif /* GPIO_H_ */
