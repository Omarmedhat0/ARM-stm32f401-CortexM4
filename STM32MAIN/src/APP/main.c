#include "MCAL\RCC.h"
#include "HAL\LED.h"
#include "HAL\Switch.h"


int main (void)
{
	RCC_Enable_AHB1_Peripheral(GPIOA);
	RCC_Enable_AHB1_Peripheral(GPIOB);
	LED_Init ();
	Switch_Init ();
	uint8_t s1 = 0 ;
	uint8_t s2 = 0 ;
  while (1)
    {
	  Switch_Get_Status(Switch1 , &s1 );
	  Switch_Get_Status(Switch2 , &s2);
       if (s1 == Switch_PRESSED)
       {
    		LED_Set_Status(Led1 ,LED_ON );
       }
       if (s2 == Switch_PRESSED)
       {
    		LED_Set_Status(Led2 ,LED_ON );
       }
       if ((s1 == Switch_PRESSED ) && (s2 == Switch_PRESSED) )
       {
    		LED_Set_Status(Led1 ,LED_OFF );
    		LED_Set_Status(Led2 ,LED_OFF );
       }
    }
    return 0 ;
}



