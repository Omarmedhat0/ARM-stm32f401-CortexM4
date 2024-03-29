/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_GPIO_H
#define _MOCK_GPIO_H

#include "unity.h"
#include "GPIO.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void mock_GPIO_Init(void);
void mock_GPIO_Destroy(void);
void mock_GPIO_Verify(void);




#define GPIO_InitPin_IgnoreAndReturn(cmock_retval) GPIO_InitPin_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void GPIO_InitPin_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, Error_enumStatus_t cmock_to_return);
#define GPIO_InitPin_StopIgnore() GPIO_InitPin_CMockStopIgnore()
void GPIO_InitPin_CMockStopIgnore(void);
#define GPIO_InitPin_ExpectAndReturn(Loc_GPIOElement, cmock_retval) GPIO_InitPin_CMockExpectAndReturn(__LINE__, Loc_GPIOElement, cmock_retval)
void GPIO_InitPin_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, GPIO_Config_t* Loc_GPIOElement, Error_enumStatus_t cmock_to_return);
typedef Error_enumStatus_t (* CMOCK_GPIO_InitPin_CALLBACK)(GPIO_Config_t* Loc_GPIOElement, int cmock_num_calls);
void GPIO_InitPin_AddCallback(CMOCK_GPIO_InitPin_CALLBACK Callback);
void GPIO_InitPin_Stub(CMOCK_GPIO_InitPin_CALLBACK Callback);
#define GPIO_InitPin_StubWithCallback GPIO_InitPin_Stub
#define GPIO_Set_PinValue_IgnoreAndReturn(cmock_retval) GPIO_Set_PinValue_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void GPIO_Set_PinValue_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, Error_enumStatus_t cmock_to_return);
#define GPIO_Set_PinValue_StopIgnore() GPIO_Set_PinValue_CMockStopIgnore()
void GPIO_Set_PinValue_CMockStopIgnore(void);
#define GPIO_Set_PinValue_ExpectAndReturn(Port, Copy_PinNum, Copy_PinState, cmock_retval) GPIO_Set_PinValue_CMockExpectAndReturn(__LINE__, Port, Copy_PinNum, Copy_PinState, cmock_retval)
void GPIO_Set_PinValue_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, void* Port, u32_t Copy_PinNum, u32_t Copy_PinState, Error_enumStatus_t cmock_to_return);
typedef Error_enumStatus_t (* CMOCK_GPIO_Set_PinValue_CALLBACK)(void* Port, u32_t Copy_PinNum, u32_t Copy_PinState, int cmock_num_calls);
void GPIO_Set_PinValue_AddCallback(CMOCK_GPIO_Set_PinValue_CALLBACK Callback);
void GPIO_Set_PinValue_Stub(CMOCK_GPIO_Set_PinValue_CALLBACK Callback);
#define GPIO_Set_PinValue_StubWithCallback GPIO_Set_PinValue_Stub
#define GPIO_Get_GetPinValue_IgnoreAndReturn(cmock_retval) GPIO_Get_GetPinValue_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void GPIO_Get_GetPinValue_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, Error_enumStatus_t cmock_to_return);
#define GPIO_Get_GetPinValue_StopIgnore() GPIO_Get_GetPinValue_CMockStopIgnore()
void GPIO_Get_GetPinValue_CMockStopIgnore(void);
#define GPIO_Get_GetPinValue_ExpectAndReturn(Port, Copy_PinNum, PinStatus, cmock_retval) GPIO_Get_GetPinValue_CMockExpectAndReturn(__LINE__, Port, Copy_PinNum, PinStatus, cmock_retval)
void GPIO_Get_GetPinValue_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, void* Port, u32_t Copy_PinNum, u8_t* PinStatus, Error_enumStatus_t cmock_to_return);
typedef Error_enumStatus_t (* CMOCK_GPIO_Get_GetPinValue_CALLBACK)(void* Port, u32_t Copy_PinNum, u8_t* PinStatus, int cmock_num_calls);
void GPIO_Get_GetPinValue_AddCallback(CMOCK_GPIO_Get_GetPinValue_CALLBACK Callback);
void GPIO_Get_GetPinValue_Stub(CMOCK_GPIO_Get_GetPinValue_CALLBACK Callback);
#define GPIO_Get_GetPinValue_StubWithCallback GPIO_Get_GetPinValue_Stub

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
