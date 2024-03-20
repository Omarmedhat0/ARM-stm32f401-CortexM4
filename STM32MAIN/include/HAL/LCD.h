/*
 ============================================================================
 Name        : LCD.h
 Author      : Omar Medhat Mohamed
 Description : Header File for the LCD Driver
 Date        : 17/2/2024
 ============================================================================
 */
#ifndef LCD_H_
#define LCD_H_
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include  	"LIB/std_types.h"
#include 	"LIB/Mask32.h"
#include 	"LIB/Error.h"
#include   	"CFG/LCD_Cfg.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LCD_ON 					0x00000001
#define LCD_OFF 				0x00010000
#define LCD_REV 				0x00010001
#define LCD_FWD 				0x00000000

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*Struct for new LCD  configuration */
typedef struct
{
	uint32_t  Pin;
	void* 	  Port;
	uint32_t  Connection;
	uint32_t  Init_Status;

}LCD_Config_t;

/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
/*
 * @brief    : Initializes a LCD pin based on the provided configuration.
 * @param[in]: Void.
 * @return   : Error_enumStatus_t - Error status indicating success or failure of the initialization.
 * @details  : This function initializes a LCD pin according to the provided configuration.
 */
Error_enumStatus_t LCD_Init (void);
/*
 * @brief    : Sets the value of a LCD pin to a specified state.
 * @param[in]: Copy_LCDName - LCD Name or ID.
 * @param[in]: Copy_LCDStatus - The state that desired to be set if it was LCD_ON or LCD_OFF .
 * @return   : Error_enumStatus_t - Error status indicating success or failure of setting the pin value.
 * @details  : This function sets the value of a LCD pin to the specified state (high or low).
 */
Error_enumStatus_t LCD_Get_Status(uint32_t Copy_LCDName , uint32_t Copy_LCDStatus);

Error_enumStatus_t LCD_Clear_Screen(uint32_t Copy_LCDName , uint32_t Copy_LCDStatus);

Error_enumStatus_t LCD_Write_String(uint32_t* Ptr_string , uint8_t size , uint8_t postion_x , uint8_t postion_y );

Error_enumStatus_t LCD_Set_Cursor(uint32_t Copy_LCDName );



#endif /* LCD_H_ */
