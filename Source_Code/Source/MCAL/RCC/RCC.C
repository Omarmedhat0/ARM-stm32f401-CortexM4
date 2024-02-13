/*
 ============================================================================
 Name        : RCC.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the RCC Driver
 Date        : 10/2/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "MCAL/RCC.h"
/*******************************************************************************
 *                             Definitions                                      *
 *******************************************************************************/
#define RCC_Base_ADDRESS 0x40023800 

#define SysClk_HSI_Ready_MASK	0x00000000
#define SysClk_HSE_Ready_MASK	0x00000004
#define SysClk_PLL_Ready_MASK	0x00000008

#define READY_HSI	0x00000002
#define READY_HSE	0x00020000
#define READY_PLL 	0x02000000

#define	SysClk_CLR_MASK		0x1111111C
#define	SysClk_READ_MASK 	0x0000000C

#define PLL_Q_SHIFTING		24
#define PLL_P_SHIFTING		16
#define PLL_N_SHIFTING		6

#define PLLQ_BOUNDARY1		2
#define PLLQ_BOUNDARY2		15
#define PLLP_BOUNDARY1		2
#define PLLP_BOUNDARY2		8
#define PLLP_WRONGWAUE1		3
#define PLLP_WRONGWAUE2		5
#define PLLP_WRONGWAUE3		7
#define PLLN_BOUNDARY1		192
#define PLLN_BOUNDARY2		432
#define PLLM_BOUNDARY1		2
#define PLLM_BOUNDARY2		63

#define PPRE2_APBH_SHIFTING	13
#define PPRE1_APBL_SHIFTING	10
#define HPRE_AHB_SHIFTING	4

#define PPRE2_APBH_CLR_MASK	0xFFFF1FFF
#define PPRE1_APBL_CLR_MASK	0xFFFFE3FF
#define HPRE_AHB_CLR_MASK	0xFFFFFF0F
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
typedef struct 
{
	uint32_t RCC_CR 		;
	uint32_t RCC_PLLCFGR 	;
	uint32_t RCC_CFGR 		;
	uint32_t RCC_CIR  		;
	uint32_t RCC_AHB1RSTR  	;
	uint32_t RCC_AHB2RSTR  	;
	uint32_t Reserved  		;
	uint32_t Reserved2 		;
	uint32_t RCC_APB1RSTR  	;
	uint32_t RCC_APB2RSTR  	;
	uint32_t Reserved3  	;
	uint32_t Reserved4 		;
	uint32_t RCC_AHB1ENR  	;
	uint32_t RCC_AHB2ENR  	;
	uint32_t Reserved5 		;
	uint32_t Reserved6 		;
	uint32_t RCC_APB1ENR  	;
	uint32_t RCC_APB2ENR  	;
	uint32_t Reserved7  	;
	uint32_t Reserved8  	;
	uint32_t RCC_AHB1LPENR  ;
	uint32_t RCC_AHB2LPENR  ;
	uint32_t Reserved9  	;
	uint32_t Reserved10  	;
	uint32_t RCC_APB1LPENR  ;
	uint32_t RCC_APB2LPENR  ;
	uint32_t Reserved11  	;
	uint32_t Reserved12  	;
	uint32_t RCC_BDCR  		;
	uint32_t RCC_CSR  	 	;
	uint32_t Reserved13  	;
	uint32_t Reserved14  	;
	uint32_t RCC_SSCGR  	;
	uint32_t RCC_PLLI2SCFGR ;
}RCC_PERI_t;

/*******************************************************************************
 *                              Variables		                                *
 *******************************************************************************/
volatile RCC_PERI_t * const RCC = (volatile RCC_PERI_t *) RCC_Base_ADDRESS;
/*******************************************************************************
 *                         Static Function Protoypes		                    *
 *******************************************************************************/
static RCC_enumError_t RCC_READ_ClockReadyState(uint32_t Copy_Clock);
static RCC_enumError_t RCC_READ_SYSClockState(uint32_t Copy_Clock);
/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*
 * @brief    : Set Clock ON.
 * @param[in]: Copy_Clock The clock source to be set on. It can be CLOCK_HSI, CLOCK_HSE, or CLOCK_PLL.
 * @return   : RCC_enumError_t Error status indicating the success or failure of setting the clock on.
 * @details  : This function turns on the specified clock source. 
 			   It enables the clock according to the provided clock source.
 */
