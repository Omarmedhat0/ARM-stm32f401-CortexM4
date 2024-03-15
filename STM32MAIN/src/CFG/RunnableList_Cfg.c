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
 *                             Implementation   				                *
 *******************************************************************************/
/*Global array to set RunnableLists configuration */
const  Runnable_t RunnableList[_RunNum] = {
   /*Ex : Set RunnableList1 Configuration*/
    //[SWITCH] = {.Name = "SwitchRunnable", .PeriodicityMs = 5,  .cb = Runnable_Switch},
    //[app3] = {.Name = "ToggleLedbySwitch", .PeriodicityMs = 50,  .cb = Runnable_APP3}
    // [app1] = {.Name = "ToggleLed1", .PeriodicityMs = 10,  .cb = Runnable_Toggle_Led1},
    // [app2] = {.Name = "ToggleLed2", .PeriodicityMs = 20,  .cb = Runnable_Toggle_Led2},
    [Traffic] = {.Name = "TrafficLight", .PeriodicityMs = 2000,  .cb = Runnable_Traffic},
};
