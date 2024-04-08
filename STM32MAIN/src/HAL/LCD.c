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

/****************************Processes Implementation************************************/
/**
 * @brief    : Handles the LCD tasks based on its current state.
 * @details  : This function checks the current state of the LCD and performs the corresponding actions.
 *             - If the LCD state is LCD_Init, it initializes the LCD by calling LCD_InitState().
 *             - If the LCD state is LCD_Operation and there's a pending user request:
 *               - If the request type is LCD_ReqWrite, it processes the write request by calling LCD_Write_Proc().
 *               - If the request type is LCD_ReqClear, it clears the LCD screen by calling LCD_Clear_Proc().
 *               - If the request type is LCD_ReqSetPos, it sets the cursor position by calling LCD_SetPosition_Proc().
 *               - If the request type is LCD_ReqWriteNumber, it writes a number to the LCD by calling LCD_WriteNumber_Proc().
 *             - If the LCD state is LCD_Off, no action is taken.
 * @param[in]: None
 * @param[out]: None
 * @return   : None
 **/
void LCD_Runnable(void)
{
    switch (g_LCD_State)
    {
    case LCD_Init:
        /* Handles the initialization process of the LCD */
        /* Calls LCD_InitState() to perform the initialization steps */
        LCD_InitState();
        break;
    case LCD_Operation:
        if (LCD_UserRequest.State == LCD_ReqBusy)
        {
            switch (LCD_UserRequest.Type)
            {
            case LCD_ReqWrite:
                /* Handles the LCD write request */
                /* Calls LCD_Write_Proc() to process the write request */
                LCD_Write_Proc();
                break;
            case LCD_ReqClear:
                /* Handles the LCD clear request */
                /* Calls LCD_Clear_Proc() to clear the LCD screen */
                LCD_Clear_Proc();
                break;
            case LCD_ReqSetPos:
                /* Handles the LCD set position request */
                /* Calls LCD_SetPosition_Proc() to set the cursor position */
                LCD_SetPosition_Proc();
                break;
            case LCD_ReqWriteNumber:
                /* Handles the LCD write number request */
                /* Calls LCD_WriteNumber_Proc() to write a number to the LCD */
                LCD_WriteNumber_Proc();
                break;
            default:
                break;
            }
        }
        break;
    case LCD_Off:
        /* No action is taken when the LCD is turned off */
        /* Do Nothing */
        break;
    default:
        break;
    }
}

/**
 * @brief    : Handles the LCD initialization process.
 * @details  : This function initializes the LCD based on the current initialization mode.
 *             - If the initialization mode is LCD_PowerOn, it performs power-on initialization by calling LCD_PowerOnProc()
 *               and sets the initialization mode to LCD_FunctionSet.
 *             - If the initialization mode is LCD_FunctionSet, it configures the LCD function settings by sending the appropriate command.
 *               If the LCD enable pin state is off, it sets the initialization mode to LCD_DisplayControl.
 *             - If the initialization mode is LCD_DisplayControl, it turns on the LCD cursor. If the LCD enable pin state is off,
 *               it sets the initialization mode to LCD_ClearDisplay.
 *             - If the initialization mode is LCD_ClearDisplay, it clears the LCD display. If the LCD enable pin state is off,
 *               it sets the initialization mode to LCD_EntryModeSet.
 *             - If the initialization mode is LCD_EntryModeSet, it configures the cursor increment and shift direction. If the LCD enable pin state is off,
 *               it sets the initialization mode to LCD_EndInit.
 *             - If the initialization mode is LCD_EndInit, it sets the LCD user request state to LCD_ReqReady and changes the LCD state to LCD_Operation.
 * @param    : None
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the initialization process.
 **/