RCC_enumError_t RCC_SET_Clock_ON(uint32_t Copy_Clock)
{
    /* Local Variable to store error status*/
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ;
    /* Set the specified clock in the RCC_CR register */
    RCC->RCC_CR |= Copy_Clock;
    /* Read the status of the specified clock in the RCC_CR register */
    uint32_t Loc_u32ReadStatus = (RCC->RCC_CR) & Copy_Clock ;
    /* Check if the specified clock is turned on */
    if (Loc_u32ReadStatus != FALSE )
    {
        Loc_enumReturnRCCErrorStatus = RCC_enumOk ;
    }
    else
    {
        /* Return RCC_enumONFailed if the clock is not turned on */
        Loc_enumReturnRCCErrorStatus = RCC_enumONFailed ;
    }

    /* Return the status of the clock operation */
    return Loc_enumReturnRCCErrorStatus ;
}

/*
 * @brief    : Set Clock OFF.
 * @param[in]: Copy_Clock The clock source to be turned off. It can be CLOCK_HSI, CLOCK_HSE, or CLOCK_PLL.
 * @return   : RCC_enumError_t Error status indicating the success or failure of turning the clock off.
 * @details  : This function turns off the specified clock source. 
 			   It disables the clock according to the provided clock source.
 */
RCC_enumError_t RCC_SET_Clock_OFF (uint32_t Copy_Clock)
{
    /* Local Variable to store error status*/
	RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ;
    /* Read the current state of the system clock */
    Loc_enumReturnRCCErrorStatus = RCC_READ_SYSClockState(Copy_Clock);
    /* Check if the system clock state is valid */
    if (Loc_enumReturnRCCErrorStatus == RCC_enumOk)
    {
        /* Turn off the specified clock in the RCC_CR register */
        RCC->RCC_CR &= ~(Copy_Clock);
    }
    else
    {
        /* Return RCC_enumOFFFailed if the clock cannot be turned off */
        Loc_enumReturnRCCErrorStatus = RCC_enumOFFFailed;
    }

    /* Return the status of the clock operation */
    return Loc_enumReturnRCCErrorStatus ;
}

/*
 * @brief    : Read if the Clock is configur as system clock or not
 * @param[in]:  Copy_Clock The clock source to be checkd. It can be CLOCK_HSI, CLOCK_HSE, or CLOCK_PLL.
 * @return   : RCC_enumError_t Error status indicating the success or failure of selecting the system clock.
 */
static RCC_enumError_t RCC_READ_SYSClockState(uint32_t Copy_Clock)
{
	/* Local Variable to store error status*/
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ;
    /* Read the current status of the system clock from the RCC_CFGR register */
    uint32_t Loc_u32ReadSYSClockStatus = ((RCC->RCC_CFGR) & (SysClk_READ_MASK)) >> 2 ; 

    /* Check the status of the specified clock */
    switch (Copy_Clock)
    {
        case CLOCK_HSI :
            /* Check if HSI is selected as the system clock */
            if (Loc_u32ReadSYSClockStatus == SysClk_HSI_MASK)
            {
                Loc_enumReturnRCCErrorStatus = RCC_enumONFailed;
            }
            else
            {
                Loc_enumReturnRCCErrorStatus = RCC_enumOk ;
            }
            break ;
        case CLOCK_HSE :
            /* Check if HSE is selected as the system clock */
            if (Loc_u32ReadSYSClockStatus == SysClk_HSE_MASK)
            {
                Loc_enumReturnRCCErrorStatus = RCC_enumONFailed ;
            }
            else
            {
                Loc_enumReturnRCCErrorStatus = RCC_enumOk ;
            }
            break ;
        case CLOCK_PLL :
            /* Check if PLL is selected as the system clock */
            if (Loc_u32ReadSYSClockStatus == SysClk_PLL_MASK)
            {
                Loc_enumReturnRCCErrorStatus = RCC_enumONFailed ;
            }
            else
            {
                Loc_enumReturnRCCErrorStatus = RCC_enumOk ;
            }
            break ;
        default:
            /* Invalid input clock type */
            Loc_enumReturnRCCErrorStatus = RCC_enumWrongInput ;
            break ;
    }

    /* Return the status of the clock state */
    return Loc_enumReturnRCCErrorStatus ;
}

