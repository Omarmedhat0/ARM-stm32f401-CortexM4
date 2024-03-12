/*
 ============================================================================
 Name        : RunnableList_CFG.c
 Author      : Omar Medhat Mohamed
 Description : Source Configuration file for the Schedular driver
 Date        : 11/3/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "CFG/RunnableList_Cfg.h"
#include "Service\Scheduler.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*Global array to set RunnableLists configuration */
const  Runnable_t RunnableList[_RunNum] = {
   /*Ex : Set RunnableList1 Configuration*/
    [app1] = {.Name = "ToggleLed1", .PeriodicityMs = 10,  .cb = Runnable_Toggle_Led1},
    [app2] = {.Name = "ToggleLed2", .PeriodicityMs = 20,  .cb = Runnable_Toggle_Led2},
};
