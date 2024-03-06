#ifdef TEST

#include "unity.h"

#include "HAL\Switch.h"
#include "HAL\Switch_Cfg.h"
#include "mock_GPIO.h"
extern const Switch_Config_t SwitchS[_Switch_Num];

void setUp(void)
{
}

void tearDown(void)
{
}
void test_Switch_Init_ValidParameters(void)
{
    GPIO_InitPin_IgnoreAndReturn(Status_enumOk);
    TEST_ASSERT_EQUAL(Status_enumOk, Switch_Init());
}
void test_Switch_Init_InValidParameters(void)
{
    GPIO_InitPin_IgnoreAndReturn(Status_enumWrongInput);
    TEST_ASSERT_EQUAL(Status_enumWrongInput, Switch_Init());
}

void test_Switch_SetState_InvalidSwitchName(void)
{
    uint32_t Switch = _Switch_Num + 1;
    uint8_t TempVarForAdrr;
    uint8_t *Ptr = &TempVarForAdrr;
    TEST_ASSERT_EQUAL(Status_enumWrongInput, Switch_Get_Status(Switch, Ptr));
}

void test_Switch_SetState_ValidSwitchName(void)
{
    if (_Switch_Num != 0)
    {
        uint32_t Switch = _Switch_Num - 1;
        uint8_t TempVarForAdrr;
        uint8_t *Ptr = &TempVarForAdrr;
        GPIO_Get_GetPinValue_IgnoreAndReturn(Status_enumOk);
        TEST_ASSERT_EQUAL(Status_enumOk, Switch_Get_Status(Switch, Ptr));
    }
}

void test_Switch_SetState_ValidSwitchPointerStatus(void)
{
    if (_Switch_Num != 0)
    {
        uint32_t Switch = _Switch_Num - 1;
        uint8_t TempVarForAdrr;
        uint8_t *Ptr = &TempVarForAdrr;
        GPIO_Get_GetPinValue_IgnoreAndReturn(Status_enumOk);
        TEST_ASSERT_EQUAL(Status_enumOk, Switch_Get_Status(Switch, Ptr));
    }
}

void test_Switch_SetState_InValidSwitchPointerStatus_NULL(void)
{
    if (_Switch_Num != 0)
    {
        uint32_t Switch = _Switch_Num - 1;
        uint8_t *Ptr = NULL;
        GPIO_Get_GetPinValue_IgnoreAndReturn(Status_enumOk);
        TEST_ASSERT_EQUAL(Status_enumNULLPointer, Switch_Get_Status(Switch, Ptr));
    }
}

#endif // TEST
