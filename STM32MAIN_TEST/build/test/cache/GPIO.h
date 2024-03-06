#include "Inc/LIB/Error.h"
#include "Inc/LIB/Mask32.h"
#include "Inc/LIB/std_types.h"
typedef struct

{







 u32_t Pin;

 void* Port;

 u32_t Speed;

 u32_t Mood;



}GPIO_Config_t;

Error_enumStatus_t GPIO_InitPin (GPIO_Config_t *Loc_GPIOElement);

Error_enumStatus_t GPIO_Set_PinValue(void *Port , u32_t Copy_PinNum , u32_t Copy_PinState );

Error_enumStatus_t GPIO_Get_GetPinValue(void *Port , u32_t Copy_PinNum, u8_t * PinStatus) ;
