################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/delay.c \
../src/epd4in2.c \
../src/epdif.c \
../src/init.c \
../src/main.c \
../src/sampleImage.c \
../src/stm32l1xx_it.c \
../src/system_stm32l1xx.c 

OBJS += \
./src/delay.o \
./src/epd4in2.o \
./src/epdif.o \
./src/init.o \
./src/main.o \
./src/sampleImage.o \
./src/stm32l1xx_it.o \
./src/system_stm32l1xx.o 

C_DEPS += \
./src/delay.d \
./src/epd4in2.d \
./src/epdif.d \
./src/init.d \
./src/main.d \
./src/sampleImage.d \
./src/stm32l1xx_it.d \
./src/system_stm32l1xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32L1 -DSTM32L152RCTx -DSTM32L152C_DISCO -DDEBUG -I"D:/programming/STM32 Workbench workspace/SmartPrice/CMSIS" -I"D:/programming/STM32 Workbench workspace/SmartPrice/STM32L1xx_StdPeriph_Driver/inc" -I"D:/programming/STM32 Workbench workspace/SmartPrice/inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


