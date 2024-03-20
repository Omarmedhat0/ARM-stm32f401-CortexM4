
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
    //SWITCH,
    //app3,
    // app1 ,
    // app2 ,
    //Traffic,
    LCD,
    LCDTest,
    _RunNum
}Run_t;
/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
extern void Runnable_Toggle_Led1(void) ;
extern void Runnable_Toggle_Led2(void) ;
extern void HSwitch_Runnable(void) ;
extern void Runnable_APP3(void);
extern void  Traffic_Runnable(void);
extern void LCD_Runnable(void) ;
extern void LCDTest_Runnable(void);
#endif