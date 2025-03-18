################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/PROJECTS/Hardware/STM32/32F746GDISCOVERY/CubeIde/LTDC_PicturesFromSDCard/SW4STM32/startup_stm32f746xx.s 

C_SRCS += \
C:/PROJECTS/Hardware/STM32/32F746GDISCOVERY/CubeIde/LTDC_PicturesFromSDCard/SW4STM32/syscalls.c 

OBJS += \
./Application/SW4STM32/startup_stm32f746xx.o \
./Application/SW4STM32/syscalls.o 

S_DEPS += \
./Application/SW4STM32/startup_stm32f746xx.d 

C_DEPS += \
./Application/SW4STM32/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
Application/SW4STM32/startup_stm32f746xx.o: C:/PROJECTS/Hardware/STM32/32F746GDISCOVERY/CubeIde/LTDC_PicturesFromSDCard/SW4STM32/startup_stm32f746xx.s Application/SW4STM32/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Application/SW4STM32/syscalls.o: C:/PROJECTS/Hardware/STM32/32F746GDISCOVERY/CubeIde/LTDC_PicturesFromSDCard/SW4STM32/syscalls.c Application/SW4STM32/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32746G-Discovery -I../../../Utilities -I../../../Utilities/Fonts -I../../../Middlewares/Third_Party/FatFs/src -I../../../Drivers/BSP/Components -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-SW4STM32

clean-Application-2f-SW4STM32:
	-$(RM) ./Application/SW4STM32/startup_stm32f746xx.d ./Application/SW4STM32/startup_stm32f746xx.o ./Application/SW4STM32/syscalls.cyclo ./Application/SW4STM32/syscalls.d ./Application/SW4STM32/syscalls.o ./Application/SW4STM32/syscalls.su

.PHONY: clean-Application-2f-SW4STM32