/*
 * @brief    : Read if the Clock is Ready or not
 * @param[in]:  Copy_Clock The clock source to be checkd. It can be CLOCK_HSI, CLOCK_HSE, or CLOCK_PLL.
 * @return   : RCC_enumError_t Error status indicating the success or failure of selecting the system clock.
 */
static RCC_enumError_t RCC_READ_ClockReadyState(uint32_t Copy_Clock)
{
    /* Initialize a variable to store the error status. */
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ;

    /* Initialize a timer for timeout */
    uint32_t timer = 1000 ; /* Set a timeout value for the clock readiness check. */

    /* Check the ready state of the specified clock */
    switch (Copy_Clock) /* Start a switch statement based on the clock type. */
    {
        case CLOCK_HSI:
            /* Check if HSI is ready */
            Copy_Clock = READY_HSI; /* Set the value to check if HSI is ready. */
            while (timer && !(RCC->RCC_CR & Copy_Clock)) /* Loop until HSI is ready or timeout occurs. */
            {
                timer-- ; /* Decrement the timer. */
            }
            if (!(RCC->RCC_CR & Copy_Clock)) /* If HSI is not ready after the loop, */
            {
                Loc_enumReturnRCCErrorStatus = RCC_enumClockNotReady ; /* Set the error status accordingly. */
            }
            else
            {} /* No action if HSI is ready. */
            break;
        case CLOCK_HSE:
            /* Check if HSE is ready */
            Copy_Clock = READY_HSE; /* Set the value to check if HSE is ready. */
            while (timer && !(RCC->RCC_CR & Copy_Clock)) /* Loop until HSE is ready or timeout occurs. */
            {
                timer-- ; /* Decrement the timer. */
            }
            if (!(RCC->RCC_CR & Copy_Clock)) /* If HSE is not ready after the loop, */
            {
                Loc_enumReturnRCCErrorStatus = RCC_enumClockNotReady ; /* Set the error status accordingly. */
            }
            else
            {} /* No action if HSE is ready. */
            break;
        case CLOCK_PLL:
            /* Check if PLL is ready */
            Copy_Clock = READY_PLL; /* Set the value to check if PLL is ready. */
            while (timer && !(RCC->RCC_CR & Copy_Clock)) /* Loop until PLL is ready or timeout occurs. */
            {
                timer-- ; /* Decrement the timer. */
            }
            if (!(RCC->RCC_CR & Copy_Clock)) /* If PLL is not ready after the loop, */
            {
                Loc_enumReturnRCCErrorStatus = RCC_enumClockNotReady ; /* Set the error status accordingly. */
            }
            else
            {} /* No action if PLL is ready. */
            break;
        default:
            /* Invalid input clock type */
            Loc_enumReturnRCCErrorStatus = RCC_enumWrongInput ; /* Set the error status since the input clock type is invalid. */
            break;
    }

    /* Return the status of the clock readiness */
    return Loc_enumReturnRCCErrorStatus ; /* Return the error status indicating the readiness of the clock. */
}

/*
 * @brief    : Select System Clock.
 * @param[in]: Copy_SysClk The system clock source to be selected. It can be SysClk_HSI_MASK, SysClk_HSE_MASK, or SysClk_PLL_MASK.
 * @return   : RCC_enumError_t Error status indicating the success or failure of selecting the system clock.
 * @details  : This function selects the system clock source among the available options: HSI, HSE, or PLL.
 */
