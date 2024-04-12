/*
 ============================================================================
 Name        : HUART_test _Run.c
 Author      : Omar Medhat Mohamed
 Description : Source File for test Huart
 Date        : 12/4/2024
 ============================================================================
 */
#include "CTRMain.h"
#ifdef HUART_TEST

#define SEND_Test  0 
#define REC_Test  1
#define CURRENT_TEST REC_Test
#include "HAL/CLK_Control.h"
#include "HAL/LED.h"
#include "HAL/HUART.h"
void SET_LED(void)
{

  static uint32_t status = LED_OFF ;

	status ^= (LED_ON | LED_OFF);
  /* Set the LED status */
  LED_Set_Status(Green_Light , status);

}
void HUART_test_Run(void)
{   
    #if (CURRENT_TEST == SEND_Test)
    static uint8_t y[4] ="Omar" ;
    HUSART_UserReq_t USART1_Req2 = {.USART_ID=USART1_ID ,.Ptr_buffer=y,.Buff_Len= 4 , .Buff_cb = SET_LED};
    HUART_SendBuffAsync(&USART1_Req2) ; 
    #else
    static uint8_t y[4] ;
    HUSART_UserReq_t USART1_Req2 = {.USART_ID=USART1_ID ,.Ptr_buffer=y,.Buff_Len= 4 , .Buff_cb = SET_LED};
    HUART_ReceiveBuffAsync(&USART1_Req2) ; 
    if (y[0]=='1')
    {
        SET_LED();
    }
    #endif

}
#endif