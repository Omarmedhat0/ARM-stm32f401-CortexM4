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
#define LCD_DISPLAY_LINE1		0
#define LCD_DISPLAY_LINE2		1
#define LCD_DISPLAY_LINE3		3
#define LCD_DISPLAY_LINE4		4

#define LCD_DISPLAY_COL1		0
#define LCD_DISPLAY_COL2		1
#define LCD_DISPLAY_COL3		2
#define LCD_DISPLAY_COL4		3
#define LCD_DISPLAY_COL5		4
#define LCD_DISPLAY_COL6		5
#define LCD_DISPLAY_COL7		6
#define LCD_DISPLAY_COL8		7
#define LCD_DISPLAY_COL9		8
#define LCD_DISPLAY_COL10		9
#define LCD_DISPLAY_COL11		10
#define LCD_DISPLAY_COL12		11
#define LCD_DISPLAY_COL13		12
#define LCD_DISPLAY_COL14		13
#define LCD_DISPLAY_COL15		14
#define LCD_DISPLAY_COL16		15

/*Configure Maximum number of rows in LCD */
#define MAX_NUM_OF_LINES 		2
/*Configure Maximum number of column in LCD */
#define MAX_NUM_OF_CHARACTERS 	16

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
/*typedef void (*LCD_CBF_t)(void);*/
/*Struct for new LCD  configuration */
typedef struct
{
	uint32_t  Pin;
	void* 	  Port;
}LCD_Config_t;

/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
/**
 * @brief    : Initializes the LCD asynchronously.
 * @details  : This function sets the LCD state to LCD_Init.
 * @param    : None
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the initialization process.
 **/
Error_enumStatus_t LCD_InitAsync (void);
/**
 * @brief    : Retrieves the current status of the LCD.
 * @details  : This function retrieves the current status of the LCD and stores it in the provided pointer variable.
 * @param[out]: Ptr_LCDStatus Pointer to a variable to store the current status of the LCD.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of retrieving the LCD status.
 **/
Error_enumStatus_t LCD_Get_Status(uint8_t* Ptr_LCDStatus);
/**
 * @brief    : Clears the LCD screen asynchronously.
 * @details  : This function sets the LCD user request state and type to initiate the clear process if the LCD state is LCD_Operation
 *             and the LCD user request state is LCD_ReqReady.
 * @param    : None
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the clear process initiation.
 **/
Error_enumStatus_t LCD_Clear_ScreenAsync(void);
/**
 * @brief    : Writes a string to the LCD asynchronously.
 * @details  : This function sets the LCD user request state and type to initiate the write process with the provided string
 *             if the LCD state is LCD_Operation and the LCD user request state is LCD_ReqReady.
 * @param[in]: Ptr_string Pointer to the string to be written to the LCD.
 * @param[in]: size       Size of the string to be written.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the write process initiation.
 **/
Error_enumStatus_t LCD_Write_StringAsync(const uint8_t* Ptr_string, uint16_t size);
/**
 * @brief    : Sets the cursor position on the LCD asynchronously.
 * @details  : This function sets the cursor position on the LCD based on the provided row and column numbers.
 *             It sets the LCD user request state and type to initiate the process if the LCD state is LCD_Operation
 *             and the LCD user request state is LCD_ReqReady.
 * @param[in]: Copy_LCDPosX Row number for the cursor position.
 * @param[in]: Copy_LCDPosY Column number for the cursor position.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the position setting process initiation.
 **/
Error_enumStatus_t LCD_Set_CursorPosAsync(uint8_t Copy_LCDPosX , uint8_t Copy_LCDPosY );
/**
 * @brief    : Writes a number to the LCD asynchronously.
 * @details  : This function writes a number to the LCD based on the provided number.
 *             It sets the LCD user request state and type to initiate the write number process if the LCD state is LCD_Operation
 *             and the LCD user request state is LCD_ReqReady.
 * @param[in]: Copy_Number Number to be written to the LCD.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the write number process initiation.
 **/
Error_enumStatus_t LCD_Write_NUmberAsync(uint32_t Copy_Number);


#endif /* LCD_H_ */
