################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/widgets/bar/lv_example_bar_1.c \
../lvgl/examples/widgets/bar/lv_example_bar_2.c \
../lvgl/examples/widgets/bar/lv_example_bar_3.c \
../lvgl/examples/widgets/bar/lv_example_bar_4.c \
../lvgl/examples/widgets/bar/lv_example_bar_5.c \
../lvgl/examples/widgets/bar/lv_example_bar_6.c 

OBJS += \
./lvgl/examples/widgets/bar/lv_example_bar_1.o \
./lvgl/examples/widgets/bar/lv_example_bar_2.o \
./lvgl/examples/widgets/bar/lv_example_bar_3.o \
./lvgl/examples/widgets/bar/lv_example_bar_4.o \
./lvgl/examples/widgets/bar/lv_example_bar_5.o \
./lvgl/examples/widgets/bar/lv_example_bar_6.o 

C_DEPS += \
./lvgl/examples/widgets/bar/lv_example_bar_1.d \
./lvgl/examples/widgets/bar/lv_example_bar_2.d \
./lvgl/examples/widgets/bar/lv_example_bar_3.d \
./lvgl/examples/widgets/bar/lv_example_bar_4.d \
./lvgl/examples/widgets/bar/lv_example_bar_5.d \
./lvgl/examples/widgets/bar/lv_example_bar_6.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/widgets/bar/%.o lvgl/examples/widgets/bar/%.su lvgl/examples/widgets/bar/%.cyclo: ../lvgl/examples/widgets/bar/%.c lvgl/examples/widgets/bar/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"E:/GitHub/lv_port_stm32f746_disco" -I"E:/GitHub/lv_port_stm32f746_disco/CMSIS/core" -I"E:/GitHub/lv_port_stm32f746_disco/HAL_Driver/Inc" -I"E:/GitHub/lv_port_stm32f746_disco/Utilities/STM32746G-Discovery" -I"E:/GitHub/lv_port_stm32f746_disco/CMSIS/device" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-widgets-2f-bar

clean-lvgl-2f-examples-2f-widgets-2f-bar:
	-$(RM) ./lvgl/examples/widgets/bar/lv_example_bar_1.cyclo ./lvgl/examples/widgets/bar/lv_example_bar_1.d ./lvgl/examples/widgets/bar/lv_example_bar_1.o ./lvgl/examples/widgets/bar/lv_example_bar_1.su ./lvgl/examples/widgets/bar/lv_example_bar_2.cyclo ./lvgl/examples/widgets/bar/lv_example_bar_2.d ./lvgl/examples/widgets/bar/lv_example_bar_2.o ./lvgl/examples/widgets/bar/lv_example_bar_2.su ./lvgl/examples/widgets/bar/lv_example_bar_3.cyclo ./lvgl/examples/widgets/bar/lv_example_bar_3.d ./lvgl/examples/widgets/bar/lv_example_bar_3.o ./lvgl/examples/widgets/bar/lv_example_bar_3.su ./lvgl/examples/widgets/bar/lv_example_bar_4.cyclo ./lvgl/examples/widgets/bar/lv_example_bar_4.d ./lvgl/examples/widgets/bar/lv_example_bar_4.o ./lvgl/examples/widgets/bar/lv_example_bar_4.su ./lvgl/examples/widgets/bar/lv_example_bar_5.cyclo ./lvgl/examples/widgets/bar/lv_example_bar_5.d ./lvgl/examples/widgets/bar/lv_example_bar_5.o ./lvgl/examples/widgets/bar/lv_example_bar_5.su ./lvgl/examples/widgets/bar/lv_example_bar_6.cyclo ./lvgl/examples/widgets/bar/lv_example_bar_6.d ./lvgl/examples/widgets/bar/lv_example_bar_6.o ./lvgl/examples/widgets/bar/lv_example_bar_6.su

.PHONY: clean-lvgl-2f-examples-2f-widgets-2f-bar

