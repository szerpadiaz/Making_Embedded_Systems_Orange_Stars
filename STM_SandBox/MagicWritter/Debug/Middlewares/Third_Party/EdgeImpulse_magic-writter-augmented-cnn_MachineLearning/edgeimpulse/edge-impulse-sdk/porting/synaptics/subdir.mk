################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/debug_log.cpp \
../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/ei_classifier_porting.cpp 

OBJS += \
./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/debug_log.o \
./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/ei_classifier_porting.o 

CPP_DEPS += \
./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/debug_log.d \
./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/ei_classifier_porting.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/%.o Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/%.su: ../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/%.cpp Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++17 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/STM32F429I-Discovery -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-cnn_MachineLearning/edgeimpulse/ -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-dnn_MachineLearning/edgeimpulse/ -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-dnn_MachineLearning/edgeimpulse/ -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/ -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-EdgeImpulse_magic-2d-writter-2d-augmented-2d-cnn_MachineLearning-2f-edgeimpulse-2f-edge-2d-impulse-2d-sdk-2f-porting-2f-synaptics

clean-Middlewares-2f-Third_Party-2f-EdgeImpulse_magic-2d-writter-2d-augmented-2d-cnn_MachineLearning-2f-edgeimpulse-2f-edge-2d-impulse-2d-sdk-2f-porting-2f-synaptics:
	-$(RM) ./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/debug_log.d ./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/debug_log.o ./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/debug_log.su ./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/ei_classifier_porting.d ./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/ei_classifier_porting.o ./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/porting/synaptics/ei_classifier_porting.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-EdgeImpulse_magic-2d-writter-2d-augmented-2d-cnn_MachineLearning-2f-edgeimpulse-2f-edge-2d-impulse-2d-sdk-2f-porting-2f-synaptics

