/*
 ============================================================================
 Name        : NVIC.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the NVIC Driver
 Date        : 3/3/2024
 ============================================================================
 */

/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "MCAL/NVIC.h"
/*******************************************************************************
 *                             Definitions                                      *
 *******************************************************************************/
#define NVIC_Base_ADDRESS 0xE000E100
#define BITS_PER_GROUP 32
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
typedef struct
{

    /* Interrupt set-enable register  */
    uint32_t NVIC_ISER[8];
    /* Reserved Bits */
    uint32_t RESERVED1[24];
    /*Interrupt clear-enable register   */
    uint32_t NVIC_ICER[8];
    /* Reserved Bits */
    uint32_t RESERVED2[24];
    /* Interrupt set-pending register */
    uint32_t NVIC_ISPR[8];
    /* Reserved Bits */
    uint32_t RESERVED3[24];
    /* Interrupt clear-pending register  */
    uint32_t NVIC_ICPR[8];
    /* Reserved Bits */
    uint32_t RESERVED4[24];
    /* Interrupt active bit register  */
    uint32_t NVIC_IABR[8];
    /* Reserved Bits */
    uint32_t RESERVED5[56];
    /* Interrupt priority register  */
    uint32_t NVIC_IPR[60];
    /* Reserved Bits */
    uint32_t RESERVED6[580];
    /* Software trigger interrupt register */
    uint32_t NVIC_STIR;
} NVIC_PERI_t;

/*******************************************************************************
 *                              Variables		                                *
 *******************************************************************************/
volatile NVIC_PERI_t *const NVIC = (volatile NVIC_PERI_t *)NVIC_Base_ADDRESS;
/*******************************************************************************
 *                         Static Function Protoypes		                    *
 *******************************************************************************/
/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*
 * @brief    : Enable NVIC IRQ
 * @param[in]: IRQn: Interrupt number
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Enables the specified NVIC interrupt.
 */
Error_enumStatus_t Enable_NVIC_IRQ(IRQn_t IRQn)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    uint8_t Loc_u8Index = IRQn / BITS_PER_GROUP;
    if (IRQn >= _INT_Num)
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    else
    {
        NVIC->NVIC_ISER[Loc_u8Index] = (1 << (IRQn % BITS_PER_GROUP));
    }
    return Loc_enumReturnStatus;
}

/*
 * @brief    : Disable NVIC IRQ
 * @param[in]: IRQn: Interrupt number
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Disables the specified NVIC interrupt.
 */
Error_enumStatus_t Disable_NVIC_IRQ(IRQn_t IRQn)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    uint8_t Loc_u8Index = IRQn / BITS_PER_GROUP;
    if (IRQn >= _INT_Num)
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    else
    {
        NVIC->NVIC_ICER[Loc_u8Index] = (1 << (IRQn % BITS_PER_GROUP));
    }
    return Loc_enumReturnStatus;
}

/*
 * @brief    : Set NVIC Pending IRQ
 * @param[in]: IRQn: Interrupt number
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Sets the specified NVIC interrupt as pending.
 */
Error_enumStatus_t Set_NVIC_Pending_IRQ(IRQn_t IRQn)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    uint8_t Loc_u8Index = IRQn / BITS_PER_GROUP;
    if (IRQn >= _INT_Num)
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    else
    {
        NVIC->NVIC_ISPR[Loc_u8Index] = (1 << (IRQn % BITS_PER_GROUP));
    }
    return Loc_enumReturnStatus;
}

/*
 * @brief    : Clear NVIC Pending IRQ
 * @param[in]: IRQn: Interrupt number
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Clears the pending status of the specified NVIC interrupt.
 */
Error_enumStatus_t Clear_NVIC_Pending_IRQ(IRQn_t IRQn)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    uint8_t Loc_u8Index = IRQn / BITS_PER_GROUP;
    if (IRQn >= _INT_Num)
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    else
    {
        NVIC->NVIC_ICPR[Loc_u8Index] = (1 << (IRQn % BITS_PER_GROUP));
    }
    return Loc_enumReturnStatus;
}

/*
 * @brief    : Get NVIC Pending IRQ status
 * @param[in]: IRQn: Interrupt number
 * @param[in]: Ptr_u8Status: Pointer to store the status
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Retrieves the pending status of the specified NVIC interrupt.
 */
Error_enumStatus_t Get_NVIC_Pending_IRQ(IRQn_t IRQn, uint8_t *Ptr_u8Status)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    uint8_t Loc_u8Index = IRQn / BITS_PER_GROUP;

    if (IRQn >= _INT_Num)
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    else if (Ptr_u8Status == NULL)
    {
        Loc_enumReturnStatus = Status_enumNULLPointer;
    }
    else
    {
       *Ptr_u8Status = (( NVIC->NVIC_ISPR[Loc_u8Index]) >> (IRQn % BITS_PER_GROUP)) & 0x01 ;
    }
    return Loc_enumReturnStatus;
}

/*
 * @brief    : Get NVIC Active IRQ status
 * @param[in]: IRQn: Interrupt number
 * @param[in]: Ptr_u8Status: Pointer to store the status
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : Retrieves the active status of the specified NVIC interrupt.
 */
Error_enumStatus_t Get_NVIC_Active_IRQ (IRQn_t IRQn , uint8_t *Ptr_u8Status)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    uint8_t Loc_u8Index = IRQn / BITS_PER_GROUP;

    if (IRQn >= _INT_Num)
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    else if (Ptr_u8Status == NULL)
    {
        Loc_enumReturnStatus = Status_enumNULLPointer;
    }
    else
    {
       *Ptr_u8Status = (( NVIC->NVIC_IABR[Loc_u8Index]) >> (IRQn % BITS_PER_GROUP)) & 0x01 ;
    }
    return Loc_enumReturnStatus;
}

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

/*
 * @brief    : Generated a Software  Interrupt
 * @param[in]: IRQn: Interrupt number
 * @return   : Error_enumStatus_t: Status of the operation
 * @details  : The value to be written is
			   the Interrupt ID of the required SGI, in the range 0-239. 
			   For example, a value of 0x03 specifies interrupt IRQ3.
 */
Error_enumStatus_t SET_Software_Interrupt(IRQn_t IRQn)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    if (IRQn >= _INT_Num)
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    else
    {
        NVIC->NVIC_STIR = IRQn ; 
    }
    return Loc_enumReturnStatus;
}
