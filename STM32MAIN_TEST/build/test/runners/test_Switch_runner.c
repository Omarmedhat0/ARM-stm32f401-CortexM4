/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "cmock.h"
#include "mock_GPIO.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_Switch_Init_ValidParameters(void);
extern void test_Switch_Init_InValidParameters(void);
extern void test_Switch_SetState_InvalidSwitchName(void);
extern void test_Switch_SetState_ValidSwitchName(void);
extern void test_Switch_SetState_ValidSwitchPointerStatus(void);
extern void test_Switch_SetState_InValidSwitchPointerStatus_NULL(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  mock_GPIO_Init();
}
static void CMock_Verify(void)
{
  mock_GPIO_Verify();
}
static void CMock_Destroy(void)
{
  mock_GPIO_Destroy();
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_Switch.c");
  run_test(test_Switch_Init_ValidParameters, "test_Switch_Init_ValidParameters", 17);
  run_test(test_Switch_Init_InValidParameters, "test_Switch_Init_InValidParameters", 22);
  run_test(test_Switch_SetState_InvalidSwitchName, "test_Switch_SetState_InvalidSwitchName", 28);
  run_test(test_Switch_SetState_ValidSwitchName, "test_Switch_SetState_ValidSwitchName", 36);
  run_test(test_Switch_SetState_ValidSwitchPointerStatus, "test_Switch_SetState_ValidSwitchPointerStatus", 48);
  run_test(test_Switch_SetState_InValidSwitchPointerStatus_NULL, "test_Switch_SetState_InValidSwitchPointerStatus_NULL", 60);

  CMock_Guts_MemFreeFinal();
  return UnityEnd();
}