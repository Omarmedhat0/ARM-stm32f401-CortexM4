/*
 ============================================================================
 Name        : RCC.h
 Author      : Omar Medhat Mohamed
 Description : Header File for the RCC Driver
 Date        : 10/2/2024
 ============================================================================
 */
#ifndef RCC_H_
#define RCC_H_
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include  	"Includes/Includes/std_types.h"
#include 	"Includes/Includes/Mask32.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define CLOCK_HSI		BIT0_MASK
#define CLOCK_HSE		BIT16_MASK
#define CLOCK_PLL 		BIT24_MASK

#define SysClk_HSI_MASK	BIT0_MASK
#define SysClk_HSE_MASK	BIT1_MASK
#define SysClk_PLL_MASK	BIT2_MASK

#define PLL_SRC_HSI		0XFFBFFFFF
#define PLL_SRC_HSE 	0X00400000

/************AHB1_BUS_Peripheral_Masks ************/
#define GPIOA	BIT0_MASK
#define GPIOB	BIT1_MASK
#define GPIOC	BIT2_MASK
#define GPIOD	BIT3_MASK
#define GPIOE	BIT4_MASK
#define GPIOH	BIT7_MASK
#define CRC 	BIT12_MASK
#define DMA1	BIT21_MASK
#define DMA2	BIT22_MASK
/************AHB2_BUS_Peripheral_Masks ************/
#define OTGFS	BIT7_MASK
/************APB1_BUS_Peripheral_Masks ************/
#define TIM2	BIT0_MASK
#define TIM3	BIT1_MASK
#define TIM4	BIT2_MASK
#define TIM5	BIT3_MASK
#define WWDG	BIT11_MASK
#define SPI2	BIT14_MASK
#define SPI3	BIT15_MASK
#define USART2	BIT17_MASK
#define I2C1	BIT21_MASK
#define I2C2	BIT22_MASK
#define I2C3	BIT23_MASK
#define PWR		BIT28_MASK
/************APB2_BUS_Peripheral_Masks ************/
#define TIM1	BIT0_MASK
#define USART1	BIT4_MASK
#define USART6	BIT5_MASK
#define ADC1	BIT8_MASK
#define SDIO	BIT11_MASK
#define SPI1	BIT12_MASK
#define SPI4	BIT13_MASK
#define SYSCFG	BIT14_MASK
#define TIM9	BIT16_MASK
#define TIM10	BIT17_MASK
#define TIM11	BIT18_MASK
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	/**
	 *@brief : Everything Ok, Function had Performed Correctly.
	 */
	RCC_enumOk ,
	RCC_enumONFailed ,
	RCC_enumOFFFailed ,
	RCC_enumClockNotReady,
	RCC_enumWrongInput

}RCC_enumError_t;

typedef enum
{
	/**
	 *@brief : Everything Ok, Function had Performed Correctly.
	 */
	APB_H_1 =  0, APB_H_2 =  4, APB_H_4, APB_H_8, APB_H_16,
}RCC_APB_HS_PRE_t;

typedef enum
{
	/**
	 *@brief : Everything Ok, Function had Performed Correctly.
	 */
	APB_L_1 =  0, APB_L_2 =  4, APB_L_4 , APB_L_8 ,APB_L_16 ,

}RCC_APB_LW_PRE_t;

typedef enum
{
	/**
	 *@brief : Everything Ok, Function had Performed Correctly.
	 */
	AHB_1 =  0, AHB_2 =  8,AHB_4 ,AHB_8	,AHB_L_16 ,	AHB_64 , AHB_128 , AHB_256 , AHB_512


}RCC_AHB_PRE_t;

typedef enum
{
	/**
	 *@brief : Everything Ok, Function had Performed Correctly.
	 */
	APB_HIGH_PRE,APB_LOW_PRE,AHB_PRE


}RCC_PRESCALER_t;
/*******************************************************************************
 *                  	    Functions Prototypes                               *
 *******************************************************************************/
/*
 * @brief    : Set Clock ON.
 * @param[in]: Copy_Clock The clock source to be set on. It can be CLOCK_HSI, CLOCK_HSE, or CLOCK_PLL.
 * @return   : RCC_enumError_t Error status indicating the success or failure of setting the clock on.
 * @details  : This function turns on the specified clock source. 
 			   It enables the clock according to the provided clock source.
 */
RCC_enumError_t RCC_SET_Clock_ON (uint32_t Copy_Clock);
/*
 * @brief    : Set Clock OFF.
 * @param[in]: Copy_Clock The clock source to be turned off. It can be CLOCK_HSI, CLOCK_HSE, or CLOCK_PLL.
 * @return   : RCC_enumError_t Error status indicating the success or failure of turning the clock off.
 * @details  : This function turns off the specified clock source. 
 			   It disables the clock according to the provided clock source.
 */
RCC_enumError_t RCC_SET_Clock_OFF (uint32_t Copy_Clock);
/*
 * @brief    : Select System Clock.
 * @param[in]: Copy_SysClk The system clock source to be selected. It can be SysClk_HSI_MASK, SysClk_HSE_MASK, or SysClk_PLL_MASK.
 * @return   : RCC_enumError_t Error status indicating the success or failure of selecting the system clock.
 * @details  : This function selects the system clock source among the available options: HSI, HSE, or PLL.
 */
