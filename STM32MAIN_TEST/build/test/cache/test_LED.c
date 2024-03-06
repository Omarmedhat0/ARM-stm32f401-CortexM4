#include "build/test/mocks/mock_GPIO.h"
#include "Inc/HAL/LED_Cfg.h"
#include "Inc/HAL/LED.h"
#include "C:/Ruby30/lib/ruby/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"








extern const LED_Config_t LEDS[_Led_Num];

void setUp(void)

{

}



void tearDown(void)

{

}



void test_LED_Init_ValidParameters(void)

{

    GPIO_InitPin_CMockIgnoreAndReturn(19, Status_enumOk);

    GPIO_Set_PinValue_CMockIgnoreAndReturn(20, Status_enumOk);

    UnityAssertEqualNumber((UNITY_INT)((Status_enumOk)), (UNITY_INT)((LED_Init())), (

   ((void *)0)

   ), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_INT);

}

void test_LED_Init_InValidParameters(void)

{

    GPIO_InitPin_CMockIgnoreAndReturn(25, Status_enumWrongInput);

    GPIO_Set_PinValue_CMockIgnoreAndReturn(26, Status_enumWrongInput);

    UnityAssertEqualNumber((UNITY_INT)((Status_enumWrongInput)), (UNITY_INT)((LED_Init())), (

   ((void *)0)

   ), (UNITY_UINT)(27), UNITY_DISPLAY_STYLE_INT);

}



void test_LED_SetState_InvalidLedName(void)

{

 uint32_t Led=_Led_Num+1;

 UnityAssertEqualNumber((UNITY_INT)((Status_enumWrongInput)), (UNITY_INT)((LED_Set_Status(Led,0x00000001))), (

((void *)0)

), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_INT);

}



void test_LED_SetState_ValidLedName(void)

{

 if(_Led_Num!=0)

 {

  uint32_t Led=_Led_Num-1;

  GPIO_Set_PinValue_CMockIgnoreAndReturn(41, Status_enumOk);

  UnityAssertEqualNumber((UNITY_INT)((Status_enumOk)), (UNITY_INT)((LED_Set_Status(Led,0x00000001))), (

 ((void *)0)

 ), (UNITY_UINT)(42), UNITY_DISPLAY_STYLE_INT);

 }

}

void test_LED_SetState_ValidLedStatus(void)

{

 if(_Led_Num!=0)

 {

  uint32_t Led=_Led_Num-1;

        uint32_t Status=0x00000001;

  GPIO_Set_PinValue_CMockIgnoreAndReturn(51, Status_enumOk);

  UnityAssertEqualNumber((UNITY_INT)((Status_enumOk)), (UNITY_INT)((LED_Set_Status(Led,Status))), (

 ((void *)0)

 ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_INT);

 }

}



void test_LED_SetState_ValidLedStatus2(void)

{

 if(_Led_Num!=0)

 {

  uint32_t Led=_Led_Num-1;

        uint32_t Status=0x00010000;

  GPIO_Set_PinValue_CMockIgnoreAndReturn(62, Status_enumOk);

  UnityAssertEqualNumber((UNITY_INT)((Status_enumOk)), (UNITY_INT)((LED_Set_Status(Led,Status))), (

 ((void *)0)

 ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_INT);

 }

}



void test_LED_SetState_InvalidLedStatus(void)

{

 if(_Led_Num!=0)

 {

        uint32_t Led=_Led_Num-1;

  uint32_t Status=8;

  GPIO_Set_PinValue_CMockIgnoreAndReturn(73, Status_enumOk);

  UnityAssertEqualNumber((UNITY_INT)((Status_enumWrongInput)), (UNITY_INT)((LED_Set_Status(Led,Status))), (

 ((void *)0)

 ), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_INT);

 }

}
