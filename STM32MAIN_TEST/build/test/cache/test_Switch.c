#include "build/test/mocks/mock_GPIO.h"
#include "Inc/HAL/Switch_Cfg.h"
#include "Inc/HAL/Switch.h"
#include "C:/Ruby30/lib/ruby/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"






extern const Switch_Config_t SwitchS[_Switch_Num];



void setUp(void)

{

}



void tearDown(void)

{

}

void test_Switch_Init_ValidParameters(void)

{

    GPIO_InitPin_CMockIgnoreAndReturn(19, Status_enumOk);

    UnityAssertEqualNumber((UNITY_INT)((Status_enumOk)), (UNITY_INT)((Switch_Init())), (

   ((void *)0)

   ), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_INT);

}

void test_Switch_Init_InValidParameters(void)

{

    GPIO_InitPin_CMockIgnoreAndReturn(24, Status_enumWrongInput);

    UnityAssertEqualNumber((UNITY_INT)((Status_enumWrongInput)), (UNITY_INT)((Switch_Init())), (

   ((void *)0)

   ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT);

}



void test_Switch_SetState_InvalidSwitchName(void)

{

    uint32_t Switch = _Switch_Num + 1;

    uint8_t TempVarForAdrr;

    uint8_t *Ptr = &TempVarForAdrr;

    UnityAssertEqualNumber((UNITY_INT)((Status_enumWrongInput)), (UNITY_INT)((Switch_Get_Status(Switch, Ptr))), (

   ((void *)0)

   ), (UNITY_UINT)(33), UNITY_DISPLAY_STYLE_INT);

}



void test_Switch_SetState_ValidSwitchName(void)

{

    if (_Switch_Num != 0)

    {

        uint32_t Switch = _Switch_Num - 1;

        uint8_t TempVarForAdrr;

        uint8_t *Ptr = &TempVarForAdrr;

        GPIO_Get_GetPinValue_CMockIgnoreAndReturn(43, Status_enumOk);

        UnityAssertEqualNumber((UNITY_INT)((Status_enumOk)), (UNITY_INT)((Switch_Get_Status(Switch, Ptr))), (

       ((void *)0)

       ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_INT);

    }

}



void test_Switch_SetState_ValidSwitchPointerStatus(void)

{

    if (_Switch_Num != 0)

    {

        uint32_t Switch = _Switch_Num - 1;

        uint8_t TempVarForAdrr;

        uint8_t *Ptr = &TempVarForAdrr;

        GPIO_Get_GetPinValue_CMockIgnoreAndReturn(55, Status_enumOk);

        UnityAssertEqualNumber((UNITY_INT)((Status_enumOk)), (UNITY_INT)((Switch_Get_Status(Switch, Ptr))), (

       ((void *)0)

       ), (UNITY_UINT)(56), UNITY_DISPLAY_STYLE_INT);

    }

}



void test_Switch_SetState_InValidSwitchPointerStatus_NULL(void)

{

    if (_Switch_Num != 0)

    {

        uint32_t Switch = _Switch_Num - 1;

        uint8_t *Ptr = 

                      ((void *)0)

                          ;

        GPIO_Get_GetPinValue_CMockIgnoreAndReturn(66, Status_enumOk);

        UnityAssertEqualNumber((UNITY_INT)((Status_enumNULLPointer)), (UNITY_INT)((Switch_Get_Status(Switch, Ptr))), (

       ((void *)0)

       ), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_INT);

    }

}
