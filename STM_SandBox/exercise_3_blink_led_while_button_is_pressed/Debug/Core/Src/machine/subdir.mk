################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/machine/Machine.cpp 

OBJS += \
./Core/Src/machine/Machine.o 

CPP_DEPS += \
./Core/Src/machine/Machine.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/machine/%.o Core/Src/machine/%.su: ../Core/Src/machine/%.cpp Core/Src/machine/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-machine

clean-Core-2f-Src-2f-machine:
	-$(RM) ./Core/Src/machine/Machine.d ./Core/Src/machine/Machine.o ./Core/Src/machine/Machine.su

.PHONY: clean-Core-2f-Src-2f-machine

