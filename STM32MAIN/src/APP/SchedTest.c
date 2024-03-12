/*
 ============================================================================
 Name        : main.c
 Author      : Omar Medhat Mohamed
 Description : Source File for test
 Date        : 8/3/2024
 ============================================================================
 */
#include "CTRMain.h"
#ifdef SCHED_TEST

#include "MCAL/STK.h"
#include "HAL/LED.h"
#include "HAL/CLK_Control.h"
#include "Service/Scheduler.h"



int main (void)
{
  Set_PORT_Clock_ON(GPIOA);
  LED_Init();
  Sched_Init();
  Sched_Start();
}

#endif



