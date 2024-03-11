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
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define CLOCK_HSI BIT0_MASK
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
typedef void (*Runnablecb_t)(void);
/*Any info or new feature developer needs to add it to be configured by user should be configured here*/
typedef struct
{
    char* 			Name ;
	uint32_t		PeriodicityMs;
	uint32_t		priority;
	Runnablecb_t	cb;
} Runnable_t;

/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
/*
 * @brief    : Function to Creat Task
 * @param[in]: Copy_Clock The clock source to be set on. It can be CLOCK_HSI, CLOCK_HSE, or CLOCK_PLL.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of setting the clock on.
 * @details  : This function turns on the specified clock source.
			   It enables the clock according to the provided clock source.
 */
Error_enumStatus_t Sched_RegistersRunnable(Runnable_t* Runnable);
/*Scheduler needs timer*/
void Sched_Init(void);
/*Task should be created between Init and start*/
void Sched_Start(void);



#endif /* Scheduler_H_ */