static Error_enumStatus_t LCD_InitState(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    
    switch (g_LCD_InitMode)
    {
        /* Handles the LCD power-on initialization */
        /* Calls LCD_PowerOnProc() to perform power-on initialization */
        /* Sets the initialization mode to LCD_FunctionSet */
        case LCD_PowerOn:
            Loc_enumReturnStatus = LCD_PowerOnProc(); 
            g_LCD_InitMode = LCD_FunctionSet; 
            break;
        
        /* Handles the configuration of LCD function settings */
        /* Sends the appropriate command */
        /* If the LCD enable pin state is off, sets the initialization mode to LCD_DisplayControl */
        case LCD_FunctionSet:
            Loc_enumReturnStatus = LCD_WriteCommand(LCD_TWO_LINES_EIGHT_BITS_MODE); 
            if (g_LCD_EnablePinState == LCD_ENABLE_OFF) 
            {
                g_LCD_InitMode = LCD_DisplayControl;
            }
            break;
        
        /* Turns on the LCD cursor */
        /* If the LCD enable pin state is off, sets the initialization mode to LCD_ClearDisplay */
        case LCD_DisplayControl:
            Loc_enumReturnStatus = LCD_WriteCommand(LCD_CURSOR_ON); 
            if (g_LCD_EnablePinState == LCD_ENABLE_OFF) 
            {
                g_LCD_InitMode = LCD_ClearDisplay;
            }
            break;
        
        /* Clears the LCD display */
        /* If the LCD enable pin state is off, sets the initialization mode to LCD_EntryModeSet */
        case LCD_ClearDisplay:
            Loc_enumReturnStatus = LCD_WriteCommand(LCD_CLEAR_COMMAND); 
            if (g_LCD_EnablePinState == LCD_ENABLE_OFF) 
            {
                g_LCD_InitMode = LCD_EntryModeSet;
            }
            break;
        
        /* Configures the cursor increment and shift direction */
        /* If the LCD enable pin state is off, sets the initialization mode to LCD_EndInit */
        case LCD_EntryModeSet:
            Loc_enumReturnStatus = LCD_WriteCommand(LCD_INCREMENT_CRUSOR_SHIFT_RIGHT_MODE); 
            if (g_LCD_EnablePinState == LCD_ENABLE_OFF) 
            {
                g_LCD_InitMode = LCD_EndInit;
            }
            break;
        
        /* Sets the LCD user request state to LCD_ReqReady */
        /* Changes the LCD state to LCD_Operation */
        case LCD_EndInit:
            LCD_UserRequest.State = LCD_ReqReady; 
            g_LCD_State = LCD_Operation; 
            break;
        
        default:
            Loc_enumReturnStatus = Status_enumNotOk; 
            break;
    }
    
    /* Return the error status */
    return Loc_enumReturnStatus;
}



/**
 * @brief    : Handles the LCD write process.
 * @details  : This function writes characters or numbers to the LCD based on the current write state.
 *             - If the write state is LCD_WriteStart, it initializes the write process by setting the write state to LCD_WriteCharacter
 *               and resetting the current column position.
 *             - If the write state is LCD_WriteCharacter, it writes characters or numbers to the LCD until the entire string or number is written.
 *               If the LCD enable pin state is off, it increments the current column position.
 * @param    : None
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the write process.
 **/
