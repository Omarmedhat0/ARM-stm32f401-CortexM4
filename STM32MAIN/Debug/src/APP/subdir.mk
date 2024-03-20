################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/APP/LCD_test.c \
../src/APP/Nvic_test.c \
../src/APP/Sched_App1.c \
../src/APP/Sched_App2.c \
../src/APP/Sched_App3_SW_Test.c \
../src/APP/Sched_Test.c \
../src/APP/SysTick_Test.c \
../src/APP/TrafficLight.c \
../src/APP/TrafficLight_test.c 

C_DEPS += \
./src/APP/LCD_test.d \
./src/APP/Nvic_test.d \
./src/APP/Sched_App1.d \
./src/APP/Sched_App2.d \
./src/APP/Sched_App3_SW_Test.d \
./src/APP/Sched_Test.d \
./src/APP/SysTick_Test.d \
./src/APP/TrafficLight.d \
./src/APP/TrafficLight_test.d 

OBJS += \
./src/APP/LCD_test.o \
./src/APP/Nvic_test.o \
./src/APP/Sched_App1.o \
./src/APP/Sched_App2.o \
./src/APP/Sched_App3_SW_Test.o \
./src/APP/Sched_Test.o \
./src/APP/SysTick_Test.o \
./src/APP/TrafficLight.o \
./src/APP/TrafficLight_test.o 


# Each subdirectory must supply rules for building sources it contributes
src/APP/%.o: ../src/APP/%.c src/APP/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=25000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


