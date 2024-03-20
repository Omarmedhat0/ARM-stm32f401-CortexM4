/*
 ============================================================================
 Name        : TrafficLight.c
 Author      : Omar Medhat Mohamed
 Description : Source File for Traffic Light
 Date        : 15/3/2024
 ============================================================================
 */
#include "APP/TrafficLight.h"
Traffic_Config_t Traffic_Status = Green;
void Traffic_Light_Init(void)
{
  Set_PORT_Clock_ON(GPIOA);
  LED_Init();
}
static void GreenLight(void)
{
  LED_Set_Status(Green_Light, LED_ON);
  LED_Set_Status(Yellow_Light, LED_OFF);
  LED_Set_Status(Red_Light, LED_OFF);
}
static void YellowLight(void)
{
  LED_Set_Status(Green_Light, LED_OFF);
  LED_Set_Status(Yellow_Light, LED_ON);
  LED_Set_Status(Red_Light, LED_OFF);
}
static void RedLight(void)
{
  LED_Set_Status(Green_Light, LED_OFF);
  LED_Set_Status(Yellow_Light, LED_OFF);
  LED_Set_Status(Red_Light, LED_ON);
}
void Traffic_Runnable(void)
{
  static uint32_t seconds = 0;
  static uint8_t prev = 0 ;
  seconds += PERIODICITY_SECOND;
  switch (Traffic_Status)
  {
  case Green:
    GreenLight();
    if (seconds % 6 == 0)
    {
      Traffic_Status = Yellow;
      prev = Green ;
    }
    break;
  case Yellow:
    YellowLight();
    if (seconds % 2 == 0)
    {
      Traffic_Status =(prev==Red)?Green:Red  ;
    }
    break;
  case Red:
    RedLight();
    if (seconds % 4 == 0)
    {
      Traffic_Status = Yellow;
      prev = Red ;
    }
    break;
  }
}