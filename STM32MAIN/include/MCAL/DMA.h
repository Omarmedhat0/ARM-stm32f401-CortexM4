/*
 ============================================================================
 Name        : DMA.h
 Author      : Omar Medhat Mohamed
 Description : Header File for the DMA Driver
 Date        : 2/4/2024
 ============================================================================
 */
#ifndef DMA_H_
#define DMA_H_
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "LIB/std_types.h"
#include "LIB/Mask32.h"
#include "LIB/Error.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DMA1_ID 				0
#define DMA2_ID 				1
#define DMA6_ID 				2
#define DMA_WL_8BIT_DATA		0X00000000
#define DMA_WL_9BIT_DATA		0X00001000
#define DMA_PARITY_ENABLE		0X00000400
#define DMA_PARITY_DISABLE	0X00000000
#define DMA_EVEN_PARITY		0X00000000
#define DMA_ODD_PARITY		0X00000200
#define DMA_STOP_BIT_1		0X00000000
#define DMA_STOP_BIT_1_5		0X00003000
#define DMA_STOP_BIT_0_5		0X00001000
#define DMA_STOP_BIT_2		0X00002000
#define DMA_OVS_8				0X00008000
#define DMA_OVS_16			0X00000000
#define FCPU					16000000
#define	Done					1
#define	NOT_Done				0
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
typedef void (*Cb)(void);
typedef struct
{
	uint8_t 	DMA_ID;
	uint32_t 	BaudRate;
	uint32_t 	WordLength;
	uint32_t 	ParityEn;
	uint32_t 	ParityType;
	uint32_t 	StopBits;
	uint32_t 	OverSamplingMode;
}
DMA_Config_t;

typedef struct
{
	uint8_t DMA_ID;
	uint8_t *Ptr_buffer ;
	uint32_t Buff_Len ;
	Cb 		Buff_cb	;
}
DMA_UserReq_t;
/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
/*
 * @brief    : Set Clock ON.
 * @param[in]: Copy_Clock The clock source to be set on. It can be CLOCK_HSI, CLOCK_HSE, or CLOCK_PLL.
 * @return   : Error_enumStatus_t Error status indicating the success or failure of setting the clock on.
 * @details  : This function turns on the specified clock source.
			   It enables the clock according to the provided clock source.
 */
Error_enumStatus_t DMA_Init(void);
Error_enumStatus_t DMA_SendByte(DMA_UserReq_t* Ptr_UserReq);
Error_enumStatus_t DMA_GetByte(DMA_UserReq_t* Ptr_UserReq);
Error_enumStatus_t DMA_TxBufferAsyncZeroCopy(DMA_UserReq_t* Ptr_UserReq );
Error_enumStatus_t DMA_RxBufferAsyncZeroCopy(DMA_UserReq_t* Ptr_UserReq );
Error_enumStatus_t DMA_TxDone(uint8_t DMA_ID,uint8_t *Ptr_Status);
Error_enumStatus_t DMA_IsRx(uint8_t DMA_ID,uint8_t *Ptr_Status);


#endif