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
/*
 * @brief    : 
 * @param[in]: 
 * @return   :
 * @details  :
 */

Error_enumStatus_t LCD_InitAsync (void);

Error_enumStatus_t LCD_Get_Status(uint8_t* Ptr_LCDStatus);

Error_enumStatus_t LCD_Clear_ScreenAsync(void);

Error_enumStatus_t LCD_Write_StringAsync(const uint8_t* Ptr_string, uint16_t size);

Error_enumStatus_t LCD_Set_CursorPosAsync(uint8_t Copy_LCDPosX , uint8_t Copy_LCDPosY );

/*Error_enumStatus_t LCD_Set_WriteCallBack(LCD_CBF_t Copy_WriteCBF);
Error_enumStatus_t LCD_Set_ClearCallBack(LCD_CBF_t Copy_ClearCBF);
Error_enumStatus_t LCD_Set_SetCursorCallBack(LCD_CBF_t Copy_SetCursorCBF);*/


#endif /* LCD_H_ */