static Error_enumStatus_t LCD_Write_Proc(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;

    switch (g_WriteState)
    {
        /* Initializes the write process */
        /* Sets the write state to LCD_WriteCharacter */
        /* Resets the current column position */
        case LCD_WriteStart:
            g_WriteState = LCD_WriteCharacter;
            g_CurrentWritePostion.CurColPostion = 0;
            break;
        
        /* Writes characters or numbers to the LCD */
        /* Increments the current column position */
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
    /* Return the error status */
    return Loc_enumReturnStatus;
}

/**
 * @brief    : Handles the process of setting the cursor position on the LCD.
 * @details  : This function sets the cursor position on the LCD based on the current position state.
 *             - If the position state is LCD_SetPosStart, it initializes the process by setting the cursor position and transitioning to LCD_SetPos.
 *             - If the position state is LCD_SetPos, it writes the command to set the cursor position.
 *               If the LCD enable pin state is off, it updates the LCD user request state and type, and resets the position state.
 * @param    : None
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the position setting process.
 **/
static Error_enumStatus_t LCD_SetPosition_Proc(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    static LCD_SetPosState_t Loc_u8PostionState = LCD_SetPosStart;
    static uint8_t Loc_Location = 0;
    switch (Loc_u8PostionState)
    {
        /* Initializes the cursor position setting process */
        /* Sets the cursor position */
        /* Transitions to LCD_SetPos */
        case LCD_SetPosStart:
            LCD_Helper_SetPosition(&Loc_Location);
            Loc_u8PostionState = LCD_SetPos;
            break;
        
        /* Writes the command to set the cursor position */
        /* Updates the LCD user request state and type */
        /* Resets the position state */
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

    /* Return the error status */
    return Loc_enumReturnStatus;
}

/**
 * @brief    : Handles the LCD clear process.
 * @details  : This function clears the content of the LCD screen.
 * @param    : None
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the clear process.
 **/
static Error_enumStatus_t LCD_Clear_Proc(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    
    /* Writes the command to clear the LCD display */
    LCD_WriteCommand(LCD_CLEAR_COMMAND);
    
    /* Updates the LCD user request state and type if the LCD enable pin state is off */
    if (g_LCD_EnablePinState == LCD_ENABLE_OFF)
    {
        LCD_UserRequest.State = LCD_ReqReady;
        LCD_UserRequest.Type = LCD_NoReq;
    }
    
    /* Return the error status */
    return Loc_enumReturnStatus;
}

/**
 * @brief    : Handles the process of writing a number to the LCD.
 * @details  : This function writes numbers to the LCD based on the current write number state.
 *             - If the write number state is LCD_WriteNumberStart, it initializes the process by setting the state to LCD_WriteNumber
 *               and resetting the current column position.
 *             - If the write number state is LCD_WriteNumber, it writes numbers to the LCD until the entire number is written.
 *               If the LCD enable pin state is off, it increments the current column position.
 * @param    : None
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the write number process.
 **/
static Error_enumStatus_t LCD_WriteNumber_Proc(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;

    switch (g_WriteNumState)
    {
        /* Initializes the write number process */
        /* Sets the write number state to LCD_WriteNumber */
        /* Resets the current column position */
        case LCD_WriteNumberStart:
            g_WriteNumState = LCD_WriteNumber;
            g_CurrentWritePostion.CurColPostion = 0;
            break;
        
        /* Writes numbers to the LCD */
        /* Increments the current column position */
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
    /* Return the error status */
    return Loc_enumReturnStatus;
}

/****************************User Async Functions************************************/

/**
 * @brief    : Initializes the LCD asynchronously.
 * @details  : This function sets the LCD state to LCD_Init.
 * @param    : None
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the initialization process.
 **/
Error_enumStatus_t LCD_InitAsync(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    
    /* Sets the LCD state to LCD_Init */
    g_LCD_State = LCD_Init;
    
    /* Return the error status */
    return Loc_enumReturnStatus;
}

/**
 * @brief    : Clears the LCD screen asynchronously.
 * @details  : This function sets the LCD user request state and type to initiate the clear process if the LCD state is LCD_Operation
 *             and the LCD user request state is LCD_ReqReady.
 * @param    : None
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the clear process initiation.
 **/
Error_enumStatus_t LCD_Clear_ScreenAsync(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    
    if (g_LCD_State == LCD_Operation && LCD_UserRequest.State == LCD_ReqReady)
    {
        /* Sets the LCD user request state and type to initiate the clear process */
        LCD_UserRequest.State = LCD_ReqBusy;
        LCD_UserRequest.Type = LCD_ReqClear;
    }
    else
    {
        Loc_enumReturnStatus = Status_enumNotOk;
    }

    /* Return the error status */
    return Loc_enumReturnStatus;
}

/**
 * @brief    : Writes a string to the LCD asynchronously.
 * @details  : This function sets the LCD user request state and type to initiate the write process with the provided string
 *             if the LCD state is LCD_Operation and the LCD user request state is LCD_ReqReady.
 * @param[in]: Ptr_string Pointer to the string to be written to the LCD.
 * @param[in]: size       Size of the string to be written.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the write process initiation.
 **/
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
            /* Sets the LCD user request state and type to initiate the write process with the provided string */
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
    
    /* Return the error status */
    return Loc_enumReturnStatus;
}

/**
 * @brief    : Sets the cursor position on the LCD asynchronously.
 * @details  : This function sets the cursor position on the LCD based on the provided row and column numbers.
 *             It sets the LCD user request state and type to initiate the process if the LCD state is LCD_Operation
 *             and the LCD user request state is LCD_ReqReady.
 * @param[in]: Copy_LCDPosX Row number for the cursor position.
 * @param[in]: Copy_LCDPosY Column number for the cursor position.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the position setting process initiation.
 **/
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
            /* Sets the LCD user request state and type to initiate the process */
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
    
    /* Return the error status */
    return Loc_enumReturnStatus;
}

/**
 * @brief    : Writes a number to the LCD asynchronously.
 * @details  : This function writes a number to the LCD based on the provided number.
 *             It sets the LCD user request state and type to initiate the write number process if the LCD state is LCD_Operation
 *             and the LCD user request state is LCD_ReqReady.
 * @param[in]: Copy_Number Number to be written to the LCD.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the write number process initiation.
 **/
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
    }
    
    /* Return the error status */
    return Loc_enumReturnStatus;
}

