/*
 ============================================================================
 Name        : Scheduler.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the Scheduler Driver
 Date        : 11/3/2024
 ============================================================================
 */

/*******************************************************************************
 *                                Includes	                                   *
 *******************************************************************************/
#include "Service/Scheduler.h"
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
/*Any info or new feature developer needs to add to the task during the run time should be configured here*/
typedef struct
{
    const Runnable_t *runnable;
    /*This indicate the remaining time to execute the the current task it should update automatically
     *When the value of it reaches 0 this mean that this the time to execute the task
     *After that ou should reset it by PeriodicityMs value*/
    uint32_t RemainingTimeMs;

} RunnableInfo_t;
/*******************************************************************************
 *                              Variables		                               *
 *******************************************************************************/
extern const Runnable_t RunnableList[_RunNum];
static volatile uint32_t PendingTicks;
RunnableInfo_t Runinfo[_RunNum];
static uint64_t TickCount = 0;
/*******************************************************************************
 *                         Static Function Prototypes		                   *
 *******************************************************************************/
static void Sched(void);
static void Tickcb(void);
/*******************************************************************************
 *                             Implementation   				               *
 *******************************************************************************/
/**
 * @brief    : Initializes the scheduler.
 * @param[in]: None.
 * @return   : Error status indicating success or failure.
 * @details  : Initializes the scheduler by configuring the system timer and setting the tick time.
 */
Error_enumStatus_t Sched_Init(void)
{
    /* Local variable to store the error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    uint8_t Loc_idx ;
    /* Configure  the system timer for scheduler operation */
    STK_SetConfig(STK_PROCESSOR_CLOCK_ENB_INT);
    /* Set the callback function for system timer interrupts */
    STK_SetCallBack(Tickcb);
    /* Set the tick time for the scheduler */
    STK_SetTimeMs(TICK_TIME_MS);
    for (Loc_idx =0 ; Loc_idx < _RunNum; Loc_idx++)
    {
        if (Runinfo[Loc_idx].runnable == NULL)
        {
            /*Pass pointer which user pass to me in the current struct of RunnableInfo_t */
            Runinfo[Loc_idx].runnable = &RunnableList[Loc_idx];
            /*Initiate the remaining time with delayms */
            Runinfo[Loc_idx].RemainingTimeMs = Runinfo[Loc_idx].runnable->DelayTime;
        }
        else
        {
            Loc_enumReturnStatus = Status_enumNotOk;
        }
    }

    /* Return the error status */
    return Loc_enumReturnStatus;
}
/**
 * @brief    : Starts the scheduler.
 * @param[in]: None.
 * @return   : Error_enumStatus_t - Error status indicating success or failure of starting the scheduler.
 * @details  : Starts the scheduler by enabling the system timer interrupts and entering an infinite loop
 *             where it checks for pending ticks and executes the scheduler function accordingly
 *             Task should be created between Init and start.
 */
Error_enumStatus_t Sched_Start(void)
{
    /* Local variable to store the error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    /* Start the system timer */
    Loc_enumReturnStatus = STK_Start();
    /* Enter infinite loop for scheduler operation */
    while (1)
    {
        /* Check if there are pending ticks */
        if (PendingTicks)
        {
            /* Decrement pending ticks counter */
            PendingTicks--;
            /* Execute the scheduler function */
            Sched();
        }
    }
    /* Return the error status */
    return Loc_enumReturnStatus;
}
/**
 * @brief    : Executes the scheduler.
 * @param[in]: None.
 * @return   : None.
 * @details  : Executes the scheduler by iterating through the list of runnables and calling their
 *             respective callback functions if the time condition is met.
 */
static void Sched(void)
{
    /* Declare variable for loop index */
    uint32_t idx;
    /* Loop through all runnables */
    for (idx = 0; idx < _RunNum; idx++)
    {
        /* Check if the callback function is not NULL and if the time condition is met */
        if ((Runinfo[idx].runnable->cb) && (Runinfo[idx].RemainingTimeMs== 0))
        {
            /* Call the callback function */
            RunnableList[idx].cb();
            Runinfo[idx].RemainingTimeMs = Runinfo[idx].runnable->PeriodicityMs ;
        }
        Runinfo[idx].RemainingTimeMs -= TICK_TIME_MS ;
    }
}
/**
 * @brief    : Callback function for system timer interrupts.
 * @param[in]: None.
 * @return   : None.
 * @details  : Increments the pending ticks counter upon system timer interrupt.
 */
static void Tickcb(void)
{
    /* Increment pending ticks counter */
    PendingTicks++;
    TickCount++;
}

uint64_t Sched_getTickCount(void)
{
	return TickCount;
}