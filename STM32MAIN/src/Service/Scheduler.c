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
 *                             Definitions                                     *
 *******************************************************************************/
#define TICK_TIME_MS 10
/*******************************************************************************
 *                              Variables		                               *
 *******************************************************************************/
extern const  Runnable_t RunnableList[_RunNum] ;
static volatile uint32_t PendingTicks  ;
/*******************************************************************************
 *                         Static Function Prototypes		                   *
 *******************************************************************************/
static void Sched(void) ;
static void Tickcb(void) ;
/******************************************************************************* 
 *                             Implementation   				               *
 *******************************************************************************/
/*
 * @brief    :
 * @param[in]:
 * @return   :
 * @details  :      
 */


/*Scheduler needs timer*/
void Sched_Init(void)
{
    /*This the time which Schedular will operate on*/
    STK_SetConfig(STK_PROCESSOR_CLOCK_ENB_INT);
    STK_SetCallBack(Tickcb);
    STK_SetTimeMs(TICK_TIME_MS);
}
/*Task should be created between Init and start*/
void Sched_Start(void)
{
    STK_Start();
    while (1)
    {
        if (PendingTicks)
        {
            PendingTicks -- ;
            Sched();
        }
    }
}

static void Sched(void)
{
    uint32_t idx;
    static uint32_t TimeStamp = 0 ;    
    for (idx = 0; idx < _RunNum; idx++)
    {
        if ((RunnableList[idx].cb) && (TimeStamp % RunnableList[idx].PeriodicityMs == 0)) 
        {
            RunnableList[idx].cb();
        }
    }
    TimeStamp += TICK_TIME_MS ;
}

static void Tickcb(void)
{
    PendingTicks ++ ;    
}