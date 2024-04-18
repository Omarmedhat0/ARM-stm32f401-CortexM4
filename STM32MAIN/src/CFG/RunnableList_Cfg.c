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
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
extern void Runnable_Toggle_Led1(void) ;
extern void Runnable_Toggle_Led2(void) ;
extern void HSwitch_Runnable(void) ;
extern void Runnable_APP3(void);
extern void  Traffic_Runnable(void);
extern void LCD_Runnable(void) ;
extern void HUART_test_Run(void);
extern void HUART_Runnable(void) ;
extern void Clock_TEST_TASK (void) ;
/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*Global array to set RunnableLists configuration */
const  Runnable_t RunnableList[_RunNum] = {
   /*Ex : Set RunnableList1 Configuration*/
    //[SWITCH] = {.Name = "SwitchRunnable", .PeriodicityMs = 5,  .cb = HSwitch_Runnable , .DelayTime = 0},
    //[app3] = {.Name = "ToggleLedbySwitch", .PeriodicityMs = 150,  .cb = Runnable_APP3 , .DelayTime = 0}
    // [app1] = {.Name = "ToggleLed1", .PeriodicityMs = 20,  .cb = Runnable_Toggle_Led1 , .DelayTime = 1000},
    // [app2] = {.Name = "ToggleLed2", .PeriodicityMs = 10,  .cb = Runnable_Toggle_Led2 , .DelayTime = 0},
    //[Traffic] = {.Name = "TrafficLight", .PeriodicityMs = 2000,  .cb = Traffic_Runnable , .DelayTime = 0},
     [HUARTTest]={.Name = "HUARTTest", .PeriodicityMs = 1000,  .cb =HUART_test_Run , .DelayTime = 20}
   //
};