/****************************User Sync Functions************************************/


/**
 * @brief    : Retrieves the current status of the LCD.
 * @details  : This function retrieves the current status of the LCD and stores it in the provided pointer variable.
 * @param[out]: Ptr_LCDStatus Pointer to a variable to store the current status of the LCD.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of retrieving the LCD status.
 **/
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
        /* Retrieves the current status of the LCD */
        *Ptr_LCDStatus = g_LCD_State;
    }
    
    /* Return the error status */
    return Loc_enumReturnStatus;
}

/**********************************Static Helper Functions*********************************/
/**
 * @brief    : Performs the power-on sequence for the LCD.
 * @details  : This function configures the GPIO pins for the LCD according to the pin configuration array.
 *             It sets the LCD user request state to LCD_ReqBusy.
 *             This function is intended to be called during LCD initialization.
 * @param    : None
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the power-on sequence.
 **/
static Error_enumStatus_t LCD_PowerOnProc(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    
    /* Sets the LCD user request state to LCD_ReqBusy */
    LCD_UserRequest.State = LCD_ReqBusy;
    
    /* Initializes GPIO pins for the LCD */
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
    
    /* Return the error status */
    return Loc_enumReturnStatus;
}

/**
 * @brief    : Writes a command to the LCD.
 * @details  : This function writes a command to the LCD.
 *             It sets the LCD enable pin state based on the current state and configures the GPIO pins for the command.
 *             This function is intended to be used for sending commands to the LCD.
 * @param[in]: Copy_LCDCommand The command to be written to the LCD.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the command write operation.
 **/
static Error_enumStatus_t LCD_WriteCommand(uint8_t Copy_LCDCommand)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    
    /* Configuration for writing a command */
    uint8_t Loc_idx;
    uint32_t Loc_u32PinState;
    
    if (g_LCD_EnablePinState == LCD_ENABLE_OFF)
    {
        /* Configures pins for command write operation */
        Loc_enumReturnStatus = GPIO_Set_PinValue(LCDS[RS].Port, LCDS[RS].Pin, GPIO_RESET_PIN);
        Loc_enumReturnStatus |= GPIO_Set_PinValue(LCDS[RW].Port, LCDS[RW].Pin, GPIO_RESET_PIN);
        
        for (Loc_idx = 0; (Loc_enumReturnStatus == Status_enumOk) && (Loc_idx < (_LCD_Num - CONTROL_PINS_NUM)); Loc_idx++)
        {
            Loc_u32PinState = (Copy_LCDCommand & (1 << Loc_idx)) ? GPIO_SET_PIN : GPIO_RESET_PIN;
            Loc_enumReturnStatus = GPIO_Set_PinValue(LCDS[Loc_idx].Port, LCDS[Loc_idx].Pin, Loc_u32PinState);
        }
        
        /* Sets the LCD enable pin state */
        g_LCD_EnablePinState = LCD_ENABLE_ON;
        LCD_CtrlEnablePin(g_LCD_EnablePinState);
    }
    else
    {
        /* Disables LCD enable pin */
        g_LCD_EnablePinState = LCD_ENABLE_OFF;
        LCD_CtrlEnablePin(g_LCD_EnablePinState);
    }
    
    /* Return the error status */
    return Loc_enumReturnStatus;
}

