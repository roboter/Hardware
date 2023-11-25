################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/tests/unity/unity.c \
../lvgl/tests/unity/unity_support.c 

OBJS += \
./lvgl/tests/unity/unity.o \
./lvgl/tests/unity/unity_support.o 

C_DEPS += \
./lvgl/tests/unity/unity.d \
./lvgl/tests/unity/unity_support.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/tests/unity/%.o lvgl/tests/unity/%.su lvgl/tests/unity/%.cyclo: ../lvgl/tests/unity/%.c lvgl/tests/unity/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"E:/GitHub/lv_port_stm32f746_disco" -I"E:/GitHub/lv_port_stm32f746_disco/CMSIS/core" -I"E:/GitHub/lv_port_stm32f746_disco/HAL_Driver/Inc" -I"E:/GitHub/lv_port_stm32f746_disco/Utilities/STM32746G-Discovery" -I"E:/GitHub/lv_port_stm32f746_disco/CMSIS/device" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-tests-2f-unity

clean-lvgl-2f-tests-2f-unity:
	-$(RM) ./lvgl/tests/unity/unity.cyclo ./lvgl/tests/unity/unity.d ./lvgl/tests/unity/unity.o ./lvgl/tests/unity/unity.su ./lvgl/tests/unity/unity_support.cyclo ./lvgl/tests/unity/unity_support.d ./lvgl/tests/unity/unity_support.o ./lvgl/tests/unity/unity_support.su

.PHONY: clean-lvgl-2f-tests-2f-unity

