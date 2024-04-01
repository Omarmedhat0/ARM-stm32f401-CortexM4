/*
 ============================================================================
 Name        : USART_CGF.c
 Author      : Omar Medhat Mohamed
 Description : Source Configuration file for the USART driver
 Date        : 30/3/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "MCAL/GPIO.h"
#include "CFG/USART_Cfg.h"
#include "MCAL/USART.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*Global array to set USARTs configuration
 I make an extra extern here beacuse of linker issue when declare and constant global array 
 It implicitly make it static fri this file so the other files can't see it */
const  USART_Config_t USARTS[_USART_Num] =
{
 [UASART_1]={
    .USART_ID=USART1_ID,
    .BaudRate=9600,
    .WordLength=USART_WL_8BIT_DATA,
    .ParityEn=USART_PARITY_DISABLE,
    .ParityType=0,
    .StopBits=USART_STOP_BIT_1,
    .OverSamplingMode=USART_OVS_16}
};