/**
 * @brief    : Writes data to the LCD.
 * @details  : This function writes data to the LCD.
 *             It sets the LCD enable pin state based on the current state and configures the GPIO pins for the data.
 *             This function is intended to be used for sending data to be displayed on the LCD.
 * @param[in]: Copy_LCDCommand The data to be written to the LCD.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the data write operation.
 **/
static Error_enumStatus_t LCD_WriteData(uint8_t Copy_LCDCommand)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    
    /* Configuration for writing data */
    uint8_t Loc_idx;
    uint32_t Loc_u32PinState;
    
    if (g_LCD_EnablePinState == LCD_ENABLE_OFF)
    {
        /* Configures pins for data write operation */
        Loc_enumReturnStatus = GPIO_Set_PinValue(LCDS[RS].Port, LCDS[RS].Pin, GPIO_SET_PIN);
        Loc_enumReturnStatus |= GPIO_Set_PinValue(LCDS[RW].Port, LCDS[RW].Pin, GPIO_RESET_PIN);
        
        for (Loc_idx = 0; (Loc_enumReturnStatus == Status_enumOk) && (Loc_idx < (_LCD_Num - CONTROL_PINS_NUM)); Loc_idx++)
        {
            Loc_u32PinState = (Copy_LCDCommand & (1 << Loc_idx)) ? GPIO_SET_PIN : GPIO_RESET_PIN;
            Loc_enumReturnStatus = GPIO_Set_PinValue(LCDS[Loc_idx].Port, LCDS[Loc_idx].Pin, Loc_u32PinState);
        }
        
        /* Sets the LCD enable pin state */
        g_LCD_EnablePinState = LCD_ENABLE_ON;
        LCD_CtrlEnablePin(g_LCD_EnablePinState);
    }
    else
    {
        /* Disables LCD enable pin */
        g_LCD_EnablePinState = LCD_ENABLE_OFF;
        LCD_CtrlEnablePin(g_LCD_EnablePinState);
    }
    
    /* Return the error status */
    return Loc_enumReturnStatus;
}

/**
 * @brief    : Controls the LCD enable pin.
 * @details  : This function sets the state of the LCD enable pin.
 *             This function is intended to be used internally by the LCD driver.
 * @param[in]: Copy_LCDEnablePinState The state to set for the LCD enable pin (LCD_ENABLE_ON or LCD_ENABLE_OFF).
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the operation.
 **/
static Error_enumStatus_t LCD_CtrlEnablePin(uint32_t Copy_LCDEnablePinState)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    
    /* Sets the state of the LCD enable pin */
    Loc_enumReturnStatus = GPIO_Set_PinValue(LCDS[EN].Port, LCDS[EN].Pin, Copy_LCDEnablePinState);
    
    /* Return the error status */
    return Loc_enumReturnStatus;
}

/**
 * @brief    : Sets the cursor position on the LCD.
 * @details  : This function calculates the position of the cursor on the LCD based on the input parameters.
 *             It is used to set the cursor position before writing data to the LCD.
 *             This function is intended to be used internally by the LCD driver.
 * @param[in,out]: PTR_PostionDDRAM Pointer to a variable to store the calculated position on the LCD DDRAM.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of the operation.
 **/
static Error_enumStatus_t LCD_Helper_SetPosition(uint8_t *PTR_PostionDDRAM)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    
    /* Calculates the position of the cursor on the LCD DDRAM */
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
    
    /* Stores the calculated position in the pointer variable */
    *PTR_PostionDDRAM = Loc_u8LCDLoctaionOnDDRAM;
    
    /* Return the error status */
    return Loc_enumReturnStatus;
}
