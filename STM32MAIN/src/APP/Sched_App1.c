/*
 ============================================================================
 Name        : Sched_App1.c
 Author      : Omar Medhat Mohamed
 Description : Source File for test
 Date        : 8/3/2024
 ============================================================================
 */
#include "CTRMain.h"
#ifdef SCHED_TEST
#include "HAL\LED.h"
void Runnable_Toggle_Led1(void)
{
    /* Static variables to keep track of counter and LED status */
  static uint32_t COUNTER = 0 ;
  static uint32_t status = LED_ON ;
  /* Increment the counter */
  COUNTER++;
  /* Check if the counter reaches 1000 milliseconds */
  if ((COUNTER % 300) ==0)
  {
  /* Toggle the LED status */
	status ^= (LED_ON | LED_OFF);
  }
    /* Set the LED status */
  LED_Set_Status(Green_Light , status);
}
#endif