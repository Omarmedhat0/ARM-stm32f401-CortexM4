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
#define MAX_SUPPORTED_TASKS 100
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
/*Any info or new feature developer needs to add to the task during the run time should be configured here*/
typedef struct
{
    Runnable_t *runnable;
    /*This indicate the remaining time to execute the the current task it should update automatically
     *When the value of it reaches 0 this mean that this the time to execute the task
     *After that ou should reset it by PeriodicityMs value*/
    uint32_t RemainingTimeMs;

} RunnableInfo_t;

/*******************************************************************************
 *                              Variables		                                *
 *******************************************************************************/
static RunnableInfo_t Runinfo[MAX_SUPPORTED_TASKS];
/*******************************************************************************
 *                         Static Function Prototypes		                    *
 *******************************************************************************/
static void Sched(void) ;
/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*
 * @brief    :
 * @param[in]:
 * @return   :
 * @details  :      
 */

Error_enumStatus_t Sched_RegistersRunnable(Runnable_t *Ptr_Runnable)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    /*Check if Runnable pointer is not equal Null
     *Check if the current runnable in the array of tasks is empty and there wasn't any task that take it place in this place
     */
    if (Ptr_Runnable && (Runinfo[Ptr_Runnable->priority].runnable == NULL))
    {
        /*Pass pointer which user pass to me in the current struct of RunnableInfo_t */
        Runinfo[Ptr_Runnable->priority].runnable = Ptr_Runnable;
        /*Initiate the remaining time with delayms */
        Runinfo[Ptr_Runnable->priority].RemainingTimeMs = Ptr_Runnable->delayms;
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
    STK_SetCallBack(Sched);
}
/*Task should be created between Init and start*/
void Sched_Start(void)
{
    STK_Start();
    while (1);
}

static void Sched(void)
{
    uint32_t idx;
    for (idx = 0; idx < MAX_SUPPORTED_TASKS; idx++)
    {
        if (Runinfo[idx].RemainingTimeMs == 0)
        {
            Runinfo[idx].runnable->cb;
            Runinfo[idx].RemainingTimeMs = Runinfo[idx].runnable->PeriodicityMs;
        }
        Runinfo[idx].RemainingTimeMs--;
    }
}