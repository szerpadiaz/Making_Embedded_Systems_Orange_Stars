################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Application/button.cpp \
../Core/Src/Application/led.cpp \
../Core/Src/Application/main.cpp 

OBJS += \
./Core/Src/Application/button.o \
./Core/Src/Application/led.o \
./Core/Src/Application/main.o 

CPP_DEPS += \
./Core/Src/Application/button.d \
./Core/Src/Application/led.d \
./Core/Src/Application/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Application/%.o Core/Src/Application/%.su: ../Core/Src/Application/%.cpp Core/Src/Application/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Application

clean-Core-2f-Src-2f-Application:
	-$(RM) ./Core/Src/Application/button.d ./Core/Src/Application/button.o ./Core/Src/Application/button.su ./Core/Src/Application/led.d ./Core/Src/Application/led.o ./Core/Src/Application/led.su ./Core/Src/Application/main.d ./Core/Src/Application/main.o ./Core/Src/Application/main.su

.PHONY: clean-Core-2f-Src-2f-Application

