/*
 ============================================================================
 Name        : main.c
 Author      : Omar Medhat Mohamed
 Description : Source File for test
 Date        : 2/4/2024
 ============================================================================
 */
#include "CTRMain.h"
#ifdef UART_TEST


#include "HAL/CLK_Control.h"
#include "MCAL/NVIC.h"
#include "MCAL/USART.h"
#include "MCAL/GPIO.h"
#include "HAL/LED.h"
#define UART1_PINS_NUM   2
#define TX_ID   0
#define RX_ID   1
void SET_LED(void)
{

  static uint32_t status = LED_OFF ;

	status ^= (LED_ON | LED_OFF);
  /* Set the LED status */
  LED_Set_Status(Green_Light , status);

}
int main (void)
{
  uint8_t x = 'c';
  uint8_t y[4] ="Omar" ;
  volatile uint8_t z = 0;
  GPIO_Config_t UART1_PINS[UART1_PINS_NUM] = {
    [TX_ID]={.Mood=GPIO_AF_PP , .Pin=GPIO_PIN9 , .Port=GPIO_PORTA , .Speed=GPIO_HIGH_SPEED},
    [RX_ID]={.Mood=GPIO_AF_PP , .Pin=GPIO_PIN10 , .Port=GPIO_PORTA , .Speed=GPIO_HIGH_SPEED}
  };
 USART_UserReq_t USART1_Req1 = {.USART_ID=USART1_ID ,.Ptr_buffer=&x,.Buff_Len= 1,.Buff_cb= NULL};
 USART_UserReq_t USART1_Req2 = {.USART_ID=USART1_ID ,.Ptr_buffer=y,.Buff_Len= 4 , .Buff_cb = SET_LED};
 USART_UserReq_t USART1_Req3 = {.USART_ID=USART1_ID ,.Ptr_buffer=&z,.Buff_Len= 1 , .Buff_cb = NULL};

  Set_Clock_ON(USART1);
  Set_Clock_ON(GPIOA);
  Set_Clock_ON(GPIOB);
  Enable_NVIC_IRQ(USART1_IRQ);
  LED_Init();
  for (uint8_t idx =0 ; idx <UART1_PINS_NUM ; idx ++)
  {
    GPIO_InitPin(&UART1_PINS[idx]);
  }
 GPIO_CFG_AlternativeFunction(UART1_PINS[TX_ID].Port , UART1_PINS[TX_ID].Pin ,GPIO_AF_7);
 GPIO_CFG_AlternativeFunction(UART1_PINS[RX_ID].Port , UART1_PINS[RX_ID].Pin ,GPIO_AF_7);
  USART_Init();
 USART_SendByte(&USART1_Req1);
 USART_TxBufferAsyncZeroCopy(&USART1_Req2);
 
  while(1)
  {
    USART_GetByte(&USART1_Req3);
    if (z=='1')
    {
      z=0;
      SET_LED();
    }
   }
    USART_RxBufferAsyncZeroCopy(&USART1_Req2);

}


#endif