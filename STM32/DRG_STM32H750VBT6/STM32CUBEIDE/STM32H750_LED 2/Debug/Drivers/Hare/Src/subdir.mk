################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Hare/Src/lcd_fonts.c \
../Drivers/Hare/Src/lcd_image.c \
../Drivers/Hare/Src/lcd_model.c \
../Drivers/Hare/Src/sccb.c 

OBJS += \
./Drivers/Hare/Src/lcd_fonts.o \
./Drivers/Hare/Src/lcd_image.o \
./Drivers/Hare/Src/lcd_model.o \
./Drivers/Hare/Src/sccb.o 

C_DEPS += \
./Drivers/Hare/Src/lcd_fonts.d \
./Drivers/Hare/Src/lcd_image.d \
./Drivers/Hare/Src/lcd_model.d \
./Drivers/Hare/Src/sccb.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Hare/Src/%.o Drivers/Hare/Src/%.su Drivers/Hare/Src/%.cyclo: ../Drivers/Hare/Src/%.c Drivers/Hare/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../FatFs -I../Drivers/Hare/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Hare-2f-Src

clean-Drivers-2f-Hare-2f-Src:
	-$(RM) ./Drivers/Hare/Src/lcd_fonts.cyclo ./Drivers/Hare/Src/lcd_fonts.d ./Drivers/Hare/Src/lcd_fonts.o ./Drivers/Hare/Src/lcd_fonts.su ./Drivers/Hare/Src/lcd_image.cyclo ./Drivers/Hare/Src/lcd_image.d ./Drivers/Hare/Src/lcd_image.o ./Drivers/Hare/Src/lcd_image.su ./Drivers/Hare/Src/lcd_model.cyclo ./Drivers/Hare/Src/lcd_model.d ./Drivers/Hare/Src/lcd_model.o ./Drivers/Hare/Src/lcd_model.su ./Drivers/Hare/Src/sccb.cyclo ./Drivers/Hare/Src/sccb.d ./Drivers/Hare/Src/sccb.o ./Drivers/Hare/Src/sccb.su

.PHONY: clean-Drivers-2f-Hare-2f-Src

