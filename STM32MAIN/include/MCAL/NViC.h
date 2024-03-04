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
#include	"LIB/Stm32F401cc.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
/*
 * @brief    : Enable NVIC IRQ
 * @param[in]: IRQn: Interrupt number
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Enables the specified NVIC interrupt.
 */
Error_enumStatus_t Enable_NVIC_IRQ(IRQn_t IRQn);

/*
 * @brief    : Disable NVIC IRQ
 * @param[in]: IRQn: Interrupt number
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Disables the specified NVIC interrupt.
 */
Error_enumStatus_t Disable_NVIC_IRQ(IRQn_t IRQn);

/*
 * @brief    : Set NVIC Pending IRQ
 * @param[in]: IRQn: Interrupt number
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Sets the specified NVIC interrupt as pending.
 */
Error_enumStatus_t Set_NVIC_Pending_IRQ(IRQn_t IRQn);

/*
 * @brief    : Clear NVIC Pending IRQ
 * @param[in]: IRQn: Interrupt number
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Clears the pending status of the specified NVIC interrupt.
 */
Error_enumStatus_t Clear_NVIC_Pending_IRQ(IRQn_t IRQn);

/*
 * @brief    : Get NVIC Pending IRQ status
 * @param[in]: IRQn: Interrupt number
 * @param[in]: Ptr_u8Status: Pointer to store the status
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Retrieves the pending status of the specified NVIC interrupt.
 */
Error_enumStatus_t Get_NVIC_Pending_IRQ(IRQn_t IRQn, uint8_t *Ptr_u8Status);

/*
 * @brief    : Get NVIC Active IRQ status
 * @param[in]: IRQn: Interrupt number
 * @param[in]: Ptr_u8Status: Pointer to store the status
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Retrieves the active status of the specified NVIC interrupt.
 */
Error_enumStatus_t Get_NVIC_Active_IRQ(IRQn_t IRQn, uint8_t *Ptr_u8Status);

/*
 * @brief    : Set Interrupt Priority
 * @param[in]: IRQn: Interrupt number
 * @param[in]: priority: Priority level to set
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Sets the priority level for the specified NVIC interrupt.
 */
Error_enumStatus_t Set_Interrupt_Priority(IRQn_t IRQn, uint32_t priority);

/*
 * @brief    : Get Interrupt Priority
 * @param[in]: IRQn: Interrupt number
 * @param[in]: Ptr_u8Status: Pointer to store the priority level
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Retrieves the priority level of the specified NVIC interrupt.
 */
Error_enumStatus_t Get_Interrupt_Priority(IRQn_t IRQn, uint8_t *Ptr_u8Status);

#endif /* NVIC_H_ */
