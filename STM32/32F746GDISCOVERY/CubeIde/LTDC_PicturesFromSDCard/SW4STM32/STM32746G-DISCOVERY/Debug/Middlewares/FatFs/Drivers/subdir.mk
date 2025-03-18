################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/PROJECTS/Hardware/STM32/32F746GDISCOVERY/CubeIde/LTDC_PicturesFromSDCard/Src/sd_diskio.c 

OBJS += \
./Middlewares/FatFs/Drivers/sd_diskio.o 

C_DEPS += \
./Middlewares/FatFs/Drivers/sd_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/Drivers/sd_diskio.o: C:/PROJECTS/Hardware/STM32/32F746GDISCOVERY/CubeIde/LTDC_PicturesFromSDCard/Src/sd_diskio.c Middlewares/FatFs/Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32746G-Discovery -I../../../Utilities -I../../../Utilities/Fonts -I../../../Middlewares/Third_Party/FatFs/src -I../../../Drivers/BSP/Components -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FatFs-2f-Drivers

clean-Middlewares-2f-FatFs-2f-Drivers:
	-$(RM) ./Middlewares/FatFs/Drivers/sd_diskio.cyclo ./Middlewares/FatFs/Drivers/sd_diskio.d ./Middlewares/FatFs/Drivers/sd_diskio.o ./Middlewares/FatFs/Drivers/sd_diskio.su

.PHONY: clean-Middlewares-2f-FatFs-2f-Drivers

