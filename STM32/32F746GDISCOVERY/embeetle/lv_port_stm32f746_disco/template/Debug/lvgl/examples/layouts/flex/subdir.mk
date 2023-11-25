################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/layouts/flex/lv_example_flex_1.c \
../lvgl/examples/layouts/flex/lv_example_flex_2.c \
../lvgl/examples/layouts/flex/lv_example_flex_3.c \
../lvgl/examples/layouts/flex/lv_example_flex_4.c \
../lvgl/examples/layouts/flex/lv_example_flex_5.c \
../lvgl/examples/layouts/flex/lv_example_flex_6.c 

OBJS += \
./lvgl/examples/layouts/flex/lv_example_flex_1.o \
./lvgl/examples/layouts/flex/lv_example_flex_2.o \
./lvgl/examples/layouts/flex/lv_example_flex_3.o \
./lvgl/examples/layouts/flex/lv_example_flex_4.o \
./lvgl/examples/layouts/flex/lv_example_flex_5.o \
./lvgl/examples/layouts/flex/lv_example_flex_6.o 

C_DEPS += \
./lvgl/examples/layouts/flex/lv_example_flex_1.d \
./lvgl/examples/layouts/flex/lv_example_flex_2.d \
./lvgl/examples/layouts/flex/lv_example_flex_3.d \
./lvgl/examples/layouts/flex/lv_example_flex_4.d \
./lvgl/examples/layouts/flex/lv_example_flex_5.d \
./lvgl/examples/layouts/flex/lv_example_flex_6.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/layouts/flex/%.o lvgl/examples/layouts/flex/%.su lvgl/examples/layouts/flex/%.cyclo: ../lvgl/examples/layouts/flex/%.c lvgl/examples/layouts/flex/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"E:/GitHub/lv_port_stm32f746_disco" -I"E:/GitHub/lv_port_stm32f746_disco/CMSIS/core" -I"E:/GitHub/lv_port_stm32f746_disco/HAL_Driver/Inc" -I"E:/GitHub/lv_port_stm32f746_disco/Utilities/STM32746G-Discovery" -I"E:/GitHub/lv_port_stm32f746_disco/CMSIS/device" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-layouts-2f-flex

clean-lvgl-2f-examples-2f-layouts-2f-flex:
	-$(RM) ./lvgl/examples/layouts/flex/lv_example_flex_1.cyclo ./lvgl/examples/layouts/flex/lv_example_flex_1.d ./lvgl/examples/layouts/flex/lv_example_flex_1.o ./lvgl/examples/layouts/flex/lv_example_flex_1.su ./lvgl/examples/layouts/flex/lv_example_flex_2.cyclo ./lvgl/examples/layouts/flex/lv_example_flex_2.d ./lvgl/examples/layouts/flex/lv_example_flex_2.o ./lvgl/examples/layouts/flex/lv_example_flex_2.su ./lvgl/examples/layouts/flex/lv_example_flex_3.cyclo ./lvgl/examples/layouts/flex/lv_example_flex_3.d ./lvgl/examples/layouts/flex/lv_example_flex_3.o ./lvgl/examples/layouts/flex/lv_example_flex_3.su ./lvgl/examples/layouts/flex/lv_example_flex_4.cyclo ./lvgl/examples/layouts/flex/lv_example_flex_4.d ./lvgl/examples/layouts/flex/lv_example_flex_4.o ./lvgl/examples/layouts/flex/lv_example_flex_4.su ./lvgl/examples/layouts/flex/lv_example_flex_5.cyclo ./lvgl/examples/layouts/flex/lv_example_flex_5.d ./lvgl/examples/layouts/flex/lv_example_flex_5.o ./lvgl/examples/layouts/flex/lv_example_flex_5.su ./lvgl/examples/layouts/flex/lv_example_flex_6.cyclo ./lvgl/examples/layouts/flex/lv_example_flex_6.d ./lvgl/examples/layouts/flex/lv_example_flex_6.o ./lvgl/examples/layouts/flex/lv_example_flex_6.su

.PHONY: clean-lvgl-2f-examples-2f-layouts-2f-flex

