################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Application/console.c \
../Core/Src/Application/consoleIo.c 

CPP_SRCS += \
../Core/Src/Application/User_control.cpp \
../Core/Src/Application/button.cpp \
../Core/Src/Application/consoleCommands.cpp \
../Core/Src/Application/gui.cpp \
../Core/Src/Application/handwriting_recognizer.cpp \
../Core/Src/Application/led.cpp \
../Core/Src/Application/main.cpp 

C_DEPS += \
./Core/Src/Application/console.d \
./Core/Src/Application/consoleIo.d 

OBJS += \
./Core/Src/Application/User_control.o \
./Core/Src/Application/button.o \
./Core/Src/Application/console.o \
./Core/Src/Application/consoleCommands.o \
./Core/Src/Application/consoleIo.o \
./Core/Src/Application/gui.o \
./Core/Src/Application/handwriting_recognizer.o \
./Core/Src/Application/led.o \
./Core/Src/Application/main.o 

CPP_DEPS += \
./Core/Src/Application/User_control.d \
./Core/Src/Application/button.d \
./Core/Src/Application/consoleCommands.d \
./Core/Src/Application/gui.d \
./Core/Src/Application/handwriting_recognizer.d \
./Core/Src/Application/led.d \
./Core/Src/Application/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Application/%.o Core/Src/Application/%.su: ../Core/Src/Application/%.cpp Core/Src/Application/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/STM32F429I-Discovery -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-cnn_MachineLearning/edgeimpulse/ -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-dnn_MachineLearning/edgeimpulse/ -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-dnn_MachineLearning/edgeimpulse/ -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/ -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/Application/%.o Core/Src/Application/%.su: ../Core/Src/Application/%.c Core/Src/Application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/STM32F429I-Discovery -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-cnn_MachineLearning/edgeimpulse/ -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-dnn_MachineLearning/edgeimpulse/ -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-dnn_MachineLearning/edgeimpulse/ -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Application

clean-Core-2f-Src-2f-Application:
	-$(RM) ./Core/Src/Application/User_control.d ./Core/Src/Application/User_control.o ./Core/Src/Application/User_control.su ./Core/Src/Application/button.d ./Core/Src/Application/button.o ./Core/Src/Application/button.su ./Core/Src/Application/console.d ./Core/Src/Application/console.o ./Core/Src/Application/console.su ./Core/Src/Application/consoleCommands.d ./Core/Src/Application/consoleCommands.o ./Core/Src/Application/consoleCommands.su ./Core/Src/Application/consoleIo.d ./Core/Src/Application/consoleIo.o ./Core/Src/Application/consoleIo.su ./Core/Src/Application/gui.d ./Core/Src/Application/gui.o ./Core/Src/Application/gui.su ./Core/Src/Application/handwriting_recognizer.d ./Core/Src/Application/handwriting_recognizer.o ./Core/Src/Application/handwriting_recognizer.su ./Core/Src/Application/led.d ./Core/Src/Application/led.o ./Core/Src/Application/led.su ./Core/Src/Application/main.d ./Core/Src/Application/main.o ./Core/Src/Application/main.su

.PHONY: clean-Core-2f-Src-2f-Application

