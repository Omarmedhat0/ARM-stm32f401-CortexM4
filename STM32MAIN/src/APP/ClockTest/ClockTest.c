/*
 ============================================================================
 Name        : CLOCK_TesT.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the CLOCK Driver
 Date        : 14/4/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "APP/ClockTest/Clock_Date.h"

void Clock_TEST_TASK (void)
{
    volatile const TimeInfo_t* Time ;
    Time =  Clock_CalculateCurrentTime();
    
    Clock_SetHours(22);
     Clock_SetMonths(6);
     char buff[] =  {Time->MillisecondsIn100 , Time->second ,Time->minute , Time->hour,Time->day , Time->month , Time->year};

}