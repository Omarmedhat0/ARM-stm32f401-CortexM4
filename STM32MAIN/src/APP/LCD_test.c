/*
 ============================================================================
 Name        : main.c
 Author      : Omar Medhat Mohamed
 Description : Source File for test
 Date        : 8/3/2024
 ============================================================================
 */
#include "CTRMain.h"
#ifdef LCD_TEST

#include "Service/Scheduler.h"
#include "HAL/LCD.h"
#include "HAL/CLK_Control.h"
void LCDTest_Runnable(void)
{   
  static uint32_t time=0;
    if (time==3)
    {
    LCD_Write_StringAsync("Hello",5);
    }
    else if (time==4)
    {
      LCD_Clear_ScreenAsync();
    }
    else if (time==5)
    {
      LCD_Set_CursorPosAsync(LCD_DISPLAY_LINE2 , LCD_DISPLAY_COL3);
    }
    else if (time==6)
    {
      LCD_Write_StringAsync("Omar",4);
    }
    time ++ ;
}
int main (void)
{
  Set_PORT_Clock_ON(GPIOA);
  LCD_InitAsync();
  Sched_Init();
  Sched_Start();
}

#endif



