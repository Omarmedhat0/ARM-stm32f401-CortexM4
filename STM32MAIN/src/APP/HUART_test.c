/*
 ============================================================================
 Name        : HUART_test.c
 Author      : Omar Medhat Mohamed
 Description : Source File for test
 Date        : 12/4/2024
 ============================================================================
 */
#include "CTRMain.h"
#ifdef HUART_TEST


#include "HAL/CLK_Control.h"
#include "HAL/HUART.h"
#include "HAL/LED.h"
#include "Service/Scheduler.h"
#define UART1_PINS_NUM   2
#define TX_ID   0
#define RX_ID   1

int main (void)
{
  Set_Clock_ON(USART1);
  Set_Clock_ON(GPIOA);
  Set_Clock_ON(GPIOB);
  LED_Init();
  HUART_Init();
  Sched_Init();
 Sched_Start();
}

#endif