
/*
 ============================================================================
 Name        : RunnableList_Cfg.h
 Author      : Omar Medhat Mohamed
 Description : Header Config File for the Schedular
 Date        : 11/3/2024
 ============================================================================
 */

#ifndef RUNNABLE_CFG_H_
#define RUNNABLE_CFG_H_
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef enum
{
    app1 ,
    app2 ,
    _RunNum
}Run_t;

extern void Runnable_Toggle_Led1(void) ;
extern void Runnable_Toggle_Led2(void) ;


#endif