/*
 ============================================================================
 Name        : GPIO.c
 Author      : Omar Medhat Mohamed
 Description : Source File for the GPIO Driver
 Date        : 16/2/2024
 ============================================================================
 */
/*******************************************************************************
 *                                Includes	                                  *
 *******************************************************************************/
#include "GPIO.h"
/*******************************************************************************
 *                             Definitions                                      *
 *******************************************************************************/
#define GPIO_MODE_MASK      0x00000003
#define GPIO_OUT_TYPE_MASK  0x00000004
#define GPIO_PULL_TYPE_MASK 0x00000018
#define GPIO_SET_1_BIT      0x00000001
#define GPIO_SET_2_BITS     0x00000003
#define GPIO_SET_3_BITS     0x00000007
#define GPIO_OUT_TYPE_SHIFT         2
#define GPIO_PULL_TYPE_SHIFT        3
#define GPIO_GROUP_OF_2_BITS        2
#define GPIO_GROUP_OF_3_BITS        3
/*******************************************************************************
 *                        	  Types Declaration                                 *
 *******************************************************************************/
typedef struct 
{
	uint32_t MODER     ;
	uint32_t OTYPER    ;
    uint32_t OSPEEDR   ;
    uint32_t PUPDR     ;
    uint32_t IDR       ;
    uint32_t ODR       ;
    uint32_t BSRR      ;
    uint32_t LCKR      ;
    uint32_t AFRL      ;
    uint32_t AFRH      ;
}GPIO_PORT_t;


/*******************************************************************************
 *                             Implementation   				                *
 *******************************************************************************/
/*
 * @brief    : Initializes a GPIO pin based on the provided configuration.
 * @param[in]: Loc_GPIOElement - Pointer to a structure containing the GPIO pin configuration.
 * @return   : Error_enumStatus_t - Error status indicating success or failure of the initialization.
 * @details  : This function initializes a GPIO pin according to the provided configuration.
 */
Error_enumStatus_t GPIO_InitPin (GPIO_Config_t *Loc_GPIOElement)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk ;
    /*Assign each digit of provides mask in local variable */
    /* Assign the first 2 bits in Loc_Mode_Value to indicate the mode of operation */  
    uint32_t Loc_Mode_Value     = (Loc_GPIOElement -> Mood) & GPIO_MODE_MASK ;
    /*Assign the next bit in Loc_OutType_Value to indicate the status of the output type if it was 
     Open drain or Push-Pull                                                                     */  
    uint32_t Loc_OutType_Value  = ((Loc_GPIOElement -> Mood) & GPIO_OUT_TYPE_MASK ) >> GPIO_OUT_TYPE_SHIFT ;
    /*Assign the next 2 bits in Loc_PuLL_Value to indicate the status of the PULL type if it was 
     Floating , Pull Up or Pull Down                                                                   */  
    uint32_t Loc_PuLL_Value     = ((Loc_GPIOElement -> Mood) & GPIO_PULL_TYPE_MASK ) >> GPIO_PULL_TYPE_SHIFT ;

    /*Assign the address of MODER according to the provided port base address to Loc_MODER */
    uint32_t Loc_MODER   =  ((GPIO_PORT_t *)(Loc_GPIOElement -> Port)) -> MODER   ;
    /*Assign the address of OTYPER according to the provided port base address to Loc_OTYPER */
    uint32_t Loc_OTYPER  =  ((GPIO_PORT_t *)(Loc_GPIOElement -> Port)) -> OTYPER  ;
    /*Assign the address of OSPEEDR according to the provided port base address to Loc_OSPEEDR 
      This regester decates the speed of the output  */
    uint32_t Loc_OSPEEDR =  ((GPIO_PORT_t *)(Loc_GPIOElement -> Port)) -> OSPEEDR ;
    /*Assign the address of PUPDR according to the provided port base address to Loc_PUPDR */
    uint32_t Loc_PUPDR   =  ((GPIO_PORT_t *)(Loc_GPIOElement -> Port)) -> PUPDR    ;

    /*Validate the input parameters*/
    if (Loc_GPIOElement == NULL )
    {
        Loc_enumReturnStatus = Status_enumNULLPointer ; 
    }
    else if (((Loc_GPIOElement->Pin) > GPIO_PIN15) ||  ((Loc_GPIOElement->Port) > GPIO_PORTH))
    {
        Loc_enumReturnStatus = Status_enumWrongInput ;
    }
    else if ((((Loc_GPIOElement->Speed) > GPIO_VERY_HIGH_SPEED) || (Loc_GPIOElement->Mood) > GPIO_AF_OD_PD))
    {
         Loc_enumReturnStatus = Status_enumWrongInput ; 
    }
    else
    {

        /*Clear bits which will be configured according to the provided configuration from the user*/
        Loc_MODER  &= ~(GPIO_SET_2_BITS << ((Loc_GPIOElement -> Pin)*GPIO_GROUP_OF_2_BITS)) ;
        Loc_OTYPER &= ~(GPIO_SET_1_BIT << ((Loc_GPIOElement -> Pin)))                      ;
        Loc_OSPEEDR&= ~(GPIO_SET_2_BITS << ((Loc_GPIOElement -> Pin)*GPIO_GROUP_OF_2_BITS)) ;
        Loc_PUPDR  &= ~(GPIO_SET_2_BITS << ((Loc_GPIOElement -> Pin)*GPIO_GROUP_OF_2_BITS)) ;

        /*Set bits which will be configured according to the provided configuration from the user
         into loacal variables after calculate it's valuse from previous lines */
        Loc_MODER   |= Loc_Mode_Value << ((Loc_GPIOElement -> Pin)*GPIO_GROUP_OF_2_BITS) ;
        Loc_OTYPER  |= (Loc_OutType_Value << ((Loc_GPIOElement -> Pin)))                      ;
        Loc_OSPEEDR |= ((Loc_GPIOElement -> Speed) << ((Loc_GPIOElement -> Pin)*GPIO_GROUP_OF_2_BITS)) ;
        Loc_PUPDR   |= (Loc_PuLL_Value << ((Loc_GPIOElement -> Pin)*GPIO_GROUP_OF_2_BITS)) ;

        
        /*Assign the new configuration the registers to init the pin with the new configuration*/
        ((GPIO_PORT_t *)(Loc_GPIOElement -> Port)) -> MODER   = Loc_MODER     ;
        ((GPIO_PORT_t *)(Loc_GPIOElement -> Port)) -> OTYPER  =Loc_OTYPER     ;
        ((GPIO_PORT_t *)(Loc_GPIOElement -> Port)) -> OSPEEDR =Loc_OSPEEDR    ;
        ((GPIO_PORT_t *)(Loc_GPIOElement -> Port))-> PUPDR    =Loc_PUPDR      ;

    }
    /*Get the error status*/
    return Loc_enumReturnStatus ; 
}

/*
 * @brief    : Sets the value of a GPIO pin to a specified state.
 * @param[in]: Port - Pointer to the GPIO port (From GPIO_PORTA to GPIO_PORTH).
 * @param[in]: Copy_PinNum - The number of the pin to be set (FROM GPIO_PIN0 TO GPIO_PIN16) .
 * @param[in]: Copy_PinState - The state to set the pin to (GPIO_SET_PIN or GPIO_RESET_PIN).
 * @return   : Error_enumStatus_t - Error status indicating success or failure of setting the pin value.
 * @details  : This function sets the value of a GPIO pin to the specified state (high or low).
 */
Error_enumStatus_t GPIO_Set_PinValue(void *Port , uint32_t Copy_PinNum , uint32_t Copy_PinState )
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk ;    /*Validate the input parameters*/
    if (Port == NULL) 
    {
         Loc_enumReturnStatus = Status_enumNULLPointer ; 
    }
    else if ((Port > GPIO_PORTH) || (Copy_PinNum > GPIO_PIN15))
    {
        Loc_enumReturnStatus = Status_enumWrongInput ; 
    }
    else if ((Copy_PinState != GPIO_SET_PIN ) && (Copy_PinState != GPIO_RESET_PIN ))
    {
        Loc_enumReturnStatus = Status_enumWrongInput ; 
    }
    else
    {
        /*Using BItSET Feture I assign the desired value of the pin in output status 
        if it was set or reset according to the pin port and number*/
        ((GPIO_PORT_t *)Port )-> BSRR = Copy_PinState << Copy_PinNum ;
    }
    return Loc_enumReturnStatus ;  ;
}

/*
 * @brief    : Gets the current value of a GPIO pin.
 * @param[in]: Port - Pointer to the GPIO port (From GPIO_PORTA to GPIO_PORTH).
 * @param[in]: Copy_PinNum - The number of the pin to be set (FROM GPIO_PIN0 TO GPIO_PIN16) .
 * @param[out]: PinStatus - Pointer to a variable to store the pin status (1 for high, 0 for low).
 * @return   : Error_enumStatus_t - Error status indicating success or failure of reading the pin value.
 * @details  : This function reads the current value of a GPIO pin and stores it in PinStatus.
 */
Error_enumStatus_t GPIO_Get_GetPinValue(void *Port , uint32_t Copy_PinNum,  uint8_t * PinStatus)
{
    /* Local Variable to store error status */
    Error_enumStatus_t Loc_enumReturnStatus = Status_enumOk ;    /*Validate the input parameters*/
    if (Port == NULL || PinStatus == NULL)
    {
         Loc_enumReturnStatus = Status_enumNULLPointer ; 
    }
    else if ( (Port > GPIO_PORTH) || (Copy_PinNum > GPIO_PIN15))
    {
        Loc_enumReturnStatus = Status_enumWrongInput ; 
    }
    else
    {
        /*Using BItSET Feture I read the desired value of the pin and assign it in PinStatus pointer */
    	*PinStatus = ( ( (GPIO_PORT_t *)Port )-> IDR ) & (1 << Copy_PinNum );
    }
    return Loc_enumReturnStatus ;
}
