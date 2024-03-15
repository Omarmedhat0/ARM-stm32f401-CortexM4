#include "HAL\LED.h"
#include "HAL\HSwitch.h"
#ifdef SCHED_TEST
void APP3_init(void)
{
  LED_Init();
  HSwitch_Init();
}
void Runnable_APP3(void)
{
   static uint32_t LED1_status = LED_OFF ;
   static uint32_t LED2_status = LED_OFF ;
  uint8_t SWitch1_status ;
  uint8_t SWitch2_status ;
  HSwitch_Get_Status(HSwitch1,&SWitch1_status);
  HSwitch_Get_Status(HSwitch2,&SWitch2_status);
  /* Check if the counter reaches 1000 milliseconds */
  if (SWitch1_status == HSwitch_PRESSED)
  {
  /* Toggle the LED status */
	LED1_status ^= (LED_ON | LED_OFF);
  LED_Set_Status(Led1 , LED1_status);
  }
  if (SWitch2_status == HSwitch_PRESSED)
  {
  /* Toggle the LED status */
	LED2_status ^= (LED_ON | LED_OFF);
   LED_Set_Status(Led2 , LED2_status);
  }
}
#endif