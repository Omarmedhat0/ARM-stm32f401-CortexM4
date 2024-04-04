/*
 ============================================================================
 Name        : LCD.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the LCD Driver
 Date        : 17/2/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "HAL/LCD.h"
#include "MCAL/GPIO.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LCD_ENABLE_OFF GPIO_RESET_PIN
#define LCD_ENABLE_ON GPIO_SET_PIN
#define LCD_WRITE_COMMAND GPIO_RESET_PIN
#define LCD_WRITE_DATA GPIO_SET_PIN
#define CONTROL_PINS_NUM 0X00000003
/**********Commands Options************************/
#define LCD_ZERO_COMMAND 0x00
#define FOUR_BITS_DATA_MODE 0x02
#define LCD_CLEAR_COMMAND 0x01
#define LCD_GO_TO_HOME 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE 0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE 0x28
#define LCD_CURSOR_OFF 0x0C
#define LCD_CURSOR_ON 0x0E
#define LCD_SET_CURSOR_LOCATION 0x80
#define LCD_INCREMENT_CRUSOR_SHIFT_RIGHT_MODE 0x06
/********************Location in DDRAM handler for Lines*********************/
#define INDEX_FOR_LINE_1 0X0
#define INDEX_FOR_LINE_2 0X40
#define INDEX_FOR_LINE_3 0X10
#define INDEX_FOR_LINE_4 0X50
#define WRITE_ON_DDRAM_INDEX 0X80
#define INTEGER_OVER_FLOW   0xFF
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
typedef enum
{
    LCD_ReqReady,
    LCD_ReqBusy
} LCD_UserRequestState;
typedef enum
{
    LCD_NoReq,
    LCD_ReqWrite,
    LCD_ReqClear,
    LCD_ReqSetPos,
    LCD_ReqWriteNumber
} LCD_UserRequestType;
typedef enum
{
    LCD_Off,
    LCD_Init,
    LCD_Operation
} LCD_State_t;
typedef enum
{
    LCD_WriteStart,
    LCD_WriteCharacter,
} LCD_WriteState_t;
typedef enum
{
    LCD_WriteNumberStart,
    LCD_WriteNumber,
} LCD_WriteNumberState_t;
typedef enum
{
    LCD_SetPosStart,
    LCD_SetPos,
    LCD_SetPosEnd
} LCD_SetPosState_t;
typedef enum
{
    LCD_PowerOn,
    LCD_FunctionSet,
    LCD_DisplayControl,
    LCD_ClearDisplay,
    LCD_EntryModeSet,
    LCD_EndInit
} LCD_InitMode_t;
typedef struct
{
    uint8_t CurLinePostion;
    uint8_t CurColPostion;

} LCD_Write_t;

struct
{
    const uint8_t *UserString;
    uint16_t Len;
    LCD_UserRequestState State;
    LCD_UserRequestType Type;
    LCD_Write_t CurrentPos;

} LCD_UserRequest;

/*******************************************************************************
 *                              Variables                                       *
 *******************************************************************************/
extern const LCD_Config_t LCDS[_LCD_Num];
static uint32_t g_LCD_EnablePinState = LCD_ENABLE_OFF;
static LCD_State_t g_LCD_State = LCD_Off;
static LCD_InitMode_t g_LCD_InitMode = LCD_PowerOn;
static LCD_WriteState_t g_WriteState = LCD_WriteStart;
static LCD_WriteNumberState_t g_WriteNumState = LCD_WriteNumberStart ;
static LCD_Write_t g_CurrentWritePostion;
/*******************************************************************************
 *                         Static Function Prototypes		                   *
 *******************************************************************************/
static Error_enumStatus_t LCD_InitState(void);
static Error_enumStatus_t LCD_PowerOnProc(void);
static Error_enumStatus_t LCD_Write_Proc(void);
static Error_enumStatus_t LCD_SetPosition_Proc(void);
static Error_enumStatus_t LCD_Helper_SetPosition(uint8_t *PTR_PostionDDRAM);
static Error_enumStatus_t LCD_Clear_Proc(void);
static Error_enumStatus_t LCD_WriteNumber_Proc(void);
static Error_enumStatus_t LCD_WriteCommand(uint8_t Copy_LCDCommand);
static Error_enumStatus_t LCD_WriteData(uint8_t Copy_LCDCommand);
static Error_enumStatus_t LCD_CtrlEnablePin(uint32_t Copy_LCDEnablePinState);

