/*
 ============================================================================
 Name        : STK.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the STK Driver
 Date        : 8/3/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "MCAL/STK.h"
/*******************************************************************************
 *                             Definitions                                      *
 *******************************************************************************/
#define STK_BASE_ADDRESS        0xE000E010
#define STK_MODE_CLR_MASK       0xFFFFFFF9
#define STK_START_STOP_MASK     0x00000001
#define RELOAD_LOW_BOUNDARY     0x00000001
#define RELOAD_HIGH_BOUNDARY    0x00FFFFFF
#define CLK_SRC_MASK            0x00000004
#define CONVERT_SEC_TO_MSEC     1000
#define N_COUNT                 1
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
typedef struct
{
    uint32_t STK_CTRL;
    uint32_t STK_LOAD;
    uint32_t STK_VAL;
    uint32_t STK_CALIB;
} STK_PERI_t;

/*******************************************************************************
 *                              Variables		                                *
 *******************************************************************************/
/* Pointer to the SysTick peripheral structure */
volatile STK_PERI_t *const STK = (volatile STK_PERI_t *)STK_BASE_ADDRESS;
/* Callback function pointer for SysTick interrupt */
static STK_CBF_t APP_CBF = NULL;
/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/**
 * @brief   : Sets the configuration of the SysTick timer.
 * @param   : Copy_Mode - The mode to configure the SysTick timer.
 * @return  : Error status indicating success or failure.
 * @details : This function configures the SysTick timer according to the provided mode.
 */
Error_enumStatus_t STK_SetConfig(uint32_t Copy_Mode)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    uint32_t Loc_u32Temp = STK->STK_CTRL;
    /* Check if the provided mode is valid */
    if (Copy_Mode != STK_AHB_8_DIS_INT &&
        Copy_Mode != STK_PROCESSOR_CLOCK_DIS_INT &&
        Copy_Mode != STK_AHB_8_ENB_INT &&
        Copy_Mode != STK_PROCESSOR_CLOCK_ENB_INT)
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    else
    {
        /* Clear the previous mode configuration and set the new mode  */
        Loc_u32Temp &= STK_MODE_CLR_MASK;
        Loc_u32Temp |= Copy_Mode;
        STK->STK_CTRL = Loc_u32Temp;
    }

    /* Return the status of the function */
    return Loc_enumReturnStatus;
}
/**
 * @brief   : Starts the SysTick timer.
 * @param   : None
 * @return  : Error status indicating success or failure.
 * @details : This function starts the SysTick timer to generate interrupts according
 *            to the configured time interval.
 */
Error_enumStatus_t STK_Start(void)
{
    /* Local variable to store the error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    /* Read the current value of STK_CTRL register */
    uint32_t Loc_u32Temp = STK->STK_CTRL;
    /* Set the START bit in the STK_CTRL register */
    Loc_u32Temp |= STK_START_STOP_MASK;
    /* Write back the modified value to STK_CTRL register */
    STK->STK_CTRL = Loc_u32Temp;
    /* Return the error status */
    return Loc_enumReturnStatus;
}
/**
 * @brief   : Stops the SysTick timer.
 * @param   : None
 * @return  : Error status indicating success or failure.
 * @details : This function stops the SysTick timer from generating interrupts.
 */
Error_enumStatus_t STK_Stop(void)
{
    /* Local variable to store the error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    /* Read the current value of STK_CTRL register */
    uint32_t Loc_u32Temp = STK->STK_CTRL;
    /* Clear the START bit in the STK_CTRL register */
    Loc_u32Temp &= ~(STK_START_STOP_MASK);
    /* Write back the modified value to STK_CTRL register */
    STK->STK_CTRL = Loc_u32Temp;
    /* Return the error status */
    return Loc_enumReturnStatus;
}
/**
 * @brief   : Sets the time interval for the SysTick timer.
 * @param   : Copy_TimeMs - The time interval in milliseconds.
 * @return  : Error status indicating success or failure.
 * @details : This function sets the time interval for the SysTick timer, which determines
 *            the period between interrupts generated by the timer.
 */
Error_enumStatus_t STK_SetTimeMs(uint32_t Copy_TimeMs)
{
    /* Local variable to store the error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    /* Calculate the microcontroller clock frequency */
    uint32_t Loc_u32MicroClock =  ((STK->STK_CTRL) & (CLK_SRC_MASK)) ? CLK_FREQANCY_IN_MHZ : CLK_FREQANCY_IN_MHZ / 8;
    /* Calculate the reload value for the given time interval */
    uint32_t Loc_u32Temp =  ((Loc_u32MicroClock / CONVERT_SEC_TO_MSEC)* Copy_TimeMs)  - N_COUNT;
    /* Check if the provided time interval is within the valid range */
    if (Loc_u32Temp < RELOAD_LOW_BOUNDARY || Loc_u32Temp > RELOAD_HIGH_BOUNDARY)
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    else
    {
        /* Set the reload value and clear the current value */
        STK->STK_LOAD = Loc_u32Temp;
        STK->STK_VAL = 0;
    }
    /* Return the error status */
    return Loc_enumReturnStatus;
}
/**
 * @brief   : Sets the callback function for the SysTick timer interrupt.
 * @param   : Copy_CallBack - Pointer to the callback function.
 * @return  : Error status indicating success or failure.
 * @details : This function sets the callback function to be called when the SysTick timer
 *            generates an interrupt. The callback function will be executed each time
 *            the timer generates an interrupt.
 */
Error_enumStatus_t STK_SetCallBack(STK_CBF_t Copy_CallBack)
{
    /* Local variable to store the error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    /* Check if the provided callback function is not NULL */
    if (Copy_CallBack != NULL)
    {
        /* Set the callback function */
        APP_CBF = Copy_CallBack;
    }
    else
    {
        /* If the provided callback function is NULL, set error status accordingly */
        Loc_enumReturnStatus = Status_enumNULLPointer;
    }
    /* Return the error status */
    return Loc_enumReturnStatus;
}
/**
 * @brief   : SysTick interrupt handler.
 * @param   : None
 * @return  : None
 * @details : This function is the interrupt handler for the SysTick timer interrupt.
 *            It checks if a callback function (APP_CBF) is registered and calls it
 *            if it exists. This function is typically called every time the SysTick
 *            timer generates an interrupt.
 */
void SysTick_Handler(void)
{
    /* Check if a callback function is registered */
    if (APP_CBF)
    {
        /* Call the registered callback function */
        APP_CBF();
    }
}
