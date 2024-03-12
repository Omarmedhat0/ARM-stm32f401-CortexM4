#include "HAL\LED.h"
void Runnable_Toggle_Led2(void)
{
    /* Static variables to keep track of counter and LED status */
  static uint32_t COUNTER = 0 ;
  static uint32_t status = LED_ON ;
  /* Increment the counter */
  COUNTER++;
  /* Check if the counter reaches 1000 milliseconds */
  if ((COUNTER % 600) ==0)
  {
  /* Toggle the LED status */
	status ^= (LED_ON | LED_OFF);
  }
    /* Set the LED status */
  LED_Set_Status(Led2 , status);
}