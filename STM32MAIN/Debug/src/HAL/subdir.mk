################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/HAL/CLK_Control.c \
../src/HAL/HSwitch.c \
../src/HAL/LCD.c \
../src/HAL/LED.c \
../src/HAL/Switch.c 

C_DEPS += \
./src/HAL/CLK_Control.d \
./src/HAL/HSwitch.d \
./src/HAL/LCD.d \
./src/HAL/LED.d \
./src/HAL/Switch.d 

OBJS += \
./src/HAL/CLK_Control.o \
./src/HAL/HSwitch.o \
./src/HAL/LCD.o \
./src/HAL/LED.o \
./src/HAL/Switch.o 


# Each subdirectory must supply rules for building sources it contributes
src/HAL/%.o: ../src/HAL/%.c src/HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


