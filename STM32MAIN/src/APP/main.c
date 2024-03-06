/*
 ============================================================================
 Name        : main.c
 Author      : Omar Medhat Mohamed
 Description : Source File for test
 Date        : 
 ============================================================================
 */
#include "MCAL/NVIC.h"
#include "HAL/LED.h"
#include "HAL/CLK_Control.h"
void delay_ms(uint32_t ms)
 {
    for (volatile uint32_t i = 0; i < ms * 16000; ++i)
    {

    }
}
void EXTI0_IRQHandler(void)
{
  LED_Set_Status(Led1 , LED_ON);
  Set_NVIC_Pending_IRQ(EXTI1);
  delay_ms(500);/*500 = 5 Sec*/
}


void EXTI1_IRQHandler(void)
{
  LED_Set_Status(Led1 , LED_OFF);
}
int main (void)
{
  Set_PORT_Clock_ON(GPIOA);
  LED_Init();
  SET_Software_Interrupt(EXTI0)  ;
  Enable_NVIC_IRQ(EXTI0);
  Enable_NVIC_IRQ(EXTI1);
  Set_Interrupt_Priority(EXTI1,3,1,PRIORITY_GROUP1);
  Set_Interrupt_Priority(EXTI0,7,1,PRIORITY_GROUP1);
  Set_NVIC_Pending_IRQ(EXTI0);
  SET_Software_Interrupt(EXTI16_PVD);
  while(1)
  {

  }
    return 0   ;
}




