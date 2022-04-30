################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Machine/machine.cpp \
../Core/Src/Machine/time.cpp 

OBJS += \
./Core/Src/Machine/machine.o \
./Core/Src/Machine/time.o 

CPP_DEPS += \
./Core/Src/Machine/machine.d \
./Core/Src/Machine/time.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Machine/%.o Core/Src/Machine/%.su: ../Core/Src/Machine/%.cpp Core/Src/Machine/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Machine

clean-Core-2f-Src-2f-Machine:
	-$(RM) ./Core/Src/Machine/machine.d ./Core/Src/Machine/machine.o ./Core/Src/Machine/machine.su ./Core/Src/Machine/time.d ./Core/Src/Machine/time.o ./Core/Src/Machine/time.su

.PHONY: clean-Core-2f-Src-2f-Machine

