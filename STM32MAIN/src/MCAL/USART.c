/*
 ============================================================================
 Name        : USART.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the USART Driver
 Date        : 30/3/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "MCAL/USART.h"
/*******************************************************************************
 *                             Definitions                                      *
 *******************************************************************************/
#define USART1_BA (void *)0x40011000
#define USART2_BA (void *)0x40004400
#define USART6_BA (void *)0x40011400
#define UART_NUMS_IN_TARGET 3
#define MANTISSA_SHIFT 4
#define UART_PRE_ENABLE_MASK 0X00002000
#define UART_TX_ENABLE_MASK 0X00000008
#define UART_TXE_ENABLE_MASK 0X00000080
#define UART_RX_ENABLE_MASK 0X00000004
#define UART_RXE_ENABLE_MASK 0X00000020
#define UART_RX_CLR_ENABLE_MASK 0XFFFFFFFB
#define UART_TX_EMPTY_FLAG 0X00000080
#define UART_RX_NOT_EMPTY_FLAG 0X00000020
#define UART_TX_DONE_FLAG 0X00000040
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
typedef void (*TX_CBF_t)(void);
typedef void (*RX_CBF_t)(void);
typedef enum
{
    USART_ReqReady,
    USART_ReqBusy
} USART_UserRequestState;
typedef struct
{
    uint8_t *data;
    uint32_t Pos;
    uint32_t size;
} USART_buffer_t;
typedef struct
{
    USART_buffer_t buffer;
    USART_UserRequestState state;
    TX_CBF_t CB;
} USART_TxReq_t;
typedef struct
{
    USART_buffer_t buffer;
    USART_UserRequestState state;
    TX_CBF_t CB;
} USART_RXReq_t;
typedef struct
{
    uint32_t USART_SR;
    uint32_t USART_DR;
    uint32_t USART_BRR;
    uint32_t USART_CR1;
    uint32_t USART_CR2;
    uint32_t USART_CR3;
    uint32_t USART_GTPR;

} USART_PERI_t;

/*******************************************************************************
 *                              Variables		                                *
 *******************************************************************************/
extern const USART_Config_t USARTS[_USART_Num];
volatile void *const USART[UART_NUMS_IN_TARGET] = {USART1_BA, USART2_BA, USART6_BA};
static USART_TxReq_t TxReq[_USART_Num];
static USART_RXReq_t RxReq[_USART_Num];
/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*
 * @brief    : Set Clock ON.
 * @param[in]: Copy_Clock The clock source to be set on. It can be CLOCK_HSI, CLOCK_HSE, or CLOCK_PLL.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of setting the clock on.
 * @details  : This function turns on the specified clock source.
               It enables the clock according to the provided clock source.
 */
