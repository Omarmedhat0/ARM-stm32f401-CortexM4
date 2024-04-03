/*
 ============================================================================
 Name        : DMA.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the DMA Driver
 Date        : 2/4/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "MCAL/DMA.h"
/*******************************************************************************
 *                             Definitions                                      *
 *******************************************************************************/
#define DMA1_BA             (void *)0x40026000
#define DMA2_BA             (void *)0x40026400
#define DMA_NUMS_IN_TARGET   2
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/

typedef struct
{
    uint32_t DMA_LISR;
    uint32_t DMA_HISR;
    uint32_t DMA_LIFCR;
    uint32_t DMA_HIFCR;
    uint32_t DMA_S0NDTR;
    uint32_t DMA_S0PAR;
    uint32_t DMA_S0M0AR;
    uint32_t DMA_S0M1AR;
    uint32_t DMA_S0FCR;
    uint32_t DMA_S1CR;
    uint32_t DMA_S1NDTR;
    uint32_t DMA_S1PAR;
    uint32_t DMA_S1M0AR;
    uint32_t DMA_S1M1AR;
    uint32_t DMA_S1FCR;
    uint32_t DMA_S2CR;
    uint32_t DMA_S2NDTR;
    uint32_t DMA_S2PAR;
    uint32_t DMA_S2M0AR;
    uint32_t DMA_S2M1AR;
    uint32_t DMA_S2FCR;
    uint32_t DMA_S3CR;
    uint32_t DMA_S3NDTR;
    uint32_t DMA_S3PAR;
    uint32_t DMA_S3M0AR;
    uint32_t DMA_S3M1AR;
    uint32_t DMA_S3FCR;
    uint32_t DMA_S4CR;
    uint32_t DMA_S4NDTR;
    uint32_t DMA_S4PAR;
    uint32_t DMA_S4M0AR;
    uint32_t DMA_S4M1AR;
    uint32_t DMA_S4FCR;
    uint32_t DMA_S5CR;
    uint32_t DMA_S5NDTR;
    uint32_t DMA_S5PAR;
    uint32_t DMA_S5M0AR;
    uint32_t DMA_S5M1AR;
    uint32_t DMA_S5FCR;
    uint32_t DMA_S6CR;
    uint32_t DMA_S6NDTR;
    uint32_t DMA_S6PAR;
    uint32_t DMA_S6M0AR;
    uint32_t DMA_S6M1AR;
    uint32_t DMA_S6FCR;
    uint32_t DMA_S7CR;
    uint32_t DMA_S7NDTR;
    uint32_t DMA_S7PAR;
    uint32_t DMA_S7M0AR;
    uint32_t DMA_S7M1AR;
    uint32_t DMA_S7FCR;
} DMA_PERI_t;

/*******************************************************************************
 *                              Variables		                                *
 *******************************************************************************/

volatile void *const DMA[DMA_NUMS_IN_TARGET] = {DMA1_BA, DMA2_BA};

/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*
 * @brief    : Set Clock ON.
 * @param[in]: Copy_Clock The clock source to be set on. It can be CLOCK_HSI, CLOCK_HSE, or CLOCK_PLL.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of setting the clock on.
 * @details  : This function turns on the specified clock source.
               It enables the clock according to the provided clock source.
 */
Error_enumStatus_t DMA_Init(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    

    /* Return the status of the clock operation */
    return Loc_enumReturnStatus;
}