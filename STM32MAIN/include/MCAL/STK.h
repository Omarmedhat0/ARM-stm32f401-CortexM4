/*
 ============================================================================
 Name        : STK.h
 Author      : Omar Medhat Mohamed
 Description : Header File for the STK Driver
 Date        : 8/3/2024
 ============================================================================
 */
#ifndef STK_H_
#define STK_H_
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "LIB/std_types.h"
#include "LIB/Mask32.h"
#include "LIB/Error.h"
#include "LIB/Stm32F401cc.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
 /*Configure with clock source by AHB/8 and does not assert the SysTick exception request*/
#define STK_AHB_8_DIS_INT 				0x00000000 
 /*Configure with clock source by Processor clock (AHB) and does not assert the SysTick exception request*/
#define STK_PROCESSOR_CLOCK_DIS_INT 	0x00000004 
 /*Configure with clock source by AHB/8 and  assert the SysTick exception request*/
#define STK_AHB_8_ENB_INT 				0x00000002 
 /*Configure with clock source by Processor clock (AHB) and  the SysTick exception request*/
#define STK_PROCESSOR_CLOCK_ENB_INT 	0x00000006 /*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/

typedef void (*STK_CBF_t)(void);
/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
/*
 * @brief   : Starts the SysTick timer.
 * @param   : None
 * @return  : Error status indicating success or failure.
 * @details : This function starts the SysTick timer to generate interrupts according
 *            to the configured time interval.
 */
Error_enumStatus_t STK_Start(void);
/*
 * @brief   : Sets the configuration of the SysTick timer.
 * @param   : Copy_Mode - The mode to configure the SysTick timer.
 * @return  : Error status indicating success or failure.
 * @details : This function configures the SysTick timer according to the provided mode.
 */
Error_enumStatus_t STK_SetConfig(uint32_t Copy_Mode);
/*
 * @brief   : Stops the SysTick timer.
 * @param   : None
 * @return  : Error status indicating success or failure.
 * @details : This function stops the SysTick timer from generating interrupts.
 */
Error_enumStatus_t STK_Stop(void);
/*
 * @brief   : Sets the time interval for the SysTick timer.
 * @param   : Copy_TimeMs - The time interval in milliseconds.
 * @return  : Error status indicating success or failure.
 * @details : This function sets the time interval for the SysTick timer, which determines
 *            the period between interrupts generated by the timer.
 */
Error_enumStatus_t STK_SetTimeMs(uint32_t Copy_TimeMs);
/*
 * @brief   : Sets the callback function for the SysTick timer interrupt.
 * @param   : Copy_CallBack - Pointer to the callback function.
 * @return  : Error status indicating success or failure.
 * @details : This function sets the callback function to be called when the SysTick timer
 *            generates an interrupt. The callback function will be executed each time
 *            the timer generates an interrupt.
 */
Error_enumStatus_t STK_SetCallBack(STK_CBF_t Copy_CallBack);



#endif /* STK_H_ */