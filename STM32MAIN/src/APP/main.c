#include "MCAL/NVIC.h"
#include "HAL/LED.h"
#include "MCAL/RCC.h"
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
  RCC_Enable_AHB1_Peripheral(GPIOA);
  LED_Init();
  SET_Software_Interrupt(EXTI0)  ;
  Enable_NVIC_IRQ(EXTI0);
  Enable_NVIC_IRQ(EXTI1);
  Set_Interrupt_Priority(EXTI1,3,1,PRIORITY_GROUP1);
  Set_Interrupt_Priority(EXTI0,7,1,PRIORITY_GROUP1);
  Set_NVIC_Pending_IRQ(EXTI0);
  while(1)
  {

  }
    return 0   ;
}




