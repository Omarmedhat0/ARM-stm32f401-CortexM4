/*
 ============================================================================
 Name        : Scheduler.h
 Author      : Omar Medhat Mohamed
 Description : Header File for the Scheduler Driver
 Date        : 11/3/2024
 ============================================================================
 */
#ifndef SCHEDULER_H_
#define SCHEDULER_H_
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "LIB/std_types.h"
#include "LIB/Mask32.h"
#include "LIB/Error.h"
#include "MCAL/STK.h"
#include "CFG/RunnableList_Cfg.h"
/*******************************************************************************
 *                             Definitions                                     *
 *******************************************************************************/
#define TICK_TIME_MS 2
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
/*New pointer to function type for set the runnable or call by it */
typedef void (*Runnablecb_t)(void);
/*Structure to hold information about each runnable task.*/
typedef struct
{
    /* Name or ID of the runnable task */
    char* Name;
    /* Periodicity of the task in milliseconds */
    uint32_t PeriodicityMs;
    /* Callback function for the task */
    Runnablecb_t cb;
} Runnable_t;
/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/

/*
 * @brief    : Initializes the scheduler.
 * @param[in]: None.
 * @return   : Error status indicating success or failure.
 * @details  : Initializes the scheduler by configuring the system timer and setting the tick time.
 */
Error_enumStatus_t Sched_Init(void);
/*
 * @brief    : Starts the scheduler.
 * @param[in]: None.
 * @return   : Error_enumStatus_t - Error status indicating success or failure of starting the scheduler.
 * @details  : Starts the scheduler by enabling the system timer interrupts and entering an infinite loop
 *             where it checks for pending ticks and executes the scheduler function accordingly
 *             Task should be created between Init and start.
 */
Error_enumStatus_t Sched_Start(void);



#endif /* Scheduler_H_ */