RCC_enumError_t RCC_Select_Sysclk(uint32_t Copy_SysClk )
{
    /* Initialize a variable to store the error status. */
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ;

    /* Initialize local variables */
    uint32_t Temp = 0 ; /* Temporary variable to store the clock source */
    uint32_t Reg = RCC->RCC_CFGR ; /* Register to hold system clock configuration */

    /* Determine the clock source based on the input */
    switch (Copy_SysClk) /* Start a switch statement based on the system clock source. */
    {
        case SysClk_HSE_MASK:
            Temp = CLOCK_HSE; /* Set the temporary variable to HSE if selected. */
            break;
        case SysClk_HSI_MASK:
            Temp = CLOCK_HSI; /* Set the temporary variable to HSI if selected. */
            break;
        case SysClk_PLL_MASK:
            Temp = CLOCK_PLL; /* Set the temporary variable to PLL if selected. */
            break;
        default:
            /* Invalid system clock source */
            Loc_enumReturnRCCErrorStatus = RCC_enumONFailed ; /* Set the error status since the input system clock source is invalid. */
            break;
    }

    /* Check if the selected clock source is ready */
    Loc_enumReturnRCCErrorStatus = RCC_READ_ClockReadyState(Temp); /* Call a function to check if the selected clock source is ready. */
    if (Loc_enumReturnRCCErrorStatus == RCC_enumOk) /* If the selected clock source is ready, */
    {
        /* Configure the system clock source */
        Reg &= SysClk_CLR_MASK ; /* Clear the bits related to system clock configuration. */
        Reg |= Copy_SysClk ; /* Set the bits for the selected system clock source. */
        RCC->RCC_CFGR = Reg; /* Update the RCC_CFGR register with the new system clock configuration. */
    }
    else
    {
        Loc_enumReturnRCCErrorStatus = RCC_enumClockNotReady; /* Set the error status since the selected clock source is not ready. */
    }

    /* Return the status of the system clock source selection */
    return Loc_enumReturnRCCErrorStatus ; /* Return the error status indicating the success or failure of system clock source selection. */
}

/*
 * @brief    : Configure PLL Source.
 * @param[in]: Copy_PLLSrc The PLL source to be configured. It can be PLL_SRC_HSI or PLL_SRC_HSE.
 * @return   : RCC_enumError_t Error status indicating the success or failure of configuring PLL source.
 * @details  : This function configures the PLL source to be either HSI or HSE.
 */
RCC_enumError_t RCC_Config_PLLSrc(uint32_t Copy_PLLSrc)
{
    /* Initialize a variable to store the error status. */
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ;

    /* Start a switch statement based on the PLL clock source. */
    switch (Copy_PLLSrc)
    {
        case CLOCK_HSI : /* If the PLL clock source is HSI */
            RCC->RCC_PLLCFGR &= PLL_SRC_HSI ; /* Configure PLL clock source as HSI. */
            break ;
        case CLOCK_HSE : /* If the PLL clock source is HSE */
            RCC->RCC_PLLCFGR |= PLL_SRC_HSE ; /* Configure PLL clock source as HSE. */
            break ;
        default: /* If the PLL clock source is invalid */
            Loc_enumReturnRCCErrorStatus = RCC_enumWrongInput ; /* Set the error status since the input PLL clock source is invalid. */
            break ;
    }

    /* Return the status of the PLL clock source configuration. */
    return Loc_enumReturnRCCErrorStatus ; /* Return the error status indicating the success or failure of PLL clock source configuration. */
}

/*
 * @brief    : Configure PLL Parameters.
 * @param[in]: PLLM, PLLN, PLLP, PLLQ The parameters to configure PLL.
 * @return   : RCC_enumError_t Error status indicating the success or failure of configuring PLL parameters.
 * @details  : This function configures the parameters (M, N, P, Q) for the PLL.
 * @note     : Ranges of Paramters 2<=PLLM<=63 ,192<=PLLN<=432 , 2<=PLLQ<=15 , PLLP = 2,4,6,8
 */
RCC_enumError_t RCC_Config_PLLParamters(uint32_t PLLM ,uint32_t PLLN , uint32_t PLLP ,uint32_t PLLQ)
{
	/* Initialize a variable to store the error status. */
	RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ;
	/* Initialize a variable to store the temporary value for PLL configuration. */
	uint32_t Loc_Temp = 0;
	/* Validate the PLL parameters */
	if ( PLLQ < PLLQ_BOUNDARY1 || PLLQ > PLLQ_BOUNDARY2)
	{
		Loc_enumReturnRCCErrorStatus = RCC_enumWrongInput ;
	}
	else if (PLLP <PLLP_BOUNDARY1 || PLLP > PLLP_BOUNDARY2 || PLLP ==PLLP_WRONGWAUE1 || PLLP == PLLP_WRONGWAUE2 || PLLP == PLLP_WRONGWAUE3)
	{
		Loc_enumReturnRCCErrorStatus = RCC_enumWrongInput ;
	}
	else if (PLLN<PLLN_BOUNDARY1 || PLLN>PLLN_BOUNDARY2)
	{
		Loc_enumReturnRCCErrorStatus = RCC_enumWrongInput ;
	}
	else if(PLLM<PLLM_BOUNDARY1 || PLLM>PLLM_BOUNDARY2 )
	{
		Loc_enumReturnRCCErrorStatus = RCC_enumWrongInput ;
	}
	else
	{
        /* Convert PLLP value */
		switch (PLLP)
		{
		case 2 :
			PLLP = 0x0;
			break ;
		case 4 :
			PLLP = 0x1;
			break ;
		case 6 :
			PLLP = 0x2;
			break ;
		case 8 :
			PLLP = 0x3;
			break ;
		default :
			break ;
		}
        /* Calculate PLL configuration value */
		Loc_Temp  = PLLQ << PLL_Q_SHIFTING ; 
		Loc_Temp |= PLLP << PLL_P_SHIFTING ; 
		Loc_Temp |= PLLN << PLL_N_SHIFTING ;
		Loc_Temp |= PLLM ;
        /* Configure the PLL with the calculated value */
		RCC->RCC_PLLCFGR = Loc_Temp;
	}
    /* Return the status of the PLL parameter configuration. */
	return Loc_enumReturnRCCErrorStatus ; 
}

