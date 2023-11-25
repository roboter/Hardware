################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_1.c \
../lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_2.c 

OBJS += \
./lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_1.o \
./lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_2.o 

C_DEPS += \
./lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_1.d \
./lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_2.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/libs/ffmpeg/%.o lvgl/examples/libs/ffmpeg/%.su lvgl/examples/libs/ffmpeg/%.cyclo: ../lvgl/examples/libs/ffmpeg/%.c lvgl/examples/libs/ffmpeg/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DSTM32 -DSTM32F7 -DSTM32F746NGHx -DSTM32F746G_DISCO -DDEBUG -DSTM32F746xx -DUSE_HAL_DRIVER -c -I"E:/GitHub/lv_port_stm32f746_disco" -I"E:/GitHub/lv_port_stm32f746_disco/CMSIS/core" -I"E:/GitHub/lv_port_stm32f746_disco/HAL_Driver/Inc" -I"E:/GitHub/lv_port_stm32f746_disco/Utilities/STM32746G-Discovery" -I"E:/GitHub/lv_port_stm32f746_disco/CMSIS/device" -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-libs-2f-ffmpeg

clean-lvgl-2f-examples-2f-libs-2f-ffmpeg:
	-$(RM) ./lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_1.cyclo ./lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_1.d ./lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_1.o ./lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_1.su ./lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_2.cyclo ./lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_2.d ./lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_2.o ./lvgl/examples/libs/ffmpeg/lv_example_ffmpeg_2.su

.PHONY: clean-lvgl-2f-examples-2f-libs-2f-ffmpeg

