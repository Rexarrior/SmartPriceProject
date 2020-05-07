################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/fonts/font12.c \
../src/fonts/font16.c \
../src/fonts/font20.c \
../src/fonts/font8.c 

OBJS += \
./src/fonts/font12.o \
./src/fonts/font16.o \
./src/fonts/font20.o \
./src/fonts/font8.o 

C_DEPS += \
./src/fonts/font12.d \
./src/fonts/font16.d \
./src/fonts/font20.d \
./src/fonts/font8.d 


# Each subdirectory must supply rules for building sources it contributes
src/fonts/%.o: ../src/fonts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L1 -DSTM32L152RCTx -DSTM32L152C_DISCO -DDEBUG -I"D:/programming/STM32 Workbench workspace/SmartPrice/CMSIS" -I"D:/programming/STM32 Workbench workspace/SmartPrice/STM32L1xx_StdPeriph_Driver/inc" -I"D:/programming/STM32 Workbench workspace/SmartPrice/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