/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/

/*
 * @brief    :
 * @param[in]:
 * @return   :
 * @details  :
 */
/****************************Processes Implementation************************************/
void LCD_Runnable(void)
{
    switch (g_LCD_State)
    {
    case LCD_Init:
        LCD_InitState();
        break;
    case LCD_Operation:
        if (LCD_UserRequest.State == LCD_ReqBusy)
        {
            switch (LCD_UserRequest.Type)
            {
            case LCD_ReqWrite:
                LCD_Write_Proc();
                break;
            case LCD_ReqClear:
                LCD_Clear_Proc();
                break;
            case LCD_ReqSetPos:
                LCD_SetPosition_Proc();
                break;
            case LCD_ReqWriteNumber:
                LCD_WriteNumber_Proc();
                break;
            default:
                break;
            }
        }
        break;
    case LCD_Off:
        /*Do Nothing*/
        break;
    default:
        break;
    }
}

static Error_enumStatus_t LCD_InitState(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    switch (g_LCD_InitMode)
    {
    case LCD_PowerOn:
        Loc_enumReturnStatus = LCD_PowerOnProc();
        g_LCD_InitMode = LCD_FunctionSet;
        break;
    case LCD_FunctionSet:
        Loc_enumReturnStatus = LCD_WriteCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
        if (g_LCD_EnablePinState == LCD_ENABLE_OFF)
        {
            g_LCD_InitMode = LCD_DisplayControl;
        }
        break;
    case LCD_DisplayControl:
        Loc_enumReturnStatus = LCD_WriteCommand(LCD_CURSOR_ON);
        if (g_LCD_EnablePinState == LCD_ENABLE_OFF)
        {
            g_LCD_InitMode = LCD_ClearDisplay;
        }
        break;
    case LCD_ClearDisplay:
        Loc_enumReturnStatus = LCD_WriteCommand(LCD_CLEAR_COMMAND);
        if (g_LCD_EnablePinState == LCD_ENABLE_OFF)
        {
            g_LCD_InitMode = LCD_EntryModeSet;
        }
        break;
    case LCD_EntryModeSet:
        Loc_enumReturnStatus = LCD_WriteCommand(LCD_INCREMENT_CRUSOR_SHIFT_RIGHT_MODE);
        if (g_LCD_EnablePinState == LCD_ENABLE_OFF)
        {
            g_LCD_InitMode = LCD_EndInit;
        }
        break;
    case LCD_EndInit:
        LCD_UserRequest.State = LCD_ReqReady;
        g_LCD_State = LCD_Operation;
        break;
    default:
        Loc_enumReturnStatus = Status_enumNotOk;
        break;
    }
    /*Return the error status*/
    return Loc_enumReturnStatus;
}

static Error_enumStatus_t LCD_Write_Proc(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;

    switch (g_WriteState)
    {
    case LCD_WriteStart:
        g_WriteState = LCD_WriteCharacter;
        g_CurrentWritePostion.CurColPostion = 0;
        break;
    case LCD_WriteCharacter:
        if (g_CurrentWritePostion.CurColPostion != LCD_UserRequest.Len)
        {
            LCD_WriteData(LCD_UserRequest.UserString[g_CurrentWritePostion.CurColPostion]);
            if (g_LCD_EnablePinState == LCD_ENABLE_OFF)
            {
                g_CurrentWritePostion.CurColPostion++;
            }
        }
        else
        {
             LCD_UserRequest.State = LCD_ReqReady;
            LCD_UserRequest.Type = LCD_NoReq;
            g_WriteState = LCD_WriteStart;
        }
        break;
    default:
        break;
    }
    /*Return the error status*/
    return Loc_enumReturnStatus;
}