/*
 * @brief    : Configure System Prescaler.
 * @param[in]: Copy_PreScalerID The prescaler type to be configured: APB_HIGH_PRE, APB_LOW_PRE, or AHB_PRE.
 * @param[in]: CopyPreScalerValue The value to configure the prescaler.
 * @return   : RCC_enumError_t Error status indicating the success or failure of configuring system prescaler.
 * @details  : This function configures the prescaler for the specified bus (AHB1, AHB2, APB1, APB2).
 */
RCC_enumError_t RCC_Config_SystemPrescaler (RCC_PRESCALER_t Copy_PreScalerID,uint32_t  CopyPreScalerValue)
{
    /* Initialize a variable to store the error status. */
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ; 

    /* Initialize a variable to store the temporary value for system prescaler configuration. */
    uint32_t Loc_Temp = RCC->RCC_CFGR ;

    /* Start a switch statement based on the prescaler ID. */
    switch (Copy_PreScalerID)
    {
        case APB_HIGH_PRE : /* If the prescaler is for APB high-speed peripheral */
            Loc_Temp &= PPRE2_APBH_CLR_MASK ; /* Clear the corresponding bits for APB high-speed peripheral prescaler. */
            Loc_Temp |= (CopyPreScalerValue << PPRE2_APBH_SHIFTING) ; /* Configure the prescaler value for APB high-speed peripheral. */
            break ; 
        case APB_LOW_PRE : /* If the prescaler is for APB low-speed peripheral */
            Loc_Temp &= PPRE1_APBL_CLR_MASK ; /* Clear the corresponding bits for APB low-speed peripheral prescaler. */
            Loc_Temp |= (CopyPreScalerValue << PPRE1_APBL_SHIFTING) ; /* Configure the prescaler value for APB low-speed peripheral. */
            break ; 
        case AHB_PRE : /* If the prescaler is for AHB (Advanced High-Performance Bus) */
            Loc_Temp &= HPRE_AHB_CLR_MASK ; /* Clear the corresponding bits for AHB prescaler. */
            Loc_Temp |= (CopyPreScalerValue << HPRE_AHB_SHIFTING) ; /* Configure the prescaler value for AHB. */
            break ; 
        default :
            Loc_enumReturnRCCErrorStatus = RCC_enumWrongInput ; /* Set the error status since the input prescaler ID is invalid. */
            break ;
    }

    /* Update the RCC_CFGR register with the configured system prescaler value. */
    RCC->RCC_CFGR = Loc_Temp ; 

    /* Return the status of the system prescaler configuration. */
    return Loc_enumReturnRCCErrorStatus ; /* Return the error status indicating the success or failure of system prescaler configuration. */
}

/*
 * @brief    : Enable AHB1 Peripheral.
 * @param[in]: Copy_AHB1PeripheralName The AHB1 peripheral to be enabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of enabling the AHB1 peripheral.
 * @details  : This function enables the specified peripheral connected to the AHB1 bus.
 */