Error_enumStatus_t USART_Init(void)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    uint8_t Loc_idx;
    uint32_t Loc_BRRValue = 0;
    uint32_t Loc_CR1Value = 0;
    uint32_t Loc_CR2Value = 0;
    uint32_t Loc_OVER8 = 0;
    uint32_t Loc_USARTDIVValue = 0;
    uint32_t Loc_DIV_Fraction = 0;
    uint32_t Loc_DIV_Mantissa = 0;
    if (_USART_Num > (USART6_ID + 1))
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    else
    {
        for (Loc_idx = 0; Loc_idx < _USART_Num; Loc_idx++)
        {
            Loc_OVER8 = USARTS[Loc_idx].OverSamplingMode / USART_OVS_8;
            Loc_USARTDIVValue = (FCPU * 100) / (8 * (2 - Loc_OVER8) * USARTS[Loc_idx].BaudRate);
            Loc_DIV_Fraction = (Loc_USARTDIVValue % 100) * (8 * (2 - Loc_OVER8));
            if (Loc_DIV_Fraction % 100 != 0)
            {
                Loc_DIV_Fraction = Loc_DIV_Fraction / 100;
                Loc_DIV_Fraction = Loc_DIV_Fraction * 100 + 100;
            }
            Loc_DIV_Mantissa = Loc_USARTDIVValue / 100;
            if (((Loc_OVER8 == 1) && (Loc_DIV_Fraction == 800)) || ((Loc_OVER8 == 0) && (Loc_DIV_Fraction == 1600)))
            {
                Loc_DIV_Fraction--;
                Loc_DIV_Mantissa++;
            }
            Loc_DIV_Fraction = Loc_DIV_Fraction / 100;
            Loc_DIV_Mantissa = Loc_DIV_Mantissa << MANTISSA_SHIFT;
            Loc_BRRValue = Loc_DIV_Mantissa | Loc_DIV_Fraction;
            Loc_CR1Value = UART_PRE_ENABLE_MASK | USARTS[Loc_idx].OverSamplingMode | USARTS[Loc_idx].WordLength | USARTS[Loc_idx].ParityEn | USARTS[Loc_idx].ParityType;
            Loc_CR2Value = USARTS[Loc_idx].StopBits;
            ((USART_PERI_t *)USART[USARTS[Loc_idx].USART_ID])->USART_BRR = Loc_BRRValue;
            ((USART_PERI_t *)USART[USARTS[Loc_idx].USART_ID])->USART_CR1 = Loc_CR1Value;
            ((USART_PERI_t *)USART[USARTS[Loc_idx].USART_ID])->USART_CR2 = Loc_CR2Value;
        }
    }

    /* Return the status of the clock operation */
    return Loc_enumReturnStatus;
}
Error_enumStatus_t USART_TxBufferAsyncZeroCopy(USART_UserReq_t *Ptr_UserReq)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    if (Ptr_UserReq == NULL)
    {
        Loc_enumReturnStatus = Status_enumNULLPointer;
    }
    else if (TxReq[Ptr_UserReq->USART_ID].state == USART_ReqReady)
    {
        TxReq[Ptr_UserReq->USART_ID].state = USART_ReqBusy;
        TxReq[Ptr_UserReq->USART_ID].buffer.data = Ptr_UserReq->Ptr_buffer;
        TxReq[Ptr_UserReq->USART_ID].buffer.size = Ptr_UserReq->Buff_Len;
        TxReq[Ptr_UserReq->USART_ID].buffer.Pos = 0;
        TxReq[Ptr_UserReq->USART_ID].CB = Ptr_UserReq->Buff_cb;
        ((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_CR1 |= UART_TX_ENABLE_MASK;
        ((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_DR = TxReq[Ptr_UserReq->USART_ID].buffer.data[0];
        TxReq[Ptr_UserReq->USART_ID].buffer.Pos++;
        ((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_CR1 |= UART_TXE_ENABLE_MASK;
    }
    else
    {
        Loc_enumReturnStatus = Status_enumBusyState;
    }

    /* Return the status of the clock operation */
    return Loc_enumReturnStatus;
}
Error_enumStatus_t USART_RxBufferAsyncZeroCopy(USART_UserReq_t *Ptr_UserReq)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    if (Ptr_UserReq == NULL)
    {
        Loc_enumReturnStatus = Status_enumNULLPointer;
    }
    else if (RxReq[Ptr_UserReq->USART_ID].state == USART_ReqReady)
    {
        /*Clear Rx ne*/
        ((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_CR1 &= UART_RX_CLR_ENABLE_MASK;
        RxReq[Ptr_UserReq->USART_ID].state = USART_ReqBusy;
        RxReq[Ptr_UserReq->USART_ID].buffer.data = Ptr_UserReq->Ptr_buffer;
        RxReq[Ptr_UserReq->USART_ID].buffer.size = Ptr_UserReq->Buff_Len;
        RxReq[Ptr_UserReq->USART_ID].buffer.Pos = 0;
        RxReq[Ptr_UserReq->USART_ID].CB = Ptr_UserReq->Buff_cb;
        ((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_CR1 |= UART_RX_ENABLE_MASK;
        ((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_CR1 |= UART_RXE_ENABLE_MASK;
        /*Enable RX NE*/
    }
    else
    {
        Loc_enumReturnStatus = Status_enumBusyState;
    }
    /* Return the status of the clock operation */
    return Loc_enumReturnStatus;
}

Error_enumStatus_t USART_SendByte(USART_UserReq_t *Ptr_UserReq)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    if (Ptr_UserReq == NULL)
    {
        Loc_enumReturnStatus = Status_enumNULLPointer;
    }
    else if (Ptr_UserReq->Buff_Len > 1)
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    else if (TxReq[Ptr_UserReq->USART_ID].state == USART_ReqReady)
    {
        volatile uint16_t Time = 2000;
        TxReq[Ptr_UserReq->USART_ID].state = USART_ReqBusy;
        ((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_DR = *(Ptr_UserReq->Ptr_buffer);
        ((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_CR1 |= UART_TX_ENABLE_MASK;
        while ((((((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_SR) & (UART_TX_EMPTY_FLAG)) == 0) && Time)
        {
            Time--;
        }
        if (Time == 0)
        {
            if (((((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_SR) & UART_TX_EMPTY_FLAG) == 0)
            {
                Loc_enumReturnStatus = Status_enumTimOut;
            }
        }
        TxReq[Ptr_UserReq->USART_ID].state = USART_ReqReady;
    }
    else
    {
        Loc_enumReturnStatus = Status_enumBusyState;
    }
    /* Return the status of the clock operation */
    return Loc_enumReturnStatus;
}
Error_enumStatus_t USART_GetByte(USART_UserReq_t *Ptr_UserReq)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    if (Ptr_UserReq == NULL)
    {
        Loc_enumReturnStatus = Status_enumNULLPointer;
    }
    else if (Ptr_UserReq->Buff_Len > 1)
    {
        Loc_enumReturnStatus = Status_enumWrongInput;
    }
    else if (RxReq[Ptr_UserReq->USART_ID].state == USART_ReqReady)
    {
        volatile uint16_t Time = 2000;
        RxReq[Ptr_UserReq->USART_ID].state = USART_ReqBusy;
       ((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_CR1 |= UART_RX_ENABLE_MASK;
        while ((((((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_SR) & UART_RX_NOT_EMPTY_FLAG) == 0) && Time)
        {
            Time--;
        }
        if (Time == 0)
        {
            if (((((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_SR) & UART_RX_NOT_EMPTY_FLAG) == 0)
            {
                Loc_enumReturnStatus = Status_enumTimOut;
            }
            else
            {
                *(Ptr_UserReq->Ptr_buffer) = ((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_DR;
            }
        }
        else
        {
            *(Ptr_UserReq->Ptr_buffer) = ((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_DR;
        }
        ((USART_PERI_t *)USART[Ptr_UserReq->USART_ID])->USART_CR1 &= ~UART_RX_ENABLE_MASK;
        RxReq[Ptr_UserReq->USART_ID].state = USART_ReqReady;
    }
    else
    {
        Loc_enumReturnStatus = Status_enumBusyState;
    }
    /* Return the status of the clock operation */
    return Loc_enumReturnStatus;
}
Error_enumStatus_t USART_TxDone(uint8_t USART_ID, uint8_t *Ptr_Status)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    if (Ptr_Status == NULL)
    {
        Loc_enumReturnStatus = Status_enumNULLPointer;
    }
    else
    {
        if ((((((USART_PERI_t *)USART[USART_ID])->USART_SR) & UART_TX_DONE_FLAG) != 0))
        {
            *Ptr_Status = Done;
        }
        else
        {
            *Ptr_Status = NOT_Done;
        }
    }
    /* Return the status of the clock operation */
    return Loc_enumReturnStatus;
}
Error_enumStatus_t USART_IsRx(uint8_t USART_ID, uint8_t *Ptr_Status)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk;
    if (Ptr_Status == NULL)
    {
        Loc_enumReturnStatus = Status_enumNULLPointer;
    }
    else
    {
        if ((((((USART_PERI_t *)USART[USART_ID])->USART_SR) & UART_RX_NOT_EMPTY_FLAG) != 0))
        {
            *Ptr_Status = Done;
        }
        else
        {
            *Ptr_Status = NOT_Done;
        }
    }
    /* Return the status of the clock operation */
    return Loc_enumReturnStatus;
}

void USART1_IRQHandler(void)
{
    uint32_t Lo_CR1_Value = ((USART_PERI_t *)USART[USART1_ID])->USART_CR1 ;
    if ((((USART_PERI_t *)USART[USART1_ID])->USART_SR) & UART_TX_DONE_FLAG)
    {
        if ((TxReq[USART1_ID].buffer.Pos) < (TxReq[USART1_ID].buffer.size))
        {
            ((USART_PERI_t *)USART[USART1_ID])->USART_DR = TxReq[USART1_ID].buffer.data[TxReq[USART1_ID].buffer.Pos];
            TxReq[USART1_ID].buffer.Pos++;
        }
        else
        {
            
            Lo_CR1_Value &= ~(UART_TXE_ENABLE_MASK); 
            Lo_CR1_Value&= ~(UART_TX_ENABLE_MASK);
            TxReq[USART1_ID].state = USART_ReqReady;
            ((USART_PERI_t *)USART[USART1_ID])->USART_CR1 = Lo_CR1_Value ;           
            if (TxReq[USART1_ID].CB)
            {
                TxReq[USART1_ID].CB();
            }
        }
    }
    if ((((USART_PERI_t *)USART[USART1_ID])->USART_SR) & UART_RX_NOT_EMPTY_FLAG)
    {
        if (RxReq[USART1_ID].buffer.Pos < RxReq[USART1_ID].buffer.size)
        {
            RxReq[USART1_ID].buffer.data[RxReq[USART1_ID].buffer.Pos] = ((USART_PERI_t *)USART[USART1_ID])->USART_DR;
            RxReq[USART1_ID].buffer.Pos++;
            if (RxReq[USART1_ID].buffer.Pos == RxReq[USART1_ID].buffer.size)
            {
                RxReq[USART1_ID].state = USART_ReqReady;
                ((USART_PERI_t *)USART[USART1_ID])->USART_CR1 &= ~UART_RXE_ENABLE_MASK;
                if (RxReq[USART1_ID].CB)
                {
                    RxReq[USART1_ID].CB();
                }
            }
        }
    }
}
void USART2_IRQHandler(void)
{
    uint32_t Lo_CR1_Value = ((USART_PERI_t *)USART[USART2_ID])->USART_CR1 ;
    if ((((USART_PERI_t *)USART[USART2_ID])->USART_SR) & UART_TX_DONE_FLAG)
    {
        if ((TxReq[USART2_ID].buffer.Pos) < (TxReq[USART2_ID].buffer.size))
        {
            ((USART_PERI_t *)USART[USART2_ID])->USART_DR = TxReq[USART2_ID].buffer.data[TxReq[USART2_ID].buffer.Pos];
            TxReq[USART2_ID].buffer.Pos++;
        }
        else
        {
            
            Lo_CR1_Value &= ~(UART_TXE_ENABLE_MASK); 
            Lo_CR1_Value&= ~(UART_TX_ENABLE_MASK);
            TxReq[USART2_ID].state = USART_ReqReady;
            ((USART_PERI_t *)USART[USART2_ID])->USART_CR1 = Lo_CR1_Value ;           
            if (TxReq[USART2_ID].CB)
            {
                TxReq[USART2_ID].CB();
            }
        }
    }
    if ((((USART_PERI_t *)USART[USART2_ID])->USART_SR) & UART_RX_NOT_EMPTY_FLAG)
    {
        if (RxReq[USART2_ID].buffer.Pos < RxReq[USART2_ID].buffer.size)
        {
            RxReq[USART2_ID].buffer.data[RxReq[USART2_ID].buffer.Pos] = ((USART_PERI_t *)USART[USART2_ID])->USART_DR;
            RxReq[USART2_ID].buffer.Pos++;
            if (RxReq[USART2_ID].buffer.Pos == RxReq[USART2_ID].buffer.size)
            {
                RxReq[USART2_ID].state = USART_ReqReady;
                ((USART_PERI_t *)USART[USART2_ID])->USART_CR1 &= ~UART_RXE_ENABLE_MASK;
                if (RxReq[USART2_ID].CB)
                {
                    RxReq[USART2_ID].CB();
                }
            }
        }
    }
}
void USART6_IRQHandler(void)
{
    uint32_t Lo_CR1_Value = ((USART_PERI_t *)USART[USART6_ID])->USART_CR1 ;
    if ((((USART_PERI_t *)USART[USART6_ID])->USART_SR) & UART_TX_DONE_FLAG)
    {
        if ((TxReq[USART6_ID].buffer.Pos) < (TxReq[USART6_ID].buffer.size))
        {
            ((USART_PERI_t *)USART[USART6_ID])->USART_DR = TxReq[USART6_ID].buffer.data[TxReq[USART6_ID].buffer.Pos];
            TxReq[USART6_ID].buffer.Pos++;
        }
        else
        {
            
            Lo_CR1_Value &= ~(UART_TXE_ENABLE_MASK); 
            Lo_CR1_Value&= ~(UART_TX_ENABLE_MASK);
            TxReq[USART6_ID].state = USART_ReqReady;
            ((USART_PERI_t *)USART[USART6_ID])->USART_CR1 = Lo_CR1_Value ;           
            if (TxReq[USART6_ID].CB)
            {
                TxReq[USART6_ID].CB();
            }
        }
    }
    if ((((USART_PERI_t *)USART[USART6_ID])->USART_SR) & UART_RX_NOT_EMPTY_FLAG)
    {
        if (RxReq[USART6_ID].buffer.Pos < RxReq[USART6_ID].buffer.size)
        {
            RxReq[USART6_ID].buffer.data[RxReq[USART6_ID].buffer.Pos] = ((USART_PERI_t *)USART[USART6_ID])->USART_DR;
            RxReq[USART6_ID].buffer.Pos++;
            if (RxReq[USART6_ID].buffer.Pos == RxReq[USART6_ID].buffer.size)
            {
                RxReq[USART6_ID].state = USART_ReqReady;
                ((USART_PERI_t *)USART[USART6_ID])->USART_CR1 &= ~UART_RXE_ENABLE_MASK;
                if (RxReq[USART6_ID].CB)
                {
                    RxReq[USART6_ID].CB();
                }
            }
        }
    }
}