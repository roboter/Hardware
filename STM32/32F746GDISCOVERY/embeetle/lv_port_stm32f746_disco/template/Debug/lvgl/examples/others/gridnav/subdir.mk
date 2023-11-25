################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/others/gridnav/lv_example_gridnav_1.c \
../lvgl/examples/others/gridnav/lv_example_gridnav_2.c \
../lvgl/examples/others/gridnav/lv_example_gridnav_3.c \
../lvgl/examples/others/gridnav/lv_example_gridnav_4.c 

OBJS += \
./lvgl/examples/others/gridnav/lv_example_gridnav_1.o \
./lvgl/examples/others/gridnav/lv_example_gridnav_2.o \
./lvgl/examples/others/gridnav/lv_example_gridnav_3.o \
./lvgl/examples/others/gridnav/lv_example_gridnav_4.o 

C_DEPS += \
./lvgl/examples/others/gridnav/lv_example_gridnav_1.d \
./lvgl/examples/others/gridnav/lv_example_gridnav_2.d \
./lvgl/examples/others/gridnav/lv_example_gridnav_3.d \
./lvgl/examples/others/gridnav/lv_example_gridnav_4.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/others/gridnav/%.o lvgl/examples/others/gridnav/%.su lvgl/examples/others/gridnav/%.cyclo: ../lvgl/examples/others/gridnav/%.c lvgl/examples/others/gridnav/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"E:/GitHub/lv_port_stm32f746_disco" -I"E:/GitHub/lv_port_stm32f746_disco/CMSIS/core" -I"E:/GitHub/lv_port_stm32f746_disco/HAL_Driver/Inc" -I"E:/GitHub/lv_port_stm32f746_disco/Utilities/STM32746G-Discovery" -I"E:/GitHub/lv_port_stm32f746_disco/CMSIS/device" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-others-2f-gridnav

clean-lvgl-2f-examples-2f-others-2f-gridnav:
	-$(RM) ./lvgl/examples/others/gridnav/lv_example_gridnav_1.cyclo ./lvgl/examples/others/gridnav/lv_example_gridnav_1.d ./lvgl/examples/others/gridnav/lv_example_gridnav_1.o ./lvgl/examples/others/gridnav/lv_example_gridnav_1.su ./lvgl/examples/others/gridnav/lv_example_gridnav_2.cyclo ./lvgl/examples/others/gridnav/lv_example_gridnav_2.d ./lvgl/examples/others/gridnav/lv_example_gridnav_2.o ./lvgl/examples/others/gridnav/lv_example_gridnav_2.su ./lvgl/examples/others/gridnav/lv_example_gridnav_3.cyclo ./lvgl/examples/others/gridnav/lv_example_gridnav_3.d ./lvgl/examples/others/gridnav/lv_example_gridnav_3.o ./lvgl/examples/others/gridnav/lv_example_gridnav_3.su ./lvgl/examples/others/gridnav/lv_example_gridnav_4.cyclo ./lvgl/examples/others/gridnav/lv_example_gridnav_4.d ./lvgl/examples/others/gridnav/lv_example_gridnav_4.o ./lvgl/examples/others/gridnav/lv_example_gridnav_4.su

.PHONY: clean-lvgl-2f-examples-2f-others-2f-gridnav