RCC_enumError_t RCC_Enable_AHB1_Peripheral(uint32_t Copy_AHB1PeripheralName)
{
    /* Initialize a variable to store the error status. */
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ; 

    /* Read the current value of RCC_AHB1ENR register. */
    uint32_t Copy_AHB1Peripheral = RCC->RCC_AHB1ENR ;

    /* Clear the bits corresponding to the AHB1 peripheral to be enabled. */
    Copy_AHB1Peripheral &= ~(Copy_AHB1PeripheralName);

    /* Set the bits corresponding to the AHB1 peripheral to be enabled. */
    Copy_AHB1Peripheral |= Copy_AHB1PeripheralName ;

    /* Write the updated value back to RCC_AHB1ENR register to enable the AHB1 peripheral. */
    RCC->RCC_AHB1ENR = Copy_AHB1Peripheral;

    /* Return the status indicating the success of enabling the AHB1 peripheral. */
    return Loc_enumReturnRCCErrorStatus ; 
}

/*
 * @brief    : Enable AHB2 Peripheral.
 * @param[in]: Copy_AHB2PeripheralName The AHB2 peripheral to be enabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of enabling the AHB2 peripheral.
 * @details  : This function enables the specified peripheral connected to the AHB2 bus.
 */
RCC_enumError_t RCC_Enable_AHB2_Peripheral(uint32_t Copy_AHB2PeripheralName)
{
    /* Initialize a variable to store the error status. */
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ; 

    /* Read the current value of RCC_AHB2ENR register. */
    uint32_t Copy_AHB2Peripheral = RCC->RCC_AHB2ENR ;

    /* Clear the bits corresponding to the AHB2 peripheral to be enabled. */
    Copy_AHB2Peripheral &= ~(Copy_AHB2PeripheralName);

    /* Set the bits corresponding to the AHB2 peripheral to be enabled. */
    Copy_AHB2Peripheral |= Copy_AHB2PeripheralName ;

    /* Write the updated value back to RCC_AHB2ENR register to enable the AHB2 peripheral. */
    RCC->RCC_AHB2ENR = Copy_AHB2Peripheral;

    /* Return the status indicating the success of enabling the AHB2 peripheral. */
    return Loc_enumReturnRCCErrorStatus ; 
}


/*
 * @brief    Enable APB1 Peripheral.
 * @param[in]: Copy_APB1PeripheralName The APB1 peripheral to be enabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of enabling the APB1 peripheral.
 * @details  : This function enables the specified peripheral connected to the APB1 bus.
 */
RCC_enumError_t RCC_Enable_APB1_Peripheral(uint32_t Copy_APB1PeripheralName)
{
    /* Initialize a variable to store the error status. */
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ; 

    /* Read the current value of RCC_APB1ENR register. */
    uint32_t Copy_APB1Peripheral = RCC->RCC_APB1ENR;

    /* Clear the bits corresponding to the APB1 peripheral to be enabled. */
    Copy_APB1Peripheral &= ~(Copy_APB1PeripheralName);

    /* Set the bits corresponding to the APB1 peripheral to be enabled. */
    Copy_APB1Peripheral |= Copy_APB1PeripheralName ;

    /* Write the updated value back to RCC_APB1ENR register to enable the APB1 peripheral. */
    RCC->RCC_APB1ENR = Copy_APB1Peripheral;

    /* Return the status indicating the success of enabling the APB1 peripheral. */
    return Loc_enumReturnRCCErrorStatus ; 
}

/*
 * @brief    Enable APB2 Peripheral.
 * @param[in]: Copy_APB2PeripheralName The APB2 peripheral to be enabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of enabling the APB2 peripheral.
 * @details  : This function enables the specified peripheral connected to the APB2 bus.
 */
RCC_enumError_t RCC_Enable_APB2_Peripheral(uint32_t Copy_APB2PeripheralName)
{
    /* Initialize a variable to store the error status. */
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ; 

    /* Read the current value of RCC_APB2ENR register. */
    uint32_t Copy_APB2Peripheral = RCC->RCC_APB2ENR ;

    /* Clear the bits corresponding to the APB2 peripheral to be enabled. */
    Copy_APB2Peripheral &= ~(Copy_APB2PeripheralName);

    /* Set the bits corresponding to the APB2 peripheral to be enabled. */
    Copy_APB2Peripheral |= Copy_APB2PeripheralName ;

    /* Write the updated value back to RCC_APB2ENR register to enable the APB2 peripheral. */
    RCC->RCC_APB2ENR = Copy_APB2Peripheral;

    /* Return the status indicating the success of enabling the APB2 peripheral. */
    return Loc_enumReturnRCCErrorStatus ; 
}

