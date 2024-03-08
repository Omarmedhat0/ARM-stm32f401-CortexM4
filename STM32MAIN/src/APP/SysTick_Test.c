/*
 ============================================================================
 Name        : main.c
 Author      : Omar Medhat Mohamed
 Description : Source File for test
 Date        : 8/3/2024
 ============================================================================
 */
#include "CTRMain.h"
#ifdef SYSTICK_TEST

#include "MCAL/STK.h"
#include "HAL/LED.h"
#include "HAL/CLK_Control.h"


/*
 * @brief   : ToggleLED function for SysTick test.
 * @details : This function toggles the LED status every 1000 milliseconds.
 */
void ToggleLEd(void)
{
  /* Static variables to keep track of counter and LED status */
  static uint32_t COUNTER = 0 ;
  static uint32_t status = LED_ON ;
  /* Increment the counter */
  COUNTER++;
  /* Check if the counter reaches 1000 milliseconds */
  if ((COUNTER % 1000) ==0)
  {
  /* Toggle the LED status */
	status ^= (LED_ON | LED_OFF);
  }
    /* Set the LED status */
  LED_Set_Status(Led1 , status);
}
int main (void)
{
  Set_PORT_Clock_ON(GPIOA);
  LED_Init();
  STK_SetConfig(STK_PROCESSOR_CLOCK_ENB_INT);
  STK_SetCallBack(ToggleLEd);
  STK_SetTimeMs(10);
  STK_Start();
  while (1)
  {
    /* code */
  }
  
    return 0   ;
}

#endif