static Error_enumStatus_t LCD_SetPosition_Proc(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    static LCD_SetPosState_t Loc_u8PostionState = LCD_SetPosStart;
    static uint8_t Loc_Location = 0;
    switch (Loc_u8PostionState)
    {
    case LCD_SetPosStart:
        LCD_Helper_SetPosition(&Loc_Location);
        Loc_u8PostionState = LCD_SetPos;
        break;
    case LCD_SetPos:
        Loc_enumReturnStatus = LCD_WriteCommand((WRITE_ON_DDRAM_INDEX + Loc_Location));
        if (g_LCD_EnablePinState == LCD_ENABLE_OFF)
        {
        LCD_UserRequest.State = LCD_ReqReady;
        LCD_UserRequest.Type = LCD_NoReq;
        Loc_u8PostionState = LCD_SetPosStart;
        }
        break;
    default:
        break;
    }

    /*Return the error status*/
    return Loc_enumReturnStatus;
}
static Error_enumStatus_t LCD_Clear_Proc(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    LCD_WriteCommand(LCD_CLEAR_COMMAND);
    if (g_LCD_EnablePinState == LCD_ENABLE_OFF)
    {
        LCD_UserRequest.State = LCD_ReqReady;
        LCD_UserRequest.Type = LCD_NoReq;
    }
    /*Return the error status*/
    return Loc_enumReturnStatus;
}
static Error_enumStatus_t LCD_WriteNumber_Proc(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;

    switch (g_WriteNumState)
    {
    case LCD_WriteNumberStart:
        g_WriteNumState = LCD_WriteNumber;
        g_CurrentWritePostion.CurColPostion = 0;
        break;
    case LCD_WriteNumber:
        if (g_CurrentWritePostion.CurColPostion != LCD_UserRequest.Len)
        {
            LCD_WriteData(LCD_UserRequest.UserString[g_CurrentWritePostion.CurColPostion]);
            if (g_LCD_EnablePinState == LCD_ENABLE_OFF)
            {
                g_CurrentWritePostion.CurColPostion++;
            }
        }
        else
        {
             LCD_UserRequest.State = LCD_ReqReady;
            LCD_UserRequest.Type = LCD_NoReq;
            g_WriteNumState = LCD_WriteNumberStart;
        }
        break;
    default:
        break;
    }
    /*Return the error status*/
    return Loc_enumReturnStatus;
}

/****************************User Async Functions************************************/

Error_enumStatus_t LCD_InitAsync(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    g_LCD_State = LCD_Init;
    /*Return the error status*/
    return Loc_enumReturnStatus;
}

Error_enumStatus_t LCD_Clear_ScreenAsync(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    if (g_LCD_State == LCD_Operation && LCD_UserRequest.State == LCD_ReqReady)
    {
        LCD_UserRequest.State = LCD_ReqBusy;
        LCD_UserRequest.Type = LCD_ReqClear;
    }
    else
    {
        Loc_enumReturnStatus = Status_enumNotOk;
    }

    /*Return the error status*/
    return Loc_enumReturnStatus;
}

Error_enumStatus_t LCD_Write_StringAsync(const uint8_t *Ptr_string, uint16_t size)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    if (Ptr_string == NULL)
    {
        Loc_enumReturnStatus = Status_enumNULLPointer;
    }
    else
    {
        if (g_LCD_State == LCD_Operation && LCD_UserRequest.State == LCD_ReqReady)
        {
            LCD_UserRequest.State = LCD_ReqBusy;
            LCD_UserRequest.Type = LCD_ReqWrite;
            LCD_UserRequest.UserString = Ptr_string;
            LCD_UserRequest.Len = size;
        }
        else
        {
            Loc_enumReturnStatus = Status_enumNotOk;
        }
    }
    /*Return the error status*/
    return Loc_enumReturnStatus;
}

