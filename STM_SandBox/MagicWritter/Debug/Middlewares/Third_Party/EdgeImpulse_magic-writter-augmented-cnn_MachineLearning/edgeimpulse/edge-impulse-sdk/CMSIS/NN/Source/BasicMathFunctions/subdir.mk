################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_add_s8.c \
../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_mul_s8.c 

C_DEPS += \
./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_add_s8.d \
./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_mul_s8.d 

OBJS += \
./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_add_s8.o \
./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_mul_s8.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/%.o Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/%.su: ../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/%.c Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -DUSE_STM32F429I_DISCO -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/STM32F429I-Discovery -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-cnn_MachineLearning/edgeimpulse/ -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-dnn_MachineLearning/edgeimpulse/ -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-dnn_MachineLearning/edgeimpulse/ -I../Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-EdgeImpulse_magic-2d-writter-2d-augmented-2d-cnn_MachineLearning-2f-edgeimpulse-2f-edge-2d-impulse-2d-sdk-2f-CMSIS-2f-NN-2f-Source-2f-BasicMathFunctions

clean-Middlewares-2f-Third_Party-2f-EdgeImpulse_magic-2d-writter-2d-augmented-2d-cnn_MachineLearning-2f-edgeimpulse-2f-edge-2d-impulse-2d-sdk-2f-CMSIS-2f-NN-2f-Source-2f-BasicMathFunctions:
	-$(RM) ./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_add_s8.d ./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_add_s8.o ./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_add_s8.su ./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_mul_s8.d ./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_mul_s8.o ./Middlewares/Third_Party/EdgeImpulse_magic-writter-augmented-cnn_MachineLearning/edgeimpulse/edge-impulse-sdk/CMSIS/NN/Source/BasicMathFunctions/arm_elementwise_mul_s8.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-EdgeImpulse_magic-2d-writter-2d-augmented-2d-cnn_MachineLearning-2f-edgeimpulse-2f-edge-2d-impulse-2d-sdk-2f-CMSIS-2f-NN-2f-Source-2f-BasicMathFunctions