RCC_enumError_t RCC_Select_Sysclk(uint32_t Copy_SysClk );
/*
 * @brief    : Configure PLL Source.
 * @param[in]: Copy_PLLSrc The PLL source to be configured. It can be PLL_SRC_HSI or PLL_SRC_HSE.
 * @return   : RCC_enumError_t Error status indicating the success or failure of configuring PLL source.
 * @details  : This function configures the PLL source to be either HSI or HSE.
 */
RCC_enumError_t RCC_Config_PLLSrc(uint32_t	Copy_PLLSrc);
/*
 * @brief    : Configure PLL Parameters.
 * @param[in]: PLLM, PLLN, PLLP, PLLQ The parameters to configure PLL.
 * @return   : RCC_enumError_t Error status indicating the success or failure of configuring PLL parameters.
 * @details  : This function configures the parameters (M, N, P, Q) for the PLL.
 * @note     : Ranges of Paramters 2<=PLLM<=63 ,192<=PLLN<=432 , 2<=PLLQ<=15 , PLLP = 2,4,6,8
 */
RCC_enumError_t RCC_Config_PLLParamters(uint32_t PLLM ,uint32_t PLLN , uint32_t PLLP ,uint32_t PLLQ);

/*
 * @brief    : Configure System Prescaler.
 * @param[in]: Copy_PreScalerID The prescaler type to be configured: APB_HIGH_PRE, APB_LOW_PRE, or AHB_PRE.
 * @param[in]: CopyPreScalerValue The value to configure the prescaler.
 * @return   : RCC_enumError_t Error status indicating the success or failure of configuring system prescaler.
 * @details  : This function configures the prescaler for the specified bus (AHB1, AHB2, APB1, APB2).
 */
RCC_enumError_t RCC_Config_SystemPrescaler (RCC_PRESCALER_t Copy_PreScalerID,uint32_t  CopyPreScalerValue);
/*
 * @brief    : Enable AHB1 Peripheral.
 * @param[in]: Copy_AHB1PeripheralName The AHB1 peripheral to be enabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of enabling the AHB1 peripheral.
 * @details  : This function enables the specified peripheral connected to the AHB1 bus.
 */
RCC_enumError_t RCC_Enable_AHB1_Peripheral(uint32_t Copy_AHB1PeripheralName);
/*
 * @brief    : Enable AHB2 Peripheral.
 * @param[in]: Copy_AHB2PeripheralName The AHB2 peripheral to be enabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of enabling the AHB2 peripheral.
 * @details  : This function enables the specified peripheral connected to the AHB2 bus.
 */
RCC_enumError_t RCC_Enable_AHB2_Peripheral(uint32_t Copy_AHB2PeripheralName);
/*
 * @brief    Enable APB1 Peripheral.
 * @param[in]: Copy_APB1PeripheralName The APB1 peripheral to be enabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of enabling the APB1 peripheral.
 * @details  : This function enables the specified peripheral connected to the APB1 bus.
 */
RCC_enumError_t RCC_Enable_APB1_Peripheral(uint32_t Copy_APB1PeripheralName);
/*
 * @brief    Enable APB2 Peripheral.
 * @param[in]: Copy_APB2PeripheralName The APB2 peripheral to be enabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of enabling the APB2 peripheral.
 * @details  : This function enables the specified peripheral connected to the APB2 bus.
 */
RCC_enumError_t RCC_Enable_APB2_Peripheral(uint32_t Copy_APB2PeripheralName);
/*
 * @brief    Disable AHB1 Peripheral.
 * @param[in]: Copy_AHB1PeripheralName The AHB1 peripheral to be disabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of disabling the AHB1 peripheral.
 * @details  : This function disables the specified peripheral connected to the AHB1 bus.
 */
RCC_enumError_t RCC_Disable_AHB1_Peripheral(uint32_t Copy_AHB1PeripheralName);
/*
 * @brief    Disable AHB2 Peripheral.
 * @param[in]: Copy_AHB2PeripheralName The AHB2 peripheral to be disabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of disabling the AHB2 peripheral.
 * @details  : This function disables the specified peripheral connected to the AHB2 bus.
 */
RCC_enumError_t RCC_Disable_AHB2_Peripheral(uint32_t Copy_AHB2PeripheralName);
/*
 * @brief    Disable APB1 Peripheral.
 * @param[in]: Copy_APB1PeripheralName The APB1 peripheral to be disabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of disabling the APB1 peripheral.
 * @details  : This function disables the specified peripheral connected to the APB1 bus.
 */
RCC_enumError_t RCC_Disable_APB1_Peripheral(uint32_t Copy_APB1PeripheralName);
/*
 * @brief    Disable APB2 Peripheral.
 * @param[in]: Copy_APB2PeripheralName The APB2 peripheral to be disabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of disabling the APB2 peripheral.
 * @details  : This function disables the specified peripheral connected to the APB2 bus.
 */
RCC_enumError_t RCC_Disable_APB2_Peripheral(uint32_t Copy_APB2PeripheralName);


#endif /* RCC_H_ */
