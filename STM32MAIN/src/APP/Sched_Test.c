/*
 ============================================================================
 Name        : Sched_Test.c
 Author      : Omar Medhat Mohamed
 Description : Source File for Schedular test
 Date        : 8/3/2024
 ============================================================================
 */
#include "CTRMain.h"
#ifdef SCHED_TEST

// #include "HAL/LED.h"
#include "HAL/CLK_Control.h"
#include "Service/Scheduler.h"

extern void APP3_init(void);

int main (void)
{
  Set_PORT_Clock_ON(GPIOA);
  Set_PORT_Clock_ON(GPIOB);
  APP3_init();
  Sched_Init();
  Sched_Start();
}

#endif



