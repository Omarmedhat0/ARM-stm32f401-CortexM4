/*
 ============================================================================
 Name        : Scheduler.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the Scheduler Driver
 Date        : 11/3/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "Service/Scheduler.h"
/*******************************************************************************
 *                             Definitions                                      *
 *******************************************************************************/
#define MAX_SUPPORTED_TASKS  100
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
/*Any info or new feature developer needs to add to the task during the run time should be configured here*/
typedef struct
{
    Runnable_t* runnable;
    /*This indicate the remaining time to execute the the current task it should update automatically 
     *When the value of it reaches 0 this mean that this the time to execute the task 
     *After that ou should reset it by PeriodicityMs value*/
    uint32_t RemainingTime;
    
} RunnableInfo_t;

/*******************************************************************************
 *                              Variables		                                *
 *******************************************************************************/
static RunnableInfo_t Runinfo[MAX_SUPPORTED_TASKS];
/*******************************************************************************
 *                         Static Function Prototypes		                    *
 *******************************************************************************/
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

Error_enumStatus_t Sched_RegistersRunnable(Runnable_t* Ptr_Runnable)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    /*Check if Runnable pointer is not equal Null
     *Check if the current runnable in the array of tasks is empty and that wasn't any task that take it place in 
    */
    if (Ptr_Runnable && (Runinfo[Ptr_Runnable-> priority].runnable ==NULL))
    {
        /*Pass pointer which user pass to me in the current struct of RunnableInfo_t */
        Runinfo[Ptr_Runnable->priority].runnable = Ptr_Runnable;

        Runinfo[Ptr_Runnable->priority].RemainingTime = Ptr_Runnable->priority;
    }
    else
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    /* Return the status of the clock operation */
    return Loc_enumReturnStatus;
}

/*Scheduler needs timer*/
void Sched_Init(void)
{
    /*This the time which Schedular will operate on*/
    STK_SetTimeMs();
    STK_SetCallBack();
    Sched_Start();
}
/*Task should be created between Init and start*/
void Sched_Start(void)
{
    STK_Start();
    while (1);
    {
        /* code */
    }
    
}