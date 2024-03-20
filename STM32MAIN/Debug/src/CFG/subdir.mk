################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CFG/HSwitch_Cfg.c \
../src/CFG/LCD_Cfg.c \
../src/CFG/LED_Cfg.c \
../src/CFG/RunnableList_Cfg.c \
../src/CFG/Switch_Cfg.c 

C_DEPS += \
./src/CFG/HSwitch_Cfg.d \
./src/CFG/LCD_Cfg.d \
./src/CFG/LED_Cfg.d \
./src/CFG/RunnableList_Cfg.d \
./src/CFG/Switch_Cfg.d 

OBJS += \
./src/CFG/HSwitch_Cfg.o \
./src/CFG/LCD_Cfg.o \
./src/CFG/LED_Cfg.o \
./src/CFG/RunnableList_Cfg.o \
./src/CFG/Switch_Cfg.o 


# Each subdirectory must supply rules for building sources it contributes
src/CFG/%.o: ../src/CFG/%.c src/CFG/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


