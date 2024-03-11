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
	uint32_t		delayms ;
} Runnable_t;

/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
/*
 * @brief    :
 * @param[in]:
 * @return   :
 * @details  :      
 */
Error_enumStatus_t Sched_RegistersRunnable(Runnable_t* Runnable);
/*Scheduler needs timer*/
void Sched_Init(void);
/*Task should be created between Init and start*/
void Sched_Start(void);



#endif /* Scheduler_H_ */
