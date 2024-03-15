/*
 ============================================================================
 Name        : main.c
 Author      : Omar Medhat Mohamed
 Description : Source File for test
 Date        : 8/3/2024
 ============================================================================
 */
#include "CTRMain.h"
#ifdef TRAFFIC_LIGHT_TEST

#include "Service/Scheduler.h"
#include "APP/TrafficLight.h"

int main (void)
{
  Traffic_Light_Init();
  Sched_Init();
  Sched_Start();
}

#endif



