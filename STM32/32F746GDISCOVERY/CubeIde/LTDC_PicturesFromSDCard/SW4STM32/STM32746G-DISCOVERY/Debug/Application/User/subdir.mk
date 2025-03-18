################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/robby/STM32CubeIDE/workspace_1.18.0/LTDC_PicturesFromSDCard/Src/fatfs_storage.c \
C:/Users/robby/STM32CubeIDE/workspace_1.18.0/LTDC_PicturesFromSDCard/Src/main.c \
C:/Users/robby/STM32CubeIDE/workspace_1.18.0/LTDC_PicturesFromSDCard/Src/stm32f7xx_it.c 

OBJS += \
./Application/User/fatfs_storage.o \
./Application/User/main.o \
./Application/User/stm32f7xx_it.o 

C_DEPS += \
./Application/User/fatfs_storage.d \
./Application/User/main.d \
./Application/User/stm32f7xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/fatfs_storage.o: C:/Users/robby/STM32CubeIDE/workspace_1.18.0/LTDC_PicturesFromSDCard/Src/fatfs_storage.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32746G-Discovery -I../../../Utilities -I../../../Utilities/Fonts -I../../../Middlewares/Third_Party/FatFs/src -I../../../Drivers/BSP/Components -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/main.o: C:/Users/robby/STM32CubeIDE/workspace_1.18.0/LTDC_PicturesFromSDCard/Src/main.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32746G-Discovery -I../../../Utilities -I../../../Utilities/Fonts -I../../../Middlewares/Third_Party/FatFs/src -I../../../Drivers/BSP/Components -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32f7xx_it.o: C:/Users/robby/STM32CubeIDE/workspace_1.18.0/LTDC_PicturesFromSDCard/Src/stm32f7xx_it.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DUSE_STM32746G_DISCO -c -I../../../Inc -I../../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../../Drivers/BSP/STM32746G-Discovery -I../../../Utilities -I../../../Utilities/Fonts -I../../../Middlewares/Third_Party/FatFs/src -I../../../Drivers/BSP/Components -I../../../Drivers/CMSIS/Include -Os -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User

clean-Application-2f-User:
	-$(RM) ./Application/User/fatfs_storage.cyclo ./Application/User/fatfs_storage.d ./Application/User/fatfs_storage.o ./Application/User/fatfs_storage.su ./Application/User/main.cyclo ./Application/User/main.d ./Application/User/main.o ./Application/User/main.su ./Application/User/stm32f7xx_it.cyclo ./Application/User/stm32f7xx_it.d ./Application/User/stm32f7xx_it.o ./Application/User/stm32f7xx_it.su

.PHONY: clean-Application-2f-User

