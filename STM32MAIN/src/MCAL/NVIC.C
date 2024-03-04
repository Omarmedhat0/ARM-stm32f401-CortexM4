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
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
typedef struct
{

    /* Interrupt set-enable register 0 */
    uint32_t NVIC_ISER0;
    /* Interrupt set-enable register 1 */
    uint32_t NVIC_ISER1;
    /* Interrupt set-enable register 2 */
    uint32_t NVIC_ISER2;
    /* Interrupt set-enable register 3 */
    uint32_t NVIC_ISER3;
    /* Interrupt set-enable register 4 */
    uint32_t NVIC_ISER4;
    /* Interrupt set-enable register 5 */
    uint32_t NVIC_ISER5;
    /* Interrupt set-enable register 6 */
    uint32_t NVIC_ISER6;
    /* Interrupt set-enable register 7 */
    uint32_t NVIC_ISER7;
    uint32_t RESERVED0[24];
    /* Interrupt clear-enable register 0 */
    uint32_t NVIC_ICER0;
    /* Interrupt clear-enable register 1 */
    uint32_t NVIC_ICER1;
    /* Interrupt clear-enable register 2 */
    uint32_t NVIC_ICER2;
    /* Interrupt clear-enable register 3 */
    uint32_t NVIC_ICER3;
    /* Interrupt clear-enable register 4 */
    uint32_t NVIC_ICER4;
    /* Interrupt clear-enable register 5 */
    uint32_t NVIC_ICER5;
    /* Interrupt clear-enable register 6 */
    uint32_t NVIC_ICER6;
    /* Interrupt clear-enable register 7 */
    uint32_t NVIC_ICER7;

    uint32_t RESERVED2[24];
    /* Interrupt set-pending register 0 */
    uint32_t NVIC_ISPR0;
    /* Interrupt set-pending register 1 */
    uint32_t NVIC_ISPR1;
    /* Interrupt set-pending register 2 */
    uint32_t NVIC_ISPR2;
    /* Interrupt set-pending register 3 */
    uint32_t NVIC_ISPR3;
    /* Interrupt set-pending register 4 */
    uint32_t NVIC_ISPR4;
    /* Interrupt set-pending register 5 */
    uint32_t NVIC_ISPR5;
    /* Interrupt set-pending register 6 */
    uint32_t NVIC_ISPR6;
    /* Interrupt set-pending register 7 */
    uint32_t NVIC_ISPR7;

    uint32_t RESERVED3[24];
    /* Interrupt clear-pending register 0 */
    uint32_t NVIC_ICPR0;
    /* Interrupt clear-pending register 1 */
    uint32_t NVIC_ICPR1;
    /* Interrupt clear-pending register 2 */
    uint32_t NVIC_ICPR2;
    /* Interrupt clear-pending register 3 */
    uint32_t NVIC_ICPR3;
    /* Interrupt clear-pending register 4 */
    uint32_t NVIC_ICPR4;
    /* Interrupt clear-pending register 5 */
    uint32_t NVIC_ICPR5;
    /* Interrupt clear-pending register 6 */
    uint32_t NVIC_ICPR6;
    /* Interrupt clear-pending register 7 */
    uint32_t NVIC_ICPR7;

    uint32_t RESERVED1[24];
    /* Interrupt active bit register 0 */
    uint32_t NVIC_IABR0;
    /* Interrupt active bit register 1 */
    uint32_t NVIC_IABR1;
    /* Interrupt active bit register 2 */
    uint32_t NVIC_IABR2;
    /* Interrupt active bit register 3 */
    uint32_t NVIC_IABR3;
    /* Interrupt active bit register 4 */
    uint32_t NVIC_IABR4;
    /* Interrupt active bit register 5 */
    uint32_t NVIC_IABR5;
    /* Interrupt active bit register 6 */
    uint32_t NVIC_IABR6;
    /* Interrupt active bit register 7 */
    uint32_t NVIC_IABR7;

    uint32_t RESERVED4[56];
    /* Interrupt priority register 0 */
    uint32_t NVIC_IPR0;
    /* Interrupt priority register 1 */
    uint32_t NVIC_IPR1;
    /* Interrupt priority register 2 */
    uint32_t NVIC_IPR2;
    /* Interrupt priority register 3 */
    uint32_t NVIC_IPR3;
    /* Interrupt priority register 4 */
    uint32_t NVIC_IPR4;
    /* Interrupt priority register 5 */
    uint32_t NVIC_IPR5;
    /* Interrupt priority register 6 */
    uint32_t NVIC_IPR6;
    /* Interrupt priority register 7 */
    uint32_t NVIC_IPR7;
    /* Interrupt priority register 8 */
    uint32_t NVIC_IPR8;
    /* Interrupt priority register 9 */
    uint32_t NVIC_IPR9;
    /* Interrupt priority register 10 */
    uint32_t NVIC_IPR10;
    /* Interrupt priority register 11 */
    uint32_t NVIC_IPR11;
    /* Interrupt priority register 12 */
    uint32_t NVIC_IPR12;
    /* Interrupt priority register 13 */
    uint32_t NVIC_IPR13;
    /* Interrupt priority register 14 */
    uint32_t NVIC_IPR14;
    /* Interrupt priority register 15 */
    uint32_t NVIC_IPR15;
    /* Interrupt priority register 16 */
    uint32_t NVIC_IPR16;
    /* Interrupt priority register 17 */
    uint32_t NVIC_IPR17;
    /* Interrupt priority register 18 */
    uint32_t NVIC_IPR18;
    /* Interrupt priority register 19 */
    uint32_t NVIC_IPR19;
    /* Interrupt priority register 20 */
    uint32_t NVIC_IPR20;
    /* Interrupt priority register 21 */
    uint32_t NVIC_IPR21;
    /* Interrupt priority register 22 */
    uint32_t NVIC_IPR22;
    /* Interrupt priority register 23 */
    uint32_t NVIC_IPR23;
    /* Interrupt priority register 24 */
    uint32_t NVIC_IPR24;
    /* Interrupt priority register 25 */
    uint32_t NVIC_IPR25;
    /* Interrupt priority register 26 */
    uint32_t NVIC_IPR26;
    /* Interrupt priority register 27 */
    uint32_t NVIC_IPR27;
    /* Interrupt priority register 28 */
    uint32_t NVIC_IPR28;
    /* Interrupt priority register 29 */
    uint32_t NVIC_IPR29;
    /* Interrupt priority register 30 */
    uint32_t NVIC_IPR30;
    /* Interrupt priority register 31 */
    uint32_t NVIC_IPR31;
    /* Interrupt priority register 32 */
    uint32_t NVIC_IPR32;
    /* Interrupt priority register 33 */
    uint32_t NVIC_IPR33;
    /* Interrupt priority register 34 */
    uint32_t NVIC_IPR34;
    /* Interrupt priority register 35 */
    uint32_t NVIC_IPR35;
    /* Interrupt priority register 36 */
    uint32_t NVIC_IPR36;
    /* Interrupt priority register 37 */
    uint32_t NVIC_IPR37;
    /* Interrupt priority register 38 */
    uint32_t NVIC_IPR38;
    /* Interrupt priority register 39 */
    uint32_t NVIC_IPR39;
    /* Interrupt priority register 40 */
    uint32_t NVIC_IPR40;
    /* Interrupt priority register 41 */
    uint32_t NVIC_IPR41;
    /* Interrupt priority register 42 */
    uint32_t NVIC_IPR42;
    /* Interrupt priority register 43 */
    uint32_t NVIC_IPR43;
    /* Interrupt priority register 44 */
    uint32_t NVIC_IPR44;
    /* Interrupt priority register 45 */
    uint32_t NVIC_IPR45;
    /* Interrupt priority register 46 */
    uint32_t NVIC_IPR46;
    /* Interrupt priority register 47 */
    uint32_t NVIC_IPR47;
    /* Interrupt priority register 48 */
    uint32_t NVIC_IPR48;
    /* Interrupt priority register 49 */
    uint32_t NVIC_IPR49;
    /* Interrupt priority register 50 */
    uint32_t NVIC_IPR50;
    /* Interrupt priority register 51 */
    uint32_t NVIC_IPR51;
    /* Interrupt priority register 52 */
    uint32_t NVIC_IPR52;
    /* Interrupt priority register 53 */
    uint32_t NVIC_IPR53;
    /* Interrupt priority register 54 */
    uint32_t NVIC_IPR54;
    /* Interrupt priority register 55 */
    uint32_t NVIC_IPR55;
    /* Interrupt priority register 56 */
    uint32_t NVIC_IPR56;
    /* Interrupt priority register 57 */
    uint32_t NVIC_IPR57;
    /* Interrupt priority register 58 */
    uint32_t NVIC_IPR58;
    /* Interrupt priority register 59 */
    uint32_t NVIC_IPR59;

    uint32_t RESERVED5[580];
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
 * @brief    : 
 * @param[in]: 
 * @details  : 
 */
Error_enumStatus_t Set_Interrupt_Priority ()
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;

    return Loc_enumReturnStatus;
}

Error_enumStatus_t Set_Interrupt_Enable ();

Error_enumStatus_t Set_Interrupt_Disable ();

Error_enumStatus_t Set_Pending ();

Error_enumStatus_t Clear_Pending ();

Error_enumStatus_t Get_Interrupt_Status();