Error_enumStatus_t LCD_Set_CursorPosAsync(uint8_t Copy_LCDPosX, uint8_t Copy_LCDPosY)
{

    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    if (g_LCD_State == LCD_Operation && LCD_UserRequest.State == LCD_ReqReady)
    {
        if ((Copy_LCDPosX >= MAX_NUM_OF_LINES) || (Copy_LCDPosY >= MAX_NUM_OF_CHARACTERS))
        {
            Loc_enumReturnStatus = Status_enumWrongInput;
        }
        else
        {
            LCD_UserRequest.State = LCD_ReqBusy;
            LCD_UserRequest.Type = LCD_ReqSetPos;
            LCD_UserRequest.CurrentPos.CurColPostion = Copy_LCDPosY;
            LCD_UserRequest.CurrentPos.CurLinePostion = Copy_LCDPosX;
        }
    }
    else
    {
        Loc_enumReturnStatus = Status_enumNotOk;
    }
    /*Return the error status*/
    return Loc_enumReturnStatus;
}

Error_enumStatus_t LCD_Write_NUmberAsync(uint32_t Copy_Number)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    static uint8_t NumberBuffer[16];
    uint8_t counter = 0;
    uint8_t Loc_idx = 0 ;
    uint32_t Loc_TempNum = Copy_Number;
    if (g_LCD_State == LCD_Operation && LCD_UserRequest.State == LCD_ReqReady)
    {
        LCD_UserRequest.State = LCD_ReqBusy;
        LCD_UserRequest.Type = LCD_ReqWriteNumber;
        if (Copy_Number == 0)
        {
            counter ++;
        }
        else
        {
            while (Loc_TempNum != 0)
            {
                Loc_TempNum = Loc_TempNum / 10;
                counter++;
            }
        }
        Loc_idx = counter-1 ;
        while (Loc_idx != INTEGER_OVER_FLOW)
        {
            NumberBuffer[Loc_idx] = (Copy_Number % 10) + '0';
            Copy_Number = Copy_Number / 10;
            Loc_idx -- ;
        }
        LCD_UserRequest.Len = counter;
        LCD_UserRequest.UserString = NumberBuffer;
    }
    else
    {
        Loc_enumReturnStatus = Status_enumNotOk;

        /*Return the error status*/
      
    }
      return Loc_enumReturnStatus;
}
/****************************User Sync Functions************************************/
Error_enumStatus_t LCD_Get_Status(uint8_t *Ptr_LCDStatus)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    if (Ptr_LCDStatus == NULL)
    {
        Loc_enumReturnStatus = Status_enumNULLPointer;
    }
    else
    {
        *Ptr_LCDStatus = g_LCD_State;
    }
    /*Return the error status*/
    return Loc_enumReturnStatus;
}
/**********************************Static Helper Functions*********************************/
static Error_enumStatus_t LCD_PowerOnProc(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    LCD_UserRequest.State = LCD_ReqBusy;
    uint8_t Loc_idx;
    GPIO_Config_t LCD_PinsHandler;
    LCD_PinsHandler.Mood = GPIO_OUTPUT_PP;
    LCD_PinsHandler.Speed = GPIO_HIGH_SPEED;
    for (Loc_idx = 0; (Loc_enumReturnStatus == Status_enumOk) && (Loc_idx < _LCD_Num); Loc_idx++)
    {
        LCD_PinsHandler.Port = LCDS[Loc_idx].Port;
        LCD_PinsHandler.Pin = LCDS[Loc_idx].Pin;
        Loc_enumReturnStatus = GPIO_InitPin(&LCD_PinsHandler);
    }
    /*Return the error status*/
    return Loc_enumReturnStatus;
}