/*
 * @brief    Disable AHB1 Peripheral.
 * @param[in]: Copy_AHB1PeripheralName The AHB1 peripheral to be disabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of disabling the AHB1 peripheral.
 * @details  : This function disables the specified peripheral connected to the AHB1 bus.
 */
RCC_enumError_t RCC_Disable_AHB1_Peripheral(uint32_t Copy_AHB1PeripheralName)
{
    /* Initialize a variable to store the error status. */
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ; 

    /* Read the current value of RCC_AHB1ENR register. */
    uint32_t Copy_AHB1Peripheral = RCC->RCC_AHB1ENR ;

    /* Clear the bits corresponding to the AHB1 peripheral to be disabled. */
    Copy_AHB1Peripheral &= ~(Copy_AHB1PeripheralName);

    /* Write the updated value back to RCC_AHB1ENR register to disable the AHB1 peripheral. */
    RCC->RCC_AHB1ENR = Copy_AHB1Peripheral;

    /* Return the status indicating the success of disabling the AHB1 peripheral. */
    return Loc_enumReturnRCCErrorStatus ; 
}

/*
 * @brief    Disable AHB2 Peripheral.
 * @param[in]: Copy_AHB2PeripheralName The AHB2 peripheral to be disabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of disabling the AHB2 peripheral.
 * @details  : This function disables the specified peripheral connected to the AHB2 bus.
 */
RCC_enumError_t RCC_Disable_AHB2_Peripheral(uint32_t Copy_AHB2PeripheralName)
{
    /* Initialize a variable to store the error status. */
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ; 

    /* Read the current value of RCC_AHB2ENR register. */
    uint32_t Copy_AHB2Peripheral = RCC->RCC_AHB2ENR ;

    /* Clear the bits corresponding to the AHB2 peripheral to be disabled. */
    Copy_AHB2Peripheral &= ~(Copy_AHB2PeripheralName);

    /* Write the updated value back to RCC_AHB2ENR register to disable the AHB2 peripheral. */
    RCC->RCC_AHB2ENR = Copy_AHB2Peripheral;

    /* Return the status indicating the success of disabling the AHB2 peripheral. */
    return Loc_enumReturnRCCErrorStatus ; 
}

/*
 * @brief    Disable APB1 Peripheral.
 * @param[in]: Copy_APB1PeripheralName The APB1 peripheral to be disabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of disabling the APB1 peripheral.
 * @details  : This function disables the specified peripheral connected to the APB1 bus.
 */
RCC_enumError_t RCC_Disable_APB1_Peripheral(uint32_t Copy_APB1PeripheralName)
{
    /* Initialize a variable to store the error status. */
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ; 

    /* Read the current value of RCC_APB1ENR register. */
    uint32_t Copy_APB1Peripheral = RCC->RCC_APB1ENR ;

    /* Clear the bits corresponding to the APB1 peripheral to be disabled. */
    Copy_APB1Peripheral &= ~(Copy_APB1PeripheralName);

    /* Write the updated value back to RCC_APB1ENR register to disable the APB1 peripheral. */
    RCC->RCC_APB1ENR = Copy_APB1Peripheral;

    /* Return the status indicating the success of disabling the APB1 peripheral. */
    return Loc_enumReturnRCCErrorStatus ; 
}

/*
 * @brief    Disable APB2 Peripheral.
 * @param[in]: Copy_APB2PeripheralName The APB2 peripheral to be disabled.
 * @return   : RCC_enumError_t Error status indicating the success or failure of disabling the APB2 peripheral.
 * @details  : This function disables the specified peripheral connected to the APB2 bus.
 */
RCC_enumError_t RCC_Disable_APB2_Peripheral(uint32_t Copy_APB2PeripheralName)
{
    /* Initialize a variable to store the error status. */
    RCC_enumError_t Loc_enumReturnRCCErrorStatus = RCC_enumOk ; 

    /* Read the current value of RCC_APB2ENR register. */
    uint32_t Copy_APB2Peripheral = RCC->RCC_APB2ENR;

    /* Clear the bits corresponding to the APB2 peripheral to be disabled. */
    Copy_APB2Peripheral &= ~(Copy_APB2PeripheralName);

    /* Write the updated value back to RCC_APB2ENR register to disable the APB2 peripheral. */
    RCC->RCC_APB2ENR = Copy_APB2Peripheral;

    /* Return the status indicating the success of disabling the APB2 peripheral. */
    return Loc_enumReturnRCCErrorStatus ; 
}
