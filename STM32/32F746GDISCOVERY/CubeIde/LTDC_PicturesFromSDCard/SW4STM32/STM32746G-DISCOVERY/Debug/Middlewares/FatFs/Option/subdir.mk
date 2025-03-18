################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/robby/STM32CubeIDE/workspace_1.18.0/LTDC_PicturesFromSDCard/Middlewares/Third_Party/FatFs/src/option/syscall.c \
C:/Users/robby/STM32CubeIDE/workspace_1.18.0/LTDC_PicturesFromSDCard/Middlewares/Third_Party/FatFs/src/option/unicode.c 

OBJS += \
./Middlewares/FatFs/Option/syscall.o \
./Middlewares/FatFs/Option/unicode.o 

C_DEPS += \
./Middlewares/FatFs/Option/syscall.d \
./Middlewares/FatFs/Option/unicode.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/Option/syscall.o: C:/Users/robby/STM32CubeIDE/workspace_1.18.0/LTDC_PicturesFromSDCard/Middlewares/Third_Party/FatFs/src/option/syscall.c Middlewares/FatFs/Option/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32746G-Discovery -I../../../Utilities -I../../../Utilities/Fonts -I../../../Middlewares/Third_Party/FatFs/src -I../../../Drivers/BSP/Components -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FatFs/Option/unicode.o: C:/Users/robby/STM32CubeIDE/workspace_1.18.0/LTDC_PicturesFromSDCard/Middlewares/Third_Party/FatFs/src/option/unicode.c Middlewares/FatFs/Option/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32746G-Discovery -I../../../Utilities -I../../../Utilities/Fonts -I../../../Middlewares/Third_Party/FatFs/src -I../../../Drivers/BSP/Components -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FatFs-2f-Option

clean-Middlewares-2f-FatFs-2f-Option:
	-$(RM) ./Middlewares/FatFs/Option/syscall.cyclo ./Middlewares/FatFs/Option/syscall.d ./Middlewares/FatFs/Option/syscall.o ./Middlewares/FatFs/Option/syscall.su ./Middlewares/FatFs/Option/unicode.cyclo ./Middlewares/FatFs/Option/unicode.d ./Middlewares/FatFs/Option/unicode.o ./Middlewares/FatFs/Option/unicode.su

.PHONY: clean-Middlewares-2f-FatFs-2f-Option