static Error_enumStatus_t LCD_WriteCommand(uint8_t Copy_LCDCommand)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    uint8_t Loc_idx;
    uint32_t Loc_u32PinState;
    if (g_LCD_EnablePinState == LCD_ENABLE_OFF)
    {
        Loc_enumReturnStatus = GPIO_Set_PinValue(LCDS[RS].Port, LCDS[RS].Pin, GPIO_RESET_PIN);
        Loc_enumReturnStatus |= GPIO_Set_PinValue(LCDS[RW].Port, LCDS[RW].Pin, GPIO_RESET_PIN);
        for (Loc_idx = 0; (Loc_enumReturnStatus == Status_enumOk) && (Loc_idx < (_LCD_Num - CONTROL_PINS_NUM)); Loc_idx++)
        {
            Loc_u32PinState = (Copy_LCDCommand & (1 << Loc_idx)) ? GPIO_SET_PIN : GPIO_RESET_PIN;
            Loc_enumReturnStatus = GPIO_Set_PinValue(LCDS[Loc_idx].Port, LCDS[Loc_idx].Pin, Loc_u32PinState);
        }
        g_LCD_EnablePinState = LCD_ENABLE_ON;
        LCD_CtrlEnablePin(g_LCD_EnablePinState);
    }
    else
    {
        g_LCD_EnablePinState = LCD_ENABLE_OFF;
        LCD_CtrlEnablePin(g_LCD_EnablePinState);
    }
    /*Return the error status*/
    return Loc_enumReturnStatus;
}
static Error_enumStatus_t LCD_WriteData(uint8_t Copy_LCDCommand)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    uint8_t Loc_idx;
    uint32_t Loc_u32PinState;
    if (g_LCD_EnablePinState == LCD_ENABLE_OFF)
    {
        Loc_enumReturnStatus = GPIO_Set_PinValue(LCDS[RS].Port, LCDS[RS].Pin, GPIO_SET_PIN);
        Loc_enumReturnStatus |= GPIO_Set_PinValue(LCDS[RW].Port, LCDS[RW].Pin, GPIO_RESET_PIN);
        for (Loc_idx = 0; (Loc_enumReturnStatus == Status_enumOk) && (Loc_idx < (_LCD_Num - CONTROL_PINS_NUM)); Loc_idx++)
        {
            Loc_u32PinState = (Copy_LCDCommand & (1 << Loc_idx)) ? GPIO_SET_PIN : GPIO_RESET_PIN;
            Loc_enumReturnStatus = GPIO_Set_PinValue(LCDS[Loc_idx].Port, LCDS[Loc_idx].Pin, Loc_u32PinState);
        }
        g_LCD_EnablePinState = LCD_ENABLE_ON;
        LCD_CtrlEnablePin(g_LCD_EnablePinState);
    }
    else
    {
        g_LCD_EnablePinState = LCD_ENABLE_OFF;
        LCD_CtrlEnablePin(g_LCD_EnablePinState);
    }
    /*Return the error status*/
    return Loc_enumReturnStatus;
}
static Error_enumStatus_t LCD_CtrlEnablePin(uint32_t Copy_LCDEnablePinState)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    Loc_enumReturnStatus = GPIO_Set_PinValue(LCDS[EN].Port, LCDS[EN].Pin, Copy_LCDEnablePinState);
    /*Return the error status*/
    return Loc_enumReturnStatus;
}

static Error_enumStatus_t LCD_Helper_SetPosition(uint8_t *PTR_PostionDDRAM)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    uint8_t Loc_u8LCDLoctaionOnDDRAM = 0;
    switch (LCD_UserRequest.CurrentPos.CurLinePostion)
    {
    case LCD_DISPLAY_LINE1:
        Loc_u8LCDLoctaionOnDDRAM = LCD_UserRequest.CurrentPos.CurColPostion + INDEX_FOR_LINE_1;
        break;
    case LCD_DISPLAY_LINE2:
        Loc_u8LCDLoctaionOnDDRAM = LCD_UserRequest.CurrentPos.CurColPostion + INDEX_FOR_LINE_2;
        break;
    case LCD_DISPLAY_LINE3:
        Loc_u8LCDLoctaionOnDDRAM = LCD_UserRequest.CurrentPos.CurColPostion + INDEX_FOR_LINE_3;
        break;
    case LCD_DISPLAY_LINE4:
        Loc_u8LCDLoctaionOnDDRAM = LCD_UserRequest.CurrentPos.CurColPostion + INDEX_FOR_LINE_4;
        break;
    default:
        break;
    }
    *PTR_PostionDDRAM = Loc_u8LCDLoctaionOnDDRAM;

    /*Return the error status*/
    return Loc_enumReturnStatus;
}