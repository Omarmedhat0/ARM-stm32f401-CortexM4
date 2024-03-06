#ifdef TEST

#include "unity.h"

#include "HAL\LED.h"
#include "HAL\LED_Cfg.h"
#include "mock_GPIO.h"
extern const LED_Config_t  LEDS[_Led_Num];
void setUp(void)
{
}

void tearDown(void)
{
}

void test_LED_Init_ValidParameters(void)
{
    GPIO_InitPin_IgnoreAndReturn(Status_enumOk);
    GPIO_Set_PinValue_IgnoreAndReturn(Status_enumOk);
    TEST_ASSERT_EQUAL(Status_enumOk, LED_Init());
}
void test_LED_Init_InValidParameters(void)
{
    GPIO_InitPin_IgnoreAndReturn(Status_enumWrongInput);
    GPIO_Set_PinValue_IgnoreAndReturn(Status_enumWrongInput);
    TEST_ASSERT_EQUAL(Status_enumWrongInput, LED_Init());
}

void test_LED_SetState_InvalidLedName(void)
{
	uint32_t Led=_Led_Num+1;
	TEST_ASSERT_EQUAL(Status_enumWrongInput,LED_Set_Status(Led,LED_ON));
}

void test_LED_SetState_ValidLedName(void)
{
	if(_Led_Num!=0)
	{
		uint32_t Led=_Led_Num-1;
		GPIO_Set_PinValue_IgnoreAndReturn(Status_enumOk);
		TEST_ASSERT_EQUAL(Status_enumOk,LED_Set_Status(Led,LED_ON));
	}
}
void test_LED_SetState_ValidLedStatus(void)
{
	if(_Led_Num!=0)
	{
		uint32_t Led=_Led_Num-1;
        uint32_t Status=LED_ON;
		GPIO_Set_PinValue_IgnoreAndReturn(Status_enumOk);
		TEST_ASSERT_EQUAL(Status_enumOk,LED_Set_Status(Led,Status));
	}
}

void test_LED_SetState_ValidLedStatus2(void)
{
	if(_Led_Num!=0)
	{
		uint32_t Led=_Led_Num-1;
        uint32_t Status=LED_OFF;
		GPIO_Set_PinValue_IgnoreAndReturn(Status_enumOk);
		TEST_ASSERT_EQUAL(Status_enumOk,LED_Set_Status(Led,Status));
	}
}

void test_LED_SetState_InvalidLedStatus(void)
{
	if(_Led_Num!=0)
	{
        uint32_t Led=_Led_Num-1;
		uint32_t Status=8;
		GPIO_Set_PinValue_IgnoreAndReturn(Status_enumOk);
		TEST_ASSERT_EQUAL(Status_enumWrongInput,LED_Set_Status(Led,Status));
	}
}
#endif // TEST
